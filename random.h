// Random number generation routines
// Copyright © 2009 The University of Chicago
#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>

namespace linguistica {

/// random float chosen uniformly from the interval [-1/2, 1/2]
/// requires: std::srand has already been called to seed the RNG
inline float random_small_float()
{
	// let the RNG calm down a bit
	for (int i = 0; i < 25; ++i)
		static_cast<void>(std::rand());
	return (static_cast<float>(std::rand()) /
		static_cast<float>(RAND_MAX)) - float(0.5);
}

} // namespace linguistica

#endif // RANDOM_H
