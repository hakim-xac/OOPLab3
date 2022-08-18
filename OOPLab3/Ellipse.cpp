#include "Ellipse.h"
#include <random>

namespace KHAS {

	MyEllipse::MyEllipse(const RECT& rect)
	: Circle(rect)
	, height_radius_() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution dist_height_radius(10, 100);
		height_radius_ = dist_height_radius(gen);
	}

	int MyEllipse::getHeightRadius() const
	{
		return height_radius_;
	}

	void MyEllipse::setBigRadius(int new_height_radius)
	{
		height_radius_ = new_height_radius;
	}

	void MyEllipse::draw(const HDC& hdc) const
	{
		HBRUSH brush_solid{ CreateSolidBrush(getColor()) };
		SelectObject(hdc, brush_solid);

		auto x{ getX() };
		auto y{ getY() };
		auto width_radius{ getRadius() };
		auto height_radius{ getHeightRadius() };

		Ellipse(hdc, x, y, x + width_radius, y + height_radius);

		DeleteObject(brush_solid);
	}

}