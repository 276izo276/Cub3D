/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:57:49 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:57:50 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
