#ifndef Line__
#define Line__

#include <Windows.h>
#include "Point.h"
#include "Enums.h"

namespace KHAS {
	class Line : public Point
	{
	private:

		int second_point_pos_x_;
		int second_point_pos_y_;

	public:
		Line() = delete;
		Line(const RECT& rect);
		virtual ~Line() = default;

		int getSecondPosX() const;
		int getSecondPosY() const;

		void setSecondPosX(int value);
		void setSecondPosY(int value);


		virtual void move(MoveDirection md)		override; 
		virtual void moveRandom()				override;
		virtual void draw(const HDC& hdc) const override;
	};
}


#endif