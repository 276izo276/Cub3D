#include "cub3d_bonus.h"
#include <math.h>
#include "utils_bonus.h"
#include "color_bonus.h"

static void	check_dir(t_data *data, int i, int j)
{
	double	posx_display;

	posx_display = 0;
	if (data->ray[i].doors[j]->dir == NORTH || data->ray[i].doors[j]->dir == SOUTH)
	{
		posx_display = data->ray[i].doors[j]->coo_x / 64;
		if (data->ray[i].doors[j]->dir == NORTH)
			posx_display = 1 - posx_display;
	}
	else if (data->ray[i].doors[j]->dir == WEST || data->ray[i].doors[j]->dir == EAST)
	{
		posx_display = data->ray[i].doors[j]->coo_y / 64;
		if (data->ray[i].doors[j]->dir == EAST)
			posx_display = 1 - posx_display;
	}
	posx_display -= floor(posx_display);
	data->ray[i].doors[j]->texture_coo.x = (int)(posx_display * data->map.door->width);
	if (data->ray[i].doors[j]->texture_coo.x < 0)
		data->ray[i].doors[j]->texture_coo.x = 0;
	if (data->ray[i].doors[j]->texture_coo.x >= data->map.door->width)
		data->ray[i].doors[j]->texture_coo.x = data->map.door->width - 1;
}

static void	put_text_pix_img(t_data *data, int i, int dist_heigh, int text_x, int j)
{
	char			*text_pix;
	int				text_y;
	char			*pixel_addr;
	unsigned int	color;
	double			door_status;

	if (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->pos >= 50)
		door_status = 50;
	else
		door_status = data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->pos;
	// door_status = 0;
	text_y = (data->ray[i].pix_y - data->ray[i].doors[j]->htop_door + door_status / 100 * data->ray[i].doors[j]->size_door)
		* data->map.door->height / dist_heigh;
	if (text_y > data->map.door->height - 5)
		return ;
	pixel_addr = data->ray[i].img_addr + (data->ray[i].pix_y
			* data->screen->size_line);
	text_pix = data->map.door->data_addr + (text_y
			* data->map.door->size_line + text_x);
	color = *(unsigned int *)text_pix;
	if (color != WHITE && color != YELLOW)
		*(unsigned int *)pixel_addr = color;

}

static void	check_dir_fixed(t_data *data, int i, int j)
{
	double	posx_display;

	posx_display = 0;
	if (data->ray[i].doors[j]->dir == NORTH || data->ray[i].doors[j]->dir == SOUTH)
	{
		posx_display = data->ray[i].doors[j]->coo_x / 64;
		if (data->ray[i].doors[j]->dir == NORTH)
			posx_display = 1 - posx_display;
	}
	else if (data->ray[i].doors[j]->dir == WEST || data->ray[i].doors[j]->dir == EAST)
	{
		posx_display = data->ray[i].doors[j]->coo_y / 64;
		if (data->ray[i].doors[j]->dir == EAST)
			posx_display = 1 - posx_display;
	}
	posx_display -= floor(posx_display);
	data->ray[i].doors[j]->texture_coo.x = (int)(posx_display * data->map.fixed_door->width);
	if (data->ray[i].doors[j]->texture_coo.x < 0)
		data->ray[i].doors[j]->texture_coo.x = 0;
	if (data->ray[i].doors[j]->texture_coo.x >= data->map.fixed_door->width)
		data->ray[i].doors[j]->texture_coo.x = data->map.fixed_door->width - 1;
}

static void	put_text_pix_img_fixed(t_data *data, int i, int dist_heigh, int text_x, int j)
{
	char			*text_pix;
	int				text_y;
	char			*pixel_addr;
	unsigned int	color;
	double			door_status;

	// if (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->pos > 100)
		door_status = 0;
	// else
	// 	door_status = data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->pos;
	text_y = (data->ray[i].pix_y - data->ray[i].doors[j]->htop_door + door_status / 100 * data->ray[i].doors[j]->size_door)
		* data->map.fixed_door->height / dist_heigh;
	if (text_y > data->map.fixed_door->height)
		return ;
	pixel_addr = data->ray[i].img_addr + (data->ray[i].pix_y
			* data->screen->size_line);
	text_pix = data->map.fixed_door->data_addr + (text_y
			* data->map.fixed_door->size_line + text_x);
	color = *(unsigned int *)text_pix;
	if (color != WHITE && color != YELLOW)
		*(unsigned int *)pixel_addr = color;
}

void	display_door(t_data *data, int i)
{
	int	text_x;
	int	dist_heigh;
	int	j;

	// printf("HERE CHECK IN >>i>>%d      value use>>%d\n",i,data->ray[i].doors[j]->use);
			j = 0;
	while (j < data->nb_door && data->ray[i].doors[j]->use != false)
		j++;
	--j;
	while (j >= 0)
	{
		if (data->ray[i].doors[j]->print == false)
		{
			ft_bzero(data->ray[i].doors[j], sizeof(t_hit_door));
			j--;
			// j++;
			continue;
		}
		check_dir(data, i, j);
		data->ray[i].img_addr = data->screen->data_addr + data->ray[i].pix_x
			* data->ray[i].calc_bits;
		text_x = data->ray[i].doors[j]->texture_coo.x
			* (data->map.door->bits_per_pixel >> 3);
		data->ray[i].pix_y = data->ray[i].doors[j]->htop_door;
		if (data->ray[i].pix_y < 0)
			data->ray[i].pix_y = 0;
		dist_heigh = data->ray[i].doors[j]->hbot_door - data->ray[i].doors[j]->htop_door;
		while (data->ray[i].pix_y < data->ray[i].doors[j]->hbot_door
			&& data->ray[i].pix_y < data->mlx.height)
		{
			if (data->ray[i].pix_y > data->ray[i].doors[j]->htop_door + dist_heigh * .15)
				put_text_pix_img(data, i, dist_heigh, text_x, j);
			data->ray[i].pix_y++;
		}
		check_dir_fixed(data, i, j);
		text_x = data->ray[i].doors[j]->texture_coo.x
			* (data->map.fixed_door->bits_per_pixel >> 3);
		data->ray[i].pix_y = data->ray[i].doors[j]->htop_door;
		if (data->ray[i].pix_y < 0)
			data->ray[i].pix_y = 0;
		dist_heigh = data->ray[i].doors[j]->hbot_door - data->ray[i].doors[j]->htop_door;
		while (data->ray[i].pix_y < data->ray[i].doors[j]->hbot_door
			&& data->ray[i].pix_y < data->mlx.height)
		{
			put_text_pix_img_fixed(data, i, dist_heigh, text_x, j);
			data->ray[i].pix_y++;
		}
		// data->ray[i].doors[j]->use = false;
		// printf("RESET USE I>>>%d j>>%d\n",i,j);
		ft_bzero(data->ray[i].doors[j], sizeof(t_hit_door));
		j--;
		// j++;
	}
}
