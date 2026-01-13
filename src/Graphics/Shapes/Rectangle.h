#pragma once
#include "Shape.h"

class Rectangle : public Shape {
public:
	Rectangle(int x0, int y0, int x1, int y1, uint32_t color) : m_X0(x0), m_Y0(y0), m_X1(x1), m_Y1(y1), m_Progress(1) {}

	virtual void Draw(IRasterizer* rasterizer) const override;
	virtual void Translate(int dx, int dy) override;

	int getStartX() const { return m_X0; }
	int getStartY() const { return m_Y0; }
	int getEndX() const { return m_X1; }
	int getEndY() const { return m_Y1; }

	int getMinX() const { return m_X0 < m_X1 ? m_X0 : m_X1; }
	int getMinY() const { return m_Y0 < m_Y1 ? m_Y0 : m_Y1; }
	int getMaxX() const { return m_X0 > m_X1 ? m_X0 : m_X1; }
	int getMaxY() const { return m_Y0 > m_Y1 ? m_Y0 : m_Y1; }

	void setStart(int x0, int y0) { m_X0 = x0; m_Y0 = y0; }
	void setEnd(int x1, int y1) { m_X1 = x1; m_Y1 = y1; }

	void setProgress(float progress) { m_Progress = progress; }

private:
	int m_X0, m_Y0, m_X1, m_Y1;
	uint32_t m_Color;
	float m_Progress;
};