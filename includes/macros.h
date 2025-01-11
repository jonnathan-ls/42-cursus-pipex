/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/05 20:31:40 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define SPACE_CHAR ' '
# define DOUBLE_COLON_CHAR ':'
# define SLASH_STRING "/"
# define PROCESS_FAILURE -1
# define LEFT_PIPE_PROCESS 0
# define ACCESS_SUCCESS	0
# define MODE_PERMISSION_FILE 0644
# define PATH_ENV_VAR "PATH"
# define PATH_ENV_VAR_LENGTH 4

# define EXIT_SUCCESS_MESSAGE "✅ program terminated successfully\n"
# define ICON_FAILURE "❌ Error: "
#define EXIT_FAILURE_MESSAGE "program terminated with failure\n"
# define INVALID_ARGUMENTS_ERROR_MESSAGE \
"\n\033[31mError: Bad arguments\n\e[0m\n \
Correct Format: ./pipex <file1> <cmd1> <cmd2> <file2>\n"
# define MALLOC_ERROR_MESSAGE	"malloc failed"
# define OPEN_INFILE_ERROR_MESSAGE "failed to open infile"
# define OPEN_OUTFILE_ERROR_MESSAGE "failed to open outfile"
# define PIPE_ERROR_MESSAGE "failed to create pipe"
# define FORK_ERROR_MESSAGE	"failed to fork process"
# define DUP2_ERROR_MESSAGE "failed to duplicate file descriptor"
# define COMMAND_NOT_FOUND_ERROR_MESSAGE	"command not found"
# define EXECVE_ERROR_MESSAGE "failed to execute command"

#endif