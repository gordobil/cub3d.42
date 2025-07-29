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
	destroy_textures(cub3d, 4);
	mlx_destroy_window(cub3d->mlx, cub3d->window);
	mlx_destroy_display(cub3d->mlx);
	cub3d->img->img = NULL;
	cub3d->img->addr = NULL;
	if_free_ptr(cub3d->mlx);
	free_cub3d(cub3d, 0);
	exit(0);
	return (0);
}

int	move_and_draw(t_cub3d *cub3d)
{
	int	old_ang;
	int	wall;

	old_ang = cub3d->player->ang;
	wall = 1;
	if (cub3d->r_key == 1)
		get_angle(cub3d, '+');
	if (cub3d->l_key == 1)
		get_angle(cub3d, '-');
	if (cub3d->w_key == 1)
		wall = walk_forwards(cub3d);
	if (cub3d->s_key == 1)
		wall = walk_backwards(cub3d);
	if (cub3d->d_key == 1)
		wall = walk_right(cub3d);
	if (cub3d->a_key == 1)
		wall = walk_left(cub3d);
	if (cub3d->player->ang != old_ang || wall == 0)
		render_frame(cub3d, cub3d->img, cub3d->ray);
	return (0);
}

int	handle_release(int keysym, t_cub3d *cub3d)
{
	if (keysym == RIGHT)
		cub3d->r_key = 0;
	if (keysym == LEFT)
		cub3d->l_key = 0;
	if (keysym == W)
		cub3d->w_key = 0;
	if (keysym == S)
		cub3d->s_key = 0;
	if (keysym == D)
		cub3d->d_key = 0;
	if (keysym == A)
		cub3d->a_key = 0;
	return (0);
}

int	handle_input(int keysym, t_cub3d *cub3d)
{
	if (keysym == Q || keysym == ESC)
		close_window(cub3d);
	if (keysym == RIGHT)
		cub3d->r_key = 1;
	if (keysym == LEFT)
		cub3d->l_key = 1;
	if (keysym == W)
		cub3d->w_key = 1;
	if (keysym == S)
		cub3d->s_key = 1;
	if (keysym == D)
		cub3d->d_key = 1;
	if (keysym == A)
		cub3d->a_key = 1;
	return (0);
}

int	mlx_management(t_cub3d *cub3d)
{
	cub3d->img = malloc(sizeof(t_img));
	if (!cub3d->img)
		return (ERROR_FATAL);
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		return (if_free_ptr(cub3d->img), ERROR_MLX);
	if (init_textures(cub3d) != 0)
		return (mlx_destroy_display(cub3d->mlx), if_free_ptr(cub3d->mlx),
			if_free_ptr(cub3d->img), ERROR_TEXTURES);
	cub3d->window = mlx_new_window(cub3d->mlx, WD, HE, "cub3d");
	if (!cub3d->window)
		return (mlx_destroy_display(cub3d->mlx), destroy_textures(cub3d, 4),
			if_free_ptr(cub3d->mlx), if_free_ptr(cub3d->img), ERROR_MLX);
	render_frame(cub3d, cub3d->img, cub3d->ray);
	mlx_hook(cub3d->window, 2, 1L<<0, handle_input, cub3d);
	mlx_hook(cub3d->window, 3, 1L<<1, handle_release, cub3d);
	mlx_hook(cub3d->window, 17, 1, close_window, cub3d);
	mlx_loop_hook(cub3d->mlx, move_and_draw, cub3d);
	mlx_loop(cub3d->mlx);
	return (mlx_destroy_display(cub3d->mlx),
		mlx_destroy_window(cub3d->mlx, cub3d->window),
		if_free_ptr(cub3d->mlx), if_free_ptr(cub3d->window), 0);
}
