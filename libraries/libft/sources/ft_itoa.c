/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:44:31 by jlacerda          #+#    #+#             */
/*   Updated: 2024/10/21 19:51:16 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	convert_number(char *str, int n, int index, int sign)
{
	str[index] = '\0';
	index--;
	while (index >= 0)
	{
		if (n < 0)
		{
			str[index] = -(n % 10) + '0';
			n = -(n / 10);
		}
		else
		{
			str[index] = n % 10 + '0';
			n = n / 10;
		}
		index--;
	}
	if (sign == -1)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	int		index;
	int		sign;
	char	*str;
	int		n_aux;

	index = 0;
	sign = 1;
	if (n == 0)
		index++;
	if (n < 0)
	{
		index++;
		sign = -1;
		n = n * -1;
	}
	n_aux = n;
	while (n_aux != 0)
	{
		n_aux = n_aux / 10;
		index++;
	}
	str = (char *)malloc(sizeof(char) * index + 1);
	if (str)
		convert_number(str, n, index, sign);
	return (str);
}
