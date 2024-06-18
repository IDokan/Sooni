extends CanvasLayer

var flag : bool

# Called when the node enters the scene tree for the first time.
func _ready():
	flag = true
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_texture_button_pressed():
	var tween = create_tween()
	if flag:
		tween.tween_property(self, "offset", Vector2(298, 0), 1)
		flag = false
	else:
		tween.tween_property(self, "offset", Vector2(0, 0), 1)
		flag = true
	pass # Replace with function body.
