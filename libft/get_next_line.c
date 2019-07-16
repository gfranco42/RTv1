/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:30:47 by gfranco           #+#    #+#             */
/*   Updated: 2018/11/16 13:09:33 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strndup(const char *stock)
{
	char		*line;
	int			i;

	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	line = (char*)ft_memalloc(i + 1);
	ft_strncpy(line, stock, i);
	return (line);
}

int				ft_ret_value(char **stock, char **line)
{
	char		*tmp;

	tmp = ft_strchr(*stock, '\n');
	if (tmp[0] == '\n')
	{
		*line = ft_strndup(*stock);
		ft_strcpy(*stock, tmp + 1);
		return (1);
	}
	return (0);
}

int				short_return(int res, int fd, char **line, char **stock)
{
	if (res == -1 || fd < 0 || BUFF_SIZE < 1 || !line)
		return (-1);
	ft_strdel(stock);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char	*stock = NULL;
	char		buff[BUFF_SIZE + 1];
	int			res;

	if (!stock)
		stock = ft_strnew(0);
	while (!(ft_strchr(stock, '\n')))
	{
		res = read(fd, buff, BUFF_SIZE);
		if (res == -1 || (res == 0 && ft_strlen(stock) == 0))
			return (short_return(res, fd, line, &stock));
		buff[res] = '\0';
		stock = ft_strjoinclr(stock, buff);
		if (res == 0 && ft_strlen(stock) > 0)
		{
			*line = ft_strndup(stock);
			ft_strdel(&stock);
			return (1);
		}
	}
	return (ft_ret_value(&stock, line));
}
