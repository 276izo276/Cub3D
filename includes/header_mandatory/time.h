/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:44:29 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:44:30 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include <sys/time.h>

typedef struct timeval	t_time;

long long	get_mtime(void);

#endif
