/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 09:26:10 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 07:49:47 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			a;
	unsigned char	*i;
	char			s;

	i = (unsigned char*)b;
	s = (char)c;
	a = 0;
	if (n == 0)
		return (b);
	while (a < n)
	{
		i[a] = s;
		a++;
	}
	return (b);
}
