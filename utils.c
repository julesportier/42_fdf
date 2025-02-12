/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:57:18 by juportie          #+#    #+#             */
/*   Updated: 2025/02/12 11:08:01 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
#include <stdlib.h>

int	splitlen(char **splits)
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
