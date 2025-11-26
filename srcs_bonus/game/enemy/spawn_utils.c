
void	set_valid_spawn(double *new_x, double *new_y)
{
	if (*new_x >= 64)
		*new_x = 63.5;
	if (*new_y >= 64)
		*new_y = 63.5;
	if (*new_x < 0)
		*new_x = .5;
	if (*new_y < 0)
		*new_y = .5;
}