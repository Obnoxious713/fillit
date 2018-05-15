/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <jfleisch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 13:16:18 by jfleisch          #+#    #+#             */
/*   Updated: 2018/05/05 13:16:18 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define MAX_TETRIMINOS 26
# define BOARD_SIZE 16
# define BUF 21
# include "libft/libft.h"

typedef	struct			s_point
{
	int					x;
	int					y;
	int					sides;
}						t_point;

typedef struct			s_etris
{
	char				**shape;
	int					width;
	int					height;
	int					id;
	t_point				*first;
}						t_etris;

typedef struct			s_map
{
	char				**rows;
	int					r;
	int					c;
	size_t				size;
}						t_map;

/*
** t_list structure found in libft/libft.h:
**
** typedef struct		s_list
** {
**		void			*cont;
**		size_t			cont_size;
**		struct s_list	*next;
**		struct s_list	*prev;
**	}					t_list;
*/

int						tet_lstadd(t_list **start, t_list **end,
									char *tet, int p_nbr);
t_list					*tet_lstnew(char *tet, int id);
void					free_tetris(t_etris **tetris);

t_etris					*make_piece(char *tet, int id);
char					**shape_piece(int height, int width);
void					fill_piece(char *tet, char id, t_etris *tetris);
int						tetris_dim(t_etris *tetris);

t_map					*create_map(size_t size);
char					**make_empty_map(size_t size);
void					free_map(t_map **map);

int						get_next_point(t_point **point, char **board);
t_point					*create_point(int location);
void					set_minmax_points(t_point ***point, int count,
										int location, int *x_max);
int						invalid_block(t_point ***points);
void					free_point(t_point **point);
void					free_minmax_points(t_point ***points);

int						check_tet_fits(t_etris *tetris, t_map *map,
										t_point *point);
int						tet_check(char *tet, int rd,
									t_point ***hash, int count);
int						validate_piece(char *tet, int location, int *sides);
int						check_tet_max(t_etris *tetris, t_map *map,
									t_point *point);
int						tet_x_shift(t_etris *tetris);

int						map_solve(t_list **pieces);
int						solve(t_list **pieces, t_map *map, t_point *first);
void					tet_remove(t_etris *tetris, t_map *map);
void					tet_place(t_etris *tetris, t_map *map, t_point *first);

#endif
