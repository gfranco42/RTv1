/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 11:15:52 by gfranco           #+#    #+#             */
/*   Updated: 2018/05/14 11:46:03 by gfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*delete;
	t_list	*nextlst;

	delete = *alst;
	nextlst = NULL;
	while (delete != NULL)
	{
		nextlst = delete->next;
		del(delete->content, delete->content_size);
		free(delete);
		delete = nextlst;
	}
	*alst = NULL;
}
