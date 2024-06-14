extends TextureRect

func _get_drag_data(_at_position):
	
	var data = {}
	data["slot"] = self
	data["texture"] = texture
	
	# setup preview texture
	if texture != null:
		var drag_texture = TextureRect.new()
		drag_texture.expand_mode = 1
		drag_texture.texture = texture
		drag_texture.size = texture.get_size()
	
		var control = Control.new()
		control.add_child(drag_texture)
		drag_texture.position = -0.5 * drag_texture.size
		set_drag_preview(control)
	
	get_node("/root/Node2D/DishContainers").prepare_spawner(texture)
	texture = null
	
	return data
	
func _can_drop_data(_at_position, _data):
	# Need to add appropriate if condition
	if _data == null:
		return false
	
	get_node("/root/Node2D/DishContainers").set_target_slot(self)
	return true
	
	
func _drop_data(_at_position, data):
	if texture != null:
		data["slot"].texture = texture
	
	texture = data["texture"]
	pass
