/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:23:09 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/22 13:42:18 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	jump_empty(char *line, int i)
{
	while (line[i] != '\0' && line[i] != '\r' && line[i] != '\n'
		&& (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0' || line[i] == '\r' || line[i] == '\n')
		return (-1);
	return (i);
}

int	get_elem_length(int i, char *line)
{
	int	start;

	start = i;
	while (line[i] != '\0' && line[i] != '\n' && line[i] != '\r'
		&& line[i] != ' ' && line[i] != '	')
		i++;
	return (i - start);
}

void	close_file(int fd, char *line)
{
	close(fd);
	if_free(line);
	get_next_line(-1);
}
