#pragma once
#include  <stdint.h>
#include "../Core/IFrameBuffer.h"

class IRasterizer {

public:
	virtual ~IRasterizer() = default;

	virtual void AttachFrameBuffer(IFrameBuffer* frameBuffer) = 0;

	virtual void DrawLineBresenham(int x0, int y0, int x1, int y1, uint32_t color, float progress) = 0;
	virtual void DrawLineSimple(int x0, int y0, int x1, int y1, uint32_t color, float progress) = 0;
	virtual void DrawCircleMidPoint(int x0, int y0, int radius, uint32_t color, float progress, bool bold) = 0;
};