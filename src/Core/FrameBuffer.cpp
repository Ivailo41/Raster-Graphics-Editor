#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height) : m_Width(width), m_Height(height)
{
	m_Pixels = new uint32_t[width * height];

	Clear(0x00000000); // Clear to transparent black
}

FrameBuffer::~FrameBuffer()
{
	delete[] m_Pixels;
}

void FrameBuffer::SetPixel(int x, int y, uint32_t color)
{
	if (x < 0 || x >= m_Width || y < 0 || y >= m_Height) {
		return;
	}

	m_Pixels[y * m_Width + x] = color;
}

uint32_t FrameBuffer::GetPixel(int x, int y) const
{
	return m_Pixels[y * m_Width + x];
}

void FrameBuffer::SetSize(unsigned width, unsigned height)
{
	delete[] m_Pixels;
	m_Width = width;
	m_Height = height;
	m_Pixels = new uint32_t[m_Width * m_Height];
}

void FrameBuffer::Clear(uint32_t color)
{
	for (int y = 0; y < m_Height; ++y) {
		for (int x = 0; x < m_Width; ++x) {
			m_Pixels[y * m_Width + x] = color;
		}
	}
}