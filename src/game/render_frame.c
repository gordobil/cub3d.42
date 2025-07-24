/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/24 12:12:37 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	deg_to_rad(double ang)
{
	return (ang * M_PI / 180);
}

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
		draw_minimap(cub3d);
		draw_pointer(cub3d);
		mlx_put_image_to_window(cub3d->mlx, cub3d->window, img->img, 0, 0);
		mlx_destroy_image(cub3d->mlx, img->img);
	}
}

double	cast_single_ray(t_cub3d *cub3d, t_ray *ray, double angle)
{
	double	step;
	int		map_x;
	int		map_y;

	ray->rx = cub3d->player->x;
	ray->ry = cub3d->player->y;
	step = 1.0;
	while (1)
	{
		map_x = (int)(ray->rx / SQ);
		map_y = (int)(ray->ry / SQ);
		if (map_y < 0 || map_y >= matrix_size(cub3d->map)
			|| map_x < 0 || map_x >= (int)ft_strlen(cub3d->map[map_y])
			|| cub3d->map[map_y][map_x] == '1')
			break ;
		ray->rx += cos(deg_to_rad(angle)) * step;
		ray->ry += sin(deg_to_rad(angle)) * step;
	}
	return (sqrt((ray->rx - cub3d->player->x) * (ray->rx - cub3d->player->x)
			+ (ray->ry - cub3d->player->y) * (ray->ry - cub3d->player->y)));
}

int	render_frame(t_cub3d *cub3d, t_img *img, t_ray *ray)
{
	int		x;
	int		y;
	int		draw_start, draw_end;

	x = -1;
	img_management(cub3d, img, 0);
	while (++x < WD)
	{
		ray->angle = cub3d->player->ang - 30 + (x * (60.0 / WD));
		if (ray->angle < 0) ray->angle += 360;
		else if (ray->angle >= 360) ray->angle -= 360;
		ray->distance = cast_single_ray(cub3d, cub3d->ray, ray->angle)
			* cos(deg_to_rad(ray->angle - cub3d->player->ang));
		draw_start = (HE / 2) - (((int)((SQ * HE) / ray->distance)) / 2);
		draw_end = (HE / 2) + (((int)((SQ * HE) / ray->distance)) / 2);
		if (draw_start < 0) draw_start = 0;
		if (draw_end >= HE) draw_end = HE - 1;
		y = draw_start;
		while (y < draw_end)
		{
			draw_textures(cub3d, x, y);
			y++;
		}
	}
	img_management(cub3d, img, 1);
	return (0);
}

