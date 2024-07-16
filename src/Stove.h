/******************************************************************************
Copyright (C)
File Name:   Stove.h
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 7.4.2024
	Header file for a stove.
    It is a work-table to create a dish.
******************************************************************************/

#ifndef STOVE_H
#define STOVE_H

#include <godot_cpp/classes/node2d.hpp>

namespace godot {

enum CookingMethods
{
	Boiling = 0,
	Poaching,
	Steaming,
	Brasing,
	Frying,
	Roasting,
	Sauteing,	// Pronounce -> sa-u-tei :: səʊteɪ
	Blanching,
	// Where are grilling, 
};

class Texture2DArray;

class Stove : public Node2D {
	GDCLASS(Stove, Node2D)

protected:
	static void _bind_methods();

public:
	Stove();
	~Stove();

	void _ready();
	void _process(double delta) override;

	Ref<Texture2DArray> get_images() const;
	void set_images(const Ref<Texture2DArray>& images);

private:
	Ref<Texture2DArray> images;
};

}

#endif