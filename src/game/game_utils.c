/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/08/01 11:21:28 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	deg_to_rad(double ang)
{
	return (ang * M_PI / 180);
}

void	get_angle(t_cub3d *cub3d, char sign)
{
	double	speed;

	speed = 1.5;
	if (sign == '+')
		cub3d->player->ang += speed;
	else if (sign == '-')
		cub3d->player->ang -= speed;
	if (cub3d->player->ang > 359)
		cub3d->player->ang -= 360;
	else if (cub3d->player->ang < 0)
		cub3d->player->ang += 360;
}
