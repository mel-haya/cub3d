/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 03:05:46 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/14 03:36:19 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		in_canvas(t_point p)
{
	if (p.x > 0 && p.x < g_window.width && p.y > 0 && p.y < g_window.height)
		return (1);
	return (0);
}

int		is_texture(char *element)
{
	if ((!ft_strncmp(element, "NO", 2)
		|| !ft_strncmp(element, "EA", 2)
		|| !ft_strncmp(element, "WE", 2)
		|| !ft_strncmp(element, "S", 2)
		|| !ft_strncmp(element, "SO", 2)))
		return (1);
	return (0);
}

int		is_floor_ceiling(char *element)
{
	if (!ft_strncmp(element, "F", 2)
	|| !ft_strncmp(element, "C", 2))
		return (1);
	return (0);
}

void	check_elements(void)
{
	int	i;

	i = 0;
	if (!g_window.map)
		print_error("Please insert a valid map!!");
	while (i < 5)
	{
		if (!g_texture[i].data)
			print_error("there is a missing texture");
		i++;
	}
	if (g_window.ceiling < 0 || g_window.ceiling > 0xffffff
	|| g_window.floor < 0 || g_window.floor > 0xffffff)
		print_error("invalid ceiling or floor color");
}

int		count_char(char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}
