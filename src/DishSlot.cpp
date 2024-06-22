/******************************************************************************
Copyright (C)
File Name:   DishSlot.cpp
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 06.18.2024
	Source file for DishSlot.
******************************************************************************/
#include "DishSlot.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "DishContainers.h"

using namespace godot;

void godot::DishSlot::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_background_texture", "_texture"), &DishSlot::set_background_texture);
    ClassDB::bind_method(D_METHOD("get_background_texture"), &DishSlot::get_background_texture);
    ClassDB::add_property("DishSlot", PropertyInfo(Variant::OBJECT, "Texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_background_texture", "get_background_texture");
}

godot::DishSlot::DishSlot()
    : slot(memnew(TextureRect))
{
}

godot::DishSlot::~DishSlot()
{
}

void godot::DishSlot::_ready()
{
    slot->set_name("Slot");
    add_child(slot);
    slot->set_owner(this);

    set_texture(ResourceLoader::get_singleton()->load("res://InventoryBg.png"));
}

void godot::DishSlot::_process(double delta)
{
}

Ref<Texture> godot::DishSlot::get_background_texture() const
{
    return background_texture;
}

void godot::DishSlot::set_background_texture(const Ref<Texture> &_texture)
{
    background_texture = _texture;
}

Ref<Texture> godot::DishSlot::get_slot_texture() const
{
    return slot->get_texture();
}

void godot::DishSlot::set_slot_texture(const Ref<Texture> &_texture)
{
    slot->set_texture(_texture);
}

Variant godot::DishSlot::_get_drag_data(const Vector2 &at_position)
{
    DishContainers* dish_containers = get_node<DishContainers>("/root/Node2D/DishContainers");
    if(dish_containers->is_any_dish_dragging() || get_slot_texture() == nullptr)
    {
        return Variant();
    }

    Dictionary data;
    data["slot"] = this;
    data["texture"] = slot->get_texture();

    Vector2 offset = get_global_rect().get_center() - get_global_mouse_position();

    if(slot->get_texture() != nullptr)
    {
        TextureRect* drag_texture = memnew(TextureRect);
        drag_texture->set_expand_mode(EXPAND_IGNORE_SIZE);
        drag_texture->set_texture(slot->get_texture());
        drag_texture->set_size(slot->get_rect().size);
        drag_texture->set_position(-0.5 * drag_texture->get_size() + offset);

        Control* control = memnew(Control);
        control->add_child(drag_texture);
        set_drag_preview(control);
    }

    dish_containers->prepare_spawner(slot->get_texture(), offset);
    slot->set_texture(nullptr);

    return data;
}

bool godot::DishSlot::_can_drop_data(const Vector2 &at_position, const Variant &data) const
{
    if (data.get_type() == Variant::Type::NIL)
    {
        return false;
    }
    
    // @@ TODO: might be improved..?
    TextureRect* tmp = dynamic_cast<TextureRect*>(const_cast<DishSlot*>(this));
    get_node<DishContainers>("/root/Node2D/DishContainers")->set_target_slot(tmp);

    return true;
}

void godot::DishSlot::_drop_data(const Vector2 &at_position, const Variant &data)
{
    // @@ TODO: Below codes are buggy. Should debugged it.
        // The possible reason why bugs happened: when cast Variant data to Dictionary, Ref<Texture2D> bugs happened! 
        // Need to debugged it first. Then need to change all slots to this class and test it.

    Dictionary dictionary = (Dictionary)data;
    
    // Update origin slot data
    if (slot->get_texture() != NULL)
    {
        DishSlot* dragged_slot = Object::cast_to<DishSlot>(dictionary["slot"]);
        if(dragged_slot == nullptr)
        {
            UtilityFunctions::print("Dragged slot data is NULL!");
            return;
        }
        dragged_slot->set_slot_texture(slot->get_texture());
    }

    Ref<Texture2D>dragged_texture = (Ref<Texture2D>)(dictionary["texture"]);
    if(dragged_texture == nullptr)
    {
        UtilityFunctions::print("Dragged texture data is NULL!");
        return; 
    }
    slot->set_texture(*dragged_texture);
}
