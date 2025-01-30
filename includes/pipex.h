/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/30 20:33:32 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "macros.h"
# include "structs.h"

// Process management
int		pipex(t_params *params, char **envp);
int		create_first_child(t_params *params, char **envp,
			int *pipefd, pid_t *pid);
int		create_second_child(t_params *params, char **envp,
			int *pipefd, pid_t *pid);

// Path handling
char	*find_executable_path(char *cmd, char **envp);
char	*search_in_path_tokens(char *cmd, char **path_tokens);
char	*get_executable_path(char *cmd, char **envp);

// Pipe handling
void	handle_left_pipe(t_params *p, int *fd, char **envp);
void	handle_right_pipe(t_params *p, int *fd, char **envp);

// Utils functions
void	free_split(char **split);
void	validates_pipes_commands_args(t_params *params);
void	configure_arguments(t_params *params, char **argv);
void	exec_process(t_params *p, int *fd, char **envp, int side);
void	free_and_exit_failure(
			char *err_msg, t_params *params, int perror_msg, int exit_status);

#endif
