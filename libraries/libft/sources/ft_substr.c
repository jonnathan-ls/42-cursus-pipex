/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:43:57 by jlacerda          #+#    #+#             */
/*   Updated: 2024/10/16 20:14:00 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	substr_len;
	char	*substr;

	i = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
		substr_len = 0;
	else if (start + len > s_len)
		substr_len = s_len - start;
	else
		substr_len = len;
	substr = (char *)malloc(substr_len + 1);
	if (substr)
	{
		while (i < len && start + i < s_len)
		{
			substr[i] = s[start + i];
			i++;
		}
		substr[i] = '\0';
	}
	return (substr);
}
