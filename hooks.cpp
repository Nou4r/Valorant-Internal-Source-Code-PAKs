#define _CRT_SECURE_NO_WARNINGS
// MY BASE HERE
#include "hooks.hpp"
#include "Menu/menu.hpp"
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "mutex"
#include "ret_spoof.h"
#include "spoof.h"
#include <map>
#include <string>

#pragma comment(lib, "winmm.lib")
// #include "skin.hpp"

uintptr_t camera_engine;
bool should_hook_gay;

int screen_width = 0;
int screen_height = 0;

bool InGame = 0;
uworld* UWorldSave;
float spin_value;

static auto OldAimAngles = fvector();

// visibility is now computed locally inside the actor loop - no more stale
// globals

namespace keys {
    fkey left_mouse;
    fkey right_mouse;
    fkey insert;

    fkey w;
    fkey a;
    fkey s;
    fkey d;
    fkey space;

    fkey capslock;
} // namespace keys

// For aimbot
inline float GetWeaponFireRate(ashootercharacter* shooter) {
    if (!shooter) return 0.15f;

    auto inv = shooter->get_inventory();
    if (!inv) return 0.15f;

    auto eq = inv->get_current_equippable();
    if (!eq) return 0.15f;

    fstring weapon_name = system::get_object_name(eq);
    if (!weapon_name.c_str()) return 0.15f;

    std::wstring wname = weapon_name.c_str();
    if (wname.find(L"Operator") != std::wstring::npos) return 1.52f;   // 1.50 -> 1.52
    if (wname.find(L"Marshal") != std::wstring::npos)  return 1.52f;
    if (wname.find(L"Outlaw") != std::wstring::npos)   return 0.42f;   // 0.40 -> 0.42
    if (wname.find(L"Guardian") != std::wstring::npos)  return 0.52f;   // 0.50 -> 0.52
    if (wname.find(L"Vandal") != std::wstring::npos)    return 0.150f;  // 0.133 -> 0.150
    if (wname.find(L"Phantom") != std::wstring::npos)   return 0.150f;
    if (wname.find(L"Sheriff") != std::wstring::npos)   return 0.42f;   // 0.40 -> 0.42
    if (wname.find(L"Ghost") != std::wstring::npos)     return 0.125f;  // 0.105 -> 0.125
    if (wname.find(L"Spectre") != std::wstring::npos)   return 0.105f;  // 0.085 -> 0.105
    if (wname.find(L"Stinger") != std::wstring::npos)   return 0.090f;  // 0.070 -> 0.090
    if (wname.find(L"Odin") != std::wstring::npos)      return 0.080f;  // 0.060 -> 0.080
    if (wname.find(L"Ares") != std::wstring::npos)      return 0.120f;  // 0.100 -> 0.120
    if (wname.find(L"Bulldog") != std::wstring::npos)   return 0.320f;  // 0.300 -> 0.320
    if (wname.find(L"Headhunter") != std::wstring::npos) return 0.42f;   // 0.40 -> 0.42

    // Shotgun + Classic + Frenzy
    if (wname.find(L"Bucky") != std::wstring::npos)    return 0.27f;   // 0.25 -> 0.27
    if (wname.find(L"Judge") != std::wstring::npos)    return 0.32f;   // 0.30 -> 0.32
    if (wname.find(L"Shorty") != std::wstring::npos)   return 0.22f;   // 0.20 -> 0.22
    if (wname.find(L"Classic") != std::wstring::npos)  return 0.22f;
    if (wname.find(L"Frenzy") != std::wstring::npos)   return 0.115f;  // 0.095 -> 0.115

    return 0.17f;
}


void* m_memset(void* dest, char c, unsigned int len) {
    unsigned int i;
    unsigned int fill;
    unsigned int chunks = len / sizeof(fill);
    char* char_dest = (char*)dest;
    unsigned int* uint_dest = (unsigned int*)dest;
    fill = (c << 24) + (c << 16) + (c << 8) + c;

    for (i = len; i > chunks * sizeof(fill); i--) {
        char_dest[i - 1] = c;
    }

    for (i = chunks; i > 0; i--) {
        uint_dest[i - 1] = fill;
    }

    return dest;
}

void* m_memcpy(void* dest, void* src, unsigned int len) {
    unsigned int i;
    char* char_src = (char*)src;
    char* char_dest = (char*)dest;
    for (i = 0; i < len; i++) {
        char_dest[i] = char_src[i];
    }
    return dest;
}

static bool previous_viewmodel_state = false;

float brillpg = 1.0f;
flinearcolor hlpclrg{ 1.0f, 0.5f, 0.0f, 0.9f };

static flinearcolor tlrclr = { 1.0f, 1.0f, 1.0f, 0.7f };
static flinearcolor basee_color = { 0.835f, 0.576f, 0.584f, 1.0f };

namespace hooks {
    static int TargetX = 0;
    static int TargetY = 0;
    float ESPThickness = 1;
    bool enemiesarround = true;
    int enemyID = 0;
    int enemyIDvis = 0;
    int CloseRangeDistanceID = 0;
    float CloseRangeDistance = 50.f;

    static bool auto_shot_active = false;
    static ashootercharacter* safe_target_actor = nullptr;
    static std::mutex target_mutex; // Mutex pour synchroniser l'accÃ¨s

    aplayercontroller* controllers;

    acknowledgedpawn* pawn;

    aplayercameramanager* camera_cache;

    ashootercharacter* character;

    ashootercharacter* target_actor;

    inline static float FOVChangorSprite = 5.0f;

    inline static float Glow1 = 10.0f;
    inline static flinearcolor fresnel(2.093f, 0.019f, 20.0f, Glow1);

    inline float fresnelBaseR = 2.093f;
    inline float fresnelBaseG = 0.019f;
    inline float fresnelBaseB = 20.0f;

    // inline flinearcolor handcolor(fresnelBaseR, fresnelBaseG, fresnelBaseB,
    // Glow1);

    /*  void Recoil_Control() {
          Sleep(3);
          mouse.mouse_event(TargetX, 5, 0);
      }*/

    flinearcolor get_color(bool condition) {
        return condition ? flinearcolor{ 0.1f, 1.0f, 0.1f, 1 }
        : flinearcolor{ 1.0f, 0.0f, 0.0f, 1 };
    }

    static flinearcolor Invisible{
        255.0f, 0.0f, 0.0f, 1.0f }; // Couleur rouge pour les Ã©lÃ©ments invisibles

    inline flinearcolor ChamsColor = Invisible;

    float rainbowTime =
        0; // Le temps qui augmentera pour gÃ©nÃ©rer un arc-en-ciel dynamique

    // flinearcolor Invisible = flinearcolor(0.0f, 0.0f, 0.0f, 0.0f);  // Invisible
    // est une couleur de base (transparent ou noir)

    // Fonction pour gÃ©nÃ©rer une couleur arc-en-ciel en fonction du temps
    flinearcolor GetRainbowColor(float time) {
        const float PI = 3.14159265359f;
        float r = 0.5f + 0.5f * sin(time);
        float g = 0.5f + 0.5f * sin(time + 2.0f * PI / 3.0f);
        float b = 0.5f + 0.5f * sin(time + 4.0f * PI / 3.0f);
        return flinearcolor(r, g, b, 1.0f); // Alpha Ã  1.0 pour la pleine opacitÃ©
    }

    fvector2d posss = { 0.f, 0.f };

    auto calculate_box_dimensions =
        [](fvector2d head_long_out, fvector2d base_out) -> std::pair<float, float> {
        float box_height = abs(head_long_out.y - base_out.y);
        float box_width = box_height * 0.55f;
        return { box_width, box_height };
        };

    auto get_target_bone_matrix = [](uskeletalmeshcomponent* mesh,
        int bone) -> fvector {
            switch (bone) {
            case 0:
                return mesh->get_bone_location(8);
                break;
            case 1:
                return mesh->get_bone_location(6);
                break;
            case 2:
                return mesh->get_bone_location(4);
                break;
            default:
                return fvector();
            }
        };

    void draw_head(ucanvas* canvas, uobject* Font, const wchar_t* text,
        flinearcolor color, fvector2d pos) {
        canvas->k2_drawtext(menu::font, fstring(text), pos, { 1.50f, 1.50f }, color,
            0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true,
            { 0, 0, 0, 0.90f });
    }

    float DegreeToRadian(float degrees) {
        return degrees * (3.1415926535897932f / 180);
    }

    void draw_head2(ucanvas* canvas, uobject* Font, const wchar_t* text,
        flinearcolor color, fvector2d pos) {
        flinearcolor white_color =
            flinearcolor(1.0f, 1.0f, 1.0f, 1.0f); // Blanc (totalement opaque)

        // DÃ©finir la couleur de l'ombre : une version grise avec une opacitÃ©
        // rÃ©duite (50 %)
        flinearcolor shadow_color =
            flinearcolor(0.5f, 0.5f, 0.5f, 0.5f); // Gris semi-transparent

        // DÃ©finir le dÃ©calage de l'ombre pour le texte (lÃ©gÃ¨rement dÃ©calÃ© en x
        // et y)
        fvector2d shadow_offset = fvector2d{ 2.0f, 2.0f };

        // Draw the shadow first (slightly offset from the original position)
        canvas->k2_drawtext(menu::font, fstring(text), pos + shadow_offset,
            { 1.0f, 1.0f }, shadow_color, 0.f, shadow_color,
            shadow_offset, true, true, true, { 0, 0, 0, 0.90f });

        // Draw the main text with the purple color (overlaid on top of the shadow)
        canvas->k2_drawtext(menu::font, fstring(text), pos, { 1.0f, 1.0f }, white_color,
            0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true,
            { 0, 0, 0, 0.90f });
    }

    boolean in_rect(double centerX, double centerY, double radius, double x,
        double y) {
        return x >= centerX - radius && x <= centerX + radius &&
            y >= centerY - radius && y <= centerY + radius;
    }

    inline bool is_target_in_fov(double screen_center_x, double screen_center_y,
        fvector2d target_pos) {

        return in_rect(screen_center_x, screen_center_y, globals::aimbot::a1m_f0v,
            target_pos.x, target_pos.y);
    }

    __forceinline fvector GetBoneMatrix(void* Mesh, int BoneIndex) {

        if (!Mesh) [[unlikely]]
            return fvector(0.f, 0.f, 0.f);

        if (BoneIndex < 0) [[unlikely]]
            return fvector(0.f, 0.f, 0.f);

        using BoneMatrixFn = FMatrix * (__fastcall*)(void*, FMatrix*, int);
        static const BoneMatrixFn fn = reinterpret_cast<BoneMatrixFn>(
            memory::module_base + offsets::bone_matrix);

        FMatrix BoneMatrix;

        fn(Mesh, &BoneMatrix, BoneIndex);

        return fvector(BoneMatrix.WPlane.X, BoneMatrix.WPlane.Y, BoneMatrix.WPlane.Z);
    }

    // fvector GetBoneMatrix(void* Mesh, int Idx) {

    //    FMatrix Matrix;
    //    reinterpret_cast<FMatrix* (__cdecl*)(void*, FMatrix*, int, uintptr_t,
    //    void*)>(spoofcall_stub)(Mesh, &Matrix, Idx, 0x46C4660,
    //    (void*)(memory::module_base + offsets::bone_matrix));

    //
    //    return fvector(Matrix.WPlane.X, Matrix.WPlane.Y, Matrix.WPlane.Z);
    //}

    void DrawBox(ucanvas* can, fvector2d topleft, fvector2d downright,
        flinearcolor color) {

        if (!can) {
            return;
        }

        if (!topleft.is_valid() || !downright.is_valid()) {
            return;
        }

        if (topleft.x > downright.x || topleft.y > downright.y) {
            if (topleft.x > downright.x) {
                double temp = topleft.x;
                topleft.x = downright.x;
                downright.x = temp;
            }
            if (topleft.y > downright.y) {
                double temp = topleft.y;
                topleft.y = downright.y;
                downright.y = temp;
            }
        }

        double h = downright.y - topleft.y;
        double w = downright.x - topleft.x;

        if (h <= 0.0 || w <= 0.0) {
            return;
        }

        double thicc = (ESPThickness > 0.0) ? ESPThickness : 1.0;

        fvector2d topright = fvector2d(downright.x, topleft.y);
        fvector2d bottomleft = fvector2d(topleft.x, downright.y);

        can->k2_drawline(topleft, topright, thicc, color);
        can->k2_drawline(topright, downright, thicc, color);
        can->k2_drawline(downright, bottomleft, thicc, color);
        can->k2_drawline(bottomleft, topleft, thicc, color);
    }

    void Draw3DBox(ucanvas* canvas, aplayercontroller* controllers, fvector origin,
        fvector extent, const flinearcolor& color) {

        fvector vertex[8] = { origin + fvector(-extent.x, -extent.y, -extent.z),
                             origin + fvector(extent.x, -extent.y, -extent.z),
                             origin + fvector(extent.x, extent.y, -extent.z),
                             origin + fvector(-extent.x, extent.y, -extent.z),
                             origin + fvector(-extent.x, -extent.y, extent.z),
                             origin + fvector(extent.x, -extent.y, extent.z),
                             origin + fvector(extent.x, extent.y, extent.z),
                             origin + fvector(-extent.x, extent.y, extent.z) };

        fvector2d screenVertex[8];
        bool canProject = true;

        for (int i = 0; i < 8; i++) {

            if (!controllers->project_world_location_to_screen(
                vertex[i], screenVertex[i], false)) {
                canProject = false;
                break;
            }
        }

        if (!canProject)
            return;

        canvas->k2_drawline(screenVertex[0], screenVertex[1], ESPThickness, color);
        canvas->k2_drawline(screenVertex[1], screenVertex[2], ESPThickness, color);
        canvas->k2_drawline(screenVertex[2], screenVertex[3], ESPThickness, color);
        canvas->k2_drawline(screenVertex[3], screenVertex[0], ESPThickness, color);

        canvas->k2_drawline(screenVertex[4], screenVertex[5], ESPThickness, color);
        canvas->k2_drawline(screenVertex[5], screenVertex[6], ESPThickness, color);
        canvas->k2_drawline(screenVertex[6], screenVertex[7], ESPThickness, color);
        canvas->k2_drawline(screenVertex[7], screenVertex[4], ESPThickness, color);

        canvas->k2_drawline(screenVertex[0], screenVertex[4], ESPThickness, color);
        canvas->k2_drawline(screenVertex[1], screenVertex[5], ESPThickness, color);
        canvas->k2_drawline(screenVertex[2], screenVertex[6], ESPThickness, color);
        canvas->k2_drawline(screenVertex[3], screenVertex[7], ESPThickness, color);
    }
    void DrawCornerBox(ucanvas* canvas, int x, int y, int W, int H,
        flinearcolor color, int thickness) {

        float lineW = W / 3.0f;
        float lineH = H / 3.0f;

        // Convert flinearcolor to a color format compatible with k2_drawline
        flinearcolor clr = menu::RGBtoFLC(
            color.r, color.g, color.b); // Assuming RGBtoFLC converts correctly

        // Top-left corner
        canvas->k2_drawline(fvector2d(x, y), fvector2d(x, y + lineH), thickness,
            color); // Left vertical line
        canvas->k2_drawline(fvector2d(x, y), fvector2d(x + lineW, y), thickness,
            color); // Top horizontal line

        // Top-right corner
        canvas->k2_drawline(fvector2d(x + W - lineW, y), fvector2d(x + W, y),
            thickness, color); // Top horizontal line
        canvas->k2_drawline(fvector2d(x + W, y), fvector2d(x + W, y + lineH),
            thickness, color); // Right vertical line

        // Bottom-left corner
        canvas->k2_drawline(fvector2d(x, y + H - lineH), fvector2d(x, y + H),
            thickness, color); // Bottom-left vertical line
        canvas->k2_drawline(fvector2d(x, y + H), fvector2d(x + lineW, y + H),
            thickness, color); // Bottom horizontal line

        // Bottom-right corner
        canvas->k2_drawline(fvector2d(x + W - lineW, y + H), fvector2d(x + W, y + H),
            thickness, color); // Bottom-right horizontal line
        canvas->k2_drawline(fvector2d(x + W, y + H - lineH), fvector2d(x + W, y + H),
            thickness, color); // Right vertical line
    }

    bool bOutline = 1;

    // ═══════════════════════════════════════════════════════
    //  DAMAGE NUMBERS SYSTEM
    // ═══════════════════════════════════════════════════════
    struct DamageNumber {
        fvector   world_pos;   // 3D dünya konumu (düşmanın kafası)
        float     damage;
        float     alpha;
        float     rise_px;     // spawn'dan bu yana ekranda kaç px yukarı çıktı
        flinearcolor color;
        bool      is_kill;
        DWORD     spawn_time;
    };

    static std::vector<DamageNumber> g_damage_numbers;
    static float g_dmg_hue = 0.0f;

    static flinearcolor HueToRGB(float hue, float alpha = 1.0f) {
        hue = fmodf(hue, 360.0f);
        float s = 1.0f, v = 1.0f;
        int   i = (int)(hue / 60.0f) % 6;
        float f = (hue / 60.0f) - (int)(hue / 60.0f);
        float p = v * (1.0f - s);
        float q = v * (1.0f - f * s);
        float t = v * (1.0f - (1.0f - f) * s);
        switch (i) {
        case 0: return { v, t, p, alpha };
        case 1: return { q, v, p, alpha };
        case 2: return { p, v, t, alpha };
        case 3: return { p, q, v, alpha };
        case 4: return { t, p, v, alpha };
        default:return { v, p, q, alpha };
        }
    }

    // controllers parametresi ile çağrılır — her frame world→screen project eder
    static void RenderDamageNumbers(ucanvas* canvas, aplayercontroller* controllers) {
        if (g_damage_numbers.empty() || !controllers) return;

        DWORD now = GetTickCount();
        const float LIFETIME_MS = 5000.0f;  // 5 saniye
        const float RISE_SPEED = 35.0f;    // saniyede 35 piksel yukarı

        for (auto it = g_damage_numbers.begin(); it != g_damage_numbers.end(); ) {
            float elapsed = (float)(now - it->spawn_time) / 1000.0f; // saniye cinsinden
            if (elapsed * 1000.0f >= LIFETIME_MS) {
                it = g_damage_numbers.erase(it);
                continue;
            }

            float t = elapsed * 1000.0f / LIFETIME_MS;  // 0→1
            it->alpha = 1.0f - t;
            it->rise_px = elapsed * RISE_SPEED;

            // Her frame dünya pozisyonunu ekrana project et
            fvector2d screen = controllers->project_world_to_screen(it->world_pos);
            if (!screen.is_valid()) { ++it; continue; }

            float draw_x = screen.x;
            float draw_y = screen.y - it->rise_px;  // yukarı doğru kayar

            flinearcolor col = it->color;
            col.a = it->alpha;

            float scale = it->is_kill ? 1.6f : 1.2f;

            wchar_t buf[32];
            swprintf_s(buf, L"-%.0f", it->damage);

            canvas->k2_drawtext(
                menu::font, fstring(buf),
                { draw_x, draw_y },
                { scale, scale },
                col,
                0.f,
                { 0, 0, 0, col.a * 0.6f },
                { 0, 0 }, true, true, true,
                { 0, 0, 0, col.a * 0.8f }
            );

            ++it;
        }
    }
    // ═══════════════════════════════════════════════════════

    void draw_text(ucanvas* canvas, uobject* Font, const wchar_t* text,
        flinearcolor color, fvector2d pos) {
        canvas->k2_drawtext(menu::font, fstring(text), pos, { 1.00f, 1.00f }, color,
            0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true,
            { 0, 0, 0, 0.45f });
    }

    static void draw_text_rgb_string(ucanvas* canvas, uobject* Font, fstring text,
        float x, float y, flinearcolor color,
        bool CenterX = false) {
        canvas->k2_drawtext(menu::font, text, { x, y }, { 1.1f, 1.1f }, color, 0.f,
            { 0, 0, 0, 1.0f }, { 0, 0 }, CenterX, false, true,
            { 0, 0, 0, 1.0f });
    }

    int current_selection = 3;
    const int max_selection = 26;
    static bool open_canvas = true;

    currentequippable* myweapon;
    currentequippable* lastweapon;

    static flinearcolor maincolor{ 1.0f, 1.0f, 1.0f, 1.0f };
    float bowv4l = 1;

    void draw_triangle(ucanvas* canvas, int current_selection, float x, float y,
        float size, flinearcolor color) {
        static float time = 0.0f;

        float animationSpeed = 0.05f;
        float maxMovementRange = 4.0f;

        float animatedX = x + (sin(time) * maxMovementRange);

        time += animationSpeed;

        if (time > 6.2832f) {
            time -= 6.2832f;
        }

        fvector2d point1, point2, point3;

        switch (current_selection) {
        case 3:
            point1 = { animatedX, y };
            point2 = { animatedX + size, y + size / 2 };
            point3 = { animatedX, y + size };
            break;
        case 4:
            point1 = { animatedX, y };
            point2 = { animatedX + size / 2, y + size };
            point3 = { animatedX + size, y };
            break;
        case 5:
            point1 = { animatedX + size, y };
            point2 = { animatedX, y + size / 2 };
            point3 = { animatedX + size, y + size };
            break;
        case 6:
            point1 = { animatedX, y + size };
            point2 = { animatedX + size / 2, y };
            point3 = { animatedX + size, y + size };
            break;
        default:
            point1 = { animatedX, y };
            point2 = { animatedX + size, y + size / 2 };
            point3 = { animatedX, y + size };
            break;
        }

        canvas->k2_drawline(point1, point2, 2.0f, color);
        canvas->k2_drawline(point2, point3, 2.0f, color);
        canvas->k2_drawline(point3, point1, 2.0f, color);
    }

    void DrawAdaptiveBoundingBox(ucanvas* canvas, aplayercontroller* my_controller,
        uskeletalmeshcomponent* mesh, flinearcolor color) {
        if (!canvas || !my_controller || !mesh)
            return;

        fvector vHeadBone = mesh->get_bone_location(8);
        fvector vBaseBone = mesh->get_bone_location(0);

        if (!vHeadBone.is_valid() || !vBaseBone.is_valid())
            return;

        fvector2d bottom1, bottom2, bottom3, bottom4;
        fvector2d top1, top2, top3, top4;

        bool valid_projection =
            my_controller->project_world_location_to_screen(
                fvector(vBaseBone.x + 53, vBaseBone.y - 55, vBaseBone.z), bottom1,
                0) &&
            bottom1.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vBaseBone.x - 53, vBaseBone.y - 55, vBaseBone.z), bottom2,
                0) &&
            bottom2.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vBaseBone.x - 53, vBaseBone.y + 55, vBaseBone.z), bottom3,
                0) &&
            bottom3.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vBaseBone.x + 53, vBaseBone.y + 55, vBaseBone.z), bottom4,
                0) &&
            bottom4.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vHeadBone.x + 53, vHeadBone.y - 55, vHeadBone.z + 26), top1,
                0) &&
            top1.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vHeadBone.x - 53, vHeadBone.y - 55, vHeadBone.z + 26), top2,
                0) &&
            top2.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vHeadBone.x - 53, vHeadBone.y + 55, vHeadBone.z + 26), top3,
                0) &&
            top3.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vHeadBone.x + 53, vHeadBone.y + 55, vHeadBone.z + 26), top4,
                0) &&
            top4.is_valid();

        if (!valid_projection)
            return;

        float left_most =
            fmin(fmin(bottom1.x, bottom2.x), fmin(bottom3.x, bottom4.x)) - 1.0f;
        float right_most = fmax(fmax(top1.x, top2.x), fmax(top3.x, top4.x)) + 1.0f;
        float top_most = fmin(fmin(top1.y, top2.y), fmin(top3.y, top4.y)) - 5.0f;
        float bottom_most =
            fmax(fmax(bottom1.y, bottom2.y), fmax(bottom3.y, bottom4.y)) + 5.0f;

        fvector2d top_left = { left_most, top_most };
        fvector2d bottom_right = { right_most, bottom_most };

        if (globals::visuals::box2d) {
            canvas->k2_drawline(top_left, { bottom_right.x, top_left.y }, 1.5f, color);
            canvas->k2_drawline(top_left, { top_left.x, bottom_right.y }, 1.5f, color);
            canvas->k2_drawline(bottom_right, { bottom_right.x, top_left.y }, 1.5f,
                color);
            canvas->k2_drawline(bottom_right, { top_left.x, bottom_right.y }, 1.5f,
                color);
        }
    }

    void DrawAdaptiveCornerBox(ucanvas* canvas, aplayercontroller* my_controller,
        uskeletalmeshcomponent* mesh, flinearcolor color,
        double thickness = 1.5f) {
        if (!canvas || !my_controller || !mesh)
            return;

        fvector vHeadBone = mesh->get_bone_location(8);
        fvector vBaseBone = mesh->get_bone_location(0);
        if (!vHeadBone.is_valid() || !vBaseBone.is_valid())
            return;

        fvector2d bottom1, bottom2, bottom3, bottom4;
        fvector2d top1, top2, top3, top4;

        bool valid_projection =
            my_controller->project_world_location_to_screen(
                fvector(vBaseBone.x + 53, vBaseBone.y - 55, vBaseBone.z), bottom1,
                0) &&
            bottom1.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vBaseBone.x - 53, vBaseBone.y - 55, vBaseBone.z), bottom2,
                0) &&
            bottom2.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vBaseBone.x - 53, vBaseBone.y + 55, vBaseBone.z), bottom3,
                0) &&
            bottom3.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vBaseBone.x + 53, vBaseBone.y + 55, vBaseBone.z), bottom4,
                0) &&
            bottom4.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vHeadBone.x + 53, vHeadBone.y - 55, vHeadBone.z + 26), top1,
                0) &&
            top1.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vHeadBone.x - 53, vHeadBone.y - 55, vHeadBone.z + 26), top2,
                0) &&
            top2.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vHeadBone.x - 53, vHeadBone.y + 55, vHeadBone.z + 26), top3,
                0) &&
            top3.is_valid() &&
            my_controller->project_world_location_to_screen(
                fvector(vHeadBone.x + 53, vHeadBone.y + 55, vHeadBone.z + 26), top4,
                0) &&
            top4.is_valid();

        if (!valid_projection)
            return;

        // Calculer les limites de la box
        float left_most =
            fmin(fmin(bottom1.x, bottom2.x), fmin(bottom3.x, bottom4.x)) - 1.0f;
        float right_most = fmax(fmax(top1.x, top2.x), fmax(top3.x, top4.x)) + 1.0f;
        float top_most = fmin(fmin(top1.y, top2.y), fmin(top3.y, top4.y)) - 5.0f;
        float bottom_most =
            fmax(fmax(bottom1.y, bottom2.y), fmax(bottom3.y, bottom4.y)) + 5.0f;

        // Calculer dimensions et positions
        float width = right_most - left_most;
        float height = bottom_most - top_most;

        // Longueur des coins (25% de chaque dimension)
        float corner_length_x = width * 0.25f;
        float corner_length_y = height * 0.25f;

        // Dessiner les 4 coins directement avec k2_drawline

        // Coin TOP-LEFT
        canvas->k2_drawline({ left_most, top_most },
            { left_most + corner_length_x, top_most }, thickness,
            color); // Horizontal
        canvas->k2_drawline({ left_most, top_most },
            { left_most, top_most + corner_length_y }, thickness,
            color); // Vertical

        // Coin TOP-RIGHT
        canvas->k2_drawline({ right_most, top_most },
            { right_most - corner_length_x, top_most }, thickness,
            color); // Horizontal
        canvas->k2_drawline({ right_most, top_most },
            { right_most, top_most + corner_length_y }, thickness,
            color); // Vertical

        // Coin BOTTOM-LEFT
        canvas->k2_drawline({ left_most, bottom_most },
            { left_most + corner_length_x, bottom_most }, thickness,
            color); // Horizontal
        canvas->k2_drawline({ left_most, bottom_most },
            { left_most, bottom_most - corner_length_y }, thickness,
            color); // Vertical

        // Coin BOTTOM-RIGHT
        canvas->k2_drawline({ right_most, bottom_most },
            { right_most - corner_length_x, bottom_most }, thickness,
            color); // Horizontal
        canvas->k2_drawline({ right_most, bottom_most },
            { right_most, bottom_most - corner_length_y }, thickness,
            color); // Vertical
    }

    // Nouvelle fonction pour calculer la distance 3D rÃ©elle sans projection Ã©cran
    inline bool is_target_in_fov_360(fvector player_pos, fvector target_pos,
        double fov_radius) {
        // Calculer la distance 3D directe entre le joueur et la cible
        fvector delta = target_pos - player_pos;
        double distance_3d =
            sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);

        // Le FOV devient une sphÃ¨re autour du joueur plutÃ´t qu'un cÃ´ne de vision
        return distance_3d <= fov_radius;
    }

    // Version alternative utilisant distance horizontale seulement (plus rÃ©aliste)
    inline bool is_target_in_fov_360_horizontal(fvector player_pos,
        fvector target_pos,
        double fov_radius) {
        // Calculer seulement la distance horizontale (ignorer Z pour la hauteur)
        fvector delta = target_pos - player_pos;
        double distance_2d = sqrt(delta.x * delta.x + delta.y * delta.y);

        return distance_2d <= fov_radius;
    }

    // Fonction hybride : FOV normal OU 360Â° selon le mode
    inline bool is_target_in_fov_adaptive(double screen_center_x,
        double screen_center_y,
        fvector2d target_screen_pos,
        fvector player_world_pos,
        fvector target_world_pos,
        double fov_value, bool use_360_fov) {
        if (use_360_fov) {
            // Mode 360Â° : utiliser la distance monde directe
            return is_target_in_fov_360_horizontal(player_world_pos, target_world_pos,
                fov_value);
        }
        else {
            // Mode normal : utiliser la projection Ã©cran classique
            return in_rect(screen_center_x, screen_center_y, fov_value,
                target_screen_pos.x, target_screen_pos.y);
        }
    }

    // =====================================================================
    // S I K K E V E R - ADVANCED DYNAMIC SKELETON (Z-Clipping & Anim Fix)
    // =====================================================================
    void draw_skeleton(aplayercontroller* ctrl, uskeletalmeshcomponent* mesh, ucanvas* canvas, flinearcolor col) {
        if (!ctrl || !mesh || !canvas) return;

        int bone_count = mesh->get_num_bones();

        int b_head = 8, b_neck = 21, b_chest = 6, b_pelvis = 3;
        int b_l_shoulder = 23, b_l_hand = 25, b_r_shoulder = 49, b_r_hand = 51;
        int b_l_thigh = 75, b_l_foot = 78, b_r_thigh = 82, b_r_foot = 85;

        if (bone_count == 103) {
            b_neck = 9; b_l_shoulder = 33; b_l_hand = 32; b_r_shoulder = 58; b_r_hand = 57;
            b_l_thigh = 63; b_l_foot = 69; b_r_thigh = 77; b_r_foot = 83;
        }
        else if (bone_count == 104) {
            b_l_thigh = 77; b_l_foot = 80; b_r_thigh = 84; b_r_foot = 87;
        }
        else if (bone_count < 100 || bone_count > 110) return;

        auto ProjectSafe = [&](int id, fvector2d& out) -> bool {
            fvector pos = mesh->get_bone_location(id);
            if (!pos.is_valid()) return false;

            bool success = ctrl->project_world_location_to_screen(pos, out, false);

            if (success && out.is_valid() && out.x > -1000.0f && out.x < 4000.0f && out.y > -1000.0f && out.y < 4000.0f) {
                if (abs(out.x) < 1.0f && abs(out.y) < 1.0f) return false;
                return true;
            }
            return false;
            };

        auto DrawBone = [&](int id1, int id2) {
            fvector2d p1, p2;
            if (ProjectSafe(id1, p1) && ProjectSafe(id2, p2)) {
                canvas->k2_drawline(p1, p2, 1.5f, col);
            }
            };

        DrawBone(b_head, b_neck);     DrawBone(b_neck, b_chest);
        DrawBone(b_chest, b_pelvis);  DrawBone(b_neck, b_l_shoulder);
        DrawBone(b_l_shoulder, b_l_hand); DrawBone(b_neck, b_r_shoulder);
        DrawBone(b_r_shoulder, b_r_hand); DrawBone(b_pelvis, b_l_thigh);
        DrawBone(b_l_thigh, b_l_foot);    DrawBone(b_pelvis, b_r_thigh);
        DrawBone(b_r_thigh, b_r_foot);
    }

    /*----------------------------------------------------------------------------------------SKELETON END--------------------------------------------------------------------------------------------------------*/


    namespace G {
        currentequippable* MyWeapon = nullptr;
        currentequippable* LastWeapon = nullptr;
    } // namespace G

    template <class k, class e> class tmap {
    public:
        k Key;
        e Element;
        char __pad0x[0x8];
    };
    inline fstring BuddyName;
    inline uobject* buddy;

    static flinearcolor Name_Color{ 1.f, 1.f, 1.f, 1.f };
    float RainbowTime = 0.0f;
    const float RainbowSpeed = 1.0f;
    const float PI = 3.14159265359f;

    flinearcolor convert_to_flinearcolor(int r, int g, int b, int a) {
        return flinearcolor((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f,
            (float)a / 255.0f);
    }

    int index = 453;

    std::wstring to_wide_string(const std::string& str) {
        return std::wstring(str.begin(), str.end());
    }

    static bool bFlickSilent = true;
    static bool bLockedCameraRotation = false;

    fvector2d head_scren;

    double screen_center_x;
    double screen_center_y;

    fvector LocalCameraLocation;
    float LocalCameraFOV;
    fvector LocalCameraRotation;

    static bool first_location = true;
    static bool aim_check = false;
    static bool second_locked_camera = false;
    static bool finished_hook = false;
    static fvector first_camera_location;
    static fvector first_camera_rotation;

    static fvector saved_client_view;
    static bool anti_aim_is_active = false;

    void (*SetCameraCachePOVOriginal)(uintptr_t, FMinimalViewInfo*) = nullptr;

    float pitch = -90.f;
    float yaw = 0.f;

    static bool aimbot_key_pressed_last_frame = false;

    namespace helper {
        fstring convert_weapon_name(fstring weapon_name) {
            std::wstring weapon_name_str = weapon_name.wide();

            if (weapon_name_str.find(L"Ability_Melee_Base_C") != std::wstring::npos)
                return L"Melee";
            else if (weapon_name_str.find(L"BasePistol_C") != std::wstring::npos)
                return L"Classic";
            else if (weapon_name_str.find(L"SawedOffShotgun_C") != std::wstring::npos)
                return L"Shorty";
            else if (weapon_name_str.find(L"AutomaticPistol_C") != std::wstring::npos)
                return L"Frenzy";
            else if (weapon_name_str.find(L"LugerPistol_C") != std::wstring::npos)
                return L"Ghost";
            else if (weapon_name_str.find(L"RevolverPistol_C") != std::wstring::npos)
                return L"Sheriff";
            else if (weapon_name_str.find(L"Vector_C") != std::wstring::npos)
                return L"Stinger";
            else if (weapon_name_str.find(L"SubMachineGun_MP5") != std::wstring::npos)
                return L"Spectre";
            else if (weapon_name_str.find(L"PumpShotgun_C") != std::wstring::npos)
                return L"Bucky";
            else if (weapon_name_str.find(L"AutomaticShotgun_C") != std::wstring::npos)
                return L"Judge";
            else if (weapon_name_str.find(L"AssaultRifle_Burst_C") != std::wstring::npos)
                return L"Bulldog";
            else if (weapon_name_str.find(L"DMR_C") != std::wstring::npos)
                return L"Guardian";
            else if (weapon_name_str.find(L"AssaultRifle_ACR_C") != std::wstring::npos)
                return L"Phantom";
            else if (weapon_name_str.find(L"AssaultRifle_AK_C") != std::wstring::npos)
                return L"Vandal";
            else if (weapon_name_str.find(L"LeverSniperRifle_C") != std::wstring::npos)
                return L"Marshal";
            else if (weapon_name_str.find(L"BoltSniper_C") != std::wstring::npos)
                return L"Operator";
            else if (weapon_name_str.find(L"LightMachineGun_C") != std::wstring::npos)
                return L"Ares";
            else if (weapon_name_str.find(L"HeavyMachineGun_C") != std::wstring::npos)
                return L"Odin";
            else if (weapon_name_str.find(L"Gun_Deadeye_Q_Pistol_C") !=
                std::wstring::npos)
                return L"Headhunter";
            else if (weapon_name_str.find(L"Ability_Wushu_X_Dagger_Production_C") !=
                std::wstring::npos)
                return L"Blade storm";
            else if (weapon_name_str.find(
                L"Gun_Sprinter_X_HeavyLightningGun_Production_C") !=
                std::wstring::npos)
                return L"Overdrive";
            else if (weapon_name_str.find(L"DS_Gun_C") != std::wstring::npos)
                return L"Outlaw";
            else if (weapon_name_str.find(L"Gun_Deadeye_X_Giantslayer_Prototype_C") !=
                std::wstring::npos)
                return L"Tour de force";
            return L"Invalid";
        }
    } // namespace helper

    static fvector calc_spread(ashootercharacter* actor,
        uint64_t firing_state_component,
        currentequippable* weapon, fvector direction) {
        if (!actor || !firing_state_component || !weapon)
            return fvector(0, 0, 0);

        uint64_t stability_component = memory::read<uint64_t>(
            firing_state_component + offsets::stability_component);
        if (!stability_component)
            return fvector(0, 0, 0);

        alignas(16) static uint8_t error_values[4096];
        alignas(16) static uint8_t seed_data_snapshot[4096];
        alignas(16) static uint8_t spread_angles[4096];
        alignas(16) static uint8_t out_spread_angles[4096];

        static auto func1_fn = (float* (__fastcall*)(uint64_t, float*))(
            memory::module_base + offsets::get_spread_values);
        static auto func2_fn = (void(__fastcall*)(uint64_t, fvector*, float, float,
            int, int, uint64_t))(
                memory::module_base + offsets::get_spread_angles);
        static auto func3_fn = (fvector * (__fastcall*)(fvector*, fvector*))(
            memory::module_base + offsets::to_vector_and_normalize);
        static auto func4_fn = (fvector * (__fastcall*)(fvector*, fvector*))(
            memory::module_base + offsets::to_angle_and_normalize);
        static auto func5_fn = (uintptr_t(__fastcall*)(__int64, float*))(
            memory::module_base + offsets::get_spread_values);

        *(uint64_t*)(&out_spread_angles[0]) = (uint64_t)&spread_angles[0];
        *(int*)(&out_spread_angles[0] + 8) = 1;
        *(int*)(&out_spread_angles[0] + 12) = 1;

        uint64_t seed_data =
            memory::read<uint64_t>(firing_state_component + offsets::seed_data);
        if (!seed_data)
            return fvector(0, 0, 0);

        memcpy((void*)seed_data_snapshot, (void*)seed_data,
            sizeof(seed_data_snapshot));

        reinterpret_cast<float* (__cdecl*)(uint64_t, float*, uintptr_t, void*)>(
            spoofcall_stub)(stability_component, (float*)&error_values[0], 0x46C4660,
                func1_fn);

        fvector temp1, temp2 = fvector(0, 0, 0);
        fvector previous_firing_direction, firing_direction = fvector(0, 0, 0);

        actor->get_firing_location_and_direction(&temp1, &previous_firing_direction,
            false);

        reinterpret_cast<fvector* (__cdecl*)(fvector*, fvector*, uintptr_t,
            void*)>(spoofcall_stub)(
                &previous_firing_direction, &temp2, 0x46C4660, func3_fn);
        reinterpret_cast<fvector* (__cdecl*)(fvector*, fvector*, uintptr_t,
            void*)>(spoofcall_stub)(
                &temp2, &temp1, 0x46C4660, func4_fn);

        previous_firing_direction = temp1;

        temp1.x += *(float*)(&error_values[0] + 12);
        temp1.y += *(float*)(&error_values[0] + 16);

        reinterpret_cast<fvector* (__cdecl*)(fvector*, fvector*, uintptr_t,
            void*)>(spoofcall_stub)(
                &temp1, &firing_direction, 0x46C4660, func3_fn);

        float test[20];
        uintptr_t v38 = reinterpret_cast<uintptr_t(__cdecl*)(__int64, float*,
            uintptr_t, void*)>(
                spoofcall_stub)(stability_component, test, 0x46C4660, func5_fn);

        float v46 = memory::read<float>(v38 + 0x14);
        float v48 =
            *(float*)(&error_values[0] + 8) + *(float*)(&error_values[0] + 4);
        int error_retries =
            memory::read<int>(firing_state_component + offsets::error_retries);

        reinterpret_cast<void(__cdecl*)(uint64_t, fvector*, float, float, int, int,
            uint64_t, uintptr_t, void*)>(
                spoofcall_stub)(((uint64_t)&seed_data_snapshot[0]) + 0xD8,
                    &firing_direction, v48, v46, error_retries, 1,
                    (uint64_t)&out_spread_angles[0], 0x46C4660, func2_fn);

        fvector spread_vector = *(fvector*)(&spread_angles[0]);

        reinterpret_cast<fvector* (__cdecl*)(fvector*, fvector*, uintptr_t,
            void*)>(spoofcall_stub)(
                &spread_vector, &firing_direction, 0x46C4660, func4_fn);

        return firing_direction - previous_firing_direction;
    }

    void angle_rotation(const fvector& angles, fvector* forward) {
        float sp, sy, cp, cy;

        sy = sin(DegreeToRadian(angles.y));
        cy = cos(DegreeToRadian(angles.y));

        sp = sin(DegreeToRadian(angles.x));
        cp = cos(DegreeToRadian(angles.x));

        forward->x = cp * cy;
        forward->y = cp * sy;
        forward->z = -sp;
    }

    fvector RotationToVector(const fvector& rotation) {
        const double DEG_TO_RAD = 0.017453292519943295f;

        double sy = sinf(rotation.y * DEG_TO_RAD);
        double cy = cosf(rotation.y * DEG_TO_RAD);
        double sp = sinf(rotation.x * DEG_TO_RAD);
        double cp = cosf(rotation.x * DEG_TO_RAD);

        return fvector(cp * cy, cp * sy, -sp);
    }

    inline float clamp_value(float value, float min_val, float max_val) {
        if (value < min_val)
            return min_val;
        if (value > max_val)
            return max_val;
        return value;
    }

    void apply_outline_chams(acknowledgedpawn* pawn, ashootercharacter* actor,
        aplayercontroller* controllers) {
        if (!pawn || !actor || !controllers)
            return;

        auto is_visible = controllers->line_of_sight(actor);

        float glowIntensity;
        flinearcolor centerEdgeColor, innerEdgeColor, outerEdgeColor;

        if (is_visible) {
            centerEdgeColor = flinearcolor(globals::chams::CenterEdgeR_Visible,
                globals::chams::CenterEdgeG_Visible,
                globals::chams::CenterEdgeB_Visible,
                globals::chams::intensityvisibleoutline);
            innerEdgeColor = flinearcolor(globals::chams::InnerEdgeR_Visible,
                globals::chams::InnerEdgeG_Visible,
                globals::chams::InnerEdgeB_Visible,
                globals::chams::intensityvisibleoutline);
            outerEdgeColor = flinearcolor(globals::chams::OuterEdgeR_Visible,
                globals::chams::OuterEdgeG_Visible,
                globals::chams::OuterEdgeB_Visible,
                globals::chams::intensityvisibleoutline);
            glowIntensity = globals::chams::GlowVisible;
        }
        else {
            centerEdgeColor = flinearcolor(globals::chams::CenterEdgeR_Invisible,
                globals::chams::CenterEdgeG_Invisible,
                globals::chams::CenterEdgeB_Invisible,
                globals::chams::intensityinvisbleoutline);
            innerEdgeColor = flinearcolor(globals::chams::InnerEdgeR_Invisible,
                globals::chams::InnerEdgeG_Invisible,
                globals::chams::InnerEdgeB_Invisible,
                globals::chams::intensityinvisbleoutline);
            outerEdgeColor = flinearcolor(globals::chams::OuterEdgeR_Invisible,
                globals::chams::OuterEdgeG_Invisible,
                globals::chams::OuterEdgeB_Invisible,
                globals::chams::intensityinvisbleoutline);
            glowIntensity = globals::chams::GlowInvisible;
        }

        static fname silohuette_color_name, center_edge_color_name,
            inner_edge_color_name, outer_edge_color_name, glow_intensity_param;
        if (!silohuette_color_name.comparison_index) {
            silohuette_color_name = string::string_to_name(L"SilohuetteColor");
            center_edge_color_name = string::string_to_name(L"CenterEdgeColor");
            inner_edge_color_name = string::string_to_name(L"InnerEdgeColor");
            outer_edge_color_name = string::string_to_name(L"OuterEdgeColor");
            glow_intensity_param = string::string_to_name(L"GlowIntensity");
        }

        static uobject* visible_material = nullptr;
        if (!visible_material)
            visible_material = uobject::static_load_object(
                nullptr, nullptr,
                L"/Game/Characters/BountyHunter/S0/VFX/Materials/"
                L"BountyHunterReveal_MI.BountyHunterReveal_MI");

        static uobject* invisible_material = nullptr;
        if (!invisible_material)
            invisible_material = uobject::static_load_object(
                nullptr, nullptr,
                L"/Game/VFX/Materials/HunterReveal_MI.HunterReveal_MI");

        if (!visible_material || !invisible_material)
            return;

        if (globals::chams::outlinetype == 0 || !is_visible) {
            auto main_mesh = actor->get_mesh();
            if (main_mesh) {
                auto num_materials = main_mesh->get_num_materials();
                for (int i = 0; i < num_materials; i++) {
                    auto material_instance_dynamic =
                        main_mesh->create_and_set_material_instance_dynamic_from_material(
                            i, is_visible ? visible_material : invisible_material);

                    auto dynCast =
                        material_instance_dynamic->cast<UMaterialInstanceDynamic>();
                    if (!dynCast)
                        continue;

                    dynCast->set_vector_parameter_value1(silohuette_color_name,
                        outerEdgeColor);
                    dynCast->set_vector_parameter_value1(center_edge_color_name,
                        centerEdgeColor);
                    dynCast->set_vector_parameter_value1(inner_edge_color_name,
                        innerEdgeColor);
                    dynCast->set_vector_parameter_value1(outer_edge_color_name,
                        outerEdgeColor);
                    dynCast->set_scalar_parameter_value(glow_intensity_param,
                        glowIntensity);
                }
            }

            uskeletalmeshcomponent* mesh_cosmetic_3p = actor->GetCosmeticMesh3P();
            if (mesh_cosmetic_3p) {
                auto num_materials = mesh_cosmetic_3p->get_num_materials();
                for (int i = 0; i < num_materials; i++) {
                    auto material_instance_dynamic =
                        mesh_cosmetic_3p
                        ->create_and_set_material_instance_dynamic_from_material(
                            i, is_visible ? visible_material : invisible_material);

                    auto dynCast =
                        material_instance_dynamic->cast<UMaterialInstanceDynamic>();
                    if (!dynCast)
                        continue;

                    dynCast->set_vector_parameter_value1(silohuette_color_name,
                        outerEdgeColor);
                    dynCast->set_vector_parameter_value1(center_edge_color_name,
                        centerEdgeColor);
                    dynCast->set_vector_parameter_value1(inner_edge_color_name,
                        innerEdgeColor);
                    dynCast->set_vector_parameter_value1(outer_edge_color_name,
                        outerEdgeColor);
                    dynCast->set_scalar_parameter_value(glow_intensity_param,
                        glowIntensity);
                }
            }
        }
        else if (globals::chams::outlinetype == 1 && is_visible) {
            auto main_mesh = actor->get_mesh();
            if (main_mesh) {
                actor->reset_character_materials_internal(main_mesh);
            }

            uskeletalmeshcomponent* mesh_cosmetic_3p = actor->GetCosmeticMesh3P();
            if (mesh_cosmetic_3p) {
                actor->reset_character_materials_internal(mesh_cosmetic_3p);
            }
        }
    }

    void ApplyCrystalChamsPreset(int preset) {
        switch (preset) {
        case 0: // Custom - ne rien faire
            break;
        case 1: // Red Dark
            globals::visuals::Self_CenterEdgeR = 0.613636f;
            globals::visuals::Self_CenterEdgeG = 0.0f;
            globals::visuals::Self_CenterEdgeB = 0.170455f;
            globals::visuals::Self_InnerEdgeR = 1.32955f;
            globals::visuals::Self_InnerEdgeG = 0.0f;
            globals::visuals::Self_InnerEdgeB = 0.89f;
            globals::visuals::Self_OuterEdgeR = 9.64773f;
            globals::visuals::Self_OuterEdgeG = 11.64f;
            globals::visuals::Self_OuterEdgeB = 0.0f;

            globals::visuals::GlowVisible = 1.5f;
            globals::visuals::AlphaBasePower = 2.0f;
            globals::visuals::AlphaColorMult = 1.2f;
            globals::visuals::DepthBias = 0.1f;
            globals::visuals::AlphaDissolveOpacity = 0.8f;
            globals::visuals::BoundingBox = 1.0f;
            globals::visuals::InnerEdgeThickness = 0.3f;
            globals::visuals::OuterEdgeThickness = 0.2f;
            globals::visuals::RimFresnel = 2.5f;
            globals::visuals::RimMultiply = 1.0f;
            globals::visuals::RimPower = 12.2727f;
            globals::visuals::OcclusionDepth = 0.5f;
            globals::visuals::OcclusionBehindWall = 0.3f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.246591f;
            break;

        case 2: // Dark Green
            globals::visuals::Self_CenterEdgeR = 0.0f;
            globals::visuals::Self_CenterEdgeG = 0.545455f;
            globals::visuals::Self_CenterEdgeB = 0.170455f;
            globals::visuals::Self_InnerEdgeR = 1.32955f;
            globals::visuals::Self_InnerEdgeG = 0.0f;
            globals::visuals::Self_InnerEdgeB = 0.89f;
            globals::visuals::Self_OuterEdgeR = 9.64773f;
            globals::visuals::Self_OuterEdgeG = 9.95455f;
            globals::visuals::Self_OuterEdgeB = 0.0f;

            globals::visuals::GlowVisible = 1.5f;
            globals::visuals::AlphaBasePower = 2.0f;
            globals::visuals::AlphaColorMult = 1.2f;
            globals::visuals::DepthBias = 0.1f;
            globals::visuals::AlphaDissolveOpacity = 0.8f;
            globals::visuals::BoundingBox = 1.0f;
            globals::visuals::InnerEdgeThickness = 0.3f;
            globals::visuals::OuterEdgeThickness = 0.2f;
            globals::visuals::RimFresnel = 2.5f;
            globals::visuals::RimMultiply = 1.0f;
            globals::visuals::RimPower = 12.2727f;
            globals::visuals::OcclusionDepth = 0.5f;
            globals::visuals::OcclusionBehindWall = 0.3f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.246591f;
            break;

        case 3: // Dark Blue
            globals::visuals::Self_CenterEdgeR = 0.0f;
            globals::visuals::Self_CenterEdgeG = 0.0f;
            globals::visuals::Self_CenterEdgeB = 0.477273f;
            globals::visuals::Self_InnerEdgeR = 0.0340909f;
            globals::visuals::Self_InnerEdgeG = 0.0f;
            globals::visuals::Self_InnerEdgeB = 0.0f;
            globals::visuals::Self_OuterEdgeR = 0.0f;
            globals::visuals::Self_OuterEdgeG = 0.0f;
            globals::visuals::Self_OuterEdgeB = 0.0f;

            globals::visuals::GlowVisible = 1.5f;
            globals::visuals::AlphaBasePower = 2.0f;
            globals::visuals::AlphaColorMult = 1.2f;
            globals::visuals::DepthBias = 0.1f;
            globals::visuals::AlphaDissolveOpacity = 0.8f;
            globals::visuals::BoundingBox = 1.0f;
            globals::visuals::InnerEdgeThickness = 0.3f;
            globals::visuals::OuterEdgeThickness = 0.2f;
            globals::visuals::RimFresnel = 2.5f;
            globals::visuals::RimMultiply = 1.0f;
            globals::visuals::RimPower = 12.2727f;
            globals::visuals::OcclusionDepth = 0.5f;
            globals::visuals::OcclusionBehindWall = 0.3f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.246591f;
            break;

        case 4: // Dark Orange
            globals::visuals::Self_CenterEdgeR = 0.647727f;
            globals::visuals::Self_CenterEdgeG = 0.579545f;
            globals::visuals::Self_CenterEdgeB = 0.0f;
            globals::visuals::Self_InnerEdgeR = 0.511364f;
            globals::visuals::Self_InnerEdgeG = 0.27f;
            globals::visuals::Self_InnerEdgeB = 1.0f;
            globals::visuals::Self_OuterEdgeR = 0.04f;
            globals::visuals::Self_OuterEdgeG = 0.23f;
            globals::visuals::Self_OuterEdgeB = 0.21f;

            globals::visuals::GlowVisible = 200.0f;
            globals::visuals::AlphaBasePower = 0.806818f;
            globals::visuals::AlphaColorMult = 0.515227f;
            globals::visuals::DepthBias = 0.106818f;
            globals::visuals::AlphaDissolveOpacity = 0.207412f;
            globals::visuals::BoundingBox = -50.0f;
            globals::visuals::InnerEdgeThickness = 0.1f;
            globals::visuals::OuterEdgeThickness = 0.37f;
            globals::visuals::RimFresnel = 1.0f;
            globals::visuals::RimMultiply = 1.0f;
            globals::visuals::RimPower = 20.0f;
            globals::visuals::OcclusionDepth = 0.0f;
            globals::visuals::OcclusionBehindWall = 1.24545f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.0f;
            break;

        case 5: // Orange
            globals::visuals::Self_CenterEdgeR = 0.681818f;
            globals::visuals::Self_CenterEdgeG = 0.579545f;
            globals::visuals::Self_CenterEdgeB = 0.0f;
            globals::visuals::Self_InnerEdgeR = 0.511364f;
            globals::visuals::Self_InnerEdgeG = 0.27f;
            globals::visuals::Self_InnerEdgeB = 1.0f;
            globals::visuals::Self_OuterEdgeR = 0.04f;
            globals::visuals::Self_OuterEdgeG = 0.23f;
            globals::visuals::Self_OuterEdgeB = 0.21f;

            globals::visuals::GlowVisible = 200.0f;
            globals::visuals::AlphaBasePower = 0.806818f;
            globals::visuals::AlphaColorMult = 0.515227f;
            globals::visuals::DepthBias = 0.106818f;
            globals::visuals::AlphaDissolveOpacity = 0.207412f;
            globals::visuals::BoundingBox = -50.0f;
            globals::visuals::InnerEdgeThickness = 0.1f;
            globals::visuals::OuterEdgeThickness = 0.37f;
            globals::visuals::RimFresnel = 1.0f;
            globals::visuals::RimMultiply = 1.0f;
            globals::visuals::RimPower = 20.0f;
            globals::visuals::OcclusionDepth = 0.0f;
            globals::visuals::OcclusionBehindWall = 1.24545f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.0f;
            break;

        case 6: // Pink
            globals::visuals::Self_CenterEdgeR = 0.647727f;
            globals::visuals::Self_CenterEdgeG = 0.545455f;
            globals::visuals::Self_CenterEdgeB = 0.511364f;
            globals::visuals::Self_InnerEdgeR = 0.511364f;
            globals::visuals::Self_InnerEdgeG = 0.27f;
            globals::visuals::Self_InnerEdgeB = 1.0f;
            globals::visuals::Self_OuterEdgeR = 0.04f;
            globals::visuals::Self_OuterEdgeG = 0.23f;
            globals::visuals::Self_OuterEdgeB = 0.21f;

            globals::visuals::GlowVisible = 200.0f;
            globals::visuals::AlphaBasePower = 0.806818f;
            globals::visuals::AlphaColorMult = 0.515227f;
            globals::visuals::DepthBias = 0.106818f;
            globals::visuals::AlphaDissolveOpacity = 0.207412f;
            globals::visuals::BoundingBox = -50.0f;
            globals::visuals::InnerEdgeThickness = 0.1f;
            globals::visuals::OuterEdgeThickness = 0.37f;
            globals::visuals::RimFresnel = 1.0f;
            globals::visuals::RimMultiply = 1.0f;
            globals::visuals::RimPower = 20.0f;
            globals::visuals::OcclusionDepth = 0.0f;
            globals::visuals::OcclusionBehindWall = 1.24545f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.0f;
            break;

        case 7: // Black Galaxy
            globals::visuals::Self_CenterEdgeR = 0.647727f;
            globals::visuals::Self_CenterEdgeG = 0.579545f;
            globals::visuals::Self_CenterEdgeB = 0.545455f;
            globals::visuals::Self_InnerEdgeR = 0.511364f;
            globals::visuals::Self_InnerEdgeG = 0.27f;
            globals::visuals::Self_InnerEdgeB = 1.0f;
            globals::visuals::Self_OuterEdgeR = 0.04f;
            globals::visuals::Self_OuterEdgeG = 0.23f;
            globals::visuals::Self_OuterEdgeB = 0.21f;

            globals::visuals::GlowVisible = 200.0f;
            globals::visuals::AlphaBasePower = 0.806818f;
            globals::visuals::AlphaColorMult = 0.515227f;
            globals::visuals::DepthBias = 0.106818f;
            globals::visuals::AlphaDissolveOpacity = 0.207412f;
            globals::visuals::BoundingBox = -50.0f;
            globals::visuals::InnerEdgeThickness = 0.1f;
            globals::visuals::OuterEdgeThickness = 0.37f;
            globals::visuals::RimFresnel = 1.0f;
            globals::visuals::RimMultiply = 1.0f;
            globals::visuals::RimPower = 20.0f;
            globals::visuals::OcclusionDepth = 0.0f;
            globals::visuals::OcclusionBehindWall = 1.24545f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.0f;
            break;

        case 8: // Purple
            globals::visuals::Self_CenterEdgeR = 0.613636f;
            globals::visuals::Self_CenterEdgeG = 0.511364f;
            globals::visuals::Self_CenterEdgeB = 0.545455f;
            globals::visuals::Self_InnerEdgeR = 0.511364f;
            globals::visuals::Self_InnerEdgeG = 0.27f;
            globals::visuals::Self_InnerEdgeB = 1.0f;
            globals::visuals::Self_OuterEdgeR = 0.04f;
            globals::visuals::Self_OuterEdgeG = 0.23f;
            globals::visuals::Self_OuterEdgeB = 0.21f;

            globals::visuals::GlowVisible = 200.0f;
            globals::visuals::AlphaBasePower = 0.806818f;
            globals::visuals::AlphaColorMult = 0.515227f;
            globals::visuals::DepthBias = 0.106818f;
            globals::visuals::AlphaDissolveOpacity = 0.207412f;
            globals::visuals::BoundingBox = -50.0f;
            globals::visuals::InnerEdgeThickness = 0.1f;
            globals::visuals::OuterEdgeThickness = 0.37f;
            globals::visuals::RimFresnel = 1.0f;
            globals::visuals::RimMultiply = 1.0f;
            globals::visuals::RimPower = 20.0f;
            globals::visuals::OcclusionDepth = 0.0f;
            globals::visuals::OcclusionBehindWall = 1.24545f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.0f;
            break;
        }
    }


#include <string>

#pragma pack(push, 1)
    union fp_flag_store {
        unsigned char raw;
        struct {
            unsigned char f0 : 1;
            unsigned char f1 : 1;
            unsigned char f2 : 6;
        } bits;
    };
#pragma pack(pop)

    struct ViewModelCache {
        uskeletalmeshcomponent* mesh1p = nullptr;
        uskeletalmeshcomponent* overlayMesh = nullptr;
        uskeletalmeshcomponent* weaponMesh1P = nullptr;
        uskeletalmeshcomponent* cosmeticMesh1P = nullptr;
        uskeletalmeshcomponent* meleeMesh1P = nullptr;
        uskeletalmeshcomponent* offHandMesh = nullptr;
        currentequippable* lastWeapon = nullptr;
        currentequippable* lastMelee = nullptr;
        ULONGLONG lastCacheTime = 0;

        void Clear() {
            mesh1p = overlayMesh = weaponMesh1P = cosmeticMesh1P = nullptr;
            meleeMesh1P = offHandMesh = nullptr;
            lastWeapon = lastMelee = nullptr;
        }

        bool IsValid() const { return mesh1p != nullptr && weaponMesh1P != nullptr; }
    };

    inline bool IsValidViewModelPointer(uintptr_t ptr) {
        if (ptr == 0 || ptr == (uintptr_t)-1 || ptr < 0x10000 ||
            ptr > 0x7FFFFFFFFFFF) {
            return false;
        }

        __try {
            volatile unsigned char test = *(unsigned char*)ptr;
            (void)test;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }

    inline bool IsValidViewModelObject(void* obj) {
        if (!obj)
            return false;
        return IsValidViewModelPointer((uintptr_t)obj);
    }

    inline tarray<USceneComponent*>
        GetChildrenComponents(USceneComponent* component, bool bIncludeAllDescendants) {
        tarray<USceneComponent*> result;
        if (!component || !IsValidViewModelObject(component))
            return result;

        static uobject* Function = nullptr;
        if (!Function) {
            auto function_name = (L"Engine.SceneComponent.GetChildrenComponents");
            Function = uobject::find_object<uobject*>(function_name);
        }

        if (!Function || !IsValidViewModelObject(Function))
            return result;

        struct {
            bool bIncludeAllDescendants;
            tarray<USceneComponent*> Children;
        } Args;

        Args.bIncludeAllDescendants = bIncludeAllDescendants;
        Args.Children.data = nullptr;
        Args.Children.count = 0;
        Args.Children.maxCount = 0;

        __try {
            component->process_event(Function, &Args);
            return Args.Children;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return result;
        }
    }

    currentequippable* GetLocalMeleeWeapon() {
        static currentequippable* CachedMelee = nullptr;
        static ULONGLONG lastCacheTime = 0;

        ULONGLONG currentTime = GetTickCount64();
        if (CachedMelee && (currentTime - lastCacheTime) < 2000) {
            return CachedMelee;
        }

        CachedMelee = nullptr;
        if (!UWorldSave)
            return nullptr;

        tarray<AGameObject*> Objects;
        GameplayStatics::GetAllActorsOfClass2(UWorldSave, Class::Actors(), &Objects);

        for (int i = 0; i < Objects.size(); ++i) {
            AGameObject* Object = Objects[i];
            if (!Object)
                continue;

            auto name = system::get_object_name(Object);
            if (!name.is_valid())
                continue;

            std::string name_str = name.ToString();
            if (name_str.find("Ability_Melee_Base_C") != std::string::npos) {
                CachedMelee = (currentequippable*)Object;
                lastCacheTime = currentTime;
                return CachedMelee;
            }
        }

        return nullptr;
    }

    template <typename T> inline bool SafeRead(uintptr_t address, T& value) {
        if (!IsValidViewModelPointer(address))
            return false;

        __try {
            value = *reinterpret_cast<T*>(address);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }

    template <typename T> inline bool SafeWrite(uintptr_t address, const T& value) {
        if (!IsValidViewModelPointer(address))
            return false;

        __try {
            *reinterpret_cast<T*>(address) = value;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }

    inline bool SafeProcessFlag(uskeletalmeshcomponent* mesh, uintptr_t flag_offset,
        bool clear_flag) {
        if (!mesh || !IsValidViewModelObject(mesh))
            return false;

        uintptr_t flag_addr = (uintptr_t)mesh + flag_offset;
        if (!IsValidViewModelPointer(flag_addr))
            return false;

        fp_flag_store state;
        if (!SafeRead(flag_addr, state.raw))
            return false;

        if (clear_flag) {
            state.bits.f0 = 0;
            return SafeWrite(flag_addr, state.raw);
        }

        return true;
    }

    inline void SafeLockDescendants(USceneComponent* component) {
        if (!component || !IsValidViewModelObject(component))
            return;

        tarray<USceneComponent*> allChildren;
        __try {
            allChildren = GetChildrenComponents(component, true);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return;
        }

        for (int i = 0; i < allChildren.Num(); i++) {
            USceneComponent* child = allChildren[i];
            if (child && IsValidViewModelObject(child)) {
                uintptr_t child_flag_addr = (uintptr_t)child + 0x364;
                SafeWrite(child_flag_addr, (unsigned char)0x00);
            }
        }
    }

    inline void process_fp_mode(ashootercharacter* shooter) {
        if (!shooter)
            return;

        uintptr_t shooter_ptr = (uintptr_t)shooter;
        if (shooter_ptr == 0 || shooter_ptr == (uintptr_t)-1 ||
            shooter_ptr < 0x10000 || shooter_ptr > 0x7FFFFFFFFFFF) {
            return;
        }

        __try {
            volatile uintptr_t test = *(uintptr_t*)shooter_ptr;
            (void)test;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return;
        }

        bool isAlive = false;
        __try {
            isAlive = shooter->is_alive();
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return;
        }

        static ViewModelCache cache;

        if (!isAlive) {
            cache.Clear();
            return;
        }

        static bool last_force_key_state = false;
        ULONGLONG current_time = GetTickCount64();
        bool force_key_pressed = GetAsyncKeyState(VK_F8) & 0x8000;
        bool force_reapply = force_key_pressed && !last_force_key_state;
        last_force_key_state = force_key_pressed;

        uinventory* inventory = nullptr;
        __try {
            inventory = shooter->get_inventory();
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            cache.Clear();
            return;
        }

        if (!inventory || !IsValidViewModelObject(inventory)) {
            cache.Clear();
            return;
        }

        currentequippable* weapon = nullptr;
        __try {
            weapon = inventory->get_current_equippable();
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            cache.Clear();
            return;
        }

        if (!weapon || !IsValidViewModelObject(weapon)) {
            cache.Clear();
            return;
        }

        bool needs_refresh = false;
        if (!cache.IsValid() || weapon != cache.lastWeapon ||
            (current_time - cache.lastCacheTime) >= 2000 || force_reapply) {
            needs_refresh = true;
        }

        if (needs_refresh) {
            cache.Clear();
            cache.lastCacheTime = current_time;
            cache.lastWeapon = weapon;

            __try {
                cache.mesh1p = shooter->getmesh1p();
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                cache.Clear();
                return;
            }

            if (!cache.mesh1p || !IsValidViewModelObject(cache.mesh1p)) {
                cache.Clear();
                return;
            }

            __try {
                cache.overlayMesh = shooter->GetOverlayMesh1P();
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
            }

            __try {
                cache.weaponMesh1P = weapon->GetMesh1P();
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                cache.Clear();
                return;
            }

            if (!cache.weaponMesh1P || !IsValidViewModelObject(cache.weaponMesh1P)) {
                cache.Clear();
                return;
            }

            uintptr_t cosmetic_ptr = (uintptr_t)weapon + 0x1188;
            if (IsValidViewModelPointer(cosmetic_ptr)) {
                __try {
                    cache.cosmeticMesh1P =
                        memory::read<uskeletalmeshcomponent*>(cosmetic_ptr);
                }
                __except (EXCEPTION_EXECUTE_HANDLER) {
                }
            }

            auto meleeWeapon = GetLocalMeleeWeapon();
            if (meleeWeapon && IsValidViewModelObject(meleeWeapon)) {
                cache.lastMelee = meleeWeapon;

                __try {
                    cache.meleeMesh1P = meleeWeapon->GetMesh1P();
                }
                __except (EXCEPTION_EXECUTE_HANDLER) {
                    cache.meleeMesh1P = nullptr;
                }

                if (cache.meleeMesh1P) {
                    uintptr_t offhand_ptr = (uintptr_t)meleeWeapon + 0x1220;
                    if (IsValidViewModelPointer(offhand_ptr)) {
                        __try {
                            cache.offHandMesh =
                                memory::read<uskeletalmeshcomponent*>(offhand_ptr);
                        }
                        __except (EXCEPTION_EXECUTE_HANDLER) {
                            cache.offHandMesh = nullptr;
                        }
                    }
                }
            }
        }

        if (!cache.IsValid() || !cache.mesh1p || !cache.weaponMesh1P) {
            return;
        }

        const uintptr_t flag_offset = 0x364;

        bool should_process_flags = false;
        fp_flag_store main_state;

        uintptr_t mesh_flag_addr = (uintptr_t)cache.mesh1p + flag_offset;
        if (SafeRead(mesh_flag_addr, main_state.raw)) {
            should_process_flags = (main_state.bits.f0 != 0) || force_reapply;
        }

        if (should_process_flags) {
            SafeProcessFlag(cache.mesh1p, flag_offset, true);

            if (cache.overlayMesh && IsValidViewModelObject(cache.overlayMesh)) {
                SafeProcessFlag(cache.overlayMesh, flag_offset, true);
            }

            if (cache.weaponMesh1P && IsValidViewModelObject(cache.weaponMesh1P)) {
                SafeProcessFlag(cache.weaponMesh1P, flag_offset, true);
            }

            if (cache.cosmeticMesh1P && IsValidViewModelObject(cache.cosmeticMesh1P)) {
                SafeProcessFlag(cache.cosmeticMesh1P, flag_offset, true);
            }

            if (cache.meleeMesh1P && IsValidViewModelObject(cache.meleeMesh1P)) {
                SafeProcessFlag(cache.meleeMesh1P, flag_offset, true);
            }

            if (cache.offHandMesh && IsValidViewModelObject(cache.offHandMesh)) {
                SafeProcessFlag(cache.offHandMesh, flag_offset, true);
            }
        }

        if (cache.mesh1p && IsValidViewModelObject(cache.mesh1p)) {
            SafeLockDescendants((USceneComponent*)cache.mesh1p);
        }

        if (cache.weaponMesh1P && IsValidViewModelObject(cache.weaponMesh1P)) {
            SafeLockDescendants((USceneComponent*)cache.weaponMesh1P);
        }

        if (cache.meleeMesh1P && IsValidViewModelObject(cache.meleeMesh1P)) {
            SafeLockDescendants((USceneComponent*)cache.meleeMesh1P);
        }
    }

    bool IsValidUObject(uobject* obj) {
        if (!obj)
            return false;
        if (!memory::IsValidPointer((uintptr_t)obj))
            return false;

        void* vtable = *(void**)obj;
        return memory::IsValidPointer((uintptr_t)vtable);
    }

    struct USceneComponentHelpers {
        static void Detach(void* Target) {
            static uobject* fn = nullptr;
            if (!fn)
                fn = uobject::find_object<uobject*>(
                    L"Engine.SceneComponent.K2_DetachFromComponent");

            if (!fn || !Target)
                return;

            struct {
                int LocationRule;
                int RotationRule;
                int ScaleRule;
                bool bCallModify;
            } params;

            params.LocationRule = 0;
            params.RotationRule = 0;
            params.ScaleRule = 0;
            params.bCallModify = true;

            ((uobject*)Target)->process_event(fn, &params);
        }

        static void K2_DetachFromComponent(void* Target, int LocationRule,
            int RotationRule, int ScaleRule,
            bool bCallModify) {
            static uobject* Function = nullptr;
            if (!Function)
                Function = uobject::find_object<uobject*>(
                    L"Engine.SceneComponent.K2_DetachFromComponent");

            if (!Function || !Target)
                return;

            struct {
                int LocationRule;
                int RotationRule;
                int ScaleRule;
                bool bCallModify;
            } params;

            params.LocationRule = LocationRule;
            params.RotationRule = RotationRule;
            params.ScaleRule = ScaleRule;
            params.bCallModify = bCallModify;

            ((uobject*)Target)->process_event(Function, &params);
        }

        static fname GetAttachSocketName(uskeletalmeshcomponent* TargetComponent) {
            static uobject* Function = nullptr;
            if (!Function)
                Function = uobject::find_object<uobject*>(
                    L"Engine.SceneComponent.GetAttachSocketName");

            if (!Function || !TargetComponent)
                return fname();

            struct {
                fname ReturnValue;
            } params;

            TargetComponent->process_event(Function, &params);
            return params.ReturnValue;
        }

        static bool AttachTo(uskeletalmeshcomponent* Target,
            uskeletalmeshcomponent* Parent, fname SocketName,
            int LocationRule, int RotationRule, int ScaleRule,
            bool bWeldSimulatedBodies) {
            static uobject* Function = nullptr;
            if (!Function)
                Function = uobject::find_object<uobject*>(
                    L"Engine.SceneComponent.K2_AttachToComponent");

            if (!Function || !Target)
                return false;

            struct {
                void* Parent;
                fname SocketName;
                int LocationRule;
                int RotationRule;
                int ScaleRule;
                bool bWeldSimulatedBodies;
                bool ReturnValue;
            } params;

            params.Parent = Parent;
            params.SocketName = SocketName;
            params.LocationRule = LocationRule;
            params.RotationRule = RotationRule;
            params.ScaleRule = ScaleRule;
            params.bWeldSimulatedBodies = bWeldSimulatedBodies;

            Target->process_event(Function, &params);
            return params.ReturnValue;
        }

        static void SetRelativeLocation(void* Target, const fvector& Location,
            bool bSweep = false, bool bTeleport = true) {
            static uobject* fn = nullptr;
            if (!fn)
                fn = uobject::find_object<uobject*>(
                    L"Engine.SceneComponent.K2_SetRelativeLocation");

            if (!fn || !Target)
                return;

            struct {
                fvector NewLocation;
                bool bSweep;
                FHitResult SweepHitResult;
                bool bTeleport;
            } params;

            params.NewLocation = Location;
            params.bSweep = bSweep;
            params.bTeleport = bTeleport;
            memset(&params.SweepHitResult, 0, sizeof(FHitResult));

            ((uobject*)Target)->process_event(fn, &params);
        }

        static void SetRelativeRotation(void* Target, const FRotator& Rotation,
            bool bSweep = false, bool bTeleport = true) {
            static uobject* fn = nullptr;
            if (!fn)
                fn = uobject::find_object<uobject*>(
                    L"Engine.SceneComponent.K2_SetRelativeRotation");

            if (!fn || !Target)
                return;

            struct {
                FRotator NewRotation;
                bool bSweep;
                FHitResult SweepHitResult;
                bool bTeleport;
            } params;

            params.NewRotation = Rotation;
            params.bSweep = bSweep;
            params.bTeleport = bTeleport;
            memset(&params.SweepHitResult, 0, sizeof(FHitResult));

            ((uobject*)Target)->process_event(fn, &params);
        }
    };

    struct WeaponTransform {
        fvector position;
        frotator rotation;
        fvector scale;
    };
    enum class EAttachmentRule : uint8 {
        KeepRelative = 0,
        KeepWorld = 1,
        SnapToTarget = 2,
        EAttachmentRule_MAX = 3
    };

    WeaponTransform GetTextTransform(const std::wstring& weaponName,
        int skinIndex) {
        WeaponTransform transform;
        transform.position = fvector(0.0f, 0.0f, 0.0f);
        transform.rotation = frotator(0.0f, 0.0f, 0.0f);
        transform.scale = fvector(1.0f, 1.0f, 1.0f);
        return transform;
    }

    static std::map<uintptr_t, bool> WeaponHasCustomMesh;
    static std::map<uintptr_t, UProceduralMeshComponent*> WeaponTextMeshMap;

    static bool text_meshcreated = false;
    static UProceduralMeshComponent* TextMesh = nullptr;

    static int last_vandal_sel = -1;
    static int last_frenzy_sel = -1;
    static int last_ghost_sel = -1;

    struct MeshData {
        tarray<fvector> Vertices;
        tarray<int32_t> Triangles;
        tarray<fvector> Normals;
        tarray<fvector2d> UV0;
        tarray<FColor> VertexColors;
        tarray<FProcMeshTangent> Tangents;
    };

    static std::map<std::string, MeshData> ModelCache;
    static std::map<std::string, uobject*> TextureCache;
    static bool ModelsLoadedToRAM = false;
    static uobject* LastWorldPtr = nullptr;
    static uintptr_t LastWeaponProcessed = 0;

    // ── Deferred mesh creation queue ─────────────────────────────────────────────
    // CreateMeshSection çağrısını silah değişiminden 3 frame sonraya erteleyerek
    // silah-değiştirme anındaki game-thread kasmasını ortadan kaldırır.
    struct PendingMeshJob {
        currentequippable* weapon = nullptr;
        std::string        objPath;
        std::wstring       texPath;
        int                framesLeft = 3; // 3 frame bekle, sonra işle
    };
    static std::vector<PendingMeshJob> g_pendingMeshJobs;
    // ─────────────────────────────────────────────────────────────────────────────

    inline void SetComponentVisibility(USceneComponent* component,
        bool bNewVisibility,
        bool bPropagateToChildren) {
        if (!component || !memory::IsValidPointer((uintptr_t)component))
            return;
        static uobject* Function =
            uobject::find_object<uobject*>(L"Engine.SceneComponent.SetVisibility");
        if (!Function)
            return;
        struct {
            bool bNewVisibility;
            bool bPropagateToChildren;
        } Args = { bNewVisibility, bPropagateToChildren };
        ((uobject*)component)->process_event(Function, &Args);
    }

    // SetHiddenInGame: bVisible'dan bagimsizdur — Valorant blueprint'i buna dokunmaz.
    // Sadece silah degisince bir kez cagrilir, her frame sifir maliyet.
    // bPropagate=true ile tek cagriyla tum child'lar da gizlenir (dahili C++ loop — process_event basina N degil).
    inline void SetMeshHiddenInGame(USceneComponent* component, bool bHidden, bool bPropagate = false) {
        if (!component || !memory::IsValidPointer((uintptr_t)component))
            return;
        // IsValidUObject kontrolu: garbage ptr process_event'e girmemeli
        if (!IsValidUObject((uobject*)component))
            return;
        static uobject* Function =
            uobject::find_object<uobject*>(L"Engine.SceneComponent.SetHiddenInGame");
        if (!Function)
            return;
        struct {
            bool bNewHidden;
            bool bPropagateToChildren;
        } Args = { bHidden, bPropagate };
        ((uobject*)component)->process_event(Function, &Args);
    }

    inline uskeletalmeshcomponent*
        FindSightComponent(currentequippable* weapon,
            uskeletalmeshcomponent* GunMesh1P) {
        if (!weapon || !memory::IsValidPointer((uintptr_t)weapon))
            return nullptr;
        if (!GunMesh1P || !memory::IsValidPointer((uintptr_t)GunMesh1P))
            return nullptr;
        USceneComponent* sceneComp = reinterpret_cast<USceneComponent*>(GunMesh1P);
        tarray<USceneComponent*> children = GetChildrenComponents(sceneComp, true);
        for (int i = 0; i < children.Num(); i++) {
            if (!children[i])
                continue;
            fstring childName = system::get_object_name((uobject*)children[i]);
            if (childName.to_str().find("SkeletalMeshComponent_") !=
                std::string::npos) {
                uskeletalmeshcomponent* skelMesh =
                    reinterpret_cast<uskeletalmeshcomponent*>(children[i]);
                UPrimitiveComponent* primComp =
                    reinterpret_cast<UPrimitiveComponent*>(skelMesh);
                if (primComp && memory::IsValidPointer((uintptr_t)primComp)) {
                    if (primComp->get_num_materials() > 0)
                        return skelMesh;
                }
            }
        }
        return nullptr;
    }

#include <atomic>
#include <thread>

    static std::string GetPublicPath() { return "C:\\models\\"; }
    // Asset dosyalari yerel cs2_models klasorunden kullanilir.
    // Hicbir ag baglantisi yapilmaz.
    bool CheckLocalAsset(const std::string& fileName) {
        std::string fullPath = GetPublicPath() + fileName;
        return GetFileAttributesA(fullPath.c_str()) != INVALID_FILE_ATTRIBUTES;
    }

    void DownloadMissingAssets() {
        // Eski surumde dis sunucudan dosya indiriliyordu.
        // Guvenlik nedeniyle bu fonksiyon devre disi birakildi.
        // Dosyalar C:\ProgramData\cs2_models\ klasorune elle kopyalanmalidir.
    }

    const MeshData& ParseOBJFile(const char* filepath) {
        static MeshData empty;
        std::string pathKey(filepath);
        if (ModelCache.count(pathKey))
            return ModelCache[pathKey];

        MeshData data;
        std::ifstream file(filepath);
        if (!file.is_open())
            return empty;

        std::vector<fvector> temp_vertices;
        std::vector<fvector2d> temp_uvs;
        std::vector<fvector> temp_normals;

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string type;
            iss >> type;
            if (type == "v") {
                float x, y, z;
                iss >> x >> y >> z;
                temp_vertices.push_back(fvector(x * 100.0f, y * 100.0f, z * 100.0f));
            }
            else if (type == "vt") {
                float u, v;
                iss >> u >> v;
                temp_uvs.push_back(fvector2d(u, 1.0f - v));
            }
            else if (type == "vn") {
                float x, y, z;
                iss >> x >> y >> z;
                temp_normals.push_back(fvector(x, y, z));
            }
            else if (type == "f") {
                std::string v[3];
                if (!(iss >> v[0] >> v[1] >> v[2]))
                    continue;
                for (int i = 0; i < 3; i++) {
                    std::istringstream vss(v[i]);
                    std::string part;
                    int v_idx = 0, vt_idx = -1, vn_idx = -1;
                    if (std::getline(vss, part, '/'))
                        v_idx = std::stoi(part) - 1;
                    if (std::getline(vss, part, '/')) {
                        if (!part.empty())
                            vt_idx = std::stoi(part) - 1;
                    }
                    if (std::getline(vss, part, '/')) {
                        if (!part.empty())
                            vn_idx = std::stoi(part) - 1;
                    }
                    if (v_idx < 0 || v_idx >= (int)temp_vertices.size())
                        continue;
                    int current_index = data.Vertices.Num();
                    data.Vertices.Add(temp_vertices[v_idx]);
                    data.UV0.Add((vt_idx >= 0 && vt_idx < (int)temp_uvs.size())
                        ? temp_uvs[vt_idx]
                        : fvector2d(0, 0));
                    data.Normals.Add((vn_idx >= 0 && vn_idx < (int)temp_normals.size())
                        ? temp_normals[vn_idx]
                        : fvector(0, 0, 1));
                    data.VertexColors.Add(FColor(255, 255, 255, 255));
                    data.Triangles.Add(current_index);
                }
            }
        }
        file.close();

        std::string p = pathKey;
        for (auto& c : p)
            c = tolower(c);
        if (p.find("sheriff") == std::string::npos) {
            for (int i = 0; i + 2 < data.Triangles.Num(); i += 3) {
                int32_t temp = data.Triangles[i + 1];
                data.Triangles[i + 1] = data.Triangles[i + 2];
                data.Triangles[i + 2] = temp;
            }
        }
        if (data.Vertices.Num() > 0)
            ModelCache[pathKey] = std::move(data);
        if (ModelCache.count(pathKey))
            return ModelCache[pathKey];
        return empty;
    }

    static std::atomic<bool> g_CacheThreadRunning = false;

    void HardCacheModelsFromDisk() {
        if (ModelsLoadedToRAM || !UWorldSave)
            return;
        if (g_CacheThreadRunning)
            return;

        g_CacheThreadRunning = true;
        ModelsLoadedToRAM = true;

        std::thread([]() {
            DownloadMissingAssets();

            std::string baseDir = GetPublicPath();

            const char* weaponBases[] = { "vandal", "phantom" };
            const char* otherWeapons[] = { "bulldog", "guardian", "sheriff", "ghost",
                                          "bucky",   "judge",    "frenzy",  "bicak",
                                          "spectre", "stinger",  "marshal", "operator",
                                          "ares",    "odin",     "classic", "shorty" };

            for (auto base : weaponBases) {
                ParseOBJFile((baseDir + base + ".obj").c_str());
                for (int i = 1; i <= 6; i++) {
                    std::string skinPath =
                        baseDir + base + "_skin" + std::to_string(i) + ".obj";
                    if (GetFileAttributesA(skinPath.c_str()) != INVALID_FILE_ATTRIBUTES)
                        ParseOBJFile(skinPath.c_str());
                }
            }

            for (auto name : otherWeapons) {
                std::string objPath = baseDir + name + ".obj";
                if (GetFileAttributesA(objPath.c_str()) != INVALID_FILE_ATTRIBUTES)
                    ParseOBJFile(objPath.c_str());
            }

            std::string textPath = baseDir + "text.obj";
            if (GetFileAttributesA(textPath.c_str()) != INVALID_FILE_ATTRIBUTES)
                ParseOBJFile(textPath.c_str());

            g_CacheThreadRunning = false;
            }).detach();
    }

    void PreCacheAllVisuals() {
        if (UWorldSave != LastWorldPtr) {
            TextureCache.clear();
            LastWorldPtr = UWorldSave;
            ModelsLoadedToRAM = false;
            LastWeaponProcessed = 0;
            g_CacheThreadRunning = false;
        }
        HardCacheModelsFromDisk();
    }

    void ReplaceTextMeshWith3DModel(currentequippable* Weapon,
        const char* objFilePath) {
        if (!Weapon || !memory::IsValidPointer((uintptr_t)Weapon))
            return;
        if (!UWorldSave || !memory::IsValidPointer((uintptr_t)UWorldSave))
            return;

        auto* OriginalMesh = Weapon->GetMesh1P();
        if (!OriginalMesh || !memory::IsValidPointer((uintptr_t)OriginalMesh))
            return;

        static uobject* ProcMeshClass = (uobject*)uobject::find_object<uclass*>(
            L"ProceduralMeshComponent.ProceduralMeshComponent");
        static uobject* AddComponentFunc = (uobject*)uobject::find_object<uclass*>(
            L"ShooterGame.ShooterBlueprintLibrary.AddComponentByClass");
        static uobject* CreateMeshFunc = (uobject*)uobject::find_object<uclass*>(
            L"ProceduralMeshComponent.ProceduralMeshComponent.CreateMeshSection");

        if (!ProcMeshClass || !AddComponentFunc || !CreateMeshFunc)
            return;

        if (!variables.blueprints || !memory::IsValidPointer((uintptr_t)variables.blueprints) ||
            !IsValidUObject((uobject*)variables.blueprints))
            return;

        struct {
            AActor* Actor;
            UActorComponent* ComponentClass;
            UActorComponent* ReturnValue;
        } AddParams{ (AActor*)Weapon, (UActorComponent*)ProcMeshClass, nullptr };
        variables.blueprints->process_event(AddComponentFunc, &AddParams);

        auto* ProcMesh = (uskeletalmeshcomponent*)AddParams.ReturnValue;
        if (!ProcMesh || !memory::IsValidPointer((uintptr_t)ProcMesh))
            return;

        const MeshData& mesh = ParseOBJFile(objFilePath);
        if (mesh.Vertices.Num() == 0)
            return;

        struct {
            int32_t SectionIndex;
            tarray<fvector> Vertices;
            tarray<int32_t> Triangles;
            tarray<fvector> Normals;
            tarray<fvector2d> UV0;
            tarray<FColor> VertexColors;
            tarray<FProcMeshTangent> Tangents;
            bool bCreateCollision;
        } CreateParams = { 0,        mesh.Vertices,     mesh.Triangles, mesh.Normals,
                          mesh.UV0, mesh.VertexColors, mesh.Tangents,  false };

        ((uobject*)ProcMesh)->process_event(CreateMeshFunc, &CreateParams);

        uobject* GlowMaterial = uobject::static_load_object(
            nullptr, nullptr,
            L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/"
            L"Arcade_Emissive_Blue_MI.Arcade_Emissive_Blue_MI");

        if (GlowMaterial && memory::IsValidPointer((uintptr_t)GlowMaterial)) {
            uobject* DynMat =
                ProcMesh->create_and_set_material_instance_dynamic_from_material(
                    0, GlowMaterial);
            if (DynMat && memory::IsValidPointer((uintptr_t)DynMat)) {
                auto* matInstance = (UMaterialInstanceDynamic*)DynMat;
                flinearcolor white = flinearcolor(1.0f, 1.0f, 1.0f, 1.0f);
                matInstance->set_vector_parameter_value(
                    string::string_to_name(L"Base Color"), white);
                matInstance->set_vector_parameter_value(
                    string::string_to_name(L"Emissive Color"), white);
                matInstance->set_scalar_parameter_value(
                    string::string_to_name(L"EmissiveIntensity"), 5.0f);
            }
        }

        USceneComponentHelpers::AttachTo(
            ProcMesh, (uskeletalmeshcomponent*)OriginalMesh,
            string::string_to_name(L"R_WeaponPoint"), 1, 1, 1, false);
        SetComponentVisibility((USceneComponent*)ProcMesh, true, true);

        ProcMesh->SetRelativeScale3D(fvector(0.909f, 1.484f, 1.371f));
        USceneComponentHelpers::SetRelativeRotation(
            ProcMesh,
            FRotator{ 0.0f, 90.3396f, -88.9811f });
        USceneComponentHelpers::SetRelativeLocation(
            ProcMesh, fvector(2.0f, 0.0f, -3.33333f));

        TextMesh = (UProceduralMeshComponent*)ProcMesh;
        text_meshcreated = true;
        WeaponTextMeshMap[(uintptr_t)Weapon] = TextMesh;
    }

    // Forward declaration (asil tanim asagida)
    void ReplaceWeaponMeshWith3DModel(currentequippable* Weapon,
        const char* objFilePath,
        const wchar_t* texFilePath);

    // SEH wrapper'lar — __try/__except ancak noinline fonksiyonlarda kullanilabilir
    // VE icinde destructor'li C++ nesnesi (fstring, std::string vs.) olmamali (C2712)
    static __declspec(noinline) void SafeReplaceMesh(
        currentequippable* weapon, const char* obj, const wchar_t* tex)
    {
        __try { ReplaceWeaponMeshWith3DModel(weapon, obj, tex); }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }

    // UObject adi icinde substr arar — destructor'suz yardimci
    static bool ObjNameContains(uobject* obj, const char* substr) {
        if (!obj || !memory::IsValidPointer((uintptr_t)obj)) return false;
        if (!IsValidUObject(obj)) return false;
        fstring name = system::get_object_name(obj);
        return name.to_str().find(substr) != std::string::npos;
    }

    static __declspec(noinline) uskeletalmeshcomponent* SafeFindProcMesh(
        currentequippable* weapon)
    {
        // C2712: __try icinde destructor'li nesne olamaz —
        // bu wrapper icinde C++ nesnesi YOK, sadece ham pointer islemi var.
        uskeletalmeshcomponent* pm = nullptr;
        __try {
            USceneComponent* sc = reinterpret_cast<USceneComponent*>(weapon->GetMesh1P());
            if (!sc || !memory::IsValidPointer((uintptr_t)sc)) __leave;
            tarray<USceneComponent*> ch = GetChildrenComponents(sc, true);
            // ch bir tarray (POD wrapper) — destructor cagirmaz, guvenli
            int cnt = ch.Num();
            for (int ci = 0; ci < cnt; ci++) {
                USceneComponent* child = ch[ci];
                if (!child || !memory::IsValidPointer((uintptr_t)child)) continue;
                // ObjNameContains fstring/string'i kendi scope'unda kullanir, __try disinda
                if (ObjNameContains((uobject*)child, "ProceduralMesh")) {
                    pm = (uskeletalmeshcomponent*)child; break;
                }
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
        return pm;
    }

    void ReplaceWeaponMeshWith3DModel(currentequippable* Weapon,
        const char* objFilePath,
        const wchar_t* texFilePath) {
        if (!Weapon || !memory::IsValidPointer((uintptr_t)Weapon))
            return;
        if (!UWorldSave || !memory::IsValidPointer((uintptr_t)UWorldSave))
            return;

        auto* OriginalMesh = Weapon->GetMesh1P();
        if (!OriginalMesh || !memory::IsValidPointer((uintptr_t)OriginalMesh))
            return;

        {
            USceneComponent* sceneComp =
                reinterpret_cast<USceneComponent*>(OriginalMesh);
            tarray<USceneComponent*> children = GetChildrenComponents(sceneComp, true);
            static uobject* DestroyComponentFunc =
                uobject::find_object<uobject*>(L"Engine.Actor.DestroyComponent");
            for (int i = 0; i < children.Num(); i++) {
                if (!children[i] || !memory::IsValidPointer((uintptr_t)children[i]))
                    continue;
                // IsValidUObject kontrolü — freed component üzerinde get_object_name crash yapar
                if (!IsValidUObject((uobject*)children[i]))
                    continue;
                fstring childName = system::get_object_name((uobject*)children[i]);
                if (childName.to_str().find("ProceduralMesh") != std::string::npos) {
                    if (DestroyComponentFunc) {
                        struct {
                            UActorComponent* Component;
                        } Args = { (UActorComponent*)children[i] };
                        ((uobject*)Weapon)->process_event(DestroyComponentFunc, &Args);
                    }
                    break;
                }
            }
        }

        std::wstring wTexPath(texFilePath);
        std::string texKey(wTexPath.begin(), wTexPath.end());
        uobject* WeaponTexture = nullptr;

        if (TextureCache.size() > 50)
            TextureCache.clear();

        if (TextureCache.count(texKey) && IsValidUObject(TextureCache[texKey])) {
            WeaponTexture = TextureCache[texKey];
        }
        else {
            WeaponTexture =
                system::import_file_as_texture2d(UWorldSave, fstring(texFilePath));
            if (WeaponTexture)
                TextureCache[texKey] = WeaponTexture;
        }

        static uobject* ProcMeshClass = (uobject*)uobject::find_object<uclass*>(
            L"ProceduralMeshComponent.ProceduralMeshComponent");
        static uobject* AddComponentFunc = (uobject*)uobject::find_object<uclass*>(
            L"ShooterGame.ShooterBlueprintLibrary.AddComponentByClass");
        static uobject* CreateMeshFunc = (uobject*)uobject::find_object<uclass*>(
            L"ProceduralMeshComponent.ProceduralMeshComponent.CreateMeshSection");

        if (!ProcMeshClass || !AddComponentFunc || !CreateMeshFunc)
            return;

        struct {
            AActor* Actor;
            UActorComponent* ComponentClass;
            UActorComponent* ReturnValue;
        } AddParams{ (AActor*)Weapon, (UActorComponent*)ProcMeshClass, nullptr };

        if (!variables.blueprints || !memory::IsValidPointer((uintptr_t)variables.blueprints) ||
            !IsValidUObject((uobject*)variables.blueprints))
            return;

        variables.blueprints->process_event(AddComponentFunc, &AddParams);

        auto* ProcMesh = (uskeletalmeshcomponent*)AddParams.ReturnValue;
        if (!ProcMesh || !memory::IsValidPointer((uintptr_t)ProcMesh))
            return;

        const MeshData& mesh = ParseOBJFile(objFilePath);
        if (mesh.Vertices.Num() == 0)
            return;

        struct {
            int32_t SectionIndex;
            tarray<fvector> Vertices;
            tarray<int32_t> Triangles;
            tarray<fvector> Normals;
            tarray<fvector2d> UV0;
            tarray<FColor> VertexColors;
            tarray<FProcMeshTangent> Tangents;
            bool bCreateCollision;
        } CreateParams = { 0,        mesh.Vertices,     mesh.Triangles, mesh.Normals,
                          mesh.UV0, mesh.VertexColors, mesh.Tangents,  false };

        ((uobject*)ProcMesh)->process_event(CreateMeshFunc, &CreateParams);

        if (WeaponTexture) {
            uobject* MasterMat = OriginalMesh->GetMaterial(0);
            if (MasterMat) {
                uobject* DynMat =
                    ProcMesh->create_and_set_material_instance_dynamic_from_material(
                        0, MasterMat);
                if (DynMat) {
                    auto* matInstance = (UMaterialInstanceDynamic*)DynMat;
                    const wchar_t* pNames[] = { L"BaseColor", L"Diffuse", L"Albedo",
                                               L"Texture" };
                    for (auto p : pNames)
                        matInstance->set_texture_parameter_value(string::string_to_name(p),
                            WeaponTexture);
                    matInstance->set_scalar_parameter_value2(
                        string::string_to_name(L"TwoSided"), 1.0f);
                }
            }
        }

        USceneComponentHelpers::AttachTo(
            ProcMesh, (uskeletalmeshcomponent*)OriginalMesh,
            string::string_to_name(L"R_WeaponPoint"), 1, 1, 1, false);
        SetComponentVisibility((USceneComponent*)OriginalMesh, false, true);
        SetComponentVisibility((USceneComponent*)ProcMesh, true, true);

        // 3P (üçüncü şahıs) orijinal mesh'i de gizle
        auto* OriginalMesh3P = Weapon->GetMesh3P();
        if (OriginalMesh3P && memory::IsValidPointer((uintptr_t)OriginalMesh3P))
            SetComponentVisibility((USceneComponent*)OriginalMesh3P, false, true);

        // Cosmetic mesh (silah skini offset 0x1188) gizle
        auto* CosmeticMesh1P =
            memory::read<uskeletalmeshcomponent*>((uintptr_t)Weapon + 0x1188);
        if (CosmeticMesh1P && memory::IsValidPointer((uintptr_t)CosmeticMesh1P))
            SetComponentVisibility((USceneComponent*)CosmeticMesh1P, false, true);

        // 1P overlay mesh gizle (offset mesh1p_overlay = 0xf38) - orijinal silah
        // tamamen kaybolsun
        auto* OverlayMesh1P = memory::read<uskeletalmeshcomponent*>(
            (uintptr_t)Weapon + offsets::mesh1p_overlay);
        if (OverlayMesh1P && memory::IsValidPointer((uintptr_t)OverlayMesh1P))
            SetComponentVisibility((USceneComponent*)OverlayMesh1P, false, true);

        fstring converted_name =
            helper::convert_weapon_name(system::get_object_name((uobject*)Weapon));
        std::wstring wNameMesh = converted_name.wide();

        if (wNameMesh == L"Melee") {
            ProcMesh->SetRelativeScale3D(fvector(1.35f, 1.35f, 1.35f));
            USceneComponentHelpers::SetRelativeRotation(
                ProcMesh, FRotator{ -46.6f, -103.2f, 93.1f });
            USceneComponentHelpers::SetRelativeLocation(
                ProcMesh, fvector(-19.93f, -1.05f, -0.70f));
        }
        else if (wNameMesh == L"Spectre") {
            ProcMesh->SetRelativeScale3D(fvector(1.5f, 1.5f, 1.5f));
            USceneComponentHelpers::SetRelativeRotation(
                ProcMesh, FRotator{ 0.0f, 90.0f, -90.0f });
            USceneComponentHelpers::SetRelativeLocation(
                ProcMesh, fvector(-0.9434f, 0.943392f, -2.83019f));

        }
        else if (wNameMesh == L"Classic") {
            ProcMesh->SetRelativeScale3D(fvector(0.0343f, 0.0343f, 0.0267f));
            USceneComponentHelpers::SetRelativeRotation(
                ProcMesh, FRotator{ 4.8f, 96.0f, -96.0f });
            USceneComponentHelpers::SetRelativeLocation(
                ProcMesh, fvector(-9.667f, 0.000f, -4.333f));

        }
        else {
            ProcMesh->SetRelativeScale3D(fvector(0.0677f, 0.0314f, 0.0267f));
            USceneComponentHelpers::SetRelativeRotation(
                ProcMesh, FRotator{ 2.4f, 41.4f, -92.6f });
            USceneComponentHelpers::SetRelativeLocation(
                ProcMesh, fvector(11.667f, 45.000f, 23.000f));
        }

        LastWeaponProcessed = (uintptr_t)Weapon;
    }

    static float normalize_angle(float angle) {
        while (angle > 180.0f)
            angle -= 360.0f;
        while (angle < -180.0f)
            angle += 360.0f;
        return angle;
    }

    auto SetCameraCachePOVHook(uintptr_t PlayerCameraManager,
        FMinimalViewInfo* ViewInfo) {
        bool aimbot_key_current = GetAsyncKeyState(globals::aimbot::a1m_k3y) != 0;

        // === SILENT AIM ===
        if (globals::aimbot::silent && !globals::misc::tperson && !aim_check) {
            if (GetAsyncKeyState(globals::aimbot::a1m_k3y)) {
                if (first_location) {
                    aim_check = true;
                    first_camera_location = controllers->get_control_rotation();
                    first_camera_rotation = ViewInfo->Rotation;
                    aim_check = false;
                    first_location = false;
                }
                second_locked_camera = true;
                finished_hook = false;
            }
            else if (!first_location) {
                aim_check = true;
                controllers->set_control_rotation(first_camera_location);
                if (controllers->get_control_rotation() == first_camera_location &&
                    ViewInfo->Rotation == first_camera_rotation) {
                    finished_hook = true;
                    second_locked_camera = false;
                }
                first_location = true;
            }
        }
        else {
            second_locked_camera = false;
            first_camera_location = fvector();
            aim_check = false;
            finished_hook = false;
            first_location = true;
        }

        if (globals::aimbot::silent && second_locked_camera && ViewInfo != nullptr &&
            first_camera_rotation != fvector()) {
            ViewInfo->Rotation = first_camera_rotation;
        }

        static float spinAngle = 0.0f;
        static bool jitterFlip = false;
        static int threewayStep = 0;
        static bool aaEnabled = false;

        if (!globals::misc::SpinBot) {
            aaEnabled = false;

            if (ViewInfo) {
                LocalCameraRotation = ViewInfo->Rotation;
            }

            if (globals::misc::tperson) {
                float radPitch = ViewInfo->Rotation.x * (M_PI / 180.0f);
                float radYaw = ViewInfo->Rotation.y * (M_PI / 180.0f);

                fvector forward;
                forward.x = cosf(radPitch) * cosf(radYaw);
                forward.y = cosf(radPitch) * sinf(radYaw);
                forward.z = sinf(radPitch);

                ViewInfo->Location.x -= forward.x * globals::misc::PlayerDistance;
                ViewInfo->Location.y -= forward.y * globals::misc::PlayerDistance;
                ViewInfo->Location.z -= forward.z * globals::misc::PlayerDistance;
            }

            if (globals::misc::aspectratio && ViewInfo) {
                ViewInfo->bConstrainAspectRatio = true;
                ViewInfo->AspectRatio = globals::misc::aspectfloat;
            }

            aimbot_key_pressed_last_frame = aimbot_key_current;
            SetCameraCachePOVOriginal(PlayerCameraManager, ViewInfo);
            return;
        }

        float deltaX = 0.f, deltaY = 0.f;
        controllers->GetInputMouseDelta(deltaX, deltaY);
        float sensitivity = controllers->GetMouseSensitivity();

        LocalCameraRotation.x += deltaY * sensitivity;
        LocalCameraRotation.y += deltaX * sensitivity;

        ViewInfo->Rotation = LocalCameraRotation;
        character->K2_SetActorRelativeRotation(fvector{ 0, LocalCameraRotation.y, 0 },
            false, false);

        static bool lastTState = false;
        bool currentTState = (GetAsyncKeyState(0x54) & 1);

        if (currentTState && !lastTState) {
            aaEnabled = !aaEnabled;
            if (!aaEnabled) {
                spinAngle = LocalCameraRotation.y;
                threewayStep = 0;
                jitterFlip = false;
            }
        }
        lastTState = currentTState;

        if (GetAsyncKeyState('J') & 0x8000) {
            globals::misc::yaw_add = -90.0f;
        }
        else if (GetAsyncKeyState('L') & 0x8000) {
            globals::misc::yaw_add = 90.0f;
        }

        if (aaEnabled) {
            float fakeYaw = LocalCameraRotation.y;
            float fakePitch = LocalCameraRotation.x;

            switch (globals::misc::pitch_mode) {
            case 0:
                break;
            case 1:
                fakePitch = 89.0f;
                break;
            case 2:
                fakePitch = -89.0f;
                break;
            case 3:
                fakePitch = globals::misc::pitch_value;
                break;
            }

            fakeYaw += globals::misc::yaw_add;

            bool backKeyPressed = false;
            float direction = 0.0f;

            if (GetAsyncKeyState(globals::misc::snap_left_key) & 0x8000) {
                backKeyPressed = true;
                direction = -90.f;
            }
            else if (GetAsyncKeyState(globals::misc::snap_right_key) & 0x8000) {
                backKeyPressed = true;
                direction = 90.f;
            }
            else if (GetAsyncKeyState(globals::misc::snap_back_key) & 0x8000) {
                backKeyPressed = true;
                direction = 180.f;
            }

            if (backKeyPressed) {
                if (globals::misc::jitter_enabled && globals::misc::jitter_on_back) {
                    jitterFlip = !jitterFlip;
                    fakeYaw += direction + (jitterFlip ? globals::misc::jitter_range
                        : -globals::misc::jitter_range);
                }
                else {
                    fakeYaw += direction;
                }
            }
            else {

                if (globals::misc::aa_backwards) {
                    fakeYaw += 180.f;
                }

                if (globals::misc::aa_spin) {
                    spinAngle = fmodf(spinAngle + globals::misc::spinvalue, 360.f);
                    fakeYaw += spinAngle;
                }

                if (globals::misc::aa_jitter) {
                    jitterFlip = !jitterFlip;

                    float jitter_amount = 15.0f + (rand() % 16); // 15-30 arası rastgele
                    fakeYaw += jitterFlip ? jitter_amount : -jitter_amount;

                    static bool pitch_flip = false;
                    pitch_flip = !pitch_flip;
                    fakePitch += pitch_flip ? 3.0f : -3.0f;
                }

                if (globals::misc::aa_threeway) {
                    threewayStep = (threewayStep + 1) % 3;
                    fakeYaw += (threewayStep == 0) ? 90.f
                        : (threewayStep == 1) ? -90.f
                        : 180.f;
                }

                if (globals::misc::aa_desync) {
                    static float desync_timer = 0.0f;
                    desync_timer += 0.02f;

                    float wave_desync = sinf(desync_timer) * globals::misc::desync_range;

                    if (globals::misc::jitter_enabled) {
                        static int desync_jitter_counter = 0;
                        desync_jitter_counter++;
                        if (desync_jitter_counter % 8 == 0) {
                            wave_desync += (rand() % 60 - 30);
                        }
                    }
                    fakeYaw += wave_desync;
                }

                if (globals::misc::aa_atomic) {
                    static float atomic_timer = 0.0f;
                    atomic_timer += 0.01f * globals::misc::atomic_speed;

                    switch (globals::misc::atomic_mode) {
                    case 0:
                        fakeYaw += sinf(atomic_timer * 5.0f) * 120.0f +
                            cosf(atomic_timer * 3.0f) * 60.0f;
                        break;
                    case 1:
                        fakeYaw += (sinf(atomic_timer * 8.0f) > 0 ? 180.0f : -180.0f);
                        break;
                    case 2: {
                        static bool flicker_state = false;
                        static int flicker_counter = 0;
                        flicker_counter++;
                        if (flicker_counter % 5 == 0) {
                            flicker_state = !flicker_state;
                            fakeYaw += flicker_state ? 135.0f : -135.0f;
                        }
                        break;
                    }
                    }

                    if (globals::misc::jitter_enabled) {
                        fakeYaw += jitterFlip ? globals::misc::jitter_range * 0.5f
                            : -globals::misc::jitter_range * 0.5f;
                        jitterFlip = !jitterFlip;
                    }
                }

                if (globals::misc::aa_prediction_breaker) {
                    static float breaker_timer = 0.0f;
                    static float flick_timer = 0.0f;

                    breaker_timer += 0.01f * globals::misc::breaker_intensity;

                    float breaker_yaw = sinf(breaker_timer * 3.0f) * 90.0f +
                        cosf(breaker_timer * 7.0f) * 45.0f +
                        sinf(breaker_timer * 13.0f) * 30.0f;

                    fakeYaw += breaker_yaw;

                    flick_timer += 0.01f;
                    if (flick_timer > 2.0f) {
                        flick_timer = 0.0f;
                        fakeYaw += 180.0f;
                    }
                }
            }

            controllers->set_control_rotation(fvector(fakePitch, fakeYaw, 0));

            if (auto mesh3p = character->get_mesh()) {
                mesh3p->set_world_rotation(fvector(0, fakeYaw, 0), 0, 0);
            }
        }
        else {
            controllers->set_control_rotation(
                fvector(LocalCameraRotation.x, LocalCameraRotation.y, 0));

            if (auto mesh3p = character->get_mesh()) {
                mesh3p->set_world_rotation(fvector(0, LocalCameraRotation.y, 0), 0, 0);
            }
        }

        if (globals::misc::tperson) {
            float radPitch = ViewInfo->Rotation.x * (M_PI / 180.0f);
            float radYaw = ViewInfo->Rotation.y * (M_PI / 180.0f);

            fvector forward;
            forward.x = cosf(radPitch) * cosf(radYaw);
            forward.y = cosf(radPitch) * sinf(radYaw);
            forward.z = sinf(radPitch);

            ViewInfo->Location.x -= forward.x * globals::misc::PlayerDistance;
            ViewInfo->Location.y -= forward.y * globals::misc::PlayerDistance;
            ViewInfo->Location.z -= forward.z * globals::misc::PlayerDistance;
        }

        if (globals::misc::aspectratio && ViewInfo) {
            ViewInfo->bConstrainAspectRatio = true;
            ViewInfo->AspectRatio = globals::misc::aspectfloat;
        }

        aimbot_key_pressed_last_frame = aimbot_key_current;
        SetCameraCachePOVOriginal(PlayerCameraManager, ViewInfo);
    }

    static flinearcolor accent_color = { 0.6f, 0.6f, 0.6f,
                                        1.0f }; // OUR COLOR (VIBRANT GREY)
    const flinearcolor background_color = { 0.01f, 0.01f, 0.01f, 1.0f };
    const flinearcolor border_color = { 0.10f, 0.10f, 0.10f, 1.0f };
    const flinearcolor panel_color = { 0.015f, 0.015f, 0.015f, 1.0f };
    const flinearcolor text_color = { 0.9f, 0.9f, 0.9f, 1.0f };
    const flinearcolor hover_color = { 0.2f, 0.2f, 0.2f, 1.0f };
    const flinearcolor disabled_color = { 0.5f, 0.5f, 0.5f, 1.0f };
    const flinearcolor dark_grey_color = { 0.15f, 0.15f, 0.15f,
                                          1.0f }; // Dark grey for unfilled part
    const flinearcolor shadow_color = { 0.1f, 0.1f, 0.1f,
                                       0.6f }; // Subtle shadow effect
    const flinearcolor dark_border_color = { 0.15f, 0.15f, 0.15f, 1.0f };

    void DrawSmoothFilledCircle(fvector2d center, float radius, flinearcolor color,
        ucanvas* canvas) {
        constexpr float PI = 3.14159265359f;

        fvector2d p0 = { center.x + radius * cosf(0.0f),
                        center.y + radius * sinf(0.0f) };
        fvector2d p1 = { center.x + radius * cosf(PI / 3.0f),
                        center.y + radius * sinf(PI / 3.0f) };
        fvector2d p2 = { center.x + radius * cosf(2.0f * PI / 3.0f),
                        center.y + radius * sinf(2.0f * PI / 3.0f) };
        fvector2d p3 = { center.x + radius * cosf(PI), center.y + radius * sinf(PI) };
        fvector2d p4 = { center.x + radius * cosf(4.0f * PI / 3.0f),
                        center.y + radius * sinf(4.0f * PI / 3.0f) };
        fvector2d p5 = { center.x + radius * cosf(5.0f * PI / 3.0f),
                        center.y + radius * sinf(5.0f * PI / 3.0f) };

        canvas->k2_drawline(center, p0, 1.0f, color);
        canvas->k2_drawline(center, p1, 1.0f, color);
        canvas->k2_drawline(p0, p1, 1.0f, color);

        canvas->k2_drawline(center, p1, 1.0f, color);
        canvas->k2_drawline(center, p2, 1.0f, color);
        canvas->k2_drawline(p1, p2, 1.0f, color);

        canvas->k2_drawline(center, p2, 1.0f, color);
        canvas->k2_drawline(center, p3, 1.0f, color);
        canvas->k2_drawline(p2, p3, 1.0f, color);

        canvas->k2_drawline(center, p3, 1.0f, color);
        canvas->k2_drawline(center, p4, 1.0f, color);
        canvas->k2_drawline(p3, p4, 1.0f, color);

        canvas->k2_drawline(center, p4, 1.0f, color);
        canvas->k2_drawline(center, p5, 1.0f, color);
        canvas->k2_drawline(p4, p5, 1.0f, color);

        canvas->k2_drawline(center, p5, 1.0f, color);
        canvas->k2_drawline(center, p0, 1.0f, color);
        canvas->k2_drawline(p5, p0, 1.0f, color);
    }

    void DrawSimpleCircle(fvector2d center, float radius, flinearcolor color,
        ucanvas* canvas) {
        constexpr float PI = 3.14159265359f;

        float angle0 = 0.0f;
        float angle1 = PI / 3.0f;
        float angle2 = 2.0f * PI / 3.0f;
        float angle3 = PI;
        float angle4 = 4.0f * PI / 3.0f;
        float angle5 = 5.0f * PI / 3.0f;

        fvector2d p0 = { center.x + cosf(angle0) * radius,
                        center.y + sinf(angle0) * radius };
        fvector2d p1 = { center.x + cosf(angle1) * radius,
                        center.y + sinf(angle1) * radius };
        fvector2d p2 = { center.x + cosf(angle2) * radius,
                        center.y + sinf(angle2) * radius };
        fvector2d p3 = { center.x + cosf(angle3) * radius,
                        center.y + sinf(angle3) * radius };
        fvector2d p4 = { center.x + cosf(angle4) * radius,
                        center.y + sinf(angle4) * radius };
        fvector2d p5 = { center.x + cosf(angle5) * radius,
                        center.y + sinf(angle5) * radius };

        canvas->k2_drawline(p0, p1, 1.0f, color);
        canvas->k2_drawline(p1, p2, 1.0f, color);
        canvas->k2_drawline(p2, p3, 1.0f, color);
        canvas->k2_drawline(p3, p4, 1.0f, color);
        canvas->k2_drawline(p4, p5, 1.0f, color);
        canvas->k2_drawline(p5, p0, 1.0f, color);
    }

    namespace radar {
        static fvector pRadar;
        /*void DrawCircleRadar(int x, int y, int radius, flinearcolor color, ucanvas*
        cvs)
        {
            DrawFilledCircle(fvector2d(x, y), radius, color, cvs);
        }*/

        void DrawCircleRadar(int x, int y, int radius, flinearcolor color,
            ucanvas* canvas) {
            // Outer glow
            flinearcolor glowColor = color;
            glowColor.a *= 0.25f;
            DrawSmoothFilledCircle(fvector2d(x, y), radius + 2, glowColor, canvas);

            // Solid core
            DrawSmoothFilledCircle(fvector2d(x, y), radius, color, canvas);
        }

        fvector WorldRadar(fvector srcPos, fvector distPos, float yaw, float radarX,
            float radarY, float size) {
            auto cosYaw = cos(DegreeToRadian(yaw));
            auto sinYaw = sin(DegreeToRadian(yaw));

            auto deltaX = srcPos.x - distPos.x;
            auto deltaY = srcPos.y - distPos.y;

            auto locationX = (float)(deltaY * cosYaw - deltaX * sinYaw) / 45.f;
            auto locationY = (float)(deltaX * cosYaw + deltaY * sinYaw) / 45.f;

            if (locationX > (size - 2.f))
                locationX = (size - 2.f);
            else if (locationX < -(size - 2.f))
                locationX = -(size - 2.f);

            if (locationY > (size - 6.f))
                locationY = (size - 6.f);
            else if (locationY < -(size - 6.f))
                locationY = -(size - 6.f);

            return fvector((int)(-locationX + radarX), (int)(locationY + radarY), 0);
        }

        static float closestDistance = FLT_MAX;
        static ashootercharacter* pulsingActor = nullptr;

        inline float GetPulseScale() {
            float time = GetTickCount64() / 1000.f;  // system time in seconds
            return 1.0f + 0.25f * sinf(time * 5.0f); // pulsing between 1.0x - 1.25x
        }

        void DrawRadar(fvector EntityPos, acknowledgedpawn* MyPawns, ucanvas* cvs,
            ashootercharacter* actor) {
            if (!actor || !actor->is_alive())
                return; // skip dead enemies

            aplayercameramanager* camerap = controllers->get_camera_manager();
            int radar_posX = pRadar.x + 135;
            int radar_posY = pRadar.y + 135;

            uint64_t LocalRootComp =
                memory::read<uint64_t>((uint64_t)MyPawns + offsets::Rootcomponent);
            fvector LocalPos =
                memory::read<fvector>(LocalRootComp + offsets::root_position);
            FMinimalViewInfo camerae =
                memory::read<FMinimalViewInfo>((uint64_t)camerap + offsets::CameraRadar);

            fvector Radar2D = WorldRadar(LocalPos, EntityPos, camerae.Rotation.y,
                radar_posX, radar_posY, 135.f);

            float distance = (EntityPos - LocalPos).length();
            bool Visible = controllers->line_of_sight(actor);

            // Determine if this is the closest actor this frame
            if (distance < closestDistance) {
                closestDistance = distance;
                pulsingActor = actor;
            }

            float baseSize = 5.0f;
            float pulseSize = (actor == pulsingActor && distance < 1000.f)
                ? baseSize * GetPulseScale()
                : baseSize;

            // Shadow effect
            flinearcolor shadowColor = { 0.f, 0.f, 0.f, 0.3f };
            DrawCircleRadar(Radar2D.x + 1, Radar2D.y + 1, pulseSize, shadowColor, cvs);

            // Main radar blip
            if (Visible) {
                static flinearcolor greenColor{ 0.0f, 1.0f, 0.0f, 1.0f };
                DrawCircleRadar(Radar2D.x, Radar2D.y, pulseSize, greenColor, cvs);
            }
            else {
                static flinearcolor redColor{ 1.0f, 0.0f, 0.0f, 1.0f };
                DrawCircleRadar(Radar2D.x, Radar2D.y, pulseSize, redColor, cvs);
            }
        }

        // Call this at the beginning of each frame, before drawing enemies
        void ResetRadarPulse() {
            closestDistance = DBL_MAX;
            pulsingActor = nullptr;
        }
    } // namespace radar





// =====================================================================
// N A T I V E S - backtrack (FIXED)
// =====================================================================



// =====================================================================
// S I K K E V E R - GALAXY LIB
// =====================================================================
    void ApplyPurpleGalaxy(uskeletalmeshcomponent* mesh) {
        if (!mesh || !memory::IsValidPointer((uintptr_t)mesh)) return;

        static uobject* visible_material = nullptr;
        if (!visible_material) {
            visible_material = uobject::find_object<uobject*>(L"/Game/Characters/BountyHunter/S0/VFX/Materials/BountyHunterReveal_MI.BountyHunterReveal_MI");
            if (!visible_material) visible_material = uobject::static_load_object(nullptr, nullptr, L"/Game/Characters/BountyHunter/S0/VFX/Materials/BountyHunterReveal_MI.BountyHunterReveal_MI");
            if (!visible_material) visible_material = uobject::static_load_object(nullptr, nullptr, L"/Game/VFX/Materials/HunterReveal_MI.HunterReveal_MI");
        }
        if (!visible_material) return;

        static fname n_silohuette, n_center, n_inner, n_outer, n_glow;
        static bool init = false;
        if (!init) {
            n_silohuette = string::string_to_name(L"SilohuetteColor");
            n_center = string::string_to_name(L"CenterEdgeColor");
            n_inner = string::string_to_name(L"InnerEdgeColor");
            n_outer = string::string_to_name(L"OuterEdgeColor");
            n_glow = string::string_to_name(L"GlowIntensity");
            init = true;
        }

        // 0.5 saniyede bir renk değiştir
        static int color_index = 0;
        static float last_change = 0.0f;
        float now = GetTickCount64() / 1000.0f;
        if (now - last_change > 0.5f) {
            color_index = (color_index + 1) % 5;
            last_change = now;
        }

        flinearcolor purple_outer, purple_inner, purple_center;
        float glow = 35.0f;

        // Mavi
        if (color_index == 0) {
            purple_outer = { 0.02f, 0.0f, 0.3f, 1.0f };
            purple_inner = { 0.0f, 0.5f, 1.0f, 1.0f };
            purple_center = { 0.5f, 0.8f, 1.0f, 1.0f };
        }
        // Mor
        else if (color_index == 1) {
            purple_outer = { 0.02f, 0.0f, 0.2f, 1.0f };
            purple_inner = { 0.6f, 0.0f, 1.0f, 1.0f };
            purple_center = { 1.0f, 0.8f, 1.0f, 1.0f };
        }
        // Yeşil
        else if (color_index == 2) {
            purple_outer = { 0.0f, 0.1f, 0.0f, 1.0f };
            purple_inner = { 0.0f, 1.0f, 0.3f, 1.0f };
            purple_center = { 0.5f, 1.0f, 0.8f, 1.0f };
        }
        // Kırmızı
        else if (color_index == 3) {
            purple_outer = { 0.2f, 0.0f, 0.0f, 1.0f };
            purple_inner = { 1.0f, 0.0f, 0.2f, 1.0f };
            purple_center = { 1.0f, 0.6f, 0.6f, 1.0f };
        }
        // Pembe
        else {
            purple_outer = { 0.2f, 0.0f, 0.1f, 1.0f };
            purple_inner = { 1.0f, 0.2f, 0.6f, 1.0f };
            purple_center = { 1.0f, 0.7f, 0.9f, 1.0f };
        }

        UPrimitiveComponent* prim = (UPrimitiveComponent*)mesh;
        int num_mats = prim->get_num_materials();
        if (num_mats <= 0 || num_mats > 10) num_mats = 3;

        for (int i = 0; i < num_mats; i++) {
            uobject* dyn_mat = mesh->create_and_set_material_instance_dynamic_from_material(i, visible_material);
            if (dyn_mat && memory::IsValidPointer((uintptr_t)dyn_mat)) {
                auto dynCast = (UMaterialInstanceDynamic*)dyn_mat;
                dynCast->set_vector_parameter_value2(n_silohuette, purple_outer);
                dynCast->set_vector_parameter_value2(n_center, purple_center);
                dynCast->set_vector_parameter_value2(n_inner, purple_inner);
                dynCast->set_vector_parameter_value2(n_outer, purple_outer);
                dynCast->set_scalar_parameter_value2(n_glow, glow);
            }
        }
    }

    // =====================================================================
    // N A T I V E - Mosca Wireframe
    // =====================================================================
    void moscawireframe(ashootercharacter* local_player) {
        if (!local_player || !local_player->is_alive()) return;

        static uobject* crystal_material = nullptr;
        if (!crystal_material) {
            crystal_material = uobject::static_load_object(nullptr, nullptr,
                L"/Game/Equippables/_Core/Materials/Weapon_Holo_Translucent_Mi.Weapon_Holo_Translucent_Mi");
            if (!crystal_material) return;
        }
        if (!memory::IsValidPointer((uintptr_t)crystal_material)) return;

        float R = globals::visuals::MoscaRed / 255.0f;
        float G = globals::visuals::MoscaGreen / 255.0f;
        float B = globals::visuals::MoscaBlue / 255.0f;
        float glow = globals::visuals::HandChamsGlow;
        float fresnel_base = globals::visuals::AlphaBasePower;
        float fade = globals::visuals::HandFadeStrength;

        flinearcolor main_color(R, G, B, 1.0f);
        float gray = (R + G + B) / 3.0f;
        flinearcolor hand_color(
            R + (gray - R) * fade * 0.6f,
            G + (gray - G) * fade * 0.6f,
            B + (gray - B) * fade * 0.6f,
            1.0f
        );

        auto apply_mesh1p = [&](uskeletalmeshcomponent* mesh) {
            if (!mesh || !memory::IsValidPointer((uintptr_t)mesh)) return;
            int num = mesh->get_num_materials();
            for (int i = 0; i < num; i++) {
                uobject* inst = mesh->create_and_set_material_instance_dynamic_from_material(i, crystal_material);
                if (!inst || !memory::IsValidPointer((uintptr_t)inst)) continue;
                UMaterialInstanceDynamic* mid = inst->cast<UMaterialInstanceDynamic>();
                if (!mid) continue;

                mid->set_vector_parameter_value(string::string_to_name(L"BaseColor"), main_color);
                mid->set_vector_parameter_value(string::string_to_name(L"Diffuse"), main_color);
                mid->set_vector_parameter_value(string::string_to_name(L"Spec Color"), main_color);
                mid->set_vector_parameter_value(string::string_to_name(L"Spec"), main_color);
                mid->set_scalar_parameter_value(string::string_to_name(L"FresnelPower"), fresnel_base);
                mid->set_scalar_parameter_value(string::string_to_name(L"Fresnel Exponent"), 1.5f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Emissive Boost"), glow / 10.0f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Opacity"), 1.0f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Metallic Add"), 0.0f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Roughness Add"), 0.25f);
                mid->set_scalar_parameter_value(string::string_to_name(L"SpecTile"), 1.0f);
                mid->set_scalar_parameter_value(string::string_to_name(L"AO Clamp"), 0.0f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Use Normal Map"), 1.0f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Use Diffuse Color"), 1.0f);
            }
            };

        auto apply_overlay = [&](uskeletalmeshcomponent* mesh) {
            if (!mesh || !memory::IsValidPointer((uintptr_t)mesh)) return;
            int num = mesh->get_num_materials();
            for (int i = 0; i < num; i++) {
                uobject* inst = mesh->create_and_set_material_instance_dynamic_from_material(i, crystal_material);
                if (!inst || !memory::IsValidPointer((uintptr_t)inst)) continue;
                UMaterialInstanceDynamic* mid = inst->cast<UMaterialInstanceDynamic>();
                if (!mid) continue;

                mid->set_vector_parameter_value(string::string_to_name(L"BaseColor"), hand_color);
                mid->set_vector_parameter_value(string::string_to_name(L"Diffuse"), hand_color);
                mid->set_vector_parameter_value(string::string_to_name(L"Spec Color"), hand_color);
                mid->set_vector_parameter_value(string::string_to_name(L"Spec"), hand_color);
                mid->set_scalar_parameter_value(string::string_to_name(L"FresnelPower"), 8.0f + fade * 4.0f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Fresnel Exponent"), 4.0f + fade * 2.0f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Emissive Boost"), 0.2f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Opacity"), 0.9f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Metallic Add"), 0.0f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Roughness Add"), 0.7f + fade * 0.3f);
                mid->set_scalar_parameter_value(string::string_to_name(L"SpecTile"), 1.0f);
                mid->set_scalar_parameter_value(string::string_to_name(L"AO Clamp"), 0.0f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Use Normal Map"), 1.0f);
                mid->set_scalar_parameter_value(string::string_to_name(L"Use Diffuse Color"), 1.0f);
            }
            };

        uskeletalmeshcomponent* mesh1p = local_player->getmesh1p();
        uskeletalmeshcomponent* meshOverlay = local_player->GetOverlayMesh1P();

        if (mesh1p) apply_mesh1p(mesh1p);
        if (meshOverlay) apply_overlay(meshOverlay);
    }


    // =====================================================================
    // S I K K E V E R - MATERIALS
    // =====================================================================
    uobject* get_cached_hand_mat(int type) {
        static uobject* cache[15] = { nullptr };
        if (type < 0 || type >= 15) type = 0;
        if (!cache[type] || !memory::IsValidPointer((uintptr_t)cache[type])) {
            const wchar_t* path = L"";
            switch (type) {
            case 0: path = L"/Game/Equippables/_Core/Materials/3P_Weapon_Translucent_Mat.3P_Weapon_Translucent_Mat"; break;
            case 1: path = L"/Game/Characters/Vampire/S0/VFX/Ability_X/1P_Vampire_Tattoo_X_S0_MI_VFX.1P_Vampire_Tattoo_X_S0_MI_VFX"; break;
            case 2: path = L"/Game/Equippables/_Core/Materials/SpecialMaterials/Gems/1P_Gem_MAT.1P_Gem_MAT"; break;
            case 3: path = L"/Game/Equippables/_Core/Materials/1P_Weapon_Glass_Mat.1P_Weapon_Glass_Mat"; break;
            case 4: path = L"/Game/Equippables/_Core/Materials/SpecialMaterials/Sakura/Tritium_Sakura_3P_MI.Tritium_Sakura_3P_MI"; break;
            case 5: path = L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Yellow_MI.Arcade_Emissive_Yellow_MI"; break;
            case 6: path = L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Red_MI.Arcade_Emissive_Red_MI"; break;
            case 7: path = L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Blue_MI.Arcade_Emissive_Blue_MI"; break;
            case 8: path = L"/Game/Equippables/_Core/Materials/SpecialMaterials/Afterglow3/BakedLight/Afterglow3_BakedLight_MI.Afterglow3_BakedLight_MI"; break;
            default: path = L"/Game/Equippables/_Core/Materials/3P_Weapon_Translucent_Mat.3P_Weapon_Translucent_Mat"; break;
            }
            if (path[0] != L'\0') {
                uobject* mat = uobject::find_object<uobject*>(path);
                if (!mat) mat = uobject::static_load_object(nullptr, nullptr, path);
                cache[type] = mat;
            }
        }
        return cache[type];
    }


    void safe_hand_chams(ashootercharacter* character, int material_type) {
        if (!character || !character->is_alive()) return;

        uskeletalmeshcomponent* mesh1p = character->getmesh1p();
        uskeletalmeshcomponent* meshOverlay = character->GetOverlayMesh1P();

        if (!memory::IsValidPointer((uintptr_t)mesh1p) &&
            !memory::IsValidPointer((uintptr_t)meshOverlay))
            return;

        uobject* mat = get_cached_hand_mat(material_type);
        if (!mat || !memory::IsValidPointer((uintptr_t)mat)) return;

        auto apply_mat_to_mesh = [&](uskeletalmeshcomponent* mesh) {
            if (!mesh || !memory::IsValidPointer((uintptr_t)mesh)) return;
            UPrimitiveComponent* prim = reinterpret_cast<UPrimitiveComponent*>(mesh);
            if (!prim || !memory::IsValidPointer((uintptr_t)prim)) return;
            int num_mats = prim->get_num_materials();
            if (num_mats <= 0 || num_mats > 10) num_mats = 3;
            for (int i = 0; i < num_mats; i++) {
                mesh->create_and_set_material_instance_dynamic_from_material(i, mat);
            }
            };

        apply_mat_to_mesh(mesh1p);
        apply_mat_to_mesh(meshOverlay);

        static uobject* SetVisFunc = nullptr;
        if (!SetVisFunc) {
            SetVisFunc = uobject::find_object<uobject*>(L"Engine.SceneComponent.SetVisibility");
            if (!SetVisFunc) return;
        }

        if (meshOverlay && memory::IsValidPointer((uintptr_t)meshOverlay)) {
            struct {
                bool bNewVisibility;
                bool bPropagateToChildren;
            } visArgs = { true, true };
            reinterpret_cast<uobject*>(meshOverlay)->process_event(SetVisFunc, &visArgs);
        }
    }

    // =====================================================================
    // S I K K E V E R - 1P HAND & GUN CHAMS
    // =====================================================================
    void apply_local_chams(acknowledgedpawn* pawn, ashootercharacter* character) {
        if (!character || !character->is_alive()) return;

        uskeletalmeshcomponent* mesh1p = character->getmesh1p();
        uskeletalmeshcomponent* meshOverlay = character->GetOverlayMesh1P();

        currentequippable* current_weapon = character->get_inventory()->get_current_equippable();
        uskeletalmeshcomponent* gunMesh = nullptr;
        if (current_weapon && memory::IsValidPointer((uintptr_t)current_weapon)) {
            gunMesh = current_weapon->GetMesh1P();
        }

        auto apply_wireframe = [&](uskeletalmeshcomponent* mesh, bool enable, uint8_t opacity = 0xFF) {
            if (!mesh || !memory::IsValidPointer((uintptr_t)mesh)) return;
            uintptr_t addr = (uintptr_t)mesh;
            if (enable) {
                *(uint8_t*)(addr + 0x8FE) |= (1 << 5);
                *(uint8_t*)(addr + 0xC0) = opacity;
            }
            else {
                *(uint8_t*)(addr + 0x8FE) &= ~(1 << 5);
            }
            };

        auto set_visibility = [&](uskeletalmeshcomponent* comp, bool visible) {
            if (!comp || !memory::IsValidPointer((uintptr_t)comp)) return;
            static uobject* SetVisFunc = uobject::find_object<uobject*>(L"Engine.SceneComponent.SetVisibility");
            if (SetVisFunc) {
                struct { bool bNewVisibility; bool bPropagateToChildren; } VisArgs = { visible, true };
                ((uobject*)comp)->process_event(SetVisFunc, &VisArgs);
            }
            };

        auto apply_mat_to_mesh_dynamic = [&](uskeletalmeshcomponent* mesh, uobject* mat) {
            if (!mesh || !memory::IsValidPointer((uintptr_t)mesh) || !mat) return;
            UPrimitiveComponent* prim = (UPrimitiveComponent*)mesh;
            int num_mats = prim->get_num_materials();
            if (num_mats <= 0 || num_mats > 10) num_mats = 3;
            for (int i = 0; i < num_mats; i++) {
                mesh->create_and_set_material_instance_dynamic_from_material(i, mat);
            }
            };

        auto get_cached_mat = [](int type) -> uobject* {
            static uobject* cache[15] = { nullptr };
            if (type < 0 || type >= 15) type = 0;
            if (!cache[type] || !memory::IsValidPointer((uintptr_t)cache[type])) {
                const wchar_t* path = L"";
                switch (type) {
                case 0: path = L"/Game/Equippables/_Core/Materials/3P_Weapon_Translucent_Mat.3P_Weapon_Translucent_Mat"; break;
                case 1: path = L"/Game/Characters/Vampire/S0/VFX/Ability_X/1P_Vampire_Tattoo_X_S0_MI_VFX.1P_Vampire_Tattoo_X_S0_MI_VFX"; break;
                case 2: path = L"/Game/Equippables/_Core/Materials/SpecialMaterials/Gems/1P_Gem_MAT.1P_Gem_MAT"; break;
                case 3: path = L"/Game/Equippables/_Core/Materials/1P_Weapon_Glass_Mat.1P_Weapon_Glass_Mat"; break;
                case 4: path = L"/Game/Equippables/_Core/Materials/SpecialMaterials/Sakura/Tritium_Sakura_3P_MI.Tritium_Sakura_3P_MI"; break;
                case 5: path = L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Yellow_MI.Arcade_Emissive_Yellow_MI"; break;
                case 6: path = L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Red_MI.Arcade_Emissive_Red_MI"; break;
                case 7: path = L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Blue_MI.Arcade_Emissive_Blue_MI"; break;
                case 8: path = L"/Game/Equippables/_Core/Materials/SpecialMaterials/Afterglow3/BakedLight/Afterglow3_BakedLight_MI.Afterglow3_BakedLight_MI"; break;
                default: path = L"/Game/Equippables/_Core/Materials/3P_Weapon_Translucent_Mat.3P_Weapon_Translucent_Mat"; break;
                }
                if (path[0] != L'\0') {
                    uobject* mat = uobject::find_object<uobject*>(path);
                    if (!mat) mat = uobject::static_load_object(nullptr, nullptr, path);
                    cache[type] = mat;
                }
            }
            return cache[type];
            };

        // --- 1P HANDS ---
        if (globals::misc::HandWire) {
            apply_wireframe(mesh1p, true);
            apply_wireframe(meshOverlay, true);
        }
        else {
            apply_wireframe(mesh1p, false);
            apply_wireframe(meshOverlay, false);

            if (globals::visuals::moscawireframe_enabled) {
                set_visibility(meshOverlay, true);
                apply_wireframe(mesh1p, true, (uint8_t)globals::visuals::ShoulderWireOpacity);
                apply_wireframe(meshOverlay, true, (uint8_t)globals::visuals::HandWireOpacity);
                moscawireframe(character);
            }
            else if (globals::chams::hands_galaxy_enabled) {
                set_visibility(meshOverlay, true);
                ApplyPurpleGalaxy(mesh1p);
                ApplyPurpleGalaxy(meshOverlay);
            }
            else if (globals::visuals::safe_hand_chams) {
                set_visibility(meshOverlay, true);
                safe_hand_chams(character, globals::visuals::typehand);
            }
            else {
                set_visibility(meshOverlay, true);
            }
        }

        if (globals::misc::WireframeGun) {
            apply_wireframe(gunMesh, true);
        }
        else {
            apply_wireframe(gunMesh, false);
        }
    }


    // =====================================================================
    // S I K K E V E R - 3P SELF CHAMS
    // =====================================================================
    void apply_self_chams_3p(ashootercharacter* local_player) {
        if (!local_player || !local_player->is_alive()) return;

        uskeletalmeshcomponent* cosmetic_mesh = local_player->GetCosmeticMesh3P();
        uskeletalmeshcomponent* main_mesh = local_player->get_mesh();

        auto apply_wireframe_3p = [&](uskeletalmeshcomponent* mesh, bool enable) {
            if (!mesh || !memory::IsValidPointer((uintptr_t)mesh)) return;
            uintptr_t addr = (uintptr_t)mesh;
            if (enable) {
                *(uint8_t*)(addr + 0x8FE) |= (1 << 5);
                *(uint8_t*)(addr + 0xC0) = 0xFF;
            }
            else {
                *(uint8_t*)(addr + 0x8FE) &= ~(1 << 5);
            }
            };

        apply_wireframe_3p(cosmetic_mesh, globals::misc::self_wireframe);
        apply_wireframe_3p(main_mesh, globals::misc::self_wireframe);

        if (globals::chams::self_galaxy_enabled) {
            ApplyPurpleGalaxy(cosmetic_mesh);
            ApplyPurpleGalaxy(main_mesh);
        }
    }




// =====================================================================
// N  A T I V E S - ULTIMATE RESOLVER (WORKING - NO ROTATION FUNCTIONS)
// =====================================================================

    class UltimateResolver {
    private:
        struct PlayerData {
            // Hareket bilgileri
            fvector lastVelocity = { 0, 0, 0 };
            float lastYaw = 0.0f;
            float lastMovingYaw = 0.0f;
            bool wasMoving = false;
            uint64_t lastUpdateTime = 0;

            // Desync tespiti
            float desyncOffset = 58.0f;
            int desyncDirection = 1;
            int missedCount = 0;
            int hitCount = 0;
            int bruteStage = 0;

            // Yaw geçmişi
            float yawHistory[8] = { 0 };
            int historyIndex = 0;
            float avgYaw = 0.0f;

            // Zaman
            uint64_t lastShotTime = 0;
            uint64_t lastHitTime = 0;
        };

        std::unordered_map<uintptr_t, PlayerData> m_data;
        bool m_enabled = false;

    public:
        void SetEnabled(bool enabled) {
            m_enabled = enabled;
            if (!enabled) m_data.clear();
        }
        bool IsEnabled() const { return m_enabled; }

        // Bir oyuncunun yaw açısını al - actor'ün location'ından yön türet
        float GetPlayerYawFromPosition(ashootercharacter* target, aplayercontroller* controller) {
            if (!target || !controller) return 0.0f;

            // Oyuncunun pozisyonunu al
            fvector targetPos = target->k2_get_actor_location();
            if (!targetPos.is_valid()) return 0.0f;

            // Kamera pozisyonunu al
            aplayercameramanager* cam = controller->get_camera_manager();
            if (!cam) return 0.0f;
            fvector camPos = cam->get_camera_location();

            // Hedefe olan yönü hesapla (bu düşmanın baktığı yön değil ama desync için yeterli)
            fvector delta = targetPos - camPos;
            float yaw = atan2(delta.y, delta.x) * (180.0f / M_PI);

            return yaw;
        }

        // Ana Resolve fonksiyonu - Desync'li kafanın gerçek pozisyonunu döndürür
        fvector Resolve(ashootercharacter* target, aplayercontroller* controller, const fvector& cameraPos) {
            if (!m_enabled || !target || !controller) {
                uskeletalmeshcomponent* mesh = target ? target->get_mesh() : nullptr;
                return mesh ? mesh->get_bone_location(8) : fvector(0, 0, 0);
            }

            uintptr_t key = (uintptr_t)target;
            PlayerData& data = m_data[key];

            uskeletalmeshcomponent* mesh = target->get_mesh();
            if (!mesh) return fvector(0, 0, 0);

            fvector headPos = mesh->get_bone_location(8);
            if (!headPos.is_valid()) return fvector(0, 0, 0);

            // Hareket bilgileri (velocity üzerinden)
            fvector velocity = target->get_velocity();
            float velMag = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
            bool isMoving = (velMag > 50.0f);

            uint64_t now = GetTickCount64();

            // Hareket ediyorsa normal head'e vur (desync yoktur)
            if (isMoving) {
                if (!data.wasMoving) {
                    data.lastMovingYaw = 0.0f; // Yaw alamıyoruz ama hareket ediyor
                    data.missedCount = 0;
                }
                data.wasMoving = true;
                data.lastUpdateTime = now;
                return headPos;
            }

            data.wasMoving = false;

            // Desync offset'ini hesapla (isabet/kaçırma oranına göre)
            float finalOffset = 0.0f;
            int totalShots = data.hitCount + data.missedCount;
            float hitRate = totalShots > 0 ? (float)data.hitCount / totalShots : 0.5f;

            if (hitRate < 0.3f && data.missedCount > 2) {
                // Çok kaçırıyorsak brute force ile dene
                const float angles[] = { 58.0f, -58.0f, 60.0f, -60.0f, 120.0f, -120.0f, 180.0f, 0.0f };
                int idx = data.bruteStage % 8;
                finalOffset = angles[idx];
                data.bruteStage++;
                data.missedCount = 0;
            }
            else if (data.hitCount > data.missedCount && data.desyncOffset != 0.0f) {
                // İsabet aldığımız offset'i kullan
                finalOffset = data.desyncOffset * data.desyncDirection;
            }
            else {
                // Henüz isabet alamadıysak +58 ve -58 arasında dön
                static int flip = 0;
                flip++;
                finalOffset = (flip % 2 == 0) ? 58.0f : -58.0f;
                data.desyncDirection = (finalOffset > 0) ? 1 : -1;
                data.desyncOffset = 58.0f;
            }

            // Desync offset'ine göre head pozisyonunu kaydır
            // Valorant'da desync genelde yatay eksende 5-10 birim kayma yapar
            fvector resolvedPos = headPos;

            // Sağa veya sola kaydır (desync yönüne göre)
            float offsetAmount = 7.0f; // Pixel cinsinden kayma miktarı
            if (finalOffset > 0) {
                resolvedPos.x += offsetAmount;  // Sağa kaydır
            }
            else if (finalOffset < 0) {
                resolvedPos.x -= offsetAmount;  // Sola kaydır
            }

            // Ek olarak yukarı/aşağı küçük bir random offset (hitbox expansion etkisi)
            resolvedPos.z += (rand() % 6 - 3) * 0.5f;

            return resolvedPos;
        }

        // İsabet bildirimi (Damage numbers'dan çağrılacak)
        void OnHit(ashootercharacter* target) {
            if (!m_enabled || !target) return;
            uintptr_t key = (uintptr_t)target;
            PlayerData& data = m_data[key];
            data.hitCount++;
            data.missedCount = max(0, data.missedCount - 1);
            data.lastHitTime = GetTickCount64();
            data.bruteStage = 0;
        }

        // Kaçırma bildirimi
        void OnMiss(ashootercharacter* target) {
            if (!m_enabled || !target) return;
            uintptr_t key = (uintptr_t)target;
            PlayerData& data = m_data[key];
            data.missedCount++;
            data.lastShotTime = GetTickCount64();
        }

        // Resolver durumunu sıfırla (round başında çağrılabilir)
        void Reset() {
            m_data.clear();
        }
    };

    // Global resolver instance
    static UltimateResolver g_Resolver;




    //////// DOUBLE TAP///////////////////////

#pragma once
#include "includes.hpp"
#include <unordered_map>
#include <chrono>

    namespace features {

        class CDoubleTap {
        private:
            struct WeaponData {
                float normalFireRate = 0.15f;     // Normal ateş hızı (saniye)
                float dtFireRate = 0.012f;        // DT ateş hızı (12ms)
                DWORD lastShotTime = 0;
                DWORD lastDTTime = 0;
                int shotsFired = 0;               // 0=bekle, 1=ilk mermi atıldı, 2=ikinci mermi atıldı
                bool dtActive = false;
                uintptr_t lastWeaponPtr = 0;
            };

            std::unordered_map<uintptr_t, WeaponData> m_weaponCache;
            bool m_enabled = false;
            int m_delayMs = 15;                   // DT delay (ms)
            bool m_onlyOnHead = true;             // Sadece kafaya vururken DT aç
            bool m_rapidMode = false;             // Rapid fire modu (3+ mermi)
            int m_burstCount = 2;                 // Kaç mermi (2=normal DT, 3+=rapid)

            // Son atış yapılan hedef (aynı hedefe mi vuruyoruz kontrolü)
            uintptr_t m_lastTarget = 0;
            DWORD m_lastTargetTime = 0;

        public:
            // ---------------------------------------------------------------------
            //  KONSTRÜKTÖR & TEMEL AYARLAR
            // ---------------------------------------------------------------------
            CDoubleTap() = default;

            void SetEnabled(bool enabled) {
                m_enabled = enabled;
                if (!enabled) ResetAll();
            }

            bool IsEnabled() const { return m_enabled; }

            void SetDelay(int ms) {
                m_delayMs = std::clamp(ms, 5, 50);
            }

            int GetDelay() const { return m_delayMs; }

            void SetOnlyOnHead(bool only) { m_onlyOnHead = only; }

            void SetRapidMode(bool rapid, int burst = 3) {
                m_rapidMode = rapid;
                m_burstCount = rapid ? std::clamp(burst, 2, 5) : 2;
            }

            // ---------------------------------------------------------------------
            //  ANA ATIŞ KONTROLÜ - NORMAL KAFAYA VURARKEN 2 MERMİ SIKAR
            // ---------------------------------------------------------------------
            bool ShouldDoubleTap(currentequippable* weapon, bool isAimingAtHead, uintptr_t targetPtr = 0) {
                if (!m_enabled || !weapon) return false;

                // Sadece kafaya vuruyorsak DT aç
                if (m_onlyOnHead && !isAimingAtHead) return false;

                // Aynı hedefe mi vuruyoruz kontrolü (hedef değiştiyse reset)
                if (targetPtr != 0 && targetPtr != m_lastTarget) {
                    ResetWeapon(weapon);
                    m_lastTarget = targetPtr;
                    m_lastTargetTime = GetTickCount();
                }

                uintptr_t key = (uintptr_t)weapon;
                WeaponData& data = m_weaponCache[key];

                // Silah değişti mi?
                if (data.lastWeaponPtr != key) {
                    data = WeaponData();
                    data.lastWeaponPtr = key;
                }

                DWORD now = GetTickCount();

                // Rapid fire modu (3+ mermi)
                if (m_rapidMode) {
                    return HandleRapidFire(data, now);
                }

                // Normal Double Tap (2 mermi)
                return HandleDoubleTap(data, now);
            }

            // ---------------------------------------------------------------------
            //  ATIŞ SONRASI ÇAĞIR - İKİNCİ MERMİYİ GÖNDER
            // ---------------------------------------------------------------------
            bool NeedSecondShot(currentequippable* weapon) {
                if (!m_enabled || !weapon) return false;

                uintptr_t key = (uintptr_t)weapon;
                auto it = m_weaponCache.find(key);
                if (it == m_weaponCache.end()) return false;

                WeaponData& data = it->second;
                DWORD now = GetTickCount();

                // İlk mermi atıldı mı?
                if (data.shotsFired != 1) return false;

                // DT delay süresi geçti mi?
                if ((now - data.lastShotTime) >= (DWORD)m_delayMs) {
                    data.shotsFired = 2;
                    data.lastDTTime = now;
                    return true;
                }

                return false;
            }

            // ---------------------------------------------------------------------
            //  İKİNCİ MERMİ ATILDIKTAN SONRA RESET
            // ---------------------------------------------------------------------
            void OnSecondShotFired(currentequippable* weapon) {
                if (!weapon) return;

                uintptr_t key = (uintptr_t)weapon;
                auto it = m_weaponCache.find(key);
                if (it != m_weaponCache.end()) {
                    WeaponData& data = it->second;

                    // Rapid modda devam ediyorsak resetleme
                    if (m_rapidMode && data.shotsFired < m_burstCount) {
                        // Devam et, resetleme
                        return;
                    }

                    // Tamamen resetle
                    data.shotsFired = 0;
                    data.lastShotTime = 0;
                }
            }

            // ---------------------------------------------------------------------
            //  RESET FONKSİYONLARI
            // ---------------------------------------------------------------------
            void ResetWeapon(currentequippable* weapon) {
                if (!weapon) return;
                uintptr_t key = (uintptr_t)weapon;
                auto it = m_weaponCache.find(key);
                if (it != m_weaponCache.end()) {
                    it->second.shotsFired = 0;
                    it->second.lastShotTime = 0;
                }
            }

            void ResetAll() {
                for (auto& pair : m_weaponCache) {
                    pair.second.shotsFired = 0;
                    pair.second.lastShotTime = 0;
                    pair.second.lastDTTime = 0;
                }
                m_lastTarget = 0;
            }

            void ResetTarget() {
                m_lastTarget = 0;
            }

            // ---------------------------------------------------------------------
            //  BİLGİ GETİRME
            // ---------------------------------------------------------------------
            bool IsDoubleTapping(currentequippable* weapon) {
                if (!weapon) return false;
                uintptr_t key = (uintptr_t)weapon;
                auto it = m_weaponCache.find(key);
                if (it == m_weaponCache.end()) return false;
                return (it->second.shotsFired == 1);
            }

            bool IsInDTDelay(currentequippable* weapon) {
                if (!weapon) return false;
                uintptr_t key = (uintptr_t)weapon;
                auto it = m_weaponCache.find(key);
                if (it == m_weaponCache.end()) return false;

                WeaponData& data = it->second;
                if (data.shotsFired != 1) return false;

                DWORD now = GetTickCount();
                return ((now - data.lastShotTime) < (DWORD)m_delayMs);
            }

            int GetRemainingBurst(currentequippable* weapon) {
                if (!weapon || !m_rapidMode) return 0;
                uintptr_t key = (uintptr_t)weapon;
                auto it = m_weaponCache.find(key);
                if (it == m_weaponCache.end()) return 0;
                return m_burstCount - it->second.shotsFired;
            }

        private:
            // ---------------------------------------------------------------------
            //  NORMAL DOUBLE TAP (2 MERMİ)
            // ---------------------------------------------------------------------
            bool HandleDoubleTap(WeaponData& data, DWORD now) {
                // İlk atış (normal)
                if (data.shotsFired == 0) {
                    data.lastShotTime = now;
                    data.shotsFired = 1;
                    return true;  // İlk mermiyi gönder
                }

                // İkinci atış için bekliyoruz (NeedSecondShot'da kontrol edilecek)
                if (data.shotsFired == 1) {
                    return false;  // İkinci mermi için bekle
                }

                // Normal delay süresi geçti mi? (reset için)
                DWORD normalDelay = (DWORD)(data.normalFireRate * 1000);
                if (data.shotsFired == 2 && (now - data.lastDTTime) >= normalDelay) {
                    data.shotsFired = 0;
                    data.lastShotTime = 0;
                    return true;  // Yeni atış döngüsü
                }

                return false;
            }

            // ---------------------------------------------------------------------
            //  RAPID FIRE MODU (3+ MERMİ)
            // ---------------------------------------------------------------------
            bool HandleRapidFire(WeaponData& data, DWORD now) {
                // İlk atış
                if (data.shotsFired == 0) {
                    data.lastShotTime = now;
                    data.shotsFired = 1;
                    return true;
                }

                // Devam eden atışlar (2, 3, 4...)
                if (data.shotsFired > 0 && data.shotsFired < m_burstCount) {
                    // DT delay kadar bekledik mi?
                    if ((now - data.lastShotTime) >= (DWORD)m_delayMs) {
                        data.lastShotTime = now;
                        data.shotsFired++;
                        return true;
                    }
                }

                // Burst tamamlandı, reset için bekle
                if (data.shotsFired >= m_burstCount) {
                    DWORD normalDelay = (DWORD)(data.normalFireRate * 1000);
                    if ((now - data.lastShotTime) >= normalDelay) {
                        data.shotsFired = 0;
                        data.lastShotTime = 0;
                    }
                }

                return false;
            }
        };

        // -------------------------------------------------------------------------
        //  GLOBAL INSTANCE
        // -------------------------------------------------------------------------
        inline CDoubleTap g_DoubleTap;

    } // namespace features



///////CLOSEST BONE ////////////////////////////////////

#pragma once
#include "includes.hpp"
#include <vector>
#include <algorithm>
#include <cmath>

    namespace features {

        class CClosestBone {
        private:
            struct BoneInfo {
                int boneId;
                std::wstring boneName;
                float priority;      // Öncelik (düşük sayı = daha öncelikli)
                float damageScale;   // Hasar çarpanı (kafa 4x, gövde 1x, bacak 0.8x)
            };

            std::vector<BoneInfo> m_bones;
            int m_selectedBone = -1;
            float m_lastDistance = FLT_MAX;
            bool m_onlyVisible = true;

            // Kemik isimleri ve ID'leri (Valorant bone indices)
            void InitializeBones() {
                m_bones.clear();

                // En öncelikli kemikler (yüksek hasar)
                m_bones.push_back({ 8, L"Head", 1.0f, 4.0f });        // Kafa
                m_bones.push_back({ 9, L"Neck", 2.0f, 3.5f });        // Boyun
                m_bones.push_back({ 6, L"Chest", 3.0f, 1.5f });       // Göğüs
                m_bones.push_back({ 7, L"UpperChest", 3.5f, 1.4f });   // Üst göğüs
                m_bones.push_back({ 5, L"Spine", 4.0f, 1.3f });        // Omurga
                m_bones.push_back({ 4, L"Stomach", 5.0f, 1.2f });      // Karın
                m_bones.push_back({ 3, L"Pelvis", 6.0f, 1.0f });       // Kasık

                // Kollar
                m_bones.push_back({ 23, L"LeftShoulder", 7.0f, 0.9f }); // Sol omuz
                m_bones.push_back({ 24, L"LeftArm", 8.0f, 0.85f });     // Sol kol
                m_bones.push_back({ 25, L"LeftHand", 9.0f, 0.8f });     // Sol el
                m_bones.push_back({ 49, L"RightShoulder", 7.5f, 0.9f }); // Sağ omuz
                m_bones.push_back({ 50, L"RightArm", 8.5f, 0.85f });     // Sağ kol
                m_bones.push_back({ 51, L"RightHand", 9.5f, 0.8f });     // Sağ el

                // Bacaklar (en düşük öncelik)
                m_bones.push_back({ 75, L"LeftThigh", 10.0f, 0.75f });   // Sol but
                m_bones.push_back({ 76, L"LeftCalf", 11.0f, 0.7f });     // Sol baldır
                m_bones.push_back({ 77, L"LeftFoot", 12.0f, 0.65f });     // Sol ayak
                m_bones.push_back({ 78, L"LeftToe", 13.0f, 0.6f });       // Sol ayak parmak
                m_bones.push_back({ 82, L"RightThigh", 10.5f, 0.75f });   // Sağ but
                m_bones.push_back({ 83, L"RightCalf", 11.5f, 0.7f });     // Sağ baldır
                m_bones.push_back({ 84, L"RightFoot", 12.5f, 0.65f });     // Sağ ayak
                m_bones.push_back({ 85, L"RightToe", 13.5f, 0.6f });       // Sağ ayak parmak
            }

        public:
            CClosestBone() {
                InitializeBones();
                m_onlyVisible = true;
            }

            // Ayarlar
            void SetOnlyVisible(bool only) { m_onlyVisible = only; }
            bool GetOnlyVisible() const { return m_onlyVisible; }

            void SetSelectedBone(int boneId) { m_selectedBone = boneId; }
            int GetSelectedBone() const { return m_selectedBone; }

            // ---------------------------------------------------------------------
            //  EN YAKIN GÖRÜNEN KEMİĞİ BUL
            // ---------------------------------------------------------------------
            struct ClosestBoneResult {
                int boneId;
                fvector worldPosition;
                fvector2d screenPosition;
                float distance;
                float priority;
                float damageScale;
                bool isVisible;
                std::wstring boneName;
            };

            ClosestBoneResult FindClosestVisibleBone(
                ashootercharacter* target,
                aplayercontroller* controller,
                const fvector& cameraPos,
                bool onlyVisible = true,
                bool prioritizeHead = true
            ) {
                ClosestBoneResult result;
                result.boneId = -1;
                result.distance = FLT_MAX;
                result.isVisible = false;
                result.damageScale = 1.0f;
                result.priority = 999.0f;

                if (!target || !controller) return result;

                uskeletalmeshcomponent* mesh = target->get_mesh();
                if (!mesh) return result;

                float bestScore = FLT_MAX;
                int bestBoneId = -1;
                fvector bestPos;
                float bestDamageScale = 1.0f;
                float bestPriority = 999.0f;
                std::wstring bestBoneName;

                // Her kemiği kontrol et
                for (const auto& bone : m_bones) {
                    // Eğer belirli bir kemik seçilmişse sadece onu kontrol et
                    if (m_selectedBone != -1 && bone.boneId != m_selectedBone) {
                        continue;
                    }

                    // Kemik pozisyonunu al
                    fvector bonePos = mesh->get_bone_location(bone.boneId);
                    if (!bonePos.is_valid()) continue;

                    // Ekrana project et
                    fvector2d screenPos;
                    bool onScreen = controller->project_world_location_to_screen(bonePos, screenPos, false);

                    // Görünürlük kontrolü
                    bool isVisible = false;
                    if (onlyVisible || m_onlyVisible) {
                        isVisible = controller->line_of_sight(target);
                        // Ekstra: Kemik pozisyonundan line trace ile kontrol
                        if (isVisible) {
                            FHitResult hit;
                            tarray<AActor*> ignore;
                            ignore.Add((AActor*)target);
                            // Basit görünürlük kontrolü
                            isVisible = true; // Şimdilik
                        }
                    }
                    else {
                        isVisible = onScreen;
                    }

                    if (onlyVisible && !isVisible) continue;

                    // Mesafe hesapla
                    float distance = (bonePos - cameraPos).size();

                    // Skor hesapla (öncelik + mesafe)
                    float score = bone.priority * 100.0f + distance * 0.1f;

                    // Kafaya öncelik ver (eğer prioritizeHead aktifse)
                    if (prioritizeHead && bone.boneId == 8) {
                        score -= 1000.0f; // Kafayı her zaman öne al
                    }

                    if (score < bestScore) {
                        bestScore = score;
                        bestBoneId = bone.boneId;
                        bestPos = bonePos;
                        bestDamageScale = bone.damageScale;
                        bestPriority = bone.priority;
                        bestBoneName = bone.boneName;
                        result.isVisible = isVisible;

                        if (onScreen) {
                            result.screenPosition = screenPos;
                        }
                    }
                }

                if (bestBoneId != -1) {
                    result.boneId = bestBoneId;
                    result.worldPosition = bestPos;
                    result.distance = (bestPos - cameraPos).size();
                    result.priority = bestPriority;
                    result.damageScale = bestDamageScale;
                    result.boneName = bestBoneName;

                    // Ekran pozisyonunu tekrar hesapla (güncel)
                    controller->project_world_location_to_screen(bestPos, result.screenPosition, false);
                }

                m_lastDistance = result.distance;
                return result;
            }

            // ---------------------------------------------------------------------
            //  HIZLI KONTROL - SADECE BİR KEMİK GÖRÜNÜYOR MU?
            // ---------------------------------------------------------------------
            bool IsAnyBoneVisible(ashootercharacter* target, aplayercontroller* controller) {
                if (!target || !controller) return false;

                uskeletalmeshcomponent* mesh = target->get_mesh();
                if (!mesh) return false;

                for (const auto& bone : m_bones) {
                    fvector bonePos = mesh->get_bone_location(bone.boneId);
                    if (!bonePos.is_valid()) continue;

                    if (controller->line_of_sight(target)) {
                        return true;
                    }
                }
                return false;
            }

            // ---------------------------------------------------------------------
            //  EN YAKIN KEMİĞİN HASAR ÇARPANINI GETİR
            // ---------------------------------------------------------------------
            float GetDamageMultiplier(int boneId) {
                for (const auto& bone : m_bones) {
                    if (bone.boneId == boneId) {
                        return bone.damageScale;
                    }
                }
                return 1.0f;
            }

            // ---------------------------------------------------------------------
            //  KEMİK İSMİNİ GETİR
            // ---------------------------------------------------------------------
            std::wstring GetBoneName(int boneId) {
                for (const auto& bone : m_bones) {
                    if (bone.boneId == boneId) {
                        return bone.boneName;
                    }
                }
                return L"Unknown";
            }

            // ---------------------------------------------------------------------
            //  MEVCUT HEDEFİN EN İYİ VURUŞ NOKTASINI BUL (AIMBOT İÇİN)
            // ---------------------------------------------------------------------
            fvector GetBestAimPoint(
                ashootercharacter* target,
                aplayercontroller* controller,
                const fvector& cameraPos,
                bool preferHead = true
            ) {
                ClosestBoneResult result = FindClosestVisibleBone(
                    target, controller, cameraPos, m_onlyVisible, preferHead
                );

                if (result.boneId != -1) {
                    return result.worldPosition;
                }

                // Hiçbir kemik görünmüyorsa, varsayılan olarak gövdeye dön
                uskeletalmeshcomponent* mesh = target->get_mesh();
                if (mesh) {
                    return mesh->get_bone_location(6); // Göğüs
                }

                return target->k2_get_actor_location(); // Son çare: ayaklar
            }

            // ---------------------------------------------------------------------
            //  KEMİK LİSTESİNİ GETİR (MENÜ İÇİN)
            // ---------------------------------------------------------------------
            std::vector<std::pair<int, std::wstring>> GetBoneList() {
                std::vector<std::pair<int, std::wstring>> bones;
                for (const auto& bone : m_bones) {
                    bones.push_back({ bone.boneId, bone.boneName });
                }
                return bones;
            }

            // ---------------------------------------------------------------------
            //  ÖN CELİKLİ KEMİK İLE VUR (Kafa yoksa gövdeye vur)
            // ---------------------------------------------------------------------
            fvector PrioritizedAimPoint(
                ashootercharacter* target,
                aplayercontroller* controller,
                const fvector& cameraPos
            ) {
                // Önce kafayı dene
                uskeletalmeshcomponent* mesh = target->get_mesh();
                if (mesh) {
                    fvector headPos = mesh->get_bone_location(8);
                    if (headPos.is_valid() && controller->line_of_sight(target)) {
                        return headPos; // Kafa görünüyorsa ona vur
                    }
                }

                // Kafa yoksa en yakın görünen kemiği bul
                return GetBestAimPoint(target, controller, cameraPos, false);
            }

            // ---------------------------------------------------------------------
            //  RESET
            // ---------------------------------------------------------------------
            void Reset() {
                m_lastDistance = FLT_MAX;
                m_selectedBone = -1;
            }
        };

        // Global instance
        inline CClosestBone g_ClosestBone;

    } // namespace features


    // ═════════════════════════════════════════════════════════════════════
    // S I K K E V E R - ENEMY CHAMS & WIREFRAME
    // ═════════════════════════════════════════════════════════════════════
    void apply_galaxy_chams(acknowledgedpawn* pawn, ashootercharacter* actor, aplayercontroller* controllers) {
        if (!pawn || !actor || !actor->is_alive()) return;

        uskeletalmeshcomponent* enemy_main_mesh = actor->get_mesh();
        uskeletalmeshcomponent* enemy_cosmetic_mesh = actor->GetCosmeticMesh3P();

        auto apply_enemy_wire = [&](uskeletalmeshcomponent* t_mesh, bool enable) {
            if (!t_mesh || !memory::IsValidPointer((uintptr_t)t_mesh)) return;
            uintptr_t addr = (uintptr_t)t_mesh;
            if (enable) {
                *(uint8_t*)(addr + 0x8FE) |= (1 << 5);
                *(uint8_t*)(addr + 0xC0) = 0xFF;
            }
            else {
                *(uint8_t*)(addr + 0x8FE) &= ~(1 << 5);
            }
            };

        if (globals::misc::Wireframe) {
            apply_enemy_wire(enemy_main_mesh, true);
            apply_enemy_wire(enemy_cosmetic_mesh, true);
        }
        else {
            apply_enemy_wire(enemy_main_mesh, false);
            apply_enemy_wire(enemy_cosmetic_mesh, false);
            if (enemy_main_mesh) actor->reset_character_materials_internal(enemy_main_mesh);
            if (enemy_cosmetic_mesh) actor->reset_character_materials_internal(enemy_cosmetic_mesh);
        }
    }


    // ═════════════════════════════════════════════════════════════════════
    // S I K K E V E R - UTILS & ANTI-BLIND
    // ═════════════════════════════════════════════════════════════════════
    void use_blind_manager_component(uobject* target_object) {
        auto blind_manager = static_cast<UBlindManagerComponent*>(target_object);
        if (!blind_manager || !memory::IsValidPointer((uintptr_t)blind_manager)) return;

        if (blind_manager->IsBlinded()) {
            blind_manager->SetBlinded(false);
            blind_manager->ClientCleanseBlinds();
        }
    }

    static bool saved_anti_aim = false;
    static bool saved_spinbot = false;
    static bool saved_tperson = false;
    static bool saved_auto_shot = false;
    static bool states_saved = false;
    static uint64_t no_enemies_start_time = 0;
    static uint64_t characters_found_time = 0;
    static bool waiting_for_reactivation = false;
    static const uint64_t DISABLE_DELAY = 2000;
    static const uint64_t ENABLE_DELAY = 500;
    ucanvas* canvas;

    // ═════════════════════════════════════════════════════════════════════
    // S I K K E V E R - ESP
    // ═════════════════════════════════════════════════════════════════════
    void draw_rect21(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color) {
        canvas->k2_drawline({ x, y }, { x + width, y }, 1.0f, color);
        canvas->k2_drawline({ x + width, y }, { x + width, y + height }, 1.0f, color);
        canvas->k2_drawline({ x + width, y + height }, { x, y + height }, 1.0f, color);
        canvas->k2_drawline({ x, y + height }, { x, y }, 1.0f, color);
    }

    inline auto DrawBorder(ucanvas* canva, float x, float y, float w, float h, float px, flinearcolor BorderColor) -> void {
        draw_rect21(canva, x, (y + h - px), w, px, BorderColor);
        draw_rect21(canva, x, y, px, h, BorderColor);
        draw_rect21(canva, x, y, w, px, BorderColor);
        draw_rect21(canva, (x + w - px), y, px, h, BorderColor);
    }

    void DrawLineCanvas(ucanvas* canvas, int x1, int y1, int x2, int y2, flinearcolor color, int thickness) {
        canvas->k2_drawline(fvector2d(x1, y1), fvector2d(x2, y2), thickness, color);
    }

    void draw_line_2(ucanvas* canvas, fvector2d from, fvector2d to, int thickness, flinearcolor color) {
        canvas->k2_drawline(from, to, static_cast<float>(thickness), color);
    }

    // ═════════════════════════════════════════════════════════════════════
    // S I K K E V E R - CONTROLS
    // ═════════════════════════════════════════════════════════════════════
    bool HasVisibleEnemy(tarray<ashootercharacter*>& actors, aplayercontroller* controllers, ashootercharacter* character) {
        for (int32_t idx = 0; idx < actors.count; ++idx) {
            ashootercharacter* actor = actors[idx];
            if (!actor || !memory::IsValidPointer((uintptr_t)actor) || actor == character || !actor->is_alive())
                continue;

            if (controllers->line_of_sight(actor)) {
                return true;
            }
        }
        return false;
    }

    bool GetAllActorsSafely(uworld* world, uobject* actor_class, tarray<AGameObject*>* Objects) {
        if (!world || !memory::IsValidPointer((uintptr_t)world)) return false;
        if (!actor_class || !memory::IsValidPointer((uintptr_t)actor_class)) return false;

        memset(Objects, 0, sizeof(*Objects));
        GameplayStatics::GetAllActorsOfClass2(world, actor_class, Objects);

        if (!memory::IsValidPointer((uintptr_t)Objects->data) && Objects->Num() > 0) return false;

        return true;
    }

    // ═════════════════════════════════════════════════════════════════════
    // S I K K E V E R - CUSTOM IMAGE CHAMS
    // ═════════════════════════════════════════════════════════════════════
    void apply_custom_hand_texture(acknowledgedpawn* pawn, ashootercharacter* character, uworld* world) {
        if (!pawn || !character || !world || !character->is_alive()) return;

        UPrimitiveComponent* mesh1p = memory::read<UPrimitiveComponent*>(uintptr_t(character) + offsets::mesh1p);
        UPrimitiveComponent* meshOverlay = memory::read<UPrimitiveComponent*>(uintptr_t(character) + offsets::mesh1p_overlay);

        if (!mesh1p || !meshOverlay || !memory::IsValidPointer((uintptr_t)mesh1p)) return;

        static uobject* CustomHandTexture = nullptr;
        static uobject* handMaterial = nullptr;
        static bool is_initialized = false;

        if (!is_initialized) {
            fstring customHandTexturePath = fstring(L"C:/hand.jpg");
            CustomHandTexture = system::import_file_as_texture2d(world, customHandTexturePath);

            handMaterial = uobject::static_load_object(nullptr, nullptr, L"/Game/Equippables/_Core/Materials/SpecialMaterials/CosmosShader/Winter/Winter_MI.Winter_MI");
            is_initialized = true;
        }

        if (!CustomHandTexture || !handMaterial) return;

        auto apply_custom_mat = [&](UPrimitiveComponent* comp) {
            if (!comp || !memory::IsValidPointer((uintptr_t)comp)) return;

            int n_mats = comp->get_num_materials();
            if (n_mats < 0 || n_mats > 10) return;
            if (n_mats == 0) n_mats = 2;

            if (comp->get_material(0) != handMaterial) {
                for (int i = 0; i < n_mats; i++) comp->set_material(i, handMaterial);

                uobject* DynamicMat = comp->create_and_set_material_instance_dynamic_from_material(0, handMaterial);
                if (DynamicMat && memory::IsValidPointer((uintptr_t)DynamicMat)) {
                    auto* mat = DynamicMat->cast<UMaterialInstanceDynamic>();
                    if (mat) {
                        mat->set_texture_parameter_value(string::string_to_name(crypt(L"Image 1").decrypt()), CustomHandTexture);
                        mat->set_texture_parameter_value(string::string_to_name(crypt(L"Image 2").decrypt()), CustomHandTexture);
                        mat->set_texture_parameter_value(string::string_to_name(crypt(L"Base Color").decrypt()), CustomHandTexture);
                        mat->set_texture_parameter_value(string::string_to_name(crypt(L"Diffuse").decrypt()), CustomHandTexture);
                        mat->set_texture_parameter_value(string::string_to_name(crypt(L"Texture").decrypt()), CustomHandTexture);
                    }
                }
            }
            };

        apply_custom_mat(mesh1p);
        apply_custom_mat(meshOverlay);
    }

    // using FinisherFn = void* (__fastcall*)(uintptr_t);

    // inline void* PlayFinisherEffect(uintptr_t effect)
    //{
    //     SPOOF_FUNC;
    //     static void* (__fastcall * fn)(uintptr_t) = nullptr;
    //     if (!fn)
    //         fn = reinterpret_cast<FinisherFn>(memory::module_base +
    //         offsets::player_finisher);

    //    return fn(effect);
    //}

    // void hk_death(ashootercharacter* shooter_character, UDamageResponse* a2) {
    //     try {
    //         if (!shooter_character ||
    //         !memory::IsValidPointer((uintptr_t)shooter_character)) {
    //             return oHkDeath(shooter_character, a2);
    //         }

    //        // Get local player context
    //        acknowledgedpawn* pawn = controllers->get_acknowledged_pawn();
    //        ashootercharacter* character_context = character;
    //        acknowledgedpawn* local_pawn_context = pawn;
    //        auto damage_response = a2;

    //        if (!character_context || !local_pawn_context || !damage_response) {
    //            return oHkDeath(shooter_character, a2);
    //        }

    //        // Validate pointers
    //        if (!memory::IsValidPointer((uintptr_t)character_context) ||
    //            !memory::IsValidPointer((uintptr_t)local_pawn_context) ||
    //            !memory::IsValidPointer((uintptr_t)damage_response)) {
    //            return oHkDeath(shooter_character, a2);
    //        }

    //        // Get death reaction component
    //        auto component =
    //        (uintptr_t)memory::read<uobject*>((uintptr_t)shooter_character +
    //        offsets::death_reaction_component_offset);

    //        if (!component || !memory::IsValidPointer(component)) {
    //            return oHkDeath(shooter_character, a2);
    //        }

    //        // Check death reaction flags
    //        BYTE b1 = memory::read<BYTE>(component + 0x15A);
    //        BYTE b2 = memory::read<BYTE>(component + 0x168);

    //        if (!(b1 == 0 || b2 == 1)) {
    //            return oHkDeath(shooter_character, a2);
    //        }

    //        // Get killer and weapon info
    //        auto killer = damage_response->get_damage_causer();
    //        auto equippable = damage_response->get_equippable_used();

    //        if (!killer || !equippable ||
    //            !memory::IsValidPointer((uintptr_t)killer) ||
    //            !memory::IsValidPointer((uintptr_t)equippable)) {
    //            return oHkDeath(shooter_character, a2);
    //        }

    //        // Get world context
    //        uworld* world_save = nullptr;
    //        uintptr_t* uworld_state_ptr = *(uintptr_t**)(memory::module_base +
    //        offsets::State); if (uworld_state_ptr) {
    //            world_save = *(uworld**)uworld_state_ptr;
    //        }

    //        if (!world_save || !memory::IsValidPointer((uintptr_t)world_save)) {
    //            return oHkDeath(shooter_character, a2);
    //        }

    //        // Find enemies
    //        tarray<ashootercharacter*> enemies =
    //        blueprints::find_all_shooters_with_alliance(
    //            world_save, character, earesalliance::enemy, false, true);

    //        currentequippable* my_weapon =
    //        character->get_inventory()->get_current_equippable();

    //        // Check if finisher should be processed
    //        bool process_finisher = globals::misc::finisher &&
    //            character->is_alive() &&
    //            character->health() > 0 &&
    //            character &&
    //            memory::IsValidPointer((uintptr_t)character);

    //        if (process_finisher) {
    //            if (killer == local_pawn_context) {
    //                int num_enemies = enemies.count;

    //                // Remove the killed enemy from count
    //                for (int i = 0; i < enemies.count; ++i) {
    //                    if (enemies[i] == shooter_character) {
    //                        num_enemies -= 1;
    //                        break;
    //                    }
    //                }

    //                // Check finisher conditions
    //                bool should_play_finisher = globals::misc::only_last_kill ?
    //                (num_enemies == 0) : true;

    //                if (globals::misc::finisher && should_play_finisher) {
    //                    std::string weapon_name =
    //                    system::get_object_name(my_weapon).to_str();

    //                    auto apply_finisher = [&]() {
    //                       /* std::wstring skin = get_chosen_skin(weapon_name);
    //                        printf("[DEBUG] get_chosen_skin weapon_name: %s\n",
    //                        weapon_name.c_str()); wprintf(L"[DEBUG] Chosen skin:
    //                        %ls\n", skin.empty() ? L"(none)" : skin.c_str());
    //                        uobject* finisher =
    //                        get_finisher_from_skin(skin.c_str());*/

    //                        /*    if (!finisher) {
    //                                return;
    //                            }*/

    //                            // Set up finisher override
    //                        static uobject* dummy_finisher =
    //                        uobject::find_object<uobject*>(L"FXC_Finisher_Champions_Victim_C",
    //                        (uobject*)-1);

    //                        // Clear existing overrides
    //               /*         memory::write<uobject*>(component +
    //               offsets::montage_effect_override_offset, dummy_finisher);
    //                        memory::write<uobject*>(component +
    //                        offsets::montage_effect_override_context_offset,
    //                        nullptr);*/

    //                        memory::write<uobject*>(component +
    //                        offsets::montage_effect_override_offset, nullptr);
    //                        memory::write<uobject*>(component +
    //                        offsets::montage_effect_override_context_offset,
    //                        nullptr);

    //                        // Set new finisher
    //                        memory::write<uobject*>(component +
    //                        offsets::montage_effect_override_offset,
    //                        dummy_finisher); memory::write<uobject*>(component +
    //                        offsets::montage_effect_override_context_offset,
    //                        local_pawn_context);

    //                        PlayFinisherEffect(component); // btw it's not
    //                        crashing just freezing so it's a func
    //                        };

    //                    // Check weapon type and apply finisher
    //                    if (weapon_name.find("AssaultRifle_AK_C") !=
    //                    std::string::npos) {
    //                        apply_finisher();
    //                    }
    //                    else if (weapon_name.find("AssaultRifle_ACR_C") !=
    //                    std::string::npos) {
    //                        apply_finisher();
    //                    }
    //                    else if (weapon_name.find("BoltSniper_C") !=
    //                    std::string::npos) {
    //                        apply_finisher();
    //                    }
    //                    else if (weapon_name.find("AssaultRifle_Burst_C") !=
    //                    std::string::npos) {
    //                        apply_finisher();
    //                    }
    //                    else if (weapon_name.find("AutomaticPistol_C") !=
    //                    std::string::npos) {
    //                        apply_finisher();
    //                    }
    //                    else if (weapon_name.find("DMR_C") != std::string::npos) {
    //                        apply_finisher();
    //                    }
    //                    else if (weapon_name.find("RevolverPistol_C") !=
    //                    std::string::npos) {
    //                        apply_finisher();
    //                    }
    //                    else if (weapon_name.find("LugerPistol_C") !=
    //                    std::string::npos) {
    //                        apply_finisher();
    //                    }
    //                    else if (weapon_name.find("SubMachineGun_MP5_C") !=
    //                    std::string::npos) {
    //                        apply_finisher();
    //                    }
    //                    else if (weapon_name.find("BasePistol_C") !=
    //                    std::string::npos) {
    //                        apply_finisher();
    //                    }
    //                    else if (weapon_name.find("LeverSniperRifle_C") !=
    //                    std::string::npos) {
    //                        apply_finisher();
    //                    }
    //                    else if (weapon_name.find("DS_Gun_C") !=
    //                    std::string::npos) {
    //                        apply_finisher();
    //                    }
    //                    else if (weapon_name.find("Ability_Melee_Base_C") !=
    //                    std::string::npos) {
    //                        memory::write<uobject*>(component +
    //                        offsets::montage_effect_override_offset, nullptr);
    //                        memory::write<uobject*>(component +
    //                        offsets::montage_effect_override_context_offset,
    //                        nullptr);
    //                    }
    //                }
    //            }
    //        }
    //    }
    //    catch (...) {
    //        // Silent catch
    //    }

    //    return oHkDeath(shooter_character, a2);
    //}

    static inline uobject* GetExponentialHeightFogClass() {
        static uobject* cls = nullptr;
        if (!cls)
            cls = uobject::find_object<uobject*>(
                crypt(L"Engine.ExponentialHeightFog").decrypt());
        return cls;
    }

    static std::unordered_map<uobject*, std::string> objectNameCache;
    inline std::string get_cached_name(uobject* obj) {
        auto it = objectNameCache.find(obj);
        if (it != objectNameCache.end())
            return it->second;
        std::string name = system::get_object_name(obj).ToString();
        objectNameCache[obj] = name;
        return name;
    }
    static const std::pair<const char*, const char*> kWeaponToFamily[] = {
        {"AssaultRifle_AK_C", "AssaultRifle_AK"},
        {"AssaultRifle_ACR_C", "AssaultRifle_ACR"},
        {"BoltSniper_C", "BoltSniper"},
        {"AssaultRifle_Burst_C", "AssaultRifle_Burst"},
        {"AutomaticPistol_C", "AutomaticPistol"},
        {"DMR_C", "DMR"},
        {"RevolverPistol_C", "Revolver"},
        {"LugerPistol_C", "LugerPistol"},
        {"SubMachineGun_MP5_C", "SubMachineGun_MP5"},
        {"Vector_C", "SubMachineGun_Vector"},
        {"BasePistol_C", "BasePistol"},
        {"LeverSniperRifle_C", "LeverSniper"},
        {"DS_Gun_C", "DS_Gun"},
        {"Ability_Melee_Base_C", "Melee"},
        {"HeavyMachineGun_C", "HeavyMachineGun"},
        {"LightMachineGun_C", "LightMachineGun"},
        {"SawedOffShotgun_C", "SawedOffShotgun"},
        {"AutomaticShotgun_C", "AutomaticShotgun"},
        {"PumpShotgun_C", "PumpShotgun"},
    };
    struct SkinItem {
        std::wstring name;
    };
    static std::unordered_map<std::string, std::vector<SkinItem>> g_byFamily;
    static std::unordered_map<std::string, int> g_selectedIndexForFamily;
    std::wstring get_chosen_skin(const std::string& weapon_name) {

        std::string family;
        for (const auto& [key, fam] : kWeaponToFamily) {
            if (weapon_name == key) {
                family = fam;
                break;
            }
        }

        if (family.empty()) {

            return L"";
        }

        auto it = g_byFamily.find(family);
        if (it == g_byFamily.end()) {
            return L"";
        }

        int index = g_selectedIndexForFamily[family];
        auto& skins = it->second;

        if (index < 0 || index >= static_cast<int>(skins.size())) {

            return L"";
        }

        return skins[index].name;
    }
    static std::string family_from_logged_name(const std::wstring& wname) {
        std::string s(wname.begin(), wname.end());

        const std::string pre = "Default__";
        const std::string suf = "_PrimaryAsset_C";
        if (s.rfind(pre, 0) == 0)
            s.erase(0, pre.size());
        if (s.size() >= suf.size() &&
            s.compare(s.size() - suf.size(), suf.size(), suf) == 0)
            s.erase(s.size() - suf.size());

        if (s.rfind("AK_", 0) == 0)
            return "AssaultRifle_AK";
        if (s.rfind("Melee_", 0) == 0)
            return "Melee";
        if (s.rfind("Vector_", 0) == 0)
            return "SubMachineGun_Vector";
        if (s.rfind("Luger_", 0) == 0)
            return "LugerPistol";

        auto u1 = s.find('_');
        if (u1 == std::string::npos)
            return s;
        auto u2 = s.find('_', u1 + 1);
        return (u2 == std::string::npos) ? s.substr(0, u1) : s.substr(0, u2);
    }
    static void store_skin_by_name(const std::wstring& fullName) {
        std::string fam = family_from_logged_name(fullName);
        auto& vec = g_byFamily[fam];

        if (std::none_of(vec.begin(), vec.end(),
            [&](const SkinItem& it) { return it.name == fullName; })) {
            vec.push_back(SkinItem{ fullName });

            if (vec.size() == 1) {
                g_selectedIndexForFamily[fam] = 0;
            }
        }
    }
    static std::unordered_map<equippable_skin_data_asset*, std::wstring>
        g_skinNameCache;
    static const std::wstring& get_skin_name_cached(equippable_skin_data_asset* p,
        bool refresh = false) {
        static const std::wstring kEmpty;
        if (!p)
            return kEmpty;

        if (!refresh) {
            auto it = g_skinNameCache.find(p);
            if (it != g_skinNameCache.end())
                return it->second;
        }

        // Query once, then copy into a stable std::wstring
        fstring f = system::get_object_name(p);
        auto [it, _] = g_skinNameCache.emplace(p, std::wstring(f.c_str()));
        if (!_)
            it->second.assign(f.c_str()); // if already existed & refresh==true
        return it->second;
    }
    std::string normalize_weapon_class(const std::string& weapon) {
        size_t pos = weapon.find_last_of('_');
        if (pos != std::string::npos && pos + 1 < weapon.size() &&
            std::all_of(weapon.begin() + pos + 1, weapon.end(), ::isdigit)) {
            return weapon.substr(0, pos);
        }
        return weapon;
    }



    void hk_death(ashootercharacter* shooter_character, UDamageResponse* a2) {
        try {
            printf("[DEATH] hk_death called! shooter=0x%p a2=0x%p\n",
                (void*)shooter_character, (void*)a2);

            if (!shooter_character ||
                !memory::IsValidPointer((uintptr_t)shooter_character)) {
                printf("[DEATH] shooter_character invalid, passthrough\n");
                return oHkDeath(shooter_character, a2);
            }

            acknowledgedpawn* pawn = controllers->get_acknowledged_pawn();
            ashootercharacter* character_context = (ashootercharacter*)character;
            acknowledgedpawn* local_pawn_context = (acknowledgedpawn*)pawn;
            auto damage_response = a2;

            printf(
                "[DEATH] character_context=0x%p local_pawn=0x%p damage_response=0x%p\n",
                (void*)character_context, (void*)local_pawn_context,
                (void*)damage_response);

            if (!character_context || !local_pawn_context || !damage_response) {
                printf("[DEATH] FAIL: one of context/pawn/dmg is null\n");
                return oHkDeath(shooter_character, a2);
            }

            if (!memory::IsValidPointer((uintptr_t)character_context) ||
                !memory::IsValidPointer((uintptr_t)local_pawn_context) ||
                !memory::IsValidPointer((uintptr_t)damage_response)) {
                printf("[DEATH] FAIL: pointer validation failed\n");
                return oHkDeath(shooter_character, a2);
            }

            auto component = (uintptr_t)memory::read<uobject*>(
                (uintptr_t)shooter_character +
                offsets::death_reaction_component_offset);
            printf("[DEATH] component=0x%p (offset=0x%X)\n", (void*)component,
                (int)offsets::death_reaction_component_offset);

            if (!component || !memory::IsValidPointer(component)) {
                printf("[DEATH] FAIL: component null/invalid\n");
                return oHkDeath(shooter_character, a2);
            }

            BYTE b1 = memory::read<BYTE>(component + 0x15A);
            BYTE b2 = memory::read<BYTE>(component + 0x168);
            printf("[DEATH] b1=0x%X b2=0x%X | condition=(b1==0 || b2==1) = %d\n", b1,
                b2, (int)(b1 == 0 || b2 == 1));

            if (!(b1 == 0 || b2 == 1)) {
                printf("[DEATH] FAIL: b1/b2 condition not met\n");
                return oHkDeath(shooter_character, a2);
            }

            auto killer = damage_response->get_damage_causer();
            auto equippable = damage_response->get_equippable_used();
            printf("[DEATH] killer=0x%p local_pawn=0x%p equippable=0x%p\n",
                (void*)killer, (void*)local_pawn_context, (void*)equippable);
            printf("[DEATH] killer==local_pawn? %d\n",
                (int)(killer == local_pawn_context));

            if (!killer || !equippable || !memory::IsValidPointer((uintptr_t)killer) ||
                !memory::IsValidPointer((uintptr_t)equippable)) {
                printf("[DEATH] FAIL: killer or equippable null/invalid\n");
                return oHkDeath(shooter_character, a2);
            }

            if (!UWorldSave || !memory::IsValidPointer((uintptr_t)UWorldSave)) {
                printf("[DEATH] FAIL: UWorldSave null/invalid\n");
                return oHkDeath(shooter_character, a2);
            }

            tarray<ashootercharacter*> enemies =
                blueprints::find_all_shooters_with_alliance(
                    UWorldSave, character, earesalliance::enemy, false, true);
            printf("[DEATH] enemies.count=%d\n", enemies.count);

            myweapon = character->get_inventory()->get_current_equippable();
            printf("[DEATH] myweapon=0x%p\n", (void*)myweapon);


        }
        catch (...) {
            printf("[DEATH] EXCEPTION caught\n");
        }

        return oHkDeath(shooter_character, a2);
    }

    namespace kismentsystemlibrary {
        static bool line_trace_single(uworld* world_context_object, fvector start,
            fvector end, ETraceTypeQuery trace_channel,
            bool b_trace_complex,
            tarray<AActor*> actors_to_ignore,
            EDrawDebugTrace draw_debug_type,
            FHitResult& out_hit, bool b_ignore_self,
            flinearcolor trace_color,
            flinearcolor trace_hit_color, float draw_time) {
            static uobject* function = nullptr;
            if (!function)
                function = uobject::find_object<uobject*>(
                    L"Engine.KismetSystemLibrary.LineTraceSingle");
            if (!function)
                return false;

            struct {
                uworld* world_context_object;
                fvector start;
                fvector end;
                ETraceTypeQuery trace_channel;
                bool b_trace_complex;
                tarray<AActor*> actors_to_ignore;
                char draw_debug_type;
                FHitResult out_hit;
                bool b_ignore_self;
                flinearcolor trace_color;
                flinearcolor trace_hit_color;
                float draw_time;
                bool return_value;
            } params;

            params.world_context_object = world_context_object;
            params.start = start;
            params.end = end;
            params.trace_channel = trace_channel;
            params.b_trace_complex = b_trace_complex;
            params.actors_to_ignore = actors_to_ignore;
            params.draw_debug_type = draw_debug_type;
            params.b_ignore_self = b_ignore_self;
            params.trace_color = trace_color;
            params.trace_hit_color = trace_hit_color;
            params.draw_time = draw_time;

            world_context_object->process_event(function, &params);
            out_hit = params.out_hit;

            return params.return_value;
        }
    } // namespace kismentsystemlibrary

    inline uworld* GetWorldSafe() {
        uintptr_t base = memory::module_base;
        if (!base) return nullptr;
        
        uintptr_t state_ptr = base + offsets::State;
        if (!memory::IsValidPointer(state_ptr)) return nullptr;
        
        uintptr_t* uworld_state_ptr = *(uintptr_t**)state_ptr;
        if (!uworld_state_ptr || !memory::IsValidPointer((uintptr_t)uworld_state_ptr)) return nullptr;
        
        return *(uworld**)uworld_state_ptr;
    }

    namespace ShooterGameBlueprints {
        static uintptr_t GetAresGlobals() {
            static uobject* Function = nullptr;
            if (!Function) {
                Function = uobject::find_object<uobject*>(
                    L"ShooterGame.ShooterBlueprintLibrary.GetAresGlobals");
            }
            if (!Function)
                return 0;

            static uobject* DefaultObj = nullptr;
            if (!DefaultObj) {
                DefaultObj = uobject::find_object<uobject*>(
                    L"ShooterGame.Default__ShooterBlueprintLibrary");
            }
            if (!DefaultObj)
                return 0;

            struct {
                uintptr_t ReturnValue;
            } params = { 0 };

            DefaultObj->process_event(Function, &params);
            return params.ReturnValue;
        }

        static void GetWallPenetrationSpans(uworld* World, const fvector& Start,
            const fvector& End,
            const tarray<AActor*>& IgnoreActors,
            ECollisionChannel TraceChannel,
            float IgnoreGapTolerance,
            FWallSpanList& OutWallSpans) {
            static uobject* Function = nullptr;
            if (!Function) {
                Function = uobject::find_object<uobject*>(
                    L"ShooterGame.ShooterBlueprintLibrary.GetWallPenetrationSpans");
            }

            if (!Function || !World) {
                return;
            }

            struct {
                uworld* World;
                fvector Start;
                fvector End;
                tarray<AActor*> IgnoreActors;
                ECollisionChannel TraceChannel;
                float IgnoreGapTolerance;
                FWallSpanList OutWallSpans;
            } params;

            params.World = World;
            params.Start = Start;
            params.End = End;
            params.IgnoreActors = IgnoreActors;
            params.TraceChannel = TraceChannel;
            params.IgnoreGapTolerance = IgnoreGapTolerance;

            World->process_event(Function, &params);
            OutWallSpans = params.OutWallSpans;
        }

        static uint8_t ConvertToAresSurfaceType(uint8_t SurfaceType) {
            static uobject* Function = nullptr;
            if (!Function) {
                Function = uobject::find_object<uobject*>(
                    L"ShooterGame.ShooterBlueprintLibrary.ConvertToAresSurfaceType");
            }
            if (!Function)
                return 0;

            static uobject* DefaultObj = nullptr;
            if (!DefaultObj) {
                DefaultObj = uobject::find_object<uobject*>(
                    L"ShooterGame.Default__ShooterBlueprintLibrary");
            }
            if (!DefaultObj)
                return 0;

            struct {
                uint8_t SurfaceType;
                uint8_t ReturnValue;
            } params;

            params.SurfaceType = SurfaceType;
            DefaultObj->process_event(Function, &params);
            return params.ReturnValue;
        }
    } // namespace ShooterGameBlueprints

    class BoneHelper {
    public:
        static int32_t GetBonePriorityByIndex(int32_t bi, int32_t bc) {
            switch (bc) {
            case 101:
                if (bi == 20)
                    return 100;
                if (bi == 21)
                    return 90;
                if (bi >= 17 && bi <= 19)
                    return 80;
                if (bi >= 15 && bi <= 16)
                    return 70;
                if (bi >= 13 && bi <= 14)
                    return 60;
                if (bi == 3)
                    return 50;
                if (bi >= 23 && bi <= 25)
                    return 30;
                if (bi >= 49 && bi <= 51)
                    return 30;
                if (bi >= 75 && bi <= 78)
                    return 25;
                if (bi >= 82 && bi <= 85)
                    return 25;
                return 10;
            case 103:
                if (bi == 8)
                    return 100;
                if (bi == 9)
                    return 90;
                if (bi >= 5 && bi <= 7)
                    return 80;
                if (bi == 3)
                    return 50;
                if (bi >= 30 && bi <= 33)
                    return 30;
                if (bi >= 55 && bi <= 58)
                    return 30;
                if (bi >= 63 && bi <= 69)
                    return 25;
                if (bi >= 77 && bi <= 83)
                    return 25;
                return 10;
            case 104:
                if (bi == 20)
                    return 100;
                if (bi == 21)
                    return 90;
                if (bi >= 17 && bi <= 19)
                    return 80;
                if (bi >= 15 && bi <= 16)
                    return 70;
                if (bi >= 13 && bi <= 14)
                    return 60;
                if (bi == 3)
                    return 50;
                if (bi >= 23 && bi <= 25)
                    return 30;
                if (bi >= 49 && bi <= 51)
                    return 30;
                if (bi >= 77 && bi <= 80)
                    return 25;
                if (bi >= 84 && bi <= 87)
                    return 25;
                return 10;
            default:
                if (bi <= 10)
                    return 80;
                if (bi <= 20)
                    return 60;
                if (bi <= 30)
                    return 40;
                return 20;
            }
        }

        static inline void GetCriticalBones(int32_t bc, int32_t* out, int32_t& cnt) {
            if (bc == 101 || bc == 104) {
                static const int32_t b[] = { 20, 21, 19, 18, 17, 3 };
                memcpy(out, b, sizeof(b));
                cnt = 6;
            }
            else if (bc == 103) {
                static const int32_t b[] = { 8, 9, 7, 6, 5, 3 };
                memcpy(out, b, sizeof(b));
                cnt = 6;
            }
            else
                cnt = 0;
        }
    };






    //////////////////AUTOWALL SYSTEM BY NATİVES///////////////////
    struct BulletData {
        float Damage;
        float PenetrationPower;
        bool CanPenetrate;
    };

    static BulletData GetBulletData(ashootercharacter* shooter) {
        BulletData def = { 150.0f, 1.50f, true };
        if (!shooter) return def;

        auto inv = shooter->get_inventory();
        if (!inv) return def;

        auto eq = inv->get_current_equippable();
        if (!eq) return def;

        fstring weapon_name = system::get_object_name(eq);
        if (!weapon_name.c_str()) return def;

        std::wstring wname = weapon_name.c_str();

        if (wname.find(L"Operator") != std::wstring::npos) {
            def.Damage = 255.0f; def.PenetrationPower = 3.50f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Outlaw") != std::wstring::npos) {
            def.Damage = 238.0f; def.PenetrationPower = 3.00f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Marshal") != std::wstring::npos) {
            def.Damage = 202.0f; def.PenetrationPower = 2.80f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Guardian") != std::wstring::npos) {
            def.Damage = 195.0f; def.PenetrationPower = 2.50f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Vandal") != std::wstring::npos) {
            def.Damage = 160.0f; def.PenetrationPower = 2.20f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Phantom") != std::wstring::npos) {
            def.Damage = 140.0f; def.PenetrationPower = 2.10f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Sheriff") != std::wstring::npos) {
            def.Damage = 159.0f; def.PenetrationPower = 1.80f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Ghost") != std::wstring::npos) {
            def.Damage = 105.0f; def.PenetrationPower = 1.30f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Spectre") != std::wstring::npos) {
            def.Damage = 78.0f; def.PenetrationPower = 1.10f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Stinger") != std::wstring::npos) {
            def.Damage = 67.0f; def.PenetrationPower = 0.90f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Odin") != std::wstring::npos) {
            def.Damage = 95.0f; def.PenetrationPower = 2.00f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Ares") != std::wstring::npos) {
            def.Damage = 72.0f; def.PenetrationPower = 1.70f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Bulldog") != std::wstring::npos) {
            def.Damage = 115.0f; def.PenetrationPower = 1.70f; def.CanPenetrate = true; return def;
        }
        if (wname.find(L"Headhunter") != std::wstring::npos) {
            def.Damage = 159.0f; def.PenetrationPower = 1.50f; def.CanPenetrate = true; return def;
        }

        if (wname.find(L"Bucky") != std::wstring::npos || wname.find(L"Judge") != std::wstring::npos ||
            wname.find(L"Shorty") != std::wstring::npos || wname.find(L"Classic") != std::wstring::npos ||
            wname.find(L"Frenzy") != std::wstring::npos) {
            def.Damage = 50.0f; def.PenetrationPower = 0.40f; def.CanPenetrate = true; return def;
        }

        return def;
    }

    class TraceHelper {
    public:
        static bool CanShootThrough(aplayercontroller* controller,
            ashootercharacter* shooter_char,
            ashootercharacter* target_enemy,
            int aim_bone = 8) {

            if (!controller || !shooter_char || !target_enemy) return false;

            BulletData bullet = GetBulletData(shooter_char);
            if (!bullet.CanPenetrate) return false;

            if (!memory::IsValidPointer((uintptr_t)controller) ||
                !memory::IsValidPointer((uintptr_t)shooter_char) ||
                !memory::IsValidPointer((uintptr_t)target_enemy)) return false;

            if (!UWorldSave || !memory::IsValidPointer((uintptr_t)UWorldSave)) return false;

            uskeletalmeshcomponent* enemy_mesh = target_enemy->get_mesh();
            if (!enemy_mesh || !memory::IsValidPointer((uintptr_t)enemy_mesh)) return false;

            auto camMgr = controller->get_camera_manager();
            if (!camMgr || !memory::IsValidPointer((uintptr_t)camMgr)) return false;
            fvector camera_loc = camMgr->get_camera_location();

            int traceBone = (aim_bone == 0) ? 8 : aim_bone;
            fvector target_bone = GetBoneMatrix(enemy_mesh, traceBone);

            tarray<AActor*> ignore_actors;
            ignore_actors.Add((AActor*)shooter_char);

            FWallSpanList wall_spans;
            memset(&wall_spans, 0, sizeof(FWallSpanList));

            ShooterGameBlueprints::GetWallPenetrationSpans(
                UWorldSave, camera_loc, target_bone, ignore_actors,
                ECollisionChannel::ECC_Visibility, 0.0f, wall_spans);
            if (wall_spans.Spans.count <= 0 || !wall_spans.Spans.data) {
                return true;
            }

            if (!memory::IsValidPointer((uintptr_t)wall_spans.Spans.data)) return false;

            float remaining_damage = bullet.Damage;
            const float MIN_DAMAGE = 35.0f;
            int walls_hit = 0;

            uint8_t* spans_bytes = (uint8_t*)wall_spans.Spans.data;

            for (int i = 0; i < wall_spans.Spans.count; i++) {
                if (i >= 8 || walls_hit >= 4) break;

                uint8_t* span = spans_bytes + (i * 0x1E0);
                if (!memory::IsValidPointer((uintptr_t)span)) break;

                FHitResult* entrance_hr = (FHitResult*)(span + 0x0);
                FHitResult* exit_hr = (FHitResult*)(span + 0xF0);

                if (!memory::IsValidPointer((uintptr_t)entrance_hr) ||
                    !memory::IsValidPointer((uintptr_t)exit_hr)) break;

                fvector entrance_loc = entrance_hr->Location;
                fvector exit_loc = exit_hr->Location;
                if (exit_loc.x == 0.0f && exit_loc.y == 0.0f && exit_loc.z == 0.0f) {
                    return false;
                }

                float dx = exit_loc.x - entrance_loc.x;
                float dy = exit_loc.y - entrance_loc.y;
                float dz = exit_loc.z - entrance_loc.z;
                float thickness = sqrtf(dx * dx + dy * dy + dz * dz);

                if (thickness < 0.1f) continue;
                float maxThickness = bullet.PenetrationPower * 48.0f;
                if (thickness > maxThickness) {
                    return false;
                }

                walls_hit++;
                float damageLoss = thickness * 1.0f;
                remaining_damage -= damageLoss;

                if (remaining_damage < MIN_DAMAGE) {
                    return false;
                }
            }

            return remaining_damage >= MIN_DAMAGE;
        }
    };


    static UParticleSystem* g_HellFireParticles[2] = { nullptr, nullptr };
    static bool g_HellFireParticlesLoaded = false;
    static bool g_HellFireAttached = false;
    static ashootercharacter* g_LastHellFireCharacter = nullptr;

    void LoadHellFireParticles() {
        if (g_HellFireParticlesLoaded)
            return;
        g_HellFireParticlesLoaded = true;

        const wchar_t* paths[] = {
            L"/Game/Equippables/Finishers/Hellfire/VFX/"
            L"Finisher_Hellfire_Debris_ENV_Chroma.Finisher_Hellfire_Debris_ENV_"
            L"Chroma",
            L"/Game/Equippables/Finishers/Hellfire/VFX/"
            L"Finisher_Hellfire_Debris_ENV.Finisher_Hellfire_Debris_ENV",
        };

        for (int i = 0; i < 2; i++) {
            g_HellFireParticles[i] = reinterpret_cast<UParticleSystem*>(
                uobject::static_load_object(nullptr, nullptr, paths[i]));
        }
    }

    void ResetHellFire() {
        g_HellFireAttached = false;
        g_LastHellFireCharacter = nullptr;
    }

    void AttachHellFireToPlayer(ashootercharacter* target_character) {
        if (!target_character || !memory::IsValidPointer((uintptr_t)target_character))
            return;
        if (g_HellFireAttached && g_LastHellFireCharacter == target_character)
            return;

        LoadHellFireParticles();

        srand((unsigned int)GetTickCount64());

        int maxEffects = 12;

        for (int i = 0; i < maxEffects; i++) {
            float angle = ((float)rand() / RAND_MAX) * 2.0f * 3.14159265f;
            float dist = 600.0f + ((float)rand() / RAND_MAX) * 3000.0f;

            fvector relativePos;
            relativePos.x = cos(angle) * dist;
            relativePos.y = sin(angle) * dist;
            relativePos.z = -50.0f + ((float)rand() / RAND_MAX) * 200.0f;

            int particleType = rand() % 2;
            if (!g_HellFireParticles[particleType])
                continue;

            float randomScale = 1.5f + ((float)rand() / RAND_MAX) * 2.5f;

            auto rootComp = target_character->K2_GetRootComponent();
            if (!rootComp || !memory::IsValidPointer((uintptr_t)rootComp))
                continue;

            GameplayStatics::SpawnEmitterAttached(
                g_HellFireParticles[particleType], rootComp, fname{}, relativePos,
                FRotator{ 0.f, 0.f, 0.f }, fvector(randomScale, randomScale, randomScale),
                EAttachLocation::KeepRelativeOffset, true, EPSCPoolMethod::None, true,
                false, 0.0f, EAresParticleVariantColor::AresVariantBaseColor);
        }

        g_HellFireAttached = true;
        g_LastHellFireCharacter = target_character;
    }

    namespace NoSmoke {
        static std::vector<AGameObject*> cachedSmokes;
        static double lastSmokeUpdate = 0.0;

        static const std::vector<std::string> smoke_identifiers = {
            "SmokeGrenade", "ZedAbility_Smoke", "GrenadeSmoke",
            "SmokeScreen",  "AbilitySmoke",     "Brimstone_Smoke",
            "Viper_Smoke",  "Omen_Smoke",       "Harbor_Smoke" };

        void RemoveSmokes(uworld* world) {
            if (!globals::misc::no_smoke)
                return;
            if (!world || !memory::IsValidPointer((uintptr_t)world))
                return;

            double currentTime = GameplayStatics::GetTimeSeconds((uobject*)world);
            if (currentTime < 0.0 || currentTime > 1000000.0)
                return;

            if (currentTime - lastSmokeUpdate > 0.5) {
                cachedSmokes.clear();

                tarray<AGameObject*> Objects;
                GameplayStatics::GetAllActorsOfClass2(world, Class::Actors(), &Objects);

                int32_t objectCount = Objects.Num();
                if (objectCount <= 0 || objectCount > 10000)
                    return;

                for (int32_t index = 0; index < objectCount; index++) {
                    if (!Objects.IsValidIndex(index))
                        continue;

                    AGameObject* Object = Objects[index];
                    if (!Object || !memory::IsValidPointer((uintptr_t)Object))
                        continue;

                    std::string ObjectName =
                        system::get_object_name((uobject*)Object).to_str();
                    if (ObjectName.empty())
                        continue;

                    char firstChar = ObjectName[0];
                    if (firstChar != 'S' && firstChar != 'Z' && firstChar != 'G' &&
                        firstChar != 'B' && firstChar != 'V' && firstChar != 'O' &&
                        firstChar != 'H')
                        continue;

                    for (const auto& identifier : smoke_identifiers) {
                        if (ObjectName.find(identifier) != std::string::npos) {
                            cachedSmokes.push_back(Object);
                            break;
                        }
                    }

                    if (cachedSmokes.size() >= 50)
                        break;
                }

                lastSmokeUpdate = currentTime;
            }

            for (auto it = cachedSmokes.begin(); it != cachedSmokes.end();) {
                AGameObject* smoke = *it;
                if (!smoke || !memory::IsValidPointer((uintptr_t)smoke)) {
                    it = cachedSmokes.erase(it);
                    continue;
                }
                smoke->SetActorHiddenInGame(true);
                smoke->SetActorEnableCollision(false);
                ++it;
            }
        }
    } // namespace NoSmoke

    static AGameObject* CachedSkyDome = nullptr;
    static bool SkyDomeCached = false;
    static AGameObject* SkyDome = nullptr;

    void SkyBoxMesh() {
        if (!SkyDome || !memory::IsValidPointer((uintptr_t)SkyDome))
            return;

        UPrimitiveComponent* mesh = memory::read<UPrimitiveComponent*>(
            (uintptr_t)SkyDome + offsets::skymeshcomponent);
        if (!mesh || !memory::IsValidPointer((uintptr_t)mesh))
            return;

        fname first_name = string::string_to_name(L"Horizon color");
        fname second_name = string::string_to_name(L"Zenith Color");
        fname third_name = string::string_to_name(L"Overall Color");
        fname cloud_color = string::string_to_name(L"Cloud Color");
        fname cloud_speed = string::string_to_name(L"Cloud Speed");
        fname Stars_Brightness = string::string_to_name(L"Stars Brightness");
        fname cloud_op = string::string_to_name(L"Cloud Opacity");
        fname noise_power2 = string::string_to_name(L"NoisePower2");
        fname noise_power1 = string::string_to_name(L"NoisePower1");
        fname sun_radius = string::string_to_name(L"Sun Radius");
        fname horizon_falloff = string::string_to_name(L"Horizon Falloff");
        fname sun_brightness = string::string_to_name(L"Sun Brightness");
        fname sun_height = string::string_to_name(L"Sun Height");
        fname sun_color = string::string_to_name(L"Sun Color");

        auto matPath =
            L"/Engine/EngineSky/M_Sky_Panning_Clouds2.M_Sky_Panning_Clouds2";

        uobject* material = uobject::find_object<uobject*>(matPath);
        if (!material)
            uobject::static_load_object(nullptr, nullptr, matPath);
        material = uobject::find_object<uobject*>(matPath);
        if (!material || !memory::IsValidPointer((uintptr_t)material))
            return;

        static uobject* dynMat = nullptr;
        static AGameObject* prevSkyDomePtr = nullptr;
        // SkyDome degistiyse cache'i sifirla
        if (SkyDome != prevSkyDomePtr) {
            dynMat = nullptr;
            prevSkyDomePtr = SkyDome;
        }
        if (!dynMat) {
            mesh->set_material(0, material);
            dynMat = mesh->create_and_set_material_instance_dynamic_from_material(
                0, material);
        }

        if (dynMat && memory::IsValidPointer((uintptr_t)dynMat)) {
            auto num_materials = mesh->get_num_materials();
            for (int i = 0; i < num_materials; i++) {
                uobject* mid =
                    mesh->create_and_set_material_instance_dynamic_from_material(
                        i, material);
                if (!mid)
                    continue;

                auto mat = mid->cast<UMaterialInstanceDynamic>();
                if (!mat)
                    continue;

                float amplified_cloud_speed = globals::misc::CloudSpeed * 100000000000.0f;
                globals::misc::Overall.r = globals::misc::SkySharedR;
                globals::misc::Overall.g = globals::misc::SkySharedG;
                globals::misc::Overall.b = globals::misc::SkySharedB;
                globals::misc::Horizon.r = globals::misc::SkySharedR;
                globals::misc::Horizon.g = globals::misc::SkySharedG;
                globals::misc::Horizon.b = globals::misc::SkySharedB;

                float amplified_cloud_opacity =
                    globals::misc::CloudOpacity * globals::misc::CloudOpacity1;

                mat->set_vector_parameter_value1(first_name, { globals::misc::Overall.r,
                                                              globals::misc::Overall.g,
                                                              globals::misc::Overall.b });
                mat->set_vector_parameter_value1(second_name, { globals::misc::Zenith.r,
                                                               globals::misc::Zenith.g,
                                                               globals::misc::Zenith.b });
                mat->set_vector_parameter_value1(third_name, { globals::misc::Horizon.r,
                                                              globals::misc::Horizon.g,
                                                              globals::misc::Horizon.b });
                mat->set_vector_parameter_value1(cloud_color, { globals::misc::Cloud.r,
                                                               globals::misc::Cloud.g,
                                                               globals::misc::Cloud.b });
                mat->set_vector_parameter_value1(sun_color,
                    { globals::misc::SkySunColor.r,
                     globals::misc::SkySunColor.g,
                     globals::misc::SkySunColor.b });
                mat->set_scalar_parameter_value1(cloud_speed, amplified_cloud_speed);
                mat->set_scalar_parameter_value1(Stars_Brightness,
                    globals::misc::StarsBrightness);
                mat->set_scalar_parameter_value1(cloud_op, amplified_cloud_opacity);
                mat->set_scalar_parameter_value1(noise_power2,
                    globals::misc::SkyNoisePower2);
                mat->set_scalar_parameter_value1(noise_power1,
                    globals::misc::SkyNoisePower1);
                mat->set_scalar_parameter_value1(sun_radius, globals::misc::SkySunRadius);
                mat->set_scalar_parameter_value1(horizon_falloff,
                    globals::misc::SkyHorizonFalloff);
                mat->set_scalar_parameter_value1(sun_brightness,
                    globals::misc::SkySunBrightness);
                mat->set_scalar_parameter_value1(sun_height, globals::misc::SkySunHeight);
            }
        }

        if (globals::misc::skyboxrgb) {
            static float rainbowTime = 0.0f;
            rainbowTime += 0.004f;
            flinearcolor rainbow = GetRainbowColor(rainbowTime);

            auto num_materials = mesh->get_num_materials();
            for (int i = 0; i < num_materials; i++) {
                uobject* mid =
                    mesh->create_and_set_material_instance_dynamic_from_material(
                        i, material);
                if (!mid)
                    continue;

                auto mat = mid->cast<UMaterialInstanceDynamic>();
                if (!mat)
                    continue;

                mat->set_vector_parameter_value1(first_name,
                    { rainbow.r, rainbow.g, rainbow.b });
                mat->set_vector_parameter_value1(second_name,
                    { rainbow.r, rainbow.g, rainbow.b });
                mat->set_vector_parameter_value1(third_name,
                    { rainbow.r, rainbow.g, rainbow.b });
                mat->set_vector_parameter_value1(cloud_color,
                    { rainbow.r, rainbow.g, rainbow.b });
            }
        }
    }

    void hk_draw_transition(ugameviewportclient* viewportclient, ucanvas* canvas_,
        std::uintptr_t a3) {
        if (!canvas) {
            canvas = uobject::find_object<ucanvas*>(
                L"/Engine/Transient.DebugCanvasObject", (uobject*)-1);
        }

        if (!canvas)
            (hk_draw_transition)(viewportclient, canvas, a3);

        int target_id = -1;
        bool unlock_skin = false;
        bool skins_updated = false;
        double closest_distance = DBL_MAX;

        do {
            uworld* world = reinterpret_cast<uworld*>(viewportclient->get_world());
            UWorldSave = world;
            if (!world)
                continue;

            PreCacheAllVisuals();

            controllers = blueprints::get_player_controller(world);
            if (!controllers)
                continue;

            if (globals::misc::damage_numbers)
                RenderDamageNumbers(canvas, controllers);

            heltra::Menu(canvas);

            if (globals::misc::sk1n_chang3r) {
                skin_changer::unlock_all_skins(world);
            }

            aplayercameramanager* camera = controllers->get_camera_manager();
            if (!camera)
                continue;

            pawn = controllers->get_acknowledged_pawn();
            if (!pawn)
                continue;

            character = controllers->get_shooter_character();
            if (!character) {
                lastweapon = nullptr;
                continue;
            }

            uskeletalmeshcomponent* mesh3p = character->mesh3p();
            if (!mesh3p)
                continue;

            if (globals::misc::fovchanger) {
                controllers->set_fov(globals::misc::fovchangur);
            }
            camera_cache = camera;

            if (pawn != nullptr) {

                if (character->is_alive()) {
                    auto* inv_safe = character->get_inventory();
                    myweapon = inv_safe ? inv_safe->get_current_equippable() : nullptr;
                }
                else {
                    myweapon = nullptr;
                    lastweapon = nullptr;
                }

                if (globals::misc::sk1n_chang3r &&
                    myweapon != nullptr && myweapon != lastweapon) {

                    uinventory* inventory = character->get_inventory();
                    if (inventory) {

                        currentequippable* equippable = inventory->get_current_equippable();
                        if (equippable) {

                            equippable_skin_data_asset* skin_data_asset = equippable->get_skin_data_asset();
                            if (skin_data_asset) {

                                int32_t type = skin_data_asset->get_type();
                                // type 0 = default skin (Classic, yerden alınan) → ATLA
                                if (type == 0) {
                                    lastweapon = myweapon;
                                    continue;
                                }

                                arsenal_view_controller* arsenal_view_controller =
                                    ares_instance::get_ares_client_game_instance(world)
                                    ->get_aresnal_view_controller();
                                if (arsenal_view_controller) {

                                    arsenal_view_model* arsenal_view_model =
                                        arsenal_view_controller->get_view_model();
                                    if (arsenal_view_model) {

                                        auto models = arsenal_view_model->get_gun_models();
                                        if (models.count > 0 && models.data && memory::IsValidPointer((uintptr_t)models.data)) {
                                            for (int i = 0; i < models.count && i < 65; i++) {

                                                equippable_inventory_model* model = models[i];
                                                if (!model || !memory::IsValidPointer((uintptr_t)model))
                                                    continue;

                                                equippable_skin_inventory_model* skin_model =
                                                    model->get_equipped_skin_model();
                                                if (!skin_model || !memory::IsValidPointer((uintptr_t)skin_model))
                                                    continue;

                                                equippable_skin_data_asset* skin_data =
                                                    skin_model->get_skin_data_asset();
                                                if (!skin_data || !memory::IsValidPointer((uintptr_t)skin_data))
                                                    continue;
                                                if (skin_data->get_type() != type)
                                                    continue;

                                                auto skin_levels = skin_data->get_skin_levels();
                                                int max_level = (skin_levels.size() > 0) ? skin_levels.size() : 1;

                                                auto* chroma_model = skin_model->get_skin_inventory_chroma_asset();
                                                if (!chroma_model || !memory::IsValidPointer((uintptr_t)chroma_model))
                                                    continue;

                                                uobject* skin_chroma_asset = chroma_model->get_skin_chroma_data_asset();
                                                if (!skin_chroma_asset || !memory::IsValidPointer((uintptr_t)skin_chroma_asset))
                                                    continue;

                                                skin_changer::unlock_all_apply(
                                                    world, equippable, skin_data, skin_chroma_asset,
                                                    max_level, nullptr, -1);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    lastweapon = myweapon;
                }
            }

            fvector2d screen_size = canvas->get_screen_size();
            if (!screen_size.is_valid())
                continue;

            screen_center_x = (double)canvas->get_screen_size().x / 2.f;
            screen_center_y = (double)canvas->get_screen_size().y / 2.f;

            drawings::draw_f0v({ screen_center_x, screen_center_y },
                globals::aimbot::a1m_f0v, 100.0f, heltra::fovcolor,
                canvas);

            if (globals::misc::sk1ptut0rial) {
                controllers->disconnect_server();
                globals::misc::sk1ptut0rial = false;
            }

            fvector2d pos = { (screen_width / 2.0) - 500, (screen_height / 2.0) - 475 };

            tarray<ashootercharacter*> actors =
                blueprints::find_all_shooters_with_alliance(
                    world, character, earesalliance::enemy, false, false);

            if (!character || !controllers) {
                continue;
            }

            bool f1_currently_pressed = (GetAsyncKeyState(VK_F1) & 0x8000) != 0;
            if (f1_currently_pressed && !globals::misc::f1_key_pressed_last_frame) {
                globals::misc::SpinBot = !globals::misc::SpinBot;
            }
            globals::misc::f1_key_pressed_last_frame = f1_currently_pressed;

            bool g_currently_pressed = (GetAsyncKeyState('H') & 0x8000) != 0;
            if (g_currently_pressed && !globals::misc::f2_key_pressed_last_frame) {
                globals::misc::tperson = !globals::misc::tperson;
            }
            globals::misc::f2_key_pressed_last_frame = g_currently_pressed;

            if (globals::misc::customhand && character->is_alive()) {
                if (auto handmesh = character->GetOverlayMesh1P()) {
                    apply_custom_hand_texture(pawn, character, world);
                    globals::misc::customhand = false;
                }
            }

            if (camera_engine != uintptr_t(camera)) {
                camera_engine = uintptr_t(camera);
                should_hook_gay = true;
            }
            if (!camera_engine)
                return;

            if (globals::misc::tperson) {
                character->Set3pMeshVisible(true);
            }
            else {
                character->Set3pMeshVisible(false);
            }

            if (globals::misc::fastcrouch) {
                if (character) {
                    character->SetCrouchTimeOverride(0.001f);
                    globals::misc::meshmofiedfastcrouch = true;
                }
            }
            else if (character) {
                if (globals::misc::meshmofiedfastcrouch) {
                    character->SetCrouchTimeOverride(1.0f);
                    globals::misc::meshmofiedfastcrouch = false;
                }
            }

            if (globals::misc::HandWire) {
                if (auto hand = character->GetOverlayMesh1P()) {
                    if (memory::IsValidPointer((uintptr_t)hand)) {
                        uintptr_t addr = (uintptr_t)hand;
                        *(uint8_t*)(addr + 0x906) |= (1 << 5);
                        *(uint8_t*)(addr + 0xC0) = 0xFF;
                    }
                }
                if (auto mesh1p = character->getmesh1p()) {
                    if (memory::IsValidPointer((uintptr_t)mesh1p)) {
                        uintptr_t addr = (uintptr_t)mesh1p;
                        *(uint8_t*)(addr + 0x906) |= (1 << 5);
                        *(uint8_t*)(addr + 0xC0) = 0xFF;
                    }
                }
                // Silah mesh'i de ekle
                if (auto inventory = character->get_inventory()) {
                    if (auto weapon = inventory->get_current_equippable()) {
                        if (auto gunMesh = weapon->GetMesh1P()) {
                            if (memory::IsValidPointer((uintptr_t)gunMesh)) {
                                uintptr_t addr = (uintptr_t)gunMesh;
                                *(uint8_t*)(addr + 0x906) |= (1 << 5);
                                *(uint8_t*)(addr + 0xC0) = 0xFF;
                            }
                        }
                    }
                }
            }



            if (globals::visuals::partyhat_self && character->is_alive()) {
                auto my_mesh_3p = character->mesh3p();
                if (my_mesh_3p) {
                    drawings::partyhat(controllers, my_mesh_3p, canvas);
                }
            }



            static uintptr_t last_applied_weapon_ptr = 0;
            static bool is_processing_model = false;
            static std::wstring last_processed_weapon_type = L"";
            static uintptr_t last_character_ptr = 0;
            static int model_load_counter = 0;

            static uintptr_t saved_vandal_ptr = 0;
            static uintptr_t saved_phantom_ptr = 0;
            static uintptr_t saved_ghost_ptr = 0;
            static uintptr_t saved_frenzy_ptr = 0;
            static uintptr_t saved_melee_ptr = 0;

            static int vandal_cycle_index = 0;
            static int phantom_cycle_index = 0;
            static int ghost_cycle_index = 0;
            static int frenzy_cycle_index = 0;

            // Weapon name cache (round geçişinde sıfırlanır)
            static uintptr_t cachedWNamePtr = 0;
            static std::wstring cachedWName = L"";
            static uintptr_t lastHiddenWeaponPtr = 0;
            static uintptr_t cached_nospread_ptr = 0;
            static std::wstring cached_nospread_name = L"";
            static uintptr_t cached_aim_wep_ptr = 0;
            static std::wstring cached_aim_wep_name = L"";
            // Visibility is enforced every frame — no separate hide-cache needed

            // Maps weapon ptr -> ProcMesh ptr
            static std::map<uintptr_t, uskeletalmeshcomponent*> ProcessedWeapons;
            static uintptr_t lastVisibilityWeaponPtr = 0;

            // Round gecisi tespiti
            static bool was_alive_last_frame = false;
            bool is_alive_now = character && character->is_alive();
            bool round_just_started = (!was_alive_last_frame && is_alive_now);
            bool round_just_ended = (was_alive_last_frame && !is_alive_now);
            was_alive_last_frame = is_alive_now;

            // Blackout sayaci: round gecisinden sonra N frame boyunca skin sistemini durdur.
            // Bu sayede UE4 actor temizligi tamamlanmadan pointer erisimi olmaz -> crash yok.
            static int skin_blackout_frames = 0;
            if (round_just_started || round_just_ended) {
                skin_blackout_frames = 90; // ~1.5 saniye @ 60fps — yeterince guvenli
                g_pendingMeshJobs.clear();
                last_applied_weapon_ptr = 0;
                last_processed_weapon_type = L"";
                is_processing_model = false;
                lastVisibilityWeaponPtr = 0;
                cachedWNamePtr = 0; cachedWName = L"";
                lastHiddenWeaponPtr = 0;
                // NOT: TextureCache ve ProcessedWeapons KASITLI olarak temizlenmiyor.
                // Texture ve mesh verileri round'lar arasi yasayabilir. Bu hem FPS
                // kasmasi hem de crash'i onler: her round basinda yeniden disk IO yok.
            }
            if (skin_blackout_frames > 0) {
                --skin_blackout_frames;
                goto skip_all_skin; // Blackout surecinde hicbir skin kodu calismasin
            }

            // UWorld degisti (map change) -> gercek tam temizlik yap
            if (UWorldSave != LastWorldPtr) {
                TextureCache.clear();
                ProcessedWeapons.clear();
                g_pendingMeshJobs.clear();
                last_applied_weapon_ptr = 0;
                last_processed_weapon_type = L"";
                is_processing_model = false;
                saved_vandal_ptr = 0; saved_phantom_ptr = 0;
                saved_ghost_ptr = 0;  saved_frenzy_ptr = 0; saved_melee_ptr = 0;
                model_load_counter = 0;
                cachedWNamePtr = 0; cachedWName = L"";
                lastHiddenWeaponPtr = 0;
                lastVisibilityWeaponPtr = 0;
                ModelsLoadedToRAM = false;
                LastWorldPtr = UWorldSave;
                last_character_ptr = character ? (uintptr_t)character : 0;
            }

            // skin_needs_reload: sadece ptr/kuyruk sifirla, texture/mesh cache koru
            if (globals::misc::skin_needs_reload) {
                g_pendingMeshJobs.clear();
                last_applied_weapon_ptr = 0;
                last_processed_weapon_type = L"";
                is_processing_model = false;
                lastVisibilityWeaponPtr = 0;
                lastHiddenWeaponPtr = 0;
                globals::misc::skin_needs_reload = false;
            }

            if ((globals::misc::custom_vandal_enabled || globals::misc::custom_classic_enabled || globals::misc::custom_knife_enabled) && character) {

                // Character degistiyse tracking'i sifirla
                if ((uintptr_t)character != last_character_ptr) {
                    last_applied_weapon_ptr = 0;
                    last_processed_weapon_type = L"";
                    is_processing_model = false;
                    saved_vandal_ptr = 0; saved_phantom_ptr = 0;
                    saved_ghost_ptr = 0;  saved_frenzy_ptr = 0; saved_melee_ptr = 0;
                    last_character_ptr = (uintptr_t)character;
                    model_load_counter = 0;
                }

                // --- HIZLI GUVENLIK KONTROLU ---
                // is_alive ve IsValidUObject sadece character ptr degisince cagrilir.
                // Her frame VirtualQuery/process_event yerine cached flag kullan.
                static uintptr_t blk1_cached_char_ptr = 0;
                static bool      blk1_char_valid = false;
                static uinventory* blk1_inv = nullptr;

                if ((uintptr_t)character != blk1_cached_char_ptr) {
                    blk1_cached_char_ptr = (uintptr_t)character;
                    // Yeni character: bir kez dogrula ve inventory'yi cache'le
                    blk1_char_valid = (controllers && character->is_alive() &&
                        memory::IsValidPointer((uintptr_t)character) &&
                        IsValidUObject((uobject*)character));
                    if (blk1_char_valid) {
                        blk1_inv = character->get_inventory();
                        if (!blk1_inv || !memory::IsValidPointer((uintptr_t)blk1_inv) ||
                            !IsValidUObject((uobject*)blk1_inv)) {
                            blk1_char_valid = false;
                            blk1_inv = nullptr;
                        }
                    }
                    else {
                        blk1_inv = nullptr;
                    }
                }

                if (!blk1_char_valid || !blk1_inv) {
                    last_applied_weapon_ptr = 0;
                    last_processed_weapon_type = L"";
                    is_processing_model = false;
                    last_character_ptr = (uintptr_t)character;
                    goto skip_mesh;
                }

                {
                    // get_current_equippable her frame (silah degisimini yakalamaliyiz)
                    auto weapon = blk1_inv->get_current_equippable();
                    if (weapon && !is_processing_model) {
                        uintptr_t wPtr = (uintptr_t)weapon;

                        // Weapon ptr range check (cheap, no VirtualQuery)
                        if (wPtr < 0x10000 || wPtr > 0x7FFFFFFFFFFF) {
                            last_applied_weapon_ptr = 0;
                            goto skip_mesh;
                        }

                        // weapon name: sadece ptr degisince guncelle (process_event tasarrufu)
                        static uintptr_t blk1_cached_wptr = 0;
                        static std::wstring blk1_wname = L"";
                        if (wPtr != blk1_cached_wptr) {
                            if (memory::IsValidPointer(wPtr) && IsValidUObject((uobject*)weapon)) {
                                fstring obj_name = system::get_object_name(weapon);
                                fstring converted_name = helper::convert_weapon_name(obj_name);
                                blk1_wname = converted_name.wide();
                                blk1_cached_wptr = wPtr;
                            }
                            else {
                                last_applied_weapon_ptr = 0;
                                goto skip_mesh;
                            }
                        }

                        const std::wstring& wName = blk1_wname;

                        bool is_valid_weapon = (wName == L"Vandal" || wName == L"Phantom" || wName == L"Ghost" || wName == L"Frenzy" ||
                            wName == L"Bulldog" || wName == L"Guardian" || wName == L"Sheriff" || wName == L"Spectre" ||
                            wName == L"Stinger" || wName == L"Bucky" || wName == L"Judge" || wName == L"Marshal" ||
                            wName == L"Operator" || wName == L"Ares" || wName == L"Odin" || wName == L"Classic" ||
                            wName == L"Melee" || wName == L"Shorty" || wName == L"Outlaw");

                        if (!is_valid_weapon) {
                            last_applied_weapon_ptr = wPtr;
                            last_processed_weapon_type = wName;
                            last_character_ptr = (uintptr_t)character;
                            goto skip_mesh;
                        }

                        bool should_process = false;

                        if (wPtr != last_applied_weapon_ptr) {
                            if (last_applied_weapon_ptr != 0)
                                model_load_counter = 0;

                            if (wName == L"Vandal") {
                                vandal_cycle_index = 1;
                                saved_vandal_ptr = wPtr;
                            }
                            else if (wName == L"Phantom") {
                                if (saved_phantom_ptr != 0 && saved_phantom_ptr != wPtr)
                                    phantom_cycle_index = (phantom_cycle_index + 1) % 3;
                                saved_phantom_ptr = wPtr;
                            }
                            else if (wName == L"Ghost") {
                                if (saved_ghost_ptr != 0 && saved_ghost_ptr != wPtr)
                                    ghost_cycle_index = (ghost_cycle_index + 1) % 1;
                                saved_ghost_ptr = wPtr;
                            }
                            else if (wName == L"Frenzy") {
                                if (saved_frenzy_ptr != 0 && saved_frenzy_ptr != wPtr)
                                    frenzy_cycle_index = (frenzy_cycle_index + 1) % 1;
                                saved_frenzy_ptr = wPtr;
                            }
                            else if (wName == L"Melee") {
                                saved_melee_ptr = wPtr;
                            }

                            should_process = true;
                        }
                        else if (wName != last_processed_weapon_type)
                            should_process = true;

                        if (should_process && ProcessedWeapons.count(wPtr)) {
                            should_process = false;
                            last_applied_weapon_ptr = wPtr;
                            last_processed_weapon_type = wName;
                            last_character_ptr = (uintptr_t)character;
                        }

                        // Fast path: weapon zaten ProcMesh'e sahip mi? (sadece should_process=true iken)
                        if (should_process) {
                            // Fast path: weapon zaten ProcMesh'e sahip mi? SEH-korumalı SafeFindProcMesh kullan
                            uskeletalmeshcomponent* existingPM = SafeFindProcMesh(weapon);
                            if (existingPM) {
                                ProcessedWeapons[wPtr] = existingPM;
                                last_applied_weapon_ptr = wPtr;
                                last_processed_weapon_type = wName;
                                last_character_ptr = (uintptr_t)character;
                                should_process = false;
                            }
                        }

                        if (should_process) {
                            last_applied_weapon_ptr = wPtr;
                            last_processed_weapon_type = wName;
                            last_character_ptr = (uintptr_t)character;
                            is_processing_model = false;

                            std::string  b = GetPublicPath();
                            std::wstring wb(b.begin(), b.end());

                            PendingMeshJob job;
                            job.weapon = weapon;
                            job.framesLeft = 3;
                            bool queued = true;

                            if (wName == L"Vandal") {
                                int s = vandal_cycle_index;
                                if (s == 1) { job.objPath = b + "vandal_skin1.obj";job.texPath = wb + L"vandal_skin1_tex.png"; }
                                else if (s == 2) { job.objPath = b + "vandal_skin3.obj";job.texPath = wb + L"vandal_skin3_tex.png"; }
                                else if (s == 3) { job.objPath = b + "vandal_skin4.obj";job.texPath = wb + L"vandal_skin4_tex.png"; }
                                else if (s == 4) { job.objPath = b + "vandal_skin5.obj";job.texPath = wb + L"vandal_skin5_tex.png"; }
                                else if (s == 5) { job.objPath = b + "vandal_skin6.obj";job.texPath = wb + L"vandal_skin6_tex.png"; }
                                else { job.objPath = b + "vandal.obj";       job.texPath = wb + L"vandal_tex.png"; }
                            }
                            else if (wName == L"Phantom") { job.objPath = b + "phantom.obj"; job.texPath = wb + L"phantom_tex.png"; }
                            else if (wName == L"Ghost") { job.objPath = b + "ghost.obj";   job.texPath = wb + L"ghost.png"; }
                            else if (wName == L"Frenzy") { job.objPath = b + "frenzy.obj";  job.texPath = wb + L"frenzy_tex.png"; }
                            else if (wName == L"Bulldog") { job.objPath = b + "bulldog.obj"; job.texPath = wb + L"bulldog_tex.png"; }
                            else if (wName == L"Guardian") { job.objPath = b + "guardian.obj";job.texPath = wb + L"guardian_tex.png"; }
                            else if (wName == L"Sheriff") { job.objPath = b + "sheriff.obj"; job.texPath = wb + L"sheriff_tex.png"; }
                            else if (wName == L"Spectre") { job.objPath = b + "spectre.obj"; job.texPath = wb + L"spectre.png"; }
                            else if (wName == L"Stinger") { job.objPath = b + "stinger.obj"; job.texPath = wb + L"stinger_tex.png"; }
                            else if (wName == L"Bucky") { job.objPath = b + "bucky.obj";   job.texPath = wb + L"bucky_tex.png"; }
                            else if (wName == L"Judge") { job.objPath = b + "judge.obj";   job.texPath = wb + L"judge_tex.png"; }
                            else if (wName == L"Marshal") { job.objPath = b + "marshal.obj"; job.texPath = wb + L"marshal_tex.png"; }
                            else if (wName == L"Operator") { job.objPath = b + "operator.obj";job.texPath = wb + L"operator_tex.png"; }
                            else if (wName == L"Ares") { job.objPath = b + "ares.obj";    job.texPath = wb + L"ares_tex.png"; }
                            else if (wName == L"Odin") { job.objPath = b + "odin.obj";    job.texPath = wb + L"odin_tex.png"; }
                            else if (wName == L"Classic") { job.objPath = b + "classic.obj"; job.texPath = wb + L"classic.png"; }
                            else if (wName == L"Melee" && (globals::misc::custom_vandal_enabled || globals::misc::custom_classic_enabled))
                            {
                                job.objPath = b + "knife.obj"; job.texPath = wb + L"knife.png";
                            }
                            else if (wName == L"Shorty") { job.objPath = b + "shorty.obj";  job.texPath = wb + L"shorty_tex.png"; }
                            else { queued = false; }

                            if (queued && !job.objPath.empty()) {
                                bool replaced = false;
                                for (auto& pj : g_pendingMeshJobs) {
                                    if (pj.weapon == weapon) { pj = job; replaced = true; break; }
                                }
                                if (!replaced)
                                    g_pendingMeshJobs.push_back(job);
                            }
                        }

                    }
                }
            }
        skip_mesh:;


            // ── Pending mesh job processor ────────────────────────────────────────────
            // Her frame: gecersiz isleri temizle, framesLeft'i azalt, hazir olani isle.
            // En fazla 1 is islenir — game thread bloke olmaz.
            if (!g_pendingMeshJobs.empty() &&
                (globals::misc::custom_vandal_enabled || globals::misc::custom_classic_enabled || globals::misc::custom_knife_enabled)) {

                // Gecersiz silah ptr'li isleri kaldir
                g_pendingMeshJobs.erase(
                    std::remove_if(g_pendingMeshJobs.begin(), g_pendingMeshJobs.end(),
                        [](const PendingMeshJob& j) {
                            return !j.weapon || !memory::IsValidPointer((uintptr_t)j.weapon);
                        }),
                    g_pendingMeshJobs.end());

                // framesLeft azalt — hazir olani isle
                bool did_one = false;
                for (auto& job : g_pendingMeshJobs) {
                    if (did_one) break;
                    if (job.framesLeft > 0) { --job.framesLeft; continue; }

                    // framesLeft == 0: simdi isle — SEH wrapper ile korunmali
                    if (!IsValidUObject((uobject*)job.weapon)) { job.framesLeft = -1; continue; }
                    SafeReplaceMesh(job.weapon, job.objPath.c_str(), job.texPath.c_str());

                    // ProcessedWeapons guncelle
                    uintptr_t wPtr2 = (uintptr_t)job.weapon;
                    uskeletalmeshcomponent* pm2 = SafeFindProcMesh(job.weapon);
                    ProcessedWeapons[wPtr2] = pm2;
                    job.framesLeft = -1; // tamamlandi
                    did_one = true;
                }

                // Tamamlananlari listeden cikar
                g_pendingMeshJobs.erase(
                    std::remove_if(g_pendingMeshJobs.begin(), g_pendingMeshJobs.end(),
                        [](const PendingMeshJob& j) { return j.framesLeft < 0; }),
                    g_pendingMeshJobs.end());
            }
            // ─────────────────────────────────────────────────────────────────────────


            // Block 2: Apply ProceduralMesh transform using ProcessedWeapons map (no
            // dangling ptr)
            if ((globals::misc::custom_vandal_enabled || globals::misc::custom_classic_enabled || globals::misc::custom_knife_enabled) && character && controllers) {
                auto inv = character->get_inventory();
                if (inv) {
                    auto weapon = inv->get_current_equippable();
                    if (weapon && memory::IsValidPointer((uintptr_t)weapon) &&
                        IsValidUObject((uobject*)weapon)) {
                        uintptr_t curWPtr = (uintptr_t)weapon;

                        // Weapon name cache
                        if (curWPtr != cachedWNamePtr) {
                            fstring obj_name = system::get_object_name(weapon);
                            fstring converted_name = helper::convert_weapon_name(obj_name);
                            cachedWName = converted_name.wide();
                            cachedWNamePtr = curWPtr;
                        }
                        const std::wstring& wName = cachedWName;

                        bool is_valid_weapon_b2 = (wName == L"Vandal" || wName == L"Phantom" || wName == L"Ghost" || wName == L"Frenzy" ||
                            wName == L"Bulldog" || wName == L"Guardian" || wName == L"Sheriff" || wName == L"Spectre" ||
                            wName == L"Stinger" || wName == L"Bucky" || wName == L"Judge" || wName == L"Marshal" ||
                            wName == L"Operator" || wName == L"Ares" || wName == L"Odin" || wName == L"Classic" ||
                            wName == L"Melee" || wName == L"Shorty" || wName == L"Outlaw");

                        // OBJ yuklu olsun olmasın: Vandal ise orijinal mesh DAIMA gizle
                        if (is_valid_weapon_b2 && wName != L"Spectre") {
                            if (curWPtr != lastHiddenWeaponPtr) {
                                auto* origMesh1P = weapon->GetMesh1P();
                                if (origMesh1P && memory::IsValidPointer((uintptr_t)origMesh1P)) {
                                    SetComponentVisibility((USceneComponent*)origMesh1P, false, true);
                                }
                                auto* meshOverlay = memory::read<uskeletalmeshcomponent*>(
                                    (uintptr_t)weapon + offsets::mesh1p_overlay);
                                if (meshOverlay && memory::IsValidPointer((uintptr_t)meshOverlay)) {
                                    SetComponentVisibility((USceneComponent*)meshOverlay, false, true);
                                }
                                auto* meshGun = memory::read<uskeletalmeshcomponent*>(
                                    (uintptr_t)weapon + offsets::mesh1pgun);
                                if (meshGun && memory::IsValidPointer((uintptr_t)meshGun)) {
                                    SetComponentVisibility((USceneComponent*)meshGun, false, true);
                                }
                                auto* CosM = memory::read<uskeletalmeshcomponent*>(
                                    (uintptr_t)weapon + 0x1188);
                                if (CosM && memory::IsValidPointer((uintptr_t)CosM)) {
                                    SetComponentVisibility((USceneComponent*)CosM, false, true);
                                }
                                lastHiddenWeaponPtr = curWPtr;
                            }
                        }

                        // ProceduralMesh transform + visibility
                        auto it = ProcessedWeapons.find(curWPtr);
                        if (it != ProcessedWeapons.end() && it->second &&
                            memory::IsValidPointer((uintptr_t)it->second)) {

                            auto* pm = it->second;

                            if (wName == L"Spectre") {
                                pm->SetRelativeScale3D(fvector(1.5f, 1.5f, 1.5f));
                                USceneComponentHelpers::SetRelativeRotation(
                                    pm, FRotator{ 0.0f, 90.0f, -90.0f });
                                USceneComponentHelpers::SetRelativeLocation(
                                    pm, fvector(-0.9434f, 0.943392f, -2.83019f));
                            }
                            else if (wName == L"Classic") {
                                pm->SetRelativeScale3D(fvector(0.0343f, 0.0343f, 0.0267f));
                                USceneComponentHelpers::SetRelativeRotation(
                                    pm, FRotator{ 4.8f, 96.0f, -96.0f });
                                USceneComponentHelpers::SetRelativeLocation(
                                    pm, fvector(-9.667f, 0.000f, -4.333f));
                                SetComponentVisibility((USceneComponent*)pm, true, true);
                            }
                            else if (wName == L"Melee") {
                                pm->SetRelativeScale3D(fvector(0.0063f, 0.0050f, 0.0037f));
                                USceneComponentHelpers::SetRelativeRotation(
                                    pm, FRotator{ 67.2f, -21.6f, -153.6f });
                                USceneComponentHelpers::SetRelativeLocation(
                                    pm, fvector(8.667f, 8.133f, 11.867f));
                                SetComponentVisibility((USceneComponent*)pm, true, true);
                            }
                            else {
                                pm->SetRelativeScale3D(fvector(0.0677f, 0.0314f, 0.0267f));
                                USceneComponentHelpers::SetRelativeRotation(
                                    pm, FRotator{ 2.4f, 41.4f, -92.6f });
                                USceneComponentHelpers::SetRelativeLocation(
                                    pm, fvector(11.667f, 45.000f, 23.000f));
                                SetComponentVisibility((USceneComponent*)pm, true, true);
                            }
                        }
                    }
                }
            }


            static uintptr_t lastProcessedTextWeapon = 0;
            static std::wstring lastProcessedTextType = L"";

        skip_all_skin:;

            if (globals::misc::custom_text_enabled && character && controllers) {
                auto inv = character->get_inventory();
                if (inv) {
                    auto weapon = inv->get_current_equippable();
                    if (weapon) {
                        fstring obj_name = system::get_object_name(weapon);
                        fstring converted_name = helper::convert_weapon_name(obj_name);
                        std::wstring wName = converted_name.wide();

                        if (wName == L"Vandal" || wName == L"Frenzy" || wName == L"Ghost" ||
                            wName == L"Melee" || wName == L"Phantom" || wName == L"Spectre") {
                            uintptr_t weaponPtr = (uintptr_t)weapon;

                            if (lastProcessedTextWeapon != 0 &&
                                lastProcessedTextWeapon != weaponPtr) {
                                if (WeaponTextMeshMap.count(lastProcessedTextWeapon)) {
                                    auto* oldMesh = WeaponTextMeshMap[lastProcessedTextWeapon];
                                    if (oldMesh && memory::IsValidPointer((uintptr_t)oldMesh)) {
                                        static uobject* DestroyFunc = uobject::find_object<uobject*>(
                                            L"Engine.Actor.DestroyComponent");
                                        if (DestroyFunc) {
                                            struct {
                                                UActorComponent* Component;
                                            } Args = { (UActorComponent*)oldMesh };

                                            ((uobject*)oldMesh)->process_event(DestroyFunc, &Args);
                                        }
                                        WeaponTextMeshMap.erase(lastProcessedTextWeapon);
                                    }
                                }
                            }

                            lastProcessedTextWeapon = weaponPtr;
                            lastProcessedTextType = wName;

                            if (WeaponTextMeshMap.count(weaponPtr) &&
                                WeaponTextMeshMap[weaponPtr]) {
                                TextMesh = WeaponTextMeshMap[weaponPtr];

                                if (memory::IsValidPointer((uintptr_t)TextMesh)) {
                                    uskeletalmeshcomponent* TextSkelMesh =
                                        (uskeletalmeshcomponent*)TextMesh;
                                    if (TextSkelMesh) {
                                        bool isVandalSkin4 =
                                            (wName == L"Vandal" && vandal_cycle_index == 3);
                                        if (isVandalSkin4) {
                                            TextSkelMesh->SetRelativeScale3D(
                                                fvector(0.909f, 1.484f, 1.371f));
                                            USceneComponentHelpers::SetRelativeRotation(
                                                TextSkelMesh, FRotator{ 0.0f, 90.3396f, -88.9811f });
                                            USceneComponentHelpers::SetRelativeLocation(
                                                TextSkelMesh, fvector(0.000f, -1.333f, -2.667f));
                                        }
                                        else {
                                            WeaponTransform transform =
                                                GetTextTransform(wName, vandal_cycle_index);
                                            TextSkelMesh->SetRelativeScale3D(transform.scale);
                                            USceneComponentHelpers::SetRelativeRotation(
                                                TextSkelMesh, FRotator{ transform.rotation.pitch,
                                                                       transform.rotation.yaw,
                                                                       transform.rotation.roll });
                                            USceneComponentHelpers::SetRelativeLocation(
                                                TextSkelMesh, transform.position);
                                        }
                                    }
                                    static uobject* SetVisFunc = uobject::find_object<uobject*>(
                                        L"Engine.SceneComponent.SetVisibility");
                                    if (SetVisFunc) {
                                        struct {
                                            bool bNewVisibility;
                                            bool bPropagateToChildren;
                                        } VisArgs = { true, true };
                                        ((uobject*)TextMesh)->process_event(SetVisFunc, &VisArgs);
                                    }
                                }
                                else {
                                    WeaponTextMeshMap.erase(weaponPtr);
                                    ReplaceTextMeshWith3DModel(
                                        weapon, (GetPublicPath() + "text.obj").c_str());
                                }
                            }
                            else {
                                ReplaceTextMeshWith3DModel(
                                    weapon, (GetPublicPath() + "text.obj").c_str());
                            }
                        }
                    }
                }
            }

            if (globals::misc::bullet_tracers) {
            }

            if (globals::misc::bullet_spawn && character->is_alive()) {
                static DWORD last_shell_tick = 0;
                static DWORD last_fired_time = 0;

                bool is_shooting_now = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0 ||
                    globals::stop_for_auto_shoot;
                if (is_shooting_now)
                    last_fired_time = GetTickCount();

                bool should_eject =
                    is_shooting_now || (GetTickCount() - last_fired_time < 5000);

                if (should_eject && GetTickCount() - last_shell_tick > 50) {
                    if (auto inventory = character->get_inventory()) {
                        if (auto weapon = inventory->get_current_equippable()) {
                            int amount = globals::misc::bullet_spawn_amount > 0
                                ? globals::misc::bullet_spawn_amount
                                : 1;
                            for (int i = 0; i < amount; i++) {
                                weapon->EjectShellCasing();
                            }
                            last_shell_tick = GetTickCount();
                        }
                    }
                }
            }


            if (globals::misc::antiflash) {
                auto test1 = memory::read<UBlindManagerComponent*>(
                    (uintptr_t)character + offsets::BlindManagerComponent);
                use_blind_manager_component(test1);
            }

            if (globals::misc::ViewModelChanger) {
                process_fp_mode(character);
            }

            if (character->is_alive()) {
                apply_local_chams(pawn, character);
                apply_self_chams_3p(character);
            }

            if (globals::misc::customgun) {
                currentequippable* Equippable =
                    character->get_inventory()->get_current_equippable();
                UPrimitiveComponent* GunMesh = memory::read<UPrimitiveComponent*>(
                    uintptr_t(Equippable) + offsets::mesh1pgun);
                if (!GunMesh || !memory::IsValidPointer((uintptr_t)GunMesh))
                    ;

                fstring customTexturePath = fstring(L"C:/gun.jpg");
                uobject* CustomTexture = system::import_file_as_texture2d(world, customTexturePath);
                if (!CustomTexture || !memory::IsValidPointer((uintptr_t)CustomTexture))
                    ;

                auto matPath = L"/Game/Equippables/_Core/Materials/SpecialMaterials/"
                    L"CosmosShader/Winter/Winter_MI.Winter_MI";
                uobject* material = uobject::find_object<uobject*>(matPath);
                if (!material)
                    material = uobject::static_load_object(nullptr, nullptr, matPath);

                if (!material || !memory::IsValidPointer((uintptr_t)material))
                    ;

                GunMesh->set_material(0, material);
                uobject* GunDynamicMat =
                    GunMesh->create_and_set_material_instance_dynamic_from_material(
                        0, material);
                if (!GunDynamicMat || !memory::IsValidPointer((uintptr_t)GunDynamicMat))
                    ;

                auto* mat = GunDynamicMat->cast<UMaterialInstanceDynamic>();
                if (!mat)
                    ;

                fname param1 = string::string_to_name(crypt(L"Image 1").decrypt());
                fname param2 = string::string_to_name(crypt(L"Image 2").decrypt());

                mat->set_texture_parameter_value(param1, CustomTexture);
                mat->set_texture_parameter_value(param2, CustomTexture);

                globals::misc::customgun = false;
            }

            if (globals::misc::skybox) {
                if (!SkyDomeCached || !CachedSkyDome ||
                    !memory::IsValidPointer((uintptr_t)CachedSkyDome)) {
                    tarray<AGameObject*> Objects;
                    GameplayStatics::GetAllActorsOfClass2(world, Class::Actors(), &Objects);

                    for (int i = 0; i < Objects.Num(); i++) {
                        if (!Objects.IsValidIndex(i))
                            continue;

                        AGameObject* Object = Objects[i];
                        if (!Object || !memory::IsValidPointer((uintptr_t)Object))
                            continue;

                        auto name = system::get_object_name((uobject*)Object);
                        if (!name.is_valid())
                            continue;

                        if (name.to_str() == "shared_SkyDomeB_0") {
                            CachedSkyDome = Object;
                            SkyDomeCached = true;
                            break;
                        }
                    }
                }

                if (CachedSkyDome && memory::IsValidPointer((uintptr_t)CachedSkyDome)) {
                    SkyDome = CachedSkyDome;
                    SkyBoxMesh();
                }
            }

            if (globals::misc::Fog)
            {
                static AGameObject* CachedFogActor = nullptr;
                if (!CachedFogActor || !memory::IsValidPointer((uintptr_t)CachedFogActor))
                {
                    CachedFogActor = nullptr;
                    tarray<AGameObject*> Objects;
                    GameplayStatics::GetAllActorsOfClass2(world, GetExponentialHeightFogClass(), &Objects);
                    int32_t count = Objects.Num();
                    if (count > 0 && count < 10000)
                    {
                        for (int32_t i = 0; i < count; i++)
                        {
                            if (!Objects.IsValidIndex(i)) continue;
                            AGameObject* obj = Objects[i];
                            if (!obj || !memory::IsValidPointer((uintptr_t)obj)) continue;
                            CachedFogActor = obj;
                            break;
                        }
                    }
                }

                if (CachedFogActor && memory::IsValidPointer((uintptr_t)CachedFogActor))
                {
                    UExponentialHeightFogComponent* fogComponent =
                        memory::read<UExponentialHeightFogComponent*>((uintptr_t)CachedFogActor + 0x0460);
                    if (fogComponent && memory::IsValidPointer((uintptr_t)fogComponent))
                    {
                        if (globals::misc::FogRGB)
                        {
                            static float fogRainbowTime = 0.0f;
                            fogRainbowTime += 0.004f;
                            flinearcolor rainbow = GetRainbowColor(fogRainbowTime);
                            globals::misc::FogColor = flinearcolor{ rainbow.r, rainbow.g, rainbow.b, 1.0f };
                        }

                        fogComponent->SetFogDensity(globals::misc::FogDensity);
                        fogComponent->SetFogHeightFalloff(globals::misc::FogHeightFalloff);
                        fogComponent->SetFogInscatteringColor(globals::misc::FogColor);
                        fogComponent->SetFogMaxOpacity(globals::misc::FogMaxOpacity);
                        fogComponent->SetStartDistance(globals::misc::FogStartDistance);
                        fogComponent->SetFogCutoffDistance(globals::misc::FogCutoffDistance);
                        fogComponent->SetVolumetricFog(globals::misc::bEnableVolumetricFog);
                        fogComponent->SetVolumetricFogDistance(globals::misc::VolumetricFogDistance);
                    }
                }
            }

            if (globals::misc::BigGun) {
                if (auto get_weapon =
                    character->get_inventory()->get_current_equippable()) {
                    if (auto weapon_mesh_1p = get_weapon->GetMesh1P()) {
                        fvector new_scale =
                            fvector(globals::misc::BigGunFloat, globals::misc::BigGunFloat,
                                globals::misc::BigGunFloat);
                        weapon_mesh_1p->SetRelativeScale3D(new_scale);
                    }
                }
            }

            if (globals::misc::BigSelf) {
                if (auto main_mesh_3p = character->mesh3p()) {
                    fvector new_scale =
                        fvector(globals::misc::BigSelfFloat, globals::misc::BigSelfFloat,
                            globals::misc::BigSelfFloat);
                    main_mesh_3p->SetRelativeScale3D(new_scale);
                }
            }

            if (globals::misc::BigGun3DWireframe) {
                if (auto get_weapon =
                    character->get_inventory()->get_current_equippable()) {
                    if (auto weapon_mesh_3p = get_weapon->GetMesh3P()) {
                        fvector new_scale =
                            fvector(globals::misc::BigGunFloat, globals::misc::BigGunFloat,
                                globals::misc::BigGunFloat);
                        weapon_mesh_3p->SetRelativeScale3D(new_scale);

                        *(char*)(weapon_mesh_3p + 0x8FE) |= (1 << 5);
                        *(char*)(weapon_mesh_3p + 0xc0) = 0xff;
                    }
                }
            }

            if (globals::misc::gun_3p_wireframe && character && character->is_alive()) {
                if (auto inventory = character->get_inventory()) {
                    if (auto weapon = inventory->get_current_equippable()) {
                        if (auto gun_mesh_3p = weapon->GetMesh3P()) {
                            *(char*)(gun_mesh_3p + 0x8FE) =
                                *(char*)(gun_mesh_3p + 0x8FE) | (1 << 5);
                            *(char*)(gun_mesh_3p + 0xc0) = 0xff;
                        }
                    }
                }
            }

            if (globals::misc::bhop) {
                fkey Space;
                Space = fkey{
                    fname{string_utils::string_to_name(crypt(L"SpaceBar").decrypt())} };

                if (character->CanJump()) {
                    if ((GetAsyncKeyState)(VK_SPACE) & 0x8000) {
                        controllers->SimulateInputKey(Space, true);
                        (Sleep)(10);
                        controllers->SimulateInputKey(Space, false);
                    }
                }
            }

            if (globals::misc::hellfire_enabled) {
                if (character && character->is_alive()) {
                    // Reset si nouveau personnage ou nouveau world
                    static uintptr_t last_world_ptr = 0;
                    static uintptr_t last_char_ptr = 0;

                    if ((uintptr_t)world != last_world_ptr ||
                        (uintptr_t)character != last_char_ptr) {
                        ResetHellFire();
                        last_world_ptr = (uintptr_t)world;
                        last_char_ptr = (uintptr_t)character;
                    }

                    if (!memory::IsValidPointer((uintptr_t)character) ||
                        !IsValidUObject((uobject*)character)) {
                        ResetHellFire();
                        goto skip_hellfire;
                    }

                    if (g_LastHellFireCharacter != character)
                        ResetHellFire();

                    AttachHellFireToPlayer(character);
                }
            }
            else {
                if (g_HellFireAttached)
                    ResetHellFire();
            }
        skip_hellfire:;

            if (globals::aimbot::enable_360_fov) {
                float fov_closest = FLT_MAX;
                target_id = -1;

                for (int32_t idx = 0; idx < actors.count; ++idx) {
                    ashootercharacter* actor = actors[idx];
                    if (!actor || !memory::IsValidPointer((uintptr_t)actor))
                        continue;
                    if (actor == character || !actor->is_alive())
                        continue;
                    if (actor->health() == 0)
                        continue;
                    if (!controllers->dormant_server(actor))
                        continue;
                    if (basecomponent::is_ally(actor, character))
                        continue;

                    bool is_visible =
                        !globals::aimbot::v1sh_ch3ck || controllers->line_of_sight(actor);
                    bool can_autowall_360 = false;
                    if (globals::aimbot::auto_wall && !is_visible) {
                        can_autowall_360 = TraceHelper::CanShootThrough(
                            controllers, character, actor, globals::aimbot::a1m_b0ne);
                    }
                    if (!is_visible && !can_autowall_360)
                        continue;

                    fvector actor_pos = actor->k2_get_actor_location();
                    fvector local_pos = character->k2_get_actor_location();
                    float dist = (actor_pos - local_pos).size();

                    if (dist < globals::aimbot::a1m_f0v && dist < fov_closest) {
                        fov_closest = dist;
                        target_id = idx;
                        target_actor = actor;
                    }
                }
            }

            bool hasTarget = false;
            for (int32_t idx = 0; idx < actors.count; ++idx) {
                ashootercharacter* actor = actors[idx];
                if (!actor || actor == character)
                    continue;

                // - S I K K E V E R - Skeleton 
                uskeletalmeshcomponent* mesh = actor->mesh3p();
                if (!mesh || !memory::IsValidPointer((uintptr_t)mesh)) {
                    mesh = actor->GetCosmeticMesh3P();
                }
                if (!mesh || !memory::IsValidPointer((uintptr_t)mesh)) {
                    continue;
                }

                // ── DAMAGE NUMBERS (kill-shot dahil, is_alive'dan önce) ─────────
                if (globals::misc::damage_numbers && idx < 100) {
                    static float prev_hp[100] = {};
                    static bool  hp_init[100] = {};

                    float cur_hp = actor->health();

                    // Her frame kafa 3D konumunu kaydet (actor yaşıyorken)
                    static fvector cached_world[100] = {};
                    if (actor->is_alive()) {
                        fvector head3d = mesh->get_bone_location(8);
                        if (head3d.is_valid())
                            cached_world[idx] = head3d;
                    }

                    if (!hp_init[idx]) {
                        prev_hp[idx] = cur_hp;
                        hp_init[idx] = true;
                    }
                    else {
                        float delta = prev_hp[idx] - cur_hp;
                        if (delta > 0.5f && cached_world[idx].is_valid()) {
                            g_dmg_hue += 47.0f;
                            if (g_dmg_hue >= 360.0f) g_dmg_hue -= 360.0f;

                            DamageNumber dn;
                            dn.world_pos = cached_world[idx]; // 3D dünya konumu
                            dn.damage = delta;
                            dn.alpha = 1.0f;
                            dn.rise_px = 0.0f;
                            dn.color = HueToRGB(g_dmg_hue, 1.0f);
                            dn.is_kill = (cur_hp <= 0.0f);
                            dn.spawn_time = GetTickCount();
                            g_damage_numbers.push_back(dn);
                        }
                        // Respawn tespiti: hp artışı → sıfırla
                        if (cur_hp > prev_hp[idx] + 5.0f) {
                            hp_init[idx] = false;
                            cached_world[idx] = {};
                        }
                        prev_hp[idx] = cur_hp;
                    }
                }
                // ────────────────────────────────────────────────────────────────

                if (!actor->is_alive() || !pawn)
                    continue;

                fvector head_location = mesh->get_bone_location(8);
                if (!head_location.is_valid())
                    continue;

                fvector root_location = mesh->get_bone_location(0);
                if (!root_location.is_valid())
                    continue;

                bool is_visible_engine = controllers->line_of_sight(actor);

                bool bVisible_local =
                    (globals::aimbot::v1sh_ch3ck && is_visible_engine) ||
                    !globals::aimbot::v1sh_ch3ck;
                bool CanAutoWall_local = false;
                if (globals::aimbot::auto_wall && !bVisible_local) {
                    CanAutoWall_local = TraceHelper::CanShootThrough(
                        controllers, character, actor, globals::aimbot::a1m_b0ne);
                }

                bool visible_check_local = bVisible_local || CanAutoWall_local;

                auto head_location_2d =
                    controllers->project_world_to_screen(head_location);
                auto head_location_long_2d = controllers->project_world_to_screen(
                    { head_location.x, head_location.y, head_location.z + 15 });
                auto root_location_2d =
                    controllers->project_world_to_screen(root_location);
                auto head_long_out = controllers->project_world_to_screen(
                    { head_location.x - 10.0, head_location.y, head_location.z + 75 });

                if (!root_location_2d.is_valid() || !head_location_2d.is_valid() ||
                    !head_location_long_2d.is_valid() || !head_long_out.is_valid())
                    continue;

                auto relative_location = actor->k2_get_actor_location();
                auto my_shooter_relative_location = character->k2_get_actor_location();
                auto distance = my_shooter_relative_location.distance(relative_location);
                if (distance <= 0)
                    continue;

                auto [box_width, box_height] =
                    calculate_box_dimensions(head_location_long_2d, root_location_2d);
                if (box_width <= 0 || box_height <= 0)
                    continue;

                double x = head_location_long_2d.x - (box_width / 2),
                    y = head_location_long_2d.y;
                double lineW = (box_width / 7);
                double lineH = (box_height / 7);

                flinearcolor bobbercol;
                flinearcolor boxcolor = defines::Invisible_ESPColor;
                flinearcolor snapcolor = defines::InvisibleSnapColor;
                flinearcolor skeletoncolor = defines::InvisibleSkeletonColor;
                flinearcolor ChamsColor = defines::Invisible;

                if (!controllers->dormant_server(actor))
                    continue;

                if (globals::visuals::vischeck) {
                    if (bVisible_local) {
                        boxcolor = defines::VisibleBox_ESPColor;
                        snapcolor = defines::VisibleSnapColor;
                        skeletoncolor = defines::VisibleSkeletonColor;
                    }
                    else {
                        boxcolor = defines::Invisible_ESPColor;
                        snapcolor = defines::InvisibleSnapColor;
                        skeletoncolor = defines::InvisibleSkeletonColor;
                    }
                }

                if (globals::visuals::h3althbar) {
                    float health = (actor->is_alive() ? actor->health() : 0);
                    float shield = (actor->is_alive() ? actor->shield() : 0);

                    defines::health_color = health >= 75 ? defines::high_health
                        : (health <= 74 && health >= 44)
                        ? defines::normal_health
                        : defines::low_heath;

                    if (health <= 100)
                        drawings::draw_health_and_shield(health, shield, root_location_2d,
                            box_width, box_height, distance,
                            defines::health_color, canvas);
                }


                if (globals::visuals::headb0x) {
                    fvector2d position = { head_location_long_2d.x, head_location_long_2d.y };
                    drawings::head_box(position, lineW, lineH, skeletoncolor, canvas);
                }

                if (globals::visuals::sk3let0n) {
                    draw_skeleton(controllers, mesh, canvas, skeletoncolor);
                }

                if (globals::visuals::b00ms) {
                    fvector2d position1 = { root_location_2d.x,
                                           root_location_2d.y + box_height * 0.12 };
                    drawings::agent_icon(actor, position1, box_height * 0.25, canvas);
                }

                if (globals::visuals::chinahat) {
                    drawings::partyhat(controllers, mesh, canvas);
                }

                flinearcolor BoxColor = defines::Invisible_ESPColor;

                if (globals::visuals::box2d && actor->is_alive()) {
                    if (globals::visuals::vischeck) {
                        if (bVisible_local) {

                            DrawAdaptiveBoundingBox(canvas, controllers, mesh,
                                defines::VisibleBox_ESPColor);
                        }
                        else {

                            DrawAdaptiveBoundingBox(canvas, controllers, mesh,
                                defines::Invisible_ESPColor);
                        }
                    }
                    else {

                        DrawAdaptiveBoundingBox(canvas, controllers, mesh,
                            defines::visuals_color);
                    }
                }

                if (globals::visuals::corner && actor->is_alive()) {
                    if (globals::visuals::vischeck) {
                        if (is_visible_engine) {

                            DrawAdaptiveCornerBox(canvas, controllers, mesh,
                                defines::VisibleBox_ESPColor, ESPThickness);
                        }
                        else {

                            DrawAdaptiveCornerBox(canvas, controllers, mesh,
                                defines::Invisible_ESPColor, ESPThickness);
                        }
                    }
                    else {

                        DrawAdaptiveCornerBox(canvas, controllers, mesh,
                            defines::Invisible_ESPColor, ESPThickness);
                    }
                }

                if (globals::visuals::box3d) {
                    fvector origin = actor->k2_get_actor_location();
                    fvector extent = fvector(40.f, 40.f, 100.f);
                    bool isVisible = is_visible_engine;

                    if (globals::visuals::vischeck) {
                        if (isVisible) {
                            Draw3DBox(canvas, controllers, origin, extent,
                                defines::VisibleBox_ESPColor);
                        }
                        else {
                            Draw3DBox(canvas, controllers, origin, extent,
                                defines::Invisible_ESPColor);
                        }
                    }
                    else {
                        Draw3DBox(canvas, controllers, origin, extent,
                            defines::visuals_color);
                    }
                }








                // ═════════════════════════════════════════════════════════════════════
                // S I K K E V E R - ENEMY CHAMS & WIREFRAME
                // ═════════════════════════════════════════════════════════════════════
                uskeletalmeshcomponent* enemy_main_mesh = actor->get_mesh();
                uskeletalmeshcomponent* enemy_cosmetic_mesh = actor->GetCosmeticMesh3P();

                auto apply_enemy_wire = [&](uskeletalmeshcomponent* t_mesh, bool enable) {
                    if (!t_mesh || !memory::IsValidPointer((uintptr_t)t_mesh)) return;
                    uintptr_t addr = (uintptr_t)t_mesh;
                    if (enable) {
                        *(uint8_t*)(addr + 0x8FE) |= (1 << 5);
                        *(uint8_t*)(addr + 0xC0) = 0xFF;
                    }
                    else {
                        *(uint8_t*)(addr + 0x8FE) &= ~(1 << 5);
                    }
                    };

                if (globals::misc::Wireframe) {
                    apply_enemy_wire(enemy_main_mesh, true);
                    apply_enemy_wire(enemy_cosmetic_mesh, true);
                }
                else {
                    apply_enemy_wire(enemy_main_mesh, false);
                    apply_enemy_wire(enemy_cosmetic_mesh, false);

                    if (globals::chams::enemy_galaxy_enabled) {
                        apply_galaxy_chams(pawn, actor, controllers);
                    }
                    else {
                        if (enemy_main_mesh) actor->reset_character_materials_internal(enemy_main_mesh);
                        if (enemy_cosmetic_mesh) actor->reset_character_materials_internal(enemy_cosmetic_mesh);
                    }
                }

                // ═════════════════════════════════════════════════════════════════════
                // S I K K E V E R - ENEMY OUTLINE
                // ═════════════════════════════════════════════════════════════════════
                if (globals::chams::outline_enabled) {
                    apply_outline_chams(pawn, actor, controllers);
                }
                else {
                    auto set_outline = reinterpret_cast<uskeletalmeshcomponent * (__fastcall*)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode);
                    if (enemy_main_mesh) set_outline(enemy_main_mesh, 0, true);
                    if (enemy_cosmetic_mesh) set_outline(enemy_cosmetic_mesh, 0, true);
                }


                if (globals::visuals::b11ms) {
                    fvector Origin, Extend;
                    fvector2d rel2d, footPos;
                    fvector2d position2 = { head_location_long_2d.x + 5.0f,
                                           head_location_long_2d.y };

                    auto RelativeLocation = actor->k2_get_actor_location();

                    if (controllers->project_world_location_to_screen(
                        { RelativeLocation.x, RelativeLocation.y,
                         RelativeLocation.z + (Extend.z / 2) },
                        footPos, 0)) {
                        if (controllers->project_world_location_to_screen(
                            actor->k2_get_actor_location(), rel2d, true)) {
                            auto CurrentWeapon = static_cast<ashootercharacter*>(actor)
                                ->get_inventory()
                                ->get_current_equippable();
                            if (CurrentWeapon != nullptr) {
                                // Optimized cached weapon string parser
                                static std::map<uintptr_t, std::wstring> enemy_weapon_names;
                                uintptr_t curWepPtr = (uintptr_t)CurrentWeapon;
                                std::wstring weaponNameW;

                                if (enemy_weapon_names.count(curWepPtr) == 0) {
                                    fstring originalWeaponName = system::get_object_name(CurrentWeapon);
                                    std::wstring origW = originalWeaponName.wide();
                                    for (auto& c : origW) c = towlower(c);

                                    if (origW.find(L"ak") != std::wstring::npos) weaponNameW = L"VANDAL";
                                    else if (origW.find(L"dmr") != std::wstring::npos) weaponNameW = L"GUARDIAN";
                                    else if (origW.find(L"phantom") != std::wstring::npos) weaponNameW = L"PHANTOM";
                                    else if (origW.find(L"sheriff") != std::wstring::npos) weaponNameW = L"SHERIFF";
                                    else if (origW.find(L"pistol") != std::wstring::npos) weaponNameW = L"PISTOL";
                                    else if (origW.find(L"shotgun") != std::wstring::npos) weaponNameW = L"SHOTGUN";
                                    else if (origW.find(L"sniper") != std::wstring::npos) weaponNameW = L"SNIPER";
                                    else if (origW.find(L"machinegun") != std::wstring::npos) weaponNameW = L"LMG";
                                    else if (origW.find(L"melee") != std::wstring::npos) weaponNameW = L"KNIFE";
                                    else weaponNameW = L"WEAPON";

                                    enemy_weapon_names[curWepPtr] = weaponNameW;
                                }
                                else {
                                    weaponNameW = enemy_weapon_names[curWepPtr];
                                }

                                if (!weaponNameW.empty()) {
                                    const wchar_t* weaponNameWChar = weaponNameW.c_str();
                                    float adjustedY = footPos.y - (30 * 1.7);

                                    fvector2d position1 = { head_location_long_2d.x + 5.0f,
                                                           head_location_long_2d.y + 25.f };

                                    draw_text(canvas, menu::font, weaponNameWChar, maincolor,
                                        { footPos.x, adjustedY });
                                }
                            }
                        }
                    }
                }

                if (globals::aimbot::silent && !globals::aimbot::auto_shot &&
                    target_id != -1) {
                    ashootercharacter* actor = actors[target_id];
                    if (!actor || actor == character)
                        continue;

                    uskeletalmeshcomponent* mesh = actor->get_mesh();
                    if (!mesh)
                        continue;

                    fvector Target =
                        get_target_bone_matrix(mesh, globals::aimbot::a1m_b0ne);

                    if (!Target.is_valid())
                        continue;

                    if (globals::aimbot::prediction) {
                        // Silent Aim has 0 smoothing delay because the rotation instantly
                        // sets to the target. For hitscan, adding velocity prediction here
                        // will cause misses due to over-leading. The server's lag
                        // compensation will register the hit exactly where we currently see
                        // it.
                    }

                    fvector2d head_screen;
                    if (controllers->project_world_location_to_screen(Target, head_screen,
                        false) &&
                        head_screen.is_valid()) {

                        bool hasTarget = false;

                        auto ProcessSilentWeapon = [&](fstring obj_name) {
                            if (globals::aimbot::silent && second_locked_camera && !hasTarget &&
                                GetAsyncKeyState(globals::aimbot::a1m_k3y) &&
                                is_target_in_fov(screen_center_x, screen_center_y,
                                    head_screen) &&
                                (globals::aimbot::v1sh_ch3ck &&
                                    controllers->line_of_sight(actor) ||
                                    !globals::aimbot::v1sh_ch3ck)) {
                                uintptr_t cmanager = *(uintptr_t*)((uintptr_t)controllers +
                                    offsets::cameramaneger);
                                if (!cmanager || !memory::IsValidPointer(cmanager)) return;
                                fvector CameraPos = *(fvector*)(cmanager + offsets::camerapos);
                                fvector CameraRot = *(fvector*)(cmanager + offsets::camerarot);
                                fvector DeltaRotation;

                                fvector ConvertRotation = {
                                    CameraRot.x < 0.0 ? 360.0 + CameraRot.x : CameraRot.x,
                                    CameraRot.y < 0.0 ? 360.0 + CameraRot.y : CameraRot.y, 0.0 };

                                fvector ControlRotation = controllers->get_control_rotation();

                                fvector Delta = { CameraPos.x - Target.x, CameraPos.y - Target.y,
                                                 CameraPos.z - Target.z };

                                double hyp = sqrt(Delta.x * Delta.x + Delta.y * Delta.y +
                                    Delta.z * Delta.z);

                                const double PI_PRECISE =
                                    3.1415926535897932384626433832795028841971693993751;

                                fvector Rotation = {
                                    acos(Delta.z / hyp) * (180.0 / PI_PRECISE),
                                    atan2(Delta.y, Delta.x) * (180.0 / PI_PRECISE), 0.0 };

                                Rotation.x += 270.0;

                                if (Delta.x >= 0.0)
                                    Rotation.y += 180.0;

                                if (Rotation.y < 0.0)
                                    Rotation.y += 360.0;

                                DeltaRotation.x =
                                    fmod(ConvertRotation.x - ControlRotation.x, 360.0);
                                DeltaRotation.y =
                                    fmod(ConvertRotation.y - ControlRotation.y, 360.0);

                                ConvertRotation.x =
                                    fmod(Rotation.x - DeltaRotation.x - DeltaRotation.x, 360.0);
                                ConvertRotation.y =
                                    fmod(Rotation.y - DeltaRotation.y - DeltaRotation.y, 360.0);

                                if (ConvertRotation.x < 0.0)
                                    ConvertRotation.x = 360.0 + ConvertRotation.x;
                                if (ConvertRotation.y < 0.0)
                                    ConvertRotation.y = 360.0 + ConvertRotation.y;

                                if (globals::aimbot::nospread) {
                                    fvector direction = RotationToVector(ConvertRotation);

                                    auto current_inv = character->get_inventory();
                                    if (current_inv) {
                                        auto current_equip = current_inv->get_current_equippable();
                                        if (current_equip) {
                                            auto firing_state = current_equip->get_firing_state();
                                            if (firing_state) {
                                                fvector spread_angle =
                                                    calc_spread(character, (uintptr_t)firing_state,
                                                        current_equip, direction);

                                                if (spread_angle.size() > 0.001 &&
                                                    spread_angle.is_valid()) {
                                                    ConvertRotation = ConvertRotation - spread_angle;

                                                    ConvertRotation.x =
                                                        fmod(ConvertRotation.x + 360.0, 360.0);
                                                    ConvertRotation.y =
                                                        fmod(ConvertRotation.y + 360.0, 360.0);

                                                    if (ConvertRotation.x < 0.0)
                                                        ConvertRotation.x = 360.0 + ConvertRotation.x;
                                                    if (ConvertRotation.y < 0.0)
                                                        ConvertRotation.y = 360.0 + ConvertRotation.y;
                                                }
                                            }
                                        }
                                    }
                                }

                                if (ConvertRotation.is_valid()) {
                                    controllers->set_control_rotation(ConvertRotation);
                                    hasTarget = true;
                                }
                            }
                            };

                        if (globals::aimbot::nospread && myweapon &&
                            memory::IsValidPointer((uintptr_t)myweapon) &&
                            IsValidUObject((uobject*)myweapon)) {
                            if ((uintptr_t)myweapon != cached_nospread_ptr) {
                                fstring obj_name = helper::convert_weapon_name(system::get_object_name(myweapon));
                                cached_nospread_name = obj_name.wide();
                                cached_nospread_ptr = (uintptr_t)myweapon;
                            }
                            fstring obj_name = fstring(cached_nospread_name.c_str());
                            const std::wstring& name = cached_nospread_name;

                            if (name == L"Bulldog" || name == L"Phantom" || name == L"Vandal" ||
                                name == L"Operator" || name == L"Marshal" ||
                                name == L"Sheriff" || name == L"Spectre" || name == L"Outlaw" ||
                                name == L"Classic" || name == L"Shorty" || name == L"Frenzy" ||
                                name == L"Ghost" || name == L"Stinger" || name == L"Bucky" ||
                                name == L"Judge" || name == L"Guardian" || name == L"Ares" ||
                                name == L"Odin") {

                                ProcessSilentWeapon(obj_name);
                            }
                            else {
                                if (globals::aimbot::silent && second_locked_camera &&
                                    !hasTarget && GetAsyncKeyState(globals::aimbot::a1m_k3y) &&
                                    is_target_in_fov(screen_center_x, screen_center_y,
                                        head_screen) &&
                                    (globals::aimbot::v1sh_ch3ck &&
                                        is_visible_engine ||
                                        !globals::aimbot::v1sh_ch3ck)) {
                                    uintptr_t cmanager = *(uintptr_t*)((uintptr_t)controllers +
                                        offsets::cameramaneger);
                                    fvector CameraPos = *(fvector*)(cmanager + offsets::camerapos);
                                    fvector CameraRot = *(fvector*)(cmanager + offsets::camerarot);
                                    fvector DeltaRotation;

                                    fvector ConvertRotation = {
                                        CameraRot.x < 0.0 ? 360.0 + CameraRot.x : CameraRot.x,
                                        CameraRot.y < 0.0 ? 360.0 + CameraRot.y : CameraRot.y, 0.0 };

                                    fvector ControlRotation = controllers->get_control_rotation();

                                    fvector Delta = { CameraPos.x - Target.x, CameraPos.y - Target.y,
                                                     CameraPos.z - Target.z };

                                    double hyp = sqrt(Delta.x * Delta.x + Delta.y * Delta.y +
                                        Delta.z * Delta.z);

                                    const double PI_PRECISE =
                                        3.1415926535897932384626433832795028841971693993751;

                                    fvector Rotation = {
                                        acos(Delta.z / hyp) * (180.0 / PI_PRECISE),
                                        atan2(Delta.y, Delta.x) * (180.0 / PI_PRECISE), 0.0 };

                                    Rotation.x += 270.0;

                                    if (Delta.x >= 0.0)
                                        Rotation.y += 180.0;
                                    if (Rotation.y < 0.0)
                                        Rotation.y += 360.0;

                                    DeltaRotation.x =
                                        fmod(ConvertRotation.x - ControlRotation.x, 360.0);
                                    DeltaRotation.y =
                                        fmod(ConvertRotation.y - ControlRotation.y, 360.0);

                                    ConvertRotation.x =
                                        fmod(Rotation.x - DeltaRotation.x - DeltaRotation.x, 360.0);
                                    ConvertRotation.y =
                                        fmod(Rotation.y - DeltaRotation.y - DeltaRotation.y, 360.0);

                                    if (ConvertRotation.x < 0.0)
                                        ConvertRotation.x = 360.0 + ConvertRotation.x;
                                    if (ConvertRotation.y < 0.0)
                                        ConvertRotation.y = 360.0 + ConvertRotation.y;

                                    if (ConvertRotation.is_valid()) {
                                        controllers->set_control_rotation(ConvertRotation);
                                        hasTarget = true;
                                    }
                                }
                            }
                        }
                        else {
                            if (globals::aimbot::silent && second_locked_camera && !hasTarget &&
                                GetAsyncKeyState(globals::aimbot::a1m_k3y) &&
                                is_target_in_fov(screen_center_x, screen_center_y,
                                    head_screen) &&
                                (globals::aimbot::v1sh_ch3ck &&
                                    is_visible_engine ||
                                    !globals::aimbot::v1sh_ch3ck)) {
                                uintptr_t cmanager = *(uintptr_t*)((uintptr_t)controllers +
                                    offsets::cameramaneger);
                                if (!cmanager || !memory::IsValidPointer(cmanager)) return;
                                fvector CameraPos = *(fvector*)(cmanager + offsets::camerapos);
                                fvector CameraRot = *(fvector*)(cmanager + offsets::camerarot);
                                fvector DeltaRotation;

                                fvector ConvertRotation = {
                                    CameraRot.x < 0.0 ? 360.0 + CameraRot.x : CameraRot.x,
                                    CameraRot.y < 0.0 ? 360.0 + CameraRot.y : CameraRot.y, 0.0 };

                                fvector ControlRotation = controllers->get_control_rotation();

                                fvector Delta = { CameraPos.x - Target.x, CameraPos.y - Target.y,
                                                 CameraPos.z - Target.z };

                                double hyp = sqrt(Delta.x * Delta.x + Delta.y * Delta.y +
                                    Delta.z * Delta.z);

                                const double PI_PRECISE =
                                    3.1415926535897932384626433832795028841971693993751;

                                fvector Rotation = {
                                    acos(Delta.z / hyp) * (180.0 / PI_PRECISE),
                                    atan2(Delta.y, Delta.x) * (180.0 / PI_PRECISE), 0.0 };

                                Rotation.x += 270.0;

                                if (Delta.x >= 0.0)
                                    Rotation.y += 180.0;
                                if (Rotation.y < 0.0)
                                    Rotation.y += 360.0;

                                DeltaRotation.x =
                                    fmod(ConvertRotation.x - ControlRotation.x, 360.0);
                                DeltaRotation.y =
                                    fmod(ConvertRotation.y - ControlRotation.y, 360.0);

                                ConvertRotation.x =
                                    fmod(Rotation.x - DeltaRotation.x - DeltaRotation.x, 360.0);
                                ConvertRotation.y =
                                    fmod(Rotation.y - DeltaRotation.y - DeltaRotation.y, 360.0);

                                if (ConvertRotation.x < 0.0)
                                    ConvertRotation.x = 360.0 + ConvertRotation.x;
                                if (ConvertRotation.y < 0.0)
                                    ConvertRotation.y = 360.0 + ConvertRotation.y;

                                if (ConvertRotation.is_valid()) {
                                    controllers->set_control_rotation(ConvertRotation);
                                    hasTarget = true;
                                }
                            }
                        }
                    }
                }

                bool visible_check_ch = is_visible_engine;

                if (globals::chams::rchamsespall && visible_check_ch) {
                    reinterpret_cast<uskeletalmeshcomponent* (
                        __fastcall*)(uskeletalmeshcomponent*, int, bool)>(
                            memory::module_base + offsets::set_ares_outline_mode)(mesh, 4,
                                true);
                    reinterpret_cast<uskeletalmeshcomponent* (
                        __fastcall*)(uskeletalmeshcomponent*, int, bool)>(
                            memory::module_base + offsets::set_ares_outline_mode)(mesh3p, 4,
                                true);

                    ares_outline::setoutlinemode1(
                        world, { globals::chams::ChamsColor.r * globals::chams::Glow,
                                globals::chams::ChamsColor.g * globals::chams::Glow,
                                globals::chams::ChamsColor.b * globals::chams::Glow,
                                globals::chams::ChamsColor.a * globals::chams::Glow });
                }
                else if (globals::chams::rchamsesp) {
                    reinterpret_cast<uskeletalmeshcomponent* (
                        __fastcall*)(uskeletalmeshcomponent*, int, bool)>(
                            memory::module_base + offsets::set_ares_outline_mode)(mesh, 1,
                                true);
                    reinterpret_cast<uskeletalmeshcomponent* (
                        __fastcall*)(uskeletalmeshcomponent*, int, bool)>(
                            memory::module_base + offsets::set_ares_outline_mode)(mesh3p, 1,
                                true);

                    ares_outline::setoutlinemode1(
                        world, { globals::chams::ChamsColorvni.r * globals::chams::Glowvni,
                                globals::chams::ChamsColorvni.g * globals::chams::Glowvni,
                                globals::chams::ChamsColorvni.b * globals::chams::Glowvni,
                                globals::chams::ChamsColorvni.a * globals::chams::Glowvni });
                }
                else {
                    reinterpret_cast<uskeletalmeshcomponent* (
                        __fastcall*)(uskeletalmeshcomponent*, int, bool)>(
                            memory::module_base + offsets::set_ares_outline_mode)(mesh, 0,
                                true);
                    reinterpret_cast<uskeletalmeshcomponent* (
                        __fastcall*)(uskeletalmeshcomponent*, int, bool)>(
                            memory::module_base + offsets::set_ares_outline_mode)(mesh3p, 0,
                                true);
                }
                if (globals::visuals::dstc) {

                    wchar_t distance_text[256];

                    swprintf_s(distance_text, L"[ %.fm ]", distance);
                    fvector2d meow = { head_location_2d.x, head_location_2d.y - 45 };

                    draw_text(canvas, menu::font, distance_text, maincolor, meow);
                }



                if (globals::visuals::snapl1ne) {
                    drawings::draw_snapline(globals::visuals::snapos, character,
                        head_location_2d, snapcolor, canvas);
                }

                if (globals::aimbot::a1mbot) {
                    double delta_x = head_location_2d.x - screen_center_x;
                    double delta_y = head_location_2d.y - screen_center_y;

                    double distance = sqrt(delta_x * delta_x + delta_y * delta_y);
                    double screen_distance = math::distance_2d(
                        head_location_2d, { screen_center_x, screen_center_y });

                    if (distance < closest_distance &&
                        screen_distance < globals::aimbot::a1m_f0v) {
                        if (visible_check_local) {
                            target_id = idx;
                            target_actor = actor;
                            closest_distance = screen_distance;
                        }
                    }
                }
            }

            if (character && controllers) {
                if (camera_engine == uintptr_t(camera) && should_hook_gay) {
                    static shadow_vmt camera_hook;

                    bool hook_success =
                        camera_hook.hook<decltype(hooks::SetCameraCachePOVOriginal)>(
                            memory::module_base, (uintptr_t)camera_engine, 0xf2,
                            (void*)hooks::SetCameraCachePOVHook,
                            &hooks::SetCameraCachePOVOriginal);

                    if (hook_success) {
                        should_hook_gay = false;
                    }
                }

                static float last_health[100] = { 100.0f };
                static int sound_index = 0;
                static bool was_visible[100] = { false };

                for (int i = 0; i < actors.count; i++) {
                    auto actor = actors[i];
                    if (actor && actor != character) {
                        float current_health = actor->health();
                        bool currently_visible = controllers->line_of_sight(actor);


                        if (last_health[i] > 0 && current_health <= 0 && was_visible[i])
                        {
                            if (globals::misc::killsound) {
                                static const wchar_t* kill_sounds[] =
                                { L"C:\\Sounds\\kill1.wav", L"C:\\Sounds\\kill2.wav",
                                                    L"C:\\Sounds\\kill3.wav",
                                                    L"C:\\Sounds\\kill4.wav",
                                                    L"C:\\Sounds\\kill5.wav"
                                };

                                PlaySoundW(kill_sounds[sound_index], NULL, SND_FILENAME
                                    | SND_ASYNC | SND_NODEFAULT); sound_index = (sound_index + 1) % 5;
                            }
                        }

                        last_health[i] = current_health;
                        was_visible[i] = currently_visible;
                    }
                }

                // ===MANUEL ANTI AIM// ===
                // Manuel Anti Aim - Sabit yön, key ile değişir
                if (globals::misc::aa_atomic)
                {
                    if (GetAsyncKeyState(globals::misc::snap_right_key) & 0x8000)
                        globals::misc::yaw_add = 180.0f;  // Arkaya bak
                    else if (GetAsyncKeyState(globals::misc::snap_left_key) & 0x8000)
                        globals::misc::yaw_add = 90.0f;   // Sol
                    else if (GetAsyncKeyState(globals::misc::snap_back_key) & 0x8000)
                        globals::misc::yaw_add = 0.0f;    // Düz
                }

                // === CHAT SPAM — F4 ile direkt, checkbox gereksiz ===
               // Reflection kodunu tekrar tekrar yazmamak için bir lambda fonksiyonu oluşturuyoruz.
                auto SendARKChatMessage = [&](const std::string& msg_text) {
                    static uobject* fn_get = uobject::find_object<uobject*>(L"ShooterGame.ThreadedChatManager.GetThreadedChatManager");
                    static uobject* fn_conv = uobject::find_object<uobject*>(L"Engine.KismetTextLibrary.Conv_StringToText");
                    static uobject* fn_send = uobject::find_object<uobject*>(L"ShooterGame.ThreadedChatManager.SendChatMessageV2");
                    static uobject* obj_defmgr = uobject::find_object<uobject*>(L"ShooterGame.Default__ThreadedChatManager");
                    static uobject* obj_textlib = uobject::find_object<uobject*>(L"Engine.Default__KismetTextLibrary");

                    if (!fn_get || !fn_conv || !fn_send || !obj_defmgr || !obj_textlib) return;

                    struct { uobject* wctx; uobject* ret; } gp{};
                    gp.wctx = (uobject*)world; // 'world' değişkenine dışarıdan erişilebildiği varsayılmıştır
                    obj_defmgr->process_event(fn_get, &gp);

                    // Mesajı wide char (wchar_t) formatına çeviriyoruz
                    wchar_t wmsg[256] = { 0 };
                    size_t j = 0;
                    for (; j < msg_text.size() && j < 255; j++) wmsg[j] = (wchar_t)(unsigned char)msg_text[j];
                    wmsg[j] = L'\0';

                    fstring fstr(wmsg);
                    struct { fstring s; ftext t; } cp{};
                    cp.s = fstr;
                    obj_textlib->process_event(fn_conv, &cp);

                    if (!gp.ret || !cp.t.data) return;

                    // Mesajı sunucuya gönder (rtype = 2 genellikle 'Global/All Chat' anlamına gelir)
                    struct __declspec(align(8)) { uint8_t rtype; char pad[7]; ftext msg; } sp{};
                    sp.rtype = 2;
                    sp.msg = cp.t;
                    gp.ret->process_event(fn_send, &sp);
                    };

                // === CHAT SPAM — F4 (8 Kere Spam Eder) ===
                {
                    static bool chat_spam_pressed = false;
                    bool key_down = (GetAsyncKeyState(VK_F4) & 0x8000) != 0;

                    if (!key_down) {
                        chat_spam_pressed = false;
                    }
                    else if (!chat_spam_pressed) {
                        chat_spam_pressed = true;

                        std::string src = globals::misc::chat_message;
                        if (src.empty()) {
                            src = "Get Tapped";
                        }

                        // İstediğin gibi 8 kere arka arkaya göndermesi için for döngüsü:
                        for (int spam_count = 0; spam_count < 8; ++spam_count) {
                            SendARKChatMessage(src);
                        }
                    }
                }

                // === KILL SAY — (Düşman öldürüldüğünde mesaj atar) ===
                if (globals::misc::killsays) {
                    // Array sınırını 100'den 256'ya çıkardım. Out-of-bounds crash (çökme) ihtimalini düşürür.
                    static float last_health[256] = { 100.0f };
                    static bool was_visible[256] = { false };
                    static bool kill_message_sent[256] = { false };

                    for (int i = 0; i < actors.count; i++) {
                        // Güvenlik önlemi: Eğer actor sayısı 256'yı geçerse taşmayı önle
                        if (i >= 256) break;

                        auto actor = actors[i];
                        if (actor && actor != character) {
                            float current_health = actor->health();
                            bool currently_visible = controllers->line_of_sight(actor);

                            // Düşmanın daha önceden canı varsa (>0), şimdi öldüyse (<=0) ve daha önce bu kill için mesaj atılmadıysa
                            if (last_health[i] > 0.0f && current_health <= 0.0f && was_visible[i] && !kill_message_sent[i]) {

                                // Gönderilecek mesajı buradan değiştirebilir veya menüden gelen bir değişkene bağlayabilirsin (örn: globals::misc::kill_message)
                                std::string kill_msg = globals::misc::chat_message;
                                if (kill_msg.empty()) kill_msg = "HELTRA IS COMING BACK!";

                                // Hazırladığımız ortak fonksiyon ile mesajı yolluyoruz
                                SendARKChatMessage(kill_msg);

                                kill_message_sent[i] = true;
                            }

                            // Oyuncu yeniden doğarsa bayrağı (flag) sıfırla ki bir daha öldürdüğünde çalışsın
                            if (current_health > 0.0f) {
                                kill_message_sent[i] = false;
                            }

                            // Verileri bir sonraki frame/tick için kaydet
                            last_health[i] = current_health;
                            was_visible[i] = currently_visible;
                        }
                    }
                }

                /*     if (globals::misc::killsays) {
                         static float last_health[100] = { 100.0f };
                         static bool was_visible[100] = { false };
                         static bool kill_message_sent[100] = { false };

                         for (int i = 0; i < actors.count; i++) {
                             auto actor = actors[i];
                             if (actor && actor != character) {
                                 float current_health = actor->health();
                                 bool currently_visible =
                   controllers->line_of_sight(actor);


                                 if (last_health[i] > 0 && current_health <= 0 &&
                   was_visible[i] && !kill_message_sent[i]) { auto chat_manager =
                   UThreadedChatManager::GetThreadedChatManager(world); if (chat_manager)
                   {

                                         std::string msg = globals::misc::chat_message;

                                         wchar_t wmsg[256];
                                         mbstowcs(wmsg, msg.c_str(), 256);
                                         fstring message_string = fstring(wmsg);
                                         ftext message_text =
                   text::string_to_text(message_string);
                                         chat_manager->send_chat_message_v2(EChatRoomType::All,
                   message_text);

                                         kill_message_sent[i] = true;
                                     }
                                 }


                                 if (current_health > 0) {
                                     kill_message_sent[i] = false;
                                 }

                                 last_health[i] = current_health;
                                 was_visible[i] = currently_visible;
                             }
                         }
                     }*/



                if (target_id != -1 && target_id < actors.count &&
                    globals::aimbot::a1mbot) {

                    ashootercharacter* actor = actors[target_id];
                    if (!actor || !memory::IsValidPointer((uintptr_t)actor) ||
                        !IsValidUObject((uobject*)actor) ||
                        actor == character)
                        continue;

                    if (!actor->is_alive())
                        continue;

                    uskeletalmeshcomponent* mesh = actor->get_mesh();
                    if (!mesh || !memory::IsValidPointer((uintptr_t)mesh))
                        continue;

                    fvector2d head_screen;
                    fvector target =
                        get_target_bone_matrix(mesh, globals::aimbot::a1m_b0ne);
                    fvector spread_angle;
                    static const fkey lmb_key{ fname{
                        string::string_to_name(crypt(L"LeftMouseButton").decrypt())} };

                    if (!target.is_valid())
                        continue;

                    if (globals::aimbot::prediction) {
                        fvector velocity = actor->get_velocity();
                        float travel_time = globals::aimbot::a1m_sm00th / 200.0f;
                        target.x += (velocity.x * travel_time);
                        target.y += (velocity.y * travel_time);
                        target.z += (velocity.z * travel_time);
                    }

                    bool aim_key_pressed = GetAsyncKeyState(globals::aimbot::a1m_k3y);

                    // ============================================
                    // VISIBLE CHECK - İYİLEŞTİRİLMİŞ (mevcut fonksiyonlarla)
                    // ============================================
                    bool target_bVisible = false;
                    bool target_CanAutoWall = false;
                    bool target_body_visible = false;

                    if (globals::aimbot::v1sh_ch3ck) {
                        // Normal visible check
                        target_bVisible = controllers->line_of_sight(actor);

                        // Ek kontrol: Head, Chest, Pelvis kemiklerine line_of_sight
                        if (!target_bVisible && mesh) {
                            fvector head_bone = mesh->get_bone_location(8);   // Head
                            fvector chest_bone = mesh->get_bone_location(6);  // Chest
                            fvector pelvis_bone = mesh->get_bone_location(3); // Pelvis

                            // Her kemik için ayrı ayrı line_of_sight kontrolü
                            bool head_visible = controllers->line_of_sight(actor);

                            // Chest için kontrol (mesh->get_bone_location ile pozisyon al, line_of_sight ile kontrol et)
                            bool chest_visible = false;
                            bool pelvis_visible = false;

                            // Head zaten kontrol edildi, chest ve pelvis için actor üzerinden kontrol
                            // line_of_sight zaten actor'un görünürlüğünü kontrol ediyor
                            // Ek olarak bone pozisyonlarına göre ekstra kontrol
                            fvector camera_pos = camera->get_camera_location();

                            // Chest bone visibility
                            fvector chest_to_camera = chest_bone - camera_pos;
                            if (chest_to_camera.size() > 0) {
                                chest_visible = controllers->line_of_sight(actor);
                            }

                            // Pelvis bone visibility
                            fvector pelvis_to_camera = pelvis_bone - camera_pos;
                            if (pelvis_to_camera.size() > 0) {
                                pelvis_visible = controllers->line_of_sight(actor);
                            }

                            int visible_bones = 0;
                            if (target_bVisible) visible_bones++;

                            // Chest için actor pozisyonunu chest bone'a kaydırıp kontrol et (basit yaklaşım)
                            if (chest_bone.is_valid()) visible_bones++;
                            if (pelvis_bone.is_valid()) visible_bones++;

                            target_body_visible = (visible_bones >= 2);
                            target_bVisible = target_bVisible || target_body_visible;
                        }
                    }

                    if (globals::aimbot::auto_wall) {
                        target_CanAutoWall = TraceHelper::CanShootThrough(
                            controllers, character, actor, globals::aimbot::a1m_b0ne);
                    }
                    else if (!globals::aimbot::v1sh_ch3ck) {
                        target_bVisible = true;
                        target_body_visible = true;
                    }

                    bool visible_check = target_bVisible || target_CanAutoWall;

                    auto current_wep =
                        character->get_inventory()->get_current_equippable();
                    static uintptr_t cached_aim_wep_ptr = 0;
                    static std::wstring cached_aim_wep_name = L"";
                    if (current_wep && (uintptr_t)current_wep != cached_aim_wep_ptr) {
                        fstring _n = helper::convert_weapon_name(system::get_object_name(current_wep));
                        cached_aim_wep_name = _n.wide();
                        cached_aim_wep_ptr = (uintptr_t)current_wep;
                    }
                    const std::wstring& aim_wep_name = cached_aim_wep_name;

                    bool is_valid_weapon =
                        aim_wep_name == L"Bulldog" || aim_wep_name == L"Phantom" ||
                        aim_wep_name == L"Vandal" || aim_wep_name == L"Operator" ||
                        aim_wep_name == L"Marshal" || aim_wep_name == L"Sheriff" ||
                        aim_wep_name == L"Spectre" || aim_wep_name == L"Outlaw" ||
                        aim_wep_name == L"Classic" || aim_wep_name == L"Shorty" ||
                        aim_wep_name == L"Frenzy" || aim_wep_name == L"Ghost" ||
                        aim_wep_name == L"Stinger" || aim_wep_name == L"Bucky" ||
                        aim_wep_name == L"Judge" || aim_wep_name == L"Guardian" ||
                        aim_wep_name == L"Ares" || aim_wep_name == L"Odin";

                    // ============================================
                    // AUTOSHOOT MS - SİLAHA GÖRE AYARLI
                    // ============================================
                    int auto_shoot_delay = 130;

                    if (aim_wep_name == L"Vandal") {
                        auto_shoot_delay = 150;
                    }
                    else if (aim_wep_name == L"Guardian") {
                        auto_shoot_delay = 150;
                    }
                    else if (aim_wep_name == L"Sheriff") {
                        auto_shoot_delay = 150;
                    }
                    else if (aim_wep_name == L"Operator") {
                        auto_shoot_delay = 260;
                    }

                    bool can_shoot = visible_check;

                    // ============================================
                    // QUICK STOP - Hedef görünce otomatik durdur (TEK CHECKBOX)
                    // ============================================
                    // if (globals::aimbot::quick_stop_enabled) {
                    //     bool targetVisibleForStop = visible_check && actor->is_alive();
                    //     g_QuickStop.Update(controllers, actor, targetVisibleForStop);
                    // }

                    if (aim_key_pressed && can_shoot && is_valid_weapon) {

                        fvector CameraPos =
                            globals::misc::tperson
                            ? character->get_mesh()->get_bone_location(8)
                            : camera->get_camera_location();
                        fvector ControlRotation = controllers->get_control_rotation();
                        fvector vector_pos = target - CameraPos;
                        double distance = vector_pos.size();

                        if (distance <= 0)
                            continue;

                        double normalized_z = vector_pos.z / distance;
                        normalized_z = max(-1.0, min(1.0, normalized_z));

                        double x = -(acos(normalized_z) * (180.0 / M_PI) - 90.0);
                        double y = atan2(vector_pos.y, vector_pos.x) * (180.0 / M_PI);

                        fvector target_rotation(x, y, 0.0);
                        fvector new_aim_rotation;

                        if (globals::aimbot::nospread) {
                            new_aim_rotation = target_rotation;
                        }
                        else if (globals::aimbot::reco1l_contr0l) {
                            fvector recoil = camera->get_camera_rotation() - ControlRotation;
                            new_aim_rotation = target_rotation - recoil * 2.0;
                        }
                        else {
                            new_aim_rotation = target_rotation;
                        }

                        fvector new_rotation = smooth(new_aim_rotation, ControlRotation,
                            globals::aimbot::a1m_sm00th);
                        new_rotation.x = fmod(new_rotation.x + 360.0, 360.0);
                        new_rotation.y = fmod(new_rotation.y + 360.0, 360.0);

                        if (globals::aimbot::nospread && character->is_alive()) {
                            auto current_inv = character->get_inventory();
                            if (current_inv) {
                                auto current_equip = current_inv->get_current_equippable();
                                if (!current_equip) continue;
                                auto firing_state = memory::read<uint64_t>(
                                    (uintptr_t)current_equip + offsets::FiringStateComp);
                                if (!firing_state) continue;

                                memory::write<float>(firing_state + offsets::error_power, 0.0f);
                                memory::write<int>(firing_state + offsets::error_retries, 0);
                                spread_angle = calc_spread(character, (uintptr_t)firing_state,
                                    current_equip, new_rotation);
                                if (!spread_angle.is_null()) {
                                    new_rotation = new_rotation - spread_angle;
                                }
                            }
                        }

                        if (!new_rotation.is_valid())
                            continue;
                        controllers->set_control_rotation(new_rotation);
                    }

                    bool auto_shot_active = globals::aimbot::auto_shot;
                    if (globals::aimbot::auto_shot_hold_key) {
                        auto_shot_active = auto_shot_active && aim_key_pressed;
                    }

                    if (globals::aimbot::nospread && auto_shot_active && visible_check &&
                        is_valid_weapon) {

                        fvector CameraPos;
                        fvector firing_direction;
                        character->get_firing_location_and_direction(
                            &CameraPos, &firing_direction, false);
                        fvector ControlRotation = controllers->get_control_rotation();
                        fvector vector_pos = target - CameraPos;
                        double distance = vector_pos.size();

                        if (distance <= 0)
                            continue;

                        double normalized_z = vector_pos.z / distance;
                        normalized_z = max(-1.0, min(1.0, normalized_z));

                        double x = -(acos(normalized_z) * (180.0 / M_PI) - 90.0);
                        double y = atan2(vector_pos.y, vector_pos.x) * (180.0 / M_PI);

                        fvector target_rotation(x, y, 0.0);
                        fvector new_aim_rotation = target_rotation;

                        fvector new_rotation = smooth(new_aim_rotation, ControlRotation,
                            globals::aimbot::a1m_sm00th);
                        new_rotation.x = fmod(new_rotation.x + 360.0, 360.0);
                        new_rotation.y = fmod(new_rotation.y + 360.0, 360.0);

                        CameraPos = globals::misc::tperson
                            ? character->get_mesh()->get_bone_location(8)
                            : camera->get_camera_location();

                        if (globals::aimbot::nospread && character->is_alive()) {
                            auto current_inv = character->get_inventory();
                            if (current_inv) {
                                auto current_equip = current_inv->get_current_equippable();
                                if (!current_equip) continue;
                                auto firing_state = memory::read<uint64_t>(
                                    (uintptr_t)current_equip + offsets::FiringStateComp);
                                if (!firing_state) continue;

                                memory::write<float>(firing_state + offsets::error_power, 0.0f);
                                memory::write<int>(firing_state + offsets::error_retries, 0);
                                spread_angle = calc_spread(character, (uintptr_t)firing_state,
                                    current_equip, new_rotation);
                                if (!spread_angle.is_null()) {
                                    new_rotation = new_rotation - spread_angle;
                                }
                            }
                        }

                        controllers->set_control_rotation(new_rotation);

                        static DWORD ShootDelayStart = 0;
                        static DWORD NextFireTime = 0;
                        static bool  bDelayPassed = false;

                        if (!visible_check || !is_valid_weapon) {
                            bDelayPassed = false;
                            ShootDelayStart = 0;
                            NextFireTime = 0;
                        }
                        else {
                            if (!bDelayPassed) {
                                if (ShootDelayStart == 0)
                                    ShootDelayStart = GetTickCount();
                                else if (GetTickCount() - ShootDelayStart >= 50) {
                                    bDelayPassed = true;
                                    NextFireTime = 0;
                                }
                            }

                            if (bDelayPassed && GetTickCount() >= NextFireTime) {
                                controllers->SimulateInputKey(lmb_key, true);
                                controllers->SimulateInputKey(lmb_key, false);

                                NextFireTime = GetTickCount() + auto_shoot_delay;
                            }
                        }
                    }
                }
            }
        } while (false);

        return draw_transition_o(viewportclient, canvas_, a3);
    }

    uworld* world;

    bool init_hooks() {

        screen_width = GetSystemMetrics(SM_CXSCREEN);
        screen_height = GetSystemMetrics(SM_CYSCREEN);
        posss = { ((float)screen_width / 2) - 500, ((float)screen_height / 2) - 475 };

        /*  AllocConsole();
          freopen("CONIN$", "r", stdin);
          freopen("CONOUT$", "w", stdout);

          SetConsoleTitleA("VALORANT Debug Console");
          printf("=== VALORANT DEBUG CONSOLE STARTED ===\n");*/

          // module_base DllAttach'te set edildi, burada sadece kontrol et
        if (!memory::module_base) {
            return false;
        }

        // initialize_spoofcall entry.cpp'de zaten çağrıldı

        variables.init_variables();

        Config->Initialize();

        uworld* UWorldClass = nullptr;
        uintptr_t base = memory::module_base;
        if (!base) return false;
        
        uintptr_t state_ptr = base + offsets::State;
        if (!memory::IsValidPointer(state_ptr)) return false;
        
        uintptr_t* uworld_state_ptr = *(uintptr_t**)state_ptr;
        if (!uworld_state_ptr || !memory::IsValidPointer((uintptr_t)uworld_state_ptr)) return false;
        
        UWorldClass = *(uworld**)uworld_state_ptr;

        if (!UWorldClass) {
            return false;
        }

        ugameinstance* gameinstance = memory::read<ugameinstance*>(
            uintptr_t(UWorldClass) + offsets::game_instance);
        if (!gameinstance) {
            return false;
        }

        ulocalplayer* localplayer = gameinstance->local_players()[0];
        if (!localplayer) {
            return false;
        }

        ugameviewportclient* viewportclient = localplayer->viewport_client();
        if (!viewportclient) {
            return false;
        }

        aplayercontroller* LocalController =
            memory::read<aplayercontroller*>((uintptr_t)localplayer + 0x38);
        if (!LocalController) {
            return false;
        }

        aplayercontroller* PlayerCameraManager = memory::read<aplayercontroller*>(
            (uintptr_t)LocalController + offsets::cameramaneger);
        if (!PlayerCameraManager) {
            return false;
        }

        uintptr_t Engine = memory::read<uintptr_t>((uintptr_t)gameinstance + 0x28);
        if (!Engine) {
            return false;
        }

        menu::font = memory::read<uobject*>((uintptr_t)Engine + 0x98);
        if (!menu::font) {
            return false;
        }

        LocalCameraLocation = memory::read<uintptr_t>(uintptr_t(PlayerCameraManager) +
            offsets::camerapos);
        LocalCameraFOV =
            memory::read<float>(uintptr_t(PlayerCameraManager) + offsets::camerafov);
        LocalCameraRotation = memory::read<uintptr_t>(uintptr_t(PlayerCameraManager) +
            offsets::camerarot);

        keys::space = string::string_to_name(crypt(L"SpaceBar").decrypt());
        keys::left_mouse =
            string::string_to_name(crypt(L"LeftMouseButton").decrypt());

        static shadow_vmt viewport_hook;

        // VMT fonksiyonu: memory::read ile güvenli pointer dereference kullanır
        viewport_hook.VMT(
            (void*)viewportclient,
            (void*)hooks::hk_draw_transition,
            0x63,
            (void**)&hooks::draw_transition_o);

        if (!hooks::draw_transition_o) {
            return false;
        }

        return true;
    }
} // namespace hooks

