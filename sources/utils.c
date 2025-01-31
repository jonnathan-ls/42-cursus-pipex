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
