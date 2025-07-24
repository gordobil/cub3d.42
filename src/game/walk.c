/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/24 12:12:12 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_walkable(t_cub3d *cub3d, int new_x, int new_y)
{
	int		map_x;
	int		map_y;
	char	tile;

	if (new_x < 0 || new_y < 0)
		return (0);
	map_x = new_x / SQ;
	map_y = new_y / SQ;
	if (map_y < 0 || map_y >= matrix_size(cub3d->map)
		|| map_x < 0 || map_x >= (int)ft_strlen(cub3d->map[map_y]))
		return (0);
	tile = cub3d->map[map_y][map_x];
	if (tile == '1')
		return (0);
	return (1);
}

int	walk_forwards(t_cub3d *cub3d)
{
	double	new_x;
	double	new_y;

	new_x = cub3d->player->x
		+ cos(deg_to_rad(cub3d->player->ang)) * cub3d->player->speed;
	new_y = cub3d->player->y
		+ sin(deg_to_rad(cub3d->player->ang)) * cub3d->player->speed;
	if (is_walkable(cub3d, new_x, new_y))
	{
		cub3d->player->x = new_x;
		cub3d->player->y = new_y;
		cub3d->ray->type = 'h';
		return (0);
	}
	return (1);
}

int	walk_backwards(t_cub3d *cub3d)
{
	double	new_x;
	double	new_y;

	new_x = cub3d->player->x
		- cos(deg_to_rad(cub3d->player->ang)) * cub3d->player->speed;
	new_y = cub3d->player->y
		- sin(deg_to_rad(cub3d->player->ang)) * cub3d->player->speed;
	if (is_walkable(cub3d, new_x, new_y))
	{
		cub3d->player->x = new_x;
		cub3d->player->y = new_y;
		cub3d->ray->type = 'h';
		return (0);
	}
	return (1);
}

int	walk_right(t_cub3d *cub3d)
{
	double	new_x;
	double	new_y;

	new_x = cub3d->player->x
		- sin(deg_to_rad(cub3d->player->ang)) * cub3d->player->speed;
	new_y = cub3d->player->y
		- cos(deg_to_rad(cub3d->player->ang)) * cub3d->player->speed;
	if (is_walkable(cub3d, new_x, new_y))
	{
		cub3d->player->x = new_x;
		cub3d->player->y = new_y;
		cub3d->ray->type = 'v';
		return (0);
	}
	return (1);
}

int	walk_left(t_cub3d *cub3d)
{
	double	new_x;
	double	new_y;

	new_x = cub3d->player->x
		+ sin(deg_to_rad(cub3d->player->ang)) * cub3d->player->speed;
	new_y = cub3d->player->y
		+ cos(deg_to_rad(cub3d->player->ang)) * cub3d->player->speed;
	if (is_walkable(cub3d, new_x, new_y))
	{
		cub3d->player->x = new_x;
		cub3d->player->y = new_y;
		cub3d->ray->type = 'v';
		return (0);
	}
	return (1);
}
