/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/01 18:39:28 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WD || y < 0 || y >= HE)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_vertical_line(t_cub3d *cub3d, int x, int start, int end)
{
	int	y;

	y = -1;
	while (++y < start)
		my_pixel_put(cub3d->img, x, y, BLUE2);
	y--;
	while (++y < end)
		my_pixel_put(cub3d->img, x, y, WHITE);
	y--;
	while (++y < HE)
		my_pixel_put(cub3d->img, x, y, BLUE);
}

void	draw_square(t_cub3d *cub3d, int x, int y, int color)
{
	int	i;
	int	j;

	i = 4;
	while (++i < MINI_TILE + 5)
	{
		j = 4;
		while (++j < MINI_TILE + 5)
			my_pixel_put(cub3d->img, x + j, y + i, color);
	}
}

void	draw_minimap_pointer(t_cub3d *cub3d, int x, int y)
{
	my_pixel_put(cub3d->img, x, y, RED);
	if (cub3d->player->ang >= 337 || cub3d->player->ang <= 23)
		my_pixel_put(cub3d->img, x, y + 1, RED);
	else if (cub3d->player->ang >= 24 || cub3d->player->ang <= 66)
		my_pixel_put(cub3d->img, x + 1, y + 1, RED);
	else if (cub3d->player->ang >= 67 || cub3d->player->ang <= 113)
		my_pixel_put(cub3d->img, x + 1, y, RED);
	else if (cub3d->player->ang >= 114 || cub3d->player->ang <= 156)
		my_pixel_put(cub3d->img, x + 1, y - 1, RED);
	else if (cub3d->player->ang >= 157 || cub3d->player->ang <= 203)
		my_pixel_put(cub3d->img, x, y - 1, RED);
	else if (cub3d->player->ang >= 204 || cub3d->player->ang <= 246)
		my_pixel_put(cub3d->img, x - 1, y - 1, RED);
	else if (cub3d->player->ang >= 247 || cub3d->player->ang <= 293)
		my_pixel_put(cub3d->img, x - 1, y, RED);
	else if (cub3d->player->ang >= 294 || cub3d->player->ang <= 336)
		my_pixel_put(cub3d->img, x - 1, y + 1, RED);
}

void	draw_minimap(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = -1;
	while (cub3d->map[++i])
	{
		j = -1;
		while (cub3d->map[i][++j])
		{
			if (cub3d->map[i][j] == '1')
				draw_square(cub3d, j * MINI_TILE, i * MINI_TILE, GREY);
			else if (cub3d->map[i][j] == '0')
				draw_square(cub3d, j * MINI_TILE, i * MINI_TILE, WHITE);
		}
	}
	draw_minimap_pointer(cub3d,
		cub3d->player->x * MINI_SCALE, cub3d->player->y * MINI_SCALE);
}

void	draw_pointer(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = (WD / 2) - 2;
	while (++x <= (WD / 2) + 1)
	{
		y = (HE / 2) - 8;
		while (++y <= (HE / 2) + 7)
			my_pixel_put(cub3d->img, x, y, RED);
	}
	x = (WD / 2) - 8;
	while (++x <= (WD / 2) + 7)
	{
		y = (HE / 2) - 2;
		while (++y <= (HE / 2) + 1)
			my_pixel_put(cub3d->img, x, y, RED);
	}
}
