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

    void prepare_spawner(Ref<Texture2D> _texture, Vector2 _offset = Vector2());
    void set_target_slot(TextureRect* _target_slot);
    void spawn_dish(Vector2 _position, Ref<Texture2D> _tex);
    // Does not care drag&drop logics, spawns a dish on the place.
    // Currently it is used by when swapped with inventory item
    void force_spawn_dish(Vector2 _position, Ref<Texture2D> _tex);

    bool is_any_dish_dragging() const;

private:
    bool will_spawn;
    Vector2 offset;
    Ref<Texture2D> texture;
    TextureRect* target_slot;
};

}

#endif