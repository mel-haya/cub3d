/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 22:45:21 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/13 23:00:21 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		texture_wall(int i, int j, float wall_height, int offset_x)
{
	int offset_y;
	int color;
	int distancefromtop;

	if (j < (g_window.height - wall_height) / 2)
		color = g_window.ceiling;
	else if (j > (g_window.height - wall_height) / 2 &&
	j < (g_window.height + wall_height) / 2)
	{
		distancefromtop = j + (wall_height - g_window.height) / 2;
		offset_y = distancefromtop * ((float)TILE_SIZE / wall_height);
		color = g_texture[g_rays[i].inv].data[(g_texture[g_rays[i].inv].width
		* ((int)(offset_y * g_texture[g_rays[i].inv].height / TILE_SIZE)))
		+ ((int)(offset_x * g_texture[g_rays[i].inv].width / TILE_SIZE))];
	}
	else
		color = g_window.floor;
	return (color);
}

void	render_walls(t_player *p)
{
	int		i;
	int		y;
	float	wall_height;
	float	correct_dist;
	int		offset_x;

	i = 0;
	while (i < g_window.width)
	{
		correct_dist = g_rays[i].distance *
		cos(g_rays[i].ray_angle - p->facing_angle);
		wall_height = (TILE_SIZE / correct_dist) * g_window.projection_plane;
		y = 0;
		if (g_rays[i].hit_vert)
			offset_x = (int)g_rays[i].closest_collision.y % TILE_SIZE;
		else
			offset_x = (int)g_rays[i].closest_collision.x % TILE_SIZE;
		while (y < g_window.height)
		{
			g_data[(g_window.width * y) + i] =
			texture_wall(i, y, wall_height, offset_x);
			y++;
		}
		i++;
	}
}

void	init_horz(t_player *p, t_point *output,
			t_point *step, int column_id)
{
	output->y = floor(p->pos.y / TILE_SIZE) * TILE_SIZE +
	g_rays[column_id].facing_down * TILE_SIZE;
	output->x = p->pos.x + (output->y - p->pos.y)
	/ tan(g_rays[column_id].ray_angle);
	step->y = g_rays[column_id].facing_down ? TILE_SIZE : -TILE_SIZE;
	step->x = TILE_SIZE / tan(g_rays[column_id].ray_angle);
	step->x *= (g_rays[column_id].facing_left && step->x > 0) ? -1 : 1;
	step->x *= (!g_rays[column_id].facing_left && step->x < 0) ? -1 : 1;
}

t_point	horz_intersection(t_player *p, int column_id)
{
	t_point step;
	t_point output;

	init_horz(p, &output, &step, column_id);
	while (output.x > 0 && output.y > 0 &&
	output.y / TILE_SIZE < g_window.map_rows &&
	output.x / TILE_SIZE < g_window.map_cols)
	{
		if (g_window.map[(int)(output.y - !g_rays[column_id].facing_down)
		/ TILE_SIZE][(int)output.x / TILE_SIZE] == 1)
		{
			if (sin(g_rays[column_id].ray_angle) > 0)
				g_rays[column_id].inh = SO;
			else
				g_rays[column_id].inh = NO;
			return (output);
		}
		else
		{
			output.x += step.x;
			output.y += step.y;
		}
	}
	return (output);
}
