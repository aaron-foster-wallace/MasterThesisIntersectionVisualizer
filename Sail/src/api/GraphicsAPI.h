#pragma once

#include "../utils/Utils.h"

class Win32Window;

class GraphicsAPI {
public:
	enum DepthMask {
		NO_MASK,
		WRITE_MASK,
		BUFFER_DISABLED
	};
	enum Culling {
		NO_CULLING,
		FRONTFACE,
		BACKFACE
	};
	enum Blending {
		NO_BLENDING,
		ALPHA,
		ADDITIVE
	};

public:
	GraphicsAPI() { };
	~GraphicsAPI() { };

	virtual bool init(Win32Window* window) = 0;
	virtual void clear(const DirectX::SimpleMath::Vector4& color) = 0;
	virtual void setDepthMask(DepthMask setting) = 0;
	virtual void setFaceCulling(Culling setting) = 0;
	virtual void setBlending(Blending setting) = 0;
	virtual void present(bool vsync = false) = 0;

protected:

private:

};