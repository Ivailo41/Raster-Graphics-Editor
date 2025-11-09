#include "Line.h"

void Line::Draw(IRasterizer* rasterizer) const
{
	if (m_Method) {
		rasterizer->DrawLineBresenham(m_X1, m_Y1, m_X2, m_Y2, m_Color, 1.0);
	}
	else {
		rasterizer->DrawLineSimple(m_X1, m_Y1, m_X2, m_Y2, m_Color, 1.0);
	}
}

void Line::Translate(int dx, int dy)
{
	m_X1 += dx;
	m_Y1 += dy;
	m_X2 += dx;
	m_Y2 += dy;
}
