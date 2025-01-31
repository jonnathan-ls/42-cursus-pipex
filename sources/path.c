/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/31 00:39:48 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

/**
 * @brief Retrieves the PATH environment variable from the environment array
 * 
 * This function searches through the environment array for the PATH variable.
 * It returns the value of the PATH variable if found, or NULL if not found.
 * 
 * @param envp Pointer to the environment array
 * @param index Index of the environment variable to check
 * @return char* Pointer to the PATH environment variable, or NULL if not found
 */
static char	*get_path_token(char **envp, int index)
{
	if (!envp || !envp[index])
		return (NULL);
	if (ft_strnstr(envp[index], PATH_ENV_VAR, PATH_ENV_VAR_LENGTH))
		return (envp[index] + PATH_PREFIX_LENGTH);
	return (get_path_token(envp, index + 1));
}

/**
 * @brief Searches for the executable path in the given path tokens
 * 
 * This function constructs a full path by appending 
	* the command to the path token.
 * It returns the constructed path if found, or NULL if not found.
 * 
 * @param cmd Command to search for
 * @param tokens Path tokens to search in
 * @param index Index of the path token to use
 * @return char* Full path to the executable, or NULL if not found
 */
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

/**
 * @brief Searches for the executable path in the given path tokens
 * 
 * This function iterates through the path
	* tokens and constructs a full path by
 * appending the command to each path token. 
	* It returns the first valid path found,
 * or NULL if no valid path is found.
 * 
 * @param cmd Command to search for
 * @param path_tokens Path tokens to search in
 * @return char* Full path to the executable, or NULL if not found
 */
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

/**
 * @brief Finds the executable path for the given command
 * 
 * This function retrieves the PATH environment variable, splits it into tokens,
 * and searches for the executable path in the given path tokens.
 * 
 * @param cmd Command to search for
 * @param envp Environment variables array
 * @return char* Full path to the executable, or NULL if not found
 */
char	*find_executable_path(char *cmd, char **envp)
{
	char	**path_tokens;

	path_tokens = ft_split(get_path_token(envp, 0), DOUBLE_COLON_CHAR);
	if (!path_tokens)
		return (NULL);
	return (search_in_path_tokens(cmd, path_tokens));
}

/**
 * @brief Retrieves the executable path for the given command
 * 
 * This function checks if the command is a full path or a relative path.
 * It returns the command itself if it's a full path and accessible,
 * or NULL if not found.
 * 
 * @param cmd Command to search for
 * @param envp Environment variables array
 * @return char* Full path to the executable, or NULL if not found
 */
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
