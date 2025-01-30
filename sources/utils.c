/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/30 20:34:15 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

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

void	free_and_exit_failure(
	char *err_msg, t_params *params, int perror_msg, int exit_status)
{
	if (params->left_cmd_args)
		free_split(params->left_cmd_args);
	if (params->right_cmd_args)
		free_split(params->right_cmd_args);
	if (params->fds.input_file > STDERR_FILENO)
		close(params->fds.input_file);
	if (params->fds.output_file > STDERR_FILENO)
		close(params->fds.output_file);
	if (perror_msg)
		perror(err_msg);
	else
		ft_putstr_fd(err_msg, STDERR_FILENO);
	exit(exit_status);
}

void	exec_process(t_params *p, int *fd, char **envp, int side)
{
	if (side == LEFT_PIPE)
		handle_left_pipe(p, fd, envp);
	else
		handle_right_pipe(p, fd, envp);
}

void	validates_pipes_commands_args(t_params *params)
{
	if (params->left_cmd_args == NULL || params->right_cmd_args == NULL)
		free_and_exit_failure(MALLOC_MSG, params, NO_PERROR, EXIT_FAILURE);
	if (params->left_cmd_args[0] == NULL || params->right_cmd_args[0] == NULL)
		free_and_exit_failure(
			INVALID_PIPE_CMD_MSG, params, NO_PERROR, EXIT_FAILURE);
}

void	configure_arguments(t_params *params, char **argv)
{
	params->left_cmd_args = ft_split(argv[2], SPACE_CHAR);
	params->right_cmd_args = ft_split(argv[3], SPACE_CHAR);
	validates_pipes_commands_args(params);
	params->fds.input_file = open(argv[1], O_RDONLY);
	params->fds.output_file = open(argv[4],
			O_WRONLY | O_CREAT | O_TRUNC, MODE_PERMISSION_FILE);
}
