/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/14 13:14:42 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_minimap_pointer(t_cub3d *cub3d, int x, int y)
{
	x += 4;
	y += 4;
	my_pixel_put(cub3d->img, x, y, BLUE);
	if (cub3d->player->ang > 335 || cub3d->player->ang < 24)
		my_pixel_put(cub3d->img, x + 1, y, RED);
	else if (cub3d->player->ang > 23 && cub3d->player->ang < 67)
		my_pixel_put(cub3d->img, x + 1, y + 1, RED);
	else if (cub3d->player->ang > 66 && cub3d->player->ang < 114)
		my_pixel_put(cub3d->img, x, y + 1, RED);
	else if (cub3d->player->ang > 113 && cub3d->player->ang < 157)
		my_pixel_put(cub3d->img, x - 1, y + 1, RED);
	else if (cub3d->player->ang > 156 && cub3d->player->ang < 203)
		my_pixel_put(cub3d->img, x - 1, y, RED);
	else if (cub3d->player->ang > 202 && cub3d->player->ang < 246)
		my_pixel_put(cub3d->img, x - 1, y - 1, RED);
	else if (cub3d->player->ang > 245 && cub3d->player->ang < 293)
		my_pixel_put(cub3d->img, x, y - 1, RED);
	else if (cub3d->player->ang > 292 && cub3d->player->ang < 336)
		my_pixel_put(cub3d->img, x + 1, y - 1, RED);
}

void	draw_minimap(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	tile;

	tile = SQ * MINI_SCALE;
	i = -1;
	while (cub3d->map[++i])
	{
		j = -1;
		while (cub3d->map[i][++j])
		{
			if (cub3d->map[i][j] == '1')
				draw_square(cub3d, j * tile, i * tile, GREY);
			else if (cub3d->map[i][j] == '0')
				draw_square(cub3d, j * tile, i * tile, WHITE);
		}
	}
	draw_minimap_pointer(cub3d,
		cub3d->player->x * MINI_SCALE, cub3d->player->y * MINI_SCALE);
}
