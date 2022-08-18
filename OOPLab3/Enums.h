#ifndef Enums__
#define Enums__

namespace KHAS {

	enum class MenuItems {
		Point
		, Circle
		, Ellipse
		, Line
		, Triangle
		, Rectangle
		, Empty
	};

	enum class MoveTypes {
		Random
		, Movement
		, Back
		, Empty
	};

	enum class DrawMenuItems {
		Back
		, Exit
		, Empty
	};

	enum class MoveDirection {
		Up
		, UpRight
		, Right
		, DownRight
		, Down
		, DownLeft
		, Left
		, UpLeft
		, Empty
	};

}

#endif
