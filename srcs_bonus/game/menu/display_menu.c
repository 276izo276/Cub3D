#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"

static int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->data_addr + (y * texture->size_line + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

void	pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*tmp_addr;

	if (x >= 0 && x < data->mlx.width && y >= 0 && y < data->mlx.height)
	{
		tmp_addr = data->screen->data_addr + (y * data->screen->size_line + x
				* (data->screen->bits_per_pixel / 8));
		*(unsigned int *)tmp_addr = color;
	}
}

static void	draw_texture_menu(t_data *data, t_img *texture, int final_x,
		int final_y)
{
	int				x;
	int				y;
	unsigned int	color;

	color = 0;
	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			color = get_texture_pixel(texture, x, y);
			pixel_put(data, final_x + x, final_y + y, color);
			++x;
		}
		++y;
	}
}

static void select_your_coa(t_data *data)
{
	int	color;
	int	start_x;
	int	start_y;

	color = 0;
	start_x = (data->mlx.width - (2 * data->menu[0].img_coa->width + 200)) / 2;
	start_y = (data->mlx.height - (2 * data->menu[0].img_coa->height - 100))
		/ 2;
	draw_texture_menu(data, data->select, 0, 0);
	draw_texture_menu(data, data->menu[0].img_coa, start_x, start_y);
	draw_texture_menu(data, data->menu[1].img_coa, start_x
		+ data->menu[0].img_coa->width + 150, start_y);
	draw_texture_menu(data, data->menu[2].img_coa, start_x, start_y
		+ data->menu[0].img_coa->height + 100);
	draw_texture_menu(data, data->menu[3].img_coa, start_x
		+ data->menu[0].img_coa->width + 150, start_y
		+ data->menu[0].img_coa->height + 100);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,
		0);
	draw_select_border(data, start_x, start_y);
}

static void draw_y_border(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 4)
		{
			pixel_put(data, x + j, y + i, data->color);
			pixel_put(data, x + 230 - j, y
				+ i, data->color);
			++j;
		}
		++i;
	}
}
static void draw_x_border(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 230)
	{
		j = 0;
		while (j < 4)
		{
			pixel_put(data, x + i, y + j, data->color);
			pixel_put(data, x + i, y
				+ 100 - j,
				data->color);
			++j;
		}
		++i;
	}
}

static void select_your_hand(t_data *data)
{

	int	y = data->mlx.height - 290;
	int x = 550;
	if (data->selected == 1)
		x += 650;
	draw_texture_menu(data, data->select_hand, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0, 0);
	draw_y_border(data, x, y);
	draw_x_border(data, x, y);
}

void	display_menu(t_data *data)
{
	if (data->color == 0)
		select_your_coa(data);
	else if (data->is_right_handed == 0)
		select_your_hand(data);
}
