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
# define COLLECT_WAND_MP3 "sound/collect_wand.mp3"
# define POPO_MP3 "sound/popo.mp3"
# define FREEDOM_MP3 "sound/freedom.mp3"
# define FLOO_MP3 "sound/floo.mp3"
# define HEART_MP3 "sound/heart.mp3"
# define LVL_UP	"sound/lvl_up.mp3"
# define WALL_MP3 "sound/wall_msg.mp3"

# define SIZE_MAP 320
# define FPS 30.0
# define V_FOV 90.0
# define H_FOV 90.0
# define FPM 30.0
# define MENU 0
# define GAME 1
# define PAUSE 2
# define FLOO_MAP 3
# define MAP 4
# define MENU_SPELL 5
# define MENU_DEATH 6
# define MENU_END 7
# define SPEED 2.5
# define KEYCODE_NB 100
# define MAX_CREATE_ENEMY 50
# define MAX_CREATE_ITEM 100
# define ITEM 1
# define ENEMY 2
# define DOOR 3

typedef struct s_wand			t_wand;
typedef struct s_wall_msg		t_wall_msg;
typedef struct s_utils_mini		t_utils_mini;
typedef struct s_spell_menu		t_spell_menu;
typedef struct s_spell			t_spell;
typedef struct s_sound			t_sound;
typedef struct s_sorcerer		t_sorcerer;
typedef struct s_ray			t_ray;
typedef struct s_popo			t_popo;
typedef struct s_player			t_player;
typedef struct s_pause_menu		t_pause_menu;
typedef struct s_mv_enemy		t_mv_enemy;
typedef struct s_mlx			t_mlx;
typedef struct s_mini			t_mini;
typedef struct s_map			t_map;
typedef struct s_lumos			t_lumos;
typedef struct s_item			t_item;
typedef struct s_img			t_img;
typedef struct s_hitray			t_hitray;
typedef struct s_hit_item		t_hit_item;
typedef struct s_hit_enemy		t_hit_enemy;
typedef struct s_hit_door		t_hit_door;
typedef struct s_foot			t_foot;
typedef struct s_fcoo			t_fcoo;
typedef struct s_enemy_vision	t_enemy_vision;
typedef struct s_enemy			t_enemy;
typedef struct s_door			t_door;
typedef struct s_display		t_display;
typedef struct s_data			t_data;
typedef struct s_damage			t_damage;
typedef struct s_cooldown		t_cooldown;
typedef struct s_coo_mini		t_coo_mini;
typedef struct s_coo			t_coo;
typedef struct s_color			t_color;
typedef struct s_coa			t_coa;
typedef struct s_case			t_case;
typedef struct s_aff			t_aff;

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
	int						case_y;
	int						case_x;
	double					coo_y;
	double					coo_x;
};

struct						s_wall_msg
{
	t_coo					texture_coo;
	t_coo					coo;
	int						pix_y;
	int						msg_nb;
	int						dir;
	char					*img_addr;
	bool					is_active;
};

struct						s_damage
{
	t_fcoo					hit;
	int						which_coa_take;
	int						which_coa_do;
	double					slow_frame_take;
	double					slow_frame_do;
	double					slow_force_take;
	double					slow_force_do;
	double					repulso_frame_take;
	double					repulso_frame_do;
	double					repulso_force_take;
	double					repulso_force_do;
	double					poison_frame_take;
	double					poison_frame_do;
	double					poison_force_take;
	double					poison_force_do;
	double					fire_frame_take;
	double					fire_frame_do;
	double					fire_force_take;
	double					fire_force_do;
	double					dist;
	double					damage_take;
	double					damage_spider_take;
	double					damage_spider_do;
	double					damage_snake_take;
	double					damage_snake_do;
	double					damage_elem_take;
	double					damage_elem_do;
	double					damage_do;
	double					damage_dementor_take;
	double					damage_dementor_do;
	double					curse_frame_take;
	double					curse_frame_do;
	double					curse_force_take;
	double					curse_force_do;
	double					confundo_frame_take;
	double					confundo_frame_do;
	double					confundo_force_take;
	double					confundo_force_do;

};

struct						s_enemy
{
	unsigned int			color_coa;
	t_img					*side_img;
	t_img					*side_front_img;
	t_img					*side_back_img;
	t_img					*front_img;
	t_img					*back_img;
	t_fcoo					right;
	t_fcoo					right_before;
	t_fcoo					left;
	t_fcoo					left_before;
	t_fcoo					goal;
	t_fcoo					center;
	t_fcoo					center_before;
	t_enemy_info			type;
	t_damage				damage;
	t_case					*way;
	long long int			time_attack_dist;
	long long int			time_attack_cac;
	int						wait;
	int						recalc_path;
	int						nb_move;
	int						drop_wolf_wand;
	int						drop_spider_wand;
	int						drop_shield;
	int						drop_heal;
	int						drop_floo;
	int						drop_elem_wand;
	int						drop_dementor_wand;
	int						drop_cloak;
	int						dist_visu;
	int						dist_stop;
	int						dist_damage;
	int						cooldown_dist;
	int						calc_path;
	double					speed;
	double					radius;
	double					rad;
	double					life;
	double					dist_target;
	double					deg;
	double					cooldown_cac;
	double					aff_rad;
	double					aff_deg;
	bool					calc;
};

struct						s_item
{
	unsigned int			nb_move;
	t_img					*front_img;
	t_img					*back_img;
	t_fcoo					right;
	t_fcoo					right_before;
	t_fcoo					left;
	t_fcoo					left_before;
	t_fcoo					center;
	t_fcoo					center_before;
	t_damage				damage;
	int						type;
	int						coa;
	int						categ;
	double					speed;
	double					radius;
	double					rad;
	double					deg;
	double					deg_rotate;
};

struct						s_door
{
	t_coo					second_p;
	t_coo					first_p;
	t_coo					coo;
	double					pos;
	bool					is_verti;
	bool					is_open;
	bool					is_floo;
	bool					is_floo_open;
};

struct						s_hit_door
{
	t_door					*door;
	t_coo					texture_coo;
	int						dir;
	int						case_y;
	int						case_x;
	double					start_y;
	double					start_x;
	double					size_door;
	double					ry;
	double					rx;
	double					max_size_door;
	double					htop_door;
	double					hbot_door;
	double					end_y;
	double					end_x;
	double					dist_door;
	double					coo_y;
	double					coo_x;
	bool					use;
	bool					print;
	bool					is_floo;
};

struct						s_hit_enemy
{
	t_enemy					*enemy;
	t_coo					texture_coo;
	int						dir;
	int						case_y;
	int						case_x;
	double					start_y;
	double					start_x;
	double					size_enemy;
	double					ry;
	double					rx;
	double					posx;
	double					max_size_enemy;
	double					htop_enemy;
	double					hbot_enemy;
	double					end_y;
	double					end_x;
	double					dist_enemy;
	double					coo_y;
	double					coo_x;
	bool					use;
	bool					print;
};

struct						s_hit_item
{
	unsigned int			color;
	t_item					*item;
	t_img					*texture;
	t_enemy					*enemy;
	t_door					*door;
	t_coo					texture_coo;
	int						type;
	int						status;
	int						side;
	int						dist_height;
	int						dir;
	int						categ;
	int						case_y;
	int						case_x;
	double					start_y;
	double					start_x;
	double					size;
	double					ry;
	double					rx;
	double					posx;
	double					max_size;
	double					htop;
	double					hbot;
	double					end_y;
	double					end_x;
	double					door_status;
	double					dist;
	double					coo_y;
	double					coo_x;
	char					*text_pix;
	char					*pixel_addr;
	bool					use;
	bool					print;
};

struct						s_pause_menu
{
	t_img					*sensitivity;
	t_img					*selector;
	t_img					*resume;
	t_img					*exit;
	t_img					*background;
	long long int			time;
	long long int			elapsed;
	int						selected;
};

struct						s_spell_menu
{
	t_img					*background;
	long long int			start_time;
	long long int			end_time;
	int						selected;
	int						name_pos_y;
};

struct						s_ray
{
	t_img					*img;
	t_hit_item				**items;
	t_hit_enemy				**enemys;
	t_hit_door				**doors;
	t_coo					texture_coo;
	int						pix_y;
	int						pix_x;
	int						dir;
	int						case_y;
	int						case_x;
	int						calc_bits;
	double					start_coo_y;
	double					start_coo_x;
	double					start_case_y;
	double					start_case_x;
	double					size_wall;
	double					save_x;
	double					ry;
	double					rx;
	double					rad;
	double					max_size_wall;
	double					max_height;
	double					max_dist_wall;
	double					htop_wall;
	double					hbot_wall;
	double					dist_wall;
	double					delta_y;
	double					delta_x;
	double					deg;
	double					d_proj;
	double					coo_y;
	double					coo_x;
	char					*pixel_addr;
	char					*img_addr;
	char					*data_addr;
};

struct						s_coo_mini
{
	double					x;
	double					y;
};

struct						s_img
{
	void					*mlx;
	void					*img;
	int						width;
	int						size_line;
	int						height;
	int						endian;
	int						bits_per_pixel;
	char					*path;
	char					*data_addr;
};

struct						s_color
{
	int						r;
	int						g;
	int						b;
};

struct						s_mlx
{
	void					*win;
	void					*mlx;
	int						width;
	int						height;
};

struct						s_utils_mini
{
	unsigned int			color;
	t_img					mmap;
	t_coo					s;
	t_coo					i;
	int						y;
	int						x;
	int						start_y;
	int						start_x;
	int						size;
	int						new_y;
	int						new_x;
	double					yfloat;
	double					ydest;
	double					xfloat;
	double					xdest;
	double					sin_val;
	double					cos_val;
	char					*pixel_addr;
};

struct						s_foot
{
	t_fcoo					coo;
	int						foot_y;
	int						foot_x;
	double					rad;
	bool					is_save;
	bool					is_left;
};

struct						s_mini
{
	t_img					img[14];
	t_foot					foot_tab[9];
	long long int			time_foot;
	int						width;
	int						need_print[SIZE_MAP][SIZE_MAP];
	int						last_foot;
	int						height;
	int						cy;
	int						cx;
	double					speed;
	double					sdy;
	double					sdx;
	double					rad;
	double					ny;
	double					nx;
	double					dy;
	double					dx;
	double					deg;
};

struct						s_map
{
	t_wall_msg				***wall_map;
	t_mini					mini;
	t_lst					*map;
	t_lst					*lines;
	t_img					*west;
	t_img					*south;
	t_img					*north;
	t_img					*floor;
	t_img					*fixed_door;
	t_img					*east;
	t_img					*door;
	t_img					*dementor_front;
	t_img					*dementor_back;
	t_img					*ceiling;
	t_img					**msg_img;
	t_door					***door_map;
	t_coo					pos_active_floo;
	int						zoom;
	int						tabmap_height;
	int						nb_floo;
	int						last_mouse_y;
	int						last_mouse_x;
	int						fd;
	double					last_pos_y;
	double					last_pos_x;
	char					**tabmap;
	bool					is_center;
	bool					floo_active;
};

struct						s_display
{
	unsigned long long		time_remove;
	unsigned long long		elapsed_time;
	unsigned int			color;
	int						text_y;
	int						text_x;
	int						text_bpp_frac;
	int						screen_bbp_frac;
	int						pos_y_hand;
	int						pos_x_hand;
	int						player_height;
	int						move_hand;
	double					world_y;
	double					world_x;
	double					sin_angle;
	double					screen_y;
	double					screen_x;
	double					pos_celly;
	double					pos_cellx;
	double					dist_texture;
	double					dist_center;
	double					cos_angle;
	char					*texture_pixel;
	char					*pixel_addr;
	bool					is_up_move_hand;
	bool					is_msg_active;
	bool					is_first_msg;
};

struct						s_lumos
{
	int						y_wand;
	int						x_wand;
	int						count_frame;
	bool					active;
};

struct						s_coa
{
	unsigned int			color;
	t_img					*img_coa;
	t_img					*border;
	double					xp;
	double					max_y;
	char					*name;
};

struct						s_hitray
{
	t_data					*data;
	int						type;
	int						j;
	int						i;
	int						deg;
	double					u;
	double					t;
	double					ry;
	double					rx;
	double					radius;
	double					hy;
	double					hx;
	double					dy;
	double					dx;
	double					delta;
	double					delta_y;
	double					delta_x;
	double					delta_u;
	double					delta_t;
	double					cy;
	double					cx;
	double					by;
	double					bx;
	double					ay;
	double					ax;
	bool					hit;
};

struct						s_case
{
	t_fcoo					coo;
	t_case					*parent;
	t_case					*child;
	int						t_cost;
	int						r_cost;
	int						is_path;
	int						h_cost;
};

struct						s_spell
{
	void					(*call)(t_data *data, int info);
	t_item					item;
	t_img					*icn;
	t_img					*icn_name;
	t_enum_class_spell		class;
	t_damage				damage;
	long long int			launch_time;
	long long int			end_time;
	int						type;
	double					necessary_lvl;
	double					base_timer;
	double					base_cooldown;
};

struct						s_player
{
	unsigned int			color;
	t_fcoo					right;
	t_fcoo					right_before;
	t_fcoo					left;
	t_fcoo					left_before;
	t_fcoo					coo;
	t_damage				damage;
	t_coo					save;
	long long int			timer_invi;
	long long int			timer_invi_short;
	int						protego;
	int						invisible;
	int						coa;
	double					xp;
	double					vul_sanen_heal;
	double					vul_sanen_frame;
	double					shield;
	double					radius;
	double					life;
	double					episkey_heal;
	double					episkey_frame;
	bool					is_front;
};

struct						s_wand
{
	int						nb_wand;
	int						count_sword;
	int						count_egg;
	char					*secret_wand;
	char					*secret_sword;
	bool					wand_status[7];
	bool					is_drop[7];
};

struct						s_popo
{
	void					(*call)(t_data *data);
	t_img					*img;
	int						nb;
	int						active;
	char					*key;
};

struct						s_cooldown
{
	long long				tig;
	long long				stupefix;
	long long				spell;
	long long				incendio;
	long long				expecto_patronum;
	long long				bh;
	long long				arania_exumai;
	long long				aguamenti;
};

struct						s_sorcerer
{
	unsigned int			color;
	t_damage				damage;
	t_cooldown				cooldown;
	int						nb_spawn;
	char					type;
	bool					is_alive;
};

struct						s_sound
{
	long long int			start;
	long long int			duration;
	int						pid;
	int						id;
};

struct						s_aff
{
	unsigned int			old_color;
	unsigned int			color;
	unsigned int			b;
	unsigned int			a;
	t_img					img;
	t_coo					new;
	t_coo					cur;
	int						y;
	int						y_max;
	int						x;
	int						x_max;
	int						r_old;
	int						r_new;
	int						g_old;
	int						g_new;
	int						b_old;
	int						b_new;
	int						a_new;
	int						dist_heigh;
	double					ray;
	double					dy;
	double					dx;
	double					dist_y;
	double					dist_x;
	double					base_y;
	double					base_x;
	char					*tmp_addr;
};

struct						s_mv_enemy
{
	int						cy;
	int						cx;
	int						right_cy;
	int						right_cx;
	int						left_cy;
	int						left_cx;
	int						new_x;
	int						new_y;
	int						new_left_x;
	int						new_left_y;
	int						new_right_x;
	int						new_right_y;
};

struct						s_enemy_vision
{
	t_ray		ray;
	t_fcoo		coo;
	t_enemy		*keep_elem;
	int			type;
	double		rad;
	double		dist_min;
	double		dist_min_player;
	double		deg;
};

struct						s_data
{
	unsigned int			color;
	t_wand					wand;
	t_utils_mini			u;
	t_spell_menu			spell_menu;
	t_spell					spell[NB_SPELL];
	t_sorcerer				sorcerer[NB_SORCERER + 1];
	t_ray					*ray;
	t_popo					popo[4];
	t_player				player;
	t_pause_menu			pause_menu;
	t_mlx					mlx;
	t_map					map;
	t_lumos					lumos;
	t_lst					*sound;
	t_lst					*item;
	t_lst					*enemy;
	t_lst					*door;
	t_item					items[NB_TYPE_ITEM];
	t_img					img[NB_TEXTURES];
	t_img					*screen;
	t_display				display;
	t_coa					coa[4];
	t_aff					aff;
	pthread_t				thread_wall;
	pthread_t				thread_third_part;
	pthread_t				thread_snd_part;
	pthread_t				thread_sky_third;
	pthread_t				thread_sky_snd;
	pthread_t				thread_sky_last;
	pthread_t				thread_sky_first;
	pthread_t				thread_ray_third;
	pthread_t				thread_ray_snd;
	pthread_t				thread_ray_last;
	pthread_t				thread_ray_first;
	pthread_t				thread_last_part;
	pthread_t				thread_fst_part;
	pthread_t				thread_floor_third;
	pthread_t				thread_floor_snd;
	pthread_t				thread_floor_last;
	pthread_t				thread_floor_first;
	pthread_mutex_t			m_data_ray;
	pthread_mutex_t			m_end;
	pthread_barrier_t		barrier_display;
	pthread_barrier_t		barrier_background;
	long long int			time_move;
	long long int			time_fps;
	long long int			spawn_frame;
	long long int			last_spawn;
	long long int			sound_frame;
	int						status;
	int						spell_take[4];
	int						selected;
	int						random_value;
	int						nb_msg;
	int						nb_enemy;
	int						nb_door;
	int						nb_create_enemy;
	int						nb_coalition;
	int						keycode[100];
	int						index_xp;
	int						index_life;
	int						frame_move;
	int						frame_floo;
	int						current_msg;
	int						count_frame;
	int						cast_spell;
	int						active_spell;
	int						info;
	int						ac;
	double					wolf_factor;
	double					spider_factor;
	double					sensitivity;
	double					elem_factor;
	double					dementor_factor;
	char					*cheat_code_xp;
	char					*cheat_code_life;
	char					**av;
	bool					portkey_is_active;
	bool					player_moved;
	bool					is_right_handed;
	bool					god_mod;
	bool					should_end;
	bool					is_thread_create;
};

t_coo						*init_t_coo(int y, int x);

#endif
