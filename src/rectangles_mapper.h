#ifndef RECTANGLES_MAPPER_H
#define RECTANGLES_MAPPER_H

#include <vector>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class Rect2;

class RectanglesMapper {
public:
	RectanglesMapper(Size2 _size);
	~RectanglesMapper();

    // Given array should be sorted from larger to smaller.
    void process(std::vector<Rect2> rectangles_will_packed);

private:
    struct Rectangle
    {
        Rectangle(Size2 _size = Size2(0, 0), bool _occupied = false);

        Size2 size;
        bool occupied;
    };

    void step(Rect2 rect);
    bool find_left_most_highest_available_cell(size_t &x, size_t &y) const;

    real_t area;

    // 2-dimensional array -> helper container to calculate how to pack rectangles.
    std::vector<std::vector<Rectangle>> rectangles;
};

}
#endif