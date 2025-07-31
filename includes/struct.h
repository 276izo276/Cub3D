#ifndef STRUCT_H
# define STRUCT_H

#include "t_lst.h"
#include <sys/time.h>

# define SIZE_MAP (5 * 64)
# define FPS 120.0
# define V_FOV 90.0
# define H_FOV 90.0
# define FPM 60.0

typedef struct s_data		t_data;
typedef struct s_map		t_map;
typedef struct s_img		t_img;
typedef struct s_ray		t_ray;
typedef struct s_color		t_color;
typedef	struct s_mlx		t_mlx;
typedef struct s_coo		t_coo;
typedef struct s_coo_mini		t_coo_mini;
typedef	struct s_mini		t_mini;
typedef struct s_utils_mini	t_utils_mini;


typedef	enum e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST
} t_dir;

struct s_coo
{
	int	x;
	int	y;
};

struct	s_ray
{
	double	d_proj;
	double	deg;
	double	coo_y;
	double	coo_x;
	int		case_y;
	int		case_x;
	double	rad;
	double	delta_x;
	double	delta_y;
	double	rx;
	double	ry;
	double	dist_wall;
	double	size_wall;
	int		pix_y;
	int		pix_x;
	char	*pixel_addr;
	int		dir;
	char	*img_addr;
	double	max_height;
	double	max_size_wall;
	double	htop_wall;
	double	hbot_wall;
	char	*data_addr;
	int		calc_bits;
	double	save_x;
	t_coo	texture_coo;
	t_img	*img;
};

struct s_coo_mini
{
	double	x;
	double	y;
};

struct	s_img
{
	void	*mlx;
	char	*path;
    char    *data_addr;
	void	*img;
	int		width;
	int		height;
    int     bits_per_pixel;
    int     size_line;
    int     endian;
};

struct s_color
{
	int	r;
	int	g;
	int	b;
};

struct s_mlx
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
};

struct s_utils_mini
{
	int				new_y;
	int				new_x;
	int				y;
	int				x;
	t_coo			s;
	t_coo			i;
	int				size;
	char			*pixel_addr;
	unsigned int	color;
	t_img			mmap;
	double			cos_val;
	double			sin_val;
	double			xdest;
	double			ydest;
	double			xfloat;
	double			yfloat;
};


struct s_mini
{
	int			need_print[SIZE_MAP][SIZE_MAP];
	t_img		img[7];
	int			height;
	int			width;
	t_coo_mini	player_coo;
	double		deg;
	double		rad;
	double		speed;
};

struct s_map
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
	t_img	*text_floor;
	t_img	*text_sky;
	t_mini	mini;
	t_color	*floor;
	t_color	*ceiling;
};

struct s_data
{
	t_utils_mini	u;
	t_img			*screen;
	long long int	time_fps;
	long long int	time_move;
	int				frame_move;
	int				ac;
	char			**av;
	t_map			map;
	t_mlx			mlx;
	t_ray		*ray;
	int				keycode[100];
	// t_img	*wh;
	// t_img	*bl;
};



t_coo	*init_t_coo(int y, int x);

#endif
