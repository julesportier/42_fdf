/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:59:52 by juportie          #+#    #+#             */
/*   Updated: 2025/02/12 11:01:59 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include "minilibx/mlx.h"

void	free_splits(char **array)
{
	int		i;
	char	**addr;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	addr = array;
	free(array);
	array = NULL;
}

void	freegrid(t_pixel **grid, int sub_nbr)
{
	while (sub_nbr--)
		free(grid[sub_nbr]);
	free(grid);
}

void	free_mlx(t_mlx_data *mlx_data)
{
	if (mlx_data->img.img != NULL)
		mlx_destroy_image(mlx_data->mlx, mlx_data->img.img);
	if (mlx_data->win != NULL)
		mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	if (mlx_data->mlx != NULL)
	{
		mlx_destroy_display(mlx_data->mlx);
		free(mlx_data->mlx);
	}
}
