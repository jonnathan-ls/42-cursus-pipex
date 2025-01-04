/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_unbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:52:12 by jlacerda          #+#    #+#             */
/*   Updated: 2024/12/21 20:15:22 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_lst	*ft_get_unbr(unsigned int ui)
{
	t_lst	*uns_nbr_node;

	if (ui < 10)
	{
		uns_nbr_node = ft_new_lst(ui + '0');
		return (uns_nbr_node);
	}
	uns_nbr_node = ft_get_unbr(ui / 10);
	ft_add_back_lst(&uns_nbr_node, ft_new_lst(ui % 10 + '0'));
	return (uns_nbr_node);
}
