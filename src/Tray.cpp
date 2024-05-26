#include "Tray.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/physics_material.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

using namespace godot;

void godot::Tray::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_texture", "_texture"), &Tray::set_texture);
    ClassDB::bind_method(D_METHOD("get_texture"), &Tray::get_texture);
    ClassDB::add_property("Tray", PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");    
}

godot::Tray::Tray()
    : body_collision(memnew(CollisionShape2D)), body_collision_shape(memnew(RectangleShape2D)),
        sprite(memnew(Sprite2D)),
        area(memnew(Area2D)), area_collision(memnew(CollisionShape2D)), area_collision_shape(memnew(RectangleShape2D))
{
    
}

godot::Tray::~Tray()
{
}

void godot::Tray::_ready()
{
    sprite->set_centered(true);
    sprite->set_name("Sprite");
    add_child(sprite);
    sprite->set_owner(this);

    const Vector2 sprite_size = sprite->get_rect().size;
    body_collision_shape->set_size(sprite_size);
    body_collision->set_name("Collision Shape");
    body_collision->set_shape(body_collision_shape);
    add_child(body_collision);
    body_collision->set_owner(this);


    // Hierarchy: Body -> area -> area collision -> area collision rectangle shape
    area_collision_shape->set_size(Vector2(sprite_size.x, sprite_size.y * TRAY_VERTICAL_DETECT_RANGE));
    area_collision->set_name("Area Collision Shape");
    area_collision->set_shape(area_collision_shape);
    area->set_name("Area");
    area->add_child(area_collision);
    area_collision->set_owner(area);
    add_child(area);
    area->set_owner(this);
}

void godot::Tray::_process(double delta)
{
}

Ref<Texture> godot::Tray::get_texture() const
{
    return texture;
}

void godot::Tray::set_texture(const Ref<Texture> &_texture)
{
    texture = _texture;
    sprite->set_texture(texture);

    Vector2 sprite_size = sprite->get_rect().size;
    body_collision_shape->set_size(sprite_size);
    area_collision_shape->set_size(Vector2(sprite_size.x, sprite_size.y * TRAY_VERTICAL_DETECT_RANGE));
}
