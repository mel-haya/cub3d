/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 20:51:35 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/14 02:31:43 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_key(int key, t_player *p)
{
	cast_rays(p);
	render_walls(p);
	render_sprite(p);
	mlx_put_image_to_window(g_window.mlx_ptr, g_window.win_ptr,
	g_map_img, 0, 0);
	if (key == ESC)
		close_win();
	if (key == KEY_UP)
		p->forward_key = 1;
	else if (key == KEY_DOWN)
		p->backward_key = 1;
	else if (key == KEY_LEFT)
		p->turn_direction = 1;
	else if (key == KEY_RIGHT)
		p->turn_direction = -1;
	p->walk_direction = p->forward_key - p->backward_key;
	return (1);
}

int		key_up(int key, t_player *p)
{
	if (key == KEY_UP)
	{
		p->forward_key = 0;
		if (p->backward_key)
			p->walk_direction = -1;
		else
			p->walk_direction = 0;
	}
	else if (key == KEY_DOWN)
	{
		p->backward_key = 0;
		if (p->forward_key)
			p->walk_direction = 1;
		else
			p->walk_direction = 0;
	}
	if (key == KEY_LEFT)
		p->turn_direction = 0;
	else if (key == KEY_RIGHT)
		p->turn_direction = 0;
	return (1);
}

int		loop_hook(t_player *p)
{
	cast_rays(p);
	render_walls(p);
	render_sprite(p);
	mlx_put_image_to_window(g_window.mlx_ptr, g_window.win_ptr,
	g_map_img, 0, 0);
	move_player(p);
	return (0);
}

int		close_win(void)
{
	free_matrix((void **)g_window.map, g_window.map_rows);
	free(g_texture);
	free(g_rays);
	exit(1);
	return (0);
}

void	free_matrix(void **array, int length)
{
	int i;

	i = 0;
	while (i < length)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
