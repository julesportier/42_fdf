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
#include "libft/get_next_line.h"
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

static int	ft_splitlen(char **splits)
{
	int	i;

	i = 0;
	if (splits != NULL)
	{
		while (splits[i])
			i++;
	}
	return (i);
}

static void	ft_free_fail(char *str, char *error)
{
	free(str);
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

static char	*remove_end_nl(char *str)
{
	int	len;

	if (str)
	{
		len = ft_strlen(str);
		if (str[len - 1] == '\n')
			str[len - 1] = '\0';
	}
	return (str);
}

t_grid_data	get_grid_size(int fd)
{
	char	*line;
	char	**splits;
	t_grid_data	grid;
	int	temp;

	ft_bzero(&grid, sizeof(t_grid_data));
	while (1)
	{
		line = remove_end_nl(get_next_line(fd));
		if (line == NULL && grid.width != 0)
			return (grid);
		if (line == NULL && grid.width == 0)
			ft_free_fail(NULL, "file is empty");
		if (++grid.height < 0)
			ft_free_fail(line, "line number overflow");
		splits = ft_split(line, ' ');
		if (splits == NULL)
			ft_free_fail(line, "ft_split() error");
		temp = ft_splitlen(splits);
		if (temp != grid.width && grid.width != 0)
			ft_free_fail(line, "wrong file formating");
		grid.width = temp;
		free(line);
		line = NULL;
	}
}
