/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:47:42 by juportie          #+#    #+#             */
/*   Updated: 2025/02/12 10:27:11 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
//#include "libft/libft.h"
#include "minilibx/mlx.h"

int	close_win_mouse(t_mlx_data *mlx_data)
{
	mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	return (0);
}

int	close_win_esc(int keycode, t_mlx_data *mlx_data)
{
	if (keycode == ESC)
		mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	return (0);
}
