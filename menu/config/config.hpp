#pragma once
#include <string_view>
#include <vector>
#include "../../includes/nlohmann/json.hpp"

namespace c {
	void create_directory();
	void update_configs();
	void create_file(const std::string_view name);
	void delete_file(const std::size_t index);
	void save(const std::size_t index);
	void load(const std::size_t index);
	inline std::string directory_path_lua;
	inline std::string directory_path_fonts;
	inline std::string directory_path;
	inline std::string directory;

	namespace backtrack {
		inline bool backtrack = false;
		inline int time = 0;
		inline float fake = 200;
		inline bool fake_latency = false;
		inline bool selected_tick = false;
	}

	namespace triggerbot {
		inline bool enabled = false;
		inline int triggerbot_key;
		inline int triggerbot_key_s = 1;
	}

	namespace aimbot {
		inline bool aimbot;
		inline int aimbot_key;
		inline int aimbot_key_s = 1;
		inline int aimbot_only_enemy;
		inline bool aimbot_silent;
		inline bool rcs;
		inline bool non_sticky_aimbot;
		inline bool aim_at_bt;
		inline bool pistol_autowall;
		inline int pistol_autowall_dmg = 1;
		inline int pistol_aimbot_fov;
		inline int pistol_hitbox;
		inline bool heavy_pistol_autowall;
		inline int heavy_pistol_autowall_dmg = 1;
		inline int heavy_pistol_aimbot_fov;
		inline int heavy_pistol_hitbox;
		inline bool shotgun_autowall;
		inline int shotgun_autowall_dmg = 1;
		inline int shotgun_aimbot_fov;
		inline int shotgun_hitbox;
		inline bool heavy_autowall;
		inline int heavy_autowall_dmg = 1;
		inline int heavy_aimbot_fov;
		inline int heavy_hitbox;
		inline bool smg_autowall;
		inline int smg_autowall_dmg = 1;
		inline int smg_aimbot_fov;
		inline int smg_hitbox;
		inline bool rifle_autowall;
		inline int rifle_autowall_dmg = 1;
		inline int rifle_aimbot_fov;
		inline int rifle_hitbox;
		inline bool sniper_autowall;
		inline int sniper_autowall_dmg = 1;
		inline int sniper_aimbot_fov;
		inline int sniper_hitbox;
		inline bool autosniper_autowall;
		inline int autosniper_autowall_dmg = 1;
		inline int autosniper_aimbot_fov;
		inline int autosniper_hitbox;
	}

	namespace movement {
		inline int  dh_tick = 1;
		inline float stamina_fade_clr[4]{ 1.f, 1.f, 1.f };
		inline bool auto_strafe = false;
		inline int  auto_strafe_key = 0;
		inline int  auto_strafe_key_s = 1;
		inline bool bhop = false;
		inline bool null_strafing = false;
		inline bool ladder_bug = false;
		inline int ladder_bug_key = 0;
		inline int ladder_bug_key_s = 1;
		inline bool delay_hop = false;
		inline int  delay_hop_key = 0;
		inline int  delay_hop_key_s = 1;
		inline bool crouch_bug = false;
		inline int crouch_bug_key = 0;
		inline int crouch_bug_key_s = 1;
		inline bool visualize_edge_bug = false;
		inline float visualize_edge_bug_clr[4]{ 1.f, 1.f, 1.f };
		inline bool edge_bug = false;
		inline bool edge_bug_advanced_search = false;
		inline bool edge_bug_strafe = false;
		inline int edge_bug_priority = 0;
		inline int edge_bug_key = 0;
		inline int edge_bug_key_s = 1;
		inline float edge_bug_ticks = 0.32f;
		inline int edge_bug_rape = 5;
		inline float edge_bug_angle_limit = 0.0f;
		inline float edge_bug_lock_amount = 0.01f;
		inline int edge_bug_lock_type = 0;
		inline int edge_bug_type = 0;
		inline float edge_bug_health_boost_effect = 0.f;
		inline int edge_bug_detection_sound = 0;
		inline bool edge_bug_counter = false;
		inline bool edge_jump = false;
		inline bool edge_jump_on_ladder = false;
		inline int edge_jump_key = 0;
		inline int edge_jump_key_s = 1;
		inline int long_jump_key = 0;
		inline int long_jump_key_s = 1;
		inline bool long_jump_on_edge = false;
		inline bool lj_null[4] = { false, false, false, false };
		inline bool mini_jump = false;
		inline bool mini_jump_ej = false;
		inline bool mini_jump_remain_crouched = false;
		inline int mini_jump_key = 0;
		inline int mini_jump_key_s = 1;
		inline bool adaptive_key_cancelling = false;
		inline bool adaptive_key_for[3] = { false, false, false };
		inline bool strafe_optimizer = false;
		inline int strafe_optimizer_key = 0;
		inline int strafe_optimizer_key_s = 1;
		inline float strafe_optimizer_desired_gain = 0.f;
		inline float strafe_optimizer_required_speed = 0.f;
		inline bool mouse_strafe_limiter = false;
		inline bool mouse_strafe_limiter_affect_pitch = false;
		inline float mouse_strafe_limiter_value = 20.f;
		inline int mouse_strafe_limiter_key = 0;
		inline int mouse_strafe_limiter_key_s = 1;
		inline bool jump_bug = false;
		inline int jump_bug_key = 0;
		inline int jump_bug_key_s = 1;
		inline bool fastduck = false;
		inline bool auto_align = false;
		inline bool freelook_surf = true;
		inline bool auto_duck = false;
		inline int  auto_duck_key = 0;
		inline int  auto_duck_key_s = 1;
		inline bool pixel_surf_fix = false;
		inline bool pixel_surf = false;
		inline int  pixel_surf_key = 0;
		inline int  pixel_surf_key_s = 1;
		inline int pixel_surf_ticks = 7;
		inline bool fakebackwards = false;
		inline int  fakebackwardskey = 0;
		inline int  fakebackwardskey_s = 1;
		inline int  fakebackwards_angle = 0;
		inline bool edge_bug_detection_printf = false;
		inline bool jump_bug_detection_printf = false;
		inline bool long_jump_detection_printf = false;
		inline bool mini_jump_detection_printf = false;
		inline bool pixel_surf_detection_printf = false;
		inline bool ladder_bug_detection_printf = false;
		inline bool velocity_indicator = false;
		inline int velocity_indicator_position = 50;
		inline int indicators_position = 50;
		inline int indicators_gap = 4;
		inline float indicators_fading_speed = 65.f;
		inline bool indicators_allow_animation = false;
		inline bool velocity_indicator_show_pre = false;
		inline bool velocity_indicator_disable_ong_show_pre = false;
		inline bool velocity_indicator_custom_color = false;
		inline float velocity_indicator_positive_clr[4]{ 0.11765f, 1.00000f, 0.42745f };
		inline float velocity_indicator_negative_clr[4]{ 1.00000f, 0.46667f, 0.46667f };
		inline float velocity_indicator_neutral_clr[4]{ 1.00000f, 0.78039f, 0.34902f };
		inline float velocity_indicator_custom_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline float velocity_indicator_custom_clr2[4]{ 1.f, 1.f, 1.f };
		inline float velocity_indicator_fade_clr3[4]{ 1.f, 1.f, 1.f, 0.f };
		inline float indicator_detect_clr[3]{ 0.195f, 0.750f, 0.269f };
		inline bool indicators_show[8] = { false, false, false, false, false, false, false, false };
		inline bool allow_detection_clr = false;
		inline int detection_saved_tick = 15;
		inline bool detection_clr_for[9] = { false, false, false, false, false, false, false, false, false };
		inline bool stamina_indicator = false;
		inline bool stamina_indicator_fade = false;
		inline bool stamina_indicator_show_pre = false;
		inline bool stamina_indicator_disable_ong_show_pre = false;
		inline int stamina_indicator_position = 275;
		inline float stamina_indicator_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool stamina_graph = false;
		inline float stamina_graph_color[3]{ 1.f, 1.f, 1.f };
		inline int stamina_graph_offset = -700;
		inline int stamina_graph_height = 100;
		inline int stamina_graph_offset_x = 500;
		inline int graph_fade = 1;
		inline bool velocity_graph = false;
		inline float velocity_graph_color[3]{ 1.f, 1.f, 1.f };
		inline bool velocity_graph_show_landed_speed = false;
		inline bool velocity_graph_show_edge_bug = false;
		inline bool velocity_graph_show_jump_bug = false;
		inline bool velocity_graph_show_pixel_surf = false;
		inline float velocity_linewidth = 3.f;
		inline int velocity_thickness = 1;
		inline float velocity_height = 4.f;
		inline int velocity_size = 185;
		inline float graph_xscreenpos = 0.800f;
		inline float velocity_tofade = 1.f;
		inline bool key_strokes;
		inline int key_strokes_position = 200;
	}

	namespace misc {
		inline bool headshot_spoofer = false;
		inline bool anti_untrusted = true;
		inline bool unlock_inventory = false;
		inline bool custom_region = false;
		inline int custom_region_selection = 0;
		inline bool mouse_fix = false;
		inline bool keybind_list = false;
		inline bool door_spam = false;
		inline int door_spam_key = 0;
		inline int door_spam_key_s = 1;
		inline bool force_crosshair = false;
		inline bool sniper_crosshair = false;
		inline bool watermark = true;
		inline bool show_spotify_currently_playing = false;
		inline bool spectators_list = true;
		inline float spectators_list_color_1[3]{ 1.f, 1.f, 1.f };
		inline float spectators_list_color_2[3]{ 1.f, 1.f, 1.f };
		inline float spectators_list_clr[3]{ 0.11765, 0.11765, 0.11765 };
		inline float spectators_list_clr_2[3]{ 0.11765, 0.11765, 0.11765 };
		inline int spectatorlist_type = 0;
		inline bool spectatorlist_show_target = true;
		inline int spectatorlist_x = 100;
		inline int spectatorlist_y = 50;
		inline int spectatorlist_w;
		inline int spectatorlist_h;
		inline bool practice = false;
		inline bool practice_window = false;
		inline int  savepos = 0;
		inline int  savepos_s = 1;
		inline int  loadpos = 0;
		inline int  loadpos_s = 1;
		inline int  nextkey = 0;
		inline int  nextkey_s = 1;
		inline int  prevkey = 0;
		inline int  prevkey_s = 1;
		inline int  undokey = 0;
		inline int  undokey_s = 1;
		inline bool enable_fov = false;
		inline float field_of_view = 0.f;
		inline bool view_model = false;
		inline float view_model_x = 0.f;
		inline float view_model_y = 0.f;
		inline float view_model_z = 0.f;
		inline bool aspect_ratio = false;
		inline float aspect_ratio_amount = 1.f;
		inline bool custom_console = false;
		inline float custom_console_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool discord_rpc = false;
		inline bool radaringame = false;
		inline bool jumpstats;
		inline bool jumpstats_show_clr_fail;
		inline bool jumpstats_show_fail;
		inline bool swayscale = false;
		inline float swayscale_value = 0.f;
		inline char misc_clantag_text[256] = "";
		inline bool misc_animated_clantag = false;
		inline bool misc_clantag_spammer = false;
		inline bool misc_clantag_rotation = false;
		inline int misc_clantag_type = 0;
		inline float misc_clantag_speed = 1.0f;
		inline bool misc_hitmarker = false;
		inline bool misc_hitmarker_sound = false;
		inline bool misc_hitmarker_screen_effect = false;
		inline bool misc_hit_info[2] = { false, false};
		inline int misc_hitmarker_sound_type = 0;
		inline bool misc_reveal_ranks = false;
		inline bool nadepred = false;
		inline float nadepred_clr[3]{ 1.f, 1.f, 1.f };
		inline bool autoaccept = false;
		inline bool vote_revealer = false;
		inline bool thirdperson = false;
		inline bool thirdperson_disabled_on_weapon = false;
		inline int thirdperson_distance = 150;
		inline int thirdperson_key = 0;
		inline int thirdperson_key_s = 1;
		inline bool freecam = false;
		inline int freecam_key = 0;
		inline int freecam_key_s = 1;
		inline bool misc_kill_msg = false;
		inline char misc_kill_message[256] = "Hello World!";
		inline int menu_key = 0x2D; //ins
		inline bool movement_rec = false;
		inline bool movement_rec_show_line = true;
		inline bool movement_rec_infowindow = false;
		inline float movement_rec_smoothing = 1.f;
		inline int movement_rec_maxrender = 528;
		inline float movement_rec_infowindowx;
		inline float movement_rec_infowindowy;
		inline bool movement_rec_lockva = true;
		inline float movement_rec_ringsize = 5;
		inline int movement_rec_keystartrecord = 0;
		inline int movement_rec_keystartrecord_s = 1;
		inline int movement_rec_keystoprecord = 0;
		inline int movement_rec_keystoprecord_s = 1;
		inline int movement_rec_keystartplayback = 0;
		inline int movement_rec_keystartplayback_s = 1;
		inline int movement_rec_keystopplayback = 0;
		inline int movement_rec_keystopplayback_s = 1;
		inline int movement_rec_keyclearrecord = 0;
		inline int movement_rec_keyclearrecord_s = 1;
		inline int movement_rec_angletype = 0;
	}

	namespace skins {
		inline bool agent_changer = false;
		inline int agent_t = 0;
		inline int agent_ct = 0;

		inline bool knife_changer_enable = false;
		inline int knife_changer_wear = 0;
		inline int knife_changer_model = 0;
		inline int knife_changer_skin_id = 0;
		inline int knife_changer_paint_kit = 0;
		inline int knife_changer_vector_paint_kit = 0;
		inline int knife_skin = 0;

		inline bool gloves_endable = false;
		inline int gloves_model = 0;
		inline int gloves_skin = 0;
		inline int gloves_skin_id = 0;
		inline int gloves_wear = 0;
		inline int agent_model = 0;

		inline bool skin_custom_clr = false;
		inline float skin_modulation1[3]{ 1.f, 1.f, 1.f };
		inline float skin_modulation2[3]{ 1.f, 1.f, 1.f };
		inline float skin_modulation3[3]{ 1.f, 1.f, 1.f };
		inline float skin_modulation4[3]{ 1.f, 1.f, 1.f };

		inline bool weapon_endable = false;
		inline int weapons_page = 0;
		inline int weapons_model = 0;

	}

	namespace visuals {
		inline bool enable_weather = false;
		inline bool enable_visuals = false;
		inline bool fade_animation = false;
		inline bool enemy_only = false;
		inline bool playerbox = false;
		inline bool apply_zoom = false;
		inline int apply_zoom_key = 0;
		inline int apply_zoom_key_s = 1;
		inline int boxtype = 0;
		inline float corner_lenght = 5.f;
		inline bool playerarmor = false;
		inline float playerarmor_clr[3]{ 0.f, 0.31f, 1.0f };
		inline bool playerammo = false;
		inline float playerammo_clr[3]{ 1.f, 1.f, 1.f };
		inline float player_weapon_color[3]{ 1.f, 1.f, 1.f };
		inline int dropped_weapon_type = 0;
		inline bool player_box_outline[2] = { false, false};
		inline float playerbox_color[3]{ 1.f, 1.f, 1.f };
		inline bool playername = false;
		inline float playername_color[3]{ 1.f, 1.f, 1.f };
		inline bool playerweapon = false;
		inline bool player_weapon_type[2] = { false, false };
		inline float dropped_weapon_icon_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool dropped_weapon_name = false;
		inline bool dropped_weapon_icon = false;
		inline float dropped_weapon_name_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline float dropped_weapon_distance = 150.f;
		inline bool dropped_weapon_glow = false;
		inline float dropped_weapon_glow_clr[3]{ 1.f, 1.f, 1.f };
		inline bool bomb_esp = false;
		inline bool healthesp = false;
		inline int healthesp_s = 0;
		inline float health_bar[3]{ 1.f, 1.f, 1.f };
		inline float health_color[3]{ 1.f, 1.f, 1.f };
		inline float health_bar_gradient[3]{ 1.f, 1.f, 1.f };
		inline int health_bar_width = 1;
		inline bool override_bar = false;
		inline bool gradient_bar = false;
		inline bool skeleton = false;
		inline bool skeletonesp = false;
		inline float skeletonesp_clr[3]{ 1.f, 1.f, 1.f };
		inline float skeletonbt_clr[3]{ 1.f, 1.f, 1.f };
		inline float skeleton_last_clr[3]{ 1.f, 1.f, 1.f };
		inline float selected_tick_clr[3]{ 1.f, 1.f, 1.f };
		inline bool skeleton_last = false;
		inline bool glow = false;
		inline bool glow_weapon = false;
		inline int glow_style = 0;
		inline bool invisibleglow = false;
		inline bool visibleglow = false;
		inline float glow_visible_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline float glow_invisible_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline float glow_weapon_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool oof_arrows;
		inline int oof_arrows_size;
		inline int oof_arrows_dist;
		inline float oof_arrows_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline float oof_arrows_clr2[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool  radar = false;
		inline bool  mbenabled = false;
		inline bool  mbforwardEnabled = false;
		inline float mbfallingMin = 10.0f;
		inline float mbfallingMax = 20.0f;
		inline float mbfallingIntensity = 1.0f;
		inline float mbrotationIntensity = 1.0f;
		inline float mbstrength = 1.0f;
		inline bool fog;
		inline int fog_distance;
		inline int fog_density;
		inline float fog_color[4]{ 1.f, 1.f, 1.f, 1.f };
		inline int skybox;
		inline int flashalpha;
		inline bool change_flashalpha = false;
		inline bool nosmoke = false;
		inline bool trails;
		inline float trails_clr1[4]{ 1.f, 1.f, 1.f, 1.f };
		inline float trails_clr2[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool visuals_flags[6] = { false, false, false, false, false, false };
		inline bool removals[5] = { false, false , false , false , false };
		inline float world_color[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool world_modulate = false;
		inline bool fullbright;
		inline bool dlight = false;
		inline float dlight_clr[4]{ 1.f, 1.f, 1.f, 255.f };
		inline bool gravity_ragdoll = false;
	}

	namespace chams {
		inline bool backtrack_chams = false;
		inline bool backtrack_chams_gradient = false;
		inline bool backtrack_chams_invisible = false;
		inline bool backtrack_chams_draw_all_ticks = false;
		inline float backtrack_chams_clr1[4]{ 1.f, 1.f, 1.f, 1.f };
		inline float backtrack_chams_clr2[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool visible_chams = false;
		inline bool visible_wireframe = false; //
		inline float visible_chams_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool visible_chams_ov = false; //
		inline bool visible_wireframe_ov = false; //
		inline float visible_chams_clr_ov[4]{ 1.f, 1.f, 1.f, 1.f }; //
		inline bool invisible_chams = false;
		inline float invisible_chams_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool invisible_wireframe = false; //
		inline bool sleeve_chams = false; //
		inline float sleeve_chams_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool sleeve_wireframe = false; //
		inline bool arms_chams = false; //
		inline float arms_chams_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool arms_wireframe = false; //
		inline bool sleeve_chams_ov = false;
		inline float sleeve_chams_clr_ov[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool sleeve_wireframe_ov = false; //
		inline bool arms_chams_ov = false;
		inline float arms_chams_clr_ov[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool arms_wireframe_ov = false; //
		inline bool wpn_chams = false; //
		inline float wpn_chams_clr[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool wpn_wireframe = false; //
		inline bool wpn_chams_ov = false; //
		inline float wpn_chams_clr_ov[4]{ 1.f, 1.f, 1.f, 1.f };
		inline bool wpn_wireframe_ov = false; //
		inline int cham_type_bt = 0;
		inline int cham_type = 0;
		inline int cham_type_overlay = 0; //
		inline int cham_type_sleeve = 0;
		inline int cham_type_sleeve_ov = 0;
		inline int cham_type_wpn = 0;
		inline int cham_type_wpn_ov = 0;
		inline int cham_type_arms = 0; //
		inline int cham_type_arms_ov = 0; //
		inline int chams_backrack_ticks = 0;
		inline int localtype = 0;
		inline int type_p = 0;
	}

	namespace fonts {

		inline int indi_size = 28.;
		inline int indi_font = 0;
		inline bool indi_font_flag[11] = { false, false, false, false, false, false, false, false, false, true, false };

		inline int sub_indi_size = 28.;
		inline int sub_indi_font = 0;
		inline bool sub_indi_font_flag[11] = { false, false, false, false, false, false, false, false, false, true, false };

		inline int esp_hp_font = 0;
		inline int esp_hp_size = 12;
		inline bool esp_font_flag[11] = { false, false, false, true, false, false, true, false, false, true, false };

		inline int sc_logs_font = 0;
		inline int sc_logs_size = 12;
		inline bool sc_logs_flag[11] = { false, false, false, true, false, false, true, false, false, true, false };

		inline int esp_name_font = 0;
		inline int esp_name_size = 12;
		inline bool esp_name_font_flag[11] = { false, false, false, true, false, false, true, false, false, true, false };

		inline int esp_wpn_font = 0;
		inline int esp_wpn_size = 12;
		inline bool esp_wpn_font_flag[11] = { false, false, false, true, false, false, true, false, false, true, false };

		inline int esp_dropped_wpn_font = 0;
		inline int esp_dropped_wpn_size = 12;
		inline bool esp_dropped_wpn_font_flag[11] = { false, false, false, true, false, false, true, false, false, true, false };

		inline int esp_font = 0;

		inline int spec_font = 0;
		inline int spec_size = 12;
		inline bool spec_font_flag[9] = { false, false, false, true, false, false, true, false, false };

		inline int watermark_font = 0;
		inline int watermark_size = 12;
		inline bool watermark_font_flag[9] = { false, false, false, true, false, false, true, false, false };

		inline int sub_spec_font = 0;
		inline bool sub_spec_font_flag[9] = { false, false, false, true, false, false, true, false, false };
	}

	namespace sfui {
		inline bool sfui_on = false;
	}

	namespace calculator {
		inline bool ps_calcualtor = false;
		inline int  toggle_wireframe_key = 0;
		inline int  toggle_wireframe_key_s = 2;
		inline int  toggle_clipbrushe_key = 0;
		inline int  toggle_clipbrushe_key_s = 2;
		inline int  set_point_key = 0;
		inline int  set_point_key_s = 1;
		inline int  calculate_point_key = 0;
		inline int  calculate_point_key_s = 1;

	}

	inline std::vector<std::string> configs;
}

struct keybind_t {
	bool enabled;
	int id;
	int type;
};

enum keybind_type {
	off,
	hold,
	toggle,
	always
};

struct cvar_t;
struct cvars_t;