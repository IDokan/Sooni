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

class Stove : public Node2D {
	GDCLASS(Stove, Node2D)

protected:
	static void _bind_methods();

public:
	Stove();
	~Stove();

	void _ready();
	void _process(double delta) override;

private:
	
};

}

#endif