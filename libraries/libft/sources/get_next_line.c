/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:40 by jlacerda          #+#    #+#             */
/*   Updated: 2024/12/21 20:44:09 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static char	*ft_get_content(int fd, char *content, char *buffer)
{
	char	*temp;
	int		bytes_read;

	bytes_read = 0;
	if (!content)
		content = ft_strdup(EMPTY_STRING);
	while (!ft_strchr(content, NEW_LINE))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(content);
			content = NULL;
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = NULL_CHAR;
		temp = content;
		content = ft_strjoin(content, buffer);
		free(temp);
	}
	return (content);
}

static int	ft_is_end_of_file(char **content, char	**buffer)
{
	if (*content[0] == NULL_CHAR)
	{
		free(*buffer);
		free(*content);
		*content = NULL;
		return (1);
	}
	return (0);
}

static char	*ft_get_line(char *content, int *index)
{
	char	*line;

	while (content[*index] && content[*index] != NEW_LINE)
		(*index)++;
	if (content[*index] && content[*index] == NEW_LINE)
		(*index)++;
	line = ft_substr(content, 0, *index);
	if (!line)
	{
		free(content);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*content[MAX_FD];
	char		*buffer;
	char		*temp;
	char		*line;
	int			index;

	index = 0;
	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	content[fd] = ft_get_content(fd, content[fd], buffer);
	if (!content[fd])
		return (NULL);
	if (ft_is_end_of_file(&content[fd], &buffer))
		return (NULL);
	line = ft_get_line(content[fd], &index);
	if (!line)
		return (NULL);
	temp = content[fd];
	content[fd] = ft_strdup(content[fd] + index);
	free(temp);
	free(buffer);
	return (line);
}
