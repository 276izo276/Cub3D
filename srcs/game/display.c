#include "cub3d.h"
#include "ft_printf.h"
#include "mlx.h"
#include "parsing.h"
#include "player.h"
#include "struct.h"
#include "texture.h"
#include "time.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

static void	check_dir(t_data *data, int i)
{
	double	posx_display;

	posx_display = 0;
	if (data->ray[i].dir == NORTH)
		data->ray[i].img = data->map.north;
	else if (data->ray[i].dir == SOUTH)
		data->ray[i].img = data->map.south;
	else if (data->ray[i].dir == EAST)
		data->ray[i].img = data->map.east;
	else if (data->ray[i].dir == WEST)
		data->ray[i].img = data->map.west;
	if (data->ray[i].dir == NORTH || data->ray[i].dir == SOUTH)
	{
		posx_display = data->ray[i].coo_x / 64;
		if (data->ray[i].dir == NORTH)
			posx_display = 1 - posx_display;
	}
	else if (data->ray[i].dir == WEST || data->ray[i].dir == EAST)
	{
		posx_display = data->ray[i].coo_y / 64;
		if (data->ray[i].dir == EAST)
			posx_display = 1 - posx_display;
	}
	posx_display -= floor(posx_display);
	data->ray[i].texture_coo.x = (int)(posx_display * data->ray[i].img->width);
	// printf("posx_display >>> %lf rayx >>> %lf rayy >>> %lf play >>> %lf playx >>> %lf textur_coo_x >>> %d\n", hit, data->ray[i].coo_x, data->ray[i].coo_y, data->map.mini.player_coo.x, data->map.mini.player_coo.y, data->ray[i].texture_coo.x);
	if (data->ray[i].texture_coo.x < 0)
		data->ray[i].texture_coo.x -= 0;
	if (data->ray[i].texture_coo.x >= data->ray[i].img->width)
		data->ray[i].texture_coo.x = data->ray[i].img->width - 1;
}

// static void	display_game_loop(t_data *data, t_ray ray, double i)
// {
// 	(void)i;
// 	int	texture_x = ray.texture_coo.x * (ray.img->bits_per_pixel >> 3);
// 	char *test1 = ray.data_addr + ray.pix_x * ray.calc_bits;
// 	char	*pixel_addr;
// 	// while (ray.pix_y > ray.htop_wall && ray.pix_y > 0) //mur haut
// 	// {
// 	// 	int	texture_y = (ray.pix_y - ray.htop_wall) * ray.img->height / (ray.hbot_wall - ray.htop_wall);
// 	// 	ray.pixel_addr = ray.data_addr + (ray.pix_y
// 	// 				* data->screen->size_line + ray.pix_x
// 	// 				* (ray.calc_bits));
// 	// 	char *texture_pixel = ray.img->data_addr + (texture_y * ray.img->size_line + texture_x * (ray.img->bits_per_pixel / 8));
// 	// 	unsigned int color = *(unsigned int *)texture_pixel;
// 	// 	*(unsigned int *)ray.pixel_addr = color;
// 	// 	// (void)color;
// 	// 	// *(unsigned int *)ray.pixel_addr = 0xFF0000;
// 	// 	ray.pix_y--;
// 	// }
// 	ray.pix_y = ray.htop_wall;
// 	if (ray.pix_y < 0)
// 		ray.pix_y = 0;
// 	int	test = (ray.hbot_wall - ray.htop_wall);
// 	while (ray.pix_y < ray.hbot_wall && ray.pix_y < data->mlx.height) //mur bas
// 	{
// 		int	texture_y = (ray.pix_y - ray.htop_wall) * ray.img->height / test;
// 		// *(unsigned int *)pixel_addr = 0x00F00FF;
// 			pixel_addr = test1 + (ray.pix_y * data->screen->size_line);
// 		char *texture_pixel = ray.img->data_addr + (texture_y * ray.img->size_line + texture_x);
// 		unsigned int color = *(unsigned int *)texture_pixel;
// 		*(unsigned int *)pixel_addr = color;
// 		ray.pix_y++;
// 		// if (ray.dist_wall < 40)
// 		// 	ray.pix_y += 1;
// 	}
// 	ray.pix_y = ray.htop_wall;
// 	if (ray.pix_y < 0)
// 		ray.pix_y = 0;
// 	while (ray.pix_y > 0) // ciel
// 	{
// 		pixel_addr = test1 + ((ray.pix_y)
// 					* data->screen->size_line);
// 		*(unsigned int *)pixel_addr = 0xFF002000;
// 		ray.pix_y--;
// 	}
// 	ray.pix_y = ray.hbot_wall;
// 	if (ray.pix_y < 0)
// 		ray.pix_y = 0;
// 	while (ray.pix_y < data->mlx.height) // sol
// 	{
// 		pixel_addr = test1 + ((ray.pix_y)
// 					* data->screen->size_line);
// 		*(unsigned int *)pixel_addr = 0xFF4F4F4F;
// 		ray.pix_y++;
// 	}
// }

// static void floor_render(t_data *data, t_ray ray, int ray_pix_y)
// {
// 	double	dist_floor;
// 	double	world_x;
// 	double	world_y;
// 	int	text_y;
// 	int	text_x;

// 	if (ray_pix_y <= 0 || ray.hbot_wall <= 0)
// 		return ;
// 	dist_floor = (data->screen->height / 2) / (ray_pix_y - (data->screen->height / 2));
// 	if (dist_floor > 50.0 || dist_floor < 0)
// 		return ;
//     double pixel_offset = ray.pix_x - data->screen->width/2.0;
//     double pixel_angle = atan(pixel_offset / ray.d_proj);
//     double angle = data->map.mini.rad + pixel_angle;
// 	// double angle =  data->map.mini.rad + (ray.pix_x - data->screen->width/2.0) * (ray.d_proj / data->screen->width);
// 	world_x = data->map.player_coo->x + cos(angle) * dist_floor;
// 	world_y = data->map.player_coo->y + sin(angle) * dist_floor;
// 	text_x = ((int)(world_x) % data->map.text_floor->width);
// 	text_y = ((int)(world_y) % data->map.text_floor->height);
// 	if (text_x < 0 || text_x >= data->map.text_floor->width || text_y < 0 || text_y >= data->map.text_floor->height)
// 		return ;
// 	// char *text_pixel = data->map.text_floor->data_addr + (text_y * data->map.text_floor->size_line + text_x * (data->map.text_floor->bits_per_pixel / 8));
// 	// unsigned int color = *(unsigned int *)text_pixel;
// 	char *pixel_addr = ray.data_addr + ray.pix_x * ray.calc_bits + (ray_pix_y * data->screen->size_line);
// 	unsigned int color = ((text_x * 4) << 16) | ((text_y * 4) << 8) | 0;
// 	*(unsigned int *)pixel_addr = color;
// }

static void	display_game_loop(t_data *data, int i)
{
	int	texture_x = data->ray[i].texture_coo.x * (data->ray[i].img->bits_per_pixel >> 3);
	char *test1 = data->ray[i].data_addr + data->ray[i].pix_x * data->ray[i].calc_bits;
	char	*pixel_addr;
	// while (data->ray[i].pix_y > data->ray[i].htop_wall && data->ray[i].pix_y > 0) //mur haut
	// {
	// 	int	texture_y = (data->ray[i].pix_y - data->ray[i].htop_wall) * data->ray[i].img->height / (data->ray[i].hbot_wall - data->ray[i].htop_wall);
	// 	data->ray[i].pixel_addr = data->ray[i].data_addr + (data->ray[i].pix_y
	// 				* data->screen->size_line + data->ray[i].pix_x
	// 				* (data->ray[i].calc_bits));
	// 	char *texture_pixel = data->ray[i].img->data_addr + (texture_y * data->ray[i].img->size_line + texture_x * (data->ray[i].img->bits_per_pixel / 8));
	// 	unsigned int color = *(unsigned int *)texture_pixel;
	// 	*(unsigned int *)data->ray[i].pixel_addr = color;
	// 	// (void)color;
	// 	// *(unsigned int *)data->ray[i].pixel_addr = 0xFF0000;
	// 	data->ray[i].pix_y--;
	// }
	data->ray[i].pix_y = data->ray[i].htop_wall;
	if (data->ray[i].pix_y < 0)
		data->ray[i].pix_y = 0;
	int	test = (data->ray[i].hbot_wall - data->ray[i].htop_wall);
	while (data->ray[i].pix_y < data->ray[i].hbot_wall && data->ray[i].pix_y < data->mlx.height) //mur bas
	{
		int	texture_y = (data->ray[i].pix_y - data->ray[i].htop_wall) * data->ray[i].img->height / test;
		// *(unsigned int *)pixel_addr = 0x00F00FF;
			pixel_addr = test1 + (data->ray[i].pix_y * data->screen->size_line);
		char *texture_pixel = data->ray[i].img->data_addr + (texture_y * data->ray[i].img->size_line + texture_x);
		unsigned int color = *(unsigned int *)texture_pixel;
		*(unsigned int *)pixel_addr = color;
		data->ray[i].pix_y++;
		// if (data->ray[i].dist_wall < 40)
		// 	data->ray[i].pix_y += 1;
	}
	data->ray[i].pix_y = data->ray[i].htop_wall;
	if (data->ray[i].pix_y < 0)
		data->ray[i].pix_y = 0;
	while (data->ray[i].pix_y > 0) // ciel
	{
		pixel_addr = test1 + ((data->ray[i].pix_y)
					* data->screen->size_line);
		*(unsigned int *)pixel_addr = 0xFF002000;
		data->ray[i].pix_y--;
	}
	data->ray[i].pix_y = data->ray[i].hbot_wall;
	if (data->ray[i].pix_y < 0)
		data->ray[i].pix_y = 0;
	while (data->ray[i].pix_y < data->mlx.height) // sol
	{
		// floor_render(data, ray, data->ray[i].pix_y);
		pixel_addr =  test1 + ((data->ray[i].pix_y)
					* data->screen->size_line);
		*(unsigned int *)pixel_addr = 0xFF4F4F4F;
		data->ray[i].pix_y++;
	}
}

void    display_game(t_data *data, int i, double x)
{
	data->ray[i].dist_wall = sqrt(((data->ray[i].case_y - data->map.player_coo->y) * 64.0 + (data->ray[i].coo_y - data->map.mini.player_coo.y))  *  ((data->ray[i].case_y - data->map.player_coo->y) * 64.0 + (data->ray[i].coo_y - data->map.mini.player_coo.y))
	+ ((data->ray[i].case_x - data->map.player_coo->x) * 64.0 + (data->ray[i].coo_x - data->map.mini.player_coo.x)) * ((data->ray[i].case_x - data->map.player_coo->x) * 64.0 + (data->ray[i].coo_x - data->map.mini.player_coo.x)));
	data->ray[i].dist_wall *= cos(atan(x));
	// printf(" ray rad %lf \n",data->ray[i].deg);
	data->ray[i].size_wall = data->ray[i].d_proj / (double)(data->ray[i].dist_wall/64.0);
	data->ray[i].pix_x = i;
	// printf("pix>%d\n",data->ray[i].pix_x);
	// data->ray[i].pix_x = 1 + data->mlx.width * 0.25 - ((data->ray[i].d_proj * tan(i * (M_PI / 180))) / (2 * data->ray[i].d_proj * tan((90 * 0.5) * (M_PI / 180)))) * data->mlx.width * 0.5;
	data->ray[i].pix_y = data->mlx.height * 0.5; // sa degagera
	data->ray[i].max_height = data->mlx.height * 0.5; // sa degagera
	data->ray[i].max_size_wall = data->ray[i].size_wall * 0.5; // sa degagera
	data->ray[i].calc_bits = (int)(data->screen->bits_per_pixel >> 3);
	data->ray[i].data_addr = data->screen->data_addr;
	data->ray[i].htop_wall = round(data->ray[i].max_height - data->ray[i].max_size_wall);
	data->ray[i].hbot_wall = round(data->ray[i].max_height + data->ray[i].max_size_wall);
	check_dir(data, i);
	display_game_loop(data, i);

}
