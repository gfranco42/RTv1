/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:58:46 by gfranco           #+#    #+#             */
/*   Updated: 2019/07/09 11:37:10 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			str_isdot(char *str)
{
	size_t		i;
	int			dot;

	i = -1;
	dot = 0;
	while (++i < ft_strlen(str))
	{
		if (str[i] == '.')
			return (1);
	}
	return (0);
}

int			str_isdouble(char *str)
{
	size_t		i;
	int			dot;

	i = -1;
	dot = 0;
	while (++i < ft_strlen(str))
	{
		if (ft_isdigit(str[i]) == 0)
		{
			if ((str[i] != '-' && str[i] != '.') || (str[i] == '-' && i != 0))
				return (0);
			else if ((str[i] == '.' && i == 0) || (str[i] == '.' && i == 1
			&& str[0] == '-'))
				return (0);
			else if (str[i] == '.' && dot == 0)
				dot++;
			else if (str[i] == '.' && dot != 0)
				return (0);
			if (str[i] == '.' && ft_isdigit(str[i + 1]) == 0)
				return (0);
		}
	}
	return (1);
}

int			str_isdigit(char *str)
{
	size_t		i;
	size_t		len;

	i = -1;
	len = ft_strlen(str);
	while (++i < len)
	{
		if (ft_isdigit(str[i]) == 0)
			if (str[i] != '-' || (str[i] == '-' && i != 0))
				return (0);
	}
	return (1);
}

int			check_vec3(char *line)
{
	char		**split;
	size_t		i;
	size_t		len;

	i = -1;
	if (!(split = ft_strsplit(line, ' ')))
		fail(3);
	len = 0;
	while (split[len] != NULL)
		len++;
	if (len != 3)
		fail(1);
	while (++i < len)
		if (str_isdouble(split[i]) == 0)
			return (0);
	i = -1;
	free_tab(split, 3);
	return (1);
}
