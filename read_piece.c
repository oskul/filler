/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oskulska <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 18:52:01 by oskulska          #+#    #+#             */
/*   Updated: 2018/05/11 18:52:03 by oskulska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		init_piece(t_filler *filler)
{
	int			i;

	i = 0;
	if (filler->piece_new == NULL)
	{
		filler->piece_new = (char **)malloc(sizeof(char *)
			* filler->max_shift_y + 1);
		filler->piece_new[filler->max_shift_y] = NULL;
		while (i < filler->max_shift_y)
		{
			filler->piece_new[i] = ft_strnew(filler->max_shift_x);
			i++;
		}
	}
}

void			get_piece_shape(t_filler *filler)
{
	char		*line;
	char		*str;

	if (get_next_line(STDIN_FILENO, &line) == -1 || !line)
		exit(-1);
	str = line;
	while (!ft_isdigit(*line))
		line++;
	filler->piece_height = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	filler->piece_width = ft_atoi(line);
	free(str);
}

void			ft_newcord_max(t_filler *filler)
{
	int			x;
	int			y;

	y = -1;
	while (++y < filler->piece_height)
	{
		x = -1;
		while (++x < filler->piece_width)
		{
			if (filler->piece[y][x] == '*')
			{
				if (y > filler->max_y)
					filler->max_y = y;
				if (x > filler->max_x)
					filler->max_x = x;
				if (y < filler->min_y)
					filler->min_y = y;
				if (x < filler->min_x)
					filler->min_x = x;
			}
		}
	}
	filler->max_shift_x = filler->max_x - filler->min_x + 1;
	filler->max_shift_y = filler->max_y - filler->min_y + 1;
}

void			read_piece(t_filler *filler)
{
	char		*line;
	int			i;

	i = 0;
	get_piece_shape(filler);
	if (filler->piece == NULL)
	{
		filler->piece = (char **)malloc(sizeof(char *)
			* filler->piece_height + 1);
		filler->piece[filler->piece_height] = NULL;
	}
	i = 0;
	while (i < filler->piece_height)
	{
		if (get_next_line(STDIN_FILENO, &line) < 1)
			exit(-1);
		filler->piece[i] = ft_strdup(line);
		ft_strdel(&line);
		i++;
	}
}

void			read_piece_sec(t_filler *filler)
{
	int			i;
	int			x;
	int			y;

	init_piece(filler);
	y = 0;
	while (y < filler->max_shift_y)
	{
		x = 0;
		while (x < filler->max_shift_x)
		{
			if (filler->piece[y + filler->min_y][x + filler->min_x] == '*')
				filler->piece_new[y][x] = '*';
			else
				filler->piece_new[y][x] = '.';
			x++;
		}
		y++;
	}
	filler->piece_height = filler->max_shift_y;
	filler->piece_width = filler->max_shift_x;
}
