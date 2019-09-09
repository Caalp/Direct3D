#pragma once
#include "Window.h"
#include "Timer.h"
class App
{
public:
	App();
	~App();
	int Go();
private:
	void Update();
private:
	Window wnd;
	Timer timer;
};