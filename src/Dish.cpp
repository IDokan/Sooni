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

    // Input* inputEvent = Input::get_singleton();
    // if(inputEvent->is_mouse_button_pressed(MOUSE_BUTTON_LEFT))
    // {
    //     // if(get_rect().has_point(to_local(get_global_mouse_position())))
    //     {
    //         set_position(get_global_mouse_position());
    //         collision_shape->set_position(get_global_mouse_position());
    //     }
    // }
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
    // @@ TODO: need to get valid destination. Current destination is (0, 0)
    UtilityFunctions::print(destination);

    Ref<Tween> t = create_tween();
    t->tween_property(this, "global_position",destination, 2.0);
    t->play();
}

Rect2 godot::Dish::get_sprite_rect() const
{
    return sprite->get_rect();
}
