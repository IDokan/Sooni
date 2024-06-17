#include "Dish.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/property_tweener.hpp>

// Physics
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/physics_material.hpp>

// Sprites
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>

// Another classes
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/grid_container.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <DishContainers.h>

using namespace godot;

void Dish::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_texture", "_texture"), &Dish::set_texture);
    ClassDB::bind_method(D_METHOD("get_texture"), &Dish::get_texture);
    ClassDB::add_property("Dish", PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");

    
}

Dish::Dish() 
    : sprite(memnew(Sprite2D)), rect_shape(memnew(RectangleShape2D))
{
    collision_shape = memnew(CollisionShape2D);
    
}

Dish::~Dish() {
	// Add your cleanup here.
    // memdelete(collision_shape);
}

void godot::Dish::_ready()
{
    Ref<PhysicsMaterial> physicsMaterial(memnew(PhysicsMaterial));
    physicsMaterial->set_bounce(0.5);
    set_physics_material_override(physicsMaterial);

    sprite->set_centered(true);
    sprite->set_name("Sprite");
    add_child(sprite);
    sprite->set_owner(this);
    
    rect_shape->set_size(sprite->get_rect().size);
    collision_shape->set_name("Collision Shape");
    collision_shape->set_shape(rect_shape);
    add_child(collision_shape);
    collision_shape->set_owner(this);

    offset = Vector2(0.0, 0.0);
    dragging = false;
}

void Dish::_process(double delta)
{
    (delta);  
}

void godot::Dish::_integrate_forces(PhysicsDirectBodyState2D *state)
{
    if(dragging)
    {
            Transform2D transform = state->get_transform();
            transform.set_origin(get_global_mouse_position() + offset);
            state->set_transform(transform);
    }
    
}

void Dish::_input(Ref<InputEvent> event)
{
    InputEventMouseButton* mouseEvent = dynamic_cast<InputEventMouseButton*>(event.ptr());

    if(mouseEvent != nullptr)
    {
        if(mouseEvent->is_pressed() && mouseEvent->get_button_index() == MOUSE_BUTTON_LEFT)
        {
            if(sprite->get_rect().has_point(to_local(mouseEvent->get_position())))
            {
                offset = sprite->get_global_position() - get_global_mouse_position();
                dragging = true;
                
                set_linear_velocity(Vector2(0.0, 0.0));
            }
        }

        
        if(mouseEvent->is_released() && mouseEvent->get_button_index() == MOUSE_BUTTON_LEFT && dragging)
        {
            dragging = false;
            set_linear_velocity(Vector2(0.0, 0.0));

            Vector2 mouse_position = mouseEvent->get_global_position();
            store_to_inventory(mouse_position, get_item_slot_index_on(mouse_position));
        }
    }
}

Ref<Texture> godot::Dish::get_texture() const
{
    return texture;
}

void godot::Dish::set_texture(const Ref<Texture> &_texture)
{
    texture = _texture;
    sprite->set_texture(texture);
    
    rect_shape->set_size(sprite->get_rect().size);
}

void godot::Dish::set_rearrange_destination(Vector2 destination)
{
    Ref<Tween> t = create_tween();
    t->tween_property(this, "global_position",destination, 2.0);
    t->play();
}

Rect2 godot::Dish::get_sprite_rect() const
{
    return sprite->get_rect();
}

bool godot::Dish::is_dragging() const
{
    return dragging;
}

int32_t godot::Dish::get_item_slot_index_on(Vector2 mouse_position)
{
    // @@ TODO: Could be better approach to find the inventory pointer
    GridContainer* inventory = get_tree()->get_root()->get_node<GridContainer>(NodePath("Node2D/CanvasLayer/NinePatchRect/MarginContainer/ScrollContainer/Inventory"));
    if (inventory == nullptr)
    {
        return -1;
    }

    int32_t child_count = inventory->get_child_count();
    for(int32_t i = 0; i < child_count; ++i)
    {
        // The below line should be change if inventory structure has changed.
        TextureRect* slot = Object::cast_to<TextureRect>(inventory->get_child(i)->get_child(0));
        if(slot != nullptr)
        {
            if(slot->get_global_rect().has_point(mouse_position))
            {
                return i;
            }
        }
    }

    return -1;
}

void godot::Dish::store_to_inventory(Vector2 mouse_position, int32_t inventory_slot_index)
{
    if(inventory_slot_index < 0)
    {
        return;
    }

    // @@ TODO: Could be better approach to find the inventory pointer
    GridContainer* inventory = get_tree()->get_root()->get_node<GridContainer>(NodePath("Node2D/CanvasLayer/NinePatchRect/MarginContainer/ScrollContainer/Inventory"));
    if(inventory == nullptr)
    {
        return;
    }

    TextureRect* slot = Object::cast_to<TextureRect>(inventory->get_child(inventory_slot_index)->get_child(0));

    // swap dish within inventory if the slot is not empty
    if(slot->get_texture() != nullptr)
    {
        // spawn a dish by an information of the slot
        Vector2 spawn_position = Vector2(get_global_position().x - (sprite->get_rect().get_size().x / 2) - (slot->get_rect().get_size().x / 2), get_global_position().y);
        get_node<DishContainers>(NodePath("/root/Node2D/DishContainers"))->force_spawn_dish(spawn_position, slot->get_texture());
    }

    // @@ TODO: Change how to send dish data.
    slot->set_texture(texture);

    queue_free();
}
