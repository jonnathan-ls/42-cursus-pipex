/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:43:57 by jlacerda          #+#    #+#             */
/*   Updated: 2024/10/16 20:22:18 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_size;
	size_t	s2_size;
	char	*joined_str;

	i = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	joined_str = (char *)malloc(s1_size + s2_size + 1);
	if (joined_str)
	{
		while (i < s1_size)
		{
			joined_str[i] = s1[i];
			i++;
		}
		while (i - s1_size < s2_size)
		{
			joined_str[i] = s2[i - s1_size];
			i++;
		}
		joined_str[i] = '\0';
	}
	return (joined_str);
}
