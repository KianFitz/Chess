#ifndef __H_WINDOW
#define __H_WINDOW

#include "../Renderers/IRenderer.h"
#include <string>
#include <vector>
#include "../Entities/IDrawable.h"

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
	virtual void Draw() = 0;
	virtual void FinishDraw() = 0;
	virtual void Destroy() = 0;
	virtual IRenderer* GetRenderer() const = 0;

	template<typename T, typename... Args>
	void AddChild(Args&&... args)
	{
		static_assert(std::is_base_of_v<IDrawable, T>, "T must derive from IDrawable");
		m_children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
	}

	bool Running() const { return m_running; }
protected:
	bool m_running { true };
	std::vector<std::unique_ptr<IDrawable>> m_children;

};





#endif