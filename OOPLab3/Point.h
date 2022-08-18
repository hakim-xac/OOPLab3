#ifndef Point__
#define Point__

#include <Windows.h>
#include "Enums.h"

namespace KHAS {
	class Point
	{
	private:

		int pos_x_;
		int pos_y_;
		RECT max_rect_;
		COLORREF color_;

	public:
		Point() = delete;
		Point(const RECT& recr);
		virtual ~Point() = default;

		int getX() const;
		int getY() const;
		const COLORREF& getColor() const;

		void setX(int value);
		void setY(int value);
		void setColor(const COLORREF& color);

		virtual void draw(const HDC& hdc) const;
		virtual void move(MoveDirection md);
		virtual void moveRandom();

	};

}


#endif