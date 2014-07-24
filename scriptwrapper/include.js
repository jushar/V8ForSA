var isMTA = true; //isMTA();
var mtaFunctions = [
	"setWeather" : "setWeather",
	"getTime" : "getTime",
]
var sampFunctions = {
	"setWeather" : function(id) { return callNativeFunction("SetWeather", id); },
};
