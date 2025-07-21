#include "includes/parser.h"
#include "mlx/minilibx-linux/mlx.h"
#include "includes/math_utils.h"
#include "includes/scene.h"
#include "includes/miniRT.h"
#include "includes/render.h"
#include <stdio.h>
#include <stdlib.h>

int validate_scene(t_scene *scene)
{
    if (!scene->lights)
    {
        printf("Error: Scene must have at least one light\n");
        return (0);
    }
    
    if (!scene->spheres && !scene->planes && !scene->cylinders)
    {
        printf("Error: Scene must have at least one object\n");
        return (0);
    }
    
    return (1);
}

void cleanup_and_exit(t_mlx_data *data)
{
    if (data->img.img)
        mlx_destroy_image(data->mlx_ptr, data->img.img);
    if (data->win_ptr)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    if (data->mlx_ptr)
    {
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
    }
    // TODO: Add scene cleanup function
    exit(0);
}

int handle_keypress(int keycode, t_mlx_data *data)
{
    if (keycode == 65307) // ESC key
    {
        cleanup_and_exit(data);
    }
    return (0);
}

int close_window(t_mlx_data *data)
{
    cleanup_and_exit(data);
    return (0);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <scene_file.rt>\n", argv[0]);
        return (1);
    }
    
    t_mlx_data data;
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "miniRT");
    data.img = init_image(data.mlx_ptr);
    
    t_scene scene;
    initialize_scene(&scene);
    data.scene = &scene;
    
    // Parse scene file
    read_rt_file(argv[1], &scene);
    
    // Render scene
    render_full_scene(&data);
    
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);
    
    // Event hooks
    mlx_hook(data.win_ptr, 2, 1L<<0, handle_keypress, &data);
    mlx_hook(data.win_ptr, 17, 1L<<17, close_window, &data);
    
    mlx_loop(data.mlx_ptr);
    return (0);
}
/*
int	main(void)
{
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, WIDTH, HEIGHT, "RT test");

	t_image	image = init_image(mlx);

	t_camera	camera = {
		.position = { -50, 0, 20 },
		.orientation = { 0, 0, 1 },
		.fov = 70
	};

	t_sphere sphere = {
		.center = { 0, 0, 20.6 },
		.radius = 12.6,
		.color = {10, 0, 255}
	};

	render(&image, camera, &sphere);

	mlx_put_image_to_window(mlx, win, image.img, 0, 0);
	mlx_loop(mlx);

	return (0);
}*/

