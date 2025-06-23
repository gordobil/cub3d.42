/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:42:55 by mafarto-          #+#    #+#             */
/*   Updated: 2025/05/30 12:21:31 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void draw_square(t_cub3d *cub3d, int x, int y, int color)
{
	for (int i = 0; i < MINI_TILE; i++)
	{
		for (int j = 0; j < MINI_TILE; j++)
		{
			mlx_pixel_put(cub3d->mlx, cub3d->window, x + j, y + i, color);
		}
	}
}

void draw_minimap(t_cub3d *cub3d)
{
	for (int i = 0; cub3d->map[i]; i++)
	{
		for (int j = 0; cub3d->map[i][j]; j++)
		{
			if (cub3d->map[i][j] == '1')
				draw_square(cub3d, j * MINI_TILE, i * MINI_TILE, 0x666666);
			else if (cub3d->map[i][j] == '0' || (cub3d->map[i][j] >= 'A' || 'Z' >= cub3d->map[i][j]))
				draw_square(cub3d, j * MINI_TILE, i * MINI_TILE, 0xFFFFFF);
		}
	}

	int px = cub3d->player->x * MINI_SCALE;
	int py = cub3d->player->y * MINI_SCALE;

	mlx_pixel_put(cub3d->mlx, cub3d->window, px, py, 0xFF0000); // rojo
}
