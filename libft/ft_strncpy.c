/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:52:57 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 07:59:53 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	a;

	a = 0;
	while (a < n && src[a] != '\0')
	{
		dst[a] = src[a];
		a++;
	}
	while (a < n)
	{
		dst[a] = '\0';
		a++;
	}
	return (dst);
}
