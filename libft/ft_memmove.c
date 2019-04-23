/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 09:21:26 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 07:44:51 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*temp;

	temp = ft_strnew(len);
	if (temp)
	{
		temp = ft_memcpy(temp, src, len);
		dst = ft_memcpy(dst, temp, len);
	}
	return (dst);
}
