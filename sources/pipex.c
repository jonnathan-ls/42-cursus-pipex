/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/14 22:17:08 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

static char	*get_path_token(char **envp)
{
	int	index;

	if (!envp)
		return (NULL);
	index = 0;
	while (envp[index] && !ft_strnstr(envp[index], PATH_ENV_VAR, PATH_ENV_VAR_LENGTH))
		index++;
	if (!envp[index])
		return (NULL);
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
		if (access(final_path, F_OK | X_OK) == ACCESS_SUCCESS)
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
	char	*original_cmd;

	if (!cmd_args || !envp)
		free_and_exit_failure("Invalid arguments", params, NO_PERROR);

	original_cmd = cmd_args[0];
	if (ft_strchr(cmd_args[0], SLASH_CHAR))
	{
		if (access(cmd_args[0], F_OK | X_OK) == ACCESS_SUCCESS)
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
		free_and_exit_failure(COMMAND_NOT_FOUND_MSG, params, PERROR);
	}
	cmd_args[0] = executable_path;
	execve(executable_path, cmd_args, envp);
	cmd_args[0] = original_cmd;
	free(executable_path);
	free_and_exit_failure(EXECVE_MSG, params, PERROR);
}

static void	exec_process(t_params *p, int *fd, char **envp, int side)
{
	if (side == LEFT_PIPE)
	{
		close(fd[0]);
		if (dup2(p->fds.input_file, STDIN_FILENO) == -1)
		{
			close(fd[1]);
			free_and_exit_failure("dup2 failed", p, PERROR);
		}
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			close(fd[1]);
			free_and_exit_failure("dup2 failed", p, PERROR);
		}
		close(fd[1]);
		close(p->fds.input_file);
		execute_command(p, p->left_cmd_args, envp);
	}
	else if (side == RIGHT_PIPE)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			close(fd[1]);
			free_and_exit_failure("dup2 failed", p, PERROR);
		}
		if (dup2(p->fds.output_file, STDOUT_FILENO) == -1)
		{
			close(fd[1]);
			free_and_exit_failure("dup2 failed", p, PERROR);
		}
		close(fd[1]);
		close(p->fds.output_file);
		execute_command(p, p->right_cmd_args, envp);
	}
}

int	pipex(t_params *params, char **envp)
{
	int		pipefd[2];
	pid_t	pid_child_process[2];
	int		status;

	if (pipe(pipefd) == PROCESS_FAILURE)
		free_and_exit_failure(PIPE_MSG, params, PERROR);
	pid_child_process[0] = fork();
	if (pid_child_process[0] == PROCESS_FAILURE)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		free_and_exit_failure(FORK_MSG, params, PERROR);
	}
	if (pid_child_process[0] == 0)
	{
		close(pipefd[0]);
		exec_process(params, pipefd, envp, LEFT_PIPE);
	}
	pid_child_process[1] = fork();
	if (pid_child_process[1] == PROCESS_FAILURE)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		free_and_exit_failure(FORK_MSG, params, PERROR);
	}
	if (pid_child_process[1] == 0)
	{
		close(pipefd[1]);
		exec_process(params, pipefd, envp, RIGHT_PIPE);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_child_process[0], &status, 0);
	if (status != 0)
		free_and_exit_failure("Command failed", params, NO_PERROR);
	waitpid(pid_child_process[1], &status, 0);
	return (status);
}
