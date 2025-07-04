#include "struct.h"
#include "texture.h"
#include "cub3d.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>



#include "ft_printf.h"

void	aff_pix_in_img(t_utils_mini *u, t_mini *mini)
{
	u->s.y = 1 * 64 + 32 + (u->y * 64 + 64 - mini->player_coo.y);
	u->i.y = 0;
	while (u->i.y < 64)
	{
		u->s.x = 1 * 64 + 32 + (u->x * 64 + 64
			- u->data->map.mini.player_coo.x);
		u->i.x = 0;
		while (u->s.y + u->i.y >= 0 && u->s.y + u->i.y < u->size && u->i.x < 64)
		{
			if (u->s.x + u->i.x >= 0 && u->s.x + u->i.x < u->size)
			{
				u->pixel_addr = u->mmap->data_addr + ((u->s.y + u->i.y) * u->mmap
						->size_line + (u->s.x + u->i.x)
						* (u->mmap->bits_per_pixel / 8));
				*(unsigned int *)u->pixel_addr = 0x00000000;
				// ft_printf_fd(2," HERERERE >>> >%s<  >%d<",*u->pixel_addr,*u->pixel_addr);
			}
			u->i.x++;
		}
		u->i.y++;
	}
}

void	aff_color_in_img(t_utils_mini *u, t_mini *mini)
{
	u->s.y = 1 * 64 + 32 + (u->y * 64 + 64 - mini->player_coo.y);
	u->i.y = 0;
	while (u->i.y < 64)
	{
		u->s.x = 1 * 64 + 32 + (u->x * 64 + 64 - mini->player_coo.x);
		u->i.x = 0;
		while (u->s.y + u->i.y >= 0 && u->s.y + u->i.y < u->size && u->i.x < 64)
		{
			if (u->s.x + u->i.x >= 0 && u->s.x + u->i.x < u->size)
			{
				u->pixel_addr = u->mmap->data_addr
						+ ((u->s.y + u->i.y) * u->mmap
						->size_line + (u->s.x + u->i.x)
						* (u->mmap->bits_per_pixel / 8));
				if (u->data->map.tabmap[u->new_y][u->new_x] == '1')
					get_pixel_color(u, MINI_WALL);
				else
					get_pixel_color(u, MINI_FLOOR);
				// ft_printf_fd(2," HERERERE >>> >%s<  >%d<    >%s<   >%d<",*u->pixel_addr,*u->pixel_addr,u->color,u->color);
				*(unsigned int *)u->pixel_addr = u->color;
				// ft_printf_fd(2," HERERERE >>> >%s<  >%d<",*u->pixel_addr,*u->pixel_addr);
			}
			u->i.x++;
		}
		u->i.y++;
	}
}

// void	set_player_in_mini_map(t_utils_mini *u)
// {
// 	u->y = u->size / 2 - 2;
// 	while (u->y < u->size / 2 + 2)
// 	{
// 		u->x = u->size / 2 - 2;
// 		while (u->x < u->size / 2 + 2)
// 		{
// 			char *pixel_addr = u->mmap->data_addr
// 				+ (u->y * u->mmap->size_line + u->x
// 				* (u->mmap->bits_per_pixel / 8));
// 			*(unsigned int *)pixel_addr = 0x00FF0000;
// 			u->x++;
// 		}
// 		u->y++;
// 	}
// }

// int	get_color(double sin_a, double cos_a, double dx, double dy)
// {
// 	double r_dx;
// 	double r_dy;

// 	r_dx = -dx * cos_a + dy * sin_a;
// 	r_dy = dx * sin_a + dy * cos_a;
// 	if ((r_dy >= -3.5 && r_dy <= -2.5 && r_dx >= -0.5 && r_dx <= 0.5)
// 		|| (r_dy >= -2.5 && r_dy <= -1.5 && r_dx >= -1.5 && r_dx <= 1.5)
// 		|| (r_dy >= -1.5 && r_dy <= -0.5 && r_dx >= -2.5 && r_dx <= 2.5))
// 		return (0x00FFFF00);
// 	else if (r_dy >= -0.5 && r_dy <= 3.5 && r_dx >= -1.5 && r_dx <= 1.5)
// 		return (0x00FF0000);
// 	return (0);
// }

// void	set_player_in_mini_map(t_utils_mini *u, double angle)
// {
// 	double	center_x;
// 	double	center_y;
// 	double	cos_a;
// 	double sin_a;
// 	double	dy;
// 	double	dx;
// 	int		color;

// 	dy = -3;
// 	center_x = u->size / 2;
// 	center_y = u->size / 2;
// 	cos_a = cos(angle);
// 	sin_a = sin(angle);
// 	while (dy <= 3)
// 	{
// 		dx = -3;
// 		while (dx <= 3)
// 		{
// 			color = get_color(sin_a, cos_a, dx, dy);
// 			if (color)
// 			{
// 				u->x = center_x + dx;
// 				u->y = center_y + dy;
// 				char *pixel_addr = u->mmap->data_addr
// 				+ (u->y * u->mmap->size_line + u->x
// 					* (u->mmap->bits_per_pixel / 8));
// 					*(unsigned int *)pixel_addr = color;
// 			}
// 			++dx;
// 		}
// 		++dy;
// 	}
// }

void	set_player_in_mini_map(t_utils_mini *u, t_img *img, double rad)
{
	(void)rad;
	int	start_y = u->size / 2 - img->height / 2;
	int	start_x = u->size / 2 - img->width / 2;

	u->y = 0;
	while (u->y < img->height)
	{
		u->x = 0;
		while (u->x < img->width)
		{
			double cos_theta = cos(rad);
			double sin_theta = sin(rad);
			double translated_x_dest = u->x - 16;
			double translated_y_dest = u->y - 19;
			double src_x_float = -(translated_x_dest) * cos_theta + (translated_y_dest) * sin_theta + 16;
			double src_y_float = (translated_x_dest) * sin_theta + (translated_y_dest) * cos_theta + 19;
			u->color = *(unsigned int *)(img->data_addr + ((u->y)
				* img->size_line
				+ (u->x) * (img->bits_per_pixel / 8)));
			if (u->color != 0x00000000)
			{
				u->pixel_addr = u->mmap->data_addr
				+ (((int)ceil(src_y_float) + start_y) * u->mmap->size_line + ((int)ceil(src_x_float) + start_x)
				* (u->mmap->bits_per_pixel / 8));
				*(unsigned int *)u->pixel_addr = u->color;
				u->pixel_addr = u->mmap->data_addr
				+ (((int)floor(src_y_float) + start_y) * u->mmap->size_line + ((int)floor(src_x_float) + start_x)
				* (u->mmap->bits_per_pixel / 8));
				*(unsigned int *)u->pixel_addr = u->color;
			}
			u->x++;
		}
		u->y++;
	}
}

void	aff_mini_map(t_data *data)
{
	t_utils_mini	u;

	init_utils_mini(&u, data);
	while (++u.y < 4)
	{
		u.x = -4;
		while (++u.x < 4)
		{
			u.new_y = data->map.player_coo->y + u.y;
			u.new_x = data->map.player_coo->x + u.x;
			if (u.new_y >= data->map.tabmap_height || u.new_y < 0
			|| u.new_x >= ft_strlen(data->map.tabmap[u.new_y]) || u.new_x < 0
			|| data->map.tabmap[u.new_y][u.new_x] == ' ')
			{
				aff_pix_in_img(&u, &u.data->map.mini);
			}
			else
			{
				aff_color_in_img(&u,&u.data->map.mini);
			}
		}
	}
	set_player_in_mini_map(&u, &u.data->map.mini.img[MINI_CURS], data->map.mini.rad);
	print_mini_map(&u);
}

