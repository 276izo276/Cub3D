
int	are_double_close(double nb1, double nb2)
{
	double	eq;

	eq = nb1 - nb2;
	if (eq < 0)
		eq = -eq;
	if (eq < 3)
		return (1);
	return (0);
}