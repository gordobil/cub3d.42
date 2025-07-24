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
	cub3d->img->img = NULL;
	cub3d->img->addr = NULL;
	if_free_ptr(cub3d->mlx);
	free_cub3d(cub3d, 0);
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
	ft_printf("ang[%d] wall[%d]\n", old_ang, wall);
	if (cub3d->player->ang != old_ang || wall == 0)
		render_frame(cub3d, cub3d->img, cub3d->ray);
	return (0);
}

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
void	init_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->path = NULL;
}

int	init_textures(t_cub3d *cub3d)
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
	init_img(cub3d->texture->north);
	init_img(cub3d->texture->south);
	init_img(cub3d->texture->west);
	init_img(cub3d->texture->east);
	cub3d->texture->north->path = ft_strdup(cub3d->elements[0]);
	cub3d->texture->south->path = ft_strdup(cub3d->elements[1]);
	cub3d->texture->west->path = ft_strdup(cub3d->elements[2]);
	cub3d->texture->east->path = ft_strdup(cub3d->elements[3]);
	if (!cub3d->texture->north->path || !cub3d->texture->south->path
		|| !cub3d->texture->west->path || !cub3d->texture->east->path)
		return (ERROR_FATAL);
	if (load_texture(cub3d->texture->north, cub3d->mlx) != 0
		|| load_texture(cub3d->texture->south, cub3d->mlx) != 0
		|| load_texture(cub3d->texture->west, cub3d->mlx) != 0
		|| load_texture(cub3d->texture->east, cub3d->mlx) != 0)
		return (ERROR_TEXTURES);
	return (0);
}

int	mlx_management(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		return (ERROR_MLX);
	cub3d->window = mlx_new_window(cub3d->mlx, WD, HE, "cub3d");
	if (!cub3d->window)
		return (ERROR_MLX);
	cub3d->img = malloc(sizeof(t_img));
	cub3d->ray = malloc(sizeof(t_ray));
	if (!cub3d->img || !cub3d->ray)
		return (ERROR_FATAL);
	init_img(cub3d->img);
	if (init_textures(cub3d) != 0)
		return (ERROR_TEXTURES);
	cub3d->ray->type = 'h';
	render_frame(cub3d, cub3d->img, cub3d->ray);
	mlx_key_hook(cub3d->window, &handle_input, cub3d);
	mlx_hook(cub3d->window, 17, 1, close_window, cub3d);
	mlx_loop(cub3d->mlx);
	return (0);
}
