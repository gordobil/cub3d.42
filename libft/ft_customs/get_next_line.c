/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:44:14 by ngordobi          #+#    #+#             */
/*   Updated: 2025/04/16 12:44:14 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*save_line(char	*buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (free(buffer), NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] != '\0' && buffer[i] == '\n')
		line[i] = '\n';
	else
		line[i] = '\0';
	return (line);
}

char	*buffer_update(char *buffer)
{
	char	*temp_buff;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	temp_buff = ft_calloc((ft_strlen(buffer) - i), sizeof(char));
	if (!temp_buff)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i] != '\0')
		temp_buff[j++] = buffer[i++];
	temp_buff[j] = '\0';
	return (free(buffer), temp_buff);
}

char	*append(char *buffer, char *temp_buff)
{
	char	*temp;

	temp = ft_strjoin(buffer, temp_buff);
	if (buffer)
		free(buffer);
	return (temp);
}

char	*read_text(int fd, char *buffer)
{
	char	*temp_buff;
	int		read_chars;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	temp_buff = ft_calloc((1 + 1), sizeof(char));
	if (!temp_buff)
		return (free(buffer), NULL);
	read_chars = 1;
	while (read_chars != 0 && ft_strchr(buffer, '\n') == NULL)
	{
		read_chars = read(fd, temp_buff, 1);
		if (read_chars < 0)
		{
			free(temp_buff);
			return (free(buffer), NULL);
		}
		temp_buff[read_chars] = '\0';
		buffer = append(buffer, temp_buff);
	}
	free(temp_buff);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0)
		return (if_free(buffer), NULL);
	buffer = read_text(fd, buffer);
	if (!buffer)
		return (NULL);
	line = save_line(buffer);
	buffer = buffer_update(buffer);
	return (line);
}
