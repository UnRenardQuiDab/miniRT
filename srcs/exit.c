/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:53:12 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/15 14:59:37 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "engine.h"

int	exit_rt(t_engine *engine, int status)
{
	if (engine->frame_details.thread_count)
		join_threads(&engine->frame_details);
	vector_free(&engine->objects);
	vector_free(&engine->lights);
	if (engine->mlx.mlx != NULL)
		mlx_destroy_mlx(&engine->mlx);
	return (status);
}
