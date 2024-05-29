#include <rectangles_mapper.h>
#include <godot_cpp/variant/rect2.hpp>

using namespace godot;

godot::RectanglesMapper::RectanglesMapper(Size2 _size)
    : area(_size.x * _size.y)
{
    rectangles.push_back(std::vector<Rectangle>(1, Rectangle(_size)));
}

godot::RectanglesMapper::~RectanglesMapper()
{
}

void godot::RectanglesMapper::process(std::vector<Rect2> rectangles_will_packed)
{
    const size_t rectangles_will_packed_size = rectangles_will_packed.size();
    
    for (size_t i = 0; i < rectangles_will_packed_size; i++)
    {
        step(rectangles_will_packed[i]);
    }
    
}

void godot::RectanglesMapper::step(Rect2 rect)
{

}

bool godot::RectanglesMapper::find_left_most_highest_available_cell(size_t &x, size_t &y) const
{
    for (size_t i = x; i < count; i++)
    {
        for (size_t j = y; j < count; j++)
        {
            /* code */
        }
        
    }
    

    return false;
}

godot::RectanglesMapper::Rectangle::Rectangle(Size2 _size, bool _occupied)
    : size(_size), occupied(_occupied)
{
}
