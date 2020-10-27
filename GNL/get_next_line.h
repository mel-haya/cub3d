/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <mel-haya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 04:52:18 by mel-haya          #+#    #+#             */
/*   Updated: 2020/03/14 00:14:12 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1000
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int		get_next_line(int fd, char **line);
void	*ft_calloc(size_t count, size_t size);
int		check_nl(char *buffer);
char	*ft_strjoin(char const *s1, char const *s2);
int		buffering(int fd, char **buffer);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*get_first_line(char **str);
int		free_buffer(char **buff, int i);
#endif
