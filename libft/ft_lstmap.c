/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 17:45:40 by gfranco           #+#    #+#             */
/*   Updated: 2018/06/01 18:29:36 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*save;

	new = NULL;
	save = lst;
	if (lst != NULL)
	{
		new = (t_list *)malloc(sizeof(lst));
		if (!new)
			return (NULL);
		new = f(lst);
		lst = lst->next;
		new->next = ft_lstmap(lst, f);
	}
	lst = save;
	return (new);
}
