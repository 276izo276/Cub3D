#ifndef IMAGE_H
# define IMAGE_H

typedef struct s_img	t_img;

struct	s_img
{
	void	*mlx;
	char	*path;
	void	*img;
	int		width;
	int		height;
};

#endif