/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/05 20:44:49 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

static char	*get_path_token(char **envp)
{
	int	index;

	index = 0;
	while (!ft_strnstr(envp[index], PATH_ENV_VAR, PATH_ENV_VAR_LENGTH))
		index++;
	return (envp[index] + PATH_ENV_VAR_LENGTH + 1);
}

static char	*find_executable_path(char *cmd, char **envp)
{
	char	**path_tokens;
	char	*partial_path;
	char	*final_path;
	int		index;

	index = 0;
	path_tokens = ft_split(get_path_token(envp), DOUBLE_COLON_CHAR);
	if (!path_tokens)
		return (NULL);
	while (path_tokens[index])
	{
		partial_path = ft_strjoin(path_tokens[index], SLASH_STRING);
		if (!partial_path)
			return (free_split(path_tokens), NULL);
		final_path = ft_strjoin(partial_path, cmd);
		free(partial_path);
		if (!final_path)
			return (free_split(path_tokens), NULL);
		if (access(final_path, F_OK) == ACCESS_SUCCESS)
			return (free_split(path_tokens), final_path);
		free(final_path);
		index++;
	}
	free_split(path_tokens);
	return (NULL);
}

static void	execute_command(t_params *params, char **cmd_args, char **envp, t_fds *fds)
{
	char	*executable_path;

	executable_path = find_executable_path(cmd_args[0], envp);
	if (!executable_path) {
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		free_and_exit_failure(params, fds, COMMAND_NOT_FOUND_ERROR_MESSAGE);
	}
	cmd_args[0] = executable_path;
	if (execve(executable_path, cmd_args, envp) == PROCESS_FAILURE)
	{
		free(executable_path);
		free_and_exit_failure(params, fds, EXECVE_ERROR_MESSAGE);
	}
	free(executable_path);
}

void	pipex(t_params *params, t_fds *fds, char **envp)
{
	int		pipefd[2];
	pid_t	pid_process;

	if (pipe(pipefd) == PROCESS_FAILURE)
		free_and_exit_failure(params, fds, PIPE_ERROR_MESSAGE);
	pid_process = fork();
	if (pid_process == PROCESS_FAILURE)
		free_and_exit_failure(params, fds, FORK_ERROR_MESSAGE);
	if (pid_process == LEFT_PIPE_PROCESS)
	{
		dup2(fds->infile, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(fds->infile);
		execute_command(params, params->left_cmd_args, envp, fds);
	}
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(fds->outfile, STDOUT_FILENO);
		close(pipefd[1]);
		close(fds->outfile);
		execute_command(params, params->right_cmd_args, envp, fds);
	}
}
