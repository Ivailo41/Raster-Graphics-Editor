#pragma once

enum class TextureScaleMode {
	INVALID = -1,
	NEAREST,
	LINEAR,
	PIXELART
};

class ITexture {
public:
	virtual ~ITexture() = default;
	virtual void UpdateTexture(const void* pixels, int pitch) = 0;
	virtual void* GetNativeTexture() const = 0;

	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
};