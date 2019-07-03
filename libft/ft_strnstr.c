/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 13:59:58 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 08:40:29 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	check;

	i = 0;
	check = 0;
	if (!(needle[i]))
		return ((char*)haystack);
	while (haystack[check] && check < len)
	{
		while (haystack[check] && haystack[i + check]
				== needle[i] && (i + check) < len)
		{
			i++;
			if (!(needle[i]))
				return ((char*)haystack + check);
		}
		i = 0;
		check++;
	}
	return (NULL);
}
