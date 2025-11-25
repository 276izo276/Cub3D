#include "struct_bonus.h"
#include <math.h>

static void	parent_coo_x(t_case *cel)
{
	if (fmod(cel->parent->coo.coo_x, 64) == 0)
		cel->coo.coo_x = 64 - cel->parent->coo.coo_x;
	else
		cel->coo.coo_x = cel->parent->coo.coo_x;
}

static void	calc_cel_x_y_child(t_case *cel)
{
	if (fmod(cel->coo.coo_x, 64) != 0)
	{
		if (cel->parent)
			parent_coo_x(cel);
		else
			cel->coo.coo_x = 32;
		cel->coo.coo_x = (cel->coo.coo_x + 32 + (cel->child->child->coo.case_x
					- cel->child->coo.case_x) * 32) / 2;
	}
	if (fmod(cel->coo.coo_y, 64) != 0)
	{
		if (cel->parent)
		{
			if (fmod(cel->parent->coo.coo_y, 64) == 0)
				cel->coo.coo_y = 64 - cel->parent->coo.coo_y;
			else
				cel->coo.coo_y = cel->parent->coo.coo_y;
		}
		else
			cel->coo.coo_y = 32;
		cel->coo.coo_y = (cel->coo.coo_y + 32 +
					(cel->child->child->coo.case_y
					- cel->child->coo.case_y) * 32) / 2;
	}
}

static void	calc_cel_x_y_nochild(t_case *cel, t_enemy *enemy)
{
	if (fmod(cel->coo.coo_x, 64) != 0)
	{
		if (cel->parent)
			parent_coo_x(cel);
		else
			cel->coo.coo_x = enemy->center.coo_x;
		cel->coo.coo_x = (cel->coo.coo_x + 32 + (cel->child->coo.case_x
					- cel->coo.case_x) * 32) / 2;
	}
	if (fmod(cel->coo.coo_y, 64) != 0)
	{
		if (cel->parent)
		{
			if (fmod(cel->parent->coo.coo_y, 64) == 0)
				cel->coo.coo_y = 64 - cel->parent->coo.coo_y;
			else
				cel->coo.coo_y = cel->parent->coo.coo_y;
		}
		else
			cel->coo.coo_y = enemy->center.coo_y;
		cel->coo.coo_y = (cel->coo.coo_y + enemy->goal.coo_y) / 2;
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
			cel->coo.coo_x = 32 + (cel->child->coo.case_x
							- cel->coo.case_x) * 32;
			cel->coo.coo_y = 32 + (cel->child->coo.case_y
							- cel->coo.case_y) * 32;
			if (cel->child->child)
				calc_cel_x_y_child(cel);
			else
				calc_cel_x_y_nochild(cel, enemy);
		}
		else
		{
			cel->coo.coo_x = enemy->goal.coo_x;
			cel->coo.coo_y = enemy->goal.coo_y;
		}
		cel = cel->child;
	}
	(void)data;
}
