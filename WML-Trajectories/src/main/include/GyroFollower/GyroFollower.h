#pragma once

#include "Path/Linear.h"

namespace wml {

/**
 * CJ's gyro follower.
 * used for simple implementation of spline
 * and linear following
 */
namespace GyroFollower {

	/**
	 * Gyro Follower config,
	 */
	struct Config {
		/**
		 * Wheel diameter in meters
		 */
		double wheelDiameter = 0.1524;

		/**
		 * Max velocity in meters per second
		 */
		double maxVelocity = 3;

		/**
		 * Max acceleration in meters per second
		 */
		double maxAcceleration = 1;

		/**
		 * PID controller
		 */
		double *kP = 0, *kI = 0, *kD = 0;

		~Config() {
			free(kP);
			free(kI);
			free(kD);
		}
	};

	/**
	 * Follower class (requires config with references to live values [left enc, right enc, gyro etc...])
	 */
	template<typename PATH>
	class Follower {
	 public:
		enum class PathType {
			LINEAR = 0
		};

		Follower(Config &config) : _config(config) {}

		Config &getConfig() {
			return _config;
		}

		void setPath(PATH path, PathType type) {
			_path = path;
			_pathType = type;
		}

		/**
		 * Follow path with the config and updated values
		 */
		std::pair<double, double> follow(double leftEnc, double rightEnc, double gyro);

	 private:
		struct Heading {
			double leftEnc, rightEnc, gyro;
		};

		void update(Heading heading);
		Config &_config;

		Heading _currentHeading;
		
		PATH _path;
		PathType _pathType;
	};

} // gf
} // wml