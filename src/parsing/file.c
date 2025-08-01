/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:23:09 by ngordobi          #+#    #+#             */
/*   Updated: 2025/04/16 12:23:09 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_path(char *path, t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (path[i + 1] != '\0')
		i++;
	if (path[i - 3] != '.' || path[i - 2] != 'c' || path[i - 1] != 'u'
		|| path[i] != 'b')
		return (ERROR_ARGS);
	cub3d->fd = open(path, O_RDONLY);
	if (cub3d->fd < 0)
		return (close(cub3d->fd), ERROR_ARGS);
	return (0);
}

int	elem_manag(char **elem, int flag)
{
	int	i;

	if (flag == 1)
	{
		if (!elem)
			return (ERROR_ELEMS);
		elem[0] = ft_strdup("NO");
		elem[1] = ft_strdup("SO");
		elem[2] = ft_strdup("WE");
		elem[3] = ft_strdup("EA");
		elem[4] = ft_strdup("F");
		elem[5] = ft_strdup("C");
		elem[6] = NULL;
	}
	else
	{
		i = -1;
		while (elem[++i] != NULL && i < 7)
			if_free_str(elem[i]);
		free(elem);
		elem = NULL;
	}
	return (0);
}

int	index_update(int i, int j, char *line)
{
	if (j >= 0 && j < 4)
		i += 2;
	else if (j >= 4 && j <= 5)
		i += 1;
	i = jump_empty(line, i);
	return (i);
}

int	get_elements(char *line, t_cub3d *cub3d, int i)
{
	char		**elem;
	char		*temp;
	static int	j;

	if (j > 5)
		return (j++, 1);
	if (i == -1)
		return (0);
	elem = malloc(7 * sizeof(char *));
	if (elem_manag(elem, 1) != 0)
		return (ERROR_ELEMS);
	if ((j >= 0 && j <= 3 && elem[j][0] == line[i] && elem[j][1] == line[i + 1]
		&& (line[i + 2] == ' ' || line[i + 2] == '\t')) || (j >= 4 && j <= 5
		&& elem[j][0] == line[i] && (line[i +1] == ' ' || line[i +1] == '\t')))
	{
		i = index_update(i, j, line);
		if (line[i] == '\0' || line[i] == '\n' || line[i] == '\r')
			return (elem_manag(elem, -1), ERROR_ELEMS);
		if_free_str(cub3d->elements[j]);
		temp = ft_substr(line, i, get_elem_length(i, line));
		cub3d->elements[j] = ft_strdup(temp);
		free(temp);
		return (j++, elem_manag(elem, -1), 0);
	}
	return (elem_manag(elem, -1), ERROR_ELEMS);
}

int	check_file(t_cub3d *cub3d)
{
	char	*line;
	int		ret;

	while (1)
	{
		line = get_next_line(cub3d->fd);
		if (line == NULL || !line)
			break ;
		if (jump_empty(line, 0) >= 0)
		{
			ret = get_elements(line, cub3d, jump_empty(line, 0));
			if (ret != 0 && ret != 1)
				return (close_file(cub3d->fd, line), ERROR_ELEMS);
			else if (ret == 1)
				ret = get_map(cub3d, line);
			if (ret != 0)
				break ;
		}
		if_free_str(line);
	}
	if (ret < 0 || ret == ERROR_ELEMS || ret == ERROR_MAP)
		return (close_file(cub3d->fd, line), ret);
	if (!cub3d->map || !cub3d->map[0])
		return (close_file(cub3d->fd, line), ERROR_MAP);
	return (close_file(cub3d->fd, line), tab_replace(cub3d), map_check(cub3d));
}
