/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/08/02 11:36:42 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_texture_pixel_x(t_cub3d *cub3d, t_img *texture, int x, int y)
{
	unsigned int	color;
	int				ty;
	int				tx;
	int				wall_height;
	int				texture_width;

	if (!texture || !texture->addr)
		return ;
	texture_width = texture->width - 1;
	tx = (int)(cub3d->ray[x].rx * texture_width / SQ);
	tx = tx % texture_width;
	wall_height = (int)((SQ * HE) / cub3d->ray[x].distance);
	ty = ((y - (HE / 2 - wall_height / 2)) * texture->height) / wall_height;
	color = *((unsigned int *)(texture->addr \
		+ (ty * texture->line_length + tx * (texture->bits_per_pixel / 8))));
	my_pixel_put(cub3d->img, x, y, color);
}

void	draw_texture_pixel_y(t_cub3d *cub3d, t_img *texture, int x, int y)
{
	unsigned int	color;
	int				ty;
	int				tx;
	int				wall_height;
	int				texture_width;

	if (!texture || !texture->addr)
		return ;
	texture_width = texture->width - 1;
	tx = (int)(cub3d->ray[x].ry * texture_width / SQ);
	tx = tx % texture_width;
	wall_height = (int)((SQ * HE) / cub3d->ray[x].distance);
	ty = ((y - (HE / 2 - wall_height / 2)) * texture->height) / wall_height;
	color = *((unsigned int *)(texture->addr \
		+ (ty * texture->line_length + tx * (texture->bits_per_pixel / 8))));
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
			draw_texture_pixel_x(cub3d, cub3d->texture->north, x, y);
		if (cub3d->ray[x].type == 'h' && cub3d->ray[x].angle < 180)
			draw_texture_pixel_x(cub3d, cub3d->texture->south, x, y);
		if (cub3d->ray[x].type == 'v' && cub3d->ray[x].angle >= 90
			&& cub3d->ray[x].angle < 270)
			draw_texture_pixel_y(cub3d, cub3d->texture->west, x, y);
		if (cub3d->ray[x].type == 'v' && (cub3d->ray[x].angle < 90
				|| cub3d->ray[x].angle > 270))
			draw_texture_pixel_y(cub3d, cub3d->texture->east, x, y);
	}
	y--;
	while (++y < HE)
		my_pixel_put(cub3d->img, x, y, cub3d->player->f_col);
}
