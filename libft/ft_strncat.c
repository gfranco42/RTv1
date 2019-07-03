/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:22:39 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 07:58:27 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	len;
	size_t	lvl;

	lvl = 0;
	len = ft_strlen(s1);
	s1[len] = s2[lvl];
	while (lvl < n && s2[lvl])
	{
		s1[len] = s2[lvl];
		len++;
		lvl++;
	}
	s1[len] = '\0';
	return (s1);
}
