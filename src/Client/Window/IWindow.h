#ifndef __H_WINDOW
#define __H_WINDOW

#include "../Renderers/IRenderer.h"
#include <string>

struct WindowCreationArgs
{
	std::string AppName;
	std::string AppVersion;
	std::string AppIdentifier;
	int ViewportWidth;
	int ViewportHeight;
};

class IWindow
{
public:
	virtual ~IWindow() = default;
	virtual bool Create(const WindowCreationArgs& args) = 0;
	virtual void CheckForInput() = 0;
	virtual void BeginDraw() = 0;
	virtual void FinishDraw() = 0;
	virtual void Destroy() = 0;
	virtual IRenderer* GetRenderer() const = 0;
	bool Running() const { return m_running; }
protected:
	bool m_running { true };
};





#endif