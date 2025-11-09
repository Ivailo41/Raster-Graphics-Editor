#include "CPURasterizer.h"
#include <math.h>
#include <iostream>

void CPURasterizer::AttachFrameBuffer(IFrameBuffer* frameBuffer)
{
	m_FrameBuffer = frameBuffer;
}

void CPURasterizer::DrawLineBresenham(int x0, int y0, int x1, int y1, uint32_t color, float progress)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

    int totalSteps = (dx > dy ? dx : dy) + 1;
    int visibleSteps = (int)(totalSteps * progress);
    if (visibleSteps < 1) return;

    for (int i = 0; i < visibleSteps; i++) {
		m_FrameBuffer->SetPixel(x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		int err2 = err * 2;
		if (err2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (err2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

void CPURasterizer::DrawLineSimple(int x0, int x1, int y0, int y1, uint32_t color, float progress)
{
    int dx = abs(y0 - x0);
    int dy = abs(y1 - x1);
    bool reverse = dx < dy;

    if (reverse) {
        std::swap(x0, x1);
        std::swap(y0, y1);
        std::swap(dx, dy);
    }

    int incX = (x0 <= y0) ? 1 : -1;
    float incY = static_cast<float>(y1 - x1) / dx;
    float y = static_cast<float>(x1);

    int x = x0;
    int n = dx + 1;

    int visibleSteps = (int)(n * progress);

    while (visibleSteps--) {
        int inty = static_cast<int>(y + 0.5f);
        if (reverse) {
            m_FrameBuffer->SetPixel(inty, x, color);
        }
        else {
            m_FrameBuffer->SetPixel(x, inty, color);
        }

        x += incX;
        y += incY;
    }
}
