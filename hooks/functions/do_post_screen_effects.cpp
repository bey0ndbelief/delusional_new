#include "../hooks.hpp"
#include "../../menu/menu.hpp"
#include "../../sdk/math/math.hpp"
#include "../../features/visuals/visuals.hpp"

bool __stdcall sdk::hooks::do_post_screen_effects::do_post_screen_effects(view_setup_t* setup) {

	for (auto hk : lua::hook_manager::get_hooks("on_post_screen_effect")) {
		auto result = hk.func();
		if (!result.valid()) {
			sol::error err = result;
			interfaces::console->console_color_printf({ 255, 0, 0, 255 }, ("[lua] "));
			interfaces::console->console_printf(std::string(err.what()).append(" \n").c_str());
		}

	}

	features::visuals::gravity_ragdoll();
	features::visuals::glow::run();

	return ofunc(interfaces::client_mode, setup);
}