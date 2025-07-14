/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:15:33 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/14 12:35:48 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	playability_check(t_cub3d *cub3d)
{
	char	**dup;

	if (cub3d->start_pos == 'X' || cub3d->start_y <= 0 || cub3d->start_x <= 0
		|| (cub3d->start_pos != 'N' && cub3d->start_pos != 'S'
			&& cub3d->start_pos != 'E' && cub3d->start_pos != 'W'))
		return (ERROR_MAP);
	dup = matrix_dup(cub3d->map);
	if (flood_fill(cub3d->start_y, cub3d->start_x, dup, cub3d->start_pos) < 0)
		return (free_matrix(dup), ERROR_MAP);
	return (free_matrix(dup), 0);
}

int	map_check(t_cub3d *cub3d)
{
	int		i;
	int		j;

	i = -1;
	while (cub3d->map[++i] != NULL)
	{
		j = -1;
		while (cub3d->map[i][++j] != '\0')
		{
			if ((cub3d->map[i][j] != '1' && cub3d->map[i][j] != '0'
				&& cub3d->map[i][j] != ' ') && (cub3d->start_pos == 'X' &&
					(cub3d->map[i][j] == 'N' || cub3d->map[i][j] == 'S'
					|| cub3d->map[i][j] == 'E' || cub3d->map[i][j] == 'W')))
			{
				cub3d->start_pos = cub3d->map[i][j];
				cub3d->start_y = i;
				cub3d->start_x = j;
			}
			else if (cub3d->map[i][j] != '1' && cub3d->map[i][j] != '0'
				&& cub3d->map[i][j] != ' ')
				return (ERROR_MAP);
		}
	}
	return (playability_check(cub3d));
}
