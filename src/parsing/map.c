/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:15:33 by ngordobi          #+#    #+#             */
/*   Updated: 2025/06/30 15:23:51 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	tab_for_spaces(t_cub3d *cub3d, char *new, int i)
{
	int	j;
	int	k;
	int	four;

	j = -1;
	k = 0;
	while (cub3d->map[i][++j] != '\0')
	{
		if (cub3d->map[i][j] == '\t')
		{
			four = k + 4;
			while (k < four)
			{
				new[k] = ' ';
				k++;
			}
		}
		else
			new[k++] = cub3d->map[i][j];
	}
	new[k] = '\0';
}

int	tab_replace(t_cub3d *cub3d)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (cub3d->map[++i] != NULL)
	{
		k = 0;
		j = -1;
		while (cub3d->map[i][++j] != '\0')
			if (cub3d->map[i][j] == '\t')
				k++;
		if (k > 0)
		{
			j = ft_strlen(cub3d->map[i]);
			new = malloc((j + (k * 4) + 1) * sizeof(char));
			tab_for_spaces(cub3d, new, i);
			free(cub3d->map[i]);
			cub3d->map[i] = ft_strdup(new);
			free(new);
		}
	}
	return (0);
}

int	get_new_map(t_cub3d *cub3d, char **new_map, char *line)
{
	int	i;

	i = 0;
	while (cub3d->map[i] != NULL)
	{
		new_map[i] = ft_strdup(cub3d->map[i]);
		i++;
	}
	if (line[ft_strlen(line) - 1] != '\n' && line[ft_strlen(line) - 1] != '\r')
		new_map[i] = ft_substr(line, 0, ft_strlen(line));
	else
		new_map[i] = ft_substr(line, 0, ft_strlen(line) - 2);
	new_map[i + 1] = NULL;
	if (!new_map || !new_map[i])
		return (free_matrix(new_map), -ERROR_FATAL);
	return (0);
}

int	get_map(t_cub3d *cub3d, char *line)
{
	static int	i;
	char		**new_map;

	if (!cub3d->map || !cub3d->map[0])
	{
		cub3d->map = malloc(2 * sizeof(char *));
		if (!cub3d->map)
			return (-ERROR_FATAL);
		cub3d->map[0] = ft_substr(line, 0, ft_strlen(line) - 2);
		if (!cub3d->map[0])
			return (-ERROR_FATAL);
		cub3d->map[1] = NULL;
		i = 1;
		return (0);
	}
	new_map = malloc((i + 2) * (sizeof(char *)));
	if (!new_map)
		return (-ERROR_FATAL);
	if (get_new_map(cub3d, new_map, line) != 0)
		return (-ERROR_FATAL);
	free_matrix(cub3d->map);
	cub3d->map = new_map;
	i++;
	return (0);
}
