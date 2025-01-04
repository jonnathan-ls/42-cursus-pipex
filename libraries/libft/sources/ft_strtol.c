/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:24:46 by jlacerda          #+#    #+#             */
/*   Updated: 2024/12/25 20:33:56 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strtol(const char *hex)
{
	int	result;
	int	value;

	result = 0;
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		hex += 2;
	while (*hex)
	{
		if (ft_isdigit(*hex))
			value = *hex - '0';
		else if (*hex >= 'a' && *hex <= 'f')
			value = *hex - 'a' + 10;
		else if (*hex >= 'A' && *hex <= 'F')
			value = *hex - 'A' + 10;
		else
			break ;
		result = (result << 4) | value;
		hex++;
	}
	return (result);
}
