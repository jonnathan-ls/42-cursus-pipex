/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:52:12 by jlacerda          #+#    #+#             */
/*   Updated: 2024/12/21 20:15:22 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_precision_str(t_lst **lst, t_flags *flags)
{
	int		index;
	t_lst	*tmp;
	t_lst	*tmp_lst;

	index = 0;
	tmp = NULL;
	tmp_lst = NULL;
	if ((*lst) && (*lst)->chr == '(' && flags->precision_value < 6)
		return (ft_free_lst(lst));
	while ((*lst) && index < flags->precision_value)
	{
		tmp = *lst;
		ft_add_back_lst(&tmp_lst, ft_new_lst((*lst)->chr));
		*lst = (*lst)->next;
		free(tmp);
		index++;
	}
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
	*lst = tmp_lst;
}

static void	ft_precision_nbr(t_lst **lst, t_flags *flags, int *len)
{
	t_lst	*tmp_lst;

	tmp_lst = NULL;
	if (ft_is_null_node_lst(*lst) && flags->precision_value == 0)
		return (ft_free_lst(lst));
	if ((*lst) && (*lst)->chr == '-' && *len <= flags->precision_value)
	{
		tmp_lst = ft_new_lst('-');
		(*lst)->chr = '0';
	}
	else if (flags->sign && *len < flags->precision_value)
	{
		tmp_lst = ft_new_lst('+');
		(*lst)->chr = '0';
	}
	while ((*len)++ < flags->precision_value)
		ft_add_front_lst(lst, ft_new_lst('0'));
	if (tmp_lst && tmp_lst->chr == '-')
		ft_add_front_lst(lst, ft_new_lst('-'));
	if (tmp_lst && tmp_lst->chr == '+')
		ft_add_front_lst(lst, ft_new_lst('+'));
	if (tmp_lst)
		free(tmp_lst);
}

static void	ft_precision_hex(t_lst **lst, t_flags *flags, int *len)
{
	t_lst	*tmp_lst;

	tmp_lst = NULL;
	if (ft_is_null_node_lst(*lst) && flags->precision_value == 0)
		return (ft_free_lst(lst));
	if (flags->alternate && (*lst)->next)
	{
		tmp_lst = ft_new_lst((*lst)->next->chr);
		flags->precision_value += 2;
		(*lst)->next->chr = '0';
	}
	while ((*len)++ < flags->precision_value)
		ft_add_front_lst(lst, ft_new_lst('0'));
	if (flags->alternate && tmp_lst)
		(*lst)->next->chr = tmp_lst->chr;
	if (tmp_lst)
		free(tmp_lst);
}

static void	ft_precision_ptr(t_lst **lst, t_flags *flags, int *len)
{
	t_lst	*tmp_lst;

	*len -= 2;
	tmp_lst = NULL;
	if (flags->sign)
	{
		tmp_lst = (*lst);
		(*lst) = (*lst)->next;
		*len -= 1;
	}
	while ((*len) < flags->precision_value && (*lst) && (*lst)->next)
	{
		(*lst)->next->chr = '0';
		ft_add_front_lst(lst, ft_new_lst('0'));
		(*lst)->next->chr = 'x';
		(*len)++;
	}
	if (tmp_lst && flags->precision_value > 0 && !flags->sign)
	{
		ft_add_front_lst(lst, ft_new_lst('x'));
		ft_add_front_lst(lst, ft_new_lst('0'));
	}
	if (flags->sign)
		ft_add_front_lst(lst, ft_new_lst(tmp_lst->chr));
}

void	ft_set_precision(t_lst **lst, t_flags *flags, char at, int *len)
{
	flags->zero_padding = 0;
	if (at == STR_ARG_TYPE)
		ft_precision_str(lst, flags);
	else if (at == DIG_ARG_TYPE || at == INT_ARG_TYPE)
		ft_precision_nbr(lst, flags, len);
	else if (at == HEX_LOWER_ARG_TYPE || at == HEX_UPPER_ARG_TYPE)
		ft_precision_hex(lst, flags, len);
	else if (at == PTR_ARG_TYPE && (*lst) && (*lst)->chr != '(')
		ft_precision_ptr(lst, flags, len);
	else if (at == UNS_ARG_TYPE)
	{
		if (ft_is_null_node_lst(*lst) && flags->precision_value == 0)
		{
			free(*lst);
			*lst = NULL;
		}
		else
		{
			while ((*len)++ < flags->precision_value)
				ft_add_front_lst(lst, ft_new_lst('0'));
		}
	}
	*len = ft_size_lst(*lst);
}
