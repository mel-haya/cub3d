/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 01:47:59 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/14 02:28:17 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_norm(char **line, int *player, int i)
{
	int	j;

	j = 1;
	if (check_row(line[i]))
		print_error("invalid character in the map");
	while (line[i][j + 1])
	{
		if (line[i][j] == '0' || line[i][j] == '2')
			if (line[i][j - 1] == ' ' || line[i][j + 1] == ' '
			|| ((int)ft_strlen(line[i - 1]) - 1 < j || line[i - 1][j] == ' ')
			|| ((int)ft_strlen(line[i + 1]) - 1 < j || line[i + 1][j] == ' '))
				print_error("the map is not closed");
		if (ft_isalpha(line[i][j]))
			if (line[i][j - 1] == ' ' || line[i][j + 1] == ' '
			|| ((int)ft_strlen(line[i - 1]) - 1 < j || line[i - 1][j] == ' ')
			|| ((int)ft_strlen(line[i + 1]) - 1 < j || line[i + 1][j] == ' '))
				print_error("player is out of the map");
		if (ft_isalpha(line[i][j]))
			*player += 1;
		j++;
	}
}

void	check_map(char *line)
{
	char	**array;
	int		i;
	int		player;

	i = 1;
	player = 0;
	array = ft_split(line, '\n');
	if (filter(array[0], "1 ") || filter(array[g_window.map_rows - 1], "1 "))
		print_error("the map is not closed ");
	while (i < g_window.map_rows - 1)
	{
		check_map_norm(array, &player, i);
		if (!ft_strchr("1 ", array[i][0])
		|| !ft_strchr("1 ", array[i][ft_strlen(array[i]) - 1]))
			print_error("the map is not closed");
		i++;
	}
	free_matrix((void **)array, g_window.map_rows);
	if (player != 1)
		print_error("multiple or no player detected");
}

void	buffering_map(char **s1, char *s2)
{
	char	*tmp;

	if (g_window.map_cols < (int)ft_strlen(s2))
		g_window.map_cols = ft_strlen(s2);
	tmp = *s1;
	*s1 = ft_strjoin(*s1, s2);
	free(tmp);
	tmp = *s1;
	*s1 = ft_strjoin(*s1, "\n");
	free(tmp);
	free(s2);
}

int		load_map(char *line, int fd, t_player *p, int *count)
{
	char	*buffer;
	int		ngl;

	if (*count != 8)
		print_error("missing element or the map is in a wrong position");
	g_window.map_cols = ft_strlen(line);
	buffer = malloc(ft_strlen(line) * sizeof(char *));
	buffer[0] = 0;
	while (is_valid_element(line[0]))
	{
		buffering_map(&buffer, line);
		ngl = get_next_line(fd, &line);
		g_window.map_rows++;
	}
	if (ngl || (line[0] && !is_valid_element(line[0])))
		print_error("wrong element after the map");
	free(line);
	check_map(buffer);
	fill_map(buffer, p);
	free(buffer);
	return (0);
}

void	load_cub_file(int fd, t_player *p)
{
	char	*line;
	char	**words;
	int		count;

	count = 0;
	while (get_next_line(fd, &line))
	{
		if (*line && !is_valid_element(line[0]))
			words = ft_split(line, ' ');
		if (*line && is_valid_element(line[0]))
		{
			load_map(line, fd, p, &count);
			break ;
		}
		else if (*line && !ft_strncmp(words[0], "R", 2))
			init_window(words, &count, line);
		else if (*line && is_texture(words[0]))
			load_textures(words, &count, line);
		else if (*line && is_floor_ceiling(words[0]))
			rgb_color(words, &count, line);
		else if (*line)
			print_error("invalid element in the file");
		free(line);
	}
}
