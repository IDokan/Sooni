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

	class TextureButton;
	class Texture;

class StoveButtons : public CanvasLayer {
	GDCLASS(StoveButtons, CanvasLayer)

protected:
	static void _bind_methods();

public:
	StoveButtons();
	~StoveButtons();

	void _ready();
	void _process(double delta) override;

	Ref<Texture> get_texture_left() const;
	void set_texture_left(const Ref<Texture>& _texture);

	Ref<Texture> get_texture_right() const;
	void set_texture_right(const Ref<Texture>& _texture);

private:
	TextureButton* texture_button_left;
	TextureButton* texture_button_right;

	Ref<Texture> texture_left;
	Ref<Texture> texture_right;
};

}

#endif