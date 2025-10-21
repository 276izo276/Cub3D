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
# define MENU 0
# define GAME 1
# define PAUSE 2
# define FLOO_MAP 3
# define MAP 4
# define MENU_SPELL 5
# define SPEED 5
# define KEYCODE_NB 100
# define MAX_CREATE_ENEMY 50
# define MAX_CREATE_ITEM 100
# define ITEM 1
# define ENEMY 2
# define DOOR 3
# define BASIC 0
# define FRONT 1
# define BACK 2
# define REVERSED 3

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
typedef struct s_lumos		t_lumos;
typedef struct s_hit_door	t_hit_door;
typedef struct s_door		t_door;
typedef struct s_hitray		t_hitray;
typedef struct s_wall_msg	t_wall_msg;
typedef struct s_pause_menu	t_pause_menu;
typedef struct s_spell_menu	t_spell_menu;
typedef struct s_enemy		t_enemy;
typedef	struct s_fcoo		t_fcoo;
typedef struct s_case		t_case;
typedef struct s_hit_enemy	t_hit_enemy;
typedef struct s_hit_item	t_hit_item;
typedef struct s_foot		t_foot;
typedef struct s_player		t_player;
typedef struct s_damage		t_damage;
typedef struct s_item		t_item;
typedef struct s_spell		t_spell;

typedef	enum e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST
} t_dir;

typedef enum e_enum_class_spell
{
	DARK_SPELL,
	HEAL_SPELL,
	SUMMON_SPELL,
	OFFENSIVE_SPELL,
	DEFENSIVE_SPELL,
	CLASIC_SPELL
}	t_enum_class_spell;

typedef enum e_enemy_info
{
	DEMENTOR = '.',
	SPIDER = ',',
	WOLF = ';',
	TROLL = ':'
}	t_enemy_info;
# define NB_TYPE_ENEMY 4

typedef enum e_imgs
{
	SPACE,
	CHAR_A,
	CHAR_B,
	CHAR_C,
	CHAR_D,
	CHAR_E,
	CHAR_F,
	CHAR_G,
	CHAR_H,
	CHAR_I,
	CHAR_J,
	CHAR_K,
	CHAR_L,
	CHAR_M,
	CHAR_N,
	CHAR_O,
	CHAR_P,
	CHAR_Q,
	CHAR_R,
	CHAR_S,
	CHAR_T,
	CHAR_U,
	CHAR_V,
	CHAR_W,
	CHAR_X,
	CHAR_Y,
	CHAR_Z,
	NB_0,
	NB_1,
	NB_2,
	NB_3,
	NB_4,
	NB_5,
	NB_6,
	NB_7,
	NB_8,
	NB_9,
	SELECT,
	SELECT_HAND,
	PLAYER_HAND,
	PLAYER_WAND,
	LEFT_SELECT,
	DEMENTOR_FRONT,
	DEMENTOR_BACK,
	DOOR_MOVE,
	DOOR_FIXED,
	FLOO_CLOSE,
	FLOO_OPEN,
	HEART,
	SHIELD,
	XP,

	INCENDIO_IMG,
	GLACIUS_IMG,
	AVADA_KEDAVRA_IMG,
	PETRIFICUS_TOTALUS_IMG,
	PROTEGO_IMG,
	BOMBARDA_IMG,
	CONFUNDO_IMG,
	ENDOLORIS_IMG,
	EPISKEY_IMG,
	EXPECTO_PATRONUM_IMG,
	EXPELLIARMUS_IMG,
	REPULSO_IMG,
	STUPEFIX_IMG,
	OPPUGNO_IMG,
	SECTUMSEMPRA_IMG,
	SERPENSORTIA_IMG,
	VENTUS_IMG,
	VIPERA_EVANESCA_IMG,
	VULNERA_SANENTUR_IMG,
	ARANIA_EXUMAI_IMG,
	AGUAMENTI_IMG,

	LUMOS_ICN,
	INCENDIO_ICN,
	GLACIUS_ICN,
	AVADA_KEDAVRA_ICN,
	PETRIFICUS_TOTALUS_ICN,
	PROTEGO_ICN,
	BOMBARDA_ICN,
	CONFUNDO_ICN,
	ENDOLORIS_ICN,
	EPISKEY_ICN,
	EXPECTO_PATRONUM_ICN,
	EXPELLIARMUS_ICN,
	REPULSO_ICN,
	STUPEFIX_ICN,
	OPPUGNO_ICN,
	SECTUMSEMPRA_ICN,
	SERPENSORTIA_ICN,
	VENTUS_ICN,
	VIPERA_EVANESCA_ICN,
	VULNERA_SANENTUR_ICN,
	ARANIA_EXUMAI_ICN,
	AGUAMENTI_ICN,

	LUMOS_NAME,
	INCENDIO_NAME,
	GLACIUS_NAME,
	AVADA_KEDAVRA_NAME,
	PETRIFICUS_TOTALUS_NAME,
	PROTEGO_NAME,
	BOMBARDA_NAME,
	CONFUNDO_NAME,
	ENDOLORIS_NAME,
	EPISKEY_NAME,
	EXPECTO_PATRONUM_NAME,
	EXPELLIARMUS_NAME,
	REPULSO_NAME,
	STUPEFIX_NAME,
	OPPUGNO_NAME,
	SECTUMSEMPRA_NAME,
	SERPENSORTIA_NAME,
	VENTUS_NAME,
	VIPERA_EVANESCA_NAME,
	VULNERA_SANENTUR_NAME,
	ARANIA_EXUMAI_NAME,
	AGUAMENTI_NAME,

	FLAME,
	POISON,
	SLOW,
	CURSE,

	SHIELD_1,
	SHIELD_2,
	SHIELD_3,
	SHIELD_4,
	SHIELD_5,
	SHIELD_6,
}	t_imgs;
# define NB_TEXTURES 126

typedef enum e_spells
{
	LUMOS,
	PROTEGO,
	PETRIFICUS_TOTALUS,
	AGUAMENTI,
	INCENDIO,
	GLACIUS,
	BOMBARDA,
	VENTUS,
	EPISKEY,
	EXPECTO_PATRONUM,
	ARANIA_EXUMAI,
	
	EXPELLIARMUS,
	REPULSO, 	
	STUPEFIX,
	SECTUMSEMPRA,
	OPPUGNO,
	VULNERA_SANENTUR,
	VIPERA_EVANESCA,
	CONFUNDO,
	SERPENSORTIA,
	ENDOLORIS,	
	AVADA_KEDAVRA,
	
	
	IMPEDIMENTA,
	IMMOBULUS,
	IMPERO,
	REVELIO,
	APARECIUM,
	CONFRINGO,
	EVERTE_STATUM,
	EVANESCO,
	ALOHOMORA,
}	t_spells;
# define NB_SPELL 31

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

struct s_damage
{
	double		damage_do;
	double		damage_spider_do;
	double		damage_dementor_do;
	double		slow_force_do;
	double		slow_frame_do;
	double		poison_force_do;
	double		poison_frame_do;
	double		fire_force_do;
	double		fire_frame_do;
	double		curse_force_do;
	double		curse_frame_do;
	
	double		damage_take;
	double		damage_spider_take;
	double		damage_dementor_take;
	double		slow_force_take;
	double		slow_frame_take;
	double		poison_force_take;
	double		poison_frame_take;
	double		fire_force_take;
	double		fire_frame_take;
	double		curse_force_take;
	double		curse_frame_take;
};

struct	s_enemy
{
	t_img			*front_img;
	t_img			*back_img;
	t_enemy_info	type;
	t_fcoo			center;
	t_fcoo			left;
	t_fcoo			right;
	t_fcoo			center_before;
	t_fcoo			left_before;
	t_fcoo			right_before;
	double			deg;
	double			rad;
	double			radius;
	double			speed;
	double			life;
	t_damage		damage;
	t_fcoo			goal;
	t_case			*way;
	int				wait;
	bool			calc;
	int				calc_path;
	double			dist_player;
};

struct s_item
{
	t_img			*front_img;
	t_img			*back_img;
	t_fcoo			center;
	t_fcoo			left;
	t_fcoo			right;
	t_fcoo			center_before;
	t_fcoo			left_before;
	t_fcoo			right_before;
	double			deg;
	double			rad;
	double			radius;
	double			speed;
	t_damage		damage;
	unsigned int	nb_move;
};

struct s_door
{
	t_coo	coo;
	t_coo	first_p;
	t_coo	second_p;
	double	pos;
	bool	is_open;
	bool	is_verti;
	bool	is_floo_open;
	bool	is_floo;
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
	bool	is_floo;
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

struct s_hit_item
{
	t_img		*texture;
	t_item		*item;
	t_enemy		*enemy;
	t_door		*door;
	int			type;
	int			side;
	int			dist_height;
	double		door_status;
	char		*pixel_addr;
	char		*text_pix;
	unsigned int	color;
	double		coo_y;
	double		coo_x;
	int			case_y;
	int			case_x;
	bool		use;
	bool		print;
	double		dist;
	double		size;
	double		max_size;
	double		htop;
	double		hbot;
	int			dir;
	t_coo		texture_coo;
	double		ry;
	double		rx;
	double		end_y;
	double		end_x;
	double		start_y;
	double		start_x;
	double		posx;
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

struct s_spell_menu
{
	t_img	*background;
	int		selected;
	int		name_pos_y;
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
	t_hit_item	**items;
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
	t_img		img[14];
	int			last_foot;
	long long int	time_foot;
	int			height;
	int			width;
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
	int				fd;
	int				tabmap_height;
	int				nb_floo;
	char			**tabmap;
	int				zoom;
	double			last_pos_x;
	double			last_pos_y;
	bool			is_center;
	bool			floo_active;
	int				last_mouse_x;
	int				last_mouse_y;
	t_coo			*pos_active_floo;
	t_door			***door_map;
	t_wall_msg		***wall_map;
	t_img			**msg_img;
	t_lst			*lines;
	t_lst			*map;
	t_img			*north;
	t_img			*south;
	t_img			*west;
	t_img			*east;
	t_img			*door;
	t_img			*fixed_door;
	t_mini			mini;
	t_img			*floor;
	t_img			*ceiling;
	t_img			*dementor_front;
	t_img			*dementor_back;
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

struct s_lumos
{
	// t_img	*img;
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
	int		deg;
	bool	hit;
	double	radius;
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

struct s_spell
{
	t_img				*icn;
	t_img				*icn_name;
	t_damage			damage;
	t_item				item;
	t_spells			type;
	double				base_cooldown;
	double				base_timer;
	long long int		launch_time;
	long long int		end_time;
	void				(*call)(t_data *data, t_spells info);
	t_enum_class_spell	class;
};

struct	s_player
{
	double		life;
	double		shield;
	double		xp;
	t_damage	damage;
	t_fcoo		coo;
	t_fcoo		left;
	t_fcoo		right;
	t_fcoo		left_before;
	t_fcoo		right_before;
	double		radius;
	int			protego;
};

struct s_data
{
	t_img			img[NB_TEXTURES];
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
	t_lumos			lumos;
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
	pthread_t		thread_sky;
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
	t_spell_menu	spell_menu;
	double			sensitivity;
	// t_img	*wh;
	// t_img	*bl;
	int			nb_enemy;
	int			nb_create_enemy;
	t_player	player;
	t_spell		spell[NB_SPELL];
	int			spell_take[4];
	int			cast_spell;
	int			active_spell;
	t_lst		*enemy;
	t_lst		*item;
	t_lst		*door;
	int			frame_floo;
};

t_coo	*init_t_coo(int y, int x);

#endif
