#ifndef Triangle__
#define Triangle__

#include <Windows.h>
#include "Line.h"
#include "Enums.h"

namespace KHAS {

	class Triangle : public Line
	{
	private:

		int third_point_pos_x_;
		int third_point_pos_y_;

	public:
		Triangle() = delete;
		Triangle(const RECT& rect);
		virtual ~Triangle() = default;

		int getThirdPosX() const;
		int getThirdPosY() const;

		void setThirdPosX(int value);
		void setThirdPosY(int value);

		virtual void draw(const HDC& hdc) const override;
		virtual void move(MoveDirection md)		override;
		virtual void moveRandom()				override;
	};

}
#endif
