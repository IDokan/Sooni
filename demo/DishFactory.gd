extends Node
#
#signal spawn_dish_request(position: Vector2, tex: Texture2D)
#
#func _ready():
	#connect("spawn_dish_request", self, "_on_spawn_dish_request")
	#pass
#
#func _on_spawn_dish_request(position: Vector2, tex: Texture2D):
	#spawn_dish(position, tex)
	#pass

var will_spawn: bool = false
var texture
var target_slot: TextureRect

func prepare_spawner(tex: Texture2D):
	texture = tex
	will_spawn = true

func set_target_slot(_target_slot: TextureRect):
	target_slot = _target_slot
	
func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_LEFT and event.is_released():
			spawn_dish(event.global_position, texture)
			will_spawn = false

func spawn_dish(position: Vector2, tex: Texture2D) :
	
	if will_spawn == false:
		return
	
	if target_slot == null:
		return
	
	# user tries to store an item to another item slot
	if target_slot.get_global_rect().has_point(position):
		return
	
	var dish = Dish.new()
	dish.texture = tex
	dish.position = position
	get_tree().root.get_child(0).add_child(dish)
	
	
	

