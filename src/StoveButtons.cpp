/******************************************************************************
Copyright (C)
File Name:   StoveButtons.cpp
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 7.17.2024
	Header file for stove buttons.
    It is buttons to send signals to stove.
******************************************************************************/
#include "StoveButtons.h"

#include <godot_cpp/classes/texture_button.hpp>

using namespace godot;

void godot::StoveButtons::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_texture_right", "_texture"), &StoveButtons::set_texture_right);
	ClassDB::bind_method(D_METHOD("get_texture_right"), &StoveButtons::get_texture_right);
	ClassDB::add_property("StoveButtons", PropertyInfo(Variant::OBJECT, "texture_right", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture_right", "get_texture_right");\

	ClassDB::bind_method(D_METHOD("set_texture_left", "_texture"), &StoveButtons::set_texture_left);
	ClassDB::bind_method(D_METHOD("get_texture_left"), &StoveButtons::get_texture_left);
	ClassDB::add_property("StoveButtons", PropertyInfo(Variant::OBJECT, "texture_left", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture_left", "get_texture_left");
}

godot::StoveButtons::StoveButtons()
	: texture_button_left(memnew(TextureButton)), texture_button_right(memnew(TextureButton))
{
}

godot::StoveButtons::~StoveButtons()
{
}

void godot::StoveButtons::_ready()
{
	add_child(texture_button_left);
	texture_button_left->set_owner(this);
	texture_button_left->set_anchors_preset(Control::LayoutPreset::PRESET_CENTER_LEFT);


	add_child(texture_button_right);
	texture_button_right->set_owner(this);
	texture_button_right->set_anchors_preset(Control::LayoutPreset::PRESET_CENTER_RIGHT);
}

void godot::StoveButtons::_process(double delta)
{
}

Ref<Texture> godot::StoveButtons::get_texture_left() const
{
    return texture_left;
}

void godot::StoveButtons::set_texture_left(const Ref<Texture> &_texture)
{
	texture_left = _texture;

	texture_button_left->set_texture_normal(texture_left);
	texture_button_left->set_texture_hover(texture_left);
	texture_button_left->set_texture_pressed(texture_left);
	texture_button_left->set_texture_disabled(texture_left);
	texture_button_left->set_texture_focused(texture_left);
}

Ref<Texture> godot::StoveButtons::get_texture_right() const
{
    return texture_right;
}

void godot::StoveButtons::set_texture_right(const Ref<Texture> &_texture)
{
	texture_right = _texture;

	texture_button_right->set_texture_normal(texture_right);
	texture_button_right->set_texture_hover(texture_right);
	texture_button_right->set_texture_pressed(texture_right);
	texture_button_right->set_texture_disabled(texture_right);
	texture_button_right->set_texture_focused(texture_right);
}
