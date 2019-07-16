/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:37:09 by gfranco           #+#    #+#             */
/*   Updated: 2018/05/16 13:19:56 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*tab;
	size_t	a;

	a = 0;
	if (!s)
		return (NULL);
	if (!(tab = (char *)malloc(sizeof(*tab) * (ft_strlen(s) + 1))))
		return (NULL);
	while (a < ft_strlen(s))
	{
		tab[a] = f(a, s[a]);
		a++;
	}
	tab[a] = '\0';
	return (tab);
}
