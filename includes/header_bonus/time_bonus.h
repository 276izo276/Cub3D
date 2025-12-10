/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:44:00 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:44:01 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_BONUS_H
# define TIME_BONUS_H

# include <sys/time.h>

typedef struct timeval	t_time;

long long				get_mtime(void);

#endif
