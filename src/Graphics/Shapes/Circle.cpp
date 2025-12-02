#include "Circle.h"

Circle::Circle(int x, int y, int radius, uint32_t color, bool bold) : m_X(x), m_Y(y), m_Radius(radius), m_Color(color), m_Bold(bold)
{

}

void Circle::Draw(IRasterizer* rasterizer) const
{
	rasterizer->DrawCircleMidPoint(m_X, m_Y, m_Radius, m_Color, 1.0, m_Bold);
}

void Circle::Translate(int dx, int dy)
{
	m_X += dx;
	m_Y += dy;
}
