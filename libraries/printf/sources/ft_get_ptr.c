/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:52:12 by jlacerda          #+#    #+#             */
/*   Updated: 2024/12/21 20:15:22 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_lst	*ft_get_ptr(void *ptr)
{
	t_lst	*ptr_node;
	t_lst	*hex_node;

	if (!ptr)
		ptr_node = ft_get_str("(nil)");
	else
	{
		ptr_node = ft_get_str("0x");
		hex_node = ft_get_hex((unsigned long)ptr, HEX_BASE_LOWER);
		ft_add_back_lst(&ptr_node, hex_node);
	}
	return (ptr_node);
}
