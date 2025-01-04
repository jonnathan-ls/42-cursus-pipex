/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:52:12 by jlacerda          #+#    #+#             */
/*   Updated: 2024/12/21 20:15:22 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_lst	*ft_get_nbr(int n)
{
	long	nbr;
	t_lst	*lst;
	int		has_sign;

	nbr = n;
	has_sign = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		has_sign = 1;
	}
	if (nbr > 9)
	{
		lst = ft_get_nbr(nbr / 10);
		ft_add_back_lst(&lst, ft_new_lst(nbr % 10 + '0'));
	}
	else
		lst = ft_new_lst(nbr % 10 + '0');
	if (has_sign)
		ft_add_front_lst(&lst, ft_new_lst('-'));
	return (lst);
}
