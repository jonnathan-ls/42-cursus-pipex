/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/11 19:37:03 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

static void	configure_arguments(t_params *params, char **argv)
{
	params->left_cmd_args = ft_split(argv[2], SPACE_CHAR);
	params->right_cmd_args = ft_split(argv[3], SPACE_CHAR);
	validates_pipes_commands_args(params);
	params->fds->input_file = open(argv[1], O_RDONLY);
	params->fds->output_file = open(argv[4],
			O_WRONLY | O_CREAT | O_TRUNC, MODE_PERMISSION_FILE);
	validates_fds_open_files(params);
}

int	main(int argc, char **argv, char **envp)
{
	t_params	*params;

	params = malloc(sizeof(t_params));
	if (!params)
		exit_failure_with_message(MALLOC_MSG, NO_PERROR);
	params->fds = malloc(sizeof(t_fds));
	if (!params->fds)
		free_and_exit_failure(MALLOC_MSG, params);
	if (argc != 5)
		exit_failure_with_message(INVALID_ARGS_ERR_MSG, NO_PERROR);
	configure_arguments(params, argv);
	pipex(params, envp);
	free_split(params->left_cmd_args);
	free_split(params->right_cmd_args);
	free(params->fds);
	return (EXIT_SUCCESS);
}
