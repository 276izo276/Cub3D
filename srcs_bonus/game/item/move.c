#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>


void	calc_left_point_item(t_item *item)
{
	double	rad;
	double	dy;
	double	dx;
	double	v_normalize;

	rad = item->rad + (90 * (M_PI / 180));
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
	dy *= item->radius;
	dx *= item->radius;
	item->left.coo_x = item->center.coo_x + dx;
	item->left.coo_y = item->center.coo_y + dy;
	item->left.case_x = item->center.case_x;
	item->left.case_y = item->center.case_y;
	if (item->left.coo_x < 0)
	{
		item->left.case_x--;
		item->left.coo_x += 64;
	}
	else if (item->left.coo_x > 64)
	{
		item->left.case_x++;
		item->left.coo_x = fmod(item->left.coo_x, 64);
	}
	if (item->left.coo_y < 0)
	{
		item->left.case_y--;
		item->left.coo_y += 64;
	}
	else if (item->left.coo_y > 64)
	{
		item->left.case_y++;
		item->left.coo_y = fmod(item->left.coo_y, 64);
	}
}

void	calc_right_point_item(t_item *item)
{
	double	rad;
	double	dy;
	double	dx;
	double	v_normalize;

	rad = item->rad - (90 * (M_PI / 180));
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
	dy *= item->radius;
	dx *= item->radius;
	item->right.coo_x = item->center.coo_x + dx;
	item->right.coo_y = item->center.coo_y + dy;
	item->right.case_x = item->center.case_x;
	item->right.case_y = item->center.case_y;
	if (item->right.coo_x < 0)
	{
		item->right.case_x--;
		item->right.coo_x += 64;
	}
	else if (item->right.coo_x > 64)
	{
		item->right.case_x++;
		item->right.coo_x = fmod(item->right.coo_x, 64);
	}
	if (item->right.coo_y < 0)
	{
		item->right.case_y--;
		item->right.coo_y += 64;
	}
	else if (item->right.coo_y > 64)
	{
		item->right.case_y++;
		item->right.coo_y = fmod(item->right.coo_y, 64);
	}
}

#include <stdio.h>

void	move_item(t_data *data)
{
	t_lst	*lst;
	t_item	*item;
	double	dy;
	double	dx;
	double	v_normalize;

	lst = get_first_elem_lst(data->item);
	while (lst)
	{
		item = lst->dt;
		item->rad = item->deg * (M_PI / 180);
		dx = sin(item->rad);
		dy = cos(item->rad);
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
		dy *= item->speed;
		dx *= item->speed;
		item->center.coo_x += dx;
		item->center.coo_y += dy;
		calc_left_point_item(item);
		calc_right_point_item(item);
		lst = lst->next;
	}
}
