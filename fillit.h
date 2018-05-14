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
	int					id;
	t_point				*first;
	t_point				*last;
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

t_list				*read_file(t_list **pieces, int file);

int					tet_lstadd(t_list **point, t_list **end, char *tet, int p_nbr);
t_list				*tet_lstnew(char *tet, int id);

t_etris				*make_piece(char *tet, int id);
char				**shape_piece(int height, int width);
void 				fill_piece(char *tet, char id, t_etris *tetris);

int					tet_check(char *tet, int rd, t_point **hash);
int					validate_piece(char *tet, int location, int *sides);

void 				set_minmax_points(t_point ***point, int count, int location, int *x_max);
t_point				*create_point(int location);

t_map				*create_map(size_t size);
char				**make_empty_map(size_t size);
void 				free_map(t_map **map);

int					solve(t_list **pieces, t_map *map, t_point *point);

void 				tet_place(t_etris *tetris, t_map *map, t_point *point);
void 				tet_remove(t_etris *pieces, t_map *map, t_point *point);
int					check_tet_max(t_etris *tetris, t_map *map, t_point *point);
int					tet_x_shift(t_etris *tetris);

int					check_safe(t_map *map, int y, int x);
int					check_tet_fits(t_etris *tetris, t_map *map);//, t_point *point);

int					next_point(t_point **point, t_map *map);

int					invalid_block(t_point ***points);
void 				free_point(t_point **point);
void 				free_minmax_points(t_point ***points);
void 				free_tetris(t_etris **tetris);

int					tet_to_tetris(t_etris *tetris, t_point **hash);

#endif

// int					next_point(t_point **point, t_map *map)
// {
// 	int				fc;
// 	int				fr;
// 	char			**board;
//
// 	fc = (*point)->y;
// 	fr = (*point)->x;
// 	board = map->rows;
// 	while (board[fc] != NULL)
// 	{
// 		while (board[fc][fr] != '\0')
// 		{
// 			if (board[fc][fr] == '.')
// 				return (1);
// 			fr += 1;
// 		}
// 		fc += 1;
// 		fr = 0;
// 	}
// 	return (0);
// }


// int					solve_map(t_map *map, t_list **pieces)
// {
// 	int				fit;
//
// 	fit = 0;
// 	if (!pieces || !*pieces)
// 	{
// 		ft_putendl("\nsolve_map !pieces || !*pieces");
// 		return (0);
// 	}
// 	while (!(fit = check_tet_fits((t_etris*)(*pieces)->cont, map)))
// 	{
// 		ft_putendl("\nsolve_map !check_tet_fits");
// 		return (0);
// 	}
// 	if (!fit)
// 	{
// 		ft_putendl("\nsolve_map !fit");
// 		return (0);
// 	}
// 	tet_place((t_etris*)(*pieces)->cont, map);
// 	if (!(solve_map(map, &((*pieces)->next))))
// 	{
// 		ft_putendl("\nsolve_map !solve_map: tet_remove called");
// 		tet_remove((t_etris*)(*pieces)->cont, map);
// 		return (solve_map(map, pieces));
// 	}
// 	return (1);
// }
//
// /*
// **	map_solve() is called until (*pieces) is NULL
// **	it calls check_tet_fits and places the tet on the map if it does
// **	it then calls map_solve() again with the next piece
// **	if that fails it removes the start tet
// */
// int					setup_solve(t_list **pieces, t_map *map)
// {
// 	t_list			*first_piece;
// 	size_t			map_size;
//
//
// 	while ((first_piece = *pieces)
// 		&& !(solve_map(map, &first_piece)))
// 	{
// 		free_map(&map);
// 		if (!(map = create_map(++map_size)))
// 		{
// 			ft_putendl("\nsetup_solve !create_map");
// 			return (0);
// 		}
// 	}
// 	ft_putstrarr(map->rows);
// 	free_map(&map);
// 	free(map);
// 	return (1);
// }
