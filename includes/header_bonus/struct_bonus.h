#ifndef STRUCT_H
# define STRUCT_H

#include "t_lst.h"
# include <stdbool.h>
#include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

# define SIZE_MAP (5 * 64)
# define FPS 120.0
# define V_FOV 90.0
# define H_FOV 90.0
# define FPM 60.0
# define GAME 1
# define MENU 0
# define SPEED 5
# define KEYCODE_NB 100

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
typedef struct s_display	t_display;
typedef struct s_coa		t_coa;
typedef struct s_spell		t_spell;
typedef struct s_hit_door	t_hit_door;
typedef struct s_door		t_door;
typedef struct s_hitray		t_hitray;

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

struct s_door
{
	t_coo	coo;
	t_coo	first_p;
	t_coo	second_p;
	double	pos;
	bool	is_open;
	bool	is_verti;
};

struct s_hit_door
{
	t_door *door;
	double	coo_y;
	double	coo_x;
	int		case_y;
	int		case_x;
	bool	use;
	bool	print;
	double	dist_door;
	double	size_door;
	double	max_size_door;
	double	htop_door;
	double	hbot_door;
	int		dir;
	t_coo	texture_coo;
	double	ry;
	double	rx;
	double	end_y;
	double	end_x;
	double	start_y;
	double	start_x;
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
	t_hit_door	**doors;
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
	double		dy;
	double		dx;
};

struct s_map
{
	int		fd;
	int		tabmap_height;
	char	**tabmap;
	t_door	***door_map;
	t_coo	*player_coo;
	t_lst	*lines;
	t_lst	*map;
	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;
	t_img	*door;
	t_img	*fixed_door;
	t_mini	mini;
	t_img	*floor;
	t_img	*ceiling;
};

struct s_display
{
	char			*pixel_addr;
	double			cos_angle;
	double			sin_angle;
	int				screen_bbp_frac;
	int				text_bpp_frac;
	double			dist_center;
	double			screen_y;
	double			dist_texture;
	double			screen_x;
	double			world_x;
	double			world_y;
	double			pos_cellx;
	double			pos_celly;
	int				text_x;
	int				text_y;
	char			*texture_pixel;
	unsigned int	color;
	int				player_height;
};

struct s_spell
{
	t_img	*lumos;
	int		x_wand;
	int		y_wand;
	bool	active;
	int		count_frame;
};

struct s_coa
{
	int		color;
	char	*name;
	t_img	*img_coa;
	t_img 	*border;
};

struct	s_hitray
{
	int		i;
	int		j;
	double	delta;
	double	delta_t;
	double	delta_u;
	double	t;
	double	u;
	double	ax;
	double	ay;
	double	bx;
	double	by;
	double	cx;
	double	cy;
	double	dx;
	double	dy;
	double	hx;
	double	hy;
	bool	hit;
};

struct s_data
{
	t_utils_mini		u;
	t_img				*screen;
	long long int		time_fps;
	long long int		time_move;
	int					frame_move;
	int					ac;
	char				**av;
	int					status;
	int					nb_coalition;
	t_map				map;
	t_mlx				mlx;
	t_ray				*ray;
	t_display			display;
	t_spell				spell;
	int					keycode[100];
	pthread_mutex_t		m_data_ray;
	pthread_t			thread_wall;
	pthread_t			thread_floor;
	pthread_t			thread_door;
	pthread_t			thread_sky;
	sem_t				*sem_background;
	sem_t				*sem_door;
	sem_t				*sem_map;
	pthread_barrier_t		barrier;
	t_coa				*coa;
	int					color;
	int					selected;
	t_img				*select;
	t_img				*select_hand;
	t_img				*player_hand;
	t_img				*player_wand;
	t_img				*left_select;
	bool				is_right_handed;
	int					nb_door;
	t_door				**doors;
	// t_img	*wh;
	// t_img	*bl;
};



t_coo	*init_t_coo(int y, int x);

#endif
