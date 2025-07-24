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

int	destroy_textures(t_cub3d *cub3d, int t)
{
	if (t == 1)
		mlx_destroy_image(cub3d->mlx, cub3d->texture->north->img);
	else if (t == 2)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->texture->north->img);
		mlx_destroy_image(cub3d->mlx, cub3d->texture->south->img);
	}
	else if (t == 3)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->texture->north->img);
		mlx_destroy_image(cub3d->mlx, cub3d->texture->south->img);
		mlx_destroy_image(cub3d->mlx, cub3d->texture->west->img);
	}
	else if (t == 4)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->texture->north->img);
		mlx_destroy_image(cub3d->mlx, cub3d->texture->south->img);
		mlx_destroy_image(cub3d->mlx, cub3d->texture->west->img);
		mlx_destroy_image(cub3d->mlx, cub3d->texture->east->img);
		return (0);
	}
	return (ERROR_TEXTURES);
}

void	free_texture(t_cub3d *cub3d)
{
	if_free_str(cub3d->texture->north->path);
	if_free_ptr(cub3d->texture->north);
	if_free_str(cub3d->texture->south->path);
	if_free_ptr(cub3d->texture->south);
	if_free_str(cub3d->texture->west->path);
	if_free_ptr(cub3d->texture->west);
	if_free_str(cub3d->texture->east->path);
	if_free_ptr(cub3d->texture->east);
	if_free_ptr(cub3d->texture);
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
	if_free_ptr(cub3d->ray);
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
	else if (code == ERROR_ELEMS || code == ERROR_TEXTURES)
		ft_printf("Error\nInvalid file elements\n");
	else if (code == ERROR_MAP)
		ft_printf("Error\nInvalid map\n");
	else if (code == ERROR_MLX)
		ft_printf("Error\nMinilbx error\n");
	return (1);
}
