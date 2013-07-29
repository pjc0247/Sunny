class CloudyBanner < WindowButton
	def initialize(x,y)
		super(x,y)
	
		@frame = Sprite.new("cloudy\\frame.png"); 
		@logo = Sprite.new("cloudy\\cloudy.png");

		@w = 400
		@h = 80

		@font = Font.new("gulim.ttc", 30)
		@font.color = Color.White
		@font.style = BOLD

		self.buttonPressedHandler = method(:login)

		@loginAni = 0
		@logoX = 195
	end

	def draw(x,y)
		if @state == NONE
			@alpha = 78
        elsif @state == HOT
			@alpha = 100
        elsif @state == DOWN
			@alpha = 120
        end

		@frame.alpha = @alpha
        @frame.color = @color
	    @frame.stretch(@x,@y,@w,@h)

		@logo.stretch(x+@logoX,y+10, 170, 60)

		if @loginAni < 255
			@font.alpha = 255-@loginAni
	        @font.draw(x+30,y+25, "Login to")
		elsif @loginAni < 255+85
			@logoX -= 2
		else
			@font.alpha = @loginAni - (255+85)
	        @font.draw(x+210,y+25, @loginedID)
		end

		if @loginAni > 0 and @loginAni < 255+85+255
			@loginAni += 1
		end
	end
	def update
		super		
	end

	def login(target, args)
		@loginForm = CloudyLogin.new($graphic.size.w/2 - 200, $graphic.size.h/2-110)
		@loginForm.loginedHandler = method(:logined)
	end

	def logined(target, args)
		@loginAni = 1
		@loginedID = args
	end
end