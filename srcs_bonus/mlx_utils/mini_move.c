#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>

#include <stdio.h>

static int	check_x_value(t_mini *mini, int y, int x)
{
	if ((y == -1 && x == -1 && mini->player_coo.y < 8 && mini->player_coo.x + mini->dx < 8)
	|| (y == 0 && x == -1 && mini->player_coo.x + mini->dx < 8)
	|| (y == 1 && x == -1 && mini->player_coo.x + mini->dx < 8 && mini->player_coo.y > 56)
	|| (y == -1 && x == 0 && mini->player_coo.y < 8)
	|| (y == 1 && x == 0 && mini->player_coo.y > 56)
	|| (y == -1 && x == 1 && mini->player_coo.y < 8 && mini->player_coo.x + mini->dx > 56)
	|| (y == 0 && x == 1 && mini->player_coo.x + mini->dx > 56)
	|| (y == 1 && x == 1 && mini->player_coo.x + mini->dx > 56 && mini->player_coo.y > 56))
		return (1);
	return (0);
}

static int	check_y_value(t_mini *mini, int y, int x)
{
	if ((y == -1 && x == -1 && mini->player_coo.y + mini->dy < 8 && mini->player_coo.x < 8)
	|| (y == 0 && x == -1 && mini->player_coo.x < 8)
	|| (y == 1 && x == -1 && mini->player_coo.x < 8 && mini->player_coo.y + mini->dy > 56)
	|| (y == -1 && x == 0 && mini->player_coo.y + mini->dy < 8)
	|| (y == 1 && x == 0 && mini->player_coo.y + mini->dy > 56)
	|| (y == -1 && x == 1 && mini->player_coo.y + mini->dy < 8 && mini->player_coo.x > 56)
	|| (y == 0 && x == 1 && mini->player_coo.x > 56)
	|| (y == 1 && x == 1 && mini->player_coo.x > 56 && mini->player_coo.y + mini->dy > 56))
		return (1);
	return (0);
}

int	hit_box_x_wall(t_map *map, t_mini *mini)
{
	int	x;
	int	y;
	
	y = -1;
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			if (map->tabmap[map->player_coo->y + y][map->player_coo->x + x] == '1')
				if (check_x_value(mini, y, x))
					return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	hit_box_y_wall(t_map *map, t_mini *mini)
{
	int	x;
	int	y;
	
	y = -1;
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			if (map->tabmap[map->player_coo->y + y][map->player_coo->x + x] == '1')
				if (check_y_value(mini, y, x))
					return (1);
			x++;
		}
		y++;
	}
	return (0);
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
	(void)data;

	angle = 0;
	if (keycode == KEY_W || keycode == KEY_UP)
		angle = 180;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		angle = 0;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		angle = 90;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		angle = 270;
	mini->dx += sin(mini->rad + angle * (M_PI / 180.0));
	mini->dy += cos(mini->rad + angle * (M_PI / 180.0));
}

void	recalc_x(t_mini *mini, t_map *map)
{
	mini->nx = mini->player_coo.x + mini->dx;
	mini->cx = 0;
	if (mini->nx < 0)
	{
		if (map->tabmap[map->player_coo->y][map->player_coo->x - 1] != '1')
		{
			mini->cx = -1;
			mini->nx = 64 + mini->nx;
		}
	}
	else if (mini->nx >= 64)
	{
		if (map->tabmap[map->player_coo->y][map->player_coo->x + 1] != '1')
		{
			mini->cx = 1;
			mini->nx = mini->nx - 64;
		}
	}
}

void	recalc_y(t_mini *mini, t_map *map)
{
	mini->ny = mini->player_coo.y + mini->dy;
	mini->cy = 0;
	if (mini->ny < 0)
	{
		if (map->tabmap[map->player_coo->y - 1][map->player_coo->x] != '1')
		{
			mini->cy = -1;
			mini->ny = 64 + mini->ny;
		}
	}
	else if (mini->ny >= 64)
	{
		if (map->tabmap[map->player_coo->y + 1][map->player_coo->x] != '1')
		{
			mini->cy = 1;
			mini->ny = mini->ny - 64;
		}
	}
}

void	movex(t_map *map, t_mini *mini, t_data *data)
{
	if (hit_box_x_wall(map, mini))
	{
		// printf("STOP HIT X\n");
		mini->nx = mini->player_coo.x;
	}
	if (data->map.tabmap[map->player_coo->y][map->player_coo->x] == 'D'
		&& data->map.door_map[map->player_coo->y][map->player_coo->x]->is_verti == true)
		{
			if ((mini->cx == 0 && mini->nx >= 22 && mini->nx <= 42)
			|| (mini->cx == 0 && mini->nx > 32 && mini->player_coo.x < 32) || (mini->cx == 0 && mini->nx < 32 && mini->player_coo.x > 32))
			{
				// printf("HIT DOOOR   xold=%lf    x=%lf\n",mini->player_coo.x, mini->nx);
				if (data->map.door_map[map->player_coo->y][map->player_coo->x]->pos <= 50 && abs_value(32 - mini->player_coo.x) > abs_value(32 - mini->nx))
					mini->nx = mini->player_coo.x;
				else if (mini->ny < 16 || mini->ny > 48)
					mini->ny = mini->player_coo.y;
				// printf("NOT EXIT\n");
			}
		}
	// printf("xold=%lf    x=%lf\n",mini->player_coo.x, mini->nx);
}


void	movey(t_map *map, t_mini *mini, t_data *data)
{

	if (hit_box_y_wall(map, mini))
	{
		// printf("STOP HIT Y\n");
		mini->ny = mini->player_coo.y;
	}
	if (data->map.tabmap[map->player_coo->y][map->player_coo->x] == 'D'
		&& data->map.door_map[map->player_coo->y][map->player_coo->x]->is_verti == false)
		{
			if ((mini->cy == 0 && mini->ny >= 22 && mini->ny <= 42)
			|| (mini->cy == 0 && mini->ny > 32 && mini->player_coo.y < 32) || (mini->cy == 0 && mini->ny < 32 && mini->player_coo.y > 32))
			{
				// printf("HIT DOOOR   yold=%lf    y=%lf\n",mini->player_coo.y, mini->ny);
				if (data->map.door_map[map->player_coo->y][map->player_coo->x]->pos <= 50 && abs_value(32 - mini->player_coo.y) > abs_value(32 - mini->ny))
					mini->ny = mini->player_coo.y;
				else if (mini->nx < 16 || mini->nx > 48)
					mini->nx = mini->player_coo.x;
				// printf("NOT EXIT\n");
			}
		}
	// printf(" yold=%lf    y=%lf\n",mini->player_coo.y, mini->ny);
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
	mini->dx *= SPEED;
	mini->dy *= SPEED;
	recalc_x(mini, map);
	recalc_y(mini, map);
	movex(map, mini, data);
	movey(map, mini, data);
	if (mini->ny != mini->player_coo.y)
	{
		mini->player_coo.y = mini->ny;
		map->player_coo->y += mini->cy;
	}
	if (mini->nx != mini->player_coo.x)
	{
		mini->player_coo.x = mini->nx;
		map->player_coo->x += mini->cx;
	}
	// move_x(data, map, mini);
	// move_y(data, map, mini);
}
