/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:44:31 by jlacerda          #+#    #+#             */
/*   Updated: 2024/12/21 20:08:29 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*lst_aux;
	t_list	*new_lst_content;

	if (!lst || !f)
		return (NULL);
	lst_aux = lst;
	new_lst = ft_lstnew(f(lst_aux->content));
	if (!new_lst)
		return (NULL);
	lst_aux = lst_aux->next;
	while (lst_aux)
	{
		new_lst_content = ft_lstnew(f(lst_aux->content));
		if (!new_lst_content)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_lst_content);
		lst_aux = lst_aux->next;
	}
	return (new_lst);
}
