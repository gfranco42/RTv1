/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:22:08 by gfranco           #+#    #+#             */
/*   Updated: 2018/05/14 12:50:41 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		foll;
	char	*s2;
	char	c2;

	foll = ft_strlen(s);
	s2 = (char *)s;
	c2 = (char)c;
	if (s2[foll] == c2)
		return (&s2[foll]);
	else
	{
		while (s2[foll] != c2)
		{
			foll--;
			if (foll < 0)
				return (NULL);
		}
	}
	return (&s2[foll]);
}
