/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 22:24:57 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/14 01:52:14 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite(int x, float distance, float height)
{
	int i;
	int j;
	int y_offset;
	int color;

	i = x;
	while (i <= x + height)
	{
		j = (g_window.height - height) / 2;
		y_offset = 0;
		if (i >= 0 && i < g_window.width && distance < g_rays[i].distance)
		{
			while (j < (g_window.height + height) / 2 - 1)
			{
				color = g_texture[4].data[(int)(y_offset / height *
				g_texture[4].height) * g_texture[4].width +
				(int)((i - x) / height * g_texture[4].width)];
				if (j < g_window.height && j >= 0 && color != 0x000000)
					g_data[(j) * g_window.width + (i)] = color;
				j++;
				y_offset++;
			}
		}
		i++;
	}
}

void	sort_sprites(t_player *p)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i++ < g_window.sprite_index)
		g_window.sprite[i].distance = dist_two_point(
			g_window.sprite[i].pos, p->pos);
	i = 0;
	while (i < g_window.sprite_index - 1)
	{
		j = 0;
		while (j < g_window.sprite_index - 1 - i)
		{
			if (g_window.sprite[j].distance < g_window.sprite[j + 1].distance)
			{
				tmp = g_window.sprite[j];
				g_window.sprite[j] = g_window.sprite[j + 1];
				g_window.sprite[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	render_sprite(t_player *p)
{
	float		angle;
	float		sprite_height;
	int			column_index;
	t_sprite	*s;
	int			i;

	s = g_window.sprite;
	sort_sprites(p);
	i = 0;
	while (i < g_window.sprite_index)
	{
		s[i].distance = dist_two_point(s[i].pos, p->pos);
		angle = atan2(s[i].pos.y - p->pos.y, s[i].pos.x - p->pos.x);
		while (angle - g_rays[0].ray_angle > M_PI)
			angle -= 2 * M_PI;
		while (angle - g_rays[0].ray_angle < -M_PI)
			angle += 2 * M_PI;
		sprite_height = (TILE_SIZE / s[i].distance)
		* g_window.projection_plane;
		column_index = (angle - g_rays[0].ray_angle)
		/ (FOV_ANGLE / g_window.width) - (sprite_height / 2);
		draw_sprite(column_index, s[i].distance, sprite_height);
		i++;
	}
}
