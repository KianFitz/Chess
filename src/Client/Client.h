#ifndef __H_CLIENT
#define __H_CLIENT

#include <cstdlib>
#include "Window/SDLWindow.h"
#include <memory>

class Client 
{
public:
	void Start();

private:
	std::unique_ptr<IWindow> m_window;
};

#endif