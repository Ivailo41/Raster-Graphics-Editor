#include "Rectangle.h"

void Rectangle::Draw(IRasterizer* rasterizer) const
{
	rasterizer->DrawRectangle(m_X0, m_Y0, m_X1, m_Y1, m_Color, m_Progress);
}

void Rectangle::Translate(int dx, int dy)
{
	m_X0 += dx;
	m_Y0 += dy;
	m_X1 += dx;
	m_Y1 += dy;
}