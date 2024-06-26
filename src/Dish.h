/******************************************************************************
Copyright (C)
File Name:   Dish.h
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 05.24.2024
	Header file for Dish class.
	It is a food that will be served. 
	It has nutrients that will be provided.
******************************************************************************/
#ifndef DISH_H
#define DISH_H

#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/classes/physics_direct_body_state2d.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot {

class InputEvent;
class CollisionShape2D;
class PhysicsDirectBodyState2D;
class Sprite2D;
class RectangleShape2D;

class Dish : public RigidBody2D {
	GDCLASS(Dish, RigidBody2D)

protected:
	static void _bind_methods();

public:
	Dish();
	~Dish();

	void _ready();
	void _process(double delta) override;
	void _integrate_forces(PhysicsDirectBodyState2D *state);

    void _input(Ref<InputEvent> event);

	Ref<Texture> get_texture() const;
	void set_texture(const Ref<Texture>& _texture);

	void set_rearrange_destination(Vector2 destination);

	Rect2 get_sprite_rect() const;

	bool is_dragging() const;

	int32_t get_nutrient_id() const;
	void set_nutrient_id(int32_t _nutrient_id);

	int32_t get_cooking_id() const;
	void set_cooking_id(int32_t _cooking_id);

	int32_t get_additive_id() const;
	void set_additive_id(int32_t _additive_id);

private:
	int32_t get_item_slot_index_on(Vector2 mouse_position);
	void store_to_inventory(Vector2 mouse_position, int32_t inventory_slot_index);

private:
	CollisionShape2D* collision_shape;
	Ref<RectangleShape2D> rect_shape;
	Sprite2D* sprite;
	Ref<Texture> texture;

	Vector2 offset;
	bool dragging;
	

	int32_t nutrient_id;
	int32_t cooking_id;
	int32_t additive_id;
};

}

#endif