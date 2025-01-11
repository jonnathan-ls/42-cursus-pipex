/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/11 19:30:06 by jlacerda         ###   ########.fr       */
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

static void	execute_command(t_params *params, char **cmd_args, char **envp)
{
	char	*executable_path;

	if (ft_strchr(cmd_args[0], SLASH_CHAR))
	{
		if (access(cmd_args[0], F_OK) == ACCESS_SUCCESS)
			executable_path = cmd_args[0];
		else
			executable_path = NULL;
	}
	else
		executable_path = find_executable_path(cmd_args[0], envp);
	if (!executable_path)
	{
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putstr_fd(" => ", STDERR_FILENO);
		free_and_exit_failure(COMMAND_NOT_FOUND_MSG, params);
	}
	cmd_args[0] = executable_path;
	if (execve(executable_path, cmd_args, envp) == PROCESS_FAILURE)
	{
		free(executable_path);
		free_and_exit_failure(EXECVE_MSG, params);
	}
	free(executable_path);
}

void	pipex(t_params *params, char **envp)
{
	int		pipefd[2];
	pid_t	pid_process;

	if (pipe(pipefd) == PROCESS_FAILURE)
		free_and_exit_failure(PIPE_MSG, params);
	pid_process = fork();
	if (pid_process == PROCESS_FAILURE)
		free_and_exit_failure(FORK_MSG, params);
	if (pid_process == LEFT_PIPE_PROCESS)
	{
		dup2(params->fds->input_file, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(params->fds->input_file);
		execute_command(params, params->left_cmd_args, envp);
	}
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(params->fds->output_file, STDOUT_FILENO);
		close(pipefd[1]);
		close(params->fds->output_file);
		execute_command(params, params->right_cmd_args, envp);
	}
}
