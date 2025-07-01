/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/01 13:18:01 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	cast_single_ray(t_cub3d *cub3d, double angle)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	step;
	int		map_x;
	int		map_y;

	x = cub3d->player->x;
	y = cub3d->player->y;
	dx = cos(DEG_TO_RAD(angle));
	dy = sin(DEG_TO_RAD(angle));
	step = 1.0;
	while (1)
	{
		map_x = (int)(x / SQ);
		map_y = (int)(y / SQ);
		if (map_y < 0 || map_y >= matrix_size(cub3d->map)
			|| map_x < 0 || map_x >= (int)ft_strlen(cub3d->map[map_y])
			|| cub3d->map[map_y][map_x] == '1')
			break ;
		x += dx * step;
		y += dy * step;
	}
	return (sqrt((x - cub3d->player->x) * (x - cub3d->player->x)
			+ (y - cub3d->player->y) * (y - cub3d->player->y)));
}

int	render_frame(t_cub3d *cub3d)
{
	int		x;
	double	ray_angle;
	double	ray_step;
	double	distance;
	int		line_height;
	int		draw_start;
	int		draw_end;

	ray_step = 60.0 / WD;
	x = 0;
	//img->img = mlx_new_image(cub3d->mlx, WD, HE);
	//img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
	//		&img->line_length, &img->endian);
	while (x < WD)
	{
		ray_angle = cub3d->player->ang - 30 + (x * ray_step);
		if (ray_angle < 0)
			ray_angle += 360;
		if (ray_angle >= 360)
			ray_angle -= 360;
		distance = cast_single_ray(cub3d, ray_angle)
			* cos(DEG_TO_RAD(ray_angle - cub3d->player->ang));
		line_height = (int)((SQ * HE) / distance);
		draw_start = (HE / 2) - (line_height / 2);
		draw_end = (HE / 2) + (line_height / 2);
		draw_vertical_line(cub3d, x, draw_start, draw_end);
		x++;
	}
	//mlx_put_image_to_window(cub3d->mlx, cub3d->window, img->img, 0, 0);
	draw_minimap(cub3d);
	draw_pointer(cub3d);
	return (0);
}
