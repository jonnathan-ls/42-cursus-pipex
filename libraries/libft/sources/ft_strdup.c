/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:20:23 by jlacerda          #+#    #+#             */
/*   Updated: 2024/10/21 18:45:34 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		src_size;
	char	*str_cpy;

	src_size = ft_strlen(src);
	str_cpy = (char *)malloc(src_size + 1);
	if (str_cpy != NULL)
	{
		ft_strlcpy(str_cpy, src, src_size + 1);
	}
	return (str_cpy);
}
