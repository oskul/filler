/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oskulska <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 18:38:54 by oskulska          #+#    #+#             */
/*   Updated: 2018/05/11 18:38:56 by oskulska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			find_first_move(t_filler *filler)
{
	int			x;
	int			y;

	y = 0;
	while (y < filler->height)
	{
		x = 0;
		while (x < filler->width)
		{
			if (filler->map[y][x] == filler->enemy)
			{
				filler->enemy_last_x = x;
				filler->enemy_last_y = y;
				break ;
			}
			x++;
		}
		y++;
	}
}

void			find_last_move(t_filler *filler)
{
	int			x;
	int			y;

	y = 0;
	while (y < filler->height)
	{
		x = 0;
		while (x < filler->width)
		{
			if (filler->map[y][x] == filler->enemy
				&& filler->old_map[y][x] != filler->map[y][x])
			{
				filler->enemy_last_x = x;
				filler->enemy_last_y = y;
				break ;
			}
			x++;
		}
		y++;
	}
}

static int		find_min_dist(t_filler *filler, int pos_x, int pos_y)
{
	int			x;
	int			y;
	int			min;

	y = -1;
	while (++y < filler->piece_height)
	{
		x = -1;
		while (++x < filler->piece_width)
		{
			if (filler->piece_new[y][x] == '*')
			{
				min = abs(filler->enemy_last_x - (x + pos_x))
				+ abs(filler->enemy_last_y - (y + pos_y));
				if (filler->min_dist > min)
				{
					filler->min_dist = min;
					filler->new_x = pos_x;
					filler->new_y = pos_y;
				}
			}
		}
	}
	return (filler->min_dist);
}

static int		can_insert(t_filler *filler, int pos_x, int pos_y)
{
	int			x;
	int			y;

	filler->count = 0;
	y = -1;
	while (++y < filler->piece_height)
	{
		x = -1;
		while (++x < filler->piece_width)
		{
			if (filler->piece_new[y][x] == '*')
			{
				if (pos_x + x < filler->width && pos_y + y < filler->height)
				{
					if (filler->map[pos_y + y][pos_x + x] == filler->player)
						filler->count++;
					if (filler->map[pos_y + y][pos_x + x] == filler->enemy)
						return (0);
				}
			}
		}
	}
	if (filler->count == 1)
		return (1);
	return (0);
}

void			find_solution(t_filler *filler)
{
	int			x;
	int			y;
	int			min;

	y = 0;
	while (y < filler->height - filler->piece_height)
	{
		x = 0;
		while (x < filler->width - filler->piece_width)
		{
			if (can_insert(filler, x, y))
			{
				min = find_min_dist(filler, x, y);
				if (filler->min_dist > min)
				{
					filler->min_dist = min;
					filler->new_x = x;
					filler->new_y = y;
				}
			}
			x++;
		}
		y++;
	}
}
