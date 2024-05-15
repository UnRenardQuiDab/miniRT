/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:52:47 by lcottet           #+#    #+#             */
/*   Updated: 2024/05/15 14:59:53 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "mlx.h"
#include "file.h"
#include "engine.h"
#include "display.h"
#include "ft_error.h"
#include "matrix.h"
#include "camera.h"

bool	is_rt_file(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 3)
		return (false);
	if (ft_strcmp(filename + len - 3, ".rt") == 0)
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_engine	engine;

	if (argc < 2 || !is_rt_file(argv[1]))
		return (custom_error(argv[0], ERR_USAGE));
	ft_memset(&engine, 0, sizeof(t_engine));
	if (parsing(&engine, argv[1]) == FAILURE)
		return (exit_rt(&engine, FAILURE));
	engine.mlx.engine = &engine;
	if (mlx_init_mlx(&engine.mlx) == FAILURE)
		return (exit_rt(&engine, custom_error(argv[0], ERR_MLX_INIT)));
	if (create_threads(&engine) == FAILURE)
		return (exit_rt(&engine, FAILURE));
	project_camera(&engine.camera);
	calculate_inside_objects(&engine);
	mlx_loop(engine.mlx.mlx);
	return (exit_rt(&engine, SUCCESS));
}
