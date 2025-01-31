/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:25:59 by jlacerda          #+#    #+#             */
/*   Updated: 2025/01/31 00:45:11 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * @brief Structure to hold file descriptors
 * 
 * This structure holds the file descriptors for the input and output files.
 */
typedef struct fds
{
	int	input_file;
	int	output_file;
}	t_fds;

/**
 * @brief Structure to hold program parameters and state
 * 
 * This structure holds the file descriptors and command arguments.
 */
typedef struct params
{
	t_fds	fds;
	char	**left_cmd_args;
	char	**right_cmd_args;
}	t_params;

#endif
