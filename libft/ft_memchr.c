/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:01:12 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 07:46:08 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			find;
	unsigned char	*str2;
	unsigned char	c2;

	find = 0;
	str2 = (unsigned char *)s;
	c2 = (unsigned char)c;
	if (!n)
		return (NULL);
	while (find < n && str2[find] != c2)
		find++;
	if (find == n)
		return (NULL);
	return (&str2[find]);
}
