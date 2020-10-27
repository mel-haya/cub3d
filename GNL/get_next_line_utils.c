/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 05:10:08 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/14 00:13:56 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*result;
	int		j;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = 0;
	return (result);
}

size_t	ft_strlen(const char *s)
{
	int count;

	count = 0;
	while (s[count] != 0)
		count++;
	return (count);
}

char	*ft_strdup(const char *src)
{
	int		length;
	int		i;
	char	*c;

	c = 0;
	i = 0;
	length = ft_strlen(src);
	c = malloc(length + 1 * sizeof(char));
	if (!c)
		return (NULL);
	while (src[i])
	{
		c[i] = src[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

int		free_buffer(char **buff, int i)
{
	char *tmp;

	tmp = *buff;
	*buff = ft_strdup(*buff + i + 1);
	if (!buff)
		return (-1);
	free(tmp);
	return (0);
}
