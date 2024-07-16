#pragma once
#include <map>
#include <filesystem>
#include "sol.hpp"

namespace lua {
	struct c_lua_hook {
		int scriptId;
		sol::protected_function func;
	};

	namespace hook_manager {
		void register_hook(std::string event_name, int script_id, sol::protected_function func);
		void un_register_hook(int script_id);
		extern std::vector<c_lua_hook> get_hooks(std::string event_name);
		inline std::map<std::string, std::vector<c_lua_hook>> hooks;
	};

	enum menu_item_type {
		menuitem_checkbox = 0,
		menuitem_sliderint,
		menuitem_sliderfloat,
		menuitem_keybind,
		menuitem_text,
		menuitem_singleselct,
		menuitem_multiselct,
		menuitem_colorpicker,
		menuitem_buttom
	};

	struct menuitem_t {
		menu_item_type type;
		int script = -1;
		std::string label = "";
		std::string key = "";

		bool is_visible = true;

		// defaults
		bool b_default = false;
		int i_default = 0;
		float f_default = 0.f;
		float c_default[4] = { 1.f, 1.f, 1.f, 1.f };
		std::map<int, bool> m_default = {};

		// keybinds
		bool allow_style_change = true;

		// singleselect & multiselect
		std::vector<const char*> items = {};

		// slider_int
		int i_min = 0;
		int i_max = 100;

		// slider_float
		float f_min = 0.f;
		float f_max = 1.f;

		// sliders
		std::string format = "%d";

		// callbacks
		sol::function callback;
	};

	void init_state();
	void init_command();
	void unload();

	void load_script(int id);
	void unload_script(int id);
	void reload_all_scripts();
	void unload_all_scripts();
	void refresh_scripts();
	int get_script_id(std::string name);
	int get_script_id_by_path(std::string path);
	std::string get_script_path(std::string name);
	std::string get_script_path(int id);

	extern std::map<std::string, std::map<std::string, std::vector<menuitem_t>>> menu_items;
	extern std::vector<std::filesystem::path> pathes;
	extern std::vector<bool> loaded;
	extern std::vector<std::string> scripts;
	extern lua_State* g_lua_state;
	extern bool g_unload_flag;
}
