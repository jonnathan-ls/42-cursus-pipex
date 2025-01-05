/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/04 22:21:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

static void *free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	*find_executable_path(char *cmd, char **envp)
{
	char	**path_tokens;
	char	*partial_path;
	char	*final_path;
	int		index;

	index = 0;
	while (!ft_strnstr(envp[index], PATH_ENV_VAR, PATH_ENV_VAR_LENGTH))
		index++;
	path_tokens = ft_split(envp[index] + PATH_ENV_VAR_LENGTH + 1, DOUBLE_COLON_CHAR);
	index = 0;
	while (path_tokens[index])
	{
		partial_path = ft_strjoin(path_tokens[index], SLASH_STRING);
		if (!partial_path)
			return free_split(path_tokens);
		final_path = ft_strjoin(partial_path, cmd);
		free(partial_path);
		if (!final_path)
			return free_split(path_tokens);
		if (access(final_path, F_OK) == ACCESS_SUCCESS)
		{
			free_split(path_tokens);
			return (final_path);
		}
		free(final_path);
		index++;
	}
	free_split(path_tokens);
	return (NULL);
}

static void	free_fds(t_fds *fds, char *error_message)
{
	perror(error_message);
	close(fds->outfile);
	close(fds->infile);
	free(fds);
}

void	pipex(t_params *params, t_fds *fds, char **envp)
{
	int		pipefd[2];
	pid_t	pid_process;
	char	*executable_path;

	if (pipe(pipefd) == PROCESS_FAILURE)
		return (free_fds(fds, PIPE_ERROR_MESSAGE));
	pid_process = fork();
	if (pid_process == PROCESS_FAILURE)
		return (free_fds(fds, FORK_ERROR_MESSAGE));
	if (pid_process == LEFT_PIPE_PROCESS)
	{
		dup2(fds->infile, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(fds->infile); 
		executable_path = find_executable_path(params->left_cmd_args[0], envp);
		if (!executable_path)
			return (free_fds(fds, EXECVE_ERROR_MESSAGE));
		params->left_cmd_args[0] = executable_path;
		execve(params->left_cmd_args[0], params->left_cmd_args, envp);
		perror(EXECVE_ERROR_MESSAGE);
	}
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(fds->outfile, STDOUT_FILENO);
		close(pipefd[1]);
		close(fds->outfile);
		executable_path = find_executable_path(params->right_cmd_args[0], envp);
		if (!executable_path)
			return (free_fds(fds, EXECVE_ERROR_MESSAGE));
		params->right_cmd_args[0] = executable_path;
		execve(params->right_cmd_args[0], params->right_cmd_args, envp);
		perror(EXECVE_ERROR_MESSAGE);
	}
}
