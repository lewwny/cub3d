#include "../includes/cub3d.h"

unsigned int	apply_shading(unsigned int color, double dist)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	double			factor;

	if (dist > MAX_DIST)
		return (0x000000);
	factor = 1.0 - (dist / MAX_DIST);
	if (factor < 0)
		factor = 0;
	if (factor > 1)
		factor = 1;
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((r << 16) | (g << 8) | b);
}
