/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/29 00:55:00 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

static char	*get_path_token(char **envp)
{
	int	index;

	index = 0;
	if (!envp)
		return (NULL);
	while (envp[index]
		&& !ft_strnstr(envp[index], PATH_ENV_VAR, PATH_ENV_VAR_LENGTH))
		index++;
	if (!envp[index])
		return (NULL);
	return (envp[index] + PATH_ENV_VAR_LENGTH + 1);
}

char	*find_executable_path(char *cmd, char **envp)
{
	char	**path_tokens;

	path_tokens = ft_split(get_path_token(envp), DOUBLE_COLON_CHAR);
	if (!path_tokens)
		return (NULL);
	return (search_in_path_tokens(cmd, path_tokens));
}

char	*search_in_path_tokens(char *cmd, char **path_tokens)
{
	char	*partial_path;
	char	*final_path;
	int		index;

	index = 0;
	while (path_tokens[index])
	{
		partial_path = ft_strjoin(path_tokens[index], SLASH_STRING);
		if (!partial_path)
			return (free_split(path_tokens), NULL);
		final_path = ft_strjoin(partial_path, cmd);
		free(partial_path);
		if (!final_path)
			return (free_split(path_tokens), NULL);
		if (access(final_path, F_OK | X_OK) == ACCESS_SUCCESS)
			return (free_split(path_tokens), final_path);
		free(final_path);
		index++;
	}
	free_split(path_tokens);
	return (NULL);
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
