/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/10 23:32:25 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	*validate_open_files(t_params *params, t_fds *fds)
{
	if (fds == NULL)
		return (NULL);
	if (fds->infile == PROCESS_FAILURE)
	{
		perror(OPEN_INFILE_ERROR_MESSAGE);
		if (fds->outfile != PROCESS_FAILURE)
			close(fds->outfile);
		free(fds);
		free_split(params->left_cmd_args);
		free_split(params->right_cmd_args);
		return (NULL);
	}
	if (fds->outfile == PROCESS_FAILURE)
	{
		perror(OPEN_OUTFILE_ERROR_MESSAGE);
		close(fds->infile);
		free(fds);
		free_split(params->left_cmd_args);
		free_split(params->right_cmd_args);
		return (NULL);
	}
	return (fds);
}

t_fds	*open_files(t_params *params)
{
	t_fds	*fds;

	fds = malloc(sizeof(t_fds));
	if (fds == NULL)
	{
		perror(MALLOC_ERROR_MESSAGE);
		return (NULL);
	}
	fds->infile = open(params->infile_path, O_RDONLY);
	fds->outfile = open(params->outfile_path,
			O_WRONLY | O_CREAT | O_TRUNC, MODE_PERMISSION_FILE);
	return (validate_open_files(params, fds));
}
