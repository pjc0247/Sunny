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

		@alpha = 120
	end

	def draw(x,y)
		if @state == NONE
            @alpha = 120
        elsif @state == HOT
            @alpha = 150
        elsif @state == DOWN
            @alpha = 180
        end

		@img.alpha = @alpha
	    @img.stretch(@x,@y,@w,@h)

		size = @@font.query(@text)

        @@font.draw x+@w/2-size.w/2,y+@h/2-size.h/2,@text
	end
end