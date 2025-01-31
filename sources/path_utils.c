/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/30 21:20:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

static char	*get_path_token(char **envp, int index)
{
	if (!envp || !envp[index])
		return (NULL);
	if (ft_strnstr(envp[index], PATH_ENV_VAR, PATH_ENV_VAR_LENGTH))
		return (envp[index] + PATH_PREFIX_LENGTH);
	return (get_path_token(envp, index + 1));
}

static char	*search_tokens(char *cmd, char **tokens, int index)
{
	char	*partial;
	char	*final;

	partial = ft_strjoin(tokens[index], SLASH_STRING);
	if (!partial)
		return (free_split(tokens), NULL);
	final = ft_strjoin(partial, cmd);
	free(partial);
	if (!final)
		return (free_split(tokens), NULL);
	return (final);
}

char	*search_in_path_tokens(char *cmd, char **path_tokens)
{
	char	*final_path;
	int		index;

	index = 0;
	while (path_tokens[index])
	{
		final_path = search_tokens(cmd, path_tokens, index);
		if (!final_path)
			return (NULL);
		if (access(final_path, F_OK | X_OK) == ACCESS_SUCCESS)
			return (free_split(path_tokens), final_path);
		free(final_path);
		index++;
	}
	free_split(path_tokens);
	return (NULL);
}

char	*find_executable_path(char *cmd, char **envp)
{
	char	**path_tokens;

	path_tokens = ft_split(get_path_token(envp, 0), DOUBLE_COLON_CHAR);
	if (!path_tokens)
		return (NULL);
	return (search_in_path_tokens(cmd, path_tokens));
}

char	*get_executable_path(char *cmd, char **envp)
{
	if (ft_strchr(cmd, SLASH_CHAR))
	{
		if (access(cmd, F_OK | X_OK) == ACCESS_SUCCESS)
			return (cmd);
		return (NULL);
	}
	return (find_executable_path(cmd, envp));
}
