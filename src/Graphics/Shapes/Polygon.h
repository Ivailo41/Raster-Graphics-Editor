#pragma once
#include "Shape.h"
#include <vector>

class Polygon : public Shape {

public:
	Polygon(const std::vector<point2d>& points, uint32_t borderColor, uint32_t fillColor);

	virtual void Draw(IRasterizer* rasterizer) const override;
	virtual void Translate(int dx, int dy) override;

	void StartFill(int x, int y);
	void ClearFill() { m_Filled = false; }

private:
	std::vector<point2d> m_Points;
	uint32_t m_BorderColor;
	uint32_t m_FillColor;

	bool m_Filled = false;
	point2d m_FillStartPoint;
};