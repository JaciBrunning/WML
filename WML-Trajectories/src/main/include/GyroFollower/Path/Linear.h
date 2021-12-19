#pragma once

#include <vector>

#include "Utils/Utils.h"

namespace wml {
namespace GyroFollower {
namespace Path {
	class Linear {
	 public:
		Linear(std::vector<Utils::Line> path) {
			appendPath(path);
		}

		Linear();

		void appendPath(Utils::Line line) {
			_path.push_back(line);
		}

		void appendPath(std::vector<Utils::Line> path) {
			if (!path.empty()) {
				for (auto line : path) {
					appendPath(line);
				}
			}
		}

		void reset() {
			_path.clear();
		}

		bool complete() {
			return _complete;
		}

		Utils::Line getCurrentLine() {
			for (auto line : _path) {
				if (!line.complete) {
					return line;
				}
			}

			_complete = true; // will it get here?? lets find out
			return Utils::Line{0,0};
		}

		void setCurrentLineComplete() {
			for (auto line : _path) {
				if (!line.complete) {
					line.complete = true;
					return;
				}
			}
		}

	 private:
		std::vector<Utils::Line> _path;

		double _totalLength;
		bool _complete = false;
	};
} // Path
} // GF
} // wml