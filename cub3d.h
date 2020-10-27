/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:26:26 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/14 13:54:31 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include "GNL/get_next_line.h"
# include "libft/libft.h"
# include "mlx.h"
# define TILE_SIZE 64
# define ESC 53
# define NO 3
# define SO 1
# define EA 2
# define WE 0
# define S 4
# define MOV_SPEED TILE_SIZE / 10
# define KEY_UP 13
# define KEY_LEFT 0
# define KEY_DOWN 1
# define KEY_RIGHT 2
# define FOV_ANGLE 60 * (M_PI / 180)
# define MINI_MAP_RATIO 0.2
# define DEG(x) x * (180 / M_PI)

typedef struct	s_point
{
	float x;
	float y;
}				t_point;

typedef struct	s_sprite
{
	t_point		pos;
	float		distance;
}				t_sprite;

typedef struct	s_texture
{
	int *data;
	int height;
	int width;
}				t_texture;

typedef struct	s_ray
{
	float	ray_angle;
	int		facing_down;
	int		facing_left;
	float	distance;
	int		hit_horz;
	int		hit_vert;
	t_point	horz_collision;
	t_point	vert_collision;
	t_point	closest_collision;
	int		inv;
	int		inh;
}				t_ray;

typedef struct	s_window
{
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*win_ptr;
	int			**map;
	int			map_rows;
	int			map_cols;
	int			floor;
	int			ceiling;
	int			sprite_index;
	t_sprite	sprite[500];
	float		projection_plane;
}				t_window;

typedef struct	s_bitmapheader{
	uint32_t	file_size;
	uint32_t	off_bits;
	uint32_t	size;
	uint32_t	info_size;
	int32_t		width;
	int32_t		height;
	uint16_t	planes;
	uint16_t	bit_count;
	uint32_t	image_size;
	int			width_in_bytes;
	int			fd;
}				t_bitmapheader;

typedef struct	s_player
{
	t_point		pos;
	int			walk_direction;
	float		facing_angle;
	int			move_speed;
	float		rotation_speed;
	int			turn_direction;
	void		*win_ptr;
	void		*mlx_ptr;
	int			forward_key;
	int			backward_key;
}				t_player;

int				close_win();
void			free_matrix(void **array, int length);
void			render_sprite(t_player *p);
void			print_error(const char *error);
void			draw_sprite(int x, float distance, float height);
void			sort_sprites(t_player *p);
void			render_sprite(t_player *p);
float			dist_two_point(t_point p1, t_point p2);
void			norm_angle(float *angle);
t_point			make_point(float x, float y);
int				in_canvas(t_point p);
void			check_map(char *line);
int				load_map(char *line, int fd, t_player *p, int *count);
void			init_window(char **words, int *count, char *line);
int				is_texture(char *element);
void			load_cub_file(int fd, t_player *p);
char			*filter(char *str, char const *set);
int				check_row(char *line);
int				ft_word_count(char const *str, char c);
void			fill_map(char *line, t_player *p);
void			rgb_color(char **colors, int *count, char *line);
void			load_textures(char **filename, int *count, char *line);
int				check_num(char *num, int min, int max);
int				is_floor_ceiling(char *element);
void			check_elements(void);
void			fill_map(char *line, t_player *p);
void			get_player_pos(t_player *p, int i, int j);
int				count_char(char *s, char c);
int				is_valid_element(char c);
int				get_key(int key, t_player *p);
int				key_up(int key, t_player *p);
int				loop_hook(t_player *p);
int				close_win(void);
void			cast_rays(t_player *p);
void			render_walls(t_player *p);
void			move_player(t_player *p);
void			make_bmp(t_player *p);
t_point			horz_intersection(t_player *p, int column_id);
void			render_walls(t_player *p);
void			cast_rays(t_player *p);
void			move_player(t_player *p);
void			get_player_pos(t_player *p, int i, int j);
void			*g_map_img;
int				*g_data;
t_texture		*g_texture;
t_ray			*g_rays;
t_window		g_window;
#endif
