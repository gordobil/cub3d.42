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

int	free_cub3d(t_cub3d *cub3d)
{
	int	ret;

	ret = 0;
	if (cub3d->map_path != NULL)
		free(cub3d->map_path);
	if (cub3d->map_fd)
		if (!close(cub3d->map_fd))
			ret += -1;
	if (cub3d->elements)
		ret += free_matrix(cub3d->elements);
	if (cub3d->map)
		ret += free_matrix(cub3d->map);
	if (cub3d)
		free(cub3d);
	if (ret != 0)
		return (error(ERROR_FATAL));
	return (0);
}

int	error(int code)
{
	if (code == ERROR_FATAL)
		ft_printf("Error\nFatal.\n");
	else if (code == ERROR_ARGS)
		ft_printf("Error\nInvalid arguments.\n");
	else if (code == ERROR_MAP_ELEMS)
		ft_printf("Error\nInvalid map elements.\n");
	else if (code == ERROR_MAP)
		ft_printf("Error\nInvalid map.\n");
	return (1);
}
