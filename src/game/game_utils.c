/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/08/01 17:27:48 by ngordobi         ###   ########.fr       */
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
	ft_printf("\n-------- CUB3D INFO --------\n");
	printf(" ¬ Player coordinates\n    [%f, %f]\n", cub3d->player->x, \
		cub3d->player->y);
	printf(" ¬ Square [%d, %d] = %c\n", (int)cub3d->player->x \
			/ SQ, (int)cub3d->player->y / SQ, \
			cub3d->map[(int)cub3d->player->x \
			/ 30][(int)cub3d->player->y / 30]);
	ft_printf("----------------------------\n\n");
}
