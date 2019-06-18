/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:21:26 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/18 14:04:26 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

// ---------------  initialisation des variables -----------------------------

void		initialize_light(t_light *l, t_prim *p_l)
{
	l->src.x = p_l->src.x;
	l->src.y = p_l->src.y;
	l->src.z = p_l->src.z;
	l->color.r = p_l->color.r;
	l->color.g = p_l->color.g;
	l->color.b = p_l->color.b;

}
