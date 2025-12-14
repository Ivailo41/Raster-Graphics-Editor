#include "Polygon.h"

Polygon::Polygon(const std::vector<point2d>& points, uint32_t borderColor, uint32_t fillColor)
	: m_Points(points), m_BorderColor(borderColor), m_FillColor(fillColor), m_Filled(false), m_FillStartPoint({ 0,0 })
{
	//nothing to do here
}

void Polygon::Draw(IRasterizer* rasterizer) const {
	for (size_t i = 0; i < m_Points.size(); ++i) {
		const point2d& p1 = m_Points[i];
		const point2d& p2 = m_Points[(i + 1) % m_Points.size()]; // Wrap around to the first point
		rasterizer->DrawLineBresenham(p1.x, p1.y, p2.x, p2.y, m_BorderColor, 1.0f);
	}

	if(m_Filled)
		rasterizer->SimpleBoundaryFill(m_FillStartPoint.x, m_FillStartPoint.y, m_FillColor, m_BorderColor, 1, 0);
}

void Polygon::Translate(int dx, int dy) {
	for (point2d& point : m_Points) {
		point.x += dx;
		point.y += dy;
	}
}

void Polygon::StartFill(int x, int y) {
	m_Filled = true;
	m_FillStartPoint = { x, y };
}
