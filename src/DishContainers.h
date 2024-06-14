#ifndef DISHCONTAINERS_H
#define DISHCONTAINERS_H

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/input_event.hpp>


namespace godot {

class TextureRect;

class DishContainers : public CanvasLayer {
	GDCLASS(DishContainers, CanvasLayer)

protected:
	static void _bind_methods();

public:
	DishContainers();
	~DishContainers();

	void _ready();
	void _process(double delta) override;
    void _input(Ref<InputEvent> event);

    void prepare_spawner(Ref<Texture2D> texture);
    void set_target_slot(TextureRect* target_slot);
    void spawn_dish(Vector2 position, Ref<Texture2D> tex);
    void force_spawn_dish(Vector2 position, Ref<Texture2D> tex);    

private:
    bool will_spawn;
    Ref<Texture2D> texture;
    TextureRect* target_slot;
};

}

#endif