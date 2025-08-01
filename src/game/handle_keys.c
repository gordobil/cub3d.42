/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:29 by ngordobi          #+#    #+#             */
/*   Updated: 2025/08/01 12:23:28 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_input(int keysym, t_cub3d *cub3d)
{
	if (keysym == Q || keysym == ESC)
		close_window(cub3d);
	if (keysym == RIGHT)
		cub3d->r_key = 1;
	if (keysym == LEFT)
		cub3d->l_key = 1;
	if (keysym == W)
		cub3d->w_key = 1;
	if (keysym == S)
		cub3d->s_key = 1;
	if (keysym == D)
		cub3d->d_key = 1;
	if (keysym == A)
		cub3d->a_key = 1;
	return (0);
}

int	handle_release(int keysym, t_cub3d *cub3d)
{
	if (keysym == RIGHT)
		cub3d->r_key = 0;
	if (keysym == LEFT)
		cub3d->l_key = 0;
	if (keysym == W)
		cub3d->w_key = 0;
	if (keysym == S)
		cub3d->s_key = 0;
	if (keysym == D)
		cub3d->d_key = 0;
	if (keysym == A)
		cub3d->a_key = 0;
	return (0);
}
