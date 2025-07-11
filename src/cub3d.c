/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:18:42 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/11 13:00:24 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_colors(char **elems, t_player *player)
{
	int	i;
	int	j;
	int	s;
	int	c[3];
	int	x;

	i = 3;
	while (++i < 6)
	{
		j = -1;
		x = -1;
		while (elems[i][++j] != '\0' && (elems[i][j] == ',' ||
			(elems[i][j] >= '0' && elems[i][j] <= '9')))
		{
			s = j;
			while ((elems[i][j] >= '0' && elems[i][j] <= '9')
				&& elems[i][j] != ',' && elems[i][j] != '\0')
				j++;
			if ((elems[i][j] < '0' || elems[i][j] > '9') && elems[i][j] != ','
				&& elems[i][j] != '\0')
				return (ERROR_ELEMS);
			c[++x] = ft_atoi(ft_substr(elems[i], s, s - j));
		}
		if (((elems[i][j] < '0' || elems[i][j] > '9') && elems[i][j] != ','
			&& elems[i][j] != '\0') || x != 2 || (x == 2 && elems[i][j] == ','))
			return (ERROR_ELEMS);
		if (i == 4)
			player->f_col = 255 | (c[0] << 24) | (c[1] << 16) | (c[2] << 8);
		else if (i == 5)
			player->c_col = 255 | (c[0] << 24) | (c[1] << 16) | (c[2] << 8);
	}
	ft_printf("%x\n%x\n", player->f_col, player->c_col);
	return (0);
}

int	init_player(t_cub3d *cub3d, t_player *player)
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
	if (get_colors(cub3d->elements, player) != 0)
		return (-ERROR_ELEMS);
	return (0);
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
	if (init_player(&cub3d, cub3d.player) != 0)
		return (free_cub3d(&cub3d), error(ERROR_ELEMS));
	if (mlx_management(cub3d) < 0)
		return (free_cub3d(&cub3d), error(ERROR_MLX));
	return (free_cub3d(&cub3d));
}

// QUE HAY K HACER:

/*
	- movimiento
	- texturas
	- colores *.cub rgb a hexadecimal
	- path not found segfault
*/
