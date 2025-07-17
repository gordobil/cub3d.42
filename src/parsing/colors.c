/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:18:42 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/17 19:36:13 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_num(char *elem, int s, int len)
{
	char	*temp;
	int		n;

	temp = ft_substr(elem, s, len);
	n = ft_atoi(temp);
	free(temp);
	return (n);
}

void	set_colors(t_player *player, int i, int c[3])
{
	if (i == 4)
		player->f_col = 255 | (c[0] << 24) | (c[1] << 16) | (c[2] << 8);
	else if (i == 5)
		player->c_col = 255 | (c[0] << 24) | (c[1] << 16) | (c[2] << 8);
}

int	get_colors(char **elems, t_player *player, int i)
{
	int		j;
	int		x;
	int		start;
	int		c[3];

	while (++i < 6)
	{
		j = -1;
		x = -1;
		while (elems[i][++j] != '\0' && ++x <= 2 && (elems[i][j] == ',' ||
			(elems[i][j] >= '0' && elems[i][j] <= '9')))
		{
			start = j;
			while (elems[i][j] >= '0' && elems[i][j] <= '9')
				j++;
			if (((elems[i][j] < '0' || elems[i][j] > '9') && elems[i][j] != ','
				&& elems[i][j] != '\0') || (x == 2 && elems[i][j] != '\0'))
				return (ERROR_ELEMS);
			c[x] = get_num(elems[i], start, j - start);
			if (c[x] > 255 || c[x] < 0)
				return (ERROR_ELEMS);
		}
		set_colors(player, i, c);
	}
	return (0);
}
