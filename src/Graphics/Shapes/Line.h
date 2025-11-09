#pragma once
#include "Shape.h"

class Line : public Shape {
public:
	Line(int x1, int y1, int x2, int y2, bool method, uint32_t color) : m_X1(x1), m_Y1(y1), m_X2(x2), m_Y2(y2), m_Method(method), m_Color(color) {}
	virtual ~Line() = default;
	virtual void Draw(IRasterizer* rasterizer) const override;

	virtual void Translate(int dx, int dy) override;

	void SetStart(int x1, int y1) { m_X1 = x1; m_Y1 = y1; }
	void SetEnd(int x2, int y2) { m_X2 = x2; m_Y2 = y2; }

private:
	int m_X1;
	int m_Y1;
	int m_X2;
	int m_Y2;
	bool m_Method;
	uint32_t m_Color;
};