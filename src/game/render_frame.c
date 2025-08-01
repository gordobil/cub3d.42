/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/08/01 12:41:45 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	img_management(t_cub3d *cub3d, t_img *img, int mark)
{
	if (mark == 0)
	{
		img->img = mlx_new_image(cub3d->mlx, WD, HE);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
				&img->line_length, &img->endian);
	}
	else if (mark == 1)
	{
		mlx_clear_window(cub3d->mlx, cub3d->window);
		draw_pointer(cub3d);
		draw_minimap(cub3d);
		mlx_put_image_to_window(cub3d->mlx, cub3d->window, img->img, 0, 0);
		mlx_destroy_image(cub3d->mlx, img->img);
	}
}

void	render_frame(t_cub3d *cub3d, t_img *img, t_ray *ray)
{
	int		x;
	int		draw_start;
	int		draw_end;

	x = -1;
	img_management(cub3d, img, 0);
	while (++x < WD)
	{
		ray[x].angle = cub3d->player->ang - 30 + (x * (60.0 / WD));
		ray[x].angle = get_angle(ray[x].angle, 0);
		ray[x].distance = cast_single_ray(cub3d, &cub3d->ray[x],
				deg_to_rad(ray[x].angle)) * cos(deg_to_rad(ray[x].angle
					- cub3d->player->ang));
		draw_start = (HE / 2) - (((int)((SQ * HE) / ray[x].distance)) / 2);
		draw_end = (HE / 2) + (((int)((SQ * HE) / ray[x].distance)) / 2);
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= HE)
			draw_end = HE - 1;
		draw_textures(cub3d, x, draw_start, draw_end);
	}
	img_management(cub3d, img, 1);
}
