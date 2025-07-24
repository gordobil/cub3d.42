/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/14 13:13:22 by ngordobi         ###   ########.fr       */
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
		my_pixel_put(cub3d->img, x, y, cub3d->player->c_col);
	y--;
	while (++y < end)
		my_pixel_put(cub3d->img, x, y, WHITE);
	y--;
	while (++y < HE)
		my_pixel_put(cub3d->img, x, y, cub3d->player->f_col);
}

void	draw_square(t_cub3d *cub3d, int x, int y, int color)
{
	int	i;
	int	j;
	int	tile;

	tile = SQ * MINI_SCALE;
	i = 4;
	while (++i < tile + 5)
	{
		j = 4;
		while (++j < tile + 5)
			my_pixel_put(cub3d->img, x + j, y + i, color);
	}
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
