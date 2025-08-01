/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/08/01 11:25:48 by ngordobi         ###   ########.fr       */
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

void	resolve_ray(t_cub3d *cub3d, t_ray *ray)
{
	int			max_depth;
	int			depth;
	int			map_x;
	int			map_y;

	max_depth = 25;
	depth = 0;
	while (depth < max_depth)
	{
		map_x = ray->rx / SQ;
		map_y = ray->ry / SQ;
		if (map_y < 0 || map_y >= matrix_size(cub3d->map)
			|| map_x < 0 || map_x >= (int)ft_strlen(cub3d->map[map_y])
			|| cub3d->map[map_y][map_x] == '1')
			break ;
		else
		{
			ray->rx += ray->delta_x;
			ray->ry += ray->delta_y;
			depth++;
		}
	}
}

void	make_ray_v(t_cub3d *cub3d, t_ray *ray, double angle)
{
	ray->rx = 0;
	ray->ry = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	if (angle >= M_PI / 2 && angle <= M_PI * 3 / 2)
	{
		ray->rx = (((int)(cub3d->player->x / SQ)) * SQ) - 0.0001;
		ray->ry = (cub3d->player->x - ray->rx) * -tan(angle) + cub3d->player->y;
		ray->delta_x = -SQ;
		ray->delta_y = -ray->delta_x * -tan(angle);
	}
	if (angle < M_PI / 2 || angle > M_PI * 3 / 2)
	{
		ray->rx = (((int)(cub3d->player->x / SQ) + 1) * SQ);
		ray->ry = (cub3d->player->x - ray->rx) * -tan(angle) + cub3d->player->y;
		ray->delta_x = SQ;
		ray->delta_y = -ray->delta_x * -tan(angle);
	}
	resolve_ray(cub3d, ray);
	ray->distance = sqrt((ray->rx - cub3d->player->x)
			* (ray->rx - cub3d->player->x) + (ray->ry - cub3d->player->y)
			* (ray->ry - cub3d->player->y));
}

void	make_ray_h(t_cub3d *cub3d, t_ray *ray, double angle)
{
	ray->rx = 0;
	ray->ry = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	if (angle > M_PI)
	{
		ray->ry = (((int)(cub3d->player->y / SQ)) * SQ) - 0.0001;
		ray->rx = (cub3d->player->y - ray->ry) * -1 / tan(angle) + cub3d->player->x;
		ray->delta_y = -SQ;
		ray->delta_x = -ray->delta_y * -1 / tan(angle);
	}
	if (angle < M_PI)
	{
		ray->ry = (((int)(cub3d->player->y / SQ) + 1) * SQ);
		ray->rx = (cub3d->player->y - ray->ry) * -1 / tan(angle) + cub3d->player->x;
		ray->delta_y = SQ;
		ray->delta_x = -ray->delta_y * -1 / tan(angle);
	}
	resolve_ray(cub3d, ray);
	ray->distance = sqrt((ray->rx - cub3d->player->x) * (ray->rx - cub3d->player->x)
	+ (ray->ry - cub3d->player->y) * (ray->ry - cub3d->player->y));
}

double cast_single_ray(t_cub3d *cub3d, t_ray *ray, double angle)
{
	t_ray	ray_h;
	t_ray	ray_v;

	make_ray_v(cub3d, &ray_v, angle);
	make_ray_h(cub3d, &ray_h, angle);

	if (ray_h.distance < ray_v.distance)
	{
		ray->rx = ray_h.rx;
		ray->ry = ray_h.ry;
		ray->type = 'h';
	}
	else
	{
		ray->rx = ray_v.rx;
		ray->ry = ray_v.ry;
		ray->type = 'v';
	}
	return (sqrt((ray->rx - cub3d->player->x) * (ray->rx - cub3d->player->x)
		+ (ray->ry - cub3d->player->y) * (ray->ry - cub3d->player->y)));
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
		ray[x].distance = cast_single_ray(cub3d, &cub3d->ray[x], deg_to_rad(ray[x].angle))
			* cos(deg_to_rad(ray[x].angle - cub3d->player->ang));
		draw_start = (HE / 2) - (((int)((SQ * HE) / ray[x].distance)) / 2);
		draw_end = (HE / 2) + (((int)((SQ * HE) / ray[x].distance)) / 2);
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= HE)
			draw_end = HE - 1;
		draw_textures(cub3d, x, draw_start, draw_end);
	}
	img_management(cub3d, img, 1);
	return (0);
}
