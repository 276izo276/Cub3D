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

void    display_games(t_data *data, t_ray ray, double i)
{
	ray.dist_wall = sqrt(((ray.case_y - data->map.player_coo->y) * 64.0 + (ray.coo_y - data->map.mini.player_coo.y))  *  ((ray.case_y - data->map.player_coo->y) * 64.0 + (ray.coo_y - data->map.mini.player_coo.y))
	+ ((ray.case_x - data->map.player_coo->x) * 64.0 + (ray.coo_x - data->map.mini.player_coo.x)) * ((ray.case_x - data->map.player_coo->x) * 64.0 + (ray.coo_x - data->map.mini.player_coo.x))  );
	// printf("cos angle >>>%lf\n",cos(fabs(i) * (M_PI / 180)));
	// printf("Angle=%lf   Distance_total=%lf\n",i,ray.dist_wall);
	ray.dist_wall *= cos(i * (M_PI / 180.0));
	// dist_wall *= .5;
	// double d_proj = data->mlx.height / 2 * tan(50 * (M_PI / 180)); HERE
	ray.size_wall = ray.d_proj / (double)(ray.dist_wall/64.0);
	// printf("dproj=%lf    Hauteur=%lf   mlx_height=%d\n",data->mlx.height / 2 * tan(30 * (M_PI / 180)), size_wall, data->mlx.height);
	ray.pix_x = data->mlx.width / 4 - ((ray.d_proj * tan(i * (M_PI / 180))) / (2 * ray.d_proj * tan((90/2) * (M_PI / 180)))) * data->mlx.width / 2;
	ray.pix_y = data->mlx.height / 2;
	// img_proj.img = mlx_new_image(data->mlx.mlx, data->mlx.width, data->mlx.height);
	// img_proj.data_addr = mlx_get_data_addr(img_proj.img,&img_proj.bits_per_pixel,&img_proj.size_line,&img_proj.endian);
	// double	pix_img_y = 1024;
	// double	pix_img_x = 1024;
	// write(1,"HERE\n",5);
	while (ray.pix_y > data->mlx.height / 2 - ray.size_wall/2 && ray.pix_y > 0 )
	{
		ray.pixel_addr = data->screen->data_addr + (ray.pix_y
					* data->screen->size_line + ray.pix_x
					* (data->screen->bits_per_pixel / 8));
		// printf("----  %d     %d  ----\n",ray.pix_y,pix_x);
		*(unsigned int *)ray.pixel_addr = 0x000000FF;
		// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,ray.pix_y,0x0000FF);
		// printf("put pixel >>> %d  %d\n",pix_x,ray.pix_y);
		ray.pix_y--;
	}
	while (ray.pix_y > 0)
	{
		ray.pixel_addr = data->screen->data_addr + ((ray.pix_y)
					* data->screen->size_line + (ray.pix_x)
					* (data->screen->bits_per_pixel / 8));
		// printf("put pixel >>> %d  %d\n",pix_x,ray.pix_y);
		*(unsigned int *)ray.pixel_addr = 0x00000000;
		// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,ray.pix_y,0x000000);
		ray.pix_y--;
	}
	ray.pix_y = data->mlx.height / 2;
	while (ray.pix_y < data->mlx.height / 2 + ray.size_wall/2 && ray.pix_y < data->mlx.height )
	{
		ray.pixel_addr = data->screen->data_addr + ((ray.pix_y)
					* data->screen->size_line + (ray.pix_x)
					* (data->screen->bits_per_pixel / 8));
		// printf("put pixel >>> %d  %d\n",pix_x,ray.pix_y);
		*(unsigned int *)ray.pixel_addr = 0x000000FF;
		// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,ray.pix_y,0x0000FF);
		ray.pix_y++;
	}
	while (ray.pix_y < data->mlx.height)
	{
		ray.pixel_addr = data->screen->data_addr + ((ray.pix_y)
					* data->screen->size_line + (ray.pix_x)
					* (data->screen->bits_per_pixel / 8));
		// printf("put pixel >>> %d  %d\n",pix_x,ray.pix_y);
		*(unsigned int *)ray.pixel_addr = 0x00000000;
		// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,ray.pix_y,0x000000);
		ray.pix_y++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,0);
	// mlx_destroy_image(data->mlx.mlx,img_proj.img);
}