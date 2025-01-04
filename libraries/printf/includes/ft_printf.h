/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:52:12 by jlacerda          #+#    #+#             */
/*   Updated: 2024/12/21 20:15:22 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define STR_ARG_TYPE 's'
# define CHR_ARG_TYPE 'c'
# define PTR_ARG_TYPE 'p'
# define DIG_ARG_TYPE 'd'
# define INT_ARG_TYPE 'i'
# define UNS_ARG_TYPE 'u'
# define HEX_LOWER_ARG_TYPE 'x'
# define HEX_UPPER_ARG_TYPE 'X'
# define HEX_BASE_LOWER "0123456789abcdef"
# define HEX_BASE_UPPER "0123456789ABCDEF"

# define FLAGS "-0.# +"
# define SIGN_FLAG '+'
# define SPACE_FLAG ' '
# define PRECISION_FLAG '.'
# define ALTERNATE_FLAG '#'
# define ALIGN_LEFT_FLAG '-'
# define ZERO_PADDING_FLAG '0'

typedef struct s_flags
{
	int	sign;
	int	space;
	int	precision;
	int	alternate;
	int	min_width;
	int	align_left;
	int	width_value;
	int	zero_padding;
	int	precision_value;
}	t_flags;

typedef struct s_lst
{
	char			chr;
	struct s_lst	*next;
}	t_lst;

t_lst	*ft_new_lst(char chr);
t_lst	*ft_last_lst(t_lst *lst);
void	ft_add_back_lst(t_lst **lst, t_lst *new);
void	ft_add_front_lst(t_lst **lst, t_lst *new);
int		ft_size_lst(t_lst *lst);

t_lst	*ft_get_nbr(int n);
t_lst	*ft_get_chr(char chr);
t_lst	*ft_get_str(char *str);
t_lst	*ft_get_ptr(void *ptr);
t_lst	*ft_get_unbr(unsigned int ui);
t_lst	*ft_get_hex(unsigned long ul, char *hex_base);

void	ft_free_lst(t_lst **lst);
int		ft_is_null_node_lst(t_lst *lst);
void	ft_set_flags(const char **chr, t_flags *flags);
void	ft_set_padding(t_lst **lst, t_flags *flags, char arg_type);
void	ft_set_precision(t_lst **lst, t_flags *f, char at, int *len);

int		ft_printf(const char *fmt, ...);

#endif
