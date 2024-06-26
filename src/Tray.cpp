/******************************************************************************
Copyright (C)
File Name:   Tray.cpp
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 05.26.2024
	Source file for Tray class.
******************************************************************************/
#include "Tray.h"

#include <algorithm>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/physics_material.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/texture_button.hpp>
#include <Dish.h>
#include <rectangles_mapper.h>

using namespace godot;

void godot::Tray::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_texture", "_texture"), &Tray::set_texture);
    ClassDB::bind_method(D_METHOD("get_texture"), &Tray::get_texture);
    ClassDB::add_property("Tray", PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");    

    ClassDB::bind_method(D_METHOD("rearrange"), &Tray::rearrange);
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

    // Connect a member function to a signal
    TextureButton* rearrange_button = Object::cast_to<TextureButton>(get_node<TextureButton>(NodePath("%TextureButton")));
    if(rearrange_button != nullptr)
    {
        rearrange_button->connect("pressed", callable_mp(this, &Tray::rearrange));
    }
    else
    {
        UtilityFunctions::print("Connect to a rearrange button has failed!");
    }
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

void godot::Tray::rearrange()
{
    // Print name of detected bodies.
    TypedArray<Node2D> overlapping_bodies = area->get_overlapping_bodies();
        
    Area2D* table_area = Object::cast_to<Area2D>(get_node<Area2D>(NodePath("%DiningTable")));
    if(table_area == nullptr)
    {
        UtilityFunctions::print("Failed to find Table area.");
        return;
    }

    CollisionShape2D* table_area_shape = Object::cast_to<CollisionShape2D>(table_area->get_child(0));
    if(table_area_shape == nullptr)
    {
        UtilityFunctions::print("table_area_shape is nullptr!");
        return;
    }
    
    const Rect2 table_rect = table_area_shape->get_shape()->get_rect();
    const int body_size = overlapping_bodies.size();

    std::vector<Dish*> dishes;
    for (size_t i = 0; i < body_size; i++)
    {
        Dish* dish = Object::cast_to<Dish>(overlapping_bodies[i]);
        if(dish != nullptr)
        {
            dishes.push_back(dish);
        }
    }

    std::sort(dishes.begin(), dishes.end(), [](Dish *lhs, Dish *rhs)
    {
        return lhs->get_sprite_rect().size.y >= rhs->get_sprite_rect().size.y;
    }
    );

    std::vector<Rect2> dish_rectangles;
    for (size_t i = 0; i < dishes.size(); i++)
    {
        dish_rectangles.push_back(dishes[i]->get_sprite_rect());
    }
    
    // @@ TODO: Need to handle if mapper failed packing.
    RectanglesMapper mapper(table_rect.size);
    mapper.process(dish_rectangles);
    std::vector<Vector2> positions = mapper.get_positions();
    for (size_t i = 0; i < dishes.size(); i++)
    {
        dishes[i]->set_rearrange_destination(table_area->to_global(positions[i] + (dishes[i]->get_sprite_rect().get_size() / 2)));
    }
    
}
