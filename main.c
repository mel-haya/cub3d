/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 23:59:36 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/14 13:54:19 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_player *p)
{
	t_point old;
	t_point new;

	old = p->pos;
	if (p->walk_direction)
	{
		new.x = old.x + cos(p->facing_angle) * (MOV_SPEED) * p->walk_direction;
		new.y = old.y + sin(p->facing_angle) * (MOV_SPEED) * p->walk_direction;
		if (g_window.map[(int)old.y / TILE_SIZE][(int)new.x / TILE_SIZE] == 0)
			p->pos.x = new.x;
		if (g_window.map[(int)new.y / TILE_SIZE][(int)old.x / TILE_SIZE] == 0)
			p->pos.y = new.y;
	}
	if (g_window.map[(int)p->pos.y / TILE_SIZE][(int)p->pos.x / TILE_SIZE] == 1)
	{
		p->pos.x = old.x;
		p->pos.y = old.y;
	}
	if (p->turn_direction)
		p->facing_angle += p->rotation_speed * -p->turn_direction;
	norm_angle(&(p->facing_angle));
}

void	get_player_pos(t_player *p, int i, int j)
{
	p->pos.x = j * TILE_SIZE + TILE_SIZE / 2;
	p->pos.y = i * TILE_SIZE + TILE_SIZE / 2;
	if (g_window.map[i][j] == 'E')
		p->facing_angle = 0;
	else if (g_window.map[i][j] == 'S')
		p->facing_angle = M_PI / 2;
	else if (g_window.map[i][j] == 'W')
		p->facing_angle = M_PI;
	else if (g_window.map[i][j] == 'N')
		p->facing_angle = 3 * M_PI / 2;
	g_window.map[i][j] = 0;
	p->rotation_speed = 4 * (M_PI / 180);
	p->turn_direction = 0;
	p->walk_direction = 0;
	p->forward_key = 0;
	p->backward_key = 0;
}

int		main(int c, char **v)
{
	t_player	p;
	void		*mlx_ptr;
	int			fd;

	mlx_ptr = mlx_init();
	if ((c < 2) | ((fd = open(v[1], O_RDONLY)) < 0)
	|| ft_strncmp(*(v + 1) + ft_strlen(v[1]) - 4, ".cub", 4))
		print_error("invalid .cub file path");
	g_texture = ft_calloc(5, sizeof(t_texture));
	g_window.mlx_ptr = mlx_ptr;
	load_cub_file(fd, &p);
	check_elements();
	g_rays = malloc(sizeof(t_ray) * g_window.width);
	if (c > 3 || (c > 2 && ft_strncmp(v[2], "--save", 7)))
		print_error("invalid arguments!!");
	if (c > 2 && !ft_strncmp(v[2], "--save", 7))
		make_bmp(&p);
	mlx_hook(g_window.win_ptr, 2, 0, get_key, &p);
	mlx_hook(g_window.win_ptr, 3, 0, key_up, &p);
	mlx_hook(g_window.win_ptr, 17, 0, close_win, NULL);
	mlx_loop_hook(mlx_ptr, loop_hook, &p);
	mlx_loop(mlx_ptr);
	return (0);
}
