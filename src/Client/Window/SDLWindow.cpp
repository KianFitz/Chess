#include "SDLWindow.h"
#include "../Entities/Board.h"


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

	m_baseRenderer = SDLRendererPtr(SDL_CreateRenderer(m_window.get(), nullptr));

	if (!m_baseRenderer)
	{
		return false;
	}

	m_renderer = std::make_unique<SDLRenderer>();
	m_renderer->SetBaseRenderer(m_baseRenderer.get());

	SDL_SetRenderLogicalPresentation(m_baseRenderer.get(), args.ViewportWidth, args.ViewportHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	SDL_ShowWindow(m_window.get());

	return true;
}

void SDLWindow::CheckForInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		{
			// Check for rectangle underneath mouse pointer.

			SDL_FPoint mouseLoc;
			SDL_GetMouseState(&mouseLoc.x, &mouseLoc.y);

			// Calculate which square is being clicked on.
			constexpr float X_OFFSET = 576.0f;
			constexpr float Y_OFFSET = 156.0f;
			constexpr float TILE_SIZE = 96.0f;

			float adjustedMouseX = mouseLoc.x - X_OFFSET;
			float adjustedMouseY = mouseLoc.y - Y_OFFSET;

			if (adjustedMouseX < 0 || adjustedMouseY < 0 ||
				adjustedMouseX > 8 * TILE_SIZE || adjustedMouseY > 8 * TILE_SIZE) {
				// Not clicked on board.
				break;
			}

			auto row = static_cast<uint8_t>(adjustedMouseY / TILE_SIZE);
			auto col = static_cast<uint8_t>(adjustedMouseX / TILE_SIZE);

			// Mark the clicked tile on the first Board child (if any)
			for (auto& child : m_children)
			{
				if (auto board = dynamic_cast<Board*>(child.get()))
				{
					board->SelectSquare(static_cast<int>(row), static_cast<int>(col));
					break;
				}
			}

			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_UP:
		{
			// If holding object, drop it

			break;
		}

		case SDL_EVENT_QUIT:
			m_running = false;
			break;
		}
	}
}

void SDLWindow::Draw()
{
	for (auto const& child : m_children) {
		child.get()->Draw(GetRenderer());
	}
}

void SDLWindow::Destroy()
{
	
}

