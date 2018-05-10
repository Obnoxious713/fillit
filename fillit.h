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
	int					width; // most tetrimino dims (2, 3) (3, 2)
	int					height; // only one possible fit in (1, 4) (4, 1) (2, 2)
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
**	}					t_list;
*/

t_list				*read_file(t_list **pieces, int file);

int					tet_lstadd(t_list **start, t_list **end, char *tet, int p_nbr);
t_list				*tet_lstnew(char *tet, int id);

t_etris				*make_piece(char *tet, int id);
char				**shape_piece(int height, int width);
void 				fill_piece(char *tet, char id, t_etris *tetris);

int					tet_check(char *tet, int rd, t_point **hash);
int					validate_piece(char *tet, int location, int *sides);

void 				set_minmax_points(t_point **point, int count, int location, int x_max);
t_point				*create_point(int location);

t_map				*create_map(size_t size);
char				**make_empty_map(size_t size);
void 				free_map(t_map **map);

int					solve(t_list *pieces);
int					setup_solve(t_list **pieces);
int					solve_map(t_map *map, t_list **pieces, t_point *point);

void 				tet_place(t_etris* tetris, t_map *map, t_point *point);
void 				tet_remove(t_etris* tetris, t_map *map);
int					check_tet_max(t_etris *tetris, t_map *map, t_point *point);
int					tet_x_shift(t_etris *tetris);

int					check_safe(t_map *map, int y, int x);
int					check_tet_fits(t_etris *tetris, t_map *map);

#endif
