/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:18:42 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/08 12:26:28 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_cub3d *cub3d, t_player *player)
{
	player->x = (cub3d->start_x * SQ) - (SQ / 2);
	player->y = (cub3d->start_y * SQ) - (SQ / 2);
	player->speed = 1;
	if (cub3d->start_pos == 'N')
		player->ang = 270;
	else if (cub3d->start_pos == 'S')
		player->ang = 90;
	else if (cub3d->start_pos == 'E')
		player->ang = 0;
	else if (cub3d->start_pos == 'W')
		player->ang = 180;
	cub3d->map[cub3d->start_y][cub3d->start_x] = '0';
}

int	init_cub3d(t_cub3d *cub3d)
{
	int	i;

	cub3d->map_path = NULL;
	cub3d->map_fd = 0;
	cub3d->map = NULL;
	cub3d->elements = malloc(7 * sizeof(char *));
	if (!cub3d->elements)
		return (free(cub3d->elements), free_cub3d(cub3d), -ERROR_FATAL);
	i = -1;
	while (++i < 7)
		cub3d->elements[i] = NULL;
	cub3d->start_pos = 'X';
	cub3d->start_y = -1;
	cub3d->start_x = -1;
	cub3d->player = malloc(sizeof(t_player));
	if (!cub3d->player)
		return (free(cub3d->player), free_cub3d(cub3d), -ERROR_FATAL);
	cub3d->img = malloc(sizeof(t_img));
	if (!cub3d->img)
		return (free(cub3d->img), free_cub3d(cub3d), -ERROR_FATAL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;
	int		ret;

	if (init_cub3d(&cub3d) < 0)
		return (free_cub3d(&cub3d), error(ERROR_FATAL));
	if (argc != 2 || !argv[1] || get_path(argv[1], &cub3d) != 0)
		return (free_cub3d(&cub3d), error(ERROR_ARGS));
	ret = check_file(&cub3d);
	if (ret < 0)
		return (free_cub3d(&cub3d), error(-ret));
	init_player(&cub3d, cub3d.player);
	if (mlx_management(cub3d) < 0)
		return (free_cub3d(&cub3d), error(ERROR_MLX));
	return (free_cub3d(&cub3d));
}
