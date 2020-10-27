/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_functions_norm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:11:13 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/14 13:55:29 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(char **words, int *count, char *line)
{
	int a;

	if (ft_word_count(line, ' ') != 3)
		print_error("insert only the two dimensions of the window");
	*count = *count + 1;
	g_window.width = check_num(words[1], 0, INT32_MAX);
	g_window.height = check_num(words[2], 0, INT32_MAX);
	if (g_window.width > 2048)
		g_window.width = 2048;
	if (g_window.height > 1152)
		g_window.height = 1152;
	g_window.projection_plane = (g_window.width / 2) / tan(FOV_ANGLE / 2);
	free_matrix((void **)words, 3);
	if (g_window.width <= 0 || g_window.height <= 0)
		print_error("the width or height of the window is invalid");
	g_window.win_ptr = mlx_new_window(
		g_window.mlx_ptr, g_window.width, g_window.height, "cub3D");
	g_map_img = mlx_new_image(
		g_window.mlx_ptr, g_window.width, g_window.height);
	g_data = (int*)mlx_get_data_addr(g_map_img, &a, &a, &a);
}

void	fill_row(char *row, int i, t_player *p)
{
	int j;

	j = 0;
	while (j < (int)ft_strlen(row))
	{
		g_window.map[i][j] = ft_isdigit(row[j]) ? row[j] - 48 : row[j];
		if (ft_isalpha(row[j]))
			get_player_pos(p, i, j);
		else if (row[j] == '2' && g_window.sprite_index < 500)
		{
			g_window.sprite[g_window.sprite_index].pos.x =
			(j * TILE_SIZE) + (float)(TILE_SIZE / 2);
			g_window.sprite[g_window.sprite_index].pos.y =
			(i * TILE_SIZE) + (float)(TILE_SIZE / 2);
			g_window.sprite_index++;
		}
		j++;
	}
	free(row);
}

void	fill_map(char *line, t_player *p)
{
	int		i;
	char	**array;

	g_window.map = malloc(g_window.map_rows * sizeof(int *));
	i = 0;
	array = ft_split(line, '\n');
	while (array[i])
	{
		g_window.map[i] = malloc((int)ft_strlen(array[i]) * sizeof(int *));
		fill_row(array[i], i, p);
		i++;
	}
	free(array);
}

void	load_textures(char **filename, int *count, char *line)
{
	int		c;
	void	*img;
	int		side;

	if (ft_word_count(line, ' ') != 2)
		print_error("insert only a XMP path after texture side");
	*count = *count + 1;
	side = 0;
	if (!ft_strncmp(filename[0], "NO", 3))
		side = NO;
	else if (!ft_strncmp(filename[0], "SO", 3))
		side = SO;
	else if (!ft_strncmp(filename[0], "EA", 3))
		side = EA;
	else if (!ft_strncmp(filename[0], "WE", 3))
		side = WE;
	else if (!ft_strncmp(filename[0], "S", 2))
		side = S;
	img = mlx_xpm_file_to_image(g_window.mlx_ptr, filename[1],
	&(g_texture[side].width), &(g_texture[side].height));
	if (!img)
		print_error("invalid texture path");
	g_texture[side].data = (int *)mlx_get_data_addr(img, &c, &c, &c);
	free(img);
	free_matrix((void **)filename, 2);
}

int		is_valid_element(char c)
{
	if ((c > '0' && c <= '2') || c == ' ')
		return (1);
	return (0);
}
