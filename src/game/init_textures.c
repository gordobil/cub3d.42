/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/31 12:45:29 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	load_texture(t_img *t, void *mlx)
{
	t->img = mlx_xpm_file_to_image(mlx, t->path, &t->width, &t->height);
	if (!t->img)
		return (ERROR_TEXTURES);
	t->addr = mlx_get_data_addr(t->img, &t->bits_per_pixel,
			&t->line_length, &t->endian);
	if (!t->addr)
		return (ERROR_TEXTURES);
	return (0);
}

int	reserve_textures(t_cub3d *cub3d)
{
	cub3d->texture = malloc(sizeof(t_texture));
	if (!cub3d->texture)
		return (ERROR_FATAL);
	cub3d->texture->north = NULL;
	cub3d->texture->south = NULL;
	cub3d->texture->west = NULL;
	cub3d->texture->east = NULL;
	cub3d->texture->north = malloc(sizeof(t_img));
	cub3d->texture->south = malloc(sizeof(t_img));
	cub3d->texture->west = malloc(sizeof(t_img));
	cub3d->texture->east = malloc(sizeof(t_img));
	if (!cub3d->texture->north || !cub3d->texture->south
		|| !cub3d->texture->west || !cub3d->texture->east)
		return (ERROR_FATAL);
	return (0);
}

int	init_textures(t_cub3d *cub3d)
{
	if (reserve_textures(cub3d) != 0)
		return (ERROR_FATAL);
	cub3d->texture->north->path = ft_strdup(cub3d->elements[0]);
	cub3d->texture->south->path = ft_strdup(cub3d->elements[1]);
	cub3d->texture->west->path = ft_strdup(cub3d->elements[2]);
	cub3d->texture->east->path = ft_strdup(cub3d->elements[3]);
	if (!cub3d->texture->north->path || !cub3d->texture->south->path
		|| !cub3d->texture->west->path || !cub3d->texture->east->path)
		return (ERROR_FATAL);
	if (load_texture(cub3d->texture->north, cub3d->mlx) != 0)
		return (ERROR_TEXTURES);
	if (load_texture(cub3d->texture->south, cub3d->mlx) != 0)
		return (destroy_textures(cub3d, 1));
	if (load_texture(cub3d->texture->west, cub3d->mlx) != 0)
		return (destroy_textures(cub3d, 2));
	if (load_texture(cub3d->texture->east, cub3d->mlx) != 0)
		return (destroy_textures(cub3d, 3));
	return (0);
}
