/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 20:05:00 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/14 13:55:03 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*make_bmp_header(t_bitmapheader *header)
{
	char	*buf;

	buf = ft_calloc(54, 1);
	header->bit_count = 24;
	header->width_in_bytes = ((g_window.width * header->bit_count + 31)
	/ 32) * 4;
	header->image_size = header->width_in_bytes * g_window.height;
	header->size = 54 + header->image_size;
	header->off_bits = 54;
	header->info_size = 40;
	header->planes = 1;
	header->width = g_window.width;
	header->height = g_window.height;
	ft_memcpy(buf, "BM", 2);
	ft_memcpy(buf + 2, &(header->size), 4);
	ft_memcpy(buf + 10, &(header->off_bits), 4);
	ft_memcpy(buf + 14, &(header->info_size), 4);
	ft_memcpy(buf + 18, &(header->width), 4);
	ft_memcpy(buf + 22, &(header->height), 4);
	ft_memcpy(buf + 26, &(header->planes), 2);
	ft_memcpy(buf + 28, &(header->bit_count), 2);
	ft_memcpy(buf + 34, &(header->image_size), 4);
	return (buf);
}

int		*get_colors(int color)
{
	int *colors;

	colors = malloc(3 * sizeof(int));
	colors[0] = ((color >> 16) & 0xFF);
	colors[1] = ((color >> 8) & 0xFF);
	colors[2] = ((color) & 0xFF);
	return (colors);
}

char	*make_img_buff(t_bitmapheader *header)
{
	char	*buf;
	int		i;
	int		j;
	int		*colors;

	buf = malloc(header->image_size);
	i = header->height - 1;
	while (i > 0)
	{
		j = 0;
		while (j < header->width)
		{
			colors = get_colors(g_data[((g_window.height - i)
			* g_window.width) + j]);
			buf[i * header->width_in_bytes + j * 3 + 2] = colors[0];
			buf[i * header->width_in_bytes + j * 3 + 1] = colors[1];
			buf[i * header->width_in_bytes + j * 3 + 0] = colors[2];
			free(colors);
			j++;
		}
		i--;
	}
	return (buf);
}

void	make_bmp(t_player *p)
{
	t_bitmapheader	header;
	char			*header_str;
	char			*img_buf;

	header.fd = open("./screenshot.bmp", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	loop_hook(p);
	header_str = make_bmp_header(&header);
	img_buf = make_img_buff(&header);
	write(header.fd, header_str, 54);
	write(header.fd, img_buf, header.image_size);
	free(header_str);
	free(img_buf);
	close_win();
}
