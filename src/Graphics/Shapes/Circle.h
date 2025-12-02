#pragma once

#include "Shape.h"

class Circle : public Shape {

public:
	Circle(int x, int y, int radius, uint32_t color, bool bold = false);
	virtual ~Circle() = default;

	virtual void Draw(IRasterizer* rasterizer) const override;

	virtual void Translate(int dx, int dy) override;

	void SetCenter(int x, int y) { m_X = x; m_Y = y; }
	void SetRadius(int radius) { m_Radius = radius; }

private:
	int m_X;
	int m_Y;
	int m_Radius;
	uint32_t m_Color;
	bool m_Bold;
};