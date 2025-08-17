#pragma once
#include "Window.h"
#include "ChiliTimer.h"
#include "Quad.h"

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void Update();
	void DoFrame();
private:
	Window wnd;
	ChiliTimer timer;
	Quad quad;
	float radius = 2;
	float centerX = 0;
	float centerY = 0;
};