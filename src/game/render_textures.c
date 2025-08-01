/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/08/01 12:08:09 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_north_texture(t_cub3d *cub3d, int x, int y)
{
	unsigned int	color;
	int				texture_width;
	int				tx;

	texture_width = cub3d->texture->north->width - 1;
	tx = (int)(cub3d->ray[x].rx * texture_width / SQ);
	tx = tx % texture_width;
	color = get_pixel_color(cub3d->texture->north,
			cub3d->ray[x].distance, y, tx);
	my_pixel_put(cub3d->img, x, y, color);
}

void	draw_south_texture(t_cub3d *cub3d, int x, int y)
{
	unsigned int	color;
	int				texture_width;
	int				tx;

	texture_width = cub3d->texture->south->width - 1;
	tx = (int)(cub3d->ray[x].rx * texture_width / SQ);
	tx = texture_width - (tx % texture_width);
	color = get_pixel_color(cub3d->texture->south,
			cub3d->ray[x].distance, y, tx);
	my_pixel_put(cub3d->img, x, y, color);
}

void	draw_west_texture(t_cub3d *cub3d, int x, int y)
{
	unsigned int	color;
	int				texture_width;
	int				ty;

	texture_width = cub3d->texture->west->width - 1;
	ty = (int)(cub3d->ray[x].ry * texture_width / SQ);
	ty = texture_width - (ty % texture_width);
	color = get_pixel_color(cub3d->texture->west,
			cub3d->ray[x].distance, y, ty);
	my_pixel_put(cub3d->img, x, y, color);
}

void	draw_east_texture(t_cub3d *cub3d, int x, int y)
{
	unsigned int	color;
	int				texture_width;
	int				ty;

	texture_width = cub3d->texture->east->width - 1;
	ty = (int)(cub3d->ray[x].ry * texture_width / SQ);
	ty = ty % texture_width;
	color = get_pixel_color(cub3d->texture->east,
			cub3d->ray[x].distance, y, ty);
	my_pixel_put(cub3d->img, x, y, color);
}

void	draw_textures(t_cub3d *cub3d, int x, int start, int end)
{
	int	y;

	y = -1;
	while (++y < start)
		my_pixel_put(cub3d->img, x, y, cub3d->player->c_col);
	y--;
	while (++y < end)
	{
		if (cub3d->ray[x].type == 'h' && cub3d->ray[x].angle >= 180)
			draw_north_texture(cub3d, x, y);
		if (cub3d->ray[x].type == 'h' && cub3d->ray[x].angle < 180)
			draw_south_texture(cub3d, x, y);
		if (cub3d->ray[x].type == 'v' && cub3d->ray[x].angle >= 90
			&& cub3d->ray[x].angle < 270)
			draw_west_texture(cub3d, x, y);
		if (cub3d->ray[x].type == 'v' && (cub3d->ray[x].angle < 90
				|| cub3d->ray[x].angle > 270))
			draw_east_texture(cub3d, x, y);
	}
	y--;
	while (++y < HE)
		my_pixel_put(cub3d->img, x, y, cub3d->player->f_col);
}
