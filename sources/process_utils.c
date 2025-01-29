/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/29 00:53:10 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

static void	execute_command(t_params *params, char **cmd_args, char **envp)
{
	char	*executable_path;
	char	*original_cmd;

	if (!cmd_args || !envp)
		free_and_exit_failure("Invalid arguments", params, NO_PERROR);
	original_cmd = cmd_args[0];
	executable_path = get_executable_path(cmd_args[0], envp);
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

int	create_first_child(t_params *params, char **envp, int *pipefd, pid_t *pid)
{
	*pid = fork();
	if (*pid == PROCESS_FAILURE)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		free_and_exit_failure(FORK_MSG, params, PERROR);
	}
	if (*pid == 0)
	{
		close(pipefd[0]);
		exec_process(params, pipefd, envp, LEFT_PIPE);
	}
	return (PROCESS_SUCCESS);
}

int	create_second_child(t_params *params, char **envp, int *pipefd, pid_t *pid)
{
	*pid = fork();
	if (*pid == PROCESS_FAILURE)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		free_and_exit_failure(FORK_MSG, params, PERROR);
	}
	if (*pid == 0)
	{
		close(pipefd[1]);
		exec_process(params, pipefd, envp, RIGHT_PIPE);
	}
	return (PROCESS_SUCCESS);
}

void	handle_left_pipe(t_params *p, int *fd, char **envp)
{
	if (dup2(p->fds.input_file, STDIN_FILENO) == -1)
	{
		close(fd[1]);
		close(fd[0]);
		free_and_exit_failure("dup2 failed", p, PERROR);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		close(fd[0]);
		free_and_exit_failure("dup2 failed", p, PERROR);
	}
	close(fd[0]);
	close(fd[1]);
	close(p->fds.input_file);
	execute_command(p, p->left_cmd_args, envp);
}

void	handle_right_pipe(t_params *p, int *fd, char **envp)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		free_and_exit_failure("dup2 failed", p, PERROR);
	}
	if (dup2(p->fds.output_file, STDOUT_FILENO) == -1)
	{
		close(fd[0]);
		free_and_exit_failure("dup2 failed", p, PERROR);
	}
	close(fd[1]);
	close(fd[0]);
	close(p->fds.output_file);
	execute_command(p, p->right_cmd_args, envp);
}
