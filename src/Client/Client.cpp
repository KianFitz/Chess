#include "Client.h"
#include <string>


std::string APP_NAME = "Chess Game";
std::string APP_VERSION = "0.1";
std::string APP_IDENTIFIER = "com.kianfitz.chessgame";



int main(int /*argc*/, char** /*argv[]*/) {

	Client client;
	client.Start();

	return 0;
}

void Client::Start()
{
	m_window = std::make_unique<SDLWindow>();

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

	while (m_window->Running())
	{
		m_window->Update();
	}

	m_window->Destroy();
}
