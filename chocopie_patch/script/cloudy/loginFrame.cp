# encoding: utf-8

import 'cloudy/InputBox.cp'
import 'cloudy/Button.cp'

class CloudyLogin < WindowBase
	def initialize(x,y)
		super(x,y, 400,220)
			puts "init cloudy box"
	
		@frame = Sprite.new("cloudy\\frame.png")
		@logo = Sprite.new("cloudy\\cloudy.png")
		@close = Sprite.new("cloudy\\x.png")

		@font = Font.new("gulim.ttc", 30)
		@font.color = Color.White
		@font.style = BOLD
		
		@tooltipFont = Font.new("gulim.ttc", 18)
		@tooltipFont.color = Color.White
		
		@id = InputBox.new(x+110,y+70,235,30)
		@pw = InputBox.new(x+110,y+125,235,30)

		@pw.password = true

		@btnLogin = CloudyButton.new(x+260,y+167,110,40, "Login")
		@btnAbout = CloudyButton.new(x+20,y+167,170,40, "About Cloudy")
		@btnClose = WindowButton.new(x+360,y-10)
		
		@btnLogin.buttonPressedHandler = method(:login)
		@btnClose.buttonPressedHandler = method(:close)
		@btnAbout.buttonPressedHandler = method(:about)

		@btnClose.img = @close

		fp = File.new("script\\cloudy\\about.txt", "r")
		@tooltipText = fp.read
		fp.close

		$layerWindow.delete self
		$layerWindow.delete @id
		$layerWindow.delete @pw
		$layerWindow.delete @btnLogin
		$layerWindow.delete @btnClose
		$layerWindow.delete @btnAbout

		$layerInterface.add self
		$layerInterface.add @id
		$layerInterface.add @pw
		$layerInterface.add @btnLogin
		$layerInterface.add @btnClose
		$layerInterface.add @btnAbout

		$layerWindow.freeze

		@alpha = 140
	end
	def dispose
		super

		$layerWindow.unfreeze
	end

	def draw(x,y)
		@frame.alpha = @alpha
	    @frame.stretch(@x,@y,@w,@h)

		@logo.draw(x-20,y-30)

		if @tooltip == nil
		    @font.draw(x+40,y+70, "ID")
			@font.draw(x+40,y+125, "PW")
		else
			@tooltipFont.draw(x+20,y+75, @tooltipText)
		end
	end
	def update
		super
	end 

	def close(target, args)
		dispose
	end
	def login(target, args)
		@loginedHandler.call self, @id.text
		
		dispose
	end
	def about(target, args)
		if @tooltip
			@id.visible = true
			@pw.visible = true
			@btnLogin.visible = true

			@tooltip = nil

			@btnAbout.text = "About Cloudy"
		else
			@id.visible = false
			@pw.visible = false
			@btnLogin.visible = false

			@tooltip = true

			@btnAbout.text = "back"
		end
	end

	def initializeHandler
		loginedHandler = method(:nullHandler)
	end
	def loginedHandler=(handler)
		@loginedHandler = handler
	end
end