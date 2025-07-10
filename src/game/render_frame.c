/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/10 13:14:57 by ngordobi         ###   ########.fr       */
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
		draw_minimap(cub3d);
		draw_pointer(cub3d);
		mlx_put_image_to_window(cub3d->mlx, cub3d->window, img->img, 0, 0);
	}
}

double	cast_single_ray(t_cub3d *cub3d, double angle)
{
	double	x;
	double	y;
	double	step;
	int		map_x;
	int		map_y;

	x = cub3d->player->x;
	y = cub3d->player->y;
	step = 1.0;
	while (1)
	{
		map_x = (int)(x / SQ);
		map_y = (int)(y / SQ);
		if (map_y < 0 || map_y >= matrix_size(cub3d->map)
			|| map_x < 0 || map_x >= (int)ft_strlen(cub3d->map[map_y])
			|| cub3d->map[map_y][map_x] == '1')
			break ;
		x += cos(DEG_TO_RAD(angle)) * step;
		y += sin(DEG_TO_RAD(angle)) * step;
	}
	return (sqrt((x - cub3d->player->x) * (x - cub3d->player->x)
			+ (y - cub3d->player->y) * (y - cub3d->player->y)));
}

int	render_frame(t_cub3d *cub3d, t_img *img)
{
	int		x;
	double	ray_angle;
	double	distance;
	int		draw_start;
	int		draw_end;

	x = -1;
	img_management(cub3d, img, 0);
	while (++x < WD)
	{
		ray_angle = cub3d->player->ang - 30 + (x * (60.0 / WD));
		if (ray_angle < 0)
			ray_angle += 360;
		else if (ray_angle >= 360)
			ray_angle -= 360;
		distance = cast_single_ray(cub3d, ray_angle)
			* cos(DEG_TO_RAD(ray_angle - cub3d->player->ang));
		draw_start = (HE / 2) - (((int)((SQ * HE) / distance)) / 2);
		draw_end = (HE / 2) + (((int)((SQ * HE) / distance)) / 2);
		draw_vertical_line(cub3d, x, draw_start, draw_end);
	}
	img_management(cub3d, img, 1);
	return (0);
}
