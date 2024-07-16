#include <fstream>
#include <ShlObj.h>
#include "scripts.hpp"
#include  <iostream>
#include "../../sdk/sdk.hpp"
#include "../../sdk/interfaces/panorama.hpp"
#include "../../features/visuals/visuals.hpp"

namespace lua {
	bool g_unload_flag = false;
	lua_State* g_lua_state = NULL;
	std::vector<bool> loaded;
	std::vector<std::string> scripts;
	std::vector<std::filesystem::path> pathes;
	std::map<std::string, std::map<std::string, std::vector<menuitem_t>>> menu_items = {};

	int extract_owner(sol::this_state st) {
		sol::state_view lua_state(st);
		sol::table rs = lua_state["debug"]["getinfo"](2, "S");
		std::string source = rs["source"];
		std::string filename = std::filesystem::path(source.substr(1)).filename().string();
		return get_script_id(filename);
	}

	namespace ns_client {
		void set_event_callback(sol::this_state s, std::string eventname, sol::function func) {
			sol::state_view lua_state(s);
			sol::table rs = lua_state["debug"]["getinfo"](2, ("S"));
			std::string source = rs["source"];
			std::string filename = std::filesystem::path(source.substr(1)).filename().string();

			hook_manager::register_hook(eventname, get_script_id(filename), func);

		}
	};

	namespace ns_cvar { 
		convar* find_var(std::string name) {
			return interfaces::console->get_convar(name.c_str());
		}
		void console_color_printf(_color color, std::string v) { 
			interfaces::console->console_color_printf(color, v.c_str());
		}
		void console_printf(std::string v) { //dziala
			interfaces::console->console_printf(v.c_str());
		}
	};

	namespace ns_convar {
		int get_int(convar* c_convar) { //dziala
			return c_convar->get_int();
		}

		float get_float(convar* c_convar) {//dziala
			return c_convar->get_float();
		}

		void set_int(convar* c_convar, int value) { //dziala
			c_convar->set_value(value);
		}

		void set_float(convar* c_convar, float value) { //dziala
			c_convar->set_value(value);
		}

		void set_char(convar* c_convar, std::string value) { //dziala
			c_convar->set_value(value.c_str());
		}
	};

	namespace ns_engine {
		void execute_cmd(std::string cmd) {
			interfaces::engine->execute_cmd(cmd.c_str());
		}

		player_info_t get_player_info(int ent) {
			player_info_t p;
			interfaces::engine->get_player_info(ent, &p);
			return p;
		}

		int get_player_for_user_id(int userid) {
			return interfaces::engine->get_player_for_user_id(userid);
		}

		int get_local_player_index() {
			return interfaces::engine->get_local_player();
		}

		vec3_t get_view_angles() {
			vec3_t va;
			interfaces::engine->get_view_angles(va);
			return va;
		}

		void set_view_angles(vec3_t va) {
			interfaces::engine->set_view_angles(va);
		}

		int get_max_clients() { //dziala
			return interfaces::globals->max_clients;
		}

		bool is_in_game() { //dziala
			return interfaces::engine->is_in_game();
		}

		bool is_connected() { //dziala
			return interfaces::engine->is_connected();
		}
	};

	namespace ns_entity {
		bool get_box(player_t* entity, bbox_t& in) {
			return features::visuals::get_playerbox(entity, in);
		}
		bool dormant(player_t* entity) {
			return entity->dormant();
		}
		bool is_alive(player_t* entity) {
			return entity->is_alive();
		}
		vec3_t get_bone_position(player_t* entity, int bone) {
			return entity->get_bone_position(bone);
		}
		vec3_t get_eye_position(player_t* entity) {
			return entity->get_eye_pos();
		}
		bool can_see_player_pos(player_t* entity, vec3_t pos) {
			return entity->can_see_player_pos(entity, pos);
		}
		bool is_weapon(player_t* entity) {
			return entity->is_weapon();
		}
		bool is_player(player_t* entity) {
			return entity->is_player();
		}
		entity_t* get_active_weapon(player_t* entity) {
			return entity->active_weapon();
		}
		vec3_t get_abs_origin(player_t* entity) {
			return entity->abs_origin();
		}
		vec3_t get_origin(player_t* entity) {
			return entity->origin();
		}
		vec3_t get_aim_punch(player_t* entity) {
			return entity->aim_punch_angle();
		}
		int get_health(player_t* entity) {
			return entity->health();
		}
		int index(player_t* entity) {
			return entity->index();
		}
		bool spotted(player_t* entity, bool data) {
			return entity->spotted() = data;
		}
		unsigned long observer_target(player_t* entity) {
			return entity->observer_target();
		}

	};

	namespace ns_math {
		bool world_to_screen(const vec3_t& origin, vec3_t& screen) {
			return interfaces::debug_overlay->world_to_screen(origin, screen);
		}
	}

	namespace ns_entity_list {
		player_t* get_entity(int index) {
			return reinterpret_cast<player_t*>(interfaces::ent_list->get_client_entity(index));
		}
		player_t* get_entity_from_handle(int handle)
		{
			return interfaces::ent_list->get_client_entity_handle(handle);
		}
		int get_highest_entity_index() {
			return interfaces::ent_list->get_highest_index();
		}
	};

	namespace ns_surface {
		void draw_line(float x0, float y0, float x1, float y1) {
			interfaces::surface->draw_line(x0, y0, x1, y1);
		}
		void set_draw_color(int r, int g, int b, int a) {
			interfaces::surface->set_drawing_color(r, g, b, a);
		}
		void draw_filled_rect(float x0, float y0, float x1, float y1) {
			interfaces::surface->draw_filled_rectangle(x0, y0, x1, y1);
		}
		void draw_filled_rect_fade(int x, int y, int x2, int y2, int alpha, int alpha2, bool horizontal) {
			interfaces::surface->draw_filled_rect_fade(x, y, x2, y2, alpha, alpha2, horizontal);
		}
		void draw_outlined_rect(float x0, float y0, float x1, float y1) {
			interfaces::surface->draw_outlined_rect(x0, y0, x1, y1);
		}
		void draw_outlined_circle(float x, float y, int r, int seg) {
			interfaces::surface->draw_outlined_circle(x, y, r, seg);
		}
		int create_font(std::string fontname, int w, int h, int blur, int flags) {
			auto f = interfaces::surface->font_create();
			interfaces::surface->set_font_glyph(f, fontname.c_str(), w, h, blur, 0, flags);
			return f;
		}
		void set_text_font(int font) {
			interfaces::surface->draw_text_font(font);
		}
		void set_text_color(int r, int g, int b, int a) {
			interfaces::surface->set_text_color(r, g, b, a);
		}
		void set_text_pos(int x, int y) {
			interfaces::surface->draw_text_pos(x, y);
		}
		void draw_text(std::wstring str) {
			interfaces::surface->draw_render_text(str.c_str(), str.length());
		}
		vec2_t screen_size() {
			int w, h;
			interfaces::surface->get_screen_size(w, h);
			return vec2_t(w, h);
		}
	};

	namespace ns_ui {

		bool new_checkbox(std::string label, bool variable)
		{
			bool d = variable;
			ImGui::Checkbox(label.c_str(), &d);
			return d;
		}
		void new_separator()
		{
			ImGui::Separator();
		}
		void new_spacing() {

			 ImGui::Spacing();
		}
		float new_slider(std::string label, float variable, float min, float max, std::string format, float power)
		{
			float d = variable;
			ImGui::Text(label.c_str());
			ImGui::SetNextItemWidth(270.f);
			ImGui::SliderFloat(std::string("##" + label).c_str(), &d, min, max, format.c_str(), power);
			return d;
		}
		void new_text(std::string txt)
		{
			ImGui::Text(txt.c_str());
		}
		int new_combo(std::string label, int cur_item, std::string items)
		{
			int d = cur_item;
			ImGui::Text(label.c_str());
			ImGui::SetNextItemWidth(305.f);
			ImGui::Combo(std::string("##" + label).c_str(), &d, items.c_str());
			return d;
		}
		bool new_button(std::string label, vec2_t size = { 0.f,0.f })
		{
			return ImGui::Button(label.c_str(), { size.x,size.y });
		}
	};

	namespace ns_globals {
		float absolute_frametime() {
			return interfaces::globals->absolute_frametime;
		}

		float cur_time() {
			return interfaces::globals->cur_time;
		}

		int frame_count() {
			return interfaces::globals->frame_count;
		}

		float frame_time() {
			return interfaces::globals->frame_time;
		}

		float interval_per_tick() {
			return interfaces::globals->interval_per_tick;
		}

		float realtime() {
			return interfaces::globals->realtime;
		}

		int tick_count() {
			return interfaces::globals->tick_count;
		}

		player_t* localplayer() {
			return g::local;
		}
	}

	namespace ns_utilities {

        // apply clant and name needed

		color create_color(int r, int g, int b, int a) {
			return color(r, g, b, a);
		}
	}

	namespace ns_render {
		void rect(int x, int y, int w, int h, color color) {
			surface::rect(x, y, w, h, color);
		}
		void filled_rect(int x, int y, int w, int h, color color) {
			surface::filled_rect(x, y, w, h, color);
		}
		void line(int x1, int y1, int x2, int y2, color color) {
			surface::line(x1, y1, x2, y2, color);
		}
		void text(int x, int y, unsigned long font, std::string string, bool text_centered, color color) {
			surface::text(x, y, font, string, text_centered, color);
		}
		vec2_t text_size(unsigned long font, std::string text) {
			return surface::get_text_size(font, text);
		}

	}

	namespace ns_panorama {

		c_ui_engine* access_ui_engine(){
			return interfaces::panorama->access_ui_engine();
		}
		c_ui_panel* get_last_dispatched_event_target_panel() {
			return interfaces::panorama->access_ui_engine()->get_last_dispatched_event_target_panel();
		}
		void run_script(c_ui_panel* panel, const char* js, const char* schema_path) {
			int a5 = 8, a6 = 10;
			bool a7 = false, a8 = false;
			return interfaces::panorama->access_ui_engine()->run_script(panel, js,schema_path, a5 = 8, a6 = 10,  a7 = false,  a8 = false);
		}

	}

	namespace ns_input_system {
		void enable_input(bool enable) {
			interfaces::input_system->enable_input(enable);
		}
		const char* button_code_to_string(int buttonCode) {
			return interfaces::input_system->buttonCodeToString(buttonCode);
		}
		int virtual_key_to_button_code(int virtualKey) {
			return interfaces::input_system->vkey2buttoncode(virtualKey);
		}
		const char* virtual_key_to_string(int virtualKey) {
			return interfaces::input_system->vkey2string(virtualKey);
		}

        #define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
        #define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

		bool is_key_down(int keycode) {
			return KEYDOWN(keycode);
		}
		bool is_key_up(int keycode) {
			return KEYUP(keycode);
		}

		vec2_t get_mouse_position() {
			POINT mousePosition;
			GetCursorPos(&mousePosition);
			ScreenToClient(FindWindow(0, "Counter-Strike: Global Offensive"), &mousePosition);
			return { static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) };
		}

		bool mouse_in_region(int x, int y, int x2, int y2) {
			if (get_mouse_position().x > x && get_mouse_position().y > y && get_mouse_position().x < x2 + x && get_mouse_position().y < y2 + y)
				return true;
			return false;
		}

	};

	void init_state() {
		lua::unload();
		g_lua_state = luaL_newstate();
		luaL_openlibs(g_lua_state);
	}

	void init_command() {
		sol::state_view lua_state(g_lua_state);
		lua_state["exit"] = []() { g_unload_flag = true; };

		lua_state.new_enum("BUTTONS",
			"IN_ATTACK", cmd_buttons::in_attack,
			"IN_JUMP", cmd_buttons::in_jump,
			"IN_DUCK", cmd_buttons::in_duck,
			"IN_FORWARD", cmd_buttons::in_forward,
			"IN_BACK", cmd_buttons::in_back,
			"IN_USE", cmd_buttons::in_use,
			"IN_MOVELEFT", cmd_buttons::in_moveleft,
			"IN_MOVERIGHT", cmd_buttons::in_moveright,
			"IN_ATTACK2", cmd_buttons::in_attack2,
			"IN_SCORE", cmd_buttons::in_score,
			"IN_BULLRUSH", cmd_buttons::in_bullrush);

		lua_state.new_usertype<vec2_t>("vec2_t",
			"x", &vec2_t::x,
			"y", &vec2_t::y
			);

		lua_state.new_usertype<vec3_t>("vec3_t",
			"x", &vec3_t::x,
			"y", &vec3_t::y,
			"z", &vec3_t::z
			);

		lua_state.new_usertype<bbox_t>("bbox_t",
			"x", &bbox_t::x,
			"y", &bbox_t::y,
			"w", &bbox_t::w,
			"h", &bbox_t::h
			);

		lua_state.new_usertype<player_info_t>("player_info_t",
			"name", sol::readonly(&player_info_t::name),
			"fakeplayer", sol::readonly(&player_info_t::fakeplayer),
			"userid", sol::readonly(&player_info_t::userid)

			);

		lua_state.new_usertype<color>("color",
			sol::constructors<color(), color(int, int, int), color(int, int, int, int)>(),
			"r", &color::r,
			"g", &color::g,
			"b", &color::b,
			"a", &color::a
			);

		lua_state.new_usertype<c_usercmd>("c_usercmd",
			"command_number", sol::readonly(&c_usercmd::command_number),
			"tick_count", sol::readonly(&c_usercmd::tick_count),
			"viewangles", &c_usercmd::view_angles,
			"aimdirection", &c_usercmd::aim_direction,
			"forwardmove", &c_usercmd::forward_move,
			"sidemove", &c_usercmd::side_move,
			"upmove", &c_usercmd::up_move,
			"buttons", &c_usercmd::buttons,
			"impulse", sol::readonly(&c_usercmd::impulse),
			"weaponselect", &c_usercmd::weapon_select,
			"weaponsubtype", sol::readonly(&c_usercmd::weapon_subtype),
			"random_seed", sol::readonly(&c_usercmd::random_seed),
			"mousedx", &c_usercmd::mouse_dx,
			"mousedy", &c_usercmd::mouse_dy,
			"hasbeenpredicted", sol::readonly(&c_usercmd::has_been_predicted)
			);

		auto client = lua_state.create_table();
		client["set_event_callback"] = ns_client::set_event_callback;
		lua_state["client"] = client;

		auto engine = lua_state.create_table();
		engine["execute_cmd"] = ns_engine::execute_cmd;
		engine["get_local_player_index"] = ns_engine::get_local_player_index;
		engine["get_max_clients"] = ns_engine::get_max_clients;
		engine["get_player_for_user_id"] = ns_engine::get_player_for_user_id;
		engine["get_player_info"] = ns_engine::get_player_info;
		engine["get_view_angles"] = ns_engine::get_view_angles;
		engine["is_connected"] = ns_engine::is_connected;
		engine["is_in_game"] = ns_engine::is_in_game;
		engine["set_view_angles"] = ns_engine::set_view_angles;
		lua_state["engine"] = engine;

		auto input_system = lua_state.create_table();
		input_system["enable_input"] = ns_input_system::enable_input;
		input_system["button_code_to_string"] = ns_input_system::button_code_to_string;
		input_system["virtual_key_to_button_code"] = ns_input_system::virtual_key_to_button_code;
		input_system["virtual_key_to_string"] = ns_input_system::virtual_key_to_string;
		input_system["get_mouse_position"] = ns_input_system::get_mouse_position;
		input_system["mouse_in_region"] = ns_input_system::mouse_in_region;
		input_system["is_key_down"] = ns_input_system::is_key_down;
		input_system["is_key_up"] = ns_input_system::is_key_up;
		lua_state["input_system"] = input_system;

		auto entity = lua_state.create_table();
		entity["get_bone_position"] = ns_entity::get_bone_position;
		entity["get_eye_position"] = ns_entity::get_eye_position;
		entity["can_see_player_pos"] = ns_entity::can_see_player_pos;
		entity["get_box"] = ns_entity::get_box;
		entity["dormant"] = ns_entity::dormant;
		entity["is_weapon"] = ns_entity::is_weapon;
		entity["is_alive"] = ns_entity::is_alive;
		entity["is_player"] = ns_entity::is_player;
		entity["get_active_weapon"] = ns_entity::get_active_weapon;
		entity["get_abs_origin"] = ns_entity::get_abs_origin;
		entity["get_aim_punch"] = ns_entity::get_aim_punch;
		entity["get_health"] = ns_entity::get_health;
		entity["spotted"] = ns_entity::spotted;
		entity["observer_target"] = ns_entity::observer_target;
		entity["get_origin"] = ns_entity::get_origin;
		entity["index"] = ns_entity::index;
		lua_state["entity"] = entity;

		auto entity_list = lua_state.create_table();
		entity_list["get_entity"] = ns_entity_list::get_entity;
		entity_list["get_entity_from_handle"] = ns_entity_list::get_entity_from_handle;
		entity_list["get_highest_entity_index"] = ns_entity_list::get_highest_entity_index;
		lua_state["entity_list"] = entity_list;

		auto cvar = lua_state.create_table();
		cvar["find_var"] = ns_cvar::find_var;
		cvar["console_printf"] = ns_cvar::console_printf;
		cvar["console_color_printf"] = ns_cvar::console_color_printf;
		lua_state["cvar"] = cvar;

		auto mathematics = lua_state.create_table();
		mathematics["world_to_screen"] = ns_math::world_to_screen;
		lua_state["mathematics"] = mathematics;

		auto convar = lua_state.create_table();
		convar["get_int"] = ns_convar::get_int;
		convar["set_int"] = ns_convar::set_int;
		convar["get_float"] = ns_convar::get_float;
		convar["set_float"] = ns_convar::set_float;
		convar["set_char"] = ns_convar::set_char;
		lua_state["convar"] = convar;


		auto surface = lua_state.create_table();
		surface["draw_line"] = ns_surface::draw_line;
		surface["set_draw_color"] = ns_surface::set_draw_color;
		surface["draw_filled_rect"] = ns_surface::draw_filled_rect;
		surface["draw_filled_rect_fade"] = ns_surface::draw_filled_rect_fade;
		surface["draw_outlined_rect"] = ns_surface::draw_outlined_rect;
		surface["draw_outlined_circle"] = ns_surface::draw_outlined_circle;
		surface["create_font"] = ns_surface::create_font;
		surface["set_text_font"] = ns_surface::set_text_font;
		surface["set_text_color"] = ns_surface::set_text_color;
		surface["set_text_pos"] = ns_surface::set_text_pos;
		surface["draw_text"] = ns_surface::draw_text;
		surface["screen_size"] = ns_surface::screen_size;
		lua_state["surface"] = surface;

		auto ui = lua_state.create_table();
		ui["new_checkbox"] = ns_ui::new_checkbox;
		ui["new_spacing"] = ns_ui::new_spacing;
		ui["new_separator"] = ns_ui::new_separator;
		ui["new_text"] = ns_ui::new_text;
		ui["new_combo"] = ns_ui::new_combo;
		ui["new_button"] = ns_ui::new_button;
		lua_state["ui"] = ui;

		auto utilities = lua_state.create_table();
		utilities["color"] = ns_utilities::create_color;
		lua_state["utilities"] = utilities;

		auto globals = lua_state.create_table();
		globals["absolute_frametime"] = ns_globals::absolute_frametime;
		globals["cur_time"] = ns_globals::cur_time;
		globals["frame_count"] = ns_globals::frame_count;
		globals["frame_time"] = ns_globals::frame_time;
		globals["interval_per_tick"] = ns_globals::interval_per_tick;
		globals["realtime"] = ns_globals::realtime;
		globals["tick_count"] = ns_globals::tick_count;
		globals["localplayer"] = ns_globals::localplayer;
		lua_state["globals"] = globals;

		auto render = lua_state.create_table();
		render["line"] = ns_render::line;
		render["filled_rect"] = ns_render::filled_rect;
		render["rect"] = ns_render::rect;
		render["text"] = ns_render::text;
		render["text_size"] = ns_render::text_size;
		lua_state["render"] = render;

		auto panorama = lua_state.create_table();
		panorama["run_script"] = ns_panorama::run_script;
		panorama["access_ui_engine"] = ns_panorama::access_ui_engine;
		panorama["get_last_dispatched_event_target_panel"] = ns_panorama::get_last_dispatched_event_target_panel;

		lua_state["panorama"] = panorama;

		refresh_scripts();

	}

	void unload() {
		if (g_lua_state != NULL) {
			lua_close(g_lua_state);
			g_lua_state = NULL;
		}
	}

	void load_script(int id) {
		if (id == -1)
			return;

		if (loaded.at(id))
			return;

		auto path = get_script_path(id);
		if (path == (""))
			return;

		sol::state_view state(g_lua_state);
		state.script_file(path, [](lua_State* me, sol::protected_function_result result) {
			if (!result.valid()) {
				sol::error err = result;
				interfaces::console->console_color_printf({ 255, 0, 0, 255 }, ("[lua] "));
				interfaces::console->console_printf(std::string(err.what()).append(" \n").c_str());
				//utilities::console::log(err.what());
			}

			return result;
			});
		loaded.at(id) = true;
	}

	void unload_script(int id) {
		if (id == -1)
			return;

		if (!loaded.at(id))
			return;

		hook_manager::un_register_hook(id);
		loaded.at(id) = false;
	}

	void reload_all_scripts() {
		for (auto s : scripts) {
			if (loaded.at(get_script_id(s))) {
				unload_script(get_script_id(s));
				load_script(get_script_id(s));
			}
		}
	}

	void unload_all_scripts() {
		for (auto s : scripts)
			if (loaded.at(get_script_id(s)))
				unload_script(get_script_id(s));
	}

	void refresh_scripts() {
		auto oldLoaded = loaded;
		auto oldScripts = scripts;

		loaded.clear();
		pathes.clear();
		scripts.clear();

		for (auto& entry : std::filesystem::directory_iterator((c::directory_path_lua))) {
			if (entry.path().extension() == (".lua")) {
				auto path = entry.path();
				auto filename = path.filename().string();

				bool didPut = false;
				int oldScriptsSize = 0;
				oldScriptsSize = oldScripts.size();
				if (oldScriptsSize < 0)
					continue;

				for (int i = 0; i < oldScriptsSize; i++) {
					if (filename == oldScripts.at(i)) {
						loaded.push_back(oldLoaded.at(i));
						didPut = true;
					}
				}

				if (!didPut)
					loaded.push_back(false);

				pathes.push_back(path);
				scripts.push_back(filename);
			}
		}
	}

	int get_script_id(std::string name) {
		int script_size = 0;
		script_size = scripts.size();
		if (script_size <= 0)
			return -1;

		for (int i = 0; i < script_size; i++) {
			if (scripts.at(i) == name)
				return i;
		}

		return -1;
	}

	int get_script_id_by_path(std::string path) {
		int path_size = 0;
		path_size = pathes.size();
		if (path_size <= 0)
			return -1;

		for (int i = 0; i < path_size; i++) {
			if (pathes.at(i).string() == path)
				return i;
		}

		return -1;
	}

	std::string get_script_path(std::string name) {
		return get_script_path(get_script_id(name));
	}

	std::string get_script_path(int id) {
		if (id == -1)
			return  "";

		return pathes.at(id).string();
	}

	void hook_manager::register_hook(std::string event_name, int script_id, sol::protected_function func) {
		c_lua_hook hk = { script_id, func };

		hooks[event_name].push_back(hk);
	}

	void hook_manager::un_register_hook(int script_id) {
		for (auto& ev : hooks) {
			int pos = 0;

			for (auto& hk : ev.second) {
				if (hk.scriptId == script_id)
					ev.second.erase(ev.second.begin() + pos);

				pos++;
			}
		}
	}

	std::vector<c_lua_hook> hook_manager::get_hooks(std::string event_name) {
		return hooks[event_name];
	}
};