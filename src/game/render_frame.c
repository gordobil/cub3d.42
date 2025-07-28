/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/24 13:49:12 by ngordobi         ###   ########.fr       */
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

double	cast_single_ray(t_cub3d *cub3d, int rayx, double angle)
{
	double		x, y;
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
		x += cos(deg_to_rad(angle)) * step;
		y += sin(deg_to_rad(angle)) * step;
	}
	cub3d->ray[rayx].rx = x;
	cub3d->ray[rayx].ry = y;
	cub3d->ray[rayx].type = 'v';
	if ((int)x % 32 == 0 && (int)y % 32 != 0)
		cub3d->ray[rayx].type = 'h';
	return (sqrt((x - cub3d->player->x) * (x - cub3d->player->x)
			+ (y - cub3d->player->y) * (y - cub3d->player->y)));
}

int	render_frame(t_cub3d *cub3d, t_img *img, t_ray *ray)
{
	int		x;
	int		draw_start;
	int		draw_end;

	x = -1;
	img_management(cub3d, img, 0);
	while (++x < WD)
	{
		ray[x].angle = cub3d->player->ang - 30 + (x * (60.0 / WD));
		if (ray[x].angle < 0)
			ray[x].angle += 360;
		else if (ray[x].angle >= 360)
			ray[x].angle -= 360;
		ray[x].distance = cast_single_ray(cub3d, x, ray[x].angle)
			* cos(deg_to_rad(ray[x].angle - cub3d->player->ang));
		draw_start = (HE / 2) - (((int)((SQ * HE) / ray[x].distance)) / 2);
		draw_end = (HE / 2) + (((int)((SQ * HE) / ray[x].distance)) / 2);
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= HE)
			draw_end = HE - 1;
		for(int i = draw_start; i < draw_end; i++)
			draw_textures(cub3d, x, i);
	}
	img_management(cub3d, img, 1);
	return (0);
}
