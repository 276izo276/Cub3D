#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>
# include "texture_bonus.h"
#include <stdio.h>

static int	check_x_value(t_data *data, t_mini *mini, int y, int x)
{
	if ((y == -1 && x == -1 && data->player.coo.coo_y < 8 && data->player.coo.coo_x + mini->dx < 8)
	|| (y == 0 && x == -1 && data->player.coo.coo_x + mini->dx < 8)
	|| (y == 1 && x == -1 && data->player.coo.coo_x + mini->dx < 8 && data->player.coo.coo_y > 56)
	|| (y == -1 && x == 0 && data->player.coo.coo_y < 8)
	|| (y == 1 && x == 0 && data->player.coo.coo_y > 56)
	|| (y == -1 && x == 1 && data->player.coo.coo_y < 8 && data->player.coo.coo_x + mini->dx > 56)
	|| (y == 0 && x == 1 && data->player.coo.coo_x + mini->dx > 56)
	|| (y == 1 && x == 1 && data->player.coo.coo_x + mini->dx > 56 && data->player.coo.coo_y > 56))
		return (1);
	return (0);
}

static int	check_y_value(t_data *data, t_mini *mini, int y, int x)
{
	if ((y == -1 && x == -1 && data->player.coo.coo_y + mini->dy < 8 && data->player.coo.coo_x < 8)
	|| (y == 0 && x == -1 && data->player.coo.coo_x < 8)
	|| (y == 1 && x == -1 && data->player.coo.coo_x < 8 && data->player.coo.coo_y + mini->dy > 56)
	|| (y == -1 && x == 0 && data->player.coo.coo_y + mini->dy < 8)
	|| (y == 1 && x == 0 && data->player.coo.coo_y + mini->dy > 56)
	|| (y == -1 && x == 1 && data->player.coo.coo_y + mini->dy < 8 && data->player.coo.coo_x > 56)
	|| (y == 0 && x == 1 && data->player.coo.coo_x > 56)
	|| (y == 1 && x == 1 && data->player.coo.coo_x > 56 && data->player.coo.coo_y + mini->dy > 56))
		return (1);
	return (0);
}

int	hit_box_x_wall(t_data *data, t_map *map, t_mini *mini)
{
	int	x;
	int	y;

	y = -1;
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			if (map->tabmap[data->player.coo.case_y + y][data->player.coo.case_x + x] == '1')
				if (check_x_value(data, mini, y, x))
					return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	hit_box_y_wall(t_data *data, t_map *map, t_mini *mini)
{
	int	x;
	int	y;

	y = -1;
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			if (map->tabmap[data->player.coo.case_y + y][data->player.coo.case_x + x] == '1')
				if (check_y_value(data, mini, y, x))
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

void	recalc_x(t_data *data, t_mini *mini, t_map *map)
{
	mini->nx = data->player.coo.coo_x + mini->dx;
	mini->cx = 0;
	if (mini->nx < 0)
	{
		if (map->tabmap[data->player.coo.case_y][data->player.coo.case_x - 1] != '1')
		{
			mini->cx = -1;
			mini->nx = 64 + mini->nx;
		}
	}
	else if (mini->nx >= 64)
	{
		if (map->tabmap[data->player.coo.case_y][data->player.coo.case_x + 1] != '1')
		{
			mini->cx = 1;
			mini->nx = mini->nx - 64;
		}
	}
}

void	recalc_y(t_data *data, t_mini *mini, t_map *map)
{
	mini->ny = data->player.coo.coo_y + mini->dy;
	mini->cy = 0;
	if (mini->ny < 0)
	{
		if (map->tabmap[data->player.coo.case_y - 1][data->player.coo.case_x] != '1')
		{
			mini->cy = -1;
			mini->ny = 64 + mini->ny;
		}
	}
	else if (mini->ny >= 64)
	{
		if (map->tabmap[data->player.coo.case_y + 1][data->player.coo.case_x] != '1')
		{
			mini->cy = 1;
			mini->ny = mini->ny - 64;
		}
	}
}

void	hit_box_x_floo(t_mini *mini, t_data *data)
{
	if ((mini->cx == 0 && mini->nx >= 22 && mini->nx <= 42)
		|| (mini->cx == 0 && mini->nx > 32 && data->player.coo.coo_x < 32) || (mini->cx == 0 && mini->nx < 32 && data->player.coo.coo_x > 32))
		{
			if (data->map.door_map[data->player.coo.case_y][data->player.coo.case_x]->is_floo_open == false && abs_value(32 - data->player.coo.coo_x) > abs_value(32 - mini->nx))
				mini->nx = data->player.coo.coo_x;
			else if ((data->player.coo.coo_x < 22 || data->player.coo.coo_x > 42) && (mini->ny < 16 || mini->ny > 48))
				mini->nx = data->player.coo.coo_x;
			else if (data->player.coo.coo_x >= 22 && data->player.coo.coo_x <= 42 && (mini->ny < 16 || mini->ny > 48))
				mini->ny = data->player.coo.coo_y;
		}
}

void	movex(t_map *map, t_mini *mini, t_data *data)
{
	if (hit_box_x_wall(data, map, mini))
	{
		// printf("STOP HIT X\n");
		mini->nx = data->player.coo.coo_x;
	}
	if (data->map.tabmap[data->player.coo.case_y][data->player.coo.case_x] == 'D'
		&& data->map.door_map[data->player.coo.case_y][data->player.coo.case_x]->is_verti == true)
		{
			if ((mini->cx == 0 && mini->nx >= 22 && mini->nx <= 42)
			|| (mini->cx == 0 && mini->nx > 32 && data->player.coo.coo_x < 32) || (mini->cx == 0 && mini->nx < 32 && data->player.coo.coo_x > 32))
			{
				// printf("HIT DOOOR   xold=%lf    x=%lf\n",data->player.coo.coo_x, mini->nx);
				if (data->map.door_map[data->player.coo.case_y][data->player.coo.case_x]->pos <= 50 && abs_value(32 - data->player.coo.coo_x) > abs_value(32 - mini->nx))
					mini->nx = data->player.coo.coo_x;
				else if ((data->player.coo.coo_x < 22 || data->player.coo.coo_x > 42) && (mini->ny < 16 || mini->ny > 48))
					mini->nx = data->player.coo.coo_x;
				else if (data->player.coo.coo_x >= 22 && data->player.coo.coo_x <= 42 && (mini->ny < 16 || mini->ny > 48))
					mini->ny = data->player.coo.coo_y;
			}
		}
	if (data->map.tabmap[data->player.coo.case_y][data->player.coo.case_x] == 'F'
		&& data->map.door_map[data->player.coo.case_y][data->player.coo.case_x]->is_verti == true)
			hit_box_x_floo(mini, data);
	// printf("xold=%lf    x=%lf\n",data->player.coo.coo_x, mini->nx);
}

void	hit_box_y_floo(t_mini *mini, t_data *data)
{
	if ((mini->cy == 0 && mini->ny >= 22 && mini->ny <= 42)
		|| (mini->cy == 0 && mini->ny > 32 && data->player.coo.coo_y < 32) || (mini->cy == 0 && mini->ny < 32 && data->player.coo.coo_y > 32))
		{
			if (data->map.door_map[data->player.coo.case_y][data->player.coo.case_x]->is_floo_open == false && abs_value(32 - data->player.coo.coo_y) > abs_value(32 - mini->ny))
				mini->ny = data->player.coo.coo_y;
			else if ((data->player.coo.coo_y < 22 || data->player.coo.coo_y > 42) && (mini->nx < 16 || mini->nx > 48))
				mini->ny = data->player.coo.coo_y;
			else if (data->player.coo.coo_y >= 22 && data->player.coo.coo_y <= 42 && (mini->nx < 16 || mini->nx > 48))
				mini->nx = data->player.coo.coo_x;
		}
}

void	movey(t_map *map, t_mini *mini, t_data *data)
{
	if (hit_box_y_wall(data, map, mini))
	{
		// printf("STOP HIT Y\n");
		mini->ny = data->player.coo.coo_y;
	}
	if (data->map.tabmap[data->player.coo.case_y][data->player.coo.case_x] == 'D'
		&& data->map.door_map[data->player.coo.case_y][data->player.coo.case_x]->is_verti == false)
		{
			if ((mini->cy == 0 && mini->ny >= 22 && mini->ny <= 42)
			|| (mini->cy == 0 && mini->ny > 32 && data->player.coo.coo_y < 32) || (mini->cy == 0 && mini->ny < 32 && data->player.coo.coo_y > 32))
			{
				// printf("HIT DOOOR   yold=%lf    y=%lf\n",data->player.coo.coo_y, mini->ny);
				if (data->map.door_map[data->player.coo.case_y][data->player.coo.case_x]->pos <= 50 && abs_value(32 - data->player.coo.coo_y) > abs_value(32 - mini->ny))
					mini->ny = data->player.coo.coo_y;
				else if ((data->player.coo.coo_y < 22 || data->player.coo.coo_y > 42) && (mini->nx < 16 || mini->nx > 48))
					mini->ny = data->player.coo.coo_y;
				else if (data->player.coo.coo_y >= 22 && data->player.coo.coo_y <= 42 && (mini->nx < 16 || mini->nx > 48))
					mini->nx = data->player.coo.coo_x;
			}
		}
	if (data->map.tabmap[data->player.coo.case_y][data->player.coo.case_x] == 'F'
		&& data->map.door_map[data->player.coo.case_y][data->player.coo.case_x]->is_verti == false)
		hit_box_y_floo(mini, data);
	// printf(" yold=%lf    y=%lf\n",data->player.coo.coo_y, mini->ny);
}

void	handle_map_status(t_map *map, t_data *data, t_mini *mini)
{
	if (data->status == FLOO_MAP)
		return ;
	if (map->tabmap[data->player.coo.case_y][data->player.coo.case_x] == 'F' && (map->door_map[data->player.coo.case_y][data->player.coo.case_x]->is_floo_open == true))
	{
		if (map->door_map[data->player.coo.case_y][data->player.coo.case_x]->is_verti == true
			&& mini->cx == 0 && ((data->player.coo.coo_x <= 32.0 && mini->nx > 32.0) || (data->player.coo.coo_x >= 32.0 && mini->nx < 32.0)))
		{
			data->status = FLOO_MAP;
		}
		else if (map->door_map[data->player.coo.case_y][data->player.coo.case_x]->is_verti == false &&
			mini->cy == 0 && ((data->player.coo.coo_y <= 32.0 && mini->ny > 32.0) || (data->player.coo.coo_y >= 32.0 && mini->ny < 32.0)))
		{
			data->status = FLOO_MAP;
		}
		if (data->status == FLOO_MAP)
		{
			data->player.coo.coo_x = 32;
			data->player.coo.coo_y = 32;
			data->map.last_pos_x = data->player.coo.case_x;
			data->map.last_pos_y = data->player.coo.case_y;
		}
	}
}

void	calc_left_point_player(t_data *data)
{
	double	rad;
	double	dy;
	double	dx;
	double	v_normalize;

	rad = data->map.mini.rad + (90 * (M_PI / 180));
	dx = sin(rad);
	dy = cos(rad);
	// printf("dx>>%lf     dy>>%lf\n",dx,dy);
	if (round(dy) == 0.0 && round(dx) == 0.0)
	{
		dy = 0;
		dx = 0;
	}
	else
	{
		v_normalize = sqrt(dx * dx + dy * dy);
		dy = dy / v_normalize;
		dx = dx / v_normalize;
	}
	dy *= data->player.radius;
	dx *= data->player.radius;
	data->player.left.coo_x = data->player.coo.coo_x + dx;
	data->player.left.coo_y = data->player.coo.coo_y + dy;
	data->player.left.case_x = data->player.coo.case_x;
	data->player.left.case_y = data->player.coo.case_y;
	if (data->player.left.coo_x < 0)
	{
		data->player.left.case_x--;
		data->player.left.coo_x += 64;
	}
	else if (data->player.left.coo_x > 64)
	{
		data->player.left.case_x++;
		data->player.left.coo_x = fmod(data->player.left.coo_x, 64);
	}
	if (data->player.left.coo_y < 0)
	{
		data->player.left.case_y--;
		data->player.left.coo_y += 64;
	}
	else if (data->player.left.coo_y > 64)
	{
		data->player.left.case_y++;
		data->player.left.coo_y = fmod(data->player.left.coo_y, 64);
	}
}

void	calc_right_point_player(t_data *data)
{
	double	rad;
	double	dy;
	double	dx;
	double	v_normalize;

	rad = data->map.mini.rad - (90 * (M_PI / 180));
	dx = sin(rad);
	dy = cos(rad);
	// printf("dx>>%lf     dy>>%lf\n",dx,dy);
	if (round(dy) == 0.0 && round(dx) == 0.0)
	{
		dy = 0;
		dx = 0;
	}
	else
	{
		v_normalize = sqrt(dx * dx + dy * dy);
		dy = dy / v_normalize;
		dx = dx / v_normalize;
	}
	dy *= data->player.radius;
	dx *= data->player.radius;
	data->player.right.coo_x = data->player.coo.coo_x + dx;
	data->player.right.coo_y = data->player.coo.coo_y + dy;
	data->player.right.case_x = data->player.coo.case_x;
	data->player.right.case_y = data->player.coo.case_y;
	if (data->player.right.coo_x < 0)
	{
		data->player.right.case_x--;
		data->player.right.coo_x += 64;
	}
	else if (data->player.right.coo_x > 64)
	{
		data->player.right.case_x++;
		data->player.right.coo_x = fmod(data->player.right.coo_x, 64);
	}
	if (data->player.right.coo_y < 0)
	{
		data->player.right.case_y--;
		data->player.right.coo_y += 64;
	}
	else if (data->player.right.coo_y > 64)
	{
		data->player.right.case_y++;
		data->player.right.coo_y = fmod(data->player.right.coo_y, 64);
	}
}

void	try_hit_player(t_data *data)
{
	t_hitray	ray;
	t_lst		*lst;
	t_item		*item;
	t_lst		*next;

	ray.ax = data->player.left.case_x * 64 + data->player.left.coo_x;
	ray.ay = data->player.left.case_y * 64 + data->player.left.coo_y;
	ray.bx = data->player.right.case_x * 64 + data->player.right.coo_x;
	ray.by = data->player.right.case_y * 64 + data->player.right.coo_y;
	ray.cx = data->player.left_before.case_x * 64 + data->player.left_before.coo_x;
	ray.cy = data->player.left_before.case_y * 64 + data->player.left_before.coo_y;
	lst = get_first_elem_lst(data->item);
	while (lst)
	{
		item = lst->dt;
		ray.dx = item->left.case_x * 64 + item->left.coo_x;
		ray.dy = item->left.case_y * 64 + item->left.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			// data->player.damage.damage_take += item->damage.damage_do;
			// data->player.damage.damage_spider_take += item->damage.damage_spider_do;
			// data->player.damage.damage_dementor_take += item->damage.damage_dementor_do;
			// data->player.damage.slow_force_take += item->damage.slow_force_do;
			// data->player.damage.slow_frame_take += item->damage.slow_frame_do;
			// data->player.damage.poison_force_take += item->damage.poison_force_do;
			// data->player.damage.poison_frame_take += item->damage.poison_frame_do;
			// data->player.damage.fire_force_take += item->damage.fire_force_do;
			// data->player.damage.fire_frame_take += item->damage.fire_frame_do;
			apply_damage(&data->player.damage, &item->damage);
			next = lst->next;
			data->item = remove_elem_lst(lst);
			f_elem_lst(lst);
			lst = next;
			continue;
		}
		ray.dx = item->center.case_x * 64 + item->center.coo_x;
		ray.dy = item->center.case_y * 64 + item->center.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			// data->player.damage.damage_take += item->damage.damage_do;
			// data->player.damage.damage_spider_take += item->damage.damage_spider_do;
			// data->player.damage.damage_dementor_take += item->damage.damage_dementor_do;
			// data->player.damage.slow_force_take += item->damage.slow_force_do;
			// data->player.damage.slow_frame_take += item->damage.slow_frame_do;
			// data->player.damage.poison_force_take += item->damage.poison_force_do;
			// data->player.damage.poison_frame_take += item->damage.poison_frame_do;
			// data->player.damage.fire_force_take += item->damage.fire_force_do;
			// data->player.damage.fire_frame_take += item->damage.fire_frame_do;
			apply_damage(&data->player.damage, &item->damage);
			next = lst->next;
			data->item = remove_elem_lst(lst);
			f_elem_lst(lst);
			lst = next;
			continue;
		}
		ray.dx = item->right.case_x * 64 + item->right.coo_x;
		ray.dy = item->right.case_y * 64 + item->right.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			// data->player.damage.damage_take += item->damage.damage_do;
			// data->player.damage.damage_spider_take += item->damage.damage_spider_do;
			// data->player.damage.damage_dementor_take += item->damage.damage_dementor_do;
			// data->player.damage.slow_force_take += item->damage.slow_force_do;
			// data->player.damage.slow_frame_take += item->damage.slow_frame_do;
			// data->player.damage.poison_force_take += item->damage.poison_force_do;
			// data->player.damage.poison_frame_take += item->damage.poison_frame_do;
			// data->player.damage.fire_force_take += item->damage.fire_force_do;
			// data->player.damage.fire_frame_take += item->damage.fire_frame_do;
			apply_damage(&data->player.damage, &item->damage);
			next = lst->next;
			data->item = remove_elem_lst(lst);
			f_elem_lst(lst);
			lst = next;
			continue;
		}
		lst = lst->next;
	}
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
			if (mini->last_foot == MINI_LEFT)
				mini->last_foot = MINI_RIGHT;
			else
				mini->last_foot = MINI_LEFT;
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
	if (data->player.damage.slow_frame_take > 0 || data->player.damage.slow_force_take > 0)
	{
		if (data->player.damage.slow_force_take > 100)
			data->player.damage.slow_force_take = 100;
		mini->dx *= (100 - data->player.damage.slow_force_take) / 100;
		mini->dy *= (100 - data->player.damage.slow_force_take) / 100;
		if (data->player.damage.slow_frame_take > 0)
			data->player.damage.slow_frame_take--;
		if (data->player.damage.slow_frame_take <= 0)
			data->player.damage.slow_force_take--;
	}
	recalc_x(data, mini, map);
	recalc_y(data, mini, map);
	movex(map, mini, data);
	movey(map, mini, data);
	handle_map_status(map, data, mini);
	if (data->status == FLOO_MAP)
		return ;
	calc_left_point_player(data);
	calc_right_point_player(data);
	data->player.left_before.coo_x = data->player.left.coo_x;
	data->player.left_before.coo_y = data->player.left.coo_y;
	data->player.left_before.case_x = data->player.left.case_x;
	data->player.left_before.case_y = data->player.left.case_y;
	data->player.right_before.coo_x = data->player.right.coo_x;
	data->player.right_before.coo_y = data->player.right.coo_y;
	data->player.right_before.case_x = data->player.right.case_x;
	data->player.right_before.case_y = data->player.right.case_y;
	if (mini->ny != data->player.coo.coo_y)
	{
		data->player.coo.coo_y = mini->ny;
		data->player.coo.case_y += mini->cy;
	}
	if (mini->nx != data->player.coo.coo_x)
	{
		data->player.coo.coo_x = mini->nx;
		data->player.coo.case_x += mini->cx;
	}
	calc_left_point_player(data);
	calc_right_point_player(data);
	try_hit_player(data);
	// move_x(data, map, mini);
	// move_y(data, map, mini);
}

