/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/05 20:36:33 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

static void	configure_arguments(t_params *params, char **argv)
{
	params->left_cmd_args = ft_split(argv[2], SPACE_CHAR);
	params->right_cmd_args = ft_split(argv[3], SPACE_CHAR);
	params->infile_path = argv[1];
	params->outfile_path = argv[4];
}

int	main(int argc, char **argv, char **envp)
{
	t_params	params;
	t_fds		*fds;

	if (argc != 5)
		exit_failure_with_message(INVALID_ARGUMENTS_ERROR_MESSAGE);
	configure_arguments(&params, argv);
	fds = open_files(&params);
	if (fds == NULL)
		return (EXIT_FAILURE);
	pipex(&params, fds, envp);
	return (EXIT_SUCCESS);
}
