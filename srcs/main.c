/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:52:47 by lcottet           #+#    #+#             */
/*   Updated: 2024/05/08 16:02:32 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "file.h"
#include "engine.h"
#include "display.h"
#include "ft_error.h"

int	main(int argc, char **argv)
{
	t_engine	engine;

	if (argc < 2)
		return (custom_error(argv[0], ERR_USAGE));
	if (parsing(&engine, argv[1]) == FAILURE)
	{
		vector_free(&engine.objects);
		return (FAILURE);
	}
	if (mlx_init_mlx(&engine.mlx) == FAILURE)
	{
		vector_free(&engine.objects);
		mlx_destroy_mlx(&engine.mlx);
		return (custom_error(argv[0], ERR_MLX_INIT));
	}
	render(&engine);
	mlx_loop(engine.mlx.mlx);
	vector_free(&engine.objects);
	vector_free(&engine.lights);
	mlx_destroy_mlx(&engine.mlx);
	return (SUCCESS);
}
