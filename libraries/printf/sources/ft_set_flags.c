/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:52:12 by jlacerda          #+#    #+#             */
/*   Updated: 2024/12/21 20:15:22 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}

static void	ft_init_flags(t_flags *flags)
{
	flags->sign = 0;
	flags->space = 0;
	flags->min_width = 0;
	flags->precision = 0;
	flags->alternate = 0;
	flags->align_left = 0;
	flags->width_value = 0;
	flags->zero_padding = 0;
	flags->precision_value = -1;
}

static int	ft_str_has_flag(char *str, char chr)
{
	while (*str && *str != chr)
		str++;
	if (*str == chr)
		return (1);
	return (0);
}

static int	ft_set_flags_with_value(const char **chr, t_flags *flags)
{
	if ((**chr >= '0' && **chr <= '9'))
	{
		flags->min_width = 1;
		flags->width_value = ft_atoi(*chr);
		while (**chr >= '0' && **chr <= '9')
			(*chr)++;
		return (1);
	}
	if (**chr == PRECISION_FLAG && !flags->precision)
	{
		flags->precision = 1;
		(*chr)++;
		flags->precision_value = ft_atoi(*chr);
		while ((**chr >= '0' && **chr <= '9'))
			(*chr)++;
		return (1);
	}
	return (0);
}

void	ft_set_flags(const char **chr, t_flags *flags)
{
	ft_init_flags(flags);
	while (ft_str_has_flag(FLAGS, **chr) || (**chr >= '0' && **chr <= '9'))
	{
		if (**chr == ALIGN_LEFT_FLAG && !flags->align_left)
			flags->align_left = 1;
		else if (**chr == SIGN_FLAG && !flags->sign)
			flags->sign = 1;
		else if (**chr == ALTERNATE_FLAG && !flags->alternate)
			flags->alternate = 1;
		else if (**chr == ZERO_PADDING_FLAG && !flags->zero_padding)
			flags->zero_padding = 1;
		else if (**chr == SPACE_FLAG && !flags->space)
			flags->space = 1;
		if (!ft_set_flags_with_value(chr, flags))
			(*chr)++;
	}
}
