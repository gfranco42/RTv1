/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 13:59:05 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 07:54:56 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tab;

	tab = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!tab)
		return (NULL);
	ft_strcpy(tab, s1);
	return (tab);
}
