#ifndef UTIL_H
#define UTIL_H

#include <random>
#include "vec3.h"

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis1(-0.5, 0.5);
uniform_real_distribution<> dis2(0.0, 1.0);

/*vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0 * vec3(dis2(gen), dis2(gen), dis2(gen)) - vec3(1, 1, 1);
	} while (p.length() >= 1.0);
	return p;
}*/

#endif


