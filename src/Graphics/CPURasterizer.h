#pragma once

#include "IRasterizer.h"
class CPURasterizer : public IRasterizer {

public:
	CPURasterizer(IFrameBuffer* frameBuffer) : m_FrameBuffer(frameBuffer) {}
	virtual ~CPURasterizer() = default;
	virtual void AttachFrameBuffer(IFrameBuffer* frameBuffer) override;

	virtual void DrawLineBresenham(int x0, int y0, int x1, int y1, uint32_t color, float progress) override;
	virtual void DrawLineSimple(int x0, int y0, int x1, int y1, uint32_t color, float progress) override;

private:
	IFrameBuffer* m_FrameBuffer;
};