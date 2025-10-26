#ifndef __H_WINDOW
#define __H_WINDOW


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
	virtual void Update() = 0;
	virtual void Destroy() = 0;
	bool Running() const { return m_running; }
protected:
	bool m_running { true };
};





#endif