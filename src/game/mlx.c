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
	cub3d->mlx = NULL;
	if_free_ptr(cub3d->mlx);
	free_cub3d(cub3d, 0);
	exit(0);
	return (0);
}

int	move_and_draw(t_cub3d *cub3d)
{
	double	old_ang;
	int		wall;

	old_ang = cub3d->player->ang;
	wall = 1;
	if (cub3d->r_key == 1)
		cub3d->player->ang = get_angle(cub3d->player->ang, '+');
	if (cub3d->l_key == 1)
		cub3d->player->ang = get_angle(cub3d->player->ang, '-');
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

int	game_init_errors(t_cub3d *cub3d, int error)
{
	if (error == 1)
	{
		cub3d->img = NULL;
		return (ERROR_FATAL);
	}
	else if (error == 2)
	{
		free (cub3d->img);
		cub3d->img = NULL;
		return (ERROR_MLX);
	}
	else if (error == 3)
	{
		free (cub3d->img);
		cub3d->img = NULL;
		return (mlx_destroy_display(cub3d->mlx),
			if_free_ptr(cub3d->mlx), ERROR_TEXTURES);
	}
	else if (error == 4)
		return (mlx_destroy_display(cub3d->mlx), destroy_textures(cub3d, 4),
			if_free_ptr(cub3d->mlx), if_free_ptr(cub3d->img), ERROR_MLX);
	return (0);
}

int	mlx_management(t_cub3d *cub3d)
{
	cub3d->img = malloc(sizeof(t_img));
	if (!cub3d->img)
		return (game_init_errors(cub3d, 1));
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		return (game_init_errors(cub3d, 2));
	if (init_textures(cub3d) != 0)
		return (game_init_errors(cub3d, 3));
	cub3d->window = mlx_new_window(cub3d->mlx, WD, HE, "cub3d");
	if (!cub3d->window)
		return (game_init_errors(cub3d, 4));
	render_frame(cub3d, cub3d->img, cub3d->ray);
	mlx_hook(cub3d->window, 2, 1L << 0, handle_input, cub3d);
	mlx_hook(cub3d->window, 3, 1L << 1, handle_release, cub3d);
	mlx_hook(cub3d->window, 17, 1, close_window, cub3d);
	mlx_loop_hook(cub3d->mlx, move_and_draw, cub3d);
	mlx_loop(cub3d->mlx);
	return (mlx_destroy_window(cub3d->mlx, cub3d->window),
		mlx_destroy_display(cub3d->mlx), 0);
}
