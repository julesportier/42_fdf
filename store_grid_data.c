/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_grid_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:35:39 by juportie          #+#    #+#             */
/*   Updated: 2025/02/06 12:42:33 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	store_spacing(t_grid_data *grid_data)
{
	int	height;
	int	width;

	height = (HEIGHT * ZOOM / 100) / grid_data->height;
	width = (WIDTH * ZOOM / 100) / grid_data->width;
	if (height < width)
		grid_data->spacing = height;
	else
		grid_data->spacing = width;
}

void	store_start_point(t_grid_data *grid_data)
{
	grid_data->start_point.y = (
		(HEIGHT - grid_data->spacing * grid_data->height) / 2);
	grid_data->start_point.x = (
		(WIDTH - grid_data->spacing * grid_data->width) / 2);
}
