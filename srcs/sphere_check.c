/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:59:21 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/08 16:58:28 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		sphere_ch(int fd)
{
	int		i;
	char	*line;

	i = -1;
	if (get_next_line(fd, &line) > 0)
		if (check_vec3(line) == 0)
			fail(1);
	if (ft_strcmp(line, "") == 0)
		fail(1);
	free(line);
	if (get_next_line(fd, &line) > 0)
		if (str_isdigit(line) == 0)
			fail(1);
	if (ft_strcmp(line, "") == 0)
		fail(1);
	free(line);
	if (get_next_line(fd, &line) > 0)
		if (check_vec3(line) == 0)
			fail(1);
	if (ft_strcmp(line, "") == 0)
		fail(1);
	free(line);
	printf("sphere OK\n");
}
