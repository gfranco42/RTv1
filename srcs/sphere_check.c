/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:59:21 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/25 02:35:18 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		sphere_ch_ext(int fd, char *line)
{
	if (ft_strcmp(line, "") == 0)
		fail(1);
	free(line);
	if (get_next_line(fd, &line) > 0)
	{
		if (check_vec3(line) == 0)
			fail(1);
	}
	else
		fail(1);
	if (ft_strcmp(line, "") == 0)
		fail(1);
	free(line);
}

void		sphere_ch(int fd)
{
	int		i;
	char	*line;

	i = -1;
	if (get_next_line(fd, &line) > 0)
	{
		if (check_vec3(line) == 0)
			fail(1);
	}
	else
		fail(1);
	if (ft_strcmp(line, "") == 0)
		fail(1);
	free(line);
	if (get_next_line(fd, &line) > 0)
	{
		if (str_isdigit(line) == 0)
			fail(1);
	}
	else
		fail(1);
	sphere_ch_ext(fd, line);
}
