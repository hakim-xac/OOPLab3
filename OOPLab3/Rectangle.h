#ifndef Rectangle__
#define Rectange__

#include <Windows.h>
#include "Line.h"
#include "Enums.h"

namespace KHAS {

	class MyRectangle : public Line
	{
	private:

		int right_point_;
		int bottom_point_;

	public:
		MyRectangle() = delete;
		MyRectangle(const RECT& rect);
		virtual ~MyRectangle() = default;

		int getRightPointX() const;
		int getBottomPointY() const;

		void setRightPointX(int value);
		void setBottomPointY(int value);

		virtual void draw(const HDC& hdc) const override;
		virtual void moveRandom()				override;
		virtual void move(MoveDirection md)		override;
	};

}
#endif