#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>

static int	check_x_value(t_mini *mini, int y, int x)
{
	if ((y == -1 && x == -1 && mini->ny < 8 && mini->nx < 8)
	|| (y == 0 && x == -1 && mini->nx < 8)
	|| (y == 1 && x == -1 && mini->nx < 8 && mini->ny > 56)
	|| (y == -1 && x == 0 && mini->ny < 8)
	|| (y == 1 && x == 0 && mini->ny > 56)
	|| (y == -1 && x == 1 && mini->ny < 8 && mini->nx > 56)
	|| (y == 0 && x == 1 && mini->nx > 56)
	|| (y == 1 && x == 1 && mini->nx > 56 && mini->ny > 56))
		return (1);
	return (0);
}

static int	check_y_value(t_mini *mini, int y, int x)
{
	if ((y == -1 && x == -1 && mini->ny < 8 && mini->nx < 8)
	|| (y == 0 && x == -1 && mini->nx < 8)
	|| (y == 1 && x == -1 && mini->nx < 8 && mini->ny > 56)
	|| (y == -1 && x == 0 && mini->ny < 8)
	|| (y == 1 && x == 0 && mini->ny > 56)
	|| (y == -1 && x == 1 && mini->ny < 8 && mini->nx > 56)
	|| (y == 0 && x == 1 && mini->nx > 56)
	|| (y == 1 && x == 1 && mini->nx > 56 && mini->ny > 56))
		return (1);
	return (0);
}

int	hit_box_wall(t_map *map, t_mini *mini)
{
	int	x;
	int	y;
	
	y= -1;
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			if (map->tabmap[map->player_coo->y + y][map->player_coo->x + x] == '1')
			{
				// if (check_x_value(mini, y, x) && check_y_value(mini, y, x))
				// 	return (0);
				if (check_x_value(mini, y, x))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (5);
}

static void	move_x(t_data *data, t_map *map, t_mini *mini)
{
	if (hit_box_wall(map, mini) % 2 == 0)
		return ;
	if (mini->dx < 0)
	{
		if (map->tabmap[map->player_coo->y][map->player_coo->x - 1] == '1')
			return ;
		--map->player_coo->x;
		mini->player_coo.x = 64 + mini->dx;
	}
	else if (mini->dx >= 64)
	{
		if (map->tabmap[map->player_coo->y][map->player_coo->x + 1] == '1')
			return ;
		++map->player_coo->x;
		mini->player_coo.x = mini->dx - 64;
	}
	else
	{
		if (data->map.tabmap[map->player_coo->y][map->player_coo->x] == 'D'
			&& data->map.door_map[map->player_coo->y][map->player_coo->x]->is_verti == true
			&& data->map.door_map[map->player_coo->y][map->player_coo->x]->pos <= 50)
			{
				if ((mini->dx >= 22 && mini->dx <= 42 && abs_value(32 - mini->player_coo.y) > abs_value(32 - mini->dx))
				|| (mini->dx > 32 && mini->player_coo.y < 32) || (mini->dx < 32 && mini->player_coo.y > 32))
					return ;
			}
		mini->player_coo.x = mini->dx;
	}
}

static void	move_y(t_data *data, t_map *map, t_mini *mini)
{
	// mini->dy = mini->player_coo.y - mini->dy * SPEED;
	if (hit_box_wall(map, mini) % 3 == 0)
		return ;
	if (mini->dy < 0)
	{
		if (map->tabmap[map->player_coo->y - 1][map->player_coo->x] == '1')
			return ;
		--map->player_coo->y;
		mini->player_coo.y = 64 + mini->dy;
	}
	else if (mini->dy >= 64)
	{
		if (map->tabmap[map->player_coo->y + 1][map->player_coo->x] == '1')
			return ;
		++map->player_coo->y;
		mini->player_coo.y = mini->dy - 64;
	}
	else
	{
		if (data->map.tabmap[map->player_coo->y][map->player_coo->x] == 'D'
			&& data->map.door_map[map->player_coo->y][map->player_coo->x]->is_verti == false
			&& data->map.door_map[map->player_coo->y][map->player_coo->x]->pos <= 50)
			{
				if ((mini->dy >= 22 && mini->dy <= 42 && abs_value(32 - mini->player_coo.y) > abs_value(32 - mini->dy))
				|| (mini->dy > 32 && mini->player_coo.y < 32) || (mini->dy < 32 && mini->player_coo.y > 32))
					return ;
			}
		mini->player_coo.y = mini->dy;
	}
}

void	v_norm(t_mini *mini, t_data *data)
{
	double	v_normalize;
	int		i;

	v_normalize = sqrt(mini->dx * mini->dx + mini->dy * mini->dy);
	mini->dy = mini->dy / v_normalize;
	mini->dx = mini->dx / v_normalize;
	i = -1;
	while (++i < KEYCODE_NB)
	{
		if (data->keycode[i] == KEY_S)
		{
			mini->dy *= .6;
			mini->dx *= .6;
		}
		else if (data->keycode[i] == KEY_A || data->keycode[i] == KEY_D)
		{
			mini->dy *= .9;
			mini->dx *= .9;
		}
		if (data->keycode[i] == KEY_SHIFT)
		{
			mini->dy *= 1.6;
			mini->dx *= 1.6;
		}
	}
}

static void	calc_dx_dy(t_data *data, int keycode, t_mini *mini)
{
	int	angle;

	angle = 0;
	if (keycode == KEY_W)
		angle = 0;
	else if (keycode == KEY_S)
		angle = 180;
	else if (keycode == KEY_D)
		angle = 270;
	else if (keycode == KEY_A)
		angle = 90;
	mini->dx += sin(mini->rad + angle * (M_PI / 180.0))
		* (double)(FPM / data->frame_move);
	mini->dy += cos(mini->rad + angle * (M_PI / 180.0))
		* (double)(FPM / data->frame_move);
}

void	recalc_x(t_mini *mini, t_map *map)
{
	mini->dx = mini->player_coo.x - mini->dx * SPEED;
	mini->nx = mini->dx;
	mini->cx = 0;
	if (mini->dx < 0)
	{
		if (map->tabmap[map->player_coo->y][map->player_coo->x - 1] == '1')
		{
			mini->cx = -1;
			mini->nx = 64 + mini->dx;
		}
	}
	else if (mini->dx >= 64)
	{
		if (map->tabmap[map->player_coo->y][map->player_coo->x + 1] == '1')
		{
			mini->cx = 1;
			mini->nx = mini->dx - 64;
		}
	}
}

void	recalc_y(t_mini *mini, t_map *map)
{
	mini->dy = mini->player_coo.y - mini->dy * SPEED;
	mini->ny = mini->dy;
	mini->cy = 0;
	if (mini->dy < 0)
	{
		if (map->tabmap[map->player_coo->y - 1][map->player_coo->x] == '1')
		{
			mini->cy = -1;
			mini->ny = 64 + mini->dy;
		}
	}
	else if (mini->dy >= 64)
	{
		if (map->tabmap[map->player_coo->y + 1][map->player_coo->x] == '1')
		{
			mini->cy = 1;
			mini->ny = mini->dy - 64;
		}
	}
}

void	movex(t_map *map, t_mini *mini)
{
	if (hit_box_wall(map, mini))
}

void	handle_move(t_map *map, t_mini *mini, t_data *data)
{
	int	i;

	mini->dy = 0;
	mini->dx = 0;
	i = 0;
	while (i < KEYCODE_NB)
	{
		if (is_move_player(data, i))
		{
			calc_dx_dy(data, data->keycode[i], mini);
			data->player_moved = true;
		}
		i++;
	}
	if (round(mini->dy) == 0.0 && round(mini->dx) == 0.0)
	{
		mini->dy = 0;
		mini->dx = 0;
	}
	else
		v_norm(mini, data);
	recalc_x(mini, map);
	recalc_y(mini, map);
	movex();
	movey();
	// move_x(data, map, mini);
	// move_y(data, map, mini);
}
