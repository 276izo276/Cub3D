#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
		*((char *)s - 1 + n--) = 0;
}
