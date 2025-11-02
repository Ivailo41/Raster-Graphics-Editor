#include "Line.h"

void Line::Draw(IRasterizer* rasterizer) const
{
	if (m_Method) {
		rasterizer->DrawLineBresenham(m_X1, m_Y1, m_X2, m_Y2, m_Color);
	}
	else {
		rasterizer->DrawLineSimple(m_X1, m_Y1, m_X2, m_Y2, m_Color);
	}
}
