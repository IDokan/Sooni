#include "MoveByClick.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>

using namespace godot;

void MoveByClick::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_input", "event"), &MoveByClick::_input);
}

MoveByClick::MoveByClick() {
	// Initialize any variables here.
}

MoveByClick::~MoveByClick() {
	// Add your cleanup here.
}

void MoveByClick::_process(double delta) {
	(delta);
}

// Should I use godot::Ref<godot::InputEvent>?
void MoveByClick::_input(Ref<InputEvent> event)
{
                set_position(Vector2(0, 0));
    InputEventMouseButton* mouseEvent = dynamic_cast<InputEventMouseButton*>(event.ptr());

    // if(mouseEvent != nullptr)
    {
        // if(mouseEvent->is_pressed() && mouseEvent->get_button_index() == MOUSE_BUTTON_LEFT)
        {
            //if(get_rect().has_point(to_local(mouseEvent->get_position())))
            {
                set_position(Vector2(0, 0));
            }
        }
    }
}
