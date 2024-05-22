#ifndef MoveByClick_H
#define MoveByClick_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot {

class InputEvent;

class MoveByClick : public Sprite2D {
	GDCLASS(MoveByClick, Sprite2D)

protected:
	static void _bind_methods();

public:
	MoveByClick();
	~MoveByClick();

	void _process(double delta) override;

    void _input(Ref<InputEvent> event);
};

}

#endif