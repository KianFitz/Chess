#ifndef __H_ITEXTUREMGR
#define __H_ITEXTUREMGR

#include <string>
#include <memory>
#include "../Renderers/IRenderer.h"
#include <unordered_map>

class ITexture;
class ITextureMgr
{
public:
	virtual void LoadTexture(const IRenderer& renderer, const std::string& name, const std::string& path) = 0;

	ITexture* GetTexture(const std::string& name) const {
		auto it = m_textures.find(name);

		if (it != m_textures.end())
		{
			return it->second.get();
		}

		return nullptr;
	}

	void DestroyTexture(const std::string& name) { m_textures.erase(name); }

protected:
	std::unordered_map<std::string, std::unique_ptr<ITexture>> m_textures;
};

#endif