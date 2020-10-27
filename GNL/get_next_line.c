/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 00:31:10 by mel-haya          #+#    #+#             */
/*   Updated: 2019/11/15 14:07:16 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	static char	*buffer;
	int			status;

	status = 0;
	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE < 0)
		return (-1);
	if (!buffer)
	{
		if (!(buffer = malloc(BUFFER_SIZE + 1)))
			return (-1);
		status = read(fd, buffer, BUFFER_SIZE);
		buffer[status] = 0;
	}
	if ((status = buffering(fd, &buffer)) == -1)
		return (-1);
	if (!(*line = get_first_line(&buffer)))
		return (-1);
	return (status != 0);
}

int		check_nl(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		buffering(int fd, char **buffer)
{
	int		eof;
	char	*tmp;
	char	*new;

	if (!(new = malloc(BUFFER_SIZE + 1)))
		return (-1);
	eof = 1;
	while (!check_nl(*buffer) && (eof = read(fd, new, BUFFER_SIZE)))
	{
		tmp = *buffer;
		new[eof] = 0;
		if (!(*buffer = ft_strjoin(tmp, new)))
			return (-1);
		free(tmp);
	}
	free(new);
	return (eof);
}

char	*get_last_line(char **str)
{
	char *output;

	if (!(output = ft_strdup(*str)))
		return (NULL);
	free(*str);
	*str = NULL;
	return (output);
}

char	*get_first_line(char **str)
{
	int		i;
	int		count;
	char	*output;

	i = 0;
	count = 0;
	if (!check_nl(*str))
		return (get_last_line(str));
	while (str[0][count] != '\n')
		count++;
	if (!(output = malloc(count + 1)))
		return (NULL);
	while (str[0][i] != '\n')
	{
		output[i] = str[0][i];
		i++;
	}
	output[i] = '\0';
	if ((count = free_buffer(str, i)) == -1)
	{
		free(output);
		output = NULL;
	}
	return (output);
}
