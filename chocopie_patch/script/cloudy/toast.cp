
class CloudyToast < GameObject
	@@frame = Sprite.new("cloudy\\frame.png")
	@@font = Font.new("HYPORM.ttf", 20)
	@@font.color = Color.White

	def initialize(msg)
		@msg = msg
		@size = @@font.query(msg)

		@x = $graphic.size.w / 2 - @size.w/2
		@y = $graphic.size.h / 2 - @size.h/2 - 150
		@w = @size.w + 30
		@h = @size.h + 10

		@text = @@font.render(msg)

		super(@x,@y,@@frame)

		@alpha = 350

		$layerInterface.add self
	end

	def draw(x,y)
		alpha = @alpha > 255 ? 255 : @alpha

		@@frame.alpha = alpha / 2
		@@frame.stretch(x,y,@w,@h)
		@text.alpha = alpha
		@text.draw(@x+15,@y+5)
	end
	def update
		super

		@alpha -= 1

		if @alpha == 0
			dispose
		end
	end
end