/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/30 20:55:11 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

static void	handle_signals(void)
{
	signal(SIGPIPE, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static int	wait_for_children(pid_t pid_child_one, pid_t pid_child_two)
{
	int	status;
	int	exit_status;

	waitpid(pid_child_two, &status, 0);
	waitpid(pid_child_one, NULL, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = SIGNAL_BASE + WTERMSIG(status);
	else
		exit_status = 1;
	return (exit_status);
}

int	pipex(t_params *params, char **envp)
{
	int		pipefd[2];
	pid_t	pid_child_process[2];

	if (pipe(pipefd) == PROCESS_FAILURE)
		free_and_exit_failure(PIPE_MSG, params, PERROR, EXIT_FAILURE);
	handle_signals();
	if (create_first_child(params, envp, pipefd, &pid_child_process[0]))
		return (PROCESS_FAILURE);
	if (create_second_child(params, envp, pipefd, &pid_child_process[1]))
		return (PROCESS_FAILURE);
	close(pipefd[0]);
	close(pipefd[1]);
	return (wait_for_children(pid_child_process[0], pid_child_process[1]));
}

int	main(int argc, char **argv, char **envp)
{
	t_params	params;
	int			status;

	params.left_cmd_args = NULL;
	params.right_cmd_args = NULL;
	params.fds.input_file = PROCESS_FAILURE;
	params.fds.output_file = PROCESS_FAILURE;
	if (argc != 5)
		free_and_exit_failure(
			INVALID_ARGS_ERR_MSG, &params, NO_PERROR, EXIT_FAILURE);
	configure_arguments(&params, argv);
	status = pipex(&params, envp);
	free_split(params.left_cmd_args);
	free_split(params.right_cmd_args);
	return (status);
}
