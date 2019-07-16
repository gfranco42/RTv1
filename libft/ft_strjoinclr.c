/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 10:04:22 by gfranco           #+#    #+#             */
/*   Updated: 2018/10/05 17:35:07 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinclr(char *s1, char const *s2)
{
	char	*tab;

	if (!s1 || !s2)
		return (NULL);
	tab = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tab)
		return (NULL);
	ft_strcpy(tab, s1);
	ft_strcat(tab, s2);
	free(s1);
	return (tab);
}
