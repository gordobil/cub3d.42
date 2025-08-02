/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/08/02 12:32:56 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	deg_to_rad(double ang)
{
	return (ang * M_PI / 180);
}

double	get_angle(double ang, char sign)
{
	double	speed;

	speed = 1.5;
	if (sign == '+')
		ang += speed;
	else if (sign == '-')
		ang -= speed;
	if (ang > 359)
		ang -= 360;
	else if (ang < 0)
		ang += 360;
	return (ang);
}

void	print_info(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = (int)cub3d->player->x / SQ;
	y = (int)cub3d->player->y / SQ;
	ft_printf("\n-------- CUB3D INFO --------\n");
	printf(" ¬ Player coordinates\n    [%f, %f]\n", cub3d->player->x, \
			cub3d->player->y);
	ft_printf(" ¬ Square [%d, %d] = ", x, y);
	ft_printf("%c\n", cub3d->map[y][x]);
	ft_printf(" ¬ Map size: %d x %d\n", ft_strlen(cub3d->map[0]), \
			matrix_size(cub3d->map));
	ft_printf("----------------------------\n\n");
}
