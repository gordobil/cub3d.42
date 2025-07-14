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

int	init_textures(t_cub3d *cub3d, t_img *img)
{
	int	w;
	int	h;

	img->north = mlx_xpm_file_to_image(cub3d->mlx, cub3d->elements[0], &w, &h);
	img->south = mlx_xpm_file_to_image(cub3d->mlx, cub3d->elements[1], &w, &h);
	img->west = mlx_xpm_file_to_image(cub3d->mlx, cub3d->elements[2], &w, &h);
	img->east = mlx_xpm_file_to_image(cub3d->mlx, cub3d->elements[3], &w, &h);
	if (!img->north || !img->south || !img->west || !img->east)
		return (ERROR_TEXTURES);
	return (0);
}

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
	if (keysym == D || keysym == RIGHT) {
		cub3d->player->ang = (cub3d->player->ang + 1) % 360;
		ft_printf("angle: %d\n", cub3d->player->ang);}
	else if (keysym == A || keysym == LEFT) {
		cub3d->player->ang = (cub3d->player->ang + 359) % 360;
		ft_printf("angle: %d\n", cub3d->player->ang);}
	if (keysym == W || keysym == UP)
		wall = walk_forwards(cub3d);
	else if (keysym == S || keysym == DOWN)
		wall = walk_backwards(cub3d);
	if (cub3d->player->ang != old_ang || wall == 0)
		render_frame(cub3d, cub3d->img);
	return (0);
}

int	mlx_management(t_cub3d cub3d)
{
	cub3d.mlx = mlx_init();
	if (!cub3d.mlx)
		return (ERROR_MLX);
	cub3d.window = mlx_new_window(cub3d.mlx, WD, HE, "cub3d");
	if (!cub3d.window)
		return (ERROR_MLX);
	/* if (init_textures(&cub3d, cub3d.img) != 0)
		return (ERROR_TEXTURES); */
	render_frame(&cub3d, cub3d.img);
	mlx_key_hook(cub3d.window, &handle_input, &cub3d);
	mlx_hook(cub3d.window, 17, 1, close_window, &cub3d);
	mlx_loop(cub3d.mlx);
	return (free(cub3d.mlx), free(cub3d.window), 0);
}
