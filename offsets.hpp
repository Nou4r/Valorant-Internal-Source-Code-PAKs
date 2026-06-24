#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdio>
#include "structs.hpp"

namespace outline_menu {
    static bool showVisibleColors = false;
    static bool showInvisibleColors = false;
    static bool showVisibleCenter = false;
    static bool showVisibleInner = false;
    static bool showVisibleOuter = false;
    static bool showInvisibleCenter = false;
    static bool showInvisibleInner = false;
    static bool showInvisibleOuter = false;
}

namespace AntiAim {
    static float jitter_speed = 15.0f;
    static float micro_jitter_amount = 2.0f;
    static float desync_offset = 0.0f;
    static int tick_counter = 0;
    static float last_real_yaw = 0.0f;
    static float fake_yaw_offset = 0.0f;
    static bool direction_switch = false;
    static float smooth_transition = 0.0f;

    // Variables pour le 3-way jitter
    static int three_way_state = 0;
    static float three_way_angles[3] = { -90.0f, 0.0f, 90.0f };

    // Variables pour le jitter avancé
    static float jitter_base = 0.0f;
    static int jitter_tick = 0;

    // Variables pour les patterns complexes
    static float pattern_time = 0.0f;
    static int pattern_state = 0;
}

namespace offsets
{
    // === EN GÜNCEL (FİX) OFFSETLER ===
    constexpr uint64_t GWorld = 0xC2DB4F0;
    constexpr uint64_t State = 0xC2DB4F0;
    constexpr uint64_t uworld_state = 0xC2DB4F0;
    constexpr uint64_t PersistentLevel = 0x38;
    constexpr uint64_t GameState = 0x178;

    constexpr uint64_t ObjectArray = 0xC357290;
    constexpr uint64_t FnamePool = 0xC480F80;
    constexpr uint64_t FName = 0xE17570;

    constexpr uint64_t process_event = 0x1BEE560;
    constexpr uint64_t bone_matrix = 0x4141180;

    constexpr uint64_t fmemory_malloc = 0x17B66B0;
    constexpr uint64_t static_find_object = 0x1C1D720;
    constexpr uint64_t static_laod_object = 0x1C21250; // Yazım hatası koruması
    constexpr uint64_t static_load_object = 0x1C21250;

    constexpr uint64_t set_ares_outline_mode = 0x40D3F50;
    constexpr uint64_t set_ares_outline = 0x40D3F50;

    constexpr uint64_t magic = 0x46C4660;

    constexpr uint64_t charm_map = 0x430;
    constexpr uint64_t charm_instance = 0x430;
    constexpr uint64_t projectile_component = 0x464;

    constexpr uint64_t RelativeScale3D = 0x17c;
    constexpr uint64_t TriggerVEH = 0x17EE1F6;

    constexpr uint64_t DefuseTimer = 0x05D0;
    constexpr uint64_t defuse_percentage = 0x05D0;
    constexpr uint64_t Timer = 0x05A8;
    constexpr uint64_t bomb_time_remaining = 0x05A8;

    constexpr uint64_t relative_rotation = 0x170;
    constexpr uint64_t cameramaneger = 0x528;
    constexpr uint64_t mesh = 0x430;

    // Not: Normalde bunlar hex olur (0x900). Listene uyumlu bırakıldı.
    constexpr uint64_t camerapos = 0x900;
    constexpr uint64_t camerafov = 0x930;
    constexpr uint64_t camerarot = 0x918;

    constexpr uint64_t game_instance = 0x1D8;
    constexpr uint64_t OwningGameInstance = 0x1D8;

    constexpr uint64_t local_players = 0x40;
    constexpr uint64_t viewport_client = 0x80;

    constexpr uint64_t engine = 0x28;
    constexpr uint64_t local_controller = 0x38;

    constexpr uintptr_t mesh_fp_flag = 0x364;

    // === FINISHER ===
    constexpr uint64_t play_finisher_effect = 0x8AB1BA0;

    constexpr uint64_t death_reaction_component_offset = 0xCA8;
    constexpr uint64_t montage_effect_override_offset = 0x100;
    constexpr uint64_t montage_effect_override_context_offset = 0x108;

    constexpr uint64_t bone_cout = 0x740;
    constexpr uint64_t mtkv = 0x37;

    constexpr uint64_t object_class = 0x10;
    constexpr uint64_t super_class = 0x48;

    // === SKINS ===
    constexpr uint64_t get_skin_levels = 0x88;
    constexpr uint64_t get_skin_data_asset = 0x108;
    constexpr uint64_t get_skin_chroma_data_asset = 0x108;
    constexpr uint64_t get_charm_data_asset = 0x68;
    constexpr uint64_t get_charm_level_data_asset = 0x70;
    constexpr uint64_t get_charm_level = 0xe0;

    constexpr uint64_t equippable_models = 0xe8;
    constexpr uint64_t skins = 0x150;
    constexpr uint64_t possible_levels = 0x138;
    constexpr uint64_t possible_levels1 = 0xfe;
    constexpr uint64_t possible_levels2 = 0xf2;
    constexpr uint64_t possible_chromas = 0x128;

    constexpr uint64_t get_screen_size1 = 0x48;
    constexpr uint64_t get_screen_size2 = 0x4c;

    constexpr uint64_t fr3scomp = 0xcd0;

    constexpr uint64_t was_invisible = 0xc8b;
    constexpr uint64_t inventory_icon = 0xdc0;
    constexpr uint64_t InventoryIcon = 0xdc0;

    constexpr uint64_t font = 0x98;

    constexpr uint64_t skymeshcomponent = 0x290;
    constexpr uint64_t sky_mesh_component = 0x290;

    // === MESHES ===
    constexpr uint64_t mesh1p = 0xf30;
    constexpr uint64_t mesh3p = 0xf00;
    constexpr uint64_t mesh1p_overlay = 0xf38;
    constexpr uint64_t mesh_cosmetic_3p = 0xef8;
    constexpr uint64_t mesh3p_mids = 0xf90; // Fallback

    constexpr uint64_t coolchams = 0x418;

    constexpr uint64_t mesh1pgun = 0xde0;
    constexpr uint64_t mesh3pgun = 0x0F38; // Eski listenden destek

    constexpr uint64_t fresnelcomponent = 0x860;
    constexpr uint64_t BlindManagerComponent = 0xa28;

    constexpr uint64_t flashend = 0x10;

    constexpr uint64_t WireFrame = 0x8fe;
    constexpr uint64_t wireframe_num = 0x8fe;

    constexpr uint64_t WireFrame2 = 0xc0;
    constexpr uint64_t wireframe_num_1 = 0xc0;

    constexpr uint64_t WireFrame3 = 0xff;

    constexpr uint64_t skin_pointer = 0x3a8;
    constexpr uint64_t skin_pointer_2 = 0xB0;
    constexpr uint64_t skin_pointer_3 = 0x80;
    constexpr uint64_t skin_data_asset = 0xDC8;
    constexpr uint64_t skin_data_assets = 0xDC8;

    constexpr uint64_t viewport_world = 0x80;
    constexpr uint64_t uworld_pointer = 0x80;

    constexpr uint64_t SetCameraPOVHook = 0xD7;
    constexpr uint64_t set_pov_hook = 0xD7;

    constexpr uint64_t viewport_gameinstance = 0x88;

    constexpr uint64_t get_spread_values = 0x6313BA0;
    constexpr uint64_t get_spread_angles = 0x6F4D720;

    constexpr uint64_t to_vector_and_normalize = 0x18B5FD0;
    constexpr uint64_t tovector_and_normalize = 0x18B5FD0;

    constexpr uint64_t to_angle_and_normalize = 0x18B07D0;
    constexpr uint64_t toangle_and_normalize = 0x18B07D0;

    constexpr uint64_t FiringStateComp = 0x1228;
    constexpr uint64_t firing_state_component = 0x1228;
    constexpr uint64_t get_firing_location_direction = 0x6ADC940;

    constexpr uint64_t seed_data = 0x4A0;
    constexpr uint64_t seed_dataadd = 0xD8;
    constexpr uint64_t unknown_pad = 0xD8;
    constexpr uint64_t stability_component = 0x490;

    constexpr uint64_t error_power = 0x49c;
    constexpr uint64_t error_retries = 0x470;

    constexpr uint64_t Inventory = 0x998;
    constexpr uint64_t inventory = 0x998;

    constexpr uint64_t Equippable = 0x248;
    constexpr uint64_t equippable = 0x248;

    constexpr uint64_t AccountLevel = 0x066C;
    constexpr uint64_t HideAccountLevel = 0x0668;

    constexpr uint64_t player_state = 0x488;
    constexpr uint64_t PlayerArray = 0x480;

    constexpr uint64_t PlatformPlayer = 0x6A0;
    constexpr uint64_t Rootcomponent = 0x290;
    constexpr uint64_t root_position = 0x170;
    constexpr uint64_t CameraRadar = 0x1F90;
    constexpr uint64_t CameraRotation = 0x396;
    constexpr uint64_t CameraFOV = 0x3A2;
    constexpr uint64_t CameraPrivate = 0x20a0;

    // === ACTOR ===
    constexpr uint64_t ActorArray = 0xa0;
    constexpr uint64_t ActorCount = 0xa8;
    constexpr uint64_t RootComponent = 0x290;
    constexpr uint64_t RelativeLocation = 0x170;
    constexpr uint64_t RelativeRotation = 0x188;

    // === MESH ===
    constexpr uint64_t Mesh = 0x430;
    constexpr uint64_t BoneArray = 0x740;
    constexpr uint64_t BoneCount = 0x748;
    constexpr uint64_t BoneArrayCache = 0x748;
    constexpr uint64_t ComponentToWorld = 0x2d0;
    constexpr uint64_t BoundsScale = 0x474;
    constexpr uint64_t LastSubmitTime = 0x478;
    constexpr uint64_t LastSubmitTimeOnScreen = 0x47c;

    // === HEALTH AND TEAM ===
    constexpr uint64_t Health = 0x200;
    constexpr uint64_t TeamID = 0xF8;
    constexpr uint64_t TeamComponent = 0x6a8;
    constexpr uint64_t WasAlly = 0xf68;
    constexpr uint64_t IsDormant = 0x225;

    // === WEAPONS ===
    constexpr uint64_t CurrentEquippable = 0x268;
    constexpr uint64_t DamageHandler = 0xc68;

    // === PAK MOUNTER ===
    constexpr uint64_t get_fpak_platform_file = 0xC30D0E8;
    constexpr uint64_t bypass_pak_signing = 0xC66D240;
    constexpr uint64_t mount_custom_pak = 0x293CE10;
    constexpr uint64_t fpak_platform_file = 0xC30D0E8;
    constexpr uint64_t mount = 0x293CE10;
    constexpr uint64_t iostore_sig_check = 0x0;

    constexpr uint64_t real_time_dormant = 0x101;
    constexpr uint64_t draw_transition = 0x40ADBC0;
}



namespace globals
{
    inline bool Watermark = true;
    inline bool stop_for_auto_shoot = false;

    namespace visuals {

        inline bool b0x = false;
        inline int b0x_type = 1;
        inline int snapos = 0;
        inline bool get_cached_mat = false;
        inline bool partyhat_self = false;
        inline bool box2d = false;
        inline bool box3d = false;
        inline bool corner = false;
        inline bool headb0x = false;
        inline bool radar = false;
        inline bool sk3let0n = true;
        inline bool snapl1ne = false;
        inline bool h3althbar = false;
        inline bool b00ms = false;
        inline bool b11ms = false;
        inline bool dstc = false;
        inline bool gunmaterial3p = false;
        inline bool gunmaterial1p = false;
        inline bool chinahat = false;
        inline bool safe_hand_chams = false;
        inline int typehand = 0;
        inline int typegun1p = 0;
        inline int typegun3d = 0;
        inline bool vischeck = false;
        inline bool spike = false;
        inline bool mosca_chams = false;
        inline bool mosca_hand_enabled = false;


        // S I K K E V E R - Mosca
        inline bool moscawireframe_enabled = false;
        inline float MoscaRed = 255.0f;
        inline float MoscaGreen = 0.0f;
        inline float MoscaBlue = 255.0f;
        inline float HandChamsGlow = 2.0f;
        inline float AlphaBasePower = 5.0f;
        inline float HandFadeStrength = 2.0f;
        inline float HandWireOpacity = 128.0f;
        inline float ShoulderWireOpacity = 64.0f;



        inline bool crystal_chams_enabled = false;
        inline int crystal_chams_preset = 0;
        inline flinearcolor backtrack_mesh_color = { 1.0f, 0.0f, 1.0f, 1.0f };
        inline int backtrack_tick_interval = 4;


        inline flinearcolor handcolor = { 1.0f, 1.0f, 1.0f, 1.0f };
        inline float handchams_intensity = 50.0f;

        inline float Self_CenterEdgeR = 0.53f;
        inline float Self_CenterEdgeG = 0.27f;
        inline float Self_CenterEdgeB = 0.47f;

        inline float Self_InnerEdgeR = 0.0f;
        inline float Self_InnerEdgeG = 0.27f;
        inline float Self_InnerEdgeB = 1.0f;

        inline float Self_OuterEdgeR = 0.04f;
        inline float Self_OuterEdgeG = 0.23f;
        inline float Self_OuterEdgeB = 0.21f;


        inline float GlowVisible = 200.0f;
        inline float AlphaColorMult = 0.0f;
        inline float DepthBias = -0.1f;
        inline float AlphaDissolveOpacity = 0.207412f;
        inline float BoundingBox = -50.0f;
        inline float InnerEdgeThickness = 0.1f;
        inline float OuterEdgeThickness = 0.37f;
        inline float RimFresnel = 1.0f;
        inline float RimMultiply = 1.0f;
        inline float RimPower = 1.0f;
        inline float OcclusionDepth = 0.0f;
        inline float OcclusionBehindWall = 1.0f;
        inline float OcclusionState = 1.0f;
        inline float RefractionDepthBias = 0.0f;
        inline float intensityvisibleoutline = 18.20f;
        inline float intensityinvisbleoutline = 18.20f;
    }


    namespace triggerbot {
        inline bool enabled = false;
        inline bool key_enabled = false;
        inline float tr1gg3r_f0v = 5.0f;
        inline bool v1s_ch3ck = false;
        inline int trigger_key = 0;
    }

    namespace aimbot {
        inline bool a1mbot = false;
        inline bool nospread = false;
        inline bool silent = false;
        inline bool auto_wall = false;
        inline bool v1sh_ch3ck = false;
        inline bool reco1l_contr0l = 0;
        inline bool draw_f0v = 0;
        inline float a1m_sm00th = 15.0f;
        inline float a1m_f0v = 70.f;
        inline bool enable_360_fov = false;
        inline bool closest_bone = false;
        inline bool resolver_enabled = false;
       inline bool double_tap_enabled = false;
       inline int double_tap_delay = 15;
       inline bool dt_only_visible = false;
       inline bool closest_bone_enabled = false;
       inline bool quick_stop_enabled = false;

        inline bool fov_360_nospread = false;
        inline bool fov_360 = false;
        inline float original_fov = 70.f;

        inline int a1m_b0ne = 0;
        inline int a1m_k3y = 0;
        inline int silent_key = 0;
        inline int silent_key1 = 0;
        inline bool silent1 = false;

        inline bool no_spread_mode = false;
        inline bool aim_lock = false;

        inline bool auto_shot = false;
        inline float auto_shot_delay_ms = 200.0f;
        inline float max_shots_per_second = 4.0f;
        inline bool auto_shot_hold_key = false;
        inline float nospread_lock_delay = 200.0f;
        inline bool advanced_timing = false;

        // Prediction settings
        inline bool prediction = false;
    }

    namespace lineup {
        inline bool enabled = false;
        inline bool show_guides = true;
        inline bool auto_aim = false;
        inline float projectile_velocity = 2000.0f;
        inline float gravity_scale = 1.0f;
        inline float render_distance = 5000.0f;
    }

    namespace autopeek {
        inline bool enabled = false;
        inline int peek_key = 0;
        inline float peek_distance = 80.0f;
        inline float peek_speed = 1.0f;
        inline bool auto_fire = true;
        inline bool draw_position = true;
    }

    namespace misc {
        inline bool backtrack_key = false;
        inline bool backtrack = false;
        inline bool sk1ptut0rial = false;
        inline bool sk1n_chang3r = false;
        inline bool customgun = false;
        inline bool no_smoke = false;
        inline bool Wireframe = false;
        inline bool gun_3p_wireframe = false;
        inline bool bullettracer = false;
        inline bool customskybox = false;
        inline bool cs2_skins = false;
        inline bool cs2_skin_enabled = false;
        inline int cs2_skin_weapon_type = 0;
        inline int BACKTRACK_MAX_TICKS = 64;
        inline int SKELETON_BONE_COUNT = 15;

        inline bool custom_text_enabled = false;
        inline bool hellfire_enabled = false;
        inline float glow = 35.0f;
        inline bool rainbow_sleeves = false;

        inline bool FogRGB = false;


        inline bool bullet_tracers = false;
        inline bool bullet_spawn = false;
        inline int  bullet_spawn_amount = 44;
        inline bool damage_numbers = false;

        inline float text_color_r = 1.5f;
        inline float text_color_g = 1.5f;
        inline float text_color_b = 1.5f;
        inline float text_emissive_intensity = 10.0f;

        inline bool Fog = false;
        inline float FogDensity = 0.02f;
        inline float FogHeightFalloff = 0.2f;
        inline flinearcolor FogColor = { 0.5f, 0.5f, 0.5f, 1.0f };
        inline float FogMaxOpacity = 1.0f;
        inline float FogStartDistance = 0.0f;
        inline float FogCutoffDistance = 0.0f;
        inline bool  bEnableVolumetricFog = false;
        inline float VolumetricFogDistance = 6000.0f;
        inline bool world_fog = false;

        // Eğer heavy_fog istiyorsanız
        inline bool heavy_fog = false;


        inline bool SpinBot = false;

        inline bool custom_vandal_enabled = false;
        inline bool skin_needs_reload = false;  // Custom Skin açılınca cache temizle

        inline bool vandal_transform_changed = false;

        // CLASSIC TRANSFORM
        inline bool custom_classic_enabled = false;

        // KNIFE TRANSFORM
        inline bool custom_knife_enabled = false;

        inline bool hellfiremode = false;
        inline bool lightningmode = false;

        // Pitch
        inline int pitch_mode = 0;             // 0=None, 1=Up, 2=Down, 3=Custom
        inline float pitch_value = 89.0f;

        // Yaw modes (checkboxes - peuvent être combinés)
        inline bool aa_spin = false;
        inline bool aa_jitter = false;
        inline bool aa_threeway = false;
        inline bool aa_desync = false;
        inline bool aa_backwards = false;
        inline bool aa_atomic = false;
        inline bool aa_prediction_breaker = false;

        // Settings
        inline float yaw_add = 0.0f;
        inline bool jitter_enabled = false;
        inline bool jitter_on_back = false;
        inline float jitter_range = 45.0f;
        inline float spinvalue = 15.0f;
        inline float desync_range = 60.0f;
        inline int atomic_mode = 0;
        inline float atomic_speed = 1.0f;
        inline float breaker_intensity = 1.0f;

        // Snap keys
        inline int snap_left_key = 0x00;
        inline int snap_right_key = 0x00;
        inline int snap_back_key = 0x00;

        inline int active_hotkey_left = -1;
        inline int active_hotkey_right = -1;
        inline int active_hotkey_back = -1;
        inline bool already_pressed_left = false;
        inline bool already_pressed_right = false;
        inline bool already_pressed_back = false;

        // === HAND SCALE ===
        inline float hand_scale_x = 2.8f;
        inline float hand_scale_y = 1.0f;
        inline float hand_scale_z = 1.0f;

        // === INSPECT SCALE ===
        inline float inspect_scale_x = 0.423117f;
        inline float inspect_scale_y = 1.0f;
        inline float inspect_scale_z = 1.0f;

        // === KNIFE SCALE ===
        inline float knife_scale_x = 0.483117f;
        inline float knife_scale_y = 1.0f;
        inline float knife_scale_z = 1.0f;

        // === WEAPON ROTATION ===
        inline float weapon_rotation_pitch = 90.0f;
        inline float weapon_rotation_yaw = 90.0f;
        inline float weapon_rotation_roll = 0.0f;

        inline bool self_wireframe = false;
        inline bool only_last_kill = false;
        inline bool finisher = false;

        // === CHAT ===
        inline bool chat_spammer = true;
        inline bool killsays = false;
        inline bool killsound = false;
        inline std::string chat_message = "discord.gg/heltra";
        inline int spam_key = VK_F4;

        inline bool fov_360 = false;
        inline static bool f1_key_pressed_last_frame = false;
        inline static bool f2_key_pressed_last_frame = false;
        inline bool customhand = false;

        // === ASHEN CRYSTAL ===
        inline bool ashen_crystal_enabled = false;
        inline double ashen_inner_b_emissive_slider = 8.0f;
        inline double ashen_inner_g_emissive_slider = 1.0f;

        // === MISC TOGGLES ===
        inline bool antiflash = false;
        inline bool WireframeGun = false;
        inline bool BuddyChanger = false;
        inline bool BigGun = false;
        inline bool ViewModelChanger = false;
        inline bool BigGun3D = false;
        inline bool fastcrouch = false;
        inline bool meshmofiedfastcrouch = false;
        inline bool bhop = false;
        inline bool BigGun3DWireframe = false;
        inline float BigGunFloat = 1;
        inline bool HandWire = false;
        inline bool materials = false;
        inline bool customskin3p = false;

        inline int chams_material_index = 0;
        inline bool playerchamsself = false;

        inline bool BigEnemy = false;
        inline bool BigSelf = false;

        // === ASHEN CRYSTAL GALAXY ===
        inline double ashen_diffuse_overlay = 15.0 * 100;
        inline double ashen_inner_b_emissive = 25.0 * 100;
        inline double ashen_inner_g_emissive = 25.0 * 100;
        inline double ashen_bump_offset = -8.0 * 100;
        inline double ashen_texture_tiling = 50.0 * 100;
        inline double ashen_reflection_vector = 5.0 * 100;
        inline double ashen_flow_map_speed = 0.1 * 100;
        inline double ashen_panner_y = 0.05 * 100;
        inline double ashen_diffuse_multiply = 8.0 * 100;
        inline double ashen_diffuse_power = 3.0 * 100;
        inline double ashen_refraction_bias = 2.0 * 100;

        // === ASHEN COLOR ===
        inline float ashen_emissive_r = 0.1f;
        inline float ashen_emissive_g = 0.0f;
        inline float ashen_emissive_b = 1.0f;
        inline float ashen_tint_r = 0.01f;
        inline float ashen_tint_g = 0.0f;
        inline float ashen_tint_b = 0.5f;
        inline float ashen_alpha = 1.0f;

        inline bool HandWire3d = false;
        inline bool HandChamsRbg = false;
        inline bool fovchanger = false;
        inline bool handglow = false;
        inline float fovchangur = 105.0f;

        // === SKYBOX MODES ===
        inline bool bloodmode = false;
        inline bool yellowmode = false;
        inline bool purplemode = false;
        inline bool orangemode = false;
        inline bool bluemode = false;
        inline bool cyanmode = false;
        inline bool greenmode = false;
        inline bool bluenight = false;
        inline bool tropicalnightmode = false;
        inline bool sunsetmode = false;
        inline bool nightmode = false;
        inline bool darknightmode = false;
        inline bool skyboxrgb = false;
        inline bool skybox = false;

        inline flinearcolor Overall = { 0.f,   0.f,   0.f,   1.f };
        inline flinearcolor Zenith = { 0.f,   0.f,   0.f,   1.f };
        inline flinearcolor Horizon = { 0.f,   0.f,   0.f,   1.f };
        inline flinearcolor Cloud = { 0.01f, 0.01f, 0.01f, 1.f };
        inline flinearcolor SkySunColor = { 0.f,   0.f,   0.f,   1.f };
        inline float CloudOpacity1 = 4000.f;


        inline float SkySharedR = 1.0f;
        inline float SkySharedG = 1.0f;
        inline float SkySharedB = 1.0f;

        // === SKYBOX VALUES ===
        inline float StarsBrightness = 0.0f;
        inline float CloudSpeed = 10.0f;
        inline float CloudOpacity = 5.0f;
        inline float SkyNoisePower2 = 1.0f;
        inline float SkyNoisePower1 = 1.0f;
        inline float SkySunRadius = 1.0f;
        inline float SkyHorizonFalloff = 1.0f;
        inline float SkySunBrightness = 1.0f;
        inline float SkySunHeight = 1.0f;
        inline float SkyLightDirection = 1.0f;

        // === SIZE ===
        inline float BigSelfFloat = 2.0f;
        inline float BigEnemyFloat = 2.0f;

        // === HAND CHAMS ===
        inline float GlowFloat1 = 1.0f;
        inline float handbright = 1.0f;
        inline flinearcolor handcolor{ 1.0f, 0.5f, 0.0f, 0.9f };
        inline float coolchamsbright = 1.0f;
        inline flinearcolor coolchamscolor{ 1.0f, 0.5f, 0.0f, 0.9f };
        inline bool handchams = false;

        // === SCALE ===
        inline float ScaleX = 1.0f;
        inline float ScaleY = 1.0f;
        inline float ScaleZ = 1.0f;
        inline float WScaleX = 1.0f;
        inline float WScaleY = 1.0f;
        inline float WScaleZ = 1.0f;

        // === HAND CHAMS SETTINGS ===
        inline float handchams_intensity = 2.0f;
        inline float handchams_speed = 1.0f;
        inline float time = 1.0f;
        inline float view = 1;

        // === THIRD PERSON ===
        inline bool tperson = false;
        inline float PlayerDistance = 100;
        inline float third_person_float = 100;
        inline float TPDistance = 300;
        inline int tpkey = 0x54; // T key for third person toggle

        // Third Person mesh offset
        inline std::uintptr_t Mesh3P = 0xF40;
        inline std::uintptr_t mesh_cosmetic_3p = 0xF40;
        inline std::uintptr_t thirdpersoncosmetic = 0xF40;

        // === ASPECT RATIO ===
        inline bool aspectratio = false;
        inline float aspectfloat = 1;
    }


    namespace chams {

        // --- OUTLINE AYARLARI ---
        inline bool outline_enabled = false;
        inline bool hand_outline_enabled = false;
        inline bool gun_outline3P_enabled = false;
        inline bool gun_outline1P_enabled = false;
        inline int outlinetype = 0;
        inline float GlowVisible = 20.f;
        inline float GlowInvisible = 80.f;

        // --- GALAXY CHAMS ŞALTERLERİ ---
        inline bool enemy_galaxy_enabled = false;
        inline bool self_galaxy_enabled = false;
        inline bool hands_galaxy_enabled = false;
        inline bool weapon_galaxy_enabled = false;
        inline bool Galax_hand_enabled = false;


        inline int galaxy_type_hand = 0;
        inline int galaxy_type_weapon = 0;
        inline int galaxy_type_self = 0;
        inline int galaxy_type_enemy = 0;

        inline bool ApplyHelfirehand = false;

        // --- RENK VE GLOW AYARLARI ---
        static float  Glow = 5.0f;
        static float  Glowvni = 5.0f;

        static flinearcolor ChamsColor{ 1.0f, 0.5f, 0.0f, 0.9f };
        static flinearcolor ChamsColorvni{ 1.0f, 0.7f, 0.0f, 0.9f };

        inline float intensityvisibleoutline = 10.0f * 100.0f;
        inline float intensityinvisbleoutline = 10.0f;

        inline int visible_outline_preset = 0;
        inline int invisible_outline_preset = 0;


        inline float Galaxy_CenterEdgeR_Visible = 0.4f;
        inline float Galaxy_CenterEdgeG_Visible = 0.0f;
        inline float Galaxy_CenterEdgeB_Visible = 0.5f;
        inline float Galaxy_InnerEdgeR_Visible = 0.2f;
        inline float Galaxy_InnerEdgeG_Visible = 0.1f;
        inline float Galaxy_InnerEdgeB_Visible = 0.6f;
        inline float Galaxy_OuterEdgeR_Visible = 0.0f;
        inline float Galaxy_OuterEdgeG_Visible = 0.6f;
        inline float Galaxy_OuterEdgeB_Visible = 1.0f;
        inline float Galaxy_GlowVisible = 20.0f;

        // Preset 1 - Blue Full Outline
        inline float BlueOutline_CenterEdgeR_Visible = 0.0f;
        inline float BlueOutline_CenterEdgeG_Visible = 0.3f;
        inline float BlueOutline_CenterEdgeB_Visible = 0.8f;
        inline float BlueOutline_InnerEdgeR_Visible = 0.1f;
        inline float BlueOutline_InnerEdgeG_Visible = 0.4f;
        inline float BlueOutline_InnerEdgeB_Visible = 0.9f;
        inline float BlueOutline_OuterEdgeR_Visible = 0.0f;
        inline float BlueOutline_OuterEdgeG_Visible = 0.5f;
        inline float BlueOutline_OuterEdgeB_Visible = 1.0f;
        inline float BlueOutline_GlowVisible = 20.0f;

        // Preset 2 - Green Full Outline
        inline float GreenOutline_CenterEdgeR_Visible = 0.1f;
        inline float GreenOutline_CenterEdgeG_Visible = 0.5f;
        inline float GreenOutline_CenterEdgeB_Visible = 0.2f;
        inline float GreenOutline_InnerEdgeR_Visible = 0.2f;
        inline float GreenOutline_InnerEdgeG_Visible = 0.7f;
        inline float GreenOutline_InnerEdgeB_Visible = 0.1f;
        inline float GreenOutline_OuterEdgeR_Visible = 0.0f;
        inline float GreenOutline_OuterEdgeG_Visible = 0.8f;
        inline float GreenOutline_OuterEdgeB_Visible = 0.3f;
        inline float GreenOutline_GlowVisible = 20.0f;

        // Preset 3 - Orange Full Outline
        inline float OrangeOutline_CenterEdgeR_Visible = 0.6f;
        inline float OrangeOutline_CenterEdgeG_Visible = 0.3f;
        inline float OrangeOutline_CenterEdgeB_Visible = 0.1f;
        inline float OrangeOutline_InnerEdgeR_Visible = 0.8f;
        inline float OrangeOutline_InnerEdgeG_Visible = 0.4f;
        inline float OrangeOutline_InnerEdgeB_Visible = 0.0f;
        inline float OrangeOutline_OuterEdgeR_Visible = 1.0f;
        inline float OrangeOutline_OuterEdgeG_Visible = 0.5f;
        inline float OrangeOutline_OuterEdgeB_Visible = 0.2f;
        inline float OrangeOutline_GlowVisible = 20.0f;

        // Preset 4 - Pink Full Outline
        inline float PinkOutline_CenterEdgeR_Visible = 0.7f;
        inline float PinkOutline_CenterEdgeG_Visible = 0.2f;
        inline float PinkOutline_CenterEdgeB_Visible = 0.5f;
        inline float PinkOutline_InnerEdgeR_Visible = 0.8f;
        inline float PinkOutline_InnerEdgeG_Visible = 0.1f;
        inline float PinkOutline_InnerEdgeB_Visible = 0.6f;
        inline float PinkOutline_OuterEdgeR_Visible = 0.9f;
        inline float PinkOutline_OuterEdgeG_Visible = 0.3f;
        inline float PinkOutline_OuterEdgeB_Visible = 0.7f;
        inline float PinkOutline_GlowVisible = 20.0f;

        // Preset 5 - White Full Outline
        inline float WhiteOutline_CenterEdgeR_Visible = 0.7f;
        inline float WhiteOutline_CenterEdgeG_Visible = 0.7f;
        inline float WhiteOutline_CenterEdgeB_Visible = 0.7f;
        inline float WhiteOutline_InnerEdgeR_Visible = 0.8f;
        inline float WhiteOutline_InnerEdgeG_Visible = 0.8f;
        inline float WhiteOutline_InnerEdgeB_Visible = 0.8f;
        inline float WhiteOutline_OuterEdgeR_Visible = 0.9f;
        inline float WhiteOutline_OuterEdgeG_Visible = 0.9f;
        inline float WhiteOutline_OuterEdgeB_Visible = 0.9f;
        inline float WhiteOutline_GlowVisible = 20.0f;

        inline float GalaxyBlackBlue_CenterEdgeR_Visible = 0.0f;     // Noir pur
        inline float GalaxyBlackBlue_CenterEdgeG_Visible = 0.0f;
        inline float GalaxyBlackBlue_CenterEdgeB_Visible = 0.0f;
        inline float GalaxyBlackBlue_InnerEdgeR_Visible = 0.4f;      // Bleu dark plus intense
        inline float GalaxyBlackBlue_InnerEdgeG_Visible = 0.3f;
        inline float GalaxyBlackBlue_InnerEdgeB_Visible = 0.7f;
        inline float GalaxyBlackBlue_OuterEdgeR_Visible = 0.0f;      // Noir
        inline float GalaxyBlackBlue_OuterEdgeG_Visible = 0.0f;
        inline float GalaxyBlackBlue_OuterEdgeB_Visible = 0.0f;
        inline float GalaxyBlackBlue_GlowVisible = 65.0f;            // Glow moyenne

        // === PRESETS POUR ENNEMIS INVISIBLES ===

        // Preset 0 - Red Full Outline (tes valeurs exactes)
        inline float RedOutline_CenterEdgeR_Invisible = 0.01f;
        inline float RedOutline_CenterEdgeG_Invisible = 0.0f;
        inline float RedOutline_CenterEdgeB_Invisible = 0.0f;
        inline float RedOutline_InnerEdgeR_Invisible = 0.1f;
        inline float RedOutline_InnerEdgeG_Invisible = 0.0f;
        inline float RedOutline_InnerEdgeB_Invisible = 0.0f;
        inline float RedOutline_OuterEdgeR_Invisible = 1.0f;
        inline float RedOutline_OuterEdgeG_Invisible = 0.0f;
        inline float RedOutline_OuterEdgeB_Invisible = 0.0f;
        inline float RedOutline_GlowInvisible = 15.0f;

        // Preset 1 - Orange Full Outline
        inline float OrangeOutline_CenterEdgeR_Invisible = 0.3f;
        inline float OrangeOutline_CenterEdgeG_Invisible = 0.1f;
        inline float OrangeOutline_CenterEdgeB_Invisible = 0.0f;
        inline float OrangeOutline_InnerEdgeR_Invisible = 0.5f;
        inline float OrangeOutline_InnerEdgeG_Invisible = 0.2f;
        inline float OrangeOutline_InnerEdgeB_Invisible = 0.0f;
        inline float OrangeOutline_OuterEdgeR_Invisible = 0.8f;
        inline float OrangeOutline_OuterEdgeG_Invisible = 0.4f;
        inline float OrangeOutline_OuterEdgeB_Invisible = 0.1f;
        inline float OrangeOutline_GlowInvisible = 15.0f;

        // Preset 2 - Yellow Full Outline
        inline float YellowOutline_CenterEdgeR_Invisible = 0.4f;
        inline float YellowOutline_CenterEdgeG_Invisible = 0.4f;
        inline float YellowOutline_CenterEdgeB_Invisible = 0.0f;
        inline float YellowOutline_InnerEdgeR_Invisible = 0.6f;
        inline float YellowOutline_InnerEdgeG_Invisible = 0.6f;
        inline float YellowOutline_InnerEdgeB_Invisible = 0.1f;
        inline float YellowOutline_OuterEdgeR_Invisible = 0.8f;
        inline float YellowOutline_OuterEdgeG_Invisible = 0.8f;
        inline float YellowOutline_OuterEdgeB_Invisible = 0.2f;
        inline float YellowOutline_GlowInvisible = 15.0f;

        // Preset 3 - Green Full Outline
        inline float GreenOutline_CenterEdgeR_Invisible = 0.1f;
        inline float GreenOutline_CenterEdgeG_Invisible = 0.3f;
        inline float GreenOutline_CenterEdgeB_Invisible = 0.0f;
        inline float GreenOutline_InnerEdgeR_Invisible = 0.2f;
        inline float GreenOutline_InnerEdgeG_Invisible = 0.5f;
        inline float GreenOutline_InnerEdgeB_Invisible = 0.1f;
        inline float GreenOutline_OuterEdgeR_Invisible = 0.3f;
        inline float GreenOutline_OuterEdgeG_Invisible = 0.7f;
        inline float GreenOutline_OuterEdgeB_Invisible = 0.2f;
        inline float GreenOutline_GlowInvisible = 15.0f;

        // Preset 4 - Pink Full Outline
        inline float PinkOutline_CenterEdgeR_Invisible = 0.4f;
        inline float PinkOutline_CenterEdgeG_Invisible = 0.1f;
        inline float PinkOutline_CenterEdgeB_Invisible = 0.3f;
        inline float PinkOutline_InnerEdgeR_Invisible = 0.6f;
        inline float PinkOutline_InnerEdgeG_Invisible = 0.0f;
        inline float PinkOutline_InnerEdgeB_Invisible = 0.4f;
        inline float PinkOutline_OuterEdgeR_Invisible = 0.8f;
        inline float PinkOutline_OuterEdgeG_Invisible = 0.2f;
        inline float PinkOutline_OuterEdgeB_Invisible = 0.6f;
        inline float PinkOutline_GlowInvisible = 15.0f;

        // Preset 5 - Gray Full Outline
        inline float GrayOutline_CenterEdgeR_Invisible = 0.2f;
        inline float GrayOutline_CenterEdgeG_Invisible = 0.2f;
        inline float GrayOutline_CenterEdgeB_Invisible = 0.2f;
        inline float GrayOutline_InnerEdgeR_Invisible = 0.4f;
        inline float GrayOutline_InnerEdgeG_Invisible = 0.4f;
        inline float GrayOutline_InnerEdgeB_Invisible = 0.4f;
        inline float GrayOutline_OuterEdgeR_Invisible = 0.6f;
        inline float GrayOutline_OuterEdgeG_Invisible = 0.6f;
        inline float GrayOutline_OuterEdgeB_Invisible = 0.6f;
        inline float GrayOutline_GlowInvisible = 15.0f;

        inline float GalaxyBlackBlue_CenterEdgeR_Invisible = 0.0f;   // Noir pur
        inline float GalaxyBlackBlue_CenterEdgeG_Invisible = 0.0f;
        inline float GalaxyBlackBlue_CenterEdgeB_Invisible = 0.0f;
        inline float GalaxyBlackBlue_InnerEdgeR_Invisible = 0.15f;   // Bleu dark un peu plus brillant
        inline float GalaxyBlackBlue_InnerEdgeG_Invisible = 0.35f;
        inline float GalaxyBlackBlue_InnerEdgeB_Invisible = 0.8f;
        inline float GalaxyBlackBlue_OuterEdgeR_Invisible = 0.0f;    // Noir
        inline float GalaxyBlackBlue_OuterEdgeG_Invisible = 0.0f;
        inline float GalaxyBlackBlue_OuterEdgeB_Invisible = 0.0f;
        inline float GalaxyBlackBlue_GlowInvisible = 40.0f;          // Glow moyenne

        // === VARIABLES ACTIVES (celles utilisées par apply_outline_chams) ===
        inline float CenterEdgeR_Visible = 0.5f;
        inline float CenterEdgeG_Visible = 0.0f;
        inline float CenterEdgeB_Visible = 1.0f;
        inline float InnerEdgeR_Visible = 0.8f;
        inline float InnerEdgeG_Visible = 0.2f;
        inline float InnerEdgeB_Visible = 1.0f;
        inline float OuterEdgeR_Visible = 0.2f;
        inline float OuterEdgeG_Visible = 0.0f;
        inline float OuterEdgeB_Visible = 0.8f;

        inline float CenterEdgeR_Invisible = 1.0f;
        inline float CenterEdgeG_Invisible = 0.0f;
        inline float CenterEdgeB_Invisible = 0.0f;
        inline float InnerEdgeR_Invisible = 0.8f;
        inline float InnerEdgeG_Invisible = 0.1f;
        inline float InnerEdgeB_Invisible = 0.0f;
        inline float OuterEdgeR_Invisible = 1.0f;
        inline float OuterEdgeG_Invisible = 0.2f;
        inline float OuterEdgeB_Invisible = 0.0f;

        inline void apply_visible_preset() {
            switch (visible_outline_preset) {
            case 0: // Galaxy Chams (tes valeurs exactes)
                CenterEdgeR_Visible = Galaxy_CenterEdgeR_Visible;
                CenterEdgeG_Visible = Galaxy_CenterEdgeG_Visible;
                CenterEdgeB_Visible = Galaxy_CenterEdgeB_Visible;
                InnerEdgeR_Visible = Galaxy_InnerEdgeR_Visible;
                InnerEdgeG_Visible = Galaxy_InnerEdgeG_Visible;
                InnerEdgeB_Visible = Galaxy_InnerEdgeB_Visible;
                OuterEdgeR_Visible = Galaxy_OuterEdgeR_Visible;
                OuterEdgeG_Visible = Galaxy_OuterEdgeG_Visible;
                OuterEdgeB_Visible = Galaxy_OuterEdgeB_Visible;
                GlowVisible = Galaxy_GlowVisible;
                break;
            case 1: // Blue Full Outline
                CenterEdgeR_Visible = BlueOutline_CenterEdgeR_Visible;
                CenterEdgeG_Visible = BlueOutline_CenterEdgeG_Visible;
                CenterEdgeB_Visible = BlueOutline_CenterEdgeB_Visible;
                InnerEdgeR_Visible = BlueOutline_InnerEdgeR_Visible;
                InnerEdgeG_Visible = BlueOutline_InnerEdgeG_Visible;
                InnerEdgeB_Visible = BlueOutline_InnerEdgeB_Visible;
                OuterEdgeR_Visible = BlueOutline_OuterEdgeR_Visible;
                OuterEdgeG_Visible = BlueOutline_OuterEdgeG_Visible;
                OuterEdgeB_Visible = BlueOutline_OuterEdgeB_Visible;
                GlowVisible = BlueOutline_GlowVisible;
                break;
            case 2: // Green Full Outline
                CenterEdgeR_Visible = GreenOutline_CenterEdgeR_Visible;
                CenterEdgeG_Visible = GreenOutline_CenterEdgeG_Visible;
                CenterEdgeB_Visible = GreenOutline_CenterEdgeB_Visible;
                InnerEdgeR_Visible = GreenOutline_InnerEdgeR_Visible;
                InnerEdgeG_Visible = GreenOutline_InnerEdgeG_Visible;
                InnerEdgeB_Visible = GreenOutline_InnerEdgeB_Visible;
                OuterEdgeR_Visible = GreenOutline_OuterEdgeR_Visible;
                OuterEdgeG_Visible = GreenOutline_OuterEdgeG_Visible;
                OuterEdgeB_Visible = GreenOutline_OuterEdgeB_Visible;
                GlowVisible = GreenOutline_GlowVisible;
                break;
            case 3: // Orange Full Outline
                CenterEdgeR_Visible = OrangeOutline_CenterEdgeR_Visible;
                CenterEdgeG_Visible = OrangeOutline_CenterEdgeG_Visible;
                CenterEdgeB_Visible = OrangeOutline_CenterEdgeB_Visible;
                InnerEdgeR_Visible = OrangeOutline_InnerEdgeR_Visible;
                InnerEdgeG_Visible = OrangeOutline_InnerEdgeG_Visible;
                InnerEdgeB_Visible = OrangeOutline_InnerEdgeB_Visible;
                OuterEdgeR_Visible = OrangeOutline_OuterEdgeR_Visible;
                OuterEdgeG_Visible = OrangeOutline_OuterEdgeG_Visible;
                OuterEdgeB_Visible = OrangeOutline_OuterEdgeB_Visible;
                GlowVisible = OrangeOutline_GlowVisible;
                break;
            case 4: // Pink Full Outline
                CenterEdgeR_Visible = PinkOutline_CenterEdgeR_Visible;
                CenterEdgeG_Visible = PinkOutline_CenterEdgeG_Visible;
                CenterEdgeB_Visible = PinkOutline_CenterEdgeB_Visible;
                InnerEdgeR_Visible = PinkOutline_InnerEdgeR_Visible;
                InnerEdgeG_Visible = PinkOutline_InnerEdgeG_Visible;
                InnerEdgeB_Visible = PinkOutline_InnerEdgeB_Visible;
                OuterEdgeR_Visible = PinkOutline_OuterEdgeR_Visible;
                OuterEdgeG_Visible = PinkOutline_OuterEdgeG_Visible;
                OuterEdgeB_Visible = PinkOutline_OuterEdgeB_Visible;
                GlowVisible = PinkOutline_GlowVisible;
                break;
            case 5: // White Full Outline
                CenterEdgeR_Visible = WhiteOutline_CenterEdgeR_Visible;
                CenterEdgeG_Visible = WhiteOutline_CenterEdgeG_Visible;
                CenterEdgeB_Visible = WhiteOutline_CenterEdgeB_Visible;
                InnerEdgeR_Visible = WhiteOutline_InnerEdgeR_Visible;
                InnerEdgeG_Visible = WhiteOutline_InnerEdgeG_Visible;
                InnerEdgeB_Visible = WhiteOutline_InnerEdgeB_Visible;
                OuterEdgeR_Visible = WhiteOutline_OuterEdgeR_Visible;
                OuterEdgeG_Visible = WhiteOutline_OuterEdgeG_Visible;
                OuterEdgeB_Visible = WhiteOutline_OuterEdgeB_Visible;
                GlowVisible = WhiteOutline_GlowVisible;
                break;
            case 6: // NEW: Galaxy Black Blue (Visible)
                CenterEdgeR_Visible = GalaxyBlackBlue_CenterEdgeR_Visible;
                CenterEdgeG_Visible = GalaxyBlackBlue_CenterEdgeG_Visible;
                CenterEdgeB_Visible = GalaxyBlackBlue_CenterEdgeB_Visible;
                InnerEdgeR_Visible = GalaxyBlackBlue_InnerEdgeR_Visible;
                InnerEdgeG_Visible = GalaxyBlackBlue_InnerEdgeG_Visible;
                InnerEdgeB_Visible = GalaxyBlackBlue_InnerEdgeB_Visible;
                OuterEdgeR_Visible = GalaxyBlackBlue_OuterEdgeR_Visible;
                OuterEdgeG_Visible = GalaxyBlackBlue_OuterEdgeG_Visible;
                OuterEdgeB_Visible = GalaxyBlackBlue_OuterEdgeB_Visible;
                GlowVisible = GalaxyBlackBlue_GlowVisible;
                break;
            }
        }

        inline void apply_invisible_preset() {
            switch (invisible_outline_preset) {
            case 0: // Red Full Outline (tes valeurs exactes)
                CenterEdgeR_Invisible = RedOutline_CenterEdgeR_Invisible;
                CenterEdgeG_Invisible = RedOutline_CenterEdgeG_Invisible;
                CenterEdgeB_Invisible = RedOutline_CenterEdgeB_Invisible;
                InnerEdgeR_Invisible = RedOutline_InnerEdgeR_Invisible;
                InnerEdgeG_Invisible = RedOutline_InnerEdgeG_Invisible;
                InnerEdgeB_Invisible = RedOutline_InnerEdgeB_Invisible;
                OuterEdgeR_Invisible = RedOutline_OuterEdgeR_Invisible;
                OuterEdgeG_Invisible = RedOutline_OuterEdgeG_Invisible;
                OuterEdgeB_Invisible = RedOutline_OuterEdgeB_Invisible;
                GlowInvisible = RedOutline_GlowInvisible;
                break;
            case 1: // Orange Full Outline
                CenterEdgeR_Invisible = OrangeOutline_CenterEdgeR_Invisible;
                CenterEdgeG_Invisible = OrangeOutline_CenterEdgeG_Invisible;
                CenterEdgeB_Invisible = OrangeOutline_CenterEdgeB_Invisible;
                InnerEdgeR_Invisible = OrangeOutline_InnerEdgeR_Invisible;
                InnerEdgeG_Invisible = OrangeOutline_InnerEdgeG_Invisible;
                InnerEdgeB_Invisible = OrangeOutline_InnerEdgeB_Invisible;
                OuterEdgeR_Invisible = OrangeOutline_OuterEdgeR_Invisible;
                OuterEdgeG_Invisible = OrangeOutline_OuterEdgeG_Invisible;
                OuterEdgeB_Invisible = OrangeOutline_OuterEdgeB_Invisible;
                GlowInvisible = OrangeOutline_GlowInvisible;
                break;
            case 2: // Yellow Full Outline
                CenterEdgeR_Invisible = YellowOutline_CenterEdgeR_Invisible;
                CenterEdgeG_Invisible = YellowOutline_CenterEdgeG_Invisible;
                CenterEdgeB_Invisible = YellowOutline_CenterEdgeB_Invisible;
                InnerEdgeR_Invisible = YellowOutline_InnerEdgeR_Invisible;
                InnerEdgeG_Invisible = YellowOutline_InnerEdgeG_Invisible;
                InnerEdgeB_Invisible = YellowOutline_InnerEdgeB_Invisible;
                OuterEdgeR_Invisible = YellowOutline_OuterEdgeR_Invisible;
                OuterEdgeG_Invisible = YellowOutline_OuterEdgeG_Invisible;
                OuterEdgeB_Invisible = YellowOutline_OuterEdgeB_Invisible;
                GlowInvisible = YellowOutline_GlowInvisible;
                break;
            case 3: // Green Full Outline
                CenterEdgeR_Invisible = GreenOutline_CenterEdgeR_Invisible;
                CenterEdgeG_Invisible = GreenOutline_CenterEdgeG_Invisible;
                CenterEdgeB_Invisible = GreenOutline_CenterEdgeB_Invisible;
                InnerEdgeR_Invisible = GreenOutline_InnerEdgeR_Invisible;
                InnerEdgeG_Invisible = GreenOutline_InnerEdgeG_Invisible;
                InnerEdgeB_Invisible = GreenOutline_InnerEdgeB_Invisible;
                OuterEdgeR_Invisible = GreenOutline_OuterEdgeR_Invisible;
                OuterEdgeG_Invisible = GreenOutline_OuterEdgeG_Invisible;
                OuterEdgeB_Invisible = GreenOutline_OuterEdgeB_Invisible;
                GlowInvisible = GreenOutline_GlowInvisible;
                break;
            case 4: // Pink Full Outline
                CenterEdgeR_Invisible = PinkOutline_CenterEdgeR_Invisible;
                CenterEdgeG_Invisible = PinkOutline_CenterEdgeG_Invisible;
                CenterEdgeB_Invisible = PinkOutline_CenterEdgeB_Invisible;
                InnerEdgeR_Invisible = PinkOutline_InnerEdgeR_Invisible;
                InnerEdgeG_Invisible = PinkOutline_InnerEdgeG_Invisible;
                InnerEdgeB_Invisible = PinkOutline_InnerEdgeB_Invisible;
                OuterEdgeR_Invisible = PinkOutline_OuterEdgeR_Invisible;
                OuterEdgeG_Invisible = PinkOutline_OuterEdgeG_Invisible;
                OuterEdgeB_Invisible = PinkOutline_OuterEdgeB_Invisible;
                GlowInvisible = PinkOutline_GlowInvisible;
                break;
            case 5: // Gray Full Outline
                CenterEdgeR_Invisible = GrayOutline_CenterEdgeR_Invisible;
                CenterEdgeG_Invisible = GrayOutline_CenterEdgeG_Invisible;
                CenterEdgeB_Invisible = GrayOutline_CenterEdgeB_Invisible;
                InnerEdgeR_Invisible = GrayOutline_InnerEdgeR_Invisible;
                InnerEdgeG_Invisible = GrayOutline_InnerEdgeG_Invisible;
                InnerEdgeB_Invisible = GrayOutline_InnerEdgeB_Invisible;
                OuterEdgeR_Invisible = GrayOutline_OuterEdgeR_Invisible;
                OuterEdgeG_Invisible = GrayOutline_OuterEdgeG_Invisible;
                OuterEdgeB_Invisible = GrayOutline_OuterEdgeB_Invisible;
                GlowInvisible = GrayOutline_GlowInvisible;
                break;
            case 6: // NEW: Galaxy Black Blue (Invisible)
                CenterEdgeR_Invisible = GalaxyBlackBlue_CenterEdgeR_Invisible;
                CenterEdgeG_Invisible = GalaxyBlackBlue_CenterEdgeG_Invisible;
                CenterEdgeB_Invisible = GalaxyBlackBlue_CenterEdgeB_Invisible;
                InnerEdgeR_Invisible = GalaxyBlackBlue_InnerEdgeR_Invisible;
                InnerEdgeG_Invisible = GalaxyBlackBlue_InnerEdgeG_Invisible;
                InnerEdgeB_Invisible = GalaxyBlackBlue_InnerEdgeB_Invisible;
                OuterEdgeR_Invisible = GalaxyBlackBlue_OuterEdgeR_Invisible;
                OuterEdgeG_Invisible = GalaxyBlackBlue_OuterEdgeG_Invisible;
                OuterEdgeB_Invisible = GalaxyBlackBlue_OuterEdgeB_Invisible;
                GlowInvisible = GalaxyBlackBlue_GlowInvisible;
                break;
            }
        }


        inline bool self_chams = false;

        inline bool chamsesp = false;
        inline bool enable_glow = false;
        inline bool rchamsesp = false;
        inline bool rchamsespall = false;
        inline float glow = 1.f;
        inline float Intenisty_fresnelz = 50;
        inline bool custom_fresnel = false;
        inline float GlowFloat = 1.0f;
        inline flinearcolor fresnel_color = flinearcolor(0.f, 26.0f, 0.f, GlowFloat);
        inline bool rainbow_fresnel = false;

        inline bool fresnelz = false;
    }

    namespace buddy {
        inline bool enabled = false;
        inline int index = 0;
    }
}