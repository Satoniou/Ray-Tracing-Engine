#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

// Alias of vec3 class, to clarify when object represents a color vs a point
using color = vec3;

void write_color(std::ostream& out, const color& pixel_color)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// Translate the [0,1] components values to the byte range [0, 255]
	static const interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	// Write out color components
	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
