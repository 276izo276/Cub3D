#include "struct_bonus.h"

void	get_world_size(t_data *data, t_display *display, int y)
{
	display->dist_center = y - data->screen->height * 0.5;
	if (display->dist_center == 0)
		display->dist_center = 0.0001;
	display->screen_y = (double)display->dist_center / data->screen->height;
	display->dist_texture = 16.0 / display->screen_y;
}
