int	calc_path_size(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
	{
		i++;
	}
	return (i);
}

int	get_start_path(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
	{
		i++;
	}
	return (i);
}
