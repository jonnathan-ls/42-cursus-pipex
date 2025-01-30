/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/30 00:39:15 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define SPACE_CHAR ' '
# define SLASH_CHAR '/'
# define DOUBLE_COLON_CHAR ':'

# define PERROR 1
# define READ_END	0
# define LEFT_PIPE 0
# define NO_PERROR 0
# define WRITE_END	1
# define RIGHT_PIPE 1
# define SIGNAL_BASE 128
# define ACCESS_SUCCESS	0
# define PROCESS_SUCCESS 0
# define CHILDREN_PROCESS 0
# define PROCESS_FAILURE -1
# define PATH_ENV_VAR_LENGTH 4
# define MODE_PERMISSION_FILE 0644

# define SLASH_STRING "/"
# define PATH_ENV_VAR "PATH"
# define COLOR_RESET	"\033[0m"
# define COLOR_ERROR	"\033[0;31m"
# define EXIT_FAILURE_MSG "Error: [ x ] "
# define INVALID_ARGS_ERR_MSG "Invalid Arguments - Correct Format: \
./pipex <file1> <cmd1> <cmd2> <file2>\n"
# define MALLOC_MSG	"malloc failed"
# define PIPE_MSG "failed to create pipe"
# define FORK_MSG "failed to fork process"
# define EXECVE_MSG "failed to execute command"
# define OPEN_INFILE_MSG "failed to open infile"
# define OPEN_OUTFILE_MSG "failed to open outfile"
# define COMMAND_NOT_FOUND_MSG	"command not found"
# define DUP2_MSG "failed to duplicate file descriptor"
# define INVALID_PIPE_CMD_MSG "Pipe not could be empty"

#endif