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
#include "../libft/src/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	err_exit(char *error)
{
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

void	perror_exit(char *caller)
{
	perror(caller);
	exit(EXIT_FAILURE);
}

void	err_free_exit(int fd, void *mem, char *error)
{
	if (mem)
		free(mem);
	ft_putendl_fd(error, 2);
	if (fd > 0)
		if (close(fd))
			perror("err_free_exit");
	exit(EXIT_FAILURE);
}

void	err_freegrid_exit(int fd, t_pixel **grid, int sub_nbr, char *error)
{
	freegrid(grid, sub_nbr);
	ft_putendl_fd(error, 2);
	if (fd > 0)
		if (close(fd))
			perror("err_free_exit");
	exit(EXIT_FAILURE);
}
