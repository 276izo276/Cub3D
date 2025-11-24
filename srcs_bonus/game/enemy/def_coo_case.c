#include "struct_bonus.h"

static void	parent_coo_x(t_case *cel)
{
	if (cel->parent->coo_x % 64 == 0)
		cel->coo_x = 64 - cel->parent->coo_x;
	else
		cel->coo_x = cel->parent->coo_x;
}

static void	calc_cel_x_y_child(t_case *cel)
{
	if (cel->coo_x % 64 != 0)
	{
		if (cel->parent)
			parent_coo_x(cel);
		else
			cel->coo_x = 32;
		cel->coo_x = (cel->coo_x + 32 + (cel->child->child->case_x
					- cel->child->case_x) * 32) / 2;
	}
	if (cel->coo_y % 64 != 0)
	{
		if (cel->parent)
		{
			if (cel->parent->coo_y % 64 == 0)
				cel->coo_y = 64 - cel->parent->coo_y;
			else
				cel->coo_y = cel->parent->coo_y;
		}
		else
			cel->coo_y = 32;
		cel->coo_y = (cel->coo_y + 32 + (cel->child->child->case_y
					- cel->child->case_y) * 32) / 2;
	}
}

static void	calc_cel_x_y_nochild(t_case *cel, t_enemy *enemy)
{
	if (cel->coo_x % 64 != 0)
	{
		if (cel->parent)
			parent_coo_x(cel);
		else
			cel->coo_x = enemy->center.coo_x;
		cel->coo_x = (cel->coo_x + 32 + (cel->child->case_x
					- cel->case_x) * 32) / 2;
	}
	if (cel->coo_y % 64 != 0)
	{
		if (cel->parent)
		{
			if (cel->parent->coo_y % 64 == 0)
				cel->coo_y = 64 - cel->parent->coo_y;
			else
				cel->coo_y = cel->parent->coo_y;
		}
		else
			cel->coo_y = enemy->center.coo_y;
		cel->coo_y = (cel->coo_y + enemy->goal.coo_y) / 2;
	}
}

void	calc_in_cell_path(t_data *data, t_enemy *enemy)
{
	t_case	*cel;

	cel = enemy->way;
	while (cel)
	{
		if (cel->child)
		{
			cel->coo_x = 32 + (cel->child->case_x - cel->case_x) * 32;
			cel->coo_y = 32 + (cel->child->case_y - cel->case_y) * 32;
			if (cel->child->child)
				calc_cel_x_y_child(cel);
			else
				calc_cel_x_y_nochild(cel, enemy);
		}
		else
		{
			cel->coo_x = enemy->goal.coo_x;
			cel->coo_y = enemy->goal.coo_y;
		}
		cel = cel->child;
	}
	(void)data;
}
