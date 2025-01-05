/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/05 20:41:05 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	exit_failure_with_message(char *error_message)
{
	ft_putendl_fd(EXIT_FAILURE_MESSAGE, STDERR_FILENO);
	perror(error_message);
	exit(EXIT_FAILURE);
}

void	free_and_exit_failure(t_fds *fds, char *err_msg)
{
	close(fds->infile);
	close(fds->outfile);
	free(fds);
	// free_split(params->left_cmd_args);
	// free_split(params->right_cmd_args);
	exit_failure_with_message(err_msg);
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
