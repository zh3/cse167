#ifndef _BASICMATH_H_
#define _BASICMATH_H_

#include <math.h>

class BasicMath
{
  public:
	  static const double PI;

	  static double radian(double a) { return a * PI/180.f; };
          static void randomInit(unsigned int seed /* = 0 */);
          // Random number in the given range, inclusive
          static int randomRange(unsigned int min, unsigned int max);
};

#endif
