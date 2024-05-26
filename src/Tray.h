#ifndef TRAY_H
#define TRAY_H

#include <godot_cpp/classes/static_body2d.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>

namespace godot {

class Sprite2D;
class RectangleShape2D;
class CollisionShape2D;

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

private:
	CollisionShape2D* collision_shape;
	Ref<RectangleShape2D> rect_shape;
	Sprite2D* sprite;
	Ref<Texture> texture;
};

}

#endif