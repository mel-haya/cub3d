/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:48:05 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/13 23:15:20 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_word_count(char const *str, char c)
{
	int i;
	int output;

	i = 0;
	output = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			output++;
		i++;
	}
	return (output);
}

int		ft_checkset(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*filter(char *str, char const *set)
{
	int		count;
	int		i;
	int		j;
	char	*output;

	count = 0;
	output = NULL;
	j = 0;
	i = 0;
	while (str[i])
		if (!ft_checkset(str[i++], set))
			count++;
	if (count)
	{
		output = malloc(count + 1);
		output[count] = 0;
		i = 0;
		while (str[i])
		{
			if (!ft_checkset(str[i], set))
				output[j++] = str[i];
			i++;
		}
	}
	return (output);
}

void	print_error(const char *error)
{
	ft_putstr_fd("Error:\n", 0);
	ft_putstr_fd((char *)error, 0);
	exit(-1);
}

int		check_row(char *line)
{
	char	*copy;
	int		output;

	output = 0;
	copy = filter(line, "012NSWE ");
	if (copy)
	{
		output = ft_strlen(copy);
		free(copy);
	}
	return (output);
}
