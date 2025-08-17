#include "App.h"
#include "Quad.h"
#include <memory>

App::App()
	:
	wnd( 1080, 1080,"Howie Mandelbrot" )
{
	quad.push_back( std::make_unique<Quad>(wnd.Gfx()) );
	// wnd.Gfx().SetProjection( DirectX::XMMatrixPerspectiveLH( 1.0f,3.0f / 4.0f,0.5f,40.0f ) ); // can we get rid of this? or just change to be normal view
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
		DoFrame();
	}
}

App::~App()
{}

void App::DoFrame()
{
	auto dt = timer.Mark();
	wnd.Gfx().ClearBuffer( 0,0,0 );
	for( auto& q : quad )
	{
		q->Update( dt );
		q->Draw( wnd.Gfx() );
	}
	wnd.Gfx().EndFrame();
}