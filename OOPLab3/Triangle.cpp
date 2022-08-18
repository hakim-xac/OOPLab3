#include "Triangle.h"
#include <random>

namespace KHAS {

	Triangle::Triangle(const RECT& rect)
		: Line(rect)
		, third_point_pos_x_()
		, third_point_pos_y_()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution dist_third_pos_x(getX(), getSecondPosX());
		std::uniform_int_distribution dist_third_pos_y(getY(), getSecondPosY());


		third_point_pos_x_ = dist_third_pos_x(gen);
		third_point_pos_y_ = dist_third_pos_y(gen);
	}

	int Triangle::getThirdPosX() const
	{
		return third_point_pos_x_;
	}

	int Triangle::getThirdPosY() const
	{
		return third_point_pos_y_;
	}

	void Triangle::setThirdPosX(int value)
	{
		third_point_pos_x_ = value;
	}

	void Triangle::setThirdPosY(int value)
	{
		third_point_pos_y_ = value;
	}

	void Triangle::move(MoveDirection md)
	{
		switch (md)
		{
		case KHAS::MoveDirection::Up:
			setY(getY() - 1);
			setSecondPosY(getSecondPosY() - 1);
			--third_point_pos_y_;
			break;
		case KHAS::MoveDirection::Right:
			setX(getX() + 1);
			setSecondPosX(getSecondPosX() + 1);
			++third_point_pos_x_;
			break;
		case KHAS::MoveDirection::Down:
			setY(getY() + 1);
			setSecondPosY(getSecondPosY() + 1);
			++third_point_pos_y_;
			break;
		case KHAS::MoveDirection::Left:
			setX(getX() - 1);
			setSecondPosX(getSecondPosX() - 1);
			--third_point_pos_x_;
			break;
		case KHAS::MoveDirection::UpRight:
			move(MoveDirection::Up);
			move(MoveDirection::Right);
			break;
		case KHAS::MoveDirection::UpLeft:
			move(MoveDirection::Up);
			move(MoveDirection::Left);
			break;
		case KHAS::MoveDirection::DownRight:
			move(MoveDirection::Down);
			move(MoveDirection::Right);
			break;
		case KHAS::MoveDirection::DownLeft:
			move(MoveDirection::Down);
			move(MoveDirection::Left);
			break;
		case KHAS::MoveDirection::Empty:
			break;
		default:
			break;
		}
	}

	void Triangle::moveRandom()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution dist_move_direction(0, 7);

		auto move_random{ dist_move_direction(gen) };

		switch (move_random)
		{
		case 0: move(MoveDirection::Up);        break;
		case 1: move(MoveDirection::UpRight);   break;
		case 2: move(MoveDirection::Right);     break;
		case 3: move(MoveDirection::DownRight); break;
		case 4: move(MoveDirection::Down);      break;
		case 5: move(MoveDirection::DownLeft);  break;
		case 6: move(MoveDirection::Left);      break;
		case 7: move(MoveDirection::UpLeft);    break;
		default:                                break;
		}
	}

	void Triangle::draw(const HDC& hdc) const
	{
		POINT array_triangle_points[]{
			POINT{ getX(), getY() }
			, POINT{ getSecondPosX(), getSecondPosY() }
			, POINT{ getThirdPosX(), getThirdPosY() }
		};
		HBRUSH solidBrush{ CreateSolidBrush(getColor()) };
		HRGN hrgn{ CreatePolygonRgn(array_triangle_points, sizeof(array_triangle_points) / sizeof(POINT), ALTERNATE)};
		SelectObject(hdc, solidBrush);

		FillRgn(hdc,hrgn, solidBrush);

		DeleteObject(hrgn);
		DeleteObject(solidBrush);
	}
}