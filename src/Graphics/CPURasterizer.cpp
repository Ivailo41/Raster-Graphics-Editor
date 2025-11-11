#include "CPURasterizer.h"
#include <math.h>
#include <iostream>

void CPURasterizer::AttachFrameBuffer(IFrameBuffer* frameBuffer)
{
	m_FrameBuffer = frameBuffer;
}

void CPURasterizer::DrawLineBresenham(int x1, int y1, int x2, int y2, uint32_t color, float progress)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    bool reverse = dx < dy; // is the line in second octant?

    if (reverse) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        std::swap(dx, dy);
    }

	int incX = (x1 <= x2) ? 1 : -1; // handle Oy simmetry
	int incY = (y1 <= y2) ? 1 : -1; // handle Ox simmetry

    int d = -dx + 2 * dy;
	int incUP = -2 * dx + 2 * dy; // Chosing upper pixel
	int incDN = 2 * dy; // Chosing down pixel

    int x = x1;
    int y = y1;

    int totalSteps = (dx > dy ? dx : dy) + 1;

    int visibleSteps = (int)(totalSteps * progress);
    if (visibleSteps < 1) {
        return;
    }

    for (int i = 0; i < visibleSteps; i++) {
        if (reverse) {
            m_FrameBuffer->SetPixel(y, x, color);
        }
        else {
            m_FrameBuffer->SetPixel(x, y, color);
        }

        x += incX;
        if (d > 0) {
            d += incUP;
            y += incY;
        }
        else {
            d += incDN;
        }
    }
}

void CPURasterizer::DrawLineSimple(int x1, int y1, int x2, int y2, uint32_t color, float progress)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
	bool reverse = dx < dy; // is the line in second octant?

    if (reverse) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        std::swap(dx, dy);
    }

	int incX = (x1 <= x2) ? 1 : -1; // handle Oy simmetry
	float incY = (float)(y2 - y1) / dx; // handle Ox simmetry
    float y = (float)y1;

    int x = x1;
    int n = dx + 1;

    int visibleSteps = (int)(n * progress);

    while (visibleSteps--) {
		int inty = static_cast<int>(y + 0.5f); // round to nearest integer
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
