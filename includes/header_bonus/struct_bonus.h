#ifndef STRUCT_H
# define STRUCT_H

# include "t_lst.h"
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

# define SIZE_MAP (5 * 64)
# define FPS 120.0
# define V_FOV 90.0
# define H_FOV 90.0
# define FPM 60.0
# define GAME 1
# define MENU 0
# define PAUSE 2
# define SPEED 5
# define KEYCODE_NB 100
# define NB_TYPE_ENEMY 4
# define MAX_CREATE_ENEMY 50

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
typedef struct s_wall_msg	t_wall_msg;
typedef struct s_pause_menu	t_pause_menu;
typedef struct s_enemy		t_enemy;
typedef	struct s_fcoo		t_fcoo;
typedef struct s_case		t_case;
typedef struct s_hit_enemy	t_hit_enemy;
typedef struct s_foot		t_foot;


typedef	enum e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST
} t_dir;

typedef	enum e_enemy_info
{
	DEMENTOR = '.',
	SPIDER = ',',
	WOLF = ';',
	TROLL = ':'
} t_enemy_info;

typedef enum e_imgs
{
	SELECT,
	SELECT_HAND,
	PLAYER_HAND,
	PLAYER_WAND,
	LEFT_SELECT
}	t_imgs;

typedef enum e_coas
{
	FIRE,
	WATER,
	EARTH,
	AIR
}	t_coas;

struct s_coo
{
	int	x;
	int	y;
};

struct s_fcoo
{
	double	coo_x;
	double	coo_y;
	int		case_y;
	int		case_x;
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

struct s_wall_msg
{
	t_coo	coo;
	t_coo	texture_coo;
	bool	is_active;
	int		pix_y;
	int		msg_nb;
	char	*img_addr;
	int		dir;
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

struct s_hit_enemy
{
	t_enemy	*enemy;
	double	coo_y;
	double	coo_x;
	int		case_y;
	int		case_x;
	bool	use;
	bool	print;
	double	dist_enemy;
	double	size_enemy;
	double	max_size_enemy;
	double	htop_enemy;
	double	hbot_enemy;
	int		dir;
	t_coo	texture_coo;
	double	ry;
	double	rx;
	double	end_y;
	double	end_x;
	double	start_y;
	double	start_x;
	double	posx;
};

struct s_pause_menu
{
	// int		pix_y;
	// char	*img_addr;
	// char	*data_addr;
	t_img	*sensitivity;
	t_img	*background;
	t_img	*exit;
	t_img	*resume;
	t_img	*selector;
	int		selected;
	long long int elapsed;
	long long int time;

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
	t_hit_enemy	**enemys;
	double	max_dist_wall;
	double	start_case_x;
	double	start_case_y;
	double	start_coo_x;
	double	start_coo_y;
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
	int				start_y;
	int				start_x;
};

struct s_foot
{
	t_fcoo	coo;
	bool	is_left;
	bool	is_save;
	int		foot_x;
	int		foot_y;
	double	rad;
};

struct s_mini
{
	int			need_print[SIZE_MAP][SIZE_MAP];
	t_foot		foot_tab[9];
	t_img		img[8];
	int			last_foot;
	long long int	time_foot;
	int			height;
	int			width;
	t_coo_mini	player_coo;
	double		deg;
	double		rad;
	double		speed;
	double		dy;
	double		dx;
	double		ny;
	double		nx;
	int			cy;
	int			cx;
};

struct s_map
{
	int		fd;
	int		tabmap_height;
	char	**tabmap;
	t_door	***door_map;
	t_wall_msg		***wall_map;
	t_img			**msg_img;
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
	t_img	*dementor_front;
	t_img	*dementor_back;
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
	int				pos_x_hand;
	int				pos_y_hand;
	int				move_hand;
	bool			is_up_move_hand;
	unsigned long long	elapsed_time;
	bool			is_msg_active;
	bool			is_first_msg;
	unsigned long long time_remove;
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
	double	rx;
	double	ry;
	double	delta_x;
	double	delta_y;
};

struct s_case
{
	t_case	*parent;
	t_case	*child;
	int		case_x;
	int		case_y;
	int		coo_x;
	int		coo_y;
	int		r_cost;
	int		h_cost;
	int		t_cost;
	int		is_path;
};

struct	s_enemy
{
	t_enemy_info	type;
	t_fcoo			center;
	t_fcoo			left;
	t_fcoo			right;
	double			deg;
	double			rad;
	int				radius;
	int				life;
	int				speed;
	t_fcoo			goal;
	t_case			*way;
	int				wait;
	bool			calc;
	int				calc_path;
};

struct s_data
{
	t_img			img[30];
	t_utils_mini	u;
	t_img			*screen;
	long long int	time_fps;
	long long int	time_move;
	int				frame_move;
	int				ac;
	char			**av;
	int				status;
	int				nb_coalition;
	t_map			map;
	t_mlx			mlx;
	t_ray			*ray;
	t_display		display;
	t_spell			spell;
	int				keycode[100];
	pthread_mutex_t	m_data_ray;
	pthread_t		thread_wall;
	pthread_t		thread_floor;
	pthread_t		thread_ray_first;
	pthread_t		thread_ray_snd;
	pthread_t		thread_ray_third;
	pthread_t		thread_ray_last;

	pthread_t		thread_fst_part;
	pthread_t		thread_snd_part;
	pthread_t		thread_third_part;
	pthread_t		thread_last_part;
	// pthread_t		thread_door;
	pthread_t		thread_sky;
	// sem_t			*sem_background;
	// sem_t			*sem_door;
	// sem_t			*sem_map;
	// sem_t			*sem_display;
	pthread_barrier_t		barrier_background;
	pthread_barrier_t		barrier_display;
	t_coa			*coa;
	int				color;
	int				selected;
	t_img			*select;
	t_img			*select_hand;
	t_img			*player_hand;
	t_img			*player_wand;
	t_img			*left_select;
	bool				is_right_handed;
	int					nb_door;
	t_door				**doors;
	bool				player_moved;
	int					current_msg;
	int					nb_msg;
	int				random_value;
	t_pause_menu	pause_menu;
	double			sensitivity;
	// t_img	*wh;
	// t_img	*bl;
	t_lst	*enemy;
	int		nb_enemy;
	int		nb_create_enemy;
};

t_coo	*init_t_coo(int y, int x);

#endif
