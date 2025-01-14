/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/13 22:00:03 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

static void	validates_pipes_commands_args(t_params *params)
{
	if (params->left_cmd_args == NULL || params->right_cmd_args == NULL)
		free_and_exit_failure(MALLOC_MSG, params, NO_PERROR);
	if (params->left_cmd_args[0] == NULL || params->right_cmd_args[0] == NULL)
		free_and_exit_failure(INVALID_LEFT_PIPE_CMD_MSG, params, NO_PERROR);
}

static void	validates_fds_open_files(t_params *params)
{
	if (params->fds.input_file == PROCESS_FAILURE)
		free_and_exit_failure(OPEN_INFILE_MSG, params, PERROR);
	if (params->fds.output_file == PROCESS_FAILURE)
		free_and_exit_failure(OPEN_OUTFILE_MSG, params, PERROR);
}

static void	configure_arguments(t_params *params, char **argv)
{
	params->left_cmd_args = ft_split(argv[2], SPACE_CHAR);
	params->right_cmd_args = ft_split(argv[3], SPACE_CHAR);
	validates_pipes_commands_args(params);
	params->fds.input_file = open(argv[1], O_RDONLY);
	params->fds.output_file = open(argv[4],
			O_WRONLY | O_CREAT | O_TRUNC, MODE_PERMISSION_FILE);
	validates_fds_open_files(params);
}

int	main(int argc, char **argv, char **envp)
{
	t_params	params;

	params.left_cmd_args = NULL;
	params.right_cmd_args = NULL;
	params.fds.input_file = PROCESS_FAILURE;
	params.fds.output_file = PROCESS_FAILURE;
	if (argc != 5)
		free_and_exit_failure(INVALID_ARGS_ERR_MSG, &params, NO_PERROR);
	configure_arguments(&params, argv);
	pipex(&params, envp);
	free_split(params.left_cmd_args);
	free_split(params.right_cmd_args);
	return (EXIT_SUCCESS);
}
