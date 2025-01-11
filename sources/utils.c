/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/11 19:33:20 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

void	exit_failure_with_message(char *error_message, int print_perror)
{
	ft_putstr_fd(COLOR_ERROR, STDERR_FILENO);
	ft_putstr_fd(EXIT_FAILURE_MSG, STDERR_FILENO);
	ft_putstr_fd(COLOR_RESET, STDERR_FILENO);
	if (print_perror)
		perror(error_message);
	else
		ft_putstr_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_and_exit_failure(char *err_msg, t_params *params)
{
	free_split(params->left_cmd_args);
	free_split(params->right_cmd_args);
	close(params->fds->input_file);
	close(params->fds->output_file);
	free(params->fds);
	free(params);
	exit_failure_with_message(err_msg, NO_PERROR);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
