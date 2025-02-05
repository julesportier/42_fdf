/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:57:18 by juportie          #+#    #+#             */
/*   Updated: 2025/02/04 14:04:40 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdlib.h>

int	ft_splitlen(char **splits)
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

void	ft_err_exit(char *error)
{
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

void	ft_err_free_exit(void *mem, char *error)
{
	free(mem);
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

char	*remove_end_nl(char *str)
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
