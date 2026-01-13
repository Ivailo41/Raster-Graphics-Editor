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

void CPURasterizer::DrawCircleMidPoint(int x0, int y0, int radius, uint32_t color, float progress, bool bold)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    int steps = (int)(y * progress);

    EightSymmetric(x0, y0, 0, radius, color, bold);

    while (x < steps)
    {
        if (d >= 0)
        {
            d += 10 + 4 * x - 4 * y;
            y--;
            steps--;
        }
        else
        {
            d += 6 + 4 * x;
        }
        x++;

        EightSymmetric(x0, y0, x, y, color, bold);
    }
}

void CPURasterizer::SimpleBoundaryFill(int x, int y, uint32_t fillColor, uint32_t borderColor, float progress, int step)
{

    uint32_t currentColor = m_FrameBuffer->GetPixel(x, y);
    if (currentColor != borderColor && currentColor != fillColor && step++ < (int)(5000 * progress))
    {
        m_FrameBuffer->SetPixel(x, y, fillColor);
        SimpleBoundaryFill(x + 1, y, fillColor, borderColor, progress, step);
        SimpleBoundaryFill(x - 1, y, fillColor, borderColor, progress, step);
        SimpleBoundaryFill(x, y + 1, fillColor, borderColor, progress, step);
        SimpleBoundaryFill(x, y - 1, fillColor, borderColor, progress, step);
	}
}

void CPURasterizer::DrawRectangle(int x0, int y0, int x1, int y1, uint32_t color, float progress)
{
	if (y0 > y1) {
		std::swap(y0, y1);
	}
	if (x0 > x1) {
		std::swap(x0, x1);
	}

	int width = abs(x1 - x0);
	int height = abs(y1 - y0);

	int visibleWidth = (int)(width * progress);
	int visibleHeight = (int)(height * progress);

	// Top edge
	for (int x = x0; x < x0 + visibleWidth + 1; x++) {
		m_FrameBuffer->SetPixel(x, y0, color);
	}

	// Bottom edge
	for (int x = x0; x < x0 + visibleWidth + 1; x++) {
		m_FrameBuffer->SetPixel(x, y0 + height, color);
	}

	// Left edge
	for (int y = y0; y < y0 + visibleHeight; y++) {
		m_FrameBuffer->SetPixel(x0, y, color);
	}

	// Right edge
	for (int y = y0; y < y0 + visibleHeight; y++) {
		m_FrameBuffer->SetPixel(x0 + width, y, color);
	}   
}

inline void CPURasterizer::ThickenPixel(int x, int y, uint32_t color, bool inverted)
{
    if (inverted) {
		m_FrameBuffer->SetPixel(x + 1, y, color);
		m_FrameBuffer->SetPixel(x - 1, y, color);
        return;
    }

	m_FrameBuffer->SetPixel(x, y + 1, color);
	m_FrameBuffer->SetPixel(x, y - 1, color);
}

inline void CPURasterizer::EightSymmetric(int x0, int y0, int x, int y, uint32_t color, bool bold)
{
	FourSymmetric(x0, y0, x, y, color, bold, false);
	FourSymmetric(x0, y0, y, x, color, bold, true);
}

inline void CPURasterizer::FourSymmetric(int x0, int y0, int x, int y, uint32_t color, bool bold, bool inverted)
{
    if (bold) {
		ThickenPixel(x0 + x, y0 + y, 0xFFFFFFFF, inverted);
		ThickenPixel(x0 - x, y0 - y, 0xFFFFFFFF, inverted);
		ThickenPixel(x0 - x, y0 + y, 0xFFFFFFFF, inverted);
		ThickenPixel(x0 + x, y0 - y, 0xFFFFFFFF, inverted);
    }
    m_FrameBuffer->SetPixel(x0 + x, y0 + y, color);
    m_FrameBuffer->SetPixel(x0 - x, y0 - y, color);
    m_FrameBuffer->SetPixel(x0 - x, y0 + y, color);
    m_FrameBuffer->SetPixel(x0 + x, y0 - y, color);
}
