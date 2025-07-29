/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:18:42 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/29 18:49:14 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_player(t_cub3d *cub3d)
{
	cub3d->player = malloc(sizeof(t_player));
	if (!cub3d->player)
		return (ERROR_FATAL);
	cub3d->player->x = (cub3d->start_x * SQ) - (SQ / 2);
	cub3d->player->y = (cub3d->start_y * SQ) - (SQ / 2);
	cub3d->player->speed = 2;
	if (cub3d->start_pos == 'N')
		cub3d->player->ang = 270;
	else if (cub3d->start_pos == 'S')
		cub3d->player->ang = 90;
	else if (cub3d->start_pos == 'E')
		cub3d->player->ang = 0;
	else if (cub3d->start_pos == 'W')
		cub3d->player->ang = 180;
	cub3d->map[cub3d->start_y][cub3d->start_x] = '0';
	if (get_colors(cub3d->elements, cub3d->player, 3, -1) != 0)
		return (ERROR_ELEMS);
	return (0);
}

int	init_cub3d(t_cub3d *cub3d)
{
	int	i;

	cub3d->fd = 0;
	cub3d->map = NULL;
	cub3d->elements = malloc(7 * sizeof(char *));
	if (!cub3d->elements)
		return (ERROR_FATAL);
	i = -1;
	while (++i < 7)
		cub3d->elements[i] = NULL;
	cub3d->start_pos = 'X';
	cub3d->start_y = -1;
	cub3d->start_x = -1;
	cub3d->mlx = NULL;
	cub3d->window = NULL;
	cub3d->player = NULL;
	cub3d->texture = NULL;
	cub3d->img = NULL;
	cub3d->w_key = 0;
	cub3d->s_key = 0;
	cub3d->a_key = 0;
	cub3d->d_key = 0;
	cub3d->r_key = 0;
	cub3d->l_key = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;
	int		ret;

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d || cub3d == NULL)
		return (error(ERROR_FATAL));
	if (init_cub3d(cub3d) != 0)
		return (free_cub3d(cub3d, ERROR_FATAL));
	if (argc != 2 || !argv[1] || get_path(argv[1], cub3d) != 0)
		return (free_cub3d(cub3d, ERROR_ARGS));
	ret = check_file(cub3d);
	if (ret != 0)
		return (free_cub3d(cub3d, ret));
	if (init_player(cub3d) != 0)
		return (free_cub3d(cub3d, ERROR_ELEMS));
	ret = mlx_management(cub3d);
	if (ret != 0)
		return (free_cub3d(cub3d, ret));
	return (free_cub3d(cub3d, 0));
}

// QUE HAY K HACER:

/*
	- texturas
	- antes de entregar quitar lo de borrar los zone identifiers del makefile
*/

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s
//-fsanitize=address
