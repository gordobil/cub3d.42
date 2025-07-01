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
	if (cub3d->img->img)
		free(cub3d->img->img);
	if (cub3d->img->addr)
		free(cub3d->img->addr);
	if (cub3d->img)
		free(cub3d->img);
}

int	free_cub3d(t_cub3d *cub3d)
{
	int	ret;

	ret = 0;
	if (cub3d->map_path)
		free(cub3d->map_path);
	if (cub3d->map_fd > 0)
		if (!close(cub3d->map_fd))
			ret += -1;
	if (cub3d->elements)
		ret += free_matrix(cub3d->elements);
	if (cub3d->map)
		ret += free_matrix(cub3d->map);
	if (cub3d->mlx)
		free(cub3d->mlx);
	if (cub3d->window)
		free(cub3d->window);
	if (cub3d->player)
		free(cub3d->player);
	if (cub3d->img)
		free_img(cub3d);
	if (ret != 0)
		return (error(ERROR_FATAL));
	return (0);
}

int	error(int code)
{
	if (code == ERROR_FATAL)
		ft_printf("Error\nFatal\n");
	else if (code == ERROR_ARGS)
		ft_printf("Error\nInvalid arguments\n");
	else if (code == ERROR_ELEMS)
		ft_printf("Error\nInvalid map elements\n");
	else if (code == ERROR_MAP)
		ft_printf("Error\nInvalid map\n");
	else if (code == ERROR_MLX)
		ft_printf("Error\nMinilbx error\n");
	return (1);
}
