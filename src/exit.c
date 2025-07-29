/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:15:33 by ngordobi          #+#    #+#             */
/*   Updated: 2025/04/16 12:15:33 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	destroy_texturesss(t_cub3d *cub3d, int t)
{
	if (t == 1)
		mlx_destroy_image(cub3d->mlx, cub3d->textures->north->img);
	else if (t == 2)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->textures->north->img);
		mlx_destroy_image(cub3d->mlx, cub3d->textures->south->img);
	}
	else if (t == 3)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->textures->north->img);
		mlx_destroy_image(cub3d->mlx, cub3d->textures->south->img);
		mlx_destroy_image(cub3d->mlx, cub3d->textures->west->img);
	}
	else if (t == 4)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->textures->north->img);
		mlx_destroy_image(cub3d->mlx, cub3d->textures->south->img);
		mlx_destroy_image(cub3d->mlx, cub3d->textures->west->img);
		mlx_destroy_image(cub3d->mlx, cub3d->textures->east->img);
		return (0);
	}
	return (ERROR_texturesS);
}

void	free_textures(t_cub3d *cub3d)
{
	if_free_str(cub3d->textures->north->path);
	if_free_ptr(cub3d->textures->north);
	if_free_str(cub3d->textures->south->path);
	if_free_ptr(cub3d->textures->south);
	if_free_str(cub3d->textures->west->path);
	if_free_ptr(cub3d->textures->west);
	if_free_str(cub3d->textures->east->path);
	if_free_ptr(cub3d->textures->east);
	if_free_ptr(cub3d->textures);
}

int	free_cub3d(t_cub3d *cub3d, int er)
{
	int	ret;

	ret = 0;
	if (cub3d->elements)
		ret += free_matrix(cub3d->elements);
	if (cub3d->map)
		ret += free_matrix(cub3d->map);
	if_free_ptr(cub3d->player);
	if_free_ptr(cub3d->img);
	if (cub3d->texture)
		free_texture(cub3d);
	ft_bzero(cub3d->ray, WD);
	if (cub3d)
		free(cub3d);
	if (ret != 0)
		return (error(ERROR_FATAL));
	return (error(er), 0);
}

int	error(int code)
{
	if (code == 0)
		return (0);
	if (code == ERROR_FATAL)
		ft_printf("Error\nFatal\n");
	else if (code == ERROR_ARGS)
		ft_printf("Error\nInvalid arguments\n");
	else if (code == ERROR_ELEMS)
		ft_printf("Error\nInvalid file elements\n");
	else if (code == ERROR_texturesS)
		ft_printf("Error\ntextures error\n");
	else if (code == ERROR_MAP)
		ft_printf("Error\nInvalid map\n");
	else if (code == ERROR_MLX)
		ft_printf("Error\nMinilbx error\n");
	return (1);
}
