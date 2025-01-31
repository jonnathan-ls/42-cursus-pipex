/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/31 00:33:28 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

/**
 * @brief Executes a command with proper error handling and resource management
 * 
 * This function attempts to execute the given command using execve(). It first
 * checks if the command exists and is executable. If any errors occur:
 * - Frees allocated memory
 * - Closes open file descriptors
 * - Exits the process with appropriate error status
 * 
 * @param p Pointer to the program parameters and state
 * @param cmd NULL-terminated array of command arguments
 * @param env Environment variables array
 * @note This function does not return on success - it replaces the process image
 * @warning Exits the process with status 127 if command not found, 
 *          or 126 if permission denied
 */
static void	execute_command(t_params *p, char **cmd, char **env)
{
	char	*path;
	int		is_allocated;

	is_allocated = 0;
	path = get_executable_path(cmd[0], env);
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		free_and_exit_failure(CMD_NOT_FOUND_MSG, p, NO_PERROR, CMD_NOT_FOUND);
	}
	is_allocated = (ft_strchr(cmd[0], SLASH_CHAR) == NULL);
	execve(path, cmd, env);
	if (is_allocated)
		free(path);
	free_and_exit_failure(cmd[0], p, PERROR, CMD_NO_EXEC_PERM);
}

/**
 * @brief Creates the first child process
 * 
 * This function forks a new process and assigns it to the first child.
 * It handles the creation of the child process and sets up the pipe for
 * communication between the parent and the child.
 * 
 * @param params Pointer to the program parameters and state
 * @param envp Environment variables array
 * @param pipefd Pipe file descriptors
 * @param pid Pointer to store the PID of the child process
 * @return int Exit status of the child process creation
 */
int	create_first_child(t_params *params, char **envp, int *pipefd, pid_t *pid)
{
	*pid = fork();
	if (*pid == PROCESS_FAILURE)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		free_and_exit_failure(FORK_FAIL_MSG, params, PERROR, EXIT_FAILURE);
	}
	if (*pid == 0)
	{
		close(pipefd[0]);
		exec_process(params, pipefd, envp, LEFT_PIPE);
	}
	return (PROCESS_SUCCESS);
}

/**
 * @brief Creates the second child process
 * 
 * This function forks a new process and assigns it to the second child.
 * It handles the creation of the child process and sets up the pipe for
 * communication between the parent and the child.
 * 
 * @param params Pointer to the program parameters and state
 * @param envp Environment variables array
 * @param pipefd Pipe file descriptors
 * @param pid Pointer to store the PID of the child process
 * @return int Exit status of the child process creation
 */
int	create_second_child(t_params *params, char **envp, int *pipefd, pid_t *pid)
{
	*pid = fork();
	if (*pid == PROCESS_FAILURE)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		free_and_exit_failure(FORK_FAIL_MSG, params, PERROR, EXIT_FAILURE);
	}
	if (*pid == 0)
	{
		close(pipefd[1]);
		exec_process(params, pipefd, envp, RIGHT_PIPE);
	}
	return (PROCESS_SUCCESS);
}

/**
 * @brief Handles the left pipe for the first child process
 * 
 * This function duplicates the input file descriptor to the standard input and
 * the output file descriptor to the standard output. It also closes the pipe
 * file descriptors and frees allocated memory if an error occurs.
 * 
 * @param p Pointer to the program parameters and state
 * @param fd Pipe file descriptors
 * @param envp Environment variables array
 */
void	handle_left_pipe(t_params *p, int *fd, char **envp)
{
	if (dup2(p->fds.input_file, STDIN_FILENO) == -1)
	{
		close(fd[1]);
		close(fd[0]);
		free_and_exit_failure(DUP2_FAIL_MSG, p, PERROR, EXIT_FAILURE);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		close(fd[0]);
		free_and_exit_failure(DUP2_FAIL_MSG, p, PERROR, EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	close(p->fds.input_file);
	execute_command(p, p->left_cmd_args, envp);
}

/**
 * @brief Handles the right pipe for the second child process
 * 
 * This function duplicates the input file descriptor to the standard input and
 * the output file descriptor to the standard output. It also closes the pipe
 * file descriptors and frees allocated memory if an error occurs.
 * 
 * @param p Pointer to the program parameters and state
 * @param fd Pipe file descriptors
 * @param envp Environment variables array
 */
void	handle_right_pipe(t_params *p, int *fd, char **envp)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		free_and_exit_failure(DUP2_FAIL_MSG, p, PERROR, EXIT_FAILURE);
	}
	if (dup2(p->fds.output_file, STDOUT_FILENO) == -1)
	{
		close(fd[0]);
		free_and_exit_failure(DUP2_FAIL_MSG, p, PERROR, EXIT_FAILURE);
	}
	close(fd[0]);
	close(p->fds.output_file);
	execute_command(p, p->right_cmd_args, envp);
}
