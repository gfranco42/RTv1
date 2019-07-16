/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:35:26 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 07:47:55 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str11;
	unsigned char	*str22;
	size_t			a;

	a = 0;
	str11 = (unsigned char *)s1;
	str22 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (str11[a] == str22[a] && a < n - 1)
		a++;
	return (str11[a] - str22[a]);
}
