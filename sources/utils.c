/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/30 21:17:04 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

/**
 * @brief Frees a split string array
 * 
 * This function frees the memory allocated for a split string array.
 * It iterates through the array, frees each string, 
	* and then frees the array itself.
 * 
 * @param split Pointer to the split string array
 */
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/**
 * @brief Frees allocated memory and exits the program with an error
 * 
 * This function frees allocated memory and exits the program with an error.
 * It handles file descriptors, frees split strings, and prints an error message.
 * 
 * @param err Error message to display
 * @param p Pointer to the program parameters and state
 * @param perr Flag to indicate if an error message should be printed
 * @param exit_status Exit status to return
 */
void	free_and_exit_failure(char *err, t_params *p, int perr, int exit_status)
{
	int	in_fd;
	int	out_fd;

	in_fd = p->fds.input_file;
	out_fd = p->fds.output_file;
	free_split(p->left_cmd_args);
	free_split(p->right_cmd_args);
	if (in_fd > STDERR_FILENO)
		close(in_fd);
	if (out_fd > STDERR_FILENO)
		close(out_fd);
	if (perr)
		perror(err);
	else
		ft_putstr_fd(err, STDERR_FILENO);
	exit(exit_status);
}

/**
 * @brief Executes a process with proper error handling and resource management
 * 
 * This function handles the execution of a process. 
	* It checks which side of the pipe to handle and calls 
	* the appropriate function to set up the pipe.
 * 
 * @param p Pointer to the program parameters and state
 * @param fd Pipe file descriptors
 * @param envp Environment variables array
 * @param side Flag to indicate which side of the pipe to handle
 */
void	exec_process(t_params *p, int *fd, char **envp, int side)
{
	if (side == LEFT_PIPE)
		handle_left_pipe(p, fd, envp);
	else
		handle_right_pipe(p, fd, envp);
}

/**
 * @brief Validates the pipes and commands arguments
 * 
 * This function checks if the pipes and commands arguments are valid.
 * It handles memory allocation errors and invalid command errors.
 * 
 * @param params Pointer to the program parameters and state
 */
void	validates_pipes_commands_args(t_params *params)
{
	if (params->left_cmd_args == NULL || params->right_cmd_args == NULL)
		free_and_exit_failure(MALLOC_MSG, params, NO_PERROR, EXIT_FAILURE);
	if (params->left_cmd_args[0] == NULL || params->right_cmd_args[0] == NULL)
		free_and_exit_failure(
			INVALID_PIPE_CMD_MSG, params, NO_PERROR, EXIT_FAILURE);
}

/**
 * @brief Configures the arguments for the left and right commands
 * 
 * This function splits the command arguments and validates them.
 * It also opens the input and output files.
 * 
 * @param params Pointer to the program parameters and state
 * @param argv Command line arguments
 */
void	configure_arguments(t_params *params, char **argv)
{
	params->left_cmd_args = ft_split(argv[2], SPACE_CHAR);
	params->right_cmd_args = ft_split(argv[3], SPACE_CHAR);
	validates_pipes_commands_args(params);
	params->fds.input_file = open(argv[1], O_RDONLY);
	params->fds.output_file = open(argv[4],
			O_WRONLY | O_CREAT | O_TRUNC, MODE_PERMISSION_FILE);
}
