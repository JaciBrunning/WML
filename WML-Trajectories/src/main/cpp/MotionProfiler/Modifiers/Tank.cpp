#include "MotionProfiler/Profiler/Modifiers/Tank.h"
#include <math.h>

namespace wml {
namespace MotionProfiler {
namespace Profiler {
namespace Modifiers {
	void Tank::modify_tank(std::vector<Segment> original, std::vector<Segment> &left_traj, std::vector<Segment> &right_traj, double wheelbase_width) {
		double w = wheelbase_width/2;

		for (size_t i = 0; i < original.size(); i++) {
			Segment seg = original[i];
			Segment left = seg;
			Segment right = seg;

			double cos_angle = cos(seg.heading);
			double sin_angle = sin(seg.heading);

			// Left
			left.x = seg.x - (w * sin_angle);
			left.y = seg.y + (w * cos_angle);
			
			if (i > 0) {
				Segment last = left_traj[i - 1];
				double distance = sqrt(
					(left.x - last.x) * (left.x - last.x)
					+ (left.y - last.y) * (left.y - last.y)
				);
				
				left.position = last.position + distance;
				left.velocity = distance / seg.dt;
				left.acceleration = (left.velocity - last.velocity) / seg.dt;
				left.jerk = (left.acceleration - last.acceleration) / seg.dt;
			}

			// Right
			right.x = seg.x + (w * sin_angle);
			right.y = seg.y - (w * cos_angle);

			if (i > 0) {
				Segment last = right_traj[i - 1];
				double distance = sqrt(
					(right.x - last.x) * (right.x - last.x)
					+ (right.y - last.y) * (right.y - last.y)
				);
				
				right.position = last.position + distance;
				right.velocity = distance / seg.dt;
				right.acceleration = (right.velocity - last.velocity) / seg.dt;
				right.jerk = (right.acceleration - last.acceleration) / seg.dt;
			}

			left_traj[i] = left;
			right_traj[i] = right;
		}
	}
} // modifiers
} // profiler
} // mp
} // wml