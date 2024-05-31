#include <rectangles_mapper.h>

using namespace godot;

godot::RectanglesMapper::RectanglesMapper(Size2 _size)
    : area(_size.x * _size.y)
{
    rectangles.push_back(std::vector<Rectangle>(1, Rectangle(_size)));
}

godot::RectanglesMapper::~RectanglesMapper()
{
}

bool godot::RectanglesMapper::process(std::vector<Rect2> rectangles_will_packed)
{
    const size_t rectangles_will_packed_size = rectangles_will_packed.size();
    
    for (size_t i = 0; i < rectangles_will_packed_size; i++)
    {
        if(step(rectangles_will_packed[i]) == false)
        {
            return false;
        }
    }

    return true;
}

std::vector<Vector2> godot::RectanglesMapper::get_positions() const
{
    return positions;
}

bool godot::RectanglesMapper::step(Rect2 rect)
{
    size_t x = 0;
    size_t y = 0;
    if(find_left_most_highest_available_cell(x, y, rect))
    {
        save_position(x, y);
        add_rectangle(x, y, rect);
        return true;
    }
    else
    {
        return false;
    }
}

bool godot::RectanglesMapper::find_left_most_highest_available_cell(size_t &x, size_t &y, Rect2 rect) const
{
    for (size_t j = x; j < rectangles[0].size(); j++)
    {
        // Search row first to find left most
        for (size_t i = y; i < rectangles.size(); i++)
        {
            if (is_available(j, i, rect))
            {
                x = j;
                y = i;
                return true;
            }
            
        }
        
    }

    return false;
}

void godot::RectanglesMapper::save_position(size_t x, size_t y)
{
    real_t sum_x = 0;
    real_t sum_y = 0;
    for (size_t i = 0; i < x; i++)
    {
        sum_x += rectangles[0][i].size.x;
    }

    for (size_t i = 0; i < y; i++)
    {
        sum_y += rectangles[i][0].size.y;
    }
    
    positions.push_back(Vector2(sum_x, sum_y));
}

// It check neighbor cells but do not tell us that we will use neighbors or not.
bool godot::RectanglesMapper::is_available(size_t x, size_t y, Rect2 rect) const
{
    // First things first, target cell should not be occupied
    if (rectangles[y][x].occupied == true)
    {
        return false;
    }

    const Size2 rect_size = rect.get_size();

    // If target cell has enough space to contain the rectangle. 
    if(rectangles[y][x].size.x >= rect_size.x && rectangles[y][x].size.y >= rect_size.y)
    {
        return true;
    }


    // If no space, try merging with neighbor rectangles.
    // Horizontal merge,
    real_t sum_x = rectangles[y][x].size.x;
    if (sum_x < rect_size.x)
    {

        for (size_t i = x + 1; i < rectangles[0].size(); i++)
        {
            if (rectangles[y][i].occupied == true)
            {
                return false;
            }
            
            sum_x += rectangles[y][i].size.x;
            

            if (sum_x >= rect_size.x)
            {
                break;
            }
        }
        
    }
    
    
    // Vertical merge,
    real_t sum_y = rectangles[y][x].size.y;
    if (sum_y < rect_size.y)
    {
        for (size_t i = y + 1; i < rectangles.size(); i++)
        {
            if (rectangles[i][x].occupied == true)
            {
                return false;
            }
            
            sum_y += rectangles[i][x].size.y;

            if (sum_y >= rect_size.y)
            {
                break;
            }
            
        }
    }

    return sum_x >= rect_size.x && sum_y >= rect_size.y;
}

void godot::RectanglesMapper::add_rectangle(size_t x, size_t y, Rect2 rect)
{
    // enlarge container
    size_t current_size = rectangles.size();
    for (size_t i = 0; i < rectangles.size(); i++)
    {
        rectangles[i].push_back(Rectangle());
    }
    rectangles.push_back(std::vector<Rectangle>(rectangles[0].size(), Rectangle()));
    
    const size_t start_x = x;
    const size_t start_y = y;
    
    // @@ ====================================================== @@
    // divide and update cells
    Size2 fill_rect_size = rect.get_size();

    // find end point of container if given rectangle is too big to contain.
    while(rectangles[y][x].size.x < fill_rect_size.x && x < rectangles[0].size())
    {
        fill_rect_size.x -= rectangles[y][x].size.x;
        x += 1;
    }

    real_t remain_x = rectangles[y][x].size.x - fill_rect_size.x;

    for (size_t i = 0; i < rectangles.size(); i++)
    {
        // shift horizontal data
        for (size_t j = rectangles[i].size() - 1; j >= x + 1; j--)
        {
            rectangles[i][j] = rectangles[i][j - 1];
        }

        // Update recently divided cells
        rectangles[i][x + 1].size.x = remain_x;
        rectangles[i][x].size.x = fill_rect_size.x;
    }
        
    while (rectangles[y][x].size.y < fill_rect_size.y && y < rectangles.size())
    {
        fill_rect_size.y -= rectangles[y][x].size.y;
        y += 1;
    }
    
    real_t remain_y = rectangles[y][x].size.y - fill_rect_size.y;

    for (size_t i = 0; i < rectangles[0].size(); i++)
    {
        // shift vertical data
        for (size_t j = rectangles.size() - 1; j >= y + 1; j--)
        {
            rectangles[j][i] = rectangles[j - 1][i];
        }

        // Update recently divided cells
        rectangles[y + 1][i].size.y = remain_y;
        rectangles[y][i].size.y = fill_rect_size.y;
                  
    }
    // @@ ====================================================== @@
    
    

    // mark up occupied
    for (size_t i = start_y; i <= y; i++)
    {
        for (size_t j = start_x; j <= x; j++)
        {
            rectangles[i][j].occupied = true;
        }
    }
}

godot::RectanglesMapper::Rectangle::Rectangle(Size2 _size, bool _occupied)
    : size(_size), occupied(_occupied)
{
}
