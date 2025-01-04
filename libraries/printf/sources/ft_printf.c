/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:52:12 by jlacerda          #+#    #+#             */
/*   Updated: 2024/12/21 20:15:22 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_lst	*ft_get_argument(va_list *args, char arg_type)
{
	t_lst	*arg;

	arg = NULL;
	if (arg_type == CHR_ARG_TYPE)
		arg = ft_get_chr(va_arg(*args, int));
	else if (arg_type == STR_ARG_TYPE)
		arg = ft_get_str(va_arg(*args, char *));
	else if (arg_type == PTR_ARG_TYPE)
		arg = ft_get_ptr(va_arg(*args, void *));
	else if (arg_type == DIG_ARG_TYPE || arg_type == INT_ARG_TYPE)
		arg = ft_get_nbr(va_arg(*args, int));
	else if (arg_type == UNS_ARG_TYPE)
		arg = ft_get_unbr(va_arg(*args, unsigned int));
	else if (arg_type == HEX_LOWER_ARG_TYPE)
		arg = ft_get_hex(va_arg(*args, unsigned int), HEX_BASE_LOWER);
	else if (arg_type == HEX_UPPER_ARG_TYPE)
		arg = ft_get_hex(va_arg(*args, unsigned int), HEX_BASE_UPPER);
	else if (arg_type == '%')
		arg = ft_get_chr('%');
	return (arg);
}

static int	ft_print_argument(const char *str, va_list *args, t_flags *flags)
{
	t_lst	*arg;
	t_lst	*print_node;
	int		print_count;
	char	arg_type;

	print_count = 0;
	arg_type = *str;
	arg = ft_get_argument(args, arg_type);
	ft_set_padding(&arg, flags, arg_type);
	while (arg)
	{
		print_node = arg;
		print_count += write(1, &print_node->chr, 1);
		arg = arg->next;
		free(print_node);
	}
	return (print_count);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	t_flags	flags;
	int		print_size;

	if (!fmt)
		return (-1);
	print_size = 0;
	va_start(args, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			ft_set_flags(&fmt, &flags);
			print_size += ft_print_argument(fmt, &args, &flags);
		}
		else
			print_size += write(1, fmt, 1);
		fmt++;
	}
	va_end(args);
	return (print_size);
}
