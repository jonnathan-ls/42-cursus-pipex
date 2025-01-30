/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/30 01:06:03 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

static void	validates_pipes_commands_args(t_params *params)
{
	if (params->left_cmd_args == NULL || params->right_cmd_args == NULL)
		free_and_exit_failure(MALLOC_MSG, params, NO_PERROR, EXIT_FAILURE);
	if (params->left_cmd_args[0] == NULL || params->right_cmd_args[0] == NULL)
		free_and_exit_failure(INVALID_PIPE_CMD_MSG, params, NO_PERROR, EXIT_FAILURE);
}

static void	configure_arguments(t_params *params, char **argv)
{
	params->left_cmd_args = ft_split(argv[2], SPACE_CHAR);
	params->right_cmd_args = ft_split(argv[3], SPACE_CHAR);
	validates_pipes_commands_args(params);
	params->fds.input_file = open(argv[1], O_RDONLY);
	params->fds.output_file = open(argv[4],
			O_WRONLY | O_CREAT | O_TRUNC, MODE_PERMISSION_FILE);
}

static void handle_signals(void) {
	signal(SIGPIPE, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	pipex(t_params *params, char **envp)
{
	int		pipefd[2];
	pid_t	pid_child_process[2];
	int		status;
	int		exit_status;

	if (pipe(pipefd) == PROCESS_FAILURE)
		free_and_exit_failure(PIPE_MSG, params, PERROR, EXIT_FAILURE);
	handle_signals();

	if (create_first_child(params, envp, pipefd, &pid_child_process[0]) == PROCESS_FAILURE)
		return (PROCESS_FAILURE);
	
	if (create_second_child(params, envp, pipefd, &pid_child_process[1]) == PROCESS_FAILURE)
		return (PROCESS_FAILURE);

	close(pipefd[1]);
	close(pipefd[0]);

	waitpid(pid_child_process[0], &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else
		exit_status = 1;

	waitpid(pid_child_process[1], &status, 0);
	if (WIFSIGNALED(status))
		exit_status = SIGNAL_BASE + WTERMSIG(status);
	else if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);

	return (exit_status);
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
