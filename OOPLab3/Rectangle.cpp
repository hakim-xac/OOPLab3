#include "Rectangle.h"
#include <random>

namespace KHAS {

	MyRectangle::MyRectangle(const RECT& rect)
		: Line(rect)
		, right_point_()
		, bottom_point_()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		auto x{ getX() };
		auto y{ getY() };
		std::uniform_int_distribution dist_right_point(x + 10, x + 100);
		std::uniform_int_distribution dist_bottom_point(y + 10, y + 100);


		right_point_ = dist_right_point(gen);
		bottom_point_ = dist_bottom_point(gen);
	}

	int MyRectangle::getRightPointX() const
	{
		return right_point_;
	}

	int MyRectangle::getBottomPointY() const
	{
		return bottom_point_;
	}

	void MyRectangle::setRightPointX(int value)
	{
		right_point_ = value;
	}

	void MyRectangle::setBottomPointY(int value)
	{
		bottom_point_ = value;
	}

	void MyRectangle::draw(const HDC& hdc) const
	{
		HBRUSH solid_brush{ CreateSolidBrush(getColor()) };
		SelectObject(hdc, solid_brush);
		Rectangle(hdc, getX(), getY(), getRightPointX(), getBottomPointY());
		DeleteObject(solid_brush);
	}

	void MyRectangle::moveRandom()
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

	void MyRectangle::move(MoveDirection md)
	{
		switch (md)
		{
		case KHAS::MoveDirection::Up:
			setY(getY() - 1);
			--bottom_point_;
			break;
		case KHAS::MoveDirection::Right:
			setX(getX() + 1);
			++right_point_;
			break;
		case KHAS::MoveDirection::Down:
			setY(getY() + 1);
			++bottom_point_;
			break;
		case KHAS::MoveDirection::Left:
			setX(getX() - 1);
			--right_point_;
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

}