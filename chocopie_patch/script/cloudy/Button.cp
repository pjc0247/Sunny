# encoding: utf-8

class CloudyButton < WindowButton
	@@frame = Sprite.new("cloudy\\frame.png");
	@@font = Font.new("gulim.ttc", 20)
	@@font.color = Color.White
	@@font.style = BOLD

	def initialize(x,y,w,h, text)
		super(x,y, w,h)

		@img = @@frame
		@text = text

		@alpha = 255
	end

	def draw(x,y)
		if @state == NONE
            @img.alpha = 0.5 * @alpha
        elsif @state == HOT
            @img.alpha = 0.65 * @alpha
        elsif @state == DOWN
            @img.alpha = 0.8 * @alpha
        end

	    @img.stretch(@x,@y,@w,@h)

		size = @@font.query(@text)

		@@font.alpha = @alpha
        @@font.draw x+@w/2-size.w/2,y+@h/2-size.h/2,@text
	end
end