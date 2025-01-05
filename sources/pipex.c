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
#include "ft_printf.h"

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

	if (pipe(pipefd) == PROCESS_FAILURE)
		return (free_fds(fds, PIPE_ERROR_MESSAGE));
	pid_process = fork();
	if (pid_process == PROCESS_FAILURE)
		return (free_fds(fds, FORK_ERROR_MESSAGE));
	if (pid_process == LEFT_PIPE_PROCESS)
	{
		close(pipefd[0]);
		dup2(fds->infile, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(fds->infile);
		close(pipefd[1]);
		execve(params->left_cmd_args[0], params->left_cmd_args, envp);
	}
	else
	{
		waitpid(pid_process, NULL, 0);
		close(pipefd[1]);
		if (dup2(fds->outfile, STDOUT_FILENO) == PROCESS_FAILURE)
			return (free_fds(fds, DUP2_ERROR_MESSAGE));
		if (dup2(pipefd[0], STDIN_FILENO) == PROCESS_FAILURE)
			return (free_fds(fds, DUP2_ERROR_MESSAGE));
		close(fds->outfile);
		close(pipefd[0]);
		execve(params->right_cmd_args[0], params->right_cmd_args, envp);
	}
}
