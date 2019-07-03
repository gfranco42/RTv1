/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:22:39 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 07:52:41 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t		lvl;
	size_t		len;

	lvl = 0;
	len = ft_strlen(s1);
	while (s2[lvl])
	{
		s1[len + lvl] = s2[lvl];
		lvl++;
	}
	s1[len + lvl] = '\0';
	return (s1);
}
