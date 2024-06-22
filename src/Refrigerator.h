/******************************************************************************
Copyright (C)
File Name:   Refrigerator.h
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 06.18.2024
	Header file for Refrigerator class.
	It is an inventory for user. 
	Cooked dishes will be stored in here.
******************************************************************************/
#ifndef REFRIGERATOR_H
#define REFRIGERATOR_H

#include <godot_cpp/classes/canvas_layer.hpp>
#include <DishSlot.h>

namespace godot {

    class TextureButton;
    class NinePatchRect;
    class MarginContainer;
    class ScrollContainer;
    class GridContainer;
    

class Refrigerator : public CanvasLayer {
	GDCLASS(Refrigerator, CanvasLayer)

protected:
	static void _bind_methods();

public:
	Refrigerator();
	~Refrigerator();

	void _ready();
	void _process(double delta) override;

	Ref<Texture> get_refrigerator_background_texture() const;
	void set_refrigerator_background_texture(const Ref<Texture>& _texture);

	Ref<Texture> get_slot_background_texture() const;
	void set_slot_background_texture(const Ref<Texture>& _texture);

	Ref<Texture> get_tween_button_texture() const;
	void set_tween_button_texture(const Ref<Texture>& _texture);

	Vector2 get_size() const;
	void set_size(const Vector2& _size);

	Vector2 get_position() const;
	void set_position(const Vector2& _position);

	int32_t get_columns() const;
	void set_columns(int32_t _columns);

	int32_t get_dish_slots_count() const;
	const DishSlot* get_dish_slot(int32_t index) const;
	DishSlot* get_dish_slot(int32_t index);
	

private:
    void _on_texture_button_pressed();
	bool slide_flag;

private:
	TextureButton* texture_button;

    NinePatchRect* nine_patch_rect;
	MarginContainer* margin_container;
	ScrollContainer* scroll_container;
	GridContainer* grid_container;

	std::vector<DishSlot*> dish_slots;

	// Textures
	Ref<Texture> refrigerator_background_texture;
	Ref<Texture> slot_background_texture;
	Ref<Texture> tween_button_texture;

	Vector2 size;
	Vector2 position;
	int32_t columns;
};

}

#endif