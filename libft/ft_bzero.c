/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:39:35 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/19 16:45:06 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *dst, size_t n)
{
	size_t	i;
	char	*pstr;

	pstr = (char*)dst;
	i = 0;
	while (i < n)
	{
		pstr[i] = 0;
		i++;
	}
}