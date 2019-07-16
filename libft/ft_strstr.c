/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:46:06 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/02 08:44:47 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_word(const char *str, const char *word, size_t save)
{
	size_t		w;

	w = 0;
	while (word[w] && word[w] == str[save])
	{
		w++;
		save++;
	}
	if (word[w] == '\0')
		return (1);
	else
		return (2);
}

static int	search(char *str, char *word)
{
	int		save;
	int		s;
	int		w;

	s = 0;
	w = 0;
	while (str[s])
	{
		w = 0;
		if (word[w] != str[s] && str[s])
			s++;
		save = s;
		if (str[s] == '\0')
			return (-1);
		else if (word[w] == str[s])
		{
			if (check_word(str, word, save) == 1)
				return (save);
		}
		s++;
	}
	return (-1);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	int		save;

	if (needle[0] == '\0')
		return (&((char *)haystack)[0]);
	save = search((char *)haystack, (char *)needle);
	if (save == -1)
		return (NULL);
	return (&((char *)haystack)[save]);
}
