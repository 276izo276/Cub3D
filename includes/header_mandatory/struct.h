/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:44:18 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:44:19 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "t_lst.h"
# include <pthread.h>
# include <sys/time.h>

# define SIZE_MAP 320
# define FPS 120.0
# define V_FOV 90.0
# define H_FOV 90.0
# define FPM 60.0
# define SPEED 5
# define KEYCODE_NB 100

typedef struct s_data		t_data;
typedef struct s_map		t_map;
typedef struct s_img		t_img;
typedef struct s_ray		t_ray;
typedef struct s_color		t_color;
typedef struct s_mlx		t_mlx;
typedef struct s_coo		t_coo;
typedef struct s_coo_mini	t_coo_mini;
typedef struct s_mini		t_mini;
typedef struct s_utils_mini	t_utils_mini;
typedef struct s_display	t_display;

typedef enum e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_dir;

struct	s_coo
{
	int						x;
	int						y;
};

struct	s_ray
{
	double			d_proj;
	double			deg;
	double			coo_y;
	double			coo_x;
	int				case_y;
	int				case_x;
	double			rad;
	double			delta_x;
	double			delta_y;
	double			rx;
	double			ry;
	double			dist_wall;
	double			size_wall;
	int				pix_y;
	int				pix_x;
	char			*pixel_addr;
	int				dir;
	char			*img_addr;
	double			max_height;
	double			max_size_wall;
	double			htop_wall;
	double			hbot_wall;
	char			*data_addr;
	int				calc_bits;
	double			save_x;
	t_coo			texture_coo;
	t_img			*img;
	pthread_mutex_t	nb_ray;
	pthread_t		thread_wall;
	pthread_t		thread_floor;
	pthread_t		thread_sky;
};

struct	s_coo_mini
{
	double	x;
	double	y;
};

struct	s_img
{
	void	*mlx;
	char	*path;
	char	*data_addr;
	void	*img;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
};

struct	s_color
{
	int	r;
	int	g;
	int	b;
};

struct	s_mlx
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
};

struct	s_utils_mini
{
	unsigned int	color;
	int				new_y;
	int				new_x;
	int				y;
	int				x;
	int				size;
	char			*pixel_addr;
	double			cos_val;
	double			sin_val;
	double			xdest;
	double			ydest;
	double			xfloat;
	double			yfloat;
	t_coo			i;
	t_coo			s;
	t_img			mmap;
};

struct	s_mini
{
	int			need_print[SIZE_MAP][SIZE_MAP];
	int			height;
	int			width;
	double		deg;
	double		rad;
	double		speed;
	double		dy;
	double		dx;
	t_img		img[7];
	t_coo_mini	player_coo;
};

struct	s_map
{
	int		fd;
	int		tabmap_height;
	char	**tabmap;
	t_coo	*player_coo;
	t_lst	*lines;
	t_lst	*map;
	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;
	t_mini	mini;
	t_color	*floor;
	t_color	*ceiling;
};

struct	s_display
{
	unsigned int	color;
	int				screen_bbp_frac;
	int				text_bpp_frac;
	int				text_x;
	int				text_y;
	double			cos_angle;
	double			sin_angle;
	double			dist_center;
	double			screen_y;
	double			dist_texture;
	double			screen_x;
	double			world_x;
	double			world_y;
	double			pos_cellx;
	double			pos_celly;
	char			*pixel_addr;
	char			*texture_pixel;
};

struct	s_data
{
	long long int	time_fps;
	long long int	time_move;
	int				keycode[100];
	int				frame_move;
	int				ac;
	char			**av;
	t_utils_mini	u;
	t_display		display;
	t_map			map;
	t_mlx			mlx;
	t_ray			*ray;
	t_img			*screen;
};

t_coo						*init_t_coo(int y, int x);

#endif
