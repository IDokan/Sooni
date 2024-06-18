/******************************************************************************
Copyright (C)
File Name:   Tray.h
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 05.26.2024
	Header file for Tray class.
	It is a container which dishes wiil served.
	The dishes on it will delievered to her to satisfy hunger.
******************************************************************************/
#ifndef TRAY_H
#define TRAY_H

#include <godot_cpp/classes/static_body2d.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>

namespace godot {

class Sprite2D;
class RectangleShape2D;
class CollisionShape2D;
class Area2D;

class Tray : public StaticBody2D {
	GDCLASS(Tray, StaticBody2D)

protected:
	static void _bind_methods();

public:
	Tray();
	~Tray();

	void _ready();
	void _process(double delta) override;

	Ref<Texture> get_texture() const;
	void set_texture(const Ref<Texture>& _texture);

	void rearrange();

private:
	CollisionShape2D* body_collision;
	Ref<RectangleShape2D> body_collision_shape;
	Sprite2D* sprite;
	Ref<Texture> texture;

	Area2D* area;
	CollisionShape2D* area_collision;
	Ref<RectangleShape2D> area_collision_shape;

private:
	// It could be better using screen vertical size. 
	// Ex) (screen_size.y / a) - b
	static constexpr int TRAY_VERTICAL_DETECT_RANGE = 30;
};

}

#endif