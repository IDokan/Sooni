/******************************************************************************
Copyright (C)
File Name:   Nutrients.cpp
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 06.25.2024
	Source file for Nutrients.
******************************************************************************/
#include "Nutrients.h"

godot::Nutrients::Nutrients()
    : calories(), total_fat(), saturated_fat(), trans_fat(), 
    colesterol(), sodium(), total_carbohydrate(), dietary_fiber(),
    sugars(), protein()
{
}

godot::Nutrients::~Nutrients()
{
}

int32_t godot::Nutrients::get_calories() const
{
    return calories;
}

void godot::Nutrients::set_calories(int32_t _calories)
{
    calories = _calories;
}

int32_t godot::Nutrients::get_total_fat() const
{
    return total_fat;
}

void godot::Nutrients::set_total_fat(int32_t _total_fat)
{
    total_fat = _total_fat;
}

int32_t godot::Nutrients::get_saturated_fat() const
{
    return saturated_fat;
}

void godot::Nutrients::set_saturated_fat(int32_t _saturated_fat)
{
    saturated_fat = _saturated_fat;
}

int32_t godot::Nutrients::get_trans_fat() const
{
    return trans_fat;
}

void godot::Nutrients::set_trans_fat(int32_t _trans_fat)
{
    _trans_fat;
}

int32_t godot::Nutrients::get_colesterol() const
{
    return colesterol;
}

void godot::Nutrients::set_colesterol(int32_t _colesterol)
{
    colesterol = _colesterol;
}

int32_t godot::Nutrients::get_sodium() const
{
    return sodium;
}

void godot::Nutrients::set_sodium(int32_t _sodium)
{
    sodium = _sodium;
}

int32_t godot::Nutrients::get_total_carbohydrate() const
{
    return total_carbohydrate;
}

void godot::Nutrients::set_total_carbohydrate(int32_t _total_carbohydrate)
{
    total_carbohydrate = _total_carbohydrate;
}

int32_t godot::Nutrients::get_dietary_fiber() const
{
    return dietary_fiber;
}

void godot::Nutrients::set_dietary_fiber(int32_t _dietary_fiber)
{
    dietary_fiber = _dietary_fiber;
}

int32_t godot::Nutrients::get_sugars() const
{
    return sugars;
}

void godot::Nutrients::set_sugars(int32_t _sugars)
{
    sugars = _sugars;
}

int32_t godot::Nutrients::get_protein() const
{
    return protein;
}

void godot::Nutrients::set_protein(int32_t _protein)
{
    protein = _protein;
}
