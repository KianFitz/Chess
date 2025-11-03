#ifndef __H_CLIENT
#define __H_CLIENT

#include <cstdlib>
#include "Textures/ITextureMgr.h"
#include "Window/SDLWindow.h"
#include <memory>

class Client 
{
public:
	void Start();

private:
	std::unique_ptr<IWindow> m_window;
	std::unique_ptr<ITextureMgr> m_textureMgr;
};

#endif