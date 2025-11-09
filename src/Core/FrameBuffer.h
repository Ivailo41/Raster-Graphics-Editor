#pragma once
#include "IFrameBuffer.h"

class FrameBuffer : public IFrameBuffer {

public:
	FrameBuffer(int width, int height);
	virtual ~FrameBuffer() override;

	virtual void SetPixel(int x, int y, uint32_t color) override;
	virtual uint32_t GetPixel(int x, int y) const override;

	virtual int GetWidth() const override { return m_Width; }
	virtual int GetHeight() const override { return m_Height; }
	virtual void SetSize(unsigned width, unsigned height);
	virtual void Clear(uint32_t color) override;

	virtual void* GetPixels() const override { return (void*)m_Pixels; }

private:
	int m_Width;
	int m_Height;
	uint32_t* m_Pixels;
};