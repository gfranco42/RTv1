/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:46:05 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 07:41:45 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		check_sign(int nbr)
{
	if (nbr < 0)
		return (1);
	return (0);
}

static int		nbr_len(int nbr)
{
	int			count;

	count = 0;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

static int		nbr_power(long long nbr)
{
	int			len;
	int			count;
	size_t		power;

	power = 1;
	count = 0;
	len = nbr_len(nbr);
	while (count < len)
	{
		power = power * 10;
		count++;
	}
	return (power / 10);
}

static char		*nbr_cpy(long long nbr)
{
	int			len;
	int			a;
	size_t		power;
	char		*dest;

	len = nbr_len(nbr);
	a = 0;
	power = nbr_power(nbr);
	if (!(dest = (char*)malloc(sizeof(char) * (len + check_sign(nbr) + 1))))
		return (NULL);
	if (check_sign(nbr) == 1)
	{
		dest[a] = '-';
		nbr = nbr * -1;
		a++;
	}
	while (power >= 1)
	{
		dest[a] = nbr / power % 10 + 48;
		a++;
		power = power / 10;
	}
	dest[a] = '\0';
	return (dest);
}

char			*ft_itoa(int n)
{
	char		*string;
	long long	nbr;

	string = NULL;
	if (n == 0)
		return (ft_strdup("0"));
	nbr = (long long)n;
	string = nbr_cpy(nbr);
	return (string);
}
