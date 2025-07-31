/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/31 14:12:12 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_texture_pixel(t_cub3d *cub3d, t_img *texture, int x, int y, int tx)
{
	unsigned int	color;
	int				ty;
	int				wall_height;

	if (!texture || !texture->addr)
		return;
	wall_height = (int)((SQ * HE) / cub3d->ray[x].distance);
	ty = ((y - (HE / 2 - wall_height / 2)) * texture->height) / wall_height;
	if (tx < 0 || tx >= texture->width || ty < 0 || ty >= texture->height)
		return ;
	color = (unsigned int)(texture->addr[x] + (ty * texture->line_length)
		+ (tx * (texture->bits_per_pixel / 8)));
	if (tx < 0 || tx >= texture->width || ty < 0 || ty >= texture->height)
		my_pixel_put(cub3d->img, x, y, 0x000000);
	else
		my_pixel_put(cub3d->img, x, y, color);
}

void	draw_north_texture(t_cub3d *cub3d, int x, int y)
{
	int texture_width = cub3d->texture->north->width - 1;
	int tx = (int)(cub3d->ray[x].rx * texture_width / SQ);
	tx = tx % texture_width;

	draw_texture_pixel(cub3d, cub3d->texture->north, x, y, tx);
}

void	draw_south_texture(t_cub3d *cub3d, int x, int y)
{
	int texture_width = cub3d->texture->south->width - 1;
	int tx = (int)(cub3d->ray[x].rx * texture_width / SQ);
	tx = texture_width - (tx % texture_width);

	draw_texture_pixel(cub3d, cub3d->texture->south, x, y, tx);
}


void	draw_west_texture(t_cub3d *cub3d, int x, int y)
{
	int texture_width = cub3d->texture->west->width - 1;
	int tx = (int)(cub3d->ray[x].ry * texture_width / SQ);
	tx = texture_width - (tx % texture_width);

	draw_texture_pixel(cub3d, cub3d->texture->west, x, y, tx);
}


void	draw_east_texture(t_cub3d *cub3d, int x, int y)
{
	int texture_width = cub3d->texture->east->width - 1;
	int tx = (int)(cub3d->ray[x].ry * texture_width / SQ);
	tx = tx % texture_width;

	draw_texture_pixel(cub3d, cub3d->texture->east, x, y, tx);
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
		if (cub3d->ray[x].type == 'h' && cub3d->ray[x].angle <= 315
			&& cub3d->ray[x].angle > 225)
			draw_north_texture(cub3d, x, y);
		else if (cub3d->ray->type == 'h' && cub3d->ray[x].angle <= 135
			&& cub3d->ray[x].angle > 45)
			draw_south_texture(cub3d, x, y);
		else if (cub3d->ray[x].type == 'v' && cub3d->ray[x].angle <= 225
			&& cub3d->ray[x].angle > 135)
			draw_west_texture(cub3d, x, y);
		else if (cub3d->ray[x].type == 'v' && cub3d->ray[x].angle < 360
			&& cub3d->ray[x].angle > 315 && cub3d->ray[x].angle > 0
			&& cub3d->ray[x].angle <= 45)
			draw_east_texture(cub3d, x, y);
	}
	y--;
	while (++y < HE)
		my_pixel_put(cub3d->img, x, y, cub3d->player->f_col);
}
