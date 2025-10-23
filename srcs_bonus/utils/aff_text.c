#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include "color_bonus.h"

#include <stdio.h>

int	calc_start_text(char *str, int x, t_data *data, int height)
{
	int				i;
	t_img			*img;
	int				size;

	// new.x = ;
	i = 0;
	img = NULL;
	size = 0;
	while (str && str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			img = &data->img[str[i] - 'a' + CHAR_A];
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			img = &data->img[str[i] - 'A' + CHAR_A];
		}
		else if (str[i] >= '0' && str[i] <= '9')
			img = &data->img[str[i] - '0' + NB_0];
		else
			img = &data->img[0];
		size = size + (double)((double)img->width / (double)img->height) * height;
		i++;
	}
	return (x - size / 2);
}

#include <stdlib.h>

void	aff_text(char *str, int height, t_coo coo, t_data *data)
{
	int				i;
	t_img			*img;
	t_coo			new;
	t_coo			cur;
	unsigned int	color;

	// new.x = ;
	if (coo.y <= MARGIN)
	{
		coo.y = MARGIN;
	}
	new.y = coo.y + height;
	i = 0;
	img = NULL;
	while (str && str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			img = &data->img[str[i] - 'a' + CHAR_A];
		else if (str[i] >= 'A' && str[i] <= 'Z')
			img = &data->img[str[i] - 'A' + CHAR_A];
		else if (str[i] >= '0' && str[i] <= '9')
			img = &data->img[str[i] - '0' + NB_0];
		else
			img = &data->img[0];
		// printf("width aff %d\n",(int)(coo.x + ((double)img->width / (double)img->height) * height));

		cur.y = coo.y;
		new.x = coo.x + (double)((double)img->width / (double)img->height) * height;
		while (cur.y < new.y && cur.y < data->mlx.height)
		{
			cur.x = coo.x;
			if (cur.x < 0)
				cur.x = 0;
			while (cur.x < new.x && cur.x < data->mlx.width)
			{
				// printf("rap >>%lf  %d\n",(double)(cur.y - coo.y) / (double)height * img->height, img->height);
				unsigned int	a = (unsigned int)((double)((double)(cur.y - coo.y) / (double)height) * img->height);
				unsigned int	b = (unsigned int)((double)((double)(cur.x - coo.x) / (double)(new.x - coo.x)) * img->width);
				color = *(unsigned int *)(img->data_addr + a * img->size_line + b * (img->bits_per_pixel >> 3));
				// printf("%X",color);
				if (color != RED)
					*(unsigned int *)(data->screen->data_addr + (cur.y - MARGIN) * data->screen->size_line + cur.x * (data->screen->bits_per_pixel >> 3)) = color;
				cur.x++;
			}
			cur.y++;
		}
		coo.x = coo.x + (double)((double)img->width / (double)img->height) * height;
		i++;
	}
}