/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:18:42 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/22 13:31:05 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_num(char *elem, int s, int j, int k)
{
	char	*temp;
	int		n;

	if (((elem[j] < '0' || elem[j] > '9') && elem[j] != ','
			&& elem[j] != '\0') || (k == 2 && elem[j] != '\0'))
		return (-ERROR_ELEMS);
	temp = ft_substr(elem, s, j - s);
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

int	get_colors(char **elems, t_player *player, int i, int j)
{
	int		k;
	int		start;
	int		c[3];

	while (elems[++i] && i <= 5)
	{
		j = -1;
		k = -1;
		while (elems[i][++j] != '\0' && ++k <= 2 && (elems[i][j] == ',' ||
			(elems[i][j] > 47 && elems[i][j] < 58)))
		{
			start = j;
			while (elems[i][j] != '\0' && elems[i][j] > 47 && elems[i][j] < 58)
				j++;
			c[k] = get_num(elems[i], start, j, k);
			if (c[k] < 0 || c[k] > 255)
				return (ERROR_ELEMS);
			if (elems[i][j] == '\0')
				break ;
		}
		set_colors(player, i, c);
	}
	return (0);
}
