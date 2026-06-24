#include "config.h"
#include "../offsets.hpp"
#include <ShlObj.h>
#include <filesystem>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

CConfig* Config = new CConfig();

void CConfig::AddItem(void* pointer, const char* name, const std::string& type) {
    items.push_back(new C_ConfigItem(std::string(name), pointer, type));
}

void CConfig::setup_item(int* pointer, int value, const std::string& name)
{
    AddItem(pointer, name.c_str(), ("int"));
    *pointer = value;
}

void CConfig::setup_item(bool* pointer, bool value, const std::string& name)
{
    AddItem(pointer, name.c_str(), ("bool"));
    *pointer = value;
}

void CConfig::setup_item(float* pointer, float value, const std::string& name)
{
    AddItem(pointer, name.c_str(), ("float"));
    *pointer = value;
}

void CConfig::setup_item(double* pointer, double value, const std::string& name)
{
    AddItem(pointer, name.c_str(), ("double"));
    *pointer = value;
}

void CConfig::setup_item(std::vector< int >* pointer, int size, const std::string& name)
{
    AddItem(pointer, name.c_str(), ("vector<int>"));
    pointer->clear();
    for (int i = 0; i < size; i++)
        pointer->push_back(FALSE);
}

void CConfig::setup_item(std::vector< std::string >* pointer, const std::string& name)
{
    AddItem(pointer, name.c_str(), ("vector<string>"));
}

void CConfig::setup_item(std::string* pointer, const std::string& value, const std::string& name)
{
    AddItem(pointer, name.c_str(), ("string"));
    *pointer = value;
}



void CConfig::SetupAimbot() {
    // AIMBOT TAB - Main subtab
    setup_item(&globals::aimbot::a1mbot, false, ("aimbot_enabled"));
    setup_item(&globals::aimbot::auto_wall, false, ("aimbot_autowall"));
    setup_item(&globals::aimbot::silent, false, ("aimbot_silent"));
    setup_item(&globals::aimbot::v1sh_ch3ck, false, ("aimbot_visible_check"));
    setup_item(&globals::aimbot::reco1l_contr0l, false, ("aimbot_recoil"));
    setup_item(&globals::aimbot::nospread, false, ("aimbot_nospread"));
    setup_item(&globals::aimbot::draw_f0v, false, ("aimbot_draw_fov"));
    setup_item(&globals::aimbot::a1m_f0v, 70.0f, ("aimbot_fov"));
    setup_item(&globals::aimbot::a1m_sm00th, 15.0f, ("aimbot_smooth"));
    setup_item(&globals::aimbot::a1m_b0ne, 0, ("aimbot_bone"));
    setup_item(&globals::aimbot::a1m_k3y, 0, ("aimbot_key"));

    // AIMBOT TAB - Auto Shot subtab
    setup_item(&globals::aimbot::auto_shot, false, ("aimbot_auto_shot"));
    setup_item(&globals::aimbot::auto_shot_hold_key, false, ("aimbot_auto_shot_hold_key"));

    // AIMBOT TAB - Prediction
    setup_item(&globals::aimbot::prediction, false, ("aimbot_prediction"));
}

void CConfig::SetupVisuals() {
    // VISUAL TAB - ESP subtab
    setup_item(&globals::visuals::box2d, false, ("visuals_box2d"));
    setup_item(&globals::misc::Wireframe, false, ("misc_wireframe"));
    setup_item(&globals::misc::self_wireframe, false, ("misc_self_wireframe"));
    setup_item(&globals::visuals::box3d, false, ("visuals_box3d"));
    setup_item(&globals::misc::HandWire, false, ("misc_handwire"));
    setup_item(&globals::visuals::safe_hand_chams, false, ("visuals_hand_material"));
    setup_item(&globals::visuals::corner, false, ("visuals_corner"));
    setup_item(&globals::misc::WireframeGun, false, ("misc_wireframe_gun"));
    setup_item(&globals::visuals::gunmaterial1p, false, ("visuals_gunmaterial1p"));
    setup_item(&globals::visuals::vischeck, false, ("visuals_vischeck"));
    setup_item(&globals::visuals::gunmaterial3p, false, ("visuals_gunmaterial3p"));
    setup_item(&globals::misc::bullettracer, false, ("misc_bullettracer"));
    setup_item(&globals::visuals::headb0x, false, ("visuals_headbox"));
    setup_item(&globals::misc::playerchamsself, false, ("misc_player_chams_self"));
    setup_item(&globals::visuals::chinahat, false, ("visuals_chinahat"));
    setup_item(&globals::visuals::b00ms, false, ("visuals_agent_icon"));
    setup_item(&globals::visuals::partyhat_self, false, ("visuals_partyhat_self"));
    setup_item(&globals::visuals::spike, false, ("visuals_spike"));
    setup_item(&globals::visuals::h3althbar, false, ("visuals_healthbar"));
    setup_item(&globals::visuals::snapl1ne, false, ("visuals_snapline"));
    setup_item(&globals::visuals::sk3let0n, false, ("visuals_skeleton"));
    setup_item(&globals::misc::gun_3p_wireframe, false, ("misc_gun_3p_wireframe"));
    setup_item(&globals::visuals::b11ms, false, ("visuals_weapon_info"));
    setup_item(&globals::visuals::dstc, false, ("visuals_distance"));

    // VISUAL TAB - Materials subtab
    setup_item(&globals::visuals::typehand, 0, ("visuals_typehand"));
    setup_item(&globals::visuals::typegun1p, 0, ("visuals_typegun1p"));
    setup_item(&globals::visuals::typegun3d, 0, ("visuals_typegun3d"));
    setup_item(&globals::misc::chams_material_index, 0, ("misc_chams_material_index"));

    // VISUAL TAB - World subtab
    setup_item(&globals::misc::skybox, false, ("misc_skybox"));
    setup_item(&globals::misc::skyboxrgb, false, ("misc_skybox_rgb"));
    setup_item(&globals::misc::StarsBrightness, 1.0, ("misc_stars_brightness"));
    setup_item(&globals::misc::CloudSpeed, 1.0, ("misc_cloud_speed"));
    setup_item(&globals::misc::CloudOpacity, 1.0, ("misc_cloud_opacity"));
}

void CConfig::SetupChams() {
    // CHAMS TAB - Outline Chams subtab
    setup_item(&globals::chams::outline_enabled, false, ("chams_outline_enabled"));
    setup_item(&globals::chams::hand_outline_enabled, false, ("chams_hand_outline_enabled"));
    setup_item(&globals::chams::self_chams, false, ("chams_self_chams"));
    setup_item(&globals::chams::gun_outline3P_enabled, false, ("chams_gun3P_outline_enabled"));
    setup_item(&globals::chams::gun_outline1P_enabled, false, ("chams_gun1P_outline_enabled"));

    setup_item(&globals::chams::intensityvisibleoutline, 50.0f, ("chams_intensity_visible"));
    setup_item(&globals::chams::intensityinvisbleoutline, 50.0f, ("chams_intensity_invisible"));
    setup_item(&globals::chams::outlinetype, 0, ("chams_outline_type"));
    setup_item(&globals::chams::visible_outline_preset, 0, ("chams_visible_outline_preset"));
    setup_item(&globals::chams::invisible_outline_preset, 0, ("chams_invisible_outline_preset"));

    // CHAMS TAB - Visible Chams subtab
    setup_item(&globals::chams::rchamsespall, false, ("chams_rainbow_all"));
    setup_item(&globals::chams::Glow, 1.0f, ("chams_glow"));

    // CHAMS TAB - Invisible Chams subtab
    setup_item(&globals::chams::rchamsesp, false, ("chams_rainbow"));
    setup_item(&globals::chams::Glowvni, 1.0f, ("chams_glow_invisible"));

    // CHAMS TAB - Hand Chams subtab
    setup_item(&globals::misc::materials, 0, ("misc_materials"));
    setup_item(&globals::misc::handchams, false, ("misc_handchams"));
    setup_item(&globals::misc::HandChamsRbg, false, ("misc_handchams_rgb"));
    setup_item(&globals::misc::handbright, 1.0f, ("misc_handbright"));
    setup_item(&globals::misc::handglow, false, ("misc_handglow"));
}

void CConfig::SetupExploits() {
    // EXPLOIT TAB - General subtab
    setup_item(&globals::misc::bhop, false, ("misc_bhop"));
    setup_item(&globals::misc::fastcrouch, false, ("misc_fastcrouch"));
    setup_item(&globals::misc::fovchanger, false, ("misc_fov_changer"));
    setup_item(&globals::misc::fovchangur, 105.0f, ("misc_fov_value"));
    setup_item(&globals::misc::aspectratio, false, ("misc_aspectratio"));
    setup_item(&globals::misc::aspectfloat, 1.0f, ("misc_aspect_float"));
    setup_item(&globals::misc::PlayerDistance, 100.0f, ("misc_player_distance"));
    setup_item(&globals::misc::tperson, false, ("misc_thirdperson"));
    setup_item(&globals::misc::custom_vandal_enabled, false, ("misc_custom_vandal_enabled"));
    setup_item(&globals::misc::custom_text_enabled, false, ("misc_custom_text_enabled"));
    setup_item(&globals::lineup::enabled, false, ("lineup_enabled"));
    setup_item(&globals::lineup::show_guides, true, ("lineup_guides"));
    setup_item(&globals::lineup::auto_aim, false, ("lineup_auto_aim"));
    setup_item(&globals::lineup::projectile_velocity, 2000.0f, ("lineup_velocity"));
    setup_item(&globals::lineup::gravity_scale, 1.0f, ("lineup_gravity"));
    setup_item(&globals::lineup::render_distance, 5000.0f, ("lineup_render_distance"));
    
    // AUTO PEEK
    setup_item(&globals::autopeek::enabled, false, ("autopeek_enabled"));
    setup_item(&globals::autopeek::peek_key, 0, ("autopeek_key"));
    setup_item(&globals::autopeek::draw_position, true, ("autopeek_draw"));
    
    // EXPLOITS
   // setup_item(&globals::misc::spam, false, ("misc_spam"));
    setup_item(&globals::misc::BigSelfFloat, 1.0f, ("misc_bigself_float"));
    setup_item(&globals::misc::BigGun, false, ("misc_biggun"));
    setup_item(&globals::misc::BigGunFloat, 1.0f, ("misc_biggun_float"));
    setup_item(&globals::misc::BigGun3D, false, ("misc_biggun3d"));
    setup_item(&globals::misc::BigGun3DWireframe, false, ("misc_biggun3d_wire"));
    setup_item(&globals::misc::customgun, false, ("misc_custom_gun"));
    setup_item(&globals::misc::customhand, false, ("misc_custom_hand"));

    // EXPLOIT TAB - Anti-Aim subtab
    setup_item(&globals::misc::SpinBot, false, ("misc_anti_aim"));
  /*  setup_item(&globals::misc::anti_aim_pitch, 0, ("misc_anti_aim_pitch"));
    setup_item(&globals::misc::anti_aim_yaw, 0, ("misc_anti_aim_yaw"));*/

    // EXPLOIT TAB - Snap Keys subtab
    setup_item(&globals::misc::snap_left_key, 0, ("misc_snap_left_key"));
    setup_item(&globals::misc::snap_right_key, 0, ("misc_snap_right_key"));
    setup_item(&globals::misc::snap_back_key, 0, ("misc_snap_back_key"));
}

void CConfig::SetupMisc() {
    // MISC TAB - General subtab
    setup_item(&globals::Watermark, true, ("watermark_enabled"));

    // MISC TAB - Gun Buddy subtab
    setup_item(&globals::buddy::enabled, false, ("buddy_enabled"));
    setup_item(&globals::buddy::index, 0, ("buddy_index"));
    setup_item(&globals::misc::killsays, false, ("misc_killsays"));
    setup_item(&globals::misc::killsound, false, ("misc_killsound"));
    setup_item(&globals::misc::chat_spammer, false, ("misc_chat_spammer"));
    setup_item(&globals::misc::spam_key, 0, ("misc_spam_key"));
    setup_item(&globals::misc::chat_message, std::string(""), ("misc_chat_message"));

    // MISC - Custom Skin
    setup_item(&globals::misc::sk1n_chang3r, false, ("misc_skin_changer"));
    setup_item(&globals::misc::custom_classic_enabled, false, ("misc_custom_classic_enabled"));
    setup_item(&globals::misc::custom_knife_enabled, false, ("misc_custom_knife_enabled"));
    setup_item(&globals::misc::finisher, false, ("misc_finisher"));

    // MISC - Other toggles
    setup_item(&globals::misc::antiflash, false, ("misc_antiflash"));
    setup_item(&globals::misc::no_smoke, false, ("misc_no_smoke"));
    setup_item(&globals::misc::BigSelf, false, ("misc_bigself"));
    setup_item(&globals::misc::bEnableVolumetricFog, false, ("misc_volumetric_fog"));

    // ANTI-AIM settings
    setup_item(&globals::misc::aa_spin, false, ("misc_aa_spin"));
    setup_item(&globals::misc::aa_backwards, false, ("misc_aa_backwards"));
    setup_item(&globals::misc::aa_jitter, false, ("misc_aa_jitter"));
    setup_item(&globals::misc::aa_desync, false, ("misc_aa_desync"));
    setup_item(&globals::misc::aa_atomic, false, ("misc_aa_atomic"));
    setup_item(&globals::misc::aa_threeway, false, ("misc_aa_threeway"));
    setup_item(&globals::misc::aa_prediction_breaker, false, ("misc_aa_prediction_breaker"));
    setup_item(&globals::misc::jitter_enabled, false, ("misc_jitter_enabled"));
    setup_item(&globals::misc::jitter_range, 0.0f, ("misc_jitter_range"));
    setup_item(&globals::misc::desync_range, 0.0f, ("misc_desync_range"));
    setup_item(&globals::misc::pitch_mode, 0, ("misc_pitch_mode"));
    setup_item(&globals::misc::pitch_value, 0.0f, ("misc_pitch_value"));
    setup_item(&globals::misc::yaw_add, 0.0f, ("misc_yaw_add"));
    setup_item(&globals::misc::atomic_mode, 0, ("misc_atomic_mode"));
    setup_item(&globals::misc::atomic_speed, 1.0f, ("misc_atomic_speed"));
    setup_item(&globals::misc::breaker_intensity, 0.0f, ("misc_breaker_intensity"));
    setup_item(&globals::misc::spinvalue, 0.0f, ("misc_spinvalue"));
    setup_item(&globals::misc::only_last_kill, false, ("misc_only_last_kill"));

    // AIMBOT - missing
    setup_item(&globals::aimbot::enable_360_fov, false, ("aimbot_360_fov"));

    // CHAMS - Galaxy toggles
    setup_item(&globals::chams::enemy_galaxy_enabled, false, ("chams_enemy_galaxy"));
    setup_item(&globals::chams::weapon_galaxy_enabled, false, ("chams_gun1p_galaxy"));
    setup_item(&globals::chams::hands_galaxy_enabled, false, ("chams_hand_galaxy"));
    setup_item(&globals::chams::self_galaxy_enabled, false, ("chams_self_galaxy"));

    // MISC - Fog
    setup_item(&globals::misc::Fog, false, ("misc_fog_enabled"));
    setup_item(&globals::misc::FogRGB, false, ("misc_fog_rgb"));
    setup_item(&globals::misc::FogDensity, 0.0f, ("misc_fog_density"));
    setup_item(&globals::misc::FogHeightFalloff, 0.0f, ("misc_fog_height_falloff"));
    setup_item(&globals::misc::FogMaxOpacity, 1.0f, ("misc_fog_max_opacity"));
    setup_item(&globals::misc::FogStartDistance, 0.0f, ("misc_fog_start_distance"));
    setup_item(&globals::misc::FogCutoffDistance, 0.0f, ("misc_fog_cutoff_distance"));
    setup_item(&globals::misc::FogColor.r, 1.0f, ("misc_fog_color_r"));
    setup_item(&globals::misc::FogColor.g, 1.0f, ("misc_fog_color_g"));
    setup_item(&globals::misc::FogColor.b, 1.0f, ("misc_fog_color_b"));
    setup_item(&globals::misc::VolumetricFogDistance, 0.0f, ("misc_volumetric_fog_dist"));

    // MISC - Sky
    setup_item(&globals::misc::SkySharedR, 1.0f, ("misc_sky_r"));
    setup_item(&globals::misc::SkySharedG, 1.0f, ("misc_sky_g"));
    setup_item(&globals::misc::SkySharedB, 1.0f, ("misc_sky_b"));

    // MISC - Other missing
    setup_item(&globals::misc::bullet_tracers, false, ("misc_bullet_tracers"));
    setup_item(&globals::misc::bullet_spawn, false, ("misc_bullet_spawn"));
    setup_item(&globals::misc::bullet_spawn_amount, 1, ("misc_bullet_spawn_amount"));
    setup_item(&globals::misc::damage_numbers, false, ("misc_damage_numbers"));
    setup_item(&globals::misc::ViewModelChanger, false, ("misc_view_model_changer"));
    setup_item(&globals::misc::hellfiremode, false, ("misc_hellfire_mode"));
    setup_item(&globals::misc::lightningmode, false, ("misc_lightning_mode"));

    // VISUALS - missing
    setup_item(&globals::visuals::crystal_chams_preset, 0, ("visuals_crystal_preset"));
}

void CConfig::Initialize() {
    SetupAimbot();
    SetupVisuals();
    SetupChams();
    SetupExploits();
    SetupMisc();
}

void CConfig::SaveSettings(const std::string& szIniFile) {
    std::ofstream file(szIniFile);

    if (!file.is_open()) {
        MessageBoxA(NULL, ("Cannot open file: " + szIniFile).c_str(), "Error", MB_OK);
        return;
    }

    file << "{\n";

    bool first = true;
    for (auto item : items) {
        if (!first) file << ",\n";
        first = false;

        file << "  \"" << item->name << "\": ";

        if (item->type == "bool") {
            file << (*(bool*)item->pointer ? "true" : "false");
        }
        else if (item->type == "int") {
            file << *(int*)item->pointer;
        }
        else if (item->type == "float") {
            file << std::fixed << std::setprecision(6) << *(float*)item->pointer;
        }
        else if (item->type == "double") {
            file << std::fixed << std::setprecision(6) << *(double*)item->pointer;
        }
        else if (item->type == "string") {
            file << "\"" << *(std::string*)item->pointer << "\"";
        }
    }

    file << "\n}";
    file.close();
}

void CConfig::LoadSettings(const std::string& szIniFile) {
    std::ifstream file(szIniFile);

    if (!file.is_open()) {
        MessageBoxA(NULL, ("Cannot open file: " + szIniFile).c_str(), "Error", MB_OK);
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    file.close();

    for (auto item : items) {
        std::string search = "\"" + item->name + "\":";
        size_t pos = content.find(search);

        if (pos != std::string::npos) {
            pos += search.length();

            // Skip whitespace
            while (pos < content.length() && (content[pos] == ' ' || content[pos] == '\t')) pos++;

            if (item->type == "bool") {
                if (content.substr(pos, 4) == "true") {
                    *(bool*)item->pointer = true;
                }
                else if (content.substr(pos, 5) == "false") {
                    *(bool*)item->pointer = false;
                }
            }
            else if (item->type == "int") {
                std::string value;
                while (pos < content.length() && (isdigit(content[pos]) || content[pos] == '-')) {
                    value += content[pos++];
                }
                if (!value.empty()) {
                    *(int*)item->pointer = std::stoi(value);
                }
            }
            else if (item->type == "float") {
                std::string value;
                while (pos < content.length() && (isdigit(content[pos]) || content[pos] == '.' || content[pos] == '-')) {
                    value += content[pos++];
                }
                if (!value.empty()) {
                    *(float*)item->pointer = std::stof(value);
                }
            }
            else if (item->type == "double") {
                std::string value;
                while (pos < content.length() && (isdigit(content[pos]) || content[pos] == '.' || content[pos] == '-')) {
                    value += content[pos++];
                }
                if (!value.empty()) {
                    *(double*)item->pointer = std::stod(value);
                }
            }
        }
    }
}