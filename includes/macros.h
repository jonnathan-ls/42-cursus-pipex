/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/30 21:29:15 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// Constants
# define SPACE_CHAR ' '
# define SLASH_CHAR '/'
# define SLASH_STRING "/"
# define PATH_ENV_VAR "PATH"
# define DOUBLE_COLON_CHAR ':'
# define MODE_PERMISSION_FILE 0644

// Exit Codes
# define CMD_NOT_FOUND 127
# define CMD_NO_EXEC_PERM 126
# define SIGNAL_BASE 128
# define DEFAULT_ERR_STATUS 1

// File Descriptors
# define READ_END 0
# define WRITE_END 1

// Process Control
# define PERROR 1
# define LEFT_PIPE 0
# define NO_PERROR 0
# define RIGHT_PIPE 1
# define ACCESS_SUCCESS 0
# define PROCESS_SUCCESS 0
# define PROCESS_FAILURE -1

// Path Handling
# define PATH_PREFIX_LENGTH 5
# define PATH_ENV_VAR_LENGTH 4

// Error Messages
# define FORK_FAIL_MSG "fork failed"
# define PIPE_FAIL_MSG "pipe failed"
# define MALLOC_MSG "malloc failed"
# define DUP2_FAIL_MSG "dup2 failed"
# define CMD_NOT_FOUND_MSG ": command not found\n"
# define INVALID_PIPE_CMD_MSG "Pipe not could be empty"
# define INVALID_ARGS_ERR_MSG "Invalid Arguments - Correct Format: \
./pipex <file1> <cmd1> <cmd2> <file2>\n"

#endif