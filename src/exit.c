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

void	free_img(t_cub3d *cub3d)
{
	if_free_ptr(cub3d->img->img);
	if_free(cub3d->img->addr);
	if_free_ptr(cub3d->img->north);
	if_free_ptr(cub3d->img->south);
	if_free_ptr(cub3d->img->west);
	if_free_ptr(cub3d->img->east);
	if_free_ptr(cub3d->img);
}

void	free_mlx(t_cub3d *cub3d)
{
	if_free_ptr(cub3d->mlx);
	if_free_ptr(cub3d->window);
}

int	free_cub3d(t_cub3d *cub3d, int er)
{
	int	ret;

	ret = 0;
	if (cub3d->elements)
		ret += free_matrix(cub3d->elements);
	if (cub3d->map)
		ret += free_matrix(cub3d->map);
	if (er == ERROR_MLX || er == ERROR_TEXTURES)
		free_mlx(cub3d);
	if (cub3d->player)
		free(cub3d->player);
	if (cub3d->img)
		free_img(cub3d);
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
