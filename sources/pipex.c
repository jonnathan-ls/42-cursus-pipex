/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/02/06 20:23:54 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"


/**
 * @brief Waits for the children processes to finish and returns the exit status
 * 
 * This function waits for the children processes to finish and returns the exit
 * status. It handles both normal exits and signaled exits.
 * 
 * @param pid_child_one PID of the first child process
 * @param pid_child_two PID of the second child process
 * @return int Exit status of the children processes
 */
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
		exit_status = DEFAULT_ERR_STATUS;
	return (exit_status);
}

/**
 * @brief Main function for the pipex program
 * 
 * This function sets up pipes and creates child processes to execute commands.
 * It handles signal handling, pipe creation, and child process creation.
 * 
 * @param params Pointer to the program parameters and state
 * @param envp Environment variables array
 * @return int Exit status of the pipex program
 */
static int	pipex(t_params *params, char **envp)
{
	int		pipefd[2];
	pid_t	pid_child_process[2];

	if (pipe(pipefd) == PROCESS_FAILURE)
		free_and_exit_failure(PIPE_FAIL_MSG, params, PERROR, EXIT_FAILURE);
	if (create_first_child(params, envp, pipefd, &pid_child_process[0]))
		return (PROCESS_FAILURE);
	close(pipefd[1]);
	if (create_second_child(params, envp, pipefd, &pid_child_process[1]))
		return (PROCESS_FAILURE);
	close(pipefd[0]);
	return (wait_for_children(pid_child_process[0], pid_child_process[1]));
}

/**
 * @brief Main function for the pipex program
 * 
 * This function initializes the program parameters, configures the arguments,
 * and executes the pipex function. It also frees allocated memory and returns
 * the exit status of the pipex program.
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @param envp Environment variables array
 * @return int Exit status of the pipex program
 */
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
