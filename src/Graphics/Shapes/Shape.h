#pragma once
#include "../IRasterizer.h"

struct point2d {
	int x;
	int y;
};

class Shape {
public:
	virtual ~Shape() = default;
	virtual void Draw(IRasterizer* rasterizer) const = 0;

	virtual void Translate(int dx, int dy) {}
};