/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:54:19 by gfranco           #+#    #+#             */
/*   Updated: 2019/06/20 18:14:52 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		key(int key, void *param)
{
	t_all	*all;

	printf("%i\n", key);
	all = (t_all*)param;
	if (key == 53)
		exit(0);
	return (0);
}
