#pragma once
#include"../event/events.h"
using namespace events;

class BaseController {
public:
	function<void(ke& e)> onforward;
	function<void(ke& e)> onbackward;
	function<void(ke& e)> onleftward;
	function<void(ke& e)> onrightward;


};