/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:49:08 by jlacerda          #+#    #+#             */
/*   Updated: 2024/10/21 18:56:11 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c)
		{
			count++;
			while (s[index] != c && s[index] != '\0')
				index++;
		}
		else
			index++;
	}
	return (count);
}

static void	ft_free_array(char **array, int array_index)
{
	while (array_index >= 0)
	{
		free(array[array_index]);
		array_index--;
	}
	free(array);
}

static char	*ft_put_word(char const *s, char c, size_t *index)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[*index + len] && s[*index + len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, (s + *index), len + 1);
	*index += len;
	return (word);
}

static int	ft_fill_array(char const *s, char c, char **array)
{
	size_t	index;
	int		array_index;

	index = 0;
	array_index = 0;
	while (s[index])
	{
		if (s[index] != c)
		{
			array[array_index] = ft_put_word(s, c, &index);
			if (!array[array_index])
			{
				ft_free_array(array, array_index - 1);
				return (0);
			}
			array_index++;
		}
		else
			index++;
	}
	array[array_index] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**array;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	if (!ft_fill_array(s, c, array))
		return (NULL);
	return (array);
}
