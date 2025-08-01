/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/08/01 12:05:32 by ngordobi         ###   ########.fr       */
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

unsigned int	get_pixel_color(t_img *texture, int distance, int y, int tx)
{
	unsigned int	color;
	int				ty;
	int				wall_height;

	if (!texture || !texture->addr)
		return (0);
	wall_height = (int)((SQ * HE) / distance);
	ty = ((y - (HE / 2 - wall_height / 2)) * texture->height) / wall_height;
	color = *((unsigned int *)(texture->addr \
		+ (ty * texture->line_length + tx * (texture->bits_per_pixel / 8))));
	return (color);
}
