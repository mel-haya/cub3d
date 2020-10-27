/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 22:35:07 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/14 03:40:15 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float		dist_two_point(t_point p1, t_point p2)
{
	return (sqrt((p2.x - p1.x) * (p2.x - p1.x)
	+ (p2.y - p1.y) * (p2.y - p1.y)));
}

void		norm_angle(float *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle += (M_PI * 2);
}

t_point		make_point(float x, float y)
{
	t_point a;

	a.x = x;
	a.y = y;
	return (a);
}

int			check_num(char *num, int min, int max)
{
	int i;
	int output;

	i = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (-1);
		i++;
	}
	if (ft_strlen(num) > 10)
		num[8] = 0;
	output = ft_atoi(num);
	if (output < min || output >= max)
		return (-1);
	return (output);
}

void		rgb_color(char **colors, int *count, char *line)
{
	char	**color;
	int		red;
	int		green;
	int		blue;
	int		output;

	if (ft_word_count(line, ' ') != 2
	|| ft_word_count(colors[1], ',') != 3
	|| count_char(colors[1], ',') != 2)
		print_error("ceiling or floor color wrong format");
	*count = *count + 1;
	color = ft_split(colors[1], ',');
	red = check_num(color[0], 0, 256);
	green = check_num(color[1], 0, 256);
	blue = check_num(color[2], 0, 256);
	if (red < 0 || blue < 0 || green < 0)
		print_error("ceiling or floor color is invalid");
	output = (red * 256 * 256) + (green * 256) + blue;
	if (colors[0][0] == 'F')
		g_window.floor = output;
	else
		g_window.ceiling = output;
	free_matrix((void **)color, 3);
	free_matrix((void **)colors, 2);
}
