#include "DishContainers.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <Dish.h>

using namespace godot;

void godot::DishContainers::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("prepare_spawner", "_texture", "_offset"), &DishContainers::prepare_spawner);
    ClassDB::bind_method(D_METHOD("set_target_slot", "_target_slot"), &DishContainers::set_target_slot);
    ClassDB::bind_method(D_METHOD("spawn_dish", "_position", "_text"), &DishContainers::spawn_dish);
    ClassDB::bind_method(D_METHOD("force_spawn_dish", "_position", "_text"), &DishContainers::force_spawn_dish);
    ClassDB::bind_method(D_METHOD("is_any_dish_dragging"), &DishContainers::is_any_dish_dragging);
}

godot::DishContainers::DishContainers()
 : will_spawn(false), offset(), texture(nullptr), target_slot(nullptr)
{
    
}

godot::DishContainers::~DishContainers()
{
}

void godot::DishContainers::_ready()
{
}

void godot::DishContainers::_process(double delta)
{
}

void godot::DishContainers::_input(Ref<InputEvent> event)
{
    InputEventMouseButton* mouseEvent = dynamic_cast<InputEventMouseButton*>(event.ptr());

    if(mouseEvent != nullptr)
    {
        if (mouseEvent->is_released() && mouseEvent->get_button_index() == MOUSE_BUTTON_LEFT)
        {
            spawn_dish(mouseEvent->get_global_position(), texture);
            will_spawn = false;
        }
        
    }
}

void godot::DishContainers::prepare_spawner(Ref<Texture2D> _texture, Vector2 _offset)
{
    texture = _texture;
    offset = _offset;
}

void godot::DishContainers::set_target_slot(TextureRect* _target_slot)
{
    target_slot = _target_slot;
    will_spawn = true;
}

void godot::DishContainers::spawn_dish(Vector2 _position, Ref<Texture2D> _tex)
{
    if(will_spawn == false)
    {
        return;
    }

    if(target_slot == nullptr)
    {
        return;
    }

	// user tries to store an item to another item slot
    if(target_slot->get_global_rect().has_point(_position))
    {
        return;
    }


    Dish* dish = memnew(Dish);
    dish->set_texture(_tex);
    // @@ TODO: set_position? set_global_position?
    dish->set_position(_position + offset);
    add_child(dish);
}

void godot::DishContainers::force_spawn_dish(Vector2 _position, Ref<Texture2D> _tex)
{
    Dish* dish = memnew(Dish);
    dish->set_texture(_tex);
    dish->set_position(_position);
    add_child(dish);
}

bool godot::DishContainers::is_any_dish_dragging() const
{
    const int32_t child_count = get_child_count();

    for (int32_t i = 0; i < child_count; i++)
    {
        Dish* dish = Object::cast_to<Dish>(get_child(i));
        if (dish->is_dragging())
        {
            return true;
        }
    }
    
    return false;
}
