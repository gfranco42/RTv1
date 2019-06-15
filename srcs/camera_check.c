/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 11:47:51 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/14 16:29:36 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		camera_ch(int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 3)
	{
		if (get_next_line(fd, &line) > 0)
			if (check_vec3(line) == 0)
				fail(1);
		if (ft_strcmp(line, "") == 0)
			fail(1);
		free(line);
	}
}
