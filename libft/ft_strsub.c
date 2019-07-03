/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 10:42:42 by gfranco           #+#    #+#             */
/*   Updated: 2018/05/17 11:28:23 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tab;
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	if (!s)
		return (NULL);
	if (!(tab = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (len == 0)
		return (tab);
	while (a < len)
	{
		tab[a++] = s[start++];
	}
	return (tab);
}
