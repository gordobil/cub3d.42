/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:44:14 by ngordobi          #+#    #+#             */
/*   Updated: 2025/05/06 10:46:09 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	flood_fill(int y, int x, char **map, char pos)
{
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (0);
	if ((map[y][x] == '0' && (y <= 0 || x <= 0 || x + 1 >= ft_strlen(map[y])
			|| y + 1 >= matrix_size(map))) || map[y][x] == ' '
		|| map[y][x] == '\0' || map[y] == NULL || y < 0 || x < 0)
		return (-1);
	else if ((map[y][x] == '0' || map[y][x] == pos || map[y][x] == 'X')
		&& (map[y][x -1] == '1' || map[y][x -1] == '0' || map[y][x -1] == 'X')
		&& (map[y][x +1] == '1' || map[y][x +1] == '0' || map[y][x +1] == 'X')
		&& (map[y -1][x] == '1' || map[y -1][x] == '0' || map[y -1][x] == 'X')
		&& (map[y +1][x] == '1' || map[y +1][x] == '0' || map[y +1][x] == 'X'))
		map[y][x] = 'X';
	else
		return (-1);
	if (flood_fill(y, x - 1, map, pos) < 0)
		return (-1);
	if (flood_fill(y, x + 1, map, pos) < 0)
		return (-1);
	if (flood_fill(y - 1, x, map, pos) < 0)
		return (-1);
	if (flood_fill(y + 1, x, map, pos) < 0)
		return (-1);
	return (1);
}
