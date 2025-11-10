#include "Client.h"
#include "Entities/Board.h"
#include <string>
#include "Textures/SDLTextureMgr.h"
#include "Entities/Piece.h"

int main(int /*argc*/, char** /*argv[]*/) {

	Client client;
	client.Start();

	return 0;
}

void Client::Start()
{
	m_window = std::make_unique<SDLWindow>();
	m_textureMgr = std::make_unique<SDLTextureMgr>();

	WindowCreationArgs args{
		.AppName = "Chess Game",
		.AppVersion = "0.1",
		.AppIdentifier = "com.kianfitz.chessgame",
		.ViewportWidth = 1920,
		.ViewportHeight = 1080
	};

	if (!m_window->Create(args))
	{
		return;
	}

	if (auto const& renderer = m_window->GetRenderer())
	{
		m_textureMgr->LoadTexture(*renderer, "pawn_black", R"(C:\Users\kianf\Documents\Development\Chess\images\pieces\black\pawn-b.svg)");
		m_textureMgr->LoadTexture(*renderer, "pawn_white", R"(C:\Users\kianf\Documents\Development\Chess\images\pieces\black\pawn-w.svg)");
	}


	// ** DEBUG CODE ** //
	auto const& texture = m_textureMgr->GetTexture("pawn_black");
	if (!texture) return;

	Piece blackPawn(*texture);
	blackPawn.SetPos(750, 250);

	m_window->AddChild<Board>();
	m_window->AddChild<Piece>(*texture, Vec2(750, 250));

	while (m_window->Running())
	{
		m_window->CheckForInput();
		m_window->BeginDraw();


		
		//// Game rendering logic here.
		//if (auto const& renderer = m_window->GetRenderer())
		//{
		//	chessBoard.Draw(renderer);
		//	blackPawn.Draw(renderer);
		//}

		m_window->Draw();
		
		m_window->FinishDraw();
	}

	m_window->Destroy();
}
