#pragma once

#include <vector>

namespace wml {
namespace GyroFollower {
namespace Path {
namespace Utils {
	/**
	 * x,y point (doubles)
	 */
	struct Point {
		double x,y;
	};

	/**
	 * Line, consists of a start point, end point
	 * and exit angle
	 */
	struct Line {
		Point start, end;
		double exitAngle = 0; // makes robot turn to the angle
		bool complete = false;
	};
}
}
}
}