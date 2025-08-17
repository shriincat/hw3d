#include "App.h"
#include "Quad.h"
#include <memory>

App::App()
	:
	wnd( 1080, 1080,"Howie Mandelbrot" ),
	quad(Quad(wnd.Gfx()))
{
}

int App::Go()
{
	while( true )
	{
		// process all messages pending, but to not block for new messages
		if( const auto ecode = Window::ProcessMessages() )
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		Update();
		DoFrame();
	}
}

App::~App()
{}

void App::Update()
{
	float dt = timer.Mark();
	if (wnd.kbd.KeyIsPressed('R'))
	{
		radius /= 1.01f;
	}
	else if (wnd.kbd.KeyIsPressed('F'))
	{
		if (radius * 1.1f <= 2.0f)
		{
			radius *= 1.01f;
		}
	}
	if (wnd.kbd.KeyIsPressed('W'))
	{
		if (centerY + dt <= 2.0f)
		{
			centerY += dt * radius;
		}
	}
	else if (wnd.kbd.KeyIsPressed('S'))
	{
		if (centerY - dt >= -2.0f)
		{
			centerY -= dt * radius;
		}
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		if (centerX + dt <= 2.0f)
		{
			centerX += dt * radius;
		}
	}
	else if (wnd.kbd.KeyIsPressed('A'))
	{
		if (centerX - dt >= -2.0f)
		{
			centerX -= dt * radius;
		}
	}
	quad.SetViewCenter(centerX, centerY);
	quad.SetViewRadius(radius);
}

void App::DoFrame()
{
	wnd.Gfx().ClearBuffer( 0,0,0 );
	quad.Draw( wnd.Gfx() );
	wnd.Gfx().EndFrame();
}