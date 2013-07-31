require 'Win32API'

CLOUDY_DLL_PATH = "extension\\Cloudy-Ruby.dll"

$cloudy_connect = Win32API.new(CLOUDY_DLL_PATH , "cloudy_connect", ['P','L'], 'L' )
$cloudy_login = Win32API.new(CLOUDY_DLL_PATH , "cloudy_login", ['P','P'], 'L' )

def CloudyConnect(ip, port)
	$cloudy_connect.Call(ip, port)
end
def CloudyLogin(id, pw)
	$cloudy_login.Call(id, pw)
end