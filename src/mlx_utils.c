/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:47:42 by juportie          #+#    #+#             */
/*   Updated: 2025/02/12 11:43:25 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../minilibx/mlx.h"

int	end_loop_mouse(t_mlx_data *mlx_data)
{
	mlx_loop_end(mlx_data->mlx);
	return (0);
}

int	end_loop_esc(int keycode, t_mlx_data *mlx_data)
{
	if (keycode == ESC)
		mlx_loop_end(mlx_data->mlx);
	return (0);
}
