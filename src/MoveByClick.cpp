#include "MoveByClick.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>

using namespace godot;

void MoveByClick::_bind_methods() {
}

MoveByClick::MoveByClick() {
	// Initialize any variables here.
}

MoveByClick::~MoveByClick() {
	// Add your cleanup here.
}

void MoveByClick::_process(double delta) {
	(delta);

    Input* inputEvent = Input::get_singleton();
    if(inputEvent->is_mouse_button_pressed(MOUSE_BUTTON_LEFT))
    {
        if(get_rect().has_point(to_local(get_global_mouse_position())))
        {
            set_position(get_global_mouse_position());
            
        }
    }

}

void MoveByClick::_input(Ref<InputEvent> event)
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
