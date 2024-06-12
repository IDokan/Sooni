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
	
	DishFactory.prepare_spawner(texture)
	texture = null
	
	return drag_texture.texture
	
func _can_drop_data(_at_position, data):
	# Need to add appropriate if condition
	DishFactory.set_target_slot(self)
	return true
	
	
func _drop_data(_at_position, data):
	texture = data
	pass
