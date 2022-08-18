#ifndef Circle__
#define Circle__

#include <Windows.h>
#include "Enums.h"
#include "Point.h"

namespace KHAS {

	class Circle : public Point
	{
	private:

		int radius_;

	public:
		Circle() = delete;
		Circle(const RECT& rect);
		virtual ~Circle() = default;

		int getRadius() const;
		void setRadius(int new_radius);

		virtual void draw(const HDC& hdc) const override;
	};

}

#endif

