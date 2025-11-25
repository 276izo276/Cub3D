#include "cub3d_bonus.h"
#include "struct_bonus.h"
#include "time_bonus.h"
#include <math.h>
#include <stdlib.h>
#include <strings.h>

void	init_folder(t_data *data)
{
	data->items[FOLDER].categ = ITEM;
	data->items[FOLDER].type = FOLDER;
	data->items[FOLDER].damage.damage_do = 25;
	data->items[FOLDER].damage.curse_force_do = .1;
	data->items[FOLDER].damage.curse_frame_do = 120;
	data->items[FOLDER].damage.slow_force_do = 70;
	data->items[FOLDER].damage.slow_frame_do = 120;
	data->items[FOLDER].damage.repulso_force_do = 2;
	data->items[FOLDER].damage.repulso_frame_do = 5;
	data->items[FOLDER].speed = 0;
	data->items[FOLDER].radius = 3;
	data->items[FOLDER].front_img = &data->img[FOLDER_IMG];
	data->items[FOLDER].back_img = &data->img[FOLDER_IMG];
}

void	init_marvin(t_data *data)
{
	data->items[MARVIN].categ = ITEM;
	data->items[MARVIN].type = MARVIN;
	data->items[MARVIN].damage.damage_do = 25;
	data->items[MARVIN].damage.curse_force_do = .1;
	data->items[MARVIN].damage.curse_frame_do = 120;
	data->items[MARVIN].damage.slow_force_do = 70;
	data->items[MARVIN].damage.slow_frame_do = 120;
	data->items[MARVIN].damage.repulso_force_do = 2;
	data->items[MARVIN].damage.repulso_frame_do = 5;
	data->items[MARVIN].speed = 10;
	data->items[MARVIN].radius = 3;
	data->items[MARVIN].front_img = &data->img[MARVIN_IMG];
	data->items[MARVIN].back_img = &data->img[MARVIN_IMG];
}

void	init_taylor_swift(t_data *data)
{
	data->items[TAYLOR_SWIFT].categ = ITEM;
	data->items[TAYLOR_SWIFT].type = TAYLOR_SWIFT;
	data->items[TAYLOR_SWIFT].damage.damage_do = 25;
	data->items[TAYLOR_SWIFT].damage.curse_force_do = .1;
	data->items[TAYLOR_SWIFT].damage.curse_frame_do = 120;
	data->items[TAYLOR_SWIFT].damage.slow_force_do = 70;
	data->items[TAYLOR_SWIFT].damage.slow_frame_do = 120;
	data->items[TAYLOR_SWIFT].damage.repulso_force_do = 2;
	data->items[TAYLOR_SWIFT].damage.repulso_frame_do = 5;
	data->items[TAYLOR_SWIFT].speed = 10;
	data->items[TAYLOR_SWIFT].radius = 5;
	data->items[TAYLOR_SWIFT].front_img = &data->img[TAYLOR_SWIFT_IMG];
	data->items[TAYLOR_SWIFT].back_img = &data->img[TAYLOR_SWIFT_IMG];
}

void	init_company(t_data *data)
{
	data->items[COMPANY].categ = ITEM;
	data->items[COMPANY].type = COMPANY;
	data->items[COMPANY].damage.damage_do = 25;
	data->items[COMPANY].damage.curse_force_do = .1;
	data->items[COMPANY].damage.curse_frame_do = 120;
	data->items[COMPANY].damage.slow_force_do = 70;
	data->items[COMPANY].damage.slow_frame_do = 120;
	data->items[COMPANY].damage.repulso_force_do = 2;
	data->items[COMPANY].damage.repulso_frame_do = 5;
	data->items[COMPANY].speed = 10;
	data->items[COMPANY].radius = 5;
	data->items[COMPANY].front_img = &data->img[COMPANY_IMG];
	data->items[COMPANY].back_img = &data->img[COMPANY_IMG];
}

void	init_logo_42(t_data *data)
{
	data->items[LOGO_42].categ = ITEM;
	data->items[LOGO_42].type = LOGO_42;
	data->items[LOGO_42].damage.damage_do = 25;
	data->items[LOGO_42].damage.curse_force_do = .1;
	data->items[LOGO_42].damage.curse_frame_do = 120;
	data->items[LOGO_42].damage.slow_force_do = 70;
	data->items[LOGO_42].damage.slow_frame_do = 120;
	data->items[LOGO_42].damage.repulso_force_do = 2;
	data->items[LOGO_42].damage.repulso_frame_do = 5;
	data->items[LOGO_42].speed = 10;
	data->items[LOGO_42].radius = 5;
	data->items[LOGO_42].front_img = &data->img[LOGO_42_IMG];
	data->items[LOGO_42].back_img = &data->img[LOGO_42_IMG];
}
