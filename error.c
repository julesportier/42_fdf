/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:04:57 by juportie          #+#    #+#             */
/*   Updated: 2025/02/12 11:12:15 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
#include <stdlib.h>

void	err_exit(char *error)
{
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

void	err_free_exit(void *mem, char *error)
{
	free(mem);
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

void	err_freegrid_exit(t_pixel **grid, int sub_nbr, char *error)
{
	freegrid(grid, sub_nbr);
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}
