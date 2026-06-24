#pragma once
#include "canva.hpp"
#include "config.h"
#include <ShlObj.h>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <vector>
#include <filesystem>
#include <string>

namespace heltra {

    // MENÜ (600x850)
    fvector2d pos = { 960 - (600 / 2), 540 - (850 / 2) };
    bool menu_open = true;
    static int tab = 0;
    static float rainbow_tick = 0.0f;
    static int waiting_for_keybind = -1;
    static bool capturing_key = false;

    // Chat input için global değişkenler
    static char chat_message_buffer[256] = "Powered By Heltra";
    static bool chat_input_active = false;
    static int chat_cursor_blink = 0;

    // ========== STATIC DEĞİŞKENLER ==========
    static bool wall_only_chams = false;
    static bool wall_only_rainbow = false;
    static bool gun_chams = false;
    static bool wireframe_gun = false;
    static bool enemy_fresnel = false;
    static bool spike_chams = false;
    static bool custom_skin_texture = false;
    static bool custom_sky_texture = false;
    static bool gun_materials = false;
    static bool shooter_trail = false;
    static bool advanced_resolver = false;
    static bool viewmodel_changer = false;
    static bool big_gun = false;
    static bool self_resizer = false;
    static bool kill_sounds = false;
    static bool killsay = false;
    static bool dynamic_hitsound = false;
    static bool apply_texture = false;
    static bool remove_scope = false;
    static bool remove_flash = false;
    static bool skip_tutorial = false;
    static bool custom_aspect_ratio = false;
    static bool third_person = false;
    static int thirdperson_key = 0;
    static bool fov_changer = false;
    static float aspect_ratio = 1.30f;
    static float thirdperson_distance = 270.0f;
    static bool hand_material = false;
    static bool enable_outline = false;
    static bool glow_effect = false;
    static float outline_thickness = 2.0f;
    static float glow_intensity = 0.5f;
    static bool enemies_only = false;
    static bool visible_only = false;
    static bool weapon_outline = false;
    static float max_distance = 5000.0f;
    static bool ignore_dormants = true;
    static bool visible_check = false;
    static bool box_25d = false;
    static bool box_2d = false;
    static bool box_outline = false;
    static bool filled_box = false;
    static bool skeleton = false;
    static bool corner_box = false;
    static bool dist_esp = false;
    static bool snaplines = false;
    static bool snapline_fov = false;
    static bool head_box = false;
    static bool health_bar = false;
    static bool agent_icon = false;
    static bool weapon_esp = false;
    static bool wukong_3p = false;
    static bool chinese_enemy = false;
    static bool chinese_hat_3p = false;
    static bool bullet_tracers = false;
    static bool radar_map = false;
    static bool platform_info = false;
    static bool agent_name = false;
    static bool player_name = false;
    static bool gun_on_ground = false;
    static bool recoil_crosshair = false;
    static bool ping_esp = false;
    static bool rank_info = false;
    static bool rank_label = false;
    static bool abilities = false;
    static bool bomb_info = false;
    static bool enable_skybox = false;
    static bool rainbow_skybox = false;
    static bool disable_vignetta = false;
    static bool world_fog = false;
    static bool spike_esp = false;
    static bool spike_timer = false;
    static bool world_esp = false;
    static bool cypher_traps = false;
    static bool gadgets = false;
    static int skybox_preset = 0;
    static float fog_cutoff1 = 300.0f;
    static float fog_cutoff2 = 1.0f;
    static float fog_cutoff3 = 300.0f;
    static float fog_height = 0.20f;
    static float fog_start = 0.0f;
    static float fog_max = 1.0f;
    static float sun_height = 0.0f;
    static float noise1 = 1.0f;
    static float noise2 = 1.0f;

    // RENKLER - MOR TEMA
    flinearcolor bg_main = { 0.0015f, 0.0015f, 0.0015f, 1.0f };
    flinearcolor bg_content = { 0.0035f, 0.0035f, 0.0035f, 1.0f };
    flinearcolor bg_element = { 0.006f, 0.006f, 0.006f, 1.0f };
    flinearcolor bg_section = { 0.008f, 0.008f, 0.010f, 1.0f };
    flinearcolor accent_primary = { 0.65f, 0.25f, 0.85f, 1.0f };
    flinearcolor accent_active = { 0.75f, 0.35f, 0.95f, 1.0f };
    flinearcolor fovcolor = { 0.65f, 0.25f, 0.85f, 0.3f };
    flinearcolor text_white = { 0.92f, 0.92f, 0.92f, 1.0f };
    flinearcolor text_gray = { 0.45f, 0.45f, 0.48f, 1.0f };
    flinearcolor text_dark_gray = { 0.25f, 0.25f, 0.25f, 1.0f };

    namespace ui {
        static int active_dropdown = -1;
        static fvector2d drop_pos;
        static float drop_width;
        static std::vector<const wchar_t*> drop_items;
        static int* drop_target = nullptr;
    }

    flinearcolor GetRainbow() {
        rainbow_tick += 0.002f;
        if (rainbow_tick > 6.0f) rainbow_tick = 0.0f;
        float r = 1.0f, g = 0.0f, b = 0.0f;
        float tick = rainbow_tick;
        if (tick < 1.0f) { r = 1.0f; g = tick; b = 0.0f; }
        else if (tick < 2.0f) { r = 2.0f - tick; g = 1.0f; b = 0.0f; }
        else if (tick < 3.0f) { r = 0.0f; g = 1.0f; b = tick - 2.0f; }
        else if (tick < 4.0f) { r = 0.0f; g = 4.0f - tick; b = 1.0f; }
        else if (tick < 5.0f) { r = tick - 4.0f; g = 0.0f; b = 1.0f; }
        else { r = 1.0f; g = 0.0f; b = 6.0f - tick; }
        return flinearcolor{ r, g, b, 1.0f };
    }

    bool MouseInRegion(fvector2d region_pos, fvector2d region_size) {
        fvector2d mouse_pos = menu::CursorPos();
        return (mouse_pos.x >= region_pos.x && mouse_pos.x <= region_pos.x + region_size.x &&
            mouse_pos.y >= region_pos.y && mouse_pos.y <= region_pos.y + region_size.y);
    }

    bool MouseClicked() {
        static bool prev_state = false;
        bool curr_state = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
        bool clicked = curr_state && !prev_state;
        prev_state = curr_state;
        return clicked;
    }

    bool MouseHeld() {
        return (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    }

    void NativeCheckbox(const wchar_t* label, bool* value) {
        fvector2d cp = fvector2d(pos.x + menu::offset_x, pos.y + menu::offset_y);
        menu::canvas->k2_drawtext(menu::font, label, fvector2d(cp.x, cp.y), fvector2d(0.80f, 0.80f), text_white, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        fvector2d box_size = { 12, 12 };
        fvector2d box_pos = { cp.x + 240, cp.y };
        menu::drawFilledRect(box_pos, box_size.x, box_size.y, bg_main);
        menu::drawFilledRect(box_pos, box_size.x, 1.0f, text_dark_gray);
        menu::drawFilledRect({ box_pos.x, box_pos.y + box_size.y - 1 }, box_size.x, 1.0f, text_dark_gray);
        menu::drawFilledRect(box_pos, 1.0f, box_size.y, text_dark_gray);
        menu::drawFilledRect({ box_pos.x + box_size.x - 1, box_pos.y }, 1.0f, box_size.y, text_dark_gray);
        if (*value) {
            menu::drawFilledRect({ box_pos.x + 2, box_pos.y + 2 }, box_size.x - 4, box_size.y - 4, accent_primary);
        }
        bool hovered = MouseInRegion({ cp.x, cp.y }, { 260, box_size.y });
        if (hovered && MouseClicked()) {
            *value = !*value;
            ui::active_dropdown = -1;
            chat_input_active = false;
        }
        menu::offset_y += 22;
    }

    void NativeSliderFloat(const wchar_t* label, float* value, float min, float max, const char* format) {
        fvector2d cp = fvector2d(pos.x + menu::offset_x, pos.y + menu::offset_y);
        menu::canvas->k2_drawtext(menu::font, label, fvector2d(cp.x, cp.y), fvector2d(0.80f, 0.80f), text_white, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        char val_buf[32];
        sprintf_s(val_buf, format, *value);
        wchar_t wval[32];
        mbstowcs(wval, val_buf, 32);
        fvector2d val_box_pos = { cp.x + 200, cp.y - 4 };
        menu::drawFilledRect(val_box_pos, 50, 18, bg_main);
        menu::canvas->k2_drawtext(menu::font, wval, { val_box_pos.x + 4, val_box_pos.y + 2 }, fvector2d(0.72f, 0.72f), accent_primary, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        float slider_width = 250.0f;
        float slider_height = 4.0f;
        fvector2d slider_pos = { cp.x, cp.y + 20 };
        menu::drawFilledRect(slider_pos, slider_width, slider_height, bg_element);
        float t = (*value - min) / (max - min);
        t = std::clamp(t, 0.0f, 1.0f);
        menu::drawFilledRect(slider_pos, slider_width * t, slider_height, accent_primary);
        bool hovered = MouseInRegion({ slider_pos.x, slider_pos.y - 4 }, { slider_width, 14 });
        if (hovered && MouseHeld()) {
            fvector2d mouse = menu::CursorPos();
            float new_t = (mouse.x - slider_pos.x) / slider_width;
            new_t = std::clamp(new_t, 0.0f, 1.0f);
            *value = min + (max - min) * new_t;
            ui::active_dropdown = -1;
            chat_input_active = false;
        }
        menu::offset_y += 42;
    }

    // INPUT BOX - Tüm karakterler için
    void NativeInputBox(const wchar_t* label, char* buffer, int buffer_size) {
        fvector2d cp = fvector2d(pos.x + menu::offset_x, pos.y + menu::offset_y);
        float box_width = 260.0f;

        if (label && wcslen(label) > 0) {
            menu::canvas->k2_drawtext(menu::font, label, fvector2d(cp.x, cp.y), fvector2d(0.80f, 0.80f), text_white, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        }

        menu::offset_y += 20;
        fvector2d box_pos = { cp.x, cp.y + 20 };

        menu::drawFilledRect(box_pos, box_width, 26.0f, bg_element);
        menu::drawFilledRect(box_pos, box_width, 1.0f, text_dark_gray);
        menu::drawFilledRect({ box_pos.x, box_pos.y + 25.0f }, box_width, 1.0f, text_dark_gray);
        menu::drawFilledRect(box_pos, 1.0f, 26.0f, text_dark_gray);
        menu::drawFilledRect({ box_pos.x + box_width - 1.0f, box_pos.y }, 1.0f, 26.0f, text_dark_gray);

        // Gösterilecek metin
        wchar_t display_text[256];
        if (!chat_input_active && strlen(buffer) == 0) {
            wcscpy_s(display_text, L"Powered By Heltra");
        }
        else {
            mbstowcs(display_text, buffer, 256);
        }

        menu::canvas->k2_drawtext(menu::font, display_text, { box_pos.x + 8, box_pos.y + 5 }, fvector2d(0.80f, 0.80f),
            (!chat_input_active && strlen(buffer) == 0) ? text_gray : text_white,
            0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });

        bool hovered = MouseInRegion(box_pos, { box_width, 26.0f });
        if (hovered && MouseClicked()) {
            chat_input_active = true;
        }

        if (chat_input_active) {
            menu::drawFilledRect(box_pos, box_width, 26.0f, { 0.12f,0.05f,0.18f,0.5f });

            if (GetAsyncKeyState(VK_ESCAPE) & 1) {
                chat_input_active = false;
            }

            // Tüm harfler (A-Z)
            for (int key = 0x41; key <= 0x5A; key++) {
                if (GetAsyncKeyState(key) & 1) {
                    int len = (int)strlen(buffer);
                    if (len < buffer_size - 1) {
                        char c = (char)key;
                        if (!(GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                            c = tolower(c);
                        }
                        buffer[len] = c;
                        buffer[len + 1] = '\0';
                    }
                    Sleep(10);
                }
            }

            // Sayılar 0-9
            for (int key = 0x30; key <= 0x39; key++) {
                if (GetAsyncKeyState(key) & 1) {
                    int len = (int)strlen(buffer);
                    if (len < buffer_size - 1) {
                        buffer[len] = (char)key;
                        buffer[len + 1] = '\0';
                    }
                    Sleep(10);
                }
            }

            // Noktalama işaretleri
            if (GetAsyncKeyState(VK_OEM_PERIOD) & 1) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = '.'; buffer[len + 1] = '\0'; }
                Sleep(10);
            }
            if (GetAsyncKeyState(VK_OEM_COMMA) & 1) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = ','; buffer[len + 1] = '\0'; }
                Sleep(10);
            }
            if (GetAsyncKeyState(VK_OEM_MINUS) & 1) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) {
                    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) buffer[len] = '_';
                    else buffer[len] = '-';
                    buffer[len + 1] = '\0';
                }
                Sleep(10);
            }
            if (GetAsyncKeyState(VK_OEM_PLUS) & 1) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) {
                    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) buffer[len] = '+';
                    else buffer[len] = '=';
                    buffer[len + 1] = '\0';
                }
                Sleep(10);
            }
            if (GetAsyncKeyState(VK_OEM_1) & 1) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) {
                    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) buffer[len] = ':';
                    else buffer[len] = ';';
                    buffer[len + 1] = '\0';
                }
                Sleep(10);
            }
            if (GetAsyncKeyState(VK_OEM_7) & 1) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) {
                    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) buffer[len] = '"';
                    else buffer[len] = '\'';
                    buffer[len + 1] = '\0';
                }
                Sleep(10);
            }
            if (GetAsyncKeyState(VK_OEM_2) & 1) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) {
                    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) buffer[len] = '?';
                    else buffer[len] = '/';
                    buffer[len + 1] = '\0';
                }
                Sleep(10);
            }
            if (GetAsyncKeyState(VK_OEM_3) & 1) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) {
                    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) buffer[len] = '~';
                    else buffer[len] = '`';
                    buffer[len + 1] = '\0';
                }
                Sleep(10);
            }
            if (GetAsyncKeyState(VK_OEM_4) & 1) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) {
                    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) buffer[len] = '{';
                    else buffer[len] = '[';
                    buffer[len + 1] = '\0';
                }
                Sleep(10);
            }
            if (GetAsyncKeyState(VK_OEM_5) & 1) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) {
                    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) buffer[len] = '|';
                    else buffer[len] = '\\';
                    buffer[len + 1] = '\0';
                }
                Sleep(10);
            }
            if (GetAsyncKeyState(VK_OEM_6) & 1) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) {
                    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) buffer[len] = '}';
                    else buffer[len] = ']';
                    buffer[len + 1] = '\0';
                }
                Sleep(10);
            }

            // Shift + sayılar ile özel karakterler
            if (GetAsyncKeyState(0x31) & 1 && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = '!'; buffer[len + 1] = '\0'; }
                Sleep(10);
            }
            if (GetAsyncKeyState(0x32) & 1 && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = '@'; buffer[len + 1] = '\0'; }
                Sleep(10);
            }
            if (GetAsyncKeyState(0x33) & 1 && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = '#'; buffer[len + 1] = '\0'; }
                Sleep(10);
            }
            if (GetAsyncKeyState(0x34) & 1 && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = '$'; buffer[len + 1] = '\0'; }
                Sleep(10);
            }
            if (GetAsyncKeyState(0x35) & 1 && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = '%'; buffer[len + 1] = '\0'; }
                Sleep(10);
            }
            if (GetAsyncKeyState(0x36) & 1 && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = '^'; buffer[len + 1] = '\0'; }
                Sleep(10);
            }
            if (GetAsyncKeyState(0x37) & 1 && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = '&'; buffer[len + 1] = '\0'; }
                Sleep(10);
            }
            if (GetAsyncKeyState(0x38) & 1 && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = '*'; buffer[len + 1] = '\0'; }
                Sleep(10);
            }
            if (GetAsyncKeyState(0x39) & 1 && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = '('; buffer[len + 1] = '\0'; }
                Sleep(10);
            }
            if (GetAsyncKeyState(0x30) & 1 && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = ')'; buffer[len + 1] = '\0'; }
                Sleep(10);
            }

            // Boşluk
            if (GetAsyncKeyState(VK_SPACE) & 1) {
                int len = (int)strlen(buffer);
                if (len < buffer_size - 1) { buffer[len] = ' '; buffer[len + 1] = '\0'; }
                Sleep(10);
            }

            // Backspace
            if (GetAsyncKeyState(VK_BACK) & 1) {
                int len = (int)strlen(buffer);
                if (len > 0) buffer[len - 1] = '\0';
                Sleep(50);
            }

            // Enter ile onaylama
            if (GetAsyncKeyState(VK_RETURN) & 1) {
                chat_input_active = false;
                if (strlen(buffer) > 0) {
                    globals::misc::chat_message = buffer;
                }
                Sleep(50);
            }
        }

        // İmleç (cursor) gösterimi
        chat_cursor_blink++;
        if (chat_input_active && (chat_cursor_blink % 60 < 30)) {
            int len = (int)strlen(buffer);
            float text_width = len * 6.5f;
            menu::drawFilledRect({ box_pos.x + 10 + text_width, box_pos.y + 7 }, 2, 12, accent_active);
        }

        menu::offset_y += 36;
    }

    void NativeCombobox(const wchar_t* label, int* selected_index, const std::vector<const wchar_t*>& items, int id) {
        fvector2d cp = fvector2d(pos.x + menu::offset_x, pos.y + menu::offset_y);
        menu::canvas->k2_drawtext(menu::font, label, fvector2d(cp.x, cp.y), fvector2d(0.80f, 0.80f), text_white, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        fvector2d box_pos = { cp.x, cp.y + 18 };
        float box_width = 260.0f;
        menu::drawFilledRect(box_pos, box_width, 22.0f, bg_element);
        if (*selected_index >= 0 && *selected_index < (int)items.size()) {
            menu::canvas->k2_drawtext(menu::font, items[*selected_index], { box_pos.x + 8, box_pos.y + 3 }, fvector2d(0.80f, 0.80f), accent_primary, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        }
        menu::canvas->k2_drawtext(menu::font, L"▼", { box_pos.x + box_width - 16, box_pos.y + 3 }, fvector2d(0.80f, 0.80f), text_gray, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        if (MouseInRegion(box_pos, { box_width, 22.0f }) && MouseClicked()) {
            if (ui::active_dropdown == id) ui::active_dropdown = -1;
            else {
                ui::active_dropdown = id;
                ui::drop_pos = { box_pos.x, box_pos.y + 22.0f };
                ui::drop_width = box_width;
                ui::drop_items = items;
                ui::drop_target = selected_index;
            }
            chat_input_active = false;
        }
        menu::offset_y += 44;
    }

    void NativeColorPicker(const wchar_t* label, flinearcolor col) {
        fvector2d cp = fvector2d(pos.x + menu::offset_x, pos.y + menu::offset_y);
        menu::drawFilledRect({ cp.x, cp.y + 2 }, 12, 12, col);
        menu::drawFilledRect({ cp.x, cp.y + 2 }, 12, 1, text_dark_gray);
        menu::drawFilledRect({ cp.x, cp.y + 13 }, 12, 1, text_dark_gray);
        menu::drawFilledRect({ cp.x, cp.y + 2 }, 1, 12, text_dark_gray);
        menu::drawFilledRect({ cp.x + 11, cp.y + 2 }, 1, 12, text_dark_gray);
        menu::canvas->k2_drawtext(menu::font, label, { cp.x + 20, cp.y }, fvector2d(0.80f, 0.80f), text_white, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        menu::offset_y += 24;
    }

    void HotkeyLabeled(const wchar_t* label, int* key) {
        fvector2d cp = fvector2d(pos.x + menu::offset_x, pos.y + menu::offset_y);
        if (label && wcslen(label) > 0) {
            menu::canvas->k2_drawtext(menu::font, label, { cp.x, cp.y + 2 }, fvector2d(0.80f, 0.80f), text_white, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        }
        float box_x = (label && wcslen(label) > 0) ? cp.x + 200 : cp.x;
        fvector2d kp = { box_x, cp.y };
        fvector2d ks = { 55, 18 };
        bool hov = MouseInRegion(kp, ks);
        if (hov && MouseClicked()) {
            capturing_key = true;
            waiting_for_keybind = (int)(uintptr_t)key;
            chat_input_active = false;
        }
        if (capturing_key && waiting_for_keybind == (int)(uintptr_t)key) {
            for (int vk = 1; vk <= 254; vk++) {
                if (vk == VK_LBUTTON || vk == VK_RBUTTON || vk == VK_MBUTTON) continue;
                if (GetAsyncKeyState(vk) & 0x8000) {
                    if (vk == VK_ESCAPE) { *key = 0; capturing_key = false; waiting_for_keybind = -1; break; }
                    *key = vk; capturing_key = false; waiting_for_keybind = -1; break;
                }
            }
        }
        bool is_active = (capturing_key && waiting_for_keybind == (int)(uintptr_t)key);
        menu::drawFilledRect(kp, ks.x, ks.y, is_active ? flinearcolor{ 0.12f,0.05f,0.18f,1.0f } : bg_element);
        flinearcolor border_col = is_active ? accent_active : (hov ? accent_primary : text_dark_gray);
        menu::drawFilledRect(kp, ks.x, 1.0f, border_col);
        menu::drawFilledRect({ kp.x, kp.y + ks.y - 1 }, ks.x, 1.0f, border_col);
        menu::drawFilledRect(kp, 1.0f, ks.y, border_col);
        menu::drawFilledRect({ kp.x + ks.x - 1, kp.y }, 1.0f, ks.y, border_col);
        const wchar_t* key_name = L"-";
        if (is_active) key_name = L"...";
        else if (*key > 0) {
            static wchar_t buf[32];
            if (*key >= 0x30 && *key <= 0x39) swprintf_s(buf, L"%c", L'0' + (*key - 0x30));
            else if (*key >= 0x41 && *key <= 0x5A) swprintf_s(buf, L"%c", L'A' + (*key - 0x41));
            else if (*key >= VK_F1 && *key <= VK_F12) swprintf_s(buf, L"F%d", *key - VK_F1 + 1);
            else if (*key == VK_LBUTTON) swprintf_s(buf, L"MB1");
            else if (*key == VK_RBUTTON) swprintf_s(buf, L"MB2");
            else if (*key == VK_MBUTTON) swprintf_s(buf, L"MB3");
            else if (*key == VK_XBUTTON1) swprintf_s(buf, L"MB4");
            else if (*key == VK_XBUTTON2) swprintf_s(buf, L"MB5");
            else if (*key == VK_SHIFT) swprintf_s(buf, L"Shift");
            else if (*key == VK_CONTROL) swprintf_s(buf, L"Ctrl");
            else if (*key == VK_MENU) swprintf_s(buf, L"Alt");
            else if (*key == VK_SPACE) swprintf_s(buf, L"Space");
            else if (*key == VK_TAB) swprintf_s(buf, L"Tab");
            else swprintf_s(buf, L"0x%X", *key);
            key_name = buf;
        }
        menu::canvas->k2_drawtext(menu::font, key_name, { kp.x + 6, kp.y + 2 }, fvector2d(0.68f, 0.68f), is_active ? text_white : text_gray, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        menu::offset_y += 24;
    }

    void SectionTitle(const wchar_t* title) {
        fvector2d sec_pos = fvector2d(pos.x + menu::offset_x, pos.y + menu::offset_y);
        menu::drawFilledRect({ sec_pos.x - 6, sec_pos.y - 3 }, 260.0f, 22.0f, bg_content);
        menu::canvas->k2_drawtext(menu::font, title, { sec_pos.x + 2, sec_pos.y }, fvector2d(0.85f, 0.85f), accent_primary, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        menu::offset_y += 30;
    }

    void TopTabButton(const wchar_t* label, int tab_id, bool active) {
        fvector2d btn_pos = fvector2d(pos.x + menu::offset_x, pos.y + menu::offset_y);
        float btn_w = 80.0f, btn_h = 38.0f;
        bool hovered = MouseInRegion(btn_pos, { btn_w, btn_h });
        if (active) {
            menu::drawFilledRect({ btn_pos.x, btn_pos.y + btn_h - 2 }, btn_w, 2.0f, accent_primary);
        }
        flinearcolor txt_col = active ? accent_primary : text_gray;
        if (hovered && !active) txt_col = text_white;
        float text_w = wcslen(label) * 7.0f;
        menu::canvas->k2_drawtext(menu::font, label, { btn_pos.x + (btn_w / 2) - (text_w / 2), btn_pos.y + 12 }, fvector2d(0.82f, 0.82f), txt_col, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        if (hovered && MouseClicked()) {
            tab = tab_id;
            ui::active_dropdown = -1;
            chat_input_active = false;
        }
        menu::offset_x += btn_w;
    }

    void SectionBackground(fvector2d sec_pos, fvector2d sec_size) {
        menu::drawFilledRect(sec_pos, sec_size.x, sec_size.y, bg_section);
        menu::drawFilledRect(sec_pos, sec_size.x, 1.0f, text_dark_gray);
        menu::drawFilledRect({ sec_pos.x, sec_pos.y + sec_size.y - 1 }, sec_size.x, 1.0f, text_dark_gray);
        menu::drawFilledRect(sec_pos, 1.0f, sec_size.y, text_dark_gray);
        menu::drawFilledRect({ sec_pos.x + sec_size.x - 1, sec_pos.y }, 1.0f, sec_size.y, text_dark_gray);
    }

    void RenderActiveDropdown() {
        if (ui::active_dropdown != -1 && ui::drop_target != nullptr) {
            float item_height = 22.0f;
            float total_height = (float)ui::drop_items.size() * item_height;
            menu::drawFilledRect(ui::drop_pos, ui::drop_width, total_height, bg_main);
            for (size_t i = 0; i < ui::drop_items.size(); i++) {
                fvector2d item_pos = { ui::drop_pos.x, ui::drop_pos.y + ((float)i * item_height) };
                bool hovered = MouseInRegion(item_pos, { ui::drop_width, item_height });
                if (hovered) {
                    menu::drawFilledRect(item_pos, ui::drop_width, item_height, bg_element);
                    if (MouseClicked()) {
                        *ui::drop_target = (int)i;
                        ui::active_dropdown = -1;
                    }
                }
                flinearcolor text_col = (*ui::drop_target == (int)i) ? accent_active : text_gray;
                if (hovered) text_col = text_white;
                menu::canvas->k2_drawtext(menu::font, ui::drop_items[i], { item_pos.x + 8, item_pos.y + 3 }, fvector2d(0.78f, 0.78f), text_col, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
            }
            menu::drawFilledRect(ui::drop_pos, ui::drop_width, 1.0f, text_dark_gray);
            menu::drawFilledRect({ ui::drop_pos.x, ui::drop_pos.y + total_height }, ui::drop_width, 1.0f, text_dark_gray);
            menu::drawFilledRect(ui::drop_pos, 1.0f, total_height, text_dark_gray);
            menu::drawFilledRect({ ui::drop_pos.x + ui::drop_width - 1, ui::drop_pos.y }, 1.0f, total_height, text_dark_gray);
        }
    }

    // RAINBOW WATERMARK
    void RenderWatermark(ucanvas* canvas) {
        if (!canvas) return;

        static int fps = 0;
        static int frameCount = 0;
        static auto lastTime = std::chrono::steady_clock::now();
        frameCount++;
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();
        if (elapsed >= 1000) {
            fps = frameCount;
            frameCount = 0;
            lastTime = currentTime;
        }

        int tickrate = 128;

        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm_time;
        localtime_s(&tm_time, &time);
        int hour = tm_time.tm_hour;
        int minute = tm_time.tm_min;
        int second = tm_time.tm_sec;
        const wchar_t* period = hour >= 12 ? L"PM" : L"AM";
        if (hour > 12) hour -= 12;
        if (hour == 0) hour = 12;
        int day = tm_time.tm_mday;
        int month = tm_time.tm_mon + 1;

        wchar_t line1[256];
        wchar_t line2[256];

        swprintf_s(line1, L"Heltra Software Private  %02d/%02d", month, day);
        swprintf_s(line2, L"FPS | %d  TICK | %d  %02d:%02d:%02d %s",
            fps, tickrate, hour, minute, second, period);

        flinearcolor rainbowColor = GetRainbow();
        flinearcolor whiteColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        flinearcolor shadowColor = { 0.0f, 0.0f, 0.0f, 0.0f };

        fvector2d wm_pos(35.0f, 70.0f);
        fvector2d normalScale(0.9f, 0.9f);
        fvector2d normalScale2(1.0f, 1.0f);
        fvector2d noOffset(0.0f, 0.0f);

        canvas->k2_drawtext(menu::font, fstring(line1), wm_pos, normalScale2, rainbowColor, 0.0f, shadowColor, noOffset, false, false, false, shadowColor);
        canvas->k2_drawtext(menu::font, fstring(line2), { wm_pos.x, wm_pos.y + 26.0f }, normalScale, whiteColor, 0.0f, shadowColor, noOffset, false, false, false, shadowColor);
    }

    bool Button(const wchar_t* label) {
        fvector2d btn_pos = fvector2d(pos.x + menu::offset_x, pos.y + menu::offset_y);
        float btn_w = 180.0f, btn_h = 28.0f;
        bool hovered = MouseInRegion(btn_pos, { btn_w, btn_h });
        menu::drawFilledRect(btn_pos, btn_w, btn_h, hovered ? bg_element : bg_main);
        menu::drawFilledRect(btn_pos, btn_w, 1.0f, accent_primary);
        menu::drawFilledRect({ btn_pos.x, btn_pos.y + btn_h - 1 }, btn_w, 1.0f, accent_primary);
        menu::drawFilledRect(btn_pos, 1.0f, btn_h, accent_primary);
        menu::drawFilledRect({ btn_pos.x + btn_w - 1, btn_pos.y }, 1.0f, btn_h, accent_primary);
        float text_w = wcslen(label) * 6.5f;
        menu::canvas->k2_drawtext(menu::font, label, { btn_pos.x + (btn_w / 2) - (text_w / 2), btn_pos.y + 6 }, fvector2d(0.72f, 0.72f), hovered ? accent_primary : text_gray, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
        bool clicked = hovered && MouseClicked();
        menu::offset_y += btn_h + 6;
        return clicked;
    }

    void Menu(ucanvas* canvas) {
        menu::SetupCanvas(canvas);
        menu::input::handle();
        RenderWatermark(canvas);
        if (GetAsyncKeyState(VK_INSERT) & 1) menu_open = !menu_open;
        if (menu::Window(L"heltra internal", &pos, { 600, 850 }, menu_open)) {
            menu::drawFilledRect(pos, 600, 850, bg_main);

            fvector2d mitamers_pos = { pos.x + 25, pos.y + 18 };
            menu::drawFilledRect({ mitamers_pos.x - 12, mitamers_pos.y + 2 }, 7, 7, accent_primary);
            menu::canvas->k2_drawtext(menu::font, L"Heltra", mitamers_pos, { 1.00f, 1.00f }, text_white, 0.0f, { 0,0,0,0 }, { 1,1 }, false, false, false, { 0,0,0,0 });
            menu::canvas->k2_drawtext(menu::font, L"25 May 2026", { pos.x + 90, mitamers_pos.y + 3 }, { 0.65f, 0.65f }, text_gray, 0.0f, { 0,0,0,0 }, { 1,1 }, false, false, false, { 0,0,0,0 });
            menu::canvas->k2_drawtext(menu::font, L"Welcome back,", { pos.x + 420, pos.y + 16 }, { 0.72f, 0.72f }, text_gray, 0.0f, { 0,0,0,0 }, { 1,1 }, false, false, false, { 0,0,0,0 });
            menu::drawFilledRect({ pos.x + 540, pos.y + 12 }, 40, 16, bg_element);
            menu::canvas->k2_drawtext(menu::font, L"BETA", { pos.x + 548, pos.y + 14 }, { 0.68f, 0.68f }, text_gray, 0.0f, { 0,0,0,0 }, { 1,1 }, false, false, false, { 0,0,0,0 });
            menu::drawFilledRect({ pos.x, pos.y + 44 }, 600, 1.0f, bg_content);

            menu::offset_x = 12; menu::offset_y = 45;
            TopTabButton(L"Aimbot", 0, tab == 0);
            TopTabButton(L"Anti Aim", 1, tab == 1);
            TopTabButton(L"Outline", 2, tab == 2);
            TopTabButton(L"Visuals", 3, tab == 3);
            TopTabButton(L"World", 4, tab == 4);
            TopTabButton(L"Misc", 5, tab == 5);
            TopTabButton(L"Config", 6, tab == 6);
            menu::drawFilledRect({ pos.x, pos.y + 85 }, 600, 1.0f, bg_content);
            menu::drawFilledRect({ pos.x + 300, pos.y + 98 }, 1.0f, 740.0f, bg_content);

            // ==================== AIMBOT ====================
            if (tab == 0) {
                menu::offset_x = 18; menu::offset_y = 108;
                SectionTitle(L"AIMBOT");
                NativeCheckbox(L"Enable Aim", &globals::aimbot::a1mbot);
                NativeCheckbox(L"Show target fov", &globals::aimbot::draw_f0v);
                NativeCheckbox(L"Recoil Control", &globals::aimbot::reco1l_contr0l);
                NativeCheckbox(L"No Spread", &globals::aimbot::nospread);
                NativeCheckbox(L"Automatic Fire", &globals::aimbot::auto_shot);
                NativeCheckbox(L"360 FOV", &globals::aimbot::enable_360_fov);
                NativeCheckbox(L"Resolver", &globals::aimbot::resolver_enabled);
                NativeCheckbox(L"360 FOV", &globals::aimbot::double_tap_enabled);
                NativeCheckbox(L"Prediction", &globals::aimbot::prediction);
                NativeCheckbox(L"Visibility Check", &globals::aimbot::v1sh_ch3ck);
                NativeCheckbox(L"Closest Bone target", &globals::aimbot::closest_bone_enabled);

                HotkeyLabeled(L"", &globals::aimbot::a1m_k3y);
                menu::offset_y += 8;
                SectionTitle(L"CONFIGURATION");
                NativeSliderFloat(L"smooth", &globals::aimbot::a1m_sm00th, 1.0f, 100.0f, "%.1f");
                NativeSliderFloat(L"fov", &globals::aimbot::a1m_f0v, 0.0f, 1100.0f, "%.0f");
                NativeCheckbox(L"Silent Aim", &globals::aimbot::silent);
                static bool dummy_closest_enemy = false;
                NativeCheckbox(L"Closest Enemy Target", &dummy_closest_enemy);
                std::vector<const wchar_t*> hitbox_items = { L"Head", L"Neck", L"Chest", L"Pelvis" };
                NativeCombobox(L"Hitbox Selector", &globals::aimbot::a1m_b0ne, hitbox_items, 1);
                menu::offset_x = 312; menu::offset_y = 108;
                SectionTitle(L"TARGET SELECTION");
                static bool dummy_target_line = false;
                static bool dummy_thru_smoke = false;
                static bool dummy_target_sel = false;
                NativeCheckbox(L"Target Line", &dummy_target_line);
                NativeCheckbox(L"Thru Smoke & Walls", &globals::aimbot::auto_wall);
                NativeCheckbox(L"Target Selector", &dummy_target_sel);
                std::vector<const wchar_t*> fire_modes = { L"Hold", L"Toggle" };
                static int dummy_autofire_mode = 0;
                NativeCombobox(L"Auto Fire (Automatic Mode)", &dummy_autofire_mode, fire_modes, 2);
                static float dummy_val1 = 150.0f;
                static float dummy_val2 = 0.0f;
                NativeSliderFloat(L"Default its 100", &dummy_val1, 0.0f, 300.0f, "%.1f");
                NativeSliderFloat(L"Default its 20", &dummy_val2, 0.0f, 100.0f, "%.1f");
                menu::offset_y += 8;
                SectionTitle(L"OTHER");
                static bool dummy_hit_priority = false;
                static float dummy_min_dmg = 0.0f;
                static float dummy_max_dst = 100000.0f;
                NativeCheckbox(L"Hit Priority", &dummy_hit_priority);
                NativeSliderFloat(L"Minimum Damage", &dummy_min_dmg, 0.0f, 100.0f, "%.0f");
                NativeSliderFloat(L"Max Aim Distance", &dummy_max_dst, 0.0f, 100000.0f, "%.0f");
                NativeSliderFloat(L"Quick Stop Default its 25", &globals::aimbot::auto_shot_delay_ms, 0.0f, 300.0f, "%.0f ms");
            }

            // ==================== ANTI AIM ====================
            else if (tab == 1) {
                menu::offset_x = 18; menu::offset_y = 108;
                SectionTitle(L"ANTI AIM");
                NativeCheckbox(L"Enable Anti Aim", &globals::misc::SpinBot);
                NativeCheckbox(L"Fast Duck", &globals::misc::fastcrouch);
                NativeCheckbox(L"Desync Move", &globals::misc::aa_desync);
                NativeSliderFloat(L"Spin Speed", &globals::misc::spinvalue, 1, 140, "%.1f");
                NativeSliderFloat(L"Rotation", &globals::misc::yaw_add, 0, 275, "%.0f");
                NativeCombobox(L"Pitch Mode", &globals::misc::pitch_mode, { L"Normal", L"Random", L"Backwards", L"3-Way" }, 10);
                menu::offset_y += 4;
                SectionTitle(L"Style");
                NativeCheckbox(L"Spin", &globals::misc::aa_spin);
                NativeCheckbox(L"Jitter", &globals::misc::aa_jitter);
                NativeCheckbox(L"Backwards", &globals::misc::aa_backwards);
                NativeCheckbox(L"3-Way", &globals::misc::aa_threeway);
                NativeCheckbox(L"Atomic AA", &globals::misc::aa_atomic);
                NativeCheckbox(L"Pred Breaker", &globals::misc::aa_prediction_breaker);
                menu::offset_y += 4;
                SectionTitle(L"Direction Keys");
                HotkeyLabeled(L"Right Key", &globals::misc::snap_right_key);
                HotkeyLabeled(L"Left Key", &globals::misc::snap_left_key);
                HotkeyLabeled(L"Back Key", &globals::misc::snap_back_key);
            }

            // ==================== OUTLINE ====================
            else if (tab == 2) {
                menu::offset_x = 18; menu::offset_y = 108;
                SectionTitle(L"OUTLINE");
                NativeCheckbox(L"Enable Outline", &enable_outline);
                NativeSliderFloat(L"Outline Thickness", &outline_thickness, 1.0f, 5.0f, "%.1f");
                NativeCheckbox(L"Glow Effect", &glow_effect);
                NativeSliderFloat(L"Glow Intensity", &glow_intensity, 0.0f, 1.0f, "%.2f");
                menu::offset_y += 8;
                SectionTitle(L"OUTLINE FILTERS");
                NativeCheckbox(L"Enemies Only", &enemies_only);
                NativeCheckbox(L"Visible Only", &visible_only);
                NativeCheckbox(L"Weapon Outline", &weapon_outline);
                NativeSliderFloat(L"Max Distance", &max_distance, 0.0f, 10000.0f, "%.0f");
                menu::offset_x = 312; menu::offset_y = 108;
                SectionTitle(L"HAND & CHAMS");
                NativeCheckbox(L"Material Hand", &globals::visuals::safe_hand_chams);
                if (globals::visuals::safe_hand_chams) {
                    menu::Combobox(fvector2d(220, 25), &globals::visuals::typehand, L"Translucent", L"Vampire", L"Gem", L"Glass", L"Sakura", L"Arcade Yellow", L"Arcade Red", L"Arcade Blue", L"Afterglow", NULL);
                }
                NativeCheckbox(L"X Hand Chams", &globals::chams::hands_galaxy_enabled);
                NativeCheckbox(L"X Self Chams", &globals::chams::self_galaxy_enabled);
                NativeCheckbox(L"Hand Wireframe", &globals::misc::HandWire);
                NativeCheckbox(L"Self Wireframe", &globals::misc::self_wireframe);
                NativeCheckbox(L"Mosca Wireframe", &globals::visuals::moscawireframe_enabled);
                NativeCheckbox(L"Wall Only Chams", &wall_only_chams);
                NativeCheckbox(L"Wall Only Rainbow", &wall_only_rainbow);
                NativeCheckbox(L"Gun Chams", &gun_chams);
                NativeCheckbox(L"Wireframe Gun", &wireframe_gun);
                NativeCheckbox(L"Enemy Fresnel", &enemy_fresnel);
                NativeCheckbox(L"Spike Chams", &spike_chams);
                NativeCheckbox(L"Custom Skin Texture", &custom_skin_texture);
                NativeCheckbox(L"Custom Sky Texture", &custom_sky_texture);
            }

            // ==================== VISUALS ====================
            else if (tab == 3) {
                menu::offset_x = 18; menu::offset_y = 108;
                SectionTitle(L"VISUALS");
                NativeCheckbox(L"Ignore Dormants", &ignore_dormants);
                NativeCheckbox(L"Visibility Check", &globals::visuals::vischeck);
                NativeCheckbox(L"3D Box", &globals::visuals::box3d);
                NativeCheckbox(L"2D Box", &globals::visuals::box2d);
                NativeCheckbox(L"Corner Box", &globals::visuals::corner);
                NativeCheckbox(L"Filled Box", &filled_box);
                NativeCheckbox(L"Skeleton", &globals::visuals::sk3let0n);

                menu::offset_y += 4;
                SectionTitle(L"VISUALS MISC");
                NativeCheckbox(L"Distance", &globals::visuals::dstc);
                NativeCheckbox(L"Snapline", &globals::visuals::snapl1ne);
                NativeCheckbox(L"Snapline (FOV Based)", &snapline_fov);
                NativeCheckbox(L"Head ESP", &globals::visuals::headb0x);
                NativeCheckbox(L"Health Bar", &globals::visuals::h3althbar);
                NativeCheckbox(L"Agent Icon", &agent_icon);
                NativeCheckbox(L"Weapon Esp", &weapon_esp);
                NativeCheckbox(L"3p Wukong", &wukong_3p);
                NativeCheckbox(L"China Hat Enemy", &globals::visuals::chinahat);
                NativeCheckbox(L"China Hat Self", &globals::visuals::partyhat_self);
                NativeCheckbox(L"Bullet Tracers", &globals::misc::bullet_tracers);
                menu::offset_x = 312; menu::offset_y = 108;
                SectionTitle(L"PLAYER INFO");
                NativeCheckbox(L"Radar Map", &radar_map);
                NativeCheckbox(L"Platform Info", &platform_info);
                NativeCheckbox(L"Agent Name", &agent_name);
                NativeCheckbox(L"Player Name", &player_name);
                NativeCheckbox(L"Gun on ground", &gun_on_ground);
                NativeCheckbox(L"Recoil crosshair", &recoil_crosshair);
                NativeCheckbox(L"Ping ESP", &ping_esp);
                NativeCheckbox(L"Rank Info", &rank_info);
                NativeCheckbox(L"Rank Label", &rank_label);
                NativeCheckbox(L"Damage Numbers", &globals::misc::damage_numbers);
                menu::offset_y += 4;
                SectionTitle(L"ABILITIES");
                NativeCheckbox(L"Abilities", &abilities);
                NativeCheckbox(L"Bomb Info", &bomb_info);
            }

            // ==================== WORLD ====================
            else if (tab == 4) {
                menu::offset_x = 18; menu::offset_y = 108;
                SectionTitle(L"WORLD");
                NativeCheckbox(L"Skybox", &globals::misc::skybox);
                NativeCheckbox(L"Rainbow Skybox", &globals::misc::skyboxrgb);
                NativeSliderFloat(L"Stars", &globals::misc::StarsBrightness, 0, 2500, "%.0f");
                NativeSliderFloat(L"Sky R", &globals::misc::SkySharedR, 0, 1, "%.2f");
                NativeSliderFloat(L"Sky G", &globals::misc::SkySharedG, 0, 1, "%.2f");
                NativeSliderFloat(L"Sky B", &globals::misc::SkySharedB, 0, 1, "%.2f");
                NativeCheckbox(L"Disable Vignetta", &disable_vignetta);
                NativeCheckbox(L"World Fog", &world_fog);
                menu::offset_y += 4;
                SectionTitle(L"TRAPS");
                NativeCheckbox(L"Spike ESP", &spike_esp);
                NativeCheckbox(L"Spike Timer", &spike_timer);
                NativeCheckbox(L"World ESP", &world_esp);
                NativeCheckbox(L"Cypher Traps", &cypher_traps);
                NativeCheckbox(L"Gadgets", &gadgets);
                menu::offset_x = 312; menu::offset_y = 108;
                SectionTitle(L"SKYBOX PRESETS");
                std::vector<const wchar_t*> presets = { L"Default", L"Night", L"Sunset" };
                NativeCombobox(L"", &skybox_preset, presets, 10);
                NativeColorPicker(L"Fog Color", { 0.65f, 0.25f, 0.85f, 1.0f });
                NativeSliderFloat(L"FogCutoffDistance", &fog_cutoff1, 0.0f, 500.0f, "%.2f");
                NativeSliderFloat(L"FogCutoffDistance", &fog_cutoff2, 0.0f, 10.0f, "%.2f");
                NativeSliderFloat(L"FogCutoffDistance", &fog_cutoff3, 0.0f, 500.0f, "%.2f");
                NativeSliderFloat(L"FogHeightFalloff", &fog_height, 0.0f, 1.0f, "%.2f");
                NativeSliderFloat(L"FogStartDistance", &fog_start, 0.0f, 100.0f, "%.2f");
                NativeSliderFloat(L"FogMaxOpacity", &fog_max, 0.0f, 1.0f, "%.2f");
                NativeSliderFloat(L"Sun Height", &sun_height, 0.0f, 10.0f, "%.2f");
                NativeSliderFloat(L"Noise Power 1", &noise1, 0.0f, 5.0f, "%.2f");
                NativeSliderFloat(L"Noise Power 2", &noise2, 0.0f, 5.0f, "%.2f");
            }

            // ==================== MISC ====================
            else if (tab == 5) {
                menu::offset_x = 18; menu::offset_y = 108;
                SectionTitle(L"SKINS");
                NativeCheckbox(L"Apply custom skins", &globals::misc::custom_vandal_enabled);
                NativeCheckbox(L"Unlock all", &globals::misc::sk1n_chang3r);
                NativeCheckbox(L"Enable Gun Buddy", &globals::buddy::enabled);
                NativeCheckbox(L"Gun Materials", &gun_materials);

                menu::offset_y += 8;
                SectionTitle(L"MISC");
                NativeCheckbox(L"Shooter Trail Esp", &shooter_trail);
                NativeCheckbox(L"Advanced Resolver", &advanced_resolver);
                NativeCheckbox(L"View Model Changer", &globals::misc::ViewModelChanger);
                NativeCheckbox(L"Big Gun", &big_gun);
                NativeCheckbox(L"Self Resizer", &self_resizer);
                NativeCheckbox(L"Finisher", &globals::misc::finisher);
                NativeCheckbox(L"Kill Sound", &globals::misc::killsound);
                NativeCheckbox(L"Kill Say", &globals::misc::killsays);
                NativeCheckbox(L"Dynamic Hitsound", &dynamic_hitsound);
                NativeCheckbox(L"Chat Spammer F4", &globals::misc::killsays);

                menu::canvas->k2_drawtext(menu::font, L"Chat Message:", { pos.x + menu::offset_x, pos.y + menu::offset_y }, { 0.80f, 0.80f }, text_white, 0.0f, { 0,0,0,0 }, { 1,1 }, false, false, false, { 0,0,0,0 });
                menu::offset_y += 20;
                NativeInputBox(L"", chat_message_buffer, 256);

                menu::offset_x = 312; menu::offset_y = 108;
                SectionTitle(L"EXPLOIT");
                NativeCheckbox(L"Apply Texture", &apply_texture);
                NativeCheckbox(L"Remove Scope", &remove_scope);
                NativeCheckbox(L"Remove flash", &remove_flash);
                NativeCheckbox(L"Bunny hop", &globals::misc::bhop);
                NativeCheckbox(L"Anti Flash", &globals::misc::antiflash);
                NativeCheckbox(L"Big Gun", &globals::misc::BigGun);
                NativeCheckbox(L"Big Self", &globals::misc::BigSelf);
                NativeCheckbox(L"Custom Gun Texture", &globals::misc::customgun);
                NativeCheckbox(L"Custom Hand Texture", &globals::misc::customhand);
                NativeCheckbox(L"Fast crouch", &globals::misc::fastcrouch);
                NativeCheckbox(L"Skip Tutorial", &globals::misc::sk1ptut0rial);

                NativeSliderFloat(L"Big Gun Scale", &globals::misc::BigGunFloat, 1.0f, 5.0f, "%.2f");
                NativeSliderFloat(L"Big Self Scale", &globals::misc::BigSelfFloat, 1.0f, 5.0f, "%.2f");


                menu::offset_y += 8;
                SectionTitle(L"FUTURE");
                NativeCheckbox(L"Third Person (P)", &globals::misc::tperson);
                NativeCheckbox(L"Aspect Ratio", &globals::misc::aspectratio);
                NativeCheckbox(L"Fov Changer", &globals::misc::fovchanger);
                NativeSliderFloat(L"TP Distance", &globals::misc::PlayerDistance, 100, 1000, "%.0f");
                NativeSliderFloat(L"Aspect ratio", &globals::misc::aspectfloat, 1.0f, 20.0f, "%.0f");
                NativeSliderFloat(L"fov", &globals::misc::fovchangur, 60.0f, 200.0f, "%.0f");
            }

            // ==================== CONFIG ====================
            else if (tab == 6) {
                menu::offset_x = 18; menu::offset_y = 108;
                SectionTitle(L"CONFIG MANAGEMENT");
                if (Button(L"Save Config")) {
                    std::filesystem::create_directories("C:/heltra");
                    Config->SaveSettings("C:/heltra/config.json");
                }
                menu::offset_y += 10;
                if (Button(L"Load Config")) {
                    Config->LoadSettings("C:/heltra/config.json");
                }
            }

            RenderActiveDropdown();
            fvector2d cp = menu::CursorPos();
            menu::drawFilledRect({ cp.x - 2, cp.y - 2 }, 4, 4, accent_active);
        }
        menu::Render();
    }
}