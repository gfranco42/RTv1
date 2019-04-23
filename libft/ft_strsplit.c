/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 11:39:04 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 07:30:09 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_word(char const *s, char c, int idx)
{
	int			count;

	count = 0;
	while (s[idx] != c && s[idx])
	{
		idx++;
		count++;
	}
	return (count);
}

static int		count_word(char const *s, char c)
{
	int			count;
	int			index;

	count = 0;
	index = 0;
	while (s[index])
	{
		while (s[index] == c && s[index])
			index++;
		if (s[index])
			count++;
		while (s[index] != c && s[index])
			index++;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**tab;
	int			word;
	int			idx;
	int			idx_tab;

	if (!s)
		return (NULL);
	word = count_word(s, c);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (word + 1))))
		return (NULL);
	idx = 0;
	idx_tab = 0;
	while (word--)
	{
		while (s[idx] == c && s[idx])
			idx++;
		if (!(tab[idx_tab] = ft_strsub(s, idx, len_word(s, c, idx))))
			return (tab);
		while (s[idx] != c && s[idx])
			idx++;
		idx_tab++;
	}
	return (tab);
}
