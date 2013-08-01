# encoding: utf-8

import 'cloudy/InputBox.cp'
import 'cloudy/Button.cp'
import 'cloudy/Toast.cp'

import 'cloudy/api.cp'

class CloudyLogin < WindowBase
	def initialize(x,y)
		super(x,y, 400,235)
			puts "init cloudy box"
			
		@frame = Sprite.new("cloudy\\frame.png")
		@logo = Sprite.new("cloudy\\cloudy.png")
		@close = Sprite.new("cloudy\\x.png")

		@font = Font.new("gulim.ttc", 30)
		@font.color = Color.White
		@font.style = BOLD
		
		@tooltipFont = Font.new("gulim.ttc", 18)
		@tooltipFont.color = Color.White
		
		@id = InputBox.new(x+110,y+75,235,30)
		@pw = InputBox.new(x+110,y+120,235,30)
		@nick = InputBox.new(x+110,y+165,235,30)

		@pw.password = true
		@nick.visible = false

		@btnLogin = CloudyButton.new(x+265,y+175,110,40, "Login")
		@btnAbout = CloudyButton.new(x+25,y+175,100,40, "Info")
		@btnRegist = CloudyButton.new(x+140,y+175,110,40, "Regist")
		@btnClose = WindowButton.new(x+360,y-10)
		
		@btnLogin.buttonPressedHandler = method(:login)
		@btnClose.buttonPressedHandler = method(:close)
		@btnAbout.buttonPressedHandler = method(:about)
		@btnRegist.buttonPressedHandler = method(:regist)

		@btnClose.img = @close

		fp = File.new("script\\cloudy\\about.txt", "r")
		@tooltipText = fp.read
		fp.close

		$layerWindow.delete self
		$layerWindow.delete @id
		$layerWindow.delete @pw
		$layerWindow.delete @nick
		$layerWindow.delete @btnLogin
		$layerWindow.delete @btnClose
		$layerWindow.delete @btnAbout
		$layerWindow.delete @btnRegist

		$layerInterface.add self
		$layerInterface.add @id
		$layerInterface.add @pw
		$layerInterface.add @nick
		$layerInterface.add @btnLogin
		$layerInterface.add @btnClose
		$layerInterface.add @btnAbout
		$layerInterface.add @btnRegist

		$layerWindow.freeze

		@state = "login"
		@ani = 0
		@aniDir = 0
		@alpha = 140

		@shakeTick = 0
		@shakeDuration = 0
		@shakeDir = 1
		@originalPos = Array.new

		@originalPos.push Point.new(@x,@y)

		$layerInterface.o.each do |key|
			@originalPos.push Point.new(key.x, key.y)
		end
	end
	def dispose
		super

		$layerWindow.unfreeze
	end

	def draw(x,y)
		@frame.alpha = @alpha
	    @frame.stretch(@x,@y,@w,@h)

		@logo.draw(x-20,y-30)

		if @state == "login"
		    @font.draw(x+40,y+75, "ID")
			@font.draw(x+32,y+120, "PW")
		elsif @state == "regist"
			@font.alpha = 255
			@font.draw(x+40,y+75, "ID")
			@font.draw(x+32,y+120, "PW")

			@font.alpha = @ani * 6.3
			@font.draw(x+27,y+165, "Nick")
		else
			@tooltipFont.draw(x+20,y+75, @tooltipText)
		end
	end
	def update
		super
		
		if @shakeTick > 0
			if getTicks - @shakeTick >= @shakeDuration
				@shakeTick = 0
				@shakeDuration = 0

				for i in 0..$layerInterface.size-1
					$layerInterface.o[i].x = @originalPos[i+1].x
					$layerInterface.o[i].y = @originalPos[i+1].y
				end
	
				@x = @originalPos[0].x
				@y = @originalPos[0].y
			else				
				sx =  4 * @shakeDir
				sy =  0 * @shakeDir
				@shakeDir *= -1

				$layerInterface.o.each do |key|
					key.x += sx
					key.y += sy
				end

				@x += sx
				@y += sy
			end
		end

		if @state == "regist"
			if @aniDir != 0
				@ani += @aniDir
				@h += @aniDir

				@btnAbout.y += @aniDir
				@btnRegist.y += @aniDir
				@btnLogin.y += @aniDir

				@nick.alpha = 6.3 * @ani

				@btnLogin.alpha = 6.3 * (40-	@ani)
				@btnRegist.x = @x+140 + @ani * 3.1
			end
			
			if @aniDir == 1 and @ani == 40
				@aniDir = 0

				@nick.visible = true
				@btnLogin.visible = false
				@id.focus
			end
			if @aniDir == -1 and @ani == 0
				@aniDir = 0
				@state = "login"
				@font.alpha = 255

				
				@nick.visible = false
			end
		end
	end 

	def close(target, args)
		dispose
	end	
	def login(target, args)
		if @id.text.length < 6 or @pw.text.length < 6
			shake 200
		else
			if CloudyConnect("127.0.0.1", 9919) == 0
				CloudyToast.new("Cannot connect to server")
				return
			end
			
#			CloudyLogin(@id.text, @pw.text)

			@loginedHandler.call self, @id.text
		
			dispose
		end
	end
	def about(target, args)
		if @state == "info"
			@id.visible = true
			@pw.visible = true
			@btnLogin.visible = true
			@btnRegist.visible = true

			@state = "login"

			@btnAbout.text = "Info"
		else
			@id.visible = false
			@pw.visible = false
			@btnLogin.visible = false
			@btnRegist.visible = false
		
			@state = "info"

			@btnAbout.text = "Back"
		end
	end
	def regist(target, args)
		if @state == "regist"
			@aniDir = -1

			@btnLogin.visible = true
			@btnAbout.text = "Info"

			@btnAbout.buttonPressedHandler = method(:about)
			@btnRegist.buttonPressedHandler = method(:regist)
		else
			@state = "regist"

			@ani = 0
			@aniDir = 1

			@nick.visible = true
			@btnAbout.text = "Back"

			@btnAbout.buttonPressedHandler = method(:regist)
			@btnRegist.buttonPressedHandler = method(:doRegist)
		end
	end
	
	# 실제로 네트워크로 회원가입을 진행하는 콜백
	def doRegist(target, args)
	end


	def shake(duration)
		@shakeTick = getTicks
		@shakeDuration = duration
	end

	def initializeHandler
		loginedHandler = method(:nullHandler)
	end
	def loginedHandler=(handler)
		@loginedHandler = handler
	end
end