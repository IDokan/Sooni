/******************************************************************************
Copyright (C)
File Name:   StoveButtons.h
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 7.17.2024
	Header file for stove buttons.
    It is buttons to send signals to stove.
******************************************************************************/

#ifndef STOVEBUTTONS_H
#define STOVEBUTTONS_H

#include <godot_cpp/classes/canvas_layer.hpp>

namespace godot {

class StoveButtons : public CanvasLayer {
	GDCLASS(StoveButtons, CanvasLayer)

protected:
	static void _bind_methods();

public:
	StoveButtons();
	~StoveButtons();

	void _ready();
	void _process(double delta) override;

private:
};

}

#endif