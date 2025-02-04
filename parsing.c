/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:13:27 by juportie          #+#    #+#             */
/*   Updated: 2025/02/04 07:50:33 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	get_fd(char *filename)
{
	int	fd;
	int	name_len;

	name_len = ft_strlen(filename);
	if (name_len < 4 || ft_strncmp(&filename[name_len - 4], ".fdf", 4))
	{
		ft_putendl_fd("Wrong filename or extension", 2);
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open() error");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
