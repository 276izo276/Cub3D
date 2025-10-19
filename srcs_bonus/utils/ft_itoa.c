#include <stdio.h>
#include <stdlib.h>

int	fill_itoa(char **str, int index, long long int nb)
{
	if (nb >= 10)
	{
		index = fill_itoa(str, index, nb / 10);
	}
	(*str)[index] = nb % 10 + 48;
	return (index + 1);
}

char	*ft_itoa(int nb)
{
	char		 *str;
	int				i;
	unsigned int	nnb;

	str = malloc(sizeof(char) * 13);
	if (!str)
		return (NULL);
	i = 0;
	while (i <= 13)
	{
		str[i++] = 0;
	}
	if (nb < 0)
	{
		nnb = -nb;
		str[0] = '-';
		fill_itoa(&str, 1, nnb);
	}
	else
		fill_itoa(&str, 0, nb);
	return (str);
}
