#
# Cloudy Client-side API binding
#
#                    written by pjc0247
#

require 'Win32API'

CLOUDY_DLL_PATH = "extension\\Cloudy-Ruby.dll"

def CloudyLoadAPI(name, param, ret)
	Win32API.new(CLOUDY_DLL_PATH , name, param, ret)
end


$cloudy_connect = CloudyLoadAPI("cloudy_connect", ['P','L'], 'L' )
$cloudy_login = CloudyLoadAPI("cloudy_login", ['P','P'], 'L' )

def CloudyConnect(ip, port)
	$cloudy_connect.Call(ip, port)
end
def CloudyLogin(id, pw)
	$cloudy_login.Call(id, pw)
end
def CloudyRegist(id, pw, nick)
	
end