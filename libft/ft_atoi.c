/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 10:59:43 by gfranco           #+#    #+#             */
/*   Updated: 2018/12/03 15:38:12 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	long	ret;
	int		sign;
	int		idx;

	ret = 0;
	idx = 0;
	while (ft_isspace(str[idx]))
		idx++;
	sign = str[idx] == '-' ? -1 : 1;
	if (str[idx] == '+' || str[idx] == '-')
		idx++;
	while (ft_isdigit(str[idx]))
		ret = ret * 10 + str[idx++] - '0';
	return ((int)ret * sign);
}
