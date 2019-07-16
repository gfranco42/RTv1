/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:59:41 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/25 02:20:17 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		plane_ch(int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 3)
	{
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
}
