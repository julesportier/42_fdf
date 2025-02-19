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

int	split_digit_len(char **splits)
{
	int	i;
	int	j;

	i = 0;
	if (splits != NULL)
	{
		while (splits[i])
		{
			if (splits[i][0] == ',')
				return (-1);
			j = 0;
			while (splits[i][j] && splits[i][j] != ',')
			{
				if (splits[i][j] >= '0' && splits[i][j] <= '9'
					|| splits [i][j] == '-')
					j++;
				else
					return (-1);
			}
			i++;
		}
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
