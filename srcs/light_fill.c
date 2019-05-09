/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:56:48 by gfranco           #+#    #+#             */
/*   Updated: 2019/05/08 18:43:50 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		light_fill(int fd, t_prim *prim, int index)
{
	prim[index].light.src = vec3_extract(fd);
	prim[index].light.color = color_extract(fd);
}
