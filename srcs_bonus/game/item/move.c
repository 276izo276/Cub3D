#include "struct_bonus.h"

void	move_item(t_data *data)
{
	t_lst	*lst;
	t_item	*item;

	lst = get_first_elem_lst(data->item);
	while (lst)
	{
		item = lst->dt;

		lst = lst->next;
	}
}
