/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:15:33 by ngordobi          #+#    #+#             */
/*   Updated: 2025/08/02 12:22:09 by ngordobi         ###   ########.fr       */
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

char	**get_new_map(t_cub3d *cub3d, char *line, int i)
{
	char	**new_map;
	int		j;
	int		len;

	new_map = malloc((i + 2) * (sizeof(char *)));
	j = 0;
	while (cub3d->map[j] != NULL)
	{
		new_map[j] = ft_strdup(cub3d->map[j]);
		j++;
	}
	len = ft_strlen(line);
	if (line[len - 1] != '\n' && line[len - 1] != '\r'
		&& line[len - 2] != '\n' && line[len - 2] != '\r')
		new_map[j] = ft_substr(line, 0, len);
	else
		new_map[j] = ft_substr(line, 0, len - 2);
	new_map[j + 1] = NULL;
	if (!new_map || !new_map[j])
		return (free_matrix(new_map), NULL);
	return (new_map);
}

int	get_map(t_cub3d *cub3d, char *line)
{
	static int	i;
	char		**new_map;

	if (!cub3d->map || !cub3d->map[0])
	{
		cub3d->map = malloc(2 * sizeof(char *));
		if (!cub3d->map)
			return (ERROR_FATAL);
		cub3d->map[0] = ft_substr(line, 0, ft_strlen(line) - 2);
		if (!cub3d->map[0])
			return (ERROR_FATAL);
		cub3d->map[1] = NULL;
		i = 1;
		return (0);
	}
	new_map = get_new_map(cub3d, line, i);
	if (!new_map || new_map == NULL)
		return (ERROR_FATAL);
	if (cub3d->map)
		free_matrix(cub3d->map);
	cub3d->map = NULL;
	cub3d->map = matrix_dup(new_map);
	free_matrix(new_map);
	new_map = NULL;
	return (i++, 0);
}
