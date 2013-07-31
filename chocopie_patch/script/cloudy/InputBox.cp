#NONE = 0
EDIT = 1

class InputBox < WindowBase
    include EventHandler

    attr_accessor :text, :default
	attr_accessor :password

    @@font = Font.new("gulim.ttc",20)
    @@font.style = BOLD

	@@frame = Sprite.new("cloudy\\inputbox.png")
	@@frame.blend = BLEND
	@@frame.colorkey = Color.Red

    def initialize(x,y,w,h)
        super(x,y,w,h)

        @default = ""        
        @text = ""
        @shown = ""
        @state = NONE

        @carrot = "_"
        
        @timerCarrot = Timer.new(700)
        @timerCarrot.start
        
        @length = 0

		@password = false
        
        self.getFocusHandler = method(:getFocus)
        self.lostFocusHandler = method(:lostFocus)
    end
    def dispose
        super
    end

    def drawText(x,y,msg,color=Color.Black,shadow=Color.Gray)
        @@font.color = shadow
        super(x+2,y+2,msg, @@font)
        @@font.color = color
        super(x,y,msg, @@font)
    end
    def draw(x=0,y=0)
        if @state == NONE
            @@frame.color = Color.new(255,255,255)
        elsif @state == EDIT
            @@frame.color = Color.new(230,230,230)
        end

		@@frame.alpha = @alpha
        @@frame.stretch(x,y,@w,@h)
        if @text.length == 0
            drawText(5,5, @default,
                    Color.new(30,30,30),Color.DarkGray)
        else
			if @password
				drawText(5,5, "*" * @text.length	)
			else
	            drawText(5,5, @shown)
			end
        end
    end
    def update
        super

		return if @visible == false

        if @timerCarrot.done
            if @carrot == "_"
                @carrot = ""
            else
                @carrot = "_"
            end
        end
        
        if @state == EDIT
            @text = getTextInput
            if @text.length != @length
                @length = @text.length
                @textChangedHandler.call(self,nil)
            end
            @shown = @text + @carrot
        end
    end

    def leftUp(x,y)
        setFocus self
    end
    
    def getFocus(e,args)
        @state = EDIT
        @text = ""
        startTextInput
    end
    def lostFocus(e,args)
        @state = NONE
        endTextInput
    end
    
    
    def initializeHandler
        super
        self.textChangedHandler = method(:nullHandler)
    end
    def textChangedHandler=(handler)
        @textChangedHandler = handler
    end
end