/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:51:03 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 07:53:01 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		foll;
	char	*str2;

	foll = 0;
	str2 = (char *)s;
	while (str2[foll] != c && str2[foll])
		foll++;
	if (str2[foll] == c)
		return (&str2[foll]);
	else
		return (NULL);
}
