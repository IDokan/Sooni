extends TextureRect

func _get_drag_data(_at_position):
	
	var drag_texture = TextureRect.new()
	drag_texture.expand_mode = 1
	drag_texture.texture = texture
	drag_texture.size = Vector2(100, 100)
	
	var control = Control.new()
	control.add_child(drag_texture)
	drag_texture.position = -0.5 * drag_texture.size
	set_drag_preview(control)
	
	texture = null
	
	return drag_texture.texture
	
func _can_drop_data(_at_position, data):
	return true
	
	
func _drop_data(_at_position, data):
	texture = data
	
	
	
	var dish = Dish.new()
	dish.texture = data
	
	
	dish.position = get_global_mouse_position()
	#get_global_transform_with_canvas().basis_xform(_at_position)
	
	get_tree().root.get_child(0).add_child(dish)
	
	pass
