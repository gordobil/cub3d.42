/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/24 12:11:33 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_texture_color(t_img *texture, int tx, int ty)
{
	char	*pixel;
	int		color;

	if (tx < 0 || tx >= texture->width || ty < 0 || ty >= texture->height)
		return (0x000000);
	pixel = texture->addr + (ty * texture->line_length
			+ tx * (texture->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	draw_texture_pixel(t_cub3d *cub3d, t_img *texture, int x, int y, int tx)
{
	int	ty;
	int	color;
	int	wall_height;

	if (!texture || !texture->addr)
		return;
	wall_height = (int)((SQ * HE) / cub3d->ray[x].distance);
	ty = ((y - (HE / 2 - wall_height / 2)) * texture->height) / wall_height;
	if (tx < 0 || tx >= texture->width || ty < 0 || ty >= texture->height)
		return;
	color = *(int *)(texture->addr + (ty * texture->line_length
			+ tx * (texture->bits_per_pixel / 8)));
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


void	draw_textures(t_cub3d *cub3d, int x, int y)
{
    printf("entro\n");
	if (cub3d->ray[x].type == 'h' && cub3d->ray[x].angle < M_PI)
    {
        printf("Paso_North\n");
		draw_north_texture(cub3d, x, y);
    }
	else if (cub3d->ray[x].type == 'h')
    {
        printf("Paso_Shouth\n");
		draw_south_texture(cub3d, x, y);
    }
	else if (cub3d->ray[x].type == 'v'
		&& (cub3d->ray[x].angle < 90 * M_PI / 180
		|| cub3d->ray[x].angle > 270 * M_PI / 180))
		draw_west_texture(cub3d, x, y);
	else
		draw_east_texture(cub3d, x, y);
}
