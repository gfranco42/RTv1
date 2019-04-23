/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 08:18:20 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 07:47:10 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			s;
	unsigned char	*src2;
	unsigned char	*dest2;

	s = 0;
	src2 = (unsigned char *)src;
	dest2 = (unsigned char *)dst;
	while (s < n)
	{
		if (src2[s] == (unsigned char)c)
		{
			dest2[s] = src2[s];
			dest2 += s + 1;
			return ((void*)dest2);
		}
		dest2[s] = src2[s];
		s++;
	}
	return (NULL);
}
