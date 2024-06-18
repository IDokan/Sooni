/******************************************************************************
Copyright (C)
File Name:   rectangles_mapper.h
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 05.30.2024
	Header file for a special data container for packing rectangles problem.
    Details in the below link
        https://web.archive.org/web/20170914175015/https://www.codeproject.com/Articles/210979/Fast-optimizing-rectangle-packing-algorithm-for-bu
******************************************************************************/
#ifndef RECTANGLES_MAPPER_H
#define RECTANGLES_MAPPER_H

#include <vector>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/rect2.hpp>

namespace godot {

class Rect2;

class RectanglesMapper {
public:
	RectanglesMapper(Size2 _size);
	~RectanglesMapper();

    // Given array should be sorted from larger to smaller.
    bool process(std::vector<Rect2> rectangles_will_packed);
    std::vector<Vector2> get_positions() const;

private:
    struct Rectangle
    {
        Rectangle(Size2 _size = Size2(0, 0), bool _occupied = false);

        Size2 size;
        bool occupied;
    };

    // return false if adding a target rect is not available. 
    bool step(Rect2 rect);
    bool find_left_most_highest_available_cell(size_t &x, size_t &y, Rect2 rect) const;
    void save_position(size_t x, size_t y);
    bool is_available(size_t x, size_t y, Rect2 rect) const;
    void add_rectangle(size_t x, size_t y, Rect2 rect);

    real_t area;

    // 2-dimensional array -> helper container to calculate how to pack rectangles.
    std::vector<std::vector<Rectangle>> rectangles;
    std::vector<Vector2> positions;
};

}
#endif