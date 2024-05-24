#include "Dish.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/circle_shape2d.hpp>
#include <godot_cpp/classes/physics_material.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>

using namespace godot;

void Dish::_bind_methods() {
}

Dish::Dish() 
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


    
    Ref<CircleShape2D> shape = memnew(CircleShape2D);
    shape->set_radius(10.0);
    collision_shape->set_shape(shape);
    collision_shape->set_name("Collision Shape");
    add_child(collision_shape);
    collision_shape->set_owner(this);
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
    

    Input* inputEvent = Input::get_singleton();
    if(inputEvent->is_mouse_button_pressed(MOUSE_BUTTON_LEFT))
    {
        // if(get_rect().has_point(to_local(get_global_mouse_position())))
        {
            auto transform = state->get_transform();
            transform.set_origin(get_global_mouse_position());
            state->set_transform(transform);

            set_linear_velocity(Vector2(0.0, 0.0));
            // set_angular_velocity(0.0);
            // set_axis_velocity(Vector2(0.0, 0.0));
        }
    }
}

void Dish::_input(Ref<InputEvent> event)
{
                
    // InputEventMouseButton* mouseEvent = dynamic_cast<InputEventMouseButton*>(event.ptr());

    // if(mouseEvent != nullptr)
    // {
    //     if(mouseEvent->is_pressed() && mouseEvent->get_button_index() == MOUSE_BUTTON_LEFT)
    //     {
    //         if(get_rect().has_point(to_local(mouseEvent->get_position())))
    //         {
    //             // set_position(mouseEvent->get_position());
    //             UtilityFunctions::print(mouseEvent->get_position());
    //         }
    //     }
    // }
}