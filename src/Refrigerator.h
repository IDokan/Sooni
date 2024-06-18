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

private:
    
};

}

#endif