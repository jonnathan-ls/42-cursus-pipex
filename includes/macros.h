/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/04 22:16:50 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define	SPACE_CHAR ' '
# define DOUBLE_COLON_CHAR ':'
# define SLASH_STRING "/"
# define PROCESS_FAILURE -1
# define LEFT_PIPE_PROCESS 0
# define ACCESS_SUCCESS	0
# define MODE_PERMISSION_FILE 0644
# define PATH_ENV_VAR "PATH"
# define PATH_ENV_VAR_LENGTH 4

# define INVALID_ARGUMENTS_ERROR_MESSAGE "Usage: ./pipex infile cmd1 cmd2 outfile"
# define MALLOC_ERROR_MESSAGE	"Error: malloc failed"
# define OPEN_INFILE_ERROR_MESSAGE "Error: failed to open infile"
# define OPEN_OUTFILE_ERROR_MESSAGE "Error: failed to open outfile"
# define PIPE_ERROR_MESSAGE "Error: failed to create pipe"
# define FORK_ERROR_MESSAGE	"Error: failed to fork process"
# define DUP2_ERROR_MESSAGE "Error: failed to duplicate file descriptor"
# define EXECVE_ERROR_MESSAGE "Error: command not found"
#endif
