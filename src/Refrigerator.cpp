/******************************************************************************
Copyright (C)
File Name:   Refrigerator.cpp
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 06.18.2024
	Source file for Refrigerator class.
******************************************************************************/
#include "Refrigerator.h"

// UI classes
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/texture_button.hpp>
#include <godot_cpp/classes/nine_patch_rect.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/scroll_container.hpp>
#include <godot_cpp/classes/grid_container.hpp>
#include <godot_cpp/classes/style_box.hpp>

// Tween
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/property_tweener.hpp>

using namespace godot;

void godot::Refrigerator::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_refrigerator_background_texture", "_texture"), &Refrigerator::set_refrigerator_background_texture);
	ClassDB::bind_method(D_METHOD("get_refrigerator_background_texture"), &Refrigerator::get_refrigerator_background_texture);
	ClassDB::add_property("Refrigerator", PropertyInfo(Variant::OBJECT, "refrigerator_background_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_refrigerator_background_texture", "get_refrigerator_background_texture");

	
	ClassDB::bind_method(D_METHOD("set_slot_background_texture", "_texture"), &Refrigerator::set_slot_background_texture);
	ClassDB::bind_method(D_METHOD("get_slot_background_texture"), &Refrigerator::get_slot_background_texture);
	ClassDB::add_property("Refrigerator", PropertyInfo(Variant::OBJECT, "slot_background_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_slot_background_texture", "get_slot_background_texture");

	ClassDB::bind_method(D_METHOD("set_tween_button_texture", "_texture"), &Refrigerator::set_tween_button_texture);
	ClassDB::bind_method(D_METHOD("get_tween_button_texture"), &Refrigerator::get_tween_button_texture);
	ClassDB::add_property("Refrigerator", PropertyInfo(Variant::OBJECT, "tween_button_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tween_button_texture", "get_tween_button_texture");

	
	ClassDB::bind_method(D_METHOD("set_size", "_size"), &Refrigerator::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &Refrigerator::get_size);
	ClassDB::add_property("Refrigerator", PropertyInfo(Variant::VECTOR2, "size"), "set_size", "get_size");

	
	ClassDB::bind_method(D_METHOD("set_position", "_position"), &Refrigerator::set_position);
	ClassDB::bind_method(D_METHOD("get_position"), &Refrigerator::get_position);
	ClassDB::add_property("Refrigerator", PropertyInfo(Variant::VECTOR2, "position"), "set_size", "get_size");

	ClassDB::bind_method(D_METHOD("set_columns", "_columns"), &Refrigerator::set_columns);
	ClassDB::bind_method(D_METHOD("get_columns"), &Refrigerator::get_columns);
	ClassDB::add_property("Refrigerator", PropertyInfo(Variant::INT, "columns", PROPERTY_HINT_RANGE, "1,20"), "set_columns", "get_columns");
	
}

godot::Refrigerator::Refrigerator()
	: slide_flag(true),
	texture_button(memnew(TextureButton)), 
	nine_patch_rect(memnew(NinePatchRect)), margin_container(memnew(MarginContainer)), scroll_container(memnew(ScrollContainer)),
	grid_container(memnew(GridContainer)), dish_slots(10)
{
	// Need to add property them
	size = Vector2(298, 583);
	position = Vector2(854, 33);
	columns = 2;

	for (size_t i = 0; i < dish_slots.size(); i++)
	{
		dish_slots[i] = memnew(DishSlot);
		grid_container->add_child(dish_slots[i]);
		dish_slots[i]->set_owner(grid_container);
	}
}

godot::Refrigerator::~Refrigerator()
{
}

void godot::Refrigerator::_ready()
{
	add_child(nine_patch_rect);
	nine_patch_rect->set_owner(this);
	nine_patch_rect->set_anchors_preset(Control::LayoutPreset::PRESET_CENTER_RIGHT);
	nine_patch_rect->set_size(size);
	nine_patch_rect->set_position(position);
	nine_patch_rect->set_h_size_flags(godot::Control::SizeFlags::SIZE_EXPAND_FILL);
	nine_patch_rect->set_v_size_flags(godot::Control::SizeFlags::SIZE_EXPAND_FILL);

	// Is it all? I thought I should change layout mode from position to anchors...
	// If bug happened in margin_container, here would be the spot to dive in.
	nine_patch_rect->add_child(margin_container);
	margin_container->set_owner(nine_patch_rect);
	margin_container->set_size(size);
	margin_container->set_anchors_preset(Control::LayoutPreset::PRESET_FULL_RECT);
	margin_container->add_theme_constant_override("margin_left", 9);
	margin_container->add_theme_constant_override("margin_top", 9);
	margin_container->add_theme_constant_override("margin_right", 9);
	margin_container->add_theme_constant_override("margin_bottom", 9);

	margin_container->add_child(scroll_container);
	scroll_container->set_owner(margin_container);
	scroll_container->set_h_size_flags(Control::SizeFlags::SIZE_FILL);
	scroll_container->set_v_size_flags(Control::SizeFlags::SIZE_FILL);

	scroll_container->add_child(grid_container);
	grid_container->set_owner(scroll_container);
	grid_container->set_columns(columns);
	grid_container->set_h_size_flags(godot::Control::SizeFlags::SIZE_EXPAND_FILL);
	grid_container->set_v_size_flags(godot::Control::SizeFlags::SIZE_EXPAND_FILL);	

	add_child(texture_button);
	texture_button->set_owner(this);
	texture_button->set_anchors_preset(Control::LayoutPreset::PRESET_CENTER_RIGHT);
	texture_button->set_position(position + Vector2(0, size.y / 2) - Vector2(texture_button->get_size().x, texture_button->get_size().y / 2));
    texture_button->connect("pressed", callable_mp(this, &Refrigerator::_on_texture_button_pressed));
}

void godot::Refrigerator::_process(double delta)
{
}

Ref<Texture> godot::Refrigerator::get_refrigerator_background_texture() const
{
    return refrigerator_background_texture;
}

void godot::Refrigerator::set_refrigerator_background_texture(const Ref<Texture> &_texture)
{
	refrigerator_background_texture = _texture;
	nine_patch_rect->set_texture(refrigerator_background_texture);
}

Ref<Texture> godot::Refrigerator::get_slot_background_texture() const
{
    return slot_background_texture;
}

void godot::Refrigerator::set_slot_background_texture(const Ref<Texture> &_texture)
{
	slot_background_texture = _texture;
	
	for (size_t i = 0; i < dish_slots.size(); i++)
	{
		dish_slots[i]->set_background_texture(slot_background_texture);
	}
}

Ref<Texture> godot::Refrigerator::get_tween_button_texture() const
{
    return tween_button_texture;
}

void godot::Refrigerator::set_tween_button_texture(const Ref<Texture> &_texture)
{
	tween_button_texture = _texture;
	texture_button->set_texture_normal(tween_button_texture);
	texture_button->set_texture_hover(tween_button_texture);
	texture_button->set_texture_pressed(tween_button_texture);
	texture_button->set_texture_disabled(tween_button_texture);
	texture_button->set_texture_focused(tween_button_texture);
	
	texture_button->set_position(position + Vector2(0, size.y / 2) - Vector2(texture_button->get_size().x, texture_button->get_size().y / 2));
}

Vector2 godot::Refrigerator::get_size() const
{
    return size;
}

void godot::Refrigerator::set_size(const Vector2 &_size)
{
	size = _size;
}

Vector2 godot::Refrigerator::get_position() const
{
    return position;
}

void godot::Refrigerator::set_position(const Vector2 &_position)
{
	position = _position;
}

int32_t godot::Refrigerator::get_columns() const
{
    return columns;
}

void godot::Refrigerator::set_columns(int32_t _columns)
{
	columns = _columns;
}

void godot::Refrigerator::_on_texture_button_pressed()
{
    Ref<Tween> t = create_tween();
	if (slide_flag)
	{
        t->tween_property(this, "offset", Vector2(size.x, 0), 1.0);
        t->play();

		slide_flag = false;
	}
	else
	{
        t->tween_property(this, "offset", Vector2(0, 0), 1.0);
        t->play();

		slide_flag = true;
	}
}
