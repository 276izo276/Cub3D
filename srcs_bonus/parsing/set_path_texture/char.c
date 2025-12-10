/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:57:33 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:57:34 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "texture_bonus.h"
#include "utils_bonus.h"

static void	set_path_letters(t_data *data)
{
	data->img[CHAR_A].path = "./texture/Letters/A.xpm";
	data->img[CHAR_B].path = "./texture/Letters/B.xpm";
	data->img[CHAR_C].path = "./texture/Letters/C.xpm";
	data->img[CHAR_D].path = "./texture/Letters/D.xpm";
	data->img[CHAR_E].path = "./texture/Letters/E.xpm";
	data->img[CHAR_F].path = "./texture/Letters/F.xpm";
	data->img[CHAR_G].path = "./texture/Letters/G.xpm";
	data->img[CHAR_H].path = "./texture/Letters/H.xpm";
	data->img[CHAR_I].path = "./texture/Letters/I.xpm";
	data->img[CHAR_J].path = "./texture/Letters/J.xpm";
	data->img[CHAR_K].path = "./texture/Letters/K.xpm";
	data->img[CHAR_L].path = "./texture/Letters/L.xpm";
	data->img[CHAR_M].path = "./texture/Letters/M.xpm";
	data->img[CHAR_N].path = "./texture/Letters/N.xpm";
	data->img[CHAR_O].path = "./texture/Letters/O.xpm";
	data->img[CHAR_P].path = "./texture/Letters/P.xpm";
	data->img[CHAR_Q].path = "./texture/Letters/Q.xpm";
	data->img[CHAR_R].path = "./texture/Letters/R.xpm";
	data->img[CHAR_S].path = "./texture/Letters/S.xpm";
	data->img[CHAR_T].path = "./texture/Letters/T.xpm";
	data->img[CHAR_U].path = "./texture/Letters/U.xpm";
	data->img[CHAR_V].path = "./texture/Letters/V.xpm";
	data->img[CHAR_W].path = "./texture/Letters/W.xpm";
	data->img[CHAR_X].path = "./texture/Letters/X.xpm";
	data->img[CHAR_Y].path = "./texture/Letters/Y.xpm";
}

static void	set_path_numbers(t_data *data)
{
	data->img[NB_0].path = "./texture/Numbers/0.xpm";
	data->img[NB_1].path = "./texture/Numbers/1.xpm";
	data->img[NB_2].path = "./texture/Numbers/2.xpm";
	data->img[NB_3].path = "./texture/Numbers/3.xpm";
	data->img[NB_4].path = "./texture/Numbers/4.xpm";
	data->img[NB_5].path = "./texture/Numbers/5.xpm";
	data->img[NB_6].path = "./texture/Numbers/6.xpm";
	data->img[NB_7].path = "./texture/Numbers/7.xpm";
	data->img[NB_8].path = "./texture/Numbers/8.xpm";
	data->img[NB_9].path = "./texture/Numbers/9.xpm";
}

void	set_path_char_texture(t_data *data)
{
	set_path_letters(data);
	set_path_numbers(data);
	data->img[SPACE].path = "./texture/Letters/space.xpm";
	data->img[CHAR_Z].path = "./texture/Letters/Z.xpm";
}
