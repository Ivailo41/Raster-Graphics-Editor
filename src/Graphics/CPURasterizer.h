#pragma once

#include "IRasterizer.h"
class CPURasterizer : public IRasterizer {

public:
	CPURasterizer(IFrameBuffer* frameBuffer) : m_FrameBuffer(frameBuffer) {}
	virtual ~CPURasterizer() = default;
	virtual void AttachFrameBuffer(IFrameBuffer* frameBuffer) override;

	virtual void DrawLineBresenham(int x0, int y0, int x1, int y1, uint32_t color, float progress) override;
	virtual void DrawLineSimple(int x0, int y0, int x1, int y1, uint32_t color, float progress) override;

	virtual void DrawCircleMidPoint(int x0, int y0, int radius, uint32_t color, float progress, bool bold) override;
	virtual void SimpleBoundaryFill(int x, int y, uint32_t fillColor, uint32_t borderColor, float progress, int step) override;
	virtual void DrawRectangle(int x0, int y0, int x1, int y1, uint32_t color, float progress) override;

private:
	inline void ThickenPixel(int x, int y, uint32_t color, bool inverted);
	inline void EightSymmetric(int xc, int yc, int x, int y, uint32_t color, bool bold);
	inline void FourSymmetric(int xc, int yc, int x, int y, uint32_t color, bool bold, bool inverted);

private:
	IFrameBuffer* m_FrameBuffer;
};