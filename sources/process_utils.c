/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/30 00:50:02 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

static void	execute_command(t_params *params, char **cmd_args, char **envp)
{
	char	*path;

	if (!cmd_args || !cmd_args[0])
	{
		free_and_exit_failure("Invalid command", params, PERROR, EXIT_FAILURE);
	}
	path = get_executable_path(cmd_args[0], envp);
	if (!path)
	{
		ft_putstr_fd(cmd_args[0], 2);
		free_and_exit_failure(": command not found\n", params, PERROR, 127);
	}
	execve(path, cmd_args, envp);
	free(path);
	perror(cmd_args[0]);
	free_and_exit_failure(NULL, params, PERROR, 126);
}

int	create_first_child(t_params *params, char **envp, int *pipefd, pid_t *pid)
{
	*pid = fork();
	if (*pid == PROCESS_FAILURE)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		free_and_exit_failure(FORK_MSG, params, PERROR, EXIT_FAILURE);
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
		free_and_exit_failure(FORK_MSG, params, PERROR, EXIT_FAILURE);
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
		free_and_exit_failure("dup2 failed", p, PERROR, EXIT_FAILURE);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		close(fd[0]);
		free_and_exit_failure("dup2 failed", p, PERROR, EXIT_FAILURE);
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
		free_and_exit_failure("dup2 failed", p, PERROR, EXIT_FAILURE);
	}
	if (dup2(p->fds.output_file, STDOUT_FILENO) == -1)
	{
		close(fd[0]);
		free_and_exit_failure("dup2 failed", p, PERROR, EXIT_FAILURE);
	}
	close(fd[1]);
	close(fd[0]);
	close(p->fds.output_file);
	execute_command(p, p->right_cmd_args, envp);
}
