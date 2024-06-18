/******************************************************************************
Copyright (C)
File Name:   DishSlot.h
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 06.18.2024
	Header file for DishSlot.
	It is a slot of dish stored in the refrigerator (inventory)
******************************************************************************/
#ifndef DISHSLOT_H
#define DISHSLOT_H

#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/texture.hpp>

namespace godot {

class DishSlot : public TextureRect {
	GDCLASS(DishSlot, TextureRect)

protected:
	static void _bind_methods();

public:
	DishSlot();
	~DishSlot();

	void _ready();
	void _process(double delta) override;

    Ref<Texture> get_background_texture() const;
    void set_background_texture(const Ref<Texture>& _texture);
    Ref<Texture> get_slot_texture() const;
    void set_slot_texture(const Ref<Texture>& _texture);
    
    
	Variant _get_drag_data(const Vector2 &at_position) override;
	bool _can_drop_data(const Vector2 &at_position, const Variant &data) const override;
	void _drop_data(const Vector2 &at_position, const Variant &data) override;

private:
    TextureRect* slot;
    Ref<Texture> background_texture;
};

}

#endif