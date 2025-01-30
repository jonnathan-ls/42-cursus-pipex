/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/30 00:36:56 by jlacerda         ###   ########.fr       */
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
