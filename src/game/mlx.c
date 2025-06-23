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

int	get_matrix_height(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	is_walkable(t_cub3d *cub3d, int new_x, int new_y)
{
	int		map_x;
	int		map_y;
	char	tile;

	if (new_x < 0 || new_y < 0)
		return (0);
	map_x = new_x / SQ;
	map_y = new_y / SQ;
	if (map_y < 0 || map_y >= get_matrix_height(cub3d->map)
		|| map_x < 0 || map_x >= (int)ft_strlen(cub3d->map[map_y]))
		return (0);
	tile = cub3d->map[map_y][map_x];
	printf("is_walkable -> player: (%d, %d) -> cell: (%d, %d) = '%c'\n",
		new_x, new_y, map_x, map_y, tile);
	if (tile == '1')
		return (0);
	return (1);
}

double	cast_single_ray(t_cub3d *cub3d, double angle)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	step;

	x = cub3d->player->x;
	y = cub3d->player->y;
	dx = cos(DEG_TO_RAD(angle));
	dy = sin(DEG_TO_RAD(angle));
	step = 1.0;
	while (1)
	{
		int map_x = (int)(x / SQ);
		int map_y = (int)(y / SQ);
		if (map_y < 0 || map_y >= get_matrix_height(cub3d->map)
			|| map_x < 0 || map_x >= (int)ft_strlen(cub3d->map[map_y])
			|| cub3d->map[map_y][map_x] == '1')
			break ;
		x += dx * step;
		y += dy * step;
	}
	return (sqrt((x - cub3d->player->x) * (x - cub3d->player->x)
			+ (y - cub3d->player->y) * (y - cub3d->player->y)));
}

void	draw_vertical_line(t_cub3d *cub3d, int x, int start, int end, int clr)
{
	int	y;

	y = start;
	while (y < end)
	{
		mlx_pixel_put(cub3d->mlx, cub3d->window, x, y, clr);
		y++;
	}
}


int	render_frame(t_cub3d *cub3d)
{
	int		x;
	double	ray_angle;
	double	ray_step;
	double	distance;
	double	corrected_distance;
	int		line_height;
	int		draw_start;
	int		draw_end;

	ray_step = 60.0 / WD;
	x = 0;
	mlx_clear_window(cub3d->mlx, cub3d->window);
	while (x < WD)
	{
		ray_angle = cub3d->player->ang - 30 + (x * ray_step);
		if (ray_angle < 0)
			ray_angle += 360;
		if (ray_angle >= 360)
			ray_angle -= 360;
		distance = cast_single_ray(cub3d, ray_angle);
		corrected_distance = distance
			* cos(DEG_TO_RAD(ray_angle - cub3d->player->ang));
		line_height = (int)((SQ * HE) / corrected_distance);
		draw_start = (HE / 2) - (line_height / 2);
		draw_end = (HE / 2) + (line_height / 2);
		draw_vertical_line(cub3d, x, draw_start, draw_end, WHITE);
		x++;
	}
	draw_minimap(cub3d);
	return (0);
}

int	handle_input(int keysym, t_cub3d *cub3d)
{
	int	new_x;
	int	new_y;

	new_x = 0;
	new_y = 0;
	if (keysym == Q || keysym == ESC)
		close_window(cub3d);
	if (keysym == W || keysym == UP)
	{
		new_x = cub3d->player->x
			+ cos(DEG_TO_RAD(cub3d->player->ang)) * cub3d->player->speed;
		new_y = cub3d->player->y
			+ sin(DEG_TO_RAD(cub3d->player->ang)) * cub3d->player->speed;
		if (is_walkable(cub3d, new_x, new_y))
		{
			printf("Entro %d\n", new_y);
			cub3d->player->x = new_x;
			cub3d->player->y = new_y;
			render_frame(cub3d);
		}
		else
			printf("No ntro\n");
	}
	else if (keysym == S || keysym == DOWN)
	{
		cub3d->player->y += 1 * cub3d->player->speed;
		render_frame(cub3d);
	}
	if (keysym == D || keysym == RIGHT)
	{
		cub3d->player->ang = (cub3d->player->ang + 1) % 360;
		render_frame(cub3d);
	}
	else if (keysym == A || keysym == LEFT)
	{
		cub3d->player->ang = (cub3d->player->ang + 359) % 360;
		render_frame(cub3d);
	}
	return (0);
}

int	mlx_management(t_cub3d cub3d)
{
	cub3d.mlx = mlx_init();
	if (!cub3d.mlx)
		return (free(cub3d.mlx), free_cub3d(&cub3d), -ERROR_MLX);
	cub3d.window = mlx_new_window(cub3d.mlx, WD, HE, "cub3d");
	if (!cub3d.window)
		return (free(cub3d.mlx), free(cub3d.window),
			free_cub3d(&cub3d), -ERROR_MLX);
	render_frame(&cub3d);
	mlx_key_hook(cub3d.window, &handle_input, &cub3d);
	//mlx_loop_hook(cub3d.mlx, &render_frame, &cub3d);
	mlx_hook(cub3d.window, 17, 1, close_window, &cub3d);
	mlx_loop(cub3d.mlx);
	return (free(cub3d.mlx), free(cub3d.window), 0);
}
