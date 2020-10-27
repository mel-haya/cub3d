/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 22:43:30 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/13 22:54:50 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_vert(t_player *p, t_point *output,
			t_point *step, int column_id)
{
	output->x = floor(p->pos.x / TILE_SIZE) * TILE_SIZE +
	!g_rays[column_id].facing_left * TILE_SIZE;
	output->y = p->pos.y + (output->x - p->pos.x)
	* tan(g_rays[column_id].ray_angle);
	step->x = g_rays[column_id].facing_left ? -TILE_SIZE : TILE_SIZE;
	step->y = TILE_SIZE * tan(g_rays[column_id].ray_angle);
	step->y *= (!g_rays[column_id].facing_down && step->y > 0) ? -1 : 1;
	step->y *= (g_rays[column_id].facing_down && step->y < 0) ? -1 : 1;
}

t_point		vert_intersection(t_player *p, int column_id)
{
	t_point step;
	t_point output;

	init_vert(p, &output, &step, column_id);
	while (output.x > 0 && output.y > 0 && output.y / TILE_SIZE
	< g_window.map_rows && output.x / TILE_SIZE < g_window.map_cols)
	{
		if (g_window.map[(int)output.y / TILE_SIZE]
		[(int)(output.x - g_rays[column_id].facing_left) / TILE_SIZE] == 1)
		{
			if (cos(g_rays[column_id].ray_angle) > 0)
				g_rays[column_id].inv = EA;
			else
				g_rays[column_id].inv = WE;
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

void		init_ray(int column_id, t_player *p)
{
	float horz_hit;
	float vert_hit;

	horz_hit = dist_two_point(p->pos, g_rays[column_id].horz_collision);
	vert_hit = dist_two_point(p->pos, g_rays[column_id].vert_collision);
	if (horz_hit > vert_hit)
	{
		g_rays[column_id].closest_collision = g_rays[column_id].vert_collision;
		g_rays[column_id].hit_vert = 1;
		g_rays[column_id].hit_horz = 0;
		g_rays[column_id].distance = vert_hit;
	}
	else
	{
		g_rays[column_id].closest_collision = g_rays[column_id].horz_collision;
		g_rays[column_id].hit_vert = 0;
		g_rays[column_id].hit_horz = 1;
		g_rays[column_id].distance = horz_hit;
		g_rays[column_id].inv = g_rays[column_id].inh;
	}
}

void		cast_rays(t_player *p)
{
	int		column_id;
	float	ray_angle;

	column_id = 0;
	ray_angle = p->facing_angle - (FOV_ANGLE / 2);
	while (column_id < g_window.width)
	{
		norm_angle(&ray_angle);
		g_rays[column_id].ray_angle = ray_angle;
		g_rays[column_id].facing_down = (g_rays[column_id].ray_angle < M_PI
		&& g_rays[column_id].ray_angle > 0) ? 1 : 0;
		g_rays[column_id].facing_left = (g_rays[column_id].ray_angle > M_PI / 2
		&& g_rays[column_id].ray_angle < 1.5 * M_PI) ? 1 : 0;
		g_rays[column_id].horz_collision = horz_intersection(p, column_id);
		g_rays[column_id].vert_collision = vert_intersection(p, column_id);
		init_ray(column_id, p);
		ray_angle += FOV_ANGLE / (g_window.width);
		column_id++;
	}
}
