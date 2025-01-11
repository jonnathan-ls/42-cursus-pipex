/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/11 19:30:06 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"
#include "pipex.h"

void	validates_pipes_commands_args(t_params *params)
{
	if (params->left_cmd_args == NULL)
		exit_failure_with_message(MALLOC_MSG, PERROR);
	if (params->left_cmd_args[0] == NULL)
		exit_failure_with_message(INVALID_LEFT_PIPE_CMD_MSG, NO_PERROR);
	if (params->right_cmd_args == NULL)
		exit_failure_with_message(MALLOC_MSG, PERROR);
	if (params->right_cmd_args[0] == NULL)
	{
		free_split(params->left_cmd_args);
		exit_failure_with_message(INVALID_RIGHT_PIPE_CMD_MSG, NO_PERROR);
	}
}

void	validates_fds_open_files(t_params *params)
{
	if (params->fds->input_file == PROCESS_FAILURE)
	{
		if (params->fds->output_file != PROCESS_FAILURE)
			close(params->fds->output_file);
		free_split(params->left_cmd_args);
		free_split(params->right_cmd_args);
		exit_failure_with_message(OPEN_INFILE_MSG, PERROR);
	}
	if (params->fds->output_file == PROCESS_FAILURE)
	{
		close(params->fds->input_file);
		free_split(params->left_cmd_args);
		free_split(params->right_cmd_args);
		exit_failure_with_message(OPEN_OUTFILE_MSG, PERROR);
	}
}
