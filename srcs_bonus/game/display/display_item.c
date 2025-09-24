#include "struct_bonus.h"
#include "utils_bonus.h"
#include "color_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>


#include <stdio.h>
#include <unistd.h>
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
	// posx_display -= floor(posx_display);
	data->ray[i].doors[j]->texture_coo.x = (int)(posx_display * data->map.door->width);
	if (data->ray[i].doors[j]->texture_coo.x < 0)
		data->ray[i].doors[j]->texture_coo.x = 0;
	if (data->ray[i].doors[j]->texture_coo.x >= data->map.door->width)
		data->ray[i].doors[j]->texture_coo.x = data->map.door->width - 1;
}

static void	check_dir_enemy(t_data *data, int i, int j)
{
	double	posx_display;

	posx_display = data->ray[i].enemys[j]->posx;
	data->ray[i].enemys[j]->texture_coo.x = (int)(posx_display * data->map.dementor_front->width);
	if (data->ray[i].enemys[j]->texture_coo.x < 0)
		data->ray[i].enemys[j]->texture_coo.x = 0;
	if (data->ray[i].enemys[j]->texture_coo.x >= data->map.dementor_front->width)
		data->ray[i].enemys[j]->texture_coo.x = data->map.dementor_front->width - 1;
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

static void	put_text_pix_img_dementor(t_data *data, int i, int dist_heigh, int text_x, int j)
{
	char			*text_pix;
	int				text_y;
	char			*pixel_addr;
	unsigned int	color;
	double			enemy_status;

	enemy_status = 0;
	if (data->ray[i].enemys[j]->enemy->deg + 360 >= data->ray[i].deg - 90 + 360
		&& data->ray[i].enemys[j]->enemy->deg + 360 <= data->ray[i].deg + 90 + 360)
	{
		text_y = (data->ray[i].pix_y - data->ray[i].enemys[j]->htop_enemy + enemy_status / 100 * data->ray[i].enemys[j]->size_enemy)
			* data->map.dementor_back->height / dist_heigh;
		if (text_y > data->map.dementor_back->height)
			return ;
		pixel_addr = data->ray[i].img_addr + (data->ray[i].pix_y
				* data->screen->size_line);
		text_pix = data->map.dementor_back->data_addr + (text_y
				* data->map.dementor_back->size_line + text_x);
	}
	else
	{
		text_y = (data->ray[i].pix_y - data->ray[i].enemys[j]->htop_enemy + enemy_status / 100 * data->ray[i].enemys[j]->size_enemy)
			* data->map.dementor_front->height / dist_heigh;
		if (text_y > data->map.dementor_front->height)
			return ;
		pixel_addr = data->ray[i].img_addr + (data->ray[i].pix_y
				* data->screen->size_line);
		text_pix = data->map.dementor_front->data_addr + (text_y
				* data->map.dementor_front->size_line + text_x);
	}
	
	color = *(unsigned int *)text_pix;
	if (color != WHITE && color != YELLOW && color != RED)
		*(unsigned int *)pixel_addr = color;
}

void	display_item(t_data *data, int i)
{
	double	dist_max_enemy;
	double	dist_max_door;
	int	j;
	int	type;
	int	text_x;
	int	dist_heigh;
	
	dist_max_enemy = 1;
	dist_max_door = 1;
	j = 0;
	while (j < data->nb_enemy)
	{
		if (data->ray[i].enemys[j]->dist_enemy < data->ray[i].dist_wall
			&& data->ray[i].enemys[j]->use == true)
		{
			// printf("enemy>>%lf    wall>>%lf\n",data->ray[i].enemys[j]->dist_enemy, data->ray[i].dist_wall);
			data->ray[i].enemys[j]->print = true;
			// printf("SET PRINT   >>%lf      >>%lf\n",data->ray[i].enemys[j]->dist_enemy, data->ray[i].dist_wall);
		}
		else
			ft_bzero(data->ray[i].enemys[j], sizeof(t_hit_enemy));
		j++;
	}
	while (dist_max_enemy != 0 || dist_max_door != 0)
	{
		dist_max_enemy = 0;
		dist_max_door = 0;
		j = 0;
		while (j < data->nb_door)
		{
			if (dist_max_door < data->ray[i].doors[j]->dist_door
				&& data->ray[i].doors[j]->print == true)
			{
				dist_max_door = data->ray[i].doors[j]->dist_door;
			}
			j++;
		}
		j = 0;
		while (j < data->nb_enemy)
		{
			if (dist_max_enemy < data->ray[i].enemys[j]->dist_enemy
				&& data->ray[i].enemys[j]->print == true)
			{
				dist_max_enemy = data->ray[i].enemys[j]->dist_enemy;
			}
			j++;
		}
		if (dist_max_door == 0 && dist_max_enemy == 0)
			break ;
		if (dist_max_door > dist_max_enemy)
			type = 0;
		else
			type = 1;
		if (type == 0)
		{
			j = -1;
			while (++j < data->nb_door)
				if (data->ray[i].doors[j]->dist_door == dist_max_door)
					break ;
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
			ft_bzero(data->ray[i].doors[j], sizeof(t_hit_door));
		}
		else if (type == 1)
		{

			// data->ray[i].deg = fmod(data->ray[i].deg + data->ray[i].rad / (M_PI / 180) + 360, 360);
			// printf("angle player >%lf           \n",data->ray[i].deg);
			j = -1;
			while (++j < data->nb_enemy)
				if (data->ray[i].enemys[j]->dist_enemy == dist_max_enemy)
					break ;
			check_dir_enemy(data, i, j);
			data->ray[i].img_addr = data->screen->data_addr + data->ray[i].pix_x
				* data->ray[i].calc_bits;
			if (data->ray[i].enemys[j]->enemy->deg + 360 >= data->ray[i].deg - 90 + 360
				&& data->ray[i].enemys[j]->enemy->deg + 360 <= data->ray[i].deg + 90 + 360)
			{
				text_x = data->ray[i].enemys[j]->texture_coo.x
					* (data->map.dementor_back->bits_per_pixel >> 3);
			}
			else
			{
				text_x = data->ray[i].enemys[j]->texture_coo.x
					* (data->map.dementor_front->bits_per_pixel >> 3);
			}
			data->ray[i].pix_y = data->ray[i].enemys[j]->htop_enemy;
			if (data->ray[i].pix_y < 0)
				data->ray[i].pix_y = 0;
			dist_heigh = data->ray[i].enemys[j]->hbot_enemy - data->ray[i].enemys[j]->htop_enemy;
			while (data->ray[i].pix_y < data->ray[i].enemys[j]->hbot_enemy
				&& data->ray[i].pix_y < data->mlx.height)
			{
				put_text_pix_img_dementor(data, i, dist_heigh, text_x, j);
				data->ray[i].pix_y++;
			}
			ft_bzero(data->ray[i].enemys[j], sizeof(t_hit_enemy));
		}
	}
	j = 0;
	while (j < data->nb_door)
	{
		ft_bzero(data->ray[i].doors[j], sizeof(t_hit_door));
		j++;
	}
	j = 0;
	while (j < data->nb_enemy)
	{
		ft_bzero(data->ray[i].enemys[j], sizeof(t_hit_door));
		j++;
	}
}