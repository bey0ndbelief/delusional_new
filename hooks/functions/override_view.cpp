#include "../hooks.hpp"
#include "../../features/visuals/visuals.hpp"
#include "../../features/misc/misc.hpp"
#include "../../menu/config/config.hpp"

void __fastcall sdk::hooks::override_view::override_view( void* _this, void* _edx, view_setup_t* setup ) {
	if (c::misc::enable_fov && g::local && g::local->is_alive( ) && !g::local->is_scoped())
		setup->fov += c::misc::field_of_view;

	for (auto hk : lua::hook_manager::get_hooks("on_override_view")) {
		auto result = hk.func();
		if (!result.valid()) {
			sol::error err = result;
			interfaces::console->console_color_printf({ 255, 0, 0, 255 }, ("[lua] "));
			interfaces::console->console_printf(std::string(err.what()).append(" \n").c_str());
		}
	}
	
	features::misc::thirdperson();
	features::misc::view_model();
	features::visuals::freecam(setup);
	features::visuals::motion_blur(setup);

	ofunc( interfaces::client_mode, _this, setup );
}

bool __stdcall sdk::hooks::is_depth_of_field_enabled::is_depth_of_field_enabled() {
	features::visuals::motion_blur(nullptr);
	return false;
}