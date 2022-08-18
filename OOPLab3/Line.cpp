#include "Line.h"
#include <random>

namespace KHAS {
	Line::Line(const RECT& rect)
		: Point(rect)
		, second_point_pos_x_()
		, second_point_pos_y_()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		auto x{ getX() };
		auto y{ getY() };
		std::uniform_int_distribution dist_second_pos_x(x, x + 200);
		std::uniform_int_distribution dist_second_pos_y(y, y + 200);


		second_point_pos_x_ = dist_second_pos_x(gen);
		second_point_pos_y_ = dist_second_pos_y(gen);
	}

	int Line::getSecondPosX() const
	{
		return second_point_pos_x_;
	}

	int Line::getSecondPosY() const
	{
		return second_point_pos_y_;
	}

	void Line::setSecondPosX(int value)
	{
		second_point_pos_x_ = value;
	}

	void Line::setSecondPosY(int value)
	{
		second_point_pos_y_ = value;
	}

	void Line::move(MoveDirection md)
	{
		switch (md)
		{
		case KHAS::MoveDirection::Up:
			setY(getY() - 1);
			--second_point_pos_y_;
			break;
		case KHAS::MoveDirection::Right:
			setX(getX() + 1);
			++second_point_pos_x_;
			break;
		case KHAS::MoveDirection::Down:
			setY(getY() + 1);
			++second_point_pos_y_;
			break;
		case KHAS::MoveDirection::Left:
			setX(getX() - 1);
			--second_point_pos_x_;
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

	void Line::moveRandom()
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

	void Line::draw(const HDC& hdc) const
	{
		HPEN line_pen{ CreatePen(PS_SOLID, 1, getColor()) };
		SelectObject(hdc, line_pen);
		MoveToEx(hdc, getX(), getY(), NULL);

		LineTo(hdc, getSecondPosX(), getSecondPosY());

		DeleteObject(line_pen);
	}



}