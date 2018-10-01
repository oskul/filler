/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oskulska <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 18:32:18 by oskulska          #+#    #+#             */
/*   Updated: 2018/05/11 18:32:20 by oskulska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			ft_clear(char **arr)
{
	size_t		count;

	count = 0;
	while (arr[count])
	{
		free(arr[count]);
		arr[count] = NULL;
		count++;
	}
	free(arr);
}

static void		set_player(t_filler *filler)
{
	char		*line;

	get_next_line(STDIN_FILENO, &line);
	if (ft_strequ("$$$ exec p1 : [./oskulska.filler]", line))
	{
		filler->player = 'O';
		filler->enemy = 'X';
	}
	else
	{
		filler->player = 'X';
		filler->enemy = 'O';
	}
	ft_strdel(&line);
}

static t_filler	*init_struct(void)
{
	t_filler	*filler;

	filler = (t_filler*)malloc(sizeof(t_filler));
	filler->map = NULL;
	filler->old_map = NULL;
	filler->piece = NULL;
	filler->piece_new = NULL;
	filler->enemy_last_x = -1;
	filler->enemy_last_y = -1;
	filler->max_shift_x = 0;
	filler->max_shift_y = 0;
	filler->new_x = 0;
	filler->new_y = 0;
	filler->first_read = 1;
	return (filler);
}

static void		free_all(t_filler *filler)
{
	if (filler->old_map)
	{
		ft_clear(filler->old_map);
		filler->old_map = NULL;
	}
	if (filler->piece)
	{
		ft_clear(filler->piece);
		filler->piece = NULL;
	}
	if (filler->piece_new)
	{
		ft_clear(filler->piece_new);
		filler->piece_new = NULL;
	}
}

int				main(void)
{
	t_filler	*filler;

	filler = init_struct();
	set_player(filler);
	while (42)
	{
		filler->min_x = 142;
		filler->min_y = 142;
		filler->max_x = 0;
		filler->max_y = 0;
		free_all(filler);
		get_map_size(filler);
		read_map(filler);
		read_piece(filler);
		ft_newcord_max(filler);
		read_piece_sec(filler);
		find_solution(filler);
		ft_printf("%d %d\n",
			filler->new_y - filler->min_y, filler->new_x - filler->min_x);
		filler->first_read = 0;
	}
}
