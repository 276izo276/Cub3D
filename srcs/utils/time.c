/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:46:18 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:46:19 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include <stdlib.h>

long long	get_mtime(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
