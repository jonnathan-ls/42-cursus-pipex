/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/11 17:09:28 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "macros.h"
# include "structs.h"

void	validates_fds_open_files(t_params *params);
void	validates_pipes_commands_args(t_params *params);
void	exit_failure_with_message(char *error_message, int print_perror);

void	free_split(char **split);
void	pipex(t_params *params, char **envp);
void	free_and_exit_failure(char *err_msg, t_params *params);

#endif
