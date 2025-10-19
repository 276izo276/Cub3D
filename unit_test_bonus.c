#include "utils_bonus.h"
#include "color_bonus.h"
#include <string.h>
#include <stdio.h>

int	exit_error(int test, char *str)
{
	printf(_RED _BOLD"KO"_END _BLUE" Error on test "_BOLD _ORANGE"%d"_END,test);
	if (str)
		printf(" %s\n",str);
	else
		printf("\n");
	return (1);
}

int main()
{
	char *str;

	printf("START UNIT TEST\n");
	printf("test 1\n");
	str = ft_itoa(-2147483648);
	if (strcmp(str, "-2147483648") != 0)
		return (exit_error(1, str));
	printf("test 2\n");
	str = ft_itoa(-42);
	if (strcmp(str, "-42") != 0)
		return (exit_error(1, str));
	printf("test 3\n");
	str = ft_itoa(-0);
	if (strcmp(str, "0") != 0)
		return (exit_error(1, str));
	printf("test 4\n");
	str = ft_itoa(2147483647);
	if (strcmp(str, "2147483647") != 0)
		return (exit_error(1, str));
	printf("test 5\n");
	str = ft_itoa(42);
	if (strcmp(str, "42") != 0)
		return (exit_error(1, str));
	printf("END UNIT TEST\n");
}