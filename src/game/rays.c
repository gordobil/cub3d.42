/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/08/01 16:16:24 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	get_ray_v(t_cub3d *cub3d, t_ray *ray, double angle)
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
	ray->distance = sqrt((ray->rx - cub3d->player->x) \
			* (ray->rx - cub3d->player->x) + (ray->ry - cub3d->player->y) \
			* (ray->ry - cub3d->player->y));
}

void	get_ray_h(t_cub3d *cub3d, t_ray *ray, double angle)
{
	ray->rx = 0;
	ray->ry = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	if (angle > M_PI)
	{
		ray->ry = (((int)(cub3d->player->y / SQ)) * SQ) - 0.0001;
		ray->rx = (cub3d->player->y - ray->ry) * -1
			/ tan(angle) + cub3d->player->x;
		ray->delta_y = -SQ;
		ray->delta_x = -ray->delta_y * -1 / tan(angle);
	}
	if (angle < M_PI)
	{
		ray->ry = (((int)(cub3d->player->y / SQ) + 1) * SQ);
		ray->rx = (cub3d->player->y - ray->ry) * -1
			/ tan(angle) + cub3d->player->x;
		ray->delta_y = SQ;
		ray->delta_x = -ray->delta_y * -1 / tan(angle);
	}
	resolve_ray(cub3d, ray);
	ray->distance = sqrt((ray->rx - cub3d->player->x) \
			* (ray->rx - cub3d->player->x) + (ray->ry - cub3d->player->y) \
			* (ray->ry - cub3d->player->y));
}

double	cast_single_ray(t_cub3d *cub3d, t_ray *ray, double angle)
{
	t_ray	ray_h;
	t_ray	ray_v;

	get_ray_v(cub3d, &ray_v, angle);
	get_ray_h(cub3d, &ray_h, angle);
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
	return (sqrt((ray->rx - cub3d->player->x) * (ray->rx - cub3d->player->x) \
			+ (ray->ry - cub3d->player->y) * (ray->ry - cub3d->player->y)));
}
