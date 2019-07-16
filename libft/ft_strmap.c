/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:25:18 by gfranco           #+#    #+#             */
/*   Updated: 2018/05/17 11:25:25 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*tab;
	size_t	a;

	a = 0;
	if (!s)
		return (NULL);
	if (!(tab = (char *)ft_memalloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (a < ft_strlen(s))
	{
		tab[a] = f(s[a]);
		a++;
	}
	tab[a] = '\0';
	return (tab);
}
