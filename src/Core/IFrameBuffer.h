#pragma once
#include <stdint.h>

class IFrameBuffer {
public:
	virtual ~IFrameBuffer() = default;
	virtual void SetPixel(int x, int y, uint32_t color) = 0;
	virtual uint32_t GetPixel(int x, int y) const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual void SetSize(unsigned width, unsigned heigth) = 0;
	virtual void Clear(uint32_t color) = 0;
	virtual void* GetPixels() const = 0;
};