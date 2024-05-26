#include "Tray.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/physics_material.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

using namespace godot;

void godot::Tray::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_texture", "_texture"), &Tray::set_texture);
    ClassDB::bind_method(D_METHOD("get_texture"), &Tray::get_texture);
    ClassDB::add_property("Tray", PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");    
}

godot::Tray::Tray()
    : sprite(memnew(Sprite2D)), rect_shape(memnew(RectangleShape2D))
{
    collision_shape = memnew(CollisionShape2D);
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

    rect_shape->set_size(sprite->get_rect().size);
    collision_shape->set_name("Collision Shape");
    collision_shape->set_shape(rect_shape);
    add_child(collision_shape);
    collision_shape->set_owner(this);
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

    rect_shape->set_size(sprite->get_rect().size);
}
