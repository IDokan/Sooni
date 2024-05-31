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

private:
	CollisionShape2D* collision_shape;
	Ref<RectangleShape2D> rect_shape;
	Sprite2D* sprite;
	Ref<Texture> texture;

	Vector2 offset;
	bool dragging;
};

}

#endif