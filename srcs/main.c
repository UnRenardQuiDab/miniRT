/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:52:47 by lcottet           #+#    #+#             */
/*   Updated: 2024/05/13 20:51:58 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "file.h"
#include "engine.h"
#include "display.h"
#include "ft_error.h"
#include "matrix.h"
#include "camera.h"

void	vec4_print(t_vec4 vec)
{
	printf("%f %f %f %f\n", vec.x, vec.y, vec.z, vec.w);
	printf("\n");
}

void	mat4_print(t_mat4 mat)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		printf("|%f %f %f %f |\n", mat.matrix[i * 4], mat.matrix[i * 4 + 1],
			mat.matrix[i * 4 + 2], mat.matrix[i * 4 + 3]);
		i++;
	}
	printf("\n");
}

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
