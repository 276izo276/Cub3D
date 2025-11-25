#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

# include "t_lst.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <sys/time.h>

# define BACK_SOUND_MP3 "sound/back_sound.mp3"
# define THEME_HP_MP3 "sound/theme_harry_potter.mp3"
# define SHOOT_MP3 "sound/shoot.mp3"
# define CRY_MP3 "sound/cry.mp3"
# define TP_MP3 "sound/teleportation.mp3"
# define DIE_MP3 "sound/die.mp3"
# define PAPER_MP3 "sound/paper.mp3"

# define LUMOS_MP3 "sound/spell/lumos.mp3"
# define ARANIA_EXUMAI_MP3 "sound/spell/arania_exumai.mp3"
# define PROTEGO_MP3 "sound/spell/protego.mp3"
# define INCENDIO_MP3 "sound/spell/incendio.mp3"
# define GLACIUS_MP3 "sound/spell/glacius.mp3"
# define REPULSO_MP3 "sound/spell/repulso.mp3"
# define AGUAMENTI_MP3 "sound/spell/aguamenti.mp3"
# define EXPELLIARMUS_MP3 "sound/spell/expelliarmus.mp3"
# define EPISKEY_MP3 "sound/spell/episkey.mp3"
# define EXPECTO_PATRONUM_MP3 "sound/spell/expecto_patronum.mp3"
# define PETRIFICUS_TOTALUS_MP3 "sound/spell/petrificus_totalus.mp3"
# define SERPENSORTIA_MP3 "sound/spell/serpensortia.mp3"
# define VENTUS_MP3 "sound/spell/ventus.mp3"
# define BOMBARDA_MP3 "sound/spell/bombarda.mp3"
# define STUPEFIX_MP3 "sound/spell/stupefix.mp3"
# define OPPUGNO_MP3 "sound/spell/oppugno.mp3"
# define VULNERA_SANENTUR_MP3 "sound/spell/vulnera_sanentur.mp3"
# define VIPERA_EVANESCA_MP3 "sound/spell/vipera_evanesca.mp3"
# define CONFUNDO_MP3 "sound/spell/confundo.mp3"
# define SECTUMSEMPRA_MP3 "sound/spell/sectumsempra.mp3"
# define ENDOLORIS_MP3 "sound/spell/endoloris.mp3"
# define AVADA_KEDAVRA_MP3 "sound/spell/avada_kedavra.mp3"

# define SIZE_MAP (5 * 64)
# define FPS 30.0
# define V_FOV 90.0
# define H_FOV 90.0
# define FPM 40.0
# define MENU 0
# define GAME 1
# define PAUSE 2
# define FLOO_MAP 3
# define MAP 4
# define MENU_SPELL 5
# define MENU_DEATH 6
# define MENU_END 7
# define SPEED 4
# define KEYCODE_NB 100
# define MAX_CREATE_ENEMY 50
# define MAX_CREATE_ITEM 100
# define ITEM 1
# define ENEMY 2
# define DOOR 3

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
typedef struct s_coa		t_coa;
typedef struct s_lumos		t_lumos;
typedef struct s_hit_door	t_hit_door;
typedef struct s_door		t_door;
typedef struct s_hitray		t_hitray;
typedef struct s_wall_msg	t_wall_msg;
typedef struct s_pause_menu	t_pause_menu;
typedef struct s_spell_menu	t_spell_menu;
typedef struct s_enemy		t_enemy;
typedef struct s_fcoo		t_fcoo;
typedef struct s_case		t_case;
typedef struct s_hit_enemy	t_hit_enemy;
typedef struct s_hit_item	t_hit_item;
typedef struct s_foot		t_foot;
typedef struct s_player		t_player;
typedef struct s_damage		t_damage;
typedef struct s_item		t_item;
typedef struct s_spell		t_spell;
typedef struct s_wand		t_wand;
typedef struct s_popo		t_popo;
typedef struct s_sorcerer	t_sorcerer;
typedef struct s_cooldown	t_cooldown;
typedef struct s_sound		t_sound;
typedef struct s_aff		t_aff;

typedef enum e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}							t_dir;

typedef enum e_side
{
	FRONT,
	BACK,
	RIGHT,
	LEFT,
	LEFT_BACK,
	LEFT_FRONT,
	RIGHT_FRONT,
	RIGHT_BACK,
	BASIC,
	REVERSED,
}							t_side;

typedef enum e_enum_class_spell
{
	DARK_SPELL,
	HEAL_SPELL,
	SUMMON_SPELL,
	OFFENSIVE_SPELL,
	DEFENSIVE_SPELL,
	CLASIC_SPELL
}							t_enum_class_spell;

typedef enum e_enemy_info
{
	DEMENTOR = '.',
	SPIDER = ',',
	WOLF = '<',
	ELEM = '>',
	BIRD = ';',
	SNAKE = ':',
	NANCY = '2',
	PILO = '3',
	ZIPPY = '4',
	KUNFANDI = '5',
	CAMEO = '6',
	ANAIS = '7',
	DIRLO = '8',
	STEF = '9',
	MARINA = 'm'
}							t_enemy_info;
# define NB_TYPE_ENEMY 15
# define NB_SORCERER 9

typedef enum e_imgs
{
	PAUSE_BACKGROUND,
	PAUSE_SENSITIVITY,
	PAUSE_RESUME,
	PAUSE_EXIT,
	PAUSE_SELECTOR,
	SPELL_BACKGROUND,
	BORDER_FIRE,
	BORDER_WATER,
	BORDER_EARTH,
	BORDER_AIR,
	MENU_AIR,
	MENU_FIRE,
	MENU_WATER,
	MENU_EARTH,
	WALL_MSG_1,
	WALL_MSG_2,
	WALL_MSG_3,
	WALL_MSG_COA,
	WALL_MSG_4,
	WALL_MSG_5,
	WALL_MSG_6,
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
	LEFT_SELECT,

	DEMENTOR_FRONT,
	DEMENTOR_SIDE_90,
	DEMENTOR_BACK,
	DEMENTOR_FRONT_45,
	DEMENTOR_BACK_45,

	KUNFANDI_FRONT,
	NANCY_FRONT,
	PILO_FRONT,
	ZIPPY_FRONT,
	CAMEO_FRONT,
	ANAIS_FRONT,
	DIRLO_FRONT,
	MARINA_FRONT,
	STEF_FRONT,

	KUNFANDI_FRONT_45,
	NANCY_FRONT_45,
	PILO_FRONT_45,
	ZIPPY_FRONT_45,
	CAMEO_FRONT_45,
	ANAIS_FRONT_45,
	DIRLO_FRONT_45,
	MARINA_FRONT_45,
	STEF_FRONT_45,

	SORCERER_SIDE_90,
	SORCERER_BACK,
	SORCERER_BACK_45,

	SNAKE_FRONT,
	SNAKE_SIDE_90,
	SNAKE_BACK,
	SNAKE_FRONT_45,
	SNAKE_BACK_45,

	SPIDER_FRONT,
	SPIDER_SIDE_90,
	SPIDER_BACK,
	SPIDER_FRONT_45,
	SPIDER_BACK_45,

	ELEM_FRONT,
	ELEM_SIDE_90,
	ELEM_BACK,
	ELEM_FRONT_45,
	ELEM_BACK_45,

	WOLF_FRONT,
	WOLF_SIDE_90,
	WOLF_BACK,
	WOLF_FRONT_45,
	WOLF_BACK_45,

	BIRD_FRONT,
	BIRD_SIDE_90,
	BIRD_BACK,
	BIRD_FRONT_45,
	BIRD_BACK_45,

	DOOR_MOVE,
	DOOR_FIXED,
	FLOO_CLOSE,
	FLOO_OPEN,
	HEART,
	SHIELD,
	XP,

	WEB_SPIDER_IMG,

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

	TIG_IMG,
	COMPANY_IMG,
	TAYLOR_SWIFT_IMG,
	LOGO_42_IMG,
	MARVIN_IMG,
	PIZZA_IMG,
	MAC_IMG,
	FOLDER_IMG,

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

	SPELL_LOCK,

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
	END_MENU,
	RETRY_BUTTON,
	QUIT_BUTTON,
	END_BACKGROUND,
	SANDGLASS,

	POPO_SHIELD,
	POPO_HEAL,
	POPO_FLOO,
	POPO_INVI,

	POPO_SHIELD_IMG,
	POPO_HEAL_IMG,
	POPO_FLOO_IMG,
	POPO_INVI_IMG,
	PORTKEY_IMG,

	PLAYER_WAND,
	PLAYER_WAND_2,
	PLAYER_WAND_3,
	PLAYER_WAND_4,
	PLAYER_WAND_5,
	PLAYER_WAND_6,
	PLAYER_WAND_7,

	WAND_SPIDER_IMG,
	WAND_DEMENTOR_IMG,
	WAND_WOLF_IMG,
	WAND_ELEM_IMG,
	PILLAR_IMG,

	END_IMG
}							t_imgs;
# define NB_TEXTURES END_IMG

typedef enum e_spells
{
	LUMOS,
	ARANIA_EXUMAI,
	PROTEGO,
	INCENDIO,
	GLACIUS,
	REPULSO,
	AGUAMENTI,
	EXPELLIARMUS,
	EPISKEY,
	EXPECTO_PATRONUM,
	PETRIFICUS_TOTALUS,
	SERPENSORTIA,
	VENTUS,
	BOMBARDA,
	STUPEFIX,
	OPPUGNO,
	VULNERA_SANENTUR,
	VIPERA_EVANESCA,
	CONFUNDO,
	SECTUMSEMPRA,
	ENDOLORIS,
	AVADA_KEDAVRA,

	END_SPELL
}							t_spells;
# define NB_SPELL END_SPELL

typedef enum e_items
{
	WEB_SPIDER,
	POISON_SPIDER,
	FIREBALL_ELEM,
	HEAL_POPO,
	SHIELD_POPO,
	FLOO_POPO,
	INVI_POPO,
	ANIM_DEATH,

	TIG,
	BH,
	PIZZA,
	MAC,
	FOLDER,
	MARVIN,
	TAYLOR_SWIFT,
	COMPANY,
	LOGO_42,
	PORTKEY,
	WOLF_WAND,
	SPIDER_WAND,
	ELEM_WAND,
	DEMENTOR_WAND,
	PILLAR,

	END_ITEM
}							t_items;
# define NB_TYPE_ITEM END_ITEM

typedef enum e_coas
{
	FIRE,
	WATER,
	EARTH,
	AIR,
	OTHERS
}							t_coas;

struct						s_coo
{
	int						x;
	int						y;
};

struct						s_fcoo
{
	double					coo_x;
	double					coo_y;
	int						case_y;
	int						case_x;
};

struct						s_wall_msg
{
	t_coo					coo;
	t_coo					texture_coo;
	bool					is_active;
	int						pix_y;
	int						msg_nb;
	char					*img_addr;
	int						dir;
};

struct						s_damage
{
	double					dist;
	t_fcoo					hit;
	double					damage_do;
	double					damage_spider_do;
	double					damage_dementor_do;
	double					damage_snake_do;
	double					damage_elem_do;
	double					slow_force_do;
	double					slow_frame_do;
	double					poison_force_do;
	double					poison_frame_do;
	double					fire_force_do;
	double					fire_frame_do;
	double					curse_force_do;
	double					curse_frame_do;
	double					confundo_frame_do;
	double					confundo_force_do;
	double					repulso_frame_do;
	double					repulso_force_do;

	double					damage_take;
	double					damage_spider_take;
	double					damage_dementor_take;
	double					damage_snake_take;
	double					damage_elem_take;
	double					slow_force_take;
	double					slow_frame_take;
	double					poison_force_take;
	double					poison_frame_take;
	double					fire_force_take;
	double					fire_frame_take;
	double					curse_force_take;
	double					curse_frame_take;
	double					confundo_frame_take;
	double					confundo_force_take;
	double					repulso_frame_take;
	double					repulso_force_take;
	int						which_coa_do;
	int						which_coa_take;
};

struct						s_enemy
{
	t_img					*front_img;
	t_img					*back_img;
	t_img					*side_img;
	t_img					*side_front_img;
	t_img					*side_back_img;
	t_enemy_info			type;
	t_fcoo					center;
	t_fcoo					left;
	t_fcoo					right;
	t_fcoo					center_before;
	t_fcoo					left_before;
	t_fcoo					right_before;
	double					aff_deg;
	double					aff_rad;
	double					deg;
	double					rad;
	double					radius;
	double					speed;
	double					life;
	t_damage				damage;
	t_fcoo					goal;
	t_case					*way;
	int						wait;
	bool					calc;
	int						calc_path;
	int						recalc_path;
	double					dist_target;
	long long int			time_attack_dist;
	long long int			time_attack_cac;
	int						cooldown_dist;
	double					cooldown_cac;
	int						dist_stop;
	int						dist_damage;
	int						dist_visu;
	int						nb_move;
	int						drop_heal;
	int						drop_shield;
	int						drop_floo;
	int						drop_cloak;
	int						drop_spider_wand;
	int						drop_wolf_wand;
	int						drop_dementor_wand;
	int						drop_elem_wand;
	unsigned int			color_coa;
};

struct						s_item
{
	t_img					*front_img;
	t_img					*back_img;
	t_fcoo					center;
	t_fcoo					left;
	t_fcoo					right;
	t_fcoo					center_before;
	t_fcoo					left_before;
	t_fcoo					right_before;
	double					deg;
	double					rad;
	double					radius;
	double					speed;
	int						type;
	int						categ;
	t_damage				damage;
	unsigned int			nb_move;
	double					deg_rotate;
	int						coa;
};

struct						s_door
{
	t_coo					coo;
	t_coo					first_p;
	t_coo					second_p;
	double					pos;
	bool					is_open;
	bool					is_verti;
	bool					is_floo_open;
	bool					is_floo;
};

struct						s_hit_door
{
	t_door					*door;
	double					coo_y;
	double					coo_x;
	int						case_y;
	int						case_x;
	bool					use;
	bool					print;
	double					dist_door;
	double					size_door;
	double					max_size_door;
	double					htop_door;
	double					hbot_door;
	int						dir;
	t_coo					texture_coo;
	double					ry;
	double					rx;
	double					end_y;
	double					end_x;
	double					start_y;
	double					start_x;
	bool					is_floo;
};

struct						s_hit_enemy
{
	t_enemy					*enemy;
	double					coo_y;
	double					coo_x;
	int						case_y;
	int						case_x;
	bool					use;
	bool					print;
	double					dist_enemy;
	double					size_enemy;
	double					max_size_enemy;
	double					htop_enemy;
	double					hbot_enemy;
	int						dir;
	t_coo					texture_coo;
	double					ry;
	double					rx;
	double					end_y;
	double					end_x;
	double					start_y;
	double					start_x;
	double					posx;
};

struct						s_hit_item
{
	t_img					*texture;
	t_item					*item;
	t_enemy					*enemy;
	t_door					*door;
	int						categ;
	int						type;
	int						status;
	int						side;
	int						dist_height;
	double					door_status;
	char					*pixel_addr;
	char					*text_pix;
	unsigned int			color;
	double					coo_y;
	double					coo_x;
	int						case_y;
	int						case_x;
	bool					use;
	bool					print;
	double					dist;
	double					size;
	double					max_size;
	double					htop;
	double					hbot;
	int						dir;
	t_coo					texture_coo;
	double					ry;
	double					rx;
	double					end_y;
	double					end_x;
	double					start_y;
	double					start_x;
	double					posx;
};

struct						s_pause_menu
{
	// int		pix_y;
	// char	*img_addr;
	// char	*data_addr;
	t_img					*sensitivity;
	t_img					*background;
	t_img					*exit;
	t_img					*resume;
	t_img					*selector;
	int						selected;
	long long int			elapsed;
	long long int			time;
};

struct						s_spell_menu
{
	t_img					*background;
	int						selected;
	int						name_pos_y;
	long long int			end_time;
	long long int			start_time;
};

struct						s_ray
{
	double					d_proj;
	double					deg;
	double					coo_y;
	double					coo_x;
	int						case_y;
	int						case_x;
	double					rad;
	double					delta_x;
	double					delta_y;
	double					rx;
	double					ry;
	double					dist_wall;
	double					size_wall;
	int						pix_y;
	int						pix_x;
	char					*pixel_addr;
	int						dir;
	char					*img_addr;
	double					max_height;
	double					max_size_wall;
	double					htop_wall;
	double					hbot_wall;
	char					*data_addr;
	int						calc_bits;
	double					save_x;
	t_coo					texture_coo;
	t_img					*img;
	t_hit_door				**doors;
	t_hit_enemy				**enemys;
	t_hit_item				**items;
	double					max_dist_wall;
	double					start_case_x;
	double					start_case_y;
	double					start_coo_x;
	double					start_coo_y;
};

struct						s_coo_mini
{
	double					x;
	double					y;
};

struct						s_img
{
	void					*mlx;
	char					*path;
	char					*data_addr;
	void					*img;
	int						width;
	int						height;
	int						bits_per_pixel;
	int						size_line;
	int						endian;
};

struct						s_color
{
	int						r;
	int						g;
	int						b;
};

struct						s_mlx
{
	void					*mlx;
	void					*win;
	int						height;
	int						width;
};

struct						s_utils_mini
{
	int						new_y;
	int						new_x;
	int						y;
	int						x;
	t_coo					s;
	t_coo					i;
	int						size;
	char					*pixel_addr;
	unsigned int			color;
	t_img					mmap;
	double					cos_val;
	double					sin_val;
	double					xdest;
	double					ydest;
	double					xfloat;
	double					yfloat;
	int						start_y;
	int						start_x;
};

struct						s_foot
{
	t_fcoo					coo;
	bool					is_left;
	bool					is_save;
	int						foot_x;
	int						foot_y;
	double					rad;
};

struct						s_mini
{
	int						need_print[SIZE_MAP][SIZE_MAP];
	t_foot					foot_tab[9];
	t_img					img[14];
	int						last_foot;
	long long int			time_foot;
	int						height;
	int						width;
	double					deg;
	double					rad;
	double					speed;
	double					sdy;
	double					sdx;
	double					dy;
	double					dx;
	double					ny;
	double					nx;
	int						cy;
	int						cx;
};

struct						s_map
{
	int						fd;
	int						tabmap_height;
	int						nb_floo;
	char					**tabmap;
	int						zoom;
	double					last_pos_x;
	double					last_pos_y;
	bool					is_center;
	bool					floo_active;
	int						last_mouse_x;
	int						last_mouse_y;
	t_coo					*pos_active_floo;
	t_door					***door_map;
	t_wall_msg				***wall_map;
	t_img					**msg_img;
	t_lst					*lines;
	t_lst					*map;
	t_img					*north;
	t_img					*south;
	t_img					*west;
	t_img					*east;
	t_img					*door;
	t_img					*fixed_door;
	t_mini					mini;
	t_img					*floor;
	t_img					*ceiling;
	t_img					*dementor_front;
	t_img					*dementor_back;
};

struct						s_display
{
	char					*pixel_addr;
	double					cos_angle;
	double					sin_angle;
	int						screen_bbp_frac;
	int						text_bpp_frac;
	double					dist_center;
	double					screen_y;
	double					dist_texture;
	double					screen_x;
	double					world_x;
	double					world_y;
	double					pos_cellx;
	double					pos_celly;
	int						text_x;
	int						text_y;
	char					*texture_pixel;
	unsigned int			color;
	int						player_height;
	int						pos_x_hand;
	int						pos_y_hand;
	int						move_hand;
	bool					is_up_move_hand;
	unsigned long long		elapsed_time;
	bool					is_msg_active;
	bool					is_first_msg;
	unsigned long long		time_remove;
};

struct						s_lumos
{
	// t_img	*img;
	int						x_wand;
	int						y_wand;
	bool					active;
	int						count_frame;
};

struct						s_coa
{
	unsigned int			color;
	char					*name;
	t_img					*img_coa;
	t_img					*border;
	double					xp;
	double					max_y;
};

struct						s_hitray
{
	int						i;
	int						j;
	int						deg;
	bool					hit;
	double					radius;
	double					delta;
	double					delta_t;
	double					delta_u;
	double					t;
	double					u;
	double					ax;
	double					ay;
	double					bx;
	double					by;
	double					cx;
	double					cy;
	double					dx;
	double					dy;
	double					hx;
	double					hy;
	double					rx;
	double					ry;
	double					delta_x;
	double					delta_y;
	int						type;
	t_data					*data;
};

struct						s_case
{
	t_case					*parent;
	t_case					*child;
	t_fcoo					coo;
	int						r_cost;
	int						h_cost;
	int						t_cost;
	int						is_path;
};

struct						s_spell
{
	t_img					*icn;
	t_img					*icn_name;
	t_damage				damage;
	t_item					item;
	int						type;
	double					necessary_lvl;
	double					base_cooldown;
	double					base_timer;
	long long int			launch_time;
	long long int			end_time;
	void					(*call)(t_data *data, int info);
	t_enum_class_spell		class;
};

struct						s_player
{
	double					life;
	double					shield;
	double					xp;
	t_damage				damage;
	t_fcoo					coo;
	t_fcoo					left;
	t_fcoo					right;
	t_fcoo					left_before;
	t_fcoo					right_before;
	t_coo					save;
	double					radius;
	int						protego;
	double					episkey_frame;
	double					episkey_heal;
	double					vul_sanen_frame;
	double					vul_sanen_heal;
	bool					is_front;
	int						invisible;
	long long int			timer_invi;
	long long int			timer_invi_short;
	int						coa;
	unsigned int			color;
};

struct						s_wand
{
	int						nb_wand;
	int						count_egg;
	char					*secret_wand;
	bool					wand_status[7];
	bool					is_drop[7];
	char					*secret_sword;
	int						count_sword;
};

struct						s_popo
{
	void					(*call)(t_data *data);
	t_img					*img;
	int						nb;
	char					*key;
	int						active;
};

struct						s_cooldown
{
	long long				spell;
	long long				incendio;
	long long				aguamenti;
	long long				expecto_patronum;
	long long				arania_exumai;
	long long				stupefix;
	long long				tig;
	long long				bh;
};

struct						s_sorcerer
{
	bool					is_alive;
	char					type;
	int						nb_spawn;
	unsigned int			color;
	t_damage				damage;
	t_cooldown				cooldown;
};

struct						s_sound
{
	int						pid;
	long long int			start;
	long long int			duration;
};

struct						s_aff
{
	unsigned int			color;
	t_img					img;
	t_coo					new;
	t_coo					cur;
	unsigned int			a;
	unsigned int			b;
	int						a_new;
	int						r_new;
	int						g_new;
	int						b_new;
	int						r_old;
	int						g_old;
	int						b_old;
	unsigned int			old_color;
};

struct						s_data
{
	t_img					img[NB_TEXTURES];
	t_utils_mini			u;
	t_img					*screen;
	long long int			time_fps;
	long long int			time_move;
	int						frame_move;
	int						ac;
	char					**av;
	int						status;
	int						nb_coalition;
	t_map					map;
	t_mlx					mlx;
	t_ray					*ray;
	t_display				display;
	t_aff					aff;
	t_lumos					lumos;
	int						keycode[100];
	pthread_mutex_t			m_data_ray;
	pthread_t				thread_wall;
	pthread_t				thread_sky_first;
	pthread_t				thread_sky_snd;
	pthread_t				thread_sky_third;
	pthread_t				thread_sky_last;
	pthread_t				thread_floor_first;
	pthread_t				thread_floor_snd;
	pthread_t				thread_floor_third;
	pthread_t				thread_floor_last;
	pthread_t				thread_ray_first;
	pthread_t				thread_ray_snd;
	pthread_t				thread_ray_third;
	pthread_t				thread_ray_last;
	pthread_t				thread_fst_part;
	pthread_t				thread_snd_part;
	pthread_t				thread_third_part;
	pthread_t				thread_last_part;
	pthread_barrier_t		barrier_background;
	pthread_barrier_t		barrier_display;
	t_coa					coa[4];
	unsigned int			color;
	int						selected;
	// t_img			*select;
	// t_img			*select_hand;
	// t_img			*player_hand;
	// t_img			*player_wand;
	// t_img			*left_select;
	bool					is_right_handed;
	int						nb_door;
	t_door					**doors;
	bool					player_moved;
	int						current_msg;
	int						nb_msg;
	int						random_value;
	t_pause_menu			pause_menu;
	t_spell_menu			spell_menu;
	double					sensitivity;
	// t_img	*wh;
	// t_img	*bl;
	int						nb_enemy;
	int						nb_create_enemy;
	double					spider_factor;
	double					elem_factor;
	double					dementor_factor;
	double					wolf_factor;
	t_player				player;
	t_spell					spell[NB_SPELL];
	t_item					items[NB_TYPE_ITEM];
	int						spell_take[4];
	int						cast_spell;
	int						active_spell;
	t_lst					*enemy;
	t_lst					*item;
	t_lst					*door;
	int						frame_floo;
	long long int			spawn_frame;
	long long int			last_spawn;
	t_wand					wand;
	char					*cheat_code_xp;
	char					*cheat_code_life;
	int						index_life;
	int						index_xp;
	bool					portkey_is_active;
	t_popo					popo[4];
	t_sorcerer				sorcerer[NB_SORCERER + 1];
	t_lst					*sound;
	int						count_frame;
};

t_coo						*init_t_coo(int y, int x);

#endif
