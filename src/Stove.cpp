#include "Stove.h"
/******************************************************************************
Copyright (C)
File Name:   Stove.cpp
Author
    - sinil.kang	rtd99062@gmail.com
Creation Date: 7.4.2024
    Source file for a stove.
    It is a work-table to create a dish.
******************************************************************************/

#include <godot_cpp/classes/texture2d_array.hpp>
using namespace godot;

void godot::Stove::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_images", "_images"), &Stove::set_images);
    ClassDB::bind_method(D_METHOD("get_images"), &Stove::get_images);
    ClassDB::add_property("Stove", PropertyInfo(Variant::OBJECT, "images", PropertyHint::PROPERTY_HINT_RESOURCE_TYPE, "Texture2DArray"), "set_images", "get_images");
}

godot::Stove::Stove()
{
}

godot::Stove::~Stove()
{
}

void godot::Stove::_ready()
{
}

void godot::Stove::_process(double delta)
{
}

Ref<Texture2DArray> godot::Stove::get_images() const
{
    return images;
}

void godot::Stove::set_images(const Ref<Texture2DArray> &_images)
{
    images = _images;
}
