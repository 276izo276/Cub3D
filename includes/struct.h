#ifndef STRUCT_H
# define STRUCT_H

#include "t_lst.h"

typedef struct s_data	t_data;
typedef struct s_map	t_map;
typedef struct s_img	t_img;
typedef struct s_color	t_color;
typedef	struct s_mlx	t_mlx;
typedef struct s_coo	t_coo;
typedef	struct s_mini	t_mini;

struct s_coo
{
	int	x;
	int	y;
};

struct s_mlx
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
};

struct s_mini
{
	char	*path[6];
	char	*sprite[6];
	int		height;
	int		width;
};

struct s_map
{
	int		fd;
	int		tabmap_height;
	char	**tabmap;
	t_coo	*player_start;
	t_lst	*lines;
	t_lst	*map;
	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;
	t_mini	mini;
	t_color	*floor;
	t_color	*ceiling;
};

struct s_data
{
	int		ac;
	char	**av;
	t_map	map;
	t_mlx	mlx;
};

struct	s_img
{
	void	*mlx;
	char	*path;
	void	*img;
	int		width;
	int		height;
};

struct s_color
{
	int	r;
	int	g;
	int	b;
};

t_coo	*init_t_coo(int y, int x);

#endif
