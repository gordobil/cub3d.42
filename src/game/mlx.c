/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/05/06 11:32:29 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_window(t_cub3d *cub3d)
{
	mlx_destroy_window(cub3d->mlx, cub3d->window);
	mlx_destroy_display(cub3d->mlx);
	exit(0);
	return (0);
}

int	handle_input(int keysym, t_cub3d *cub3d)
{
	int	old_ang;
	int	wall;

	old_ang = cub3d->player->ang;
	wall = 1;
	if (keysym == Q || keysym == ESC)
		close_window(cub3d);
	else if (keysym == RIGHT)
		cub3d->player->ang = (cub3d->player->ang + 1) % 360;
	else if (keysym == LEFT)
		cub3d->player->ang = (cub3d->player->ang + 359) % 360;
	else if (keysym == W)
		wall = walk_forwards(cub3d);
	else if (keysym == S)
		wall = walk_backwards(cub3d);
	else if (keysym == D)
		wall = walk_right(cub3d);
	else if (keysym == A)
		wall = walk_left(cub3d);
	if (cub3d->player->ang != old_ang || wall == 0)
		render_frame(cub3d, cub3d->img);
	return (0);
}

int	mlx_management(t_cub3d *cub3d)
{
	cub3d->img = malloc(sizeof(t_img));
	if (!cub3d->img)
		return (ERROR_FATAL);
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		return (ERROR_MLX);
	cub3d->window = mlx_new_window(cub3d->mlx, WD, HE, "cub3d");
	if (!cub3d->window)
		return (ERROR_MLX);
	render_frame(cub3d, cub3d->img);
	mlx_key_hook(cub3d->window, &handle_input, cub3d);
	mlx_hook(cub3d->window, 17, 1, close_window, cub3d);
	mlx_loop(cub3d->mlx);
	return (free(cub3d->mlx), free(cub3d->window), 0);
}
