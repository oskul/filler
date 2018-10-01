/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oskulska <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 18:57:00 by oskulska          #+#    #+#             */
/*   Updated: 2018/05/11 18:57:03 by oskulska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft/libft.h"
# include <fcntl.h>

typedef	struct		s_filler
{
	char			**map;
	char			**old_map;
	char			**piece;
	char			**piece_new;
	char			player;
	char			enemy;
	int				width;
	int				height;
	int				max_x;
	int				max_y;
	int				min_x;
	int				min_y;
	int				max_shift_x;
	int				max_shift_y;
	int				piece_width;
	int				piece_height;
	int				new_x;
	int				new_y;
	int				enemy_last_x;
	int				enemy_last_y;
	int				min_dist;
	int				first_read;
	int				count;
}					t_filler;

void				get_map_size(t_filler *filler);
void				get_piece_shape(t_filler *filler);
void				read_piece_sec(t_filler *filler);
void				ft_newcord_max(t_filler *filler);
void				read_piece(t_filler *filler);
void				read_map(t_filler *filler);
void				find_first_move(t_filler *filler);
void				find_last_move(t_filler *filler);
void				find_solution(t_filler *filler);
void				ft_clear(char **arr);

#endif
