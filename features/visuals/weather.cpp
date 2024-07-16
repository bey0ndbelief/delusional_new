#include "visuals.hpp"

void features::weather::reset_weather(const bool cleanup) {
    created_rain = false;

    if (rain_entity && !IsBadReadPtr(rain_entity, 4) && cleanup) {
        if (rain_entity->networkable())
            rain_entity->net_release();
    }

    rain_entity = nullptr;
}

void features::weather::update_weather() {
    if (!precipitation) {
        for (auto client_class = interfaces::client->get_all_classes(); client_class && !precipitation;
            client_class = client_class->next_ptr) {
            if (client_class->class_id == cprecipitation)
                precipitation = client_class;
        }
    }

    if (!precipitation)
        return;

    if (!created_rain && c::visuals::enable_weather || c::visuals::enable_weather && !last_state) {
        if (created_rain && rain_entity)
            reset_weather();

        if (precipitation->create_fn && precipitation->create_fn(MAX_EDICTS - 1, 0)) {
            rain_entity = reinterpret_cast<precipitation_t*>(interfaces::ent_list->get_client_entity(MAX_EDICTS - 1));

            rain_entity->precip_type() = precipitation_type_t::PRECIPITATION_TYPE_SNOW;

            rain_entity->net_pre_data_update(0);
            rain_entity->pre_data_change(0);

            rain_entity->collideable()->mins() = { -16384.0f, -16384.0f, -16384.0f };
            rain_entity->collideable()->maxs() = {16384.0f, 16384.0f, 16384.0f};

            rain_entity->on_data_changed(0);
            rain_entity->post_data_update(0);

            created_rain = true;
        }
    }
    else if (created_rain && !c::visuals::enable_weather && last_state) {
        reset_weather();
    }

    last_state = c::visuals::enable_weather;
}