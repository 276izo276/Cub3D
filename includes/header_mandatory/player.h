/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:44:15 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:44:16 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "struct.h"

//move mini_map
void	handle_move(t_map *map, t_mini *mini, t_data *data);
void	rotate_right(t_data *data);
void	rotate_left(t_data *data);

#endif
