#include "SDLWindow.h"


bool SDLWindow::Create(const WindowCreationArgs& args) 
{
	SDL_SetAppMetadata(args.AppName.c_str(), args.AppVersion.c_str(), args.AppIdentifier.c_str());

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_Log("Couldn't init SDL, error: %s", SDL_GetError());
		return false;
	}

	m_window = SDLWindowPtr(SDL_CreateWindow(args.AppName.c_str(), args.ViewportWidth, args.ViewportHeight, SDL_WINDOW_RESIZABLE));

	if (!m_window)
	{
		return false;
		// Do stuff
	}

	m_renderer = SDLRendererPtr(SDL_CreateRenderer(m_window.get(), nullptr));

	if (!m_renderer)
	{
		return false;
	}

	SDL_SetRenderLogicalPresentation(m_renderer.get(), args.ViewportWidth, args.ViewportHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	SDL_ShowWindow(m_window.get());

	return true;
}

void SDLWindow::Update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			m_running = true;
		}
	}

	SDL_RenderClear(m_renderer.get());
	SDL_RenderPresent(m_renderer.get());
}

void SDLWindow::Destroy()
{
	
}

