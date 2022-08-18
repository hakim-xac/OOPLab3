#ifndef Ellipse__
#define Ellipse__

#include <Windows.h>
#include "Circle.h"

namespace KHAS {
	class MyEllipse : public Circle
	{
	private:

		int height_radius_;

	public:
		MyEllipse() = delete;
		MyEllipse(const RECT& rect);
		virtual ~MyEllipse() = default;

		int getHeightRadius() const;
		void setBigRadius(int new_height_radius);

		virtual void draw(const HDC& hdc) const override;
	};
}

#endif