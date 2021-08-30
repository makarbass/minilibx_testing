#include "fdf.h"

int deal_key(int key, fdf *data)  // ОБРАБОТКА КНОПОК
{
	printf("keycode : %d\n", key);
	if (key == 53) // ESC
	{
		free(data); // освободить память, которую выделяем в main'e
		exit(0); // выйти из программы
	}
	if (key == 124 || key == 2) // -> & D
		data->x += data->zoom; // смещаемся по х вправо
	if (key == 123 || key == 0) // <- & A
		data->x -= data->zoom; // смещаемся по х влево
	if (key == 126 || key == 13) //DOWN & S
		data->y -= data->zoom; // смещаемся по у вниз
	if (key == 125 || key == 1) // UP & W
		data->y += data->zoom; // смещаемся по у вверх
	mlx_clear_window (data->mlx_ptr, data->win_ptr); // очищаем окно
	square(data); //рисуем квадрат
	return(0);
}

int main(int argc, char** argv)
{
	fdf *data; // структура, в которой хранятся все данные вместо переменных

	data = (fdf*)malloc(sizeof(fdf)); // Выделяем память
	data->mlx_ptr = mlx_init(); // инизиацизируем форму (значение в структуре data - mlx_ptr) 
	data->win_ptr = mlx_new_window(data->mlx_ptr, 800, 600, "TEST"); // создаем окно 
	data->zoom = 16; // коэффицент размера (будет не пиксель а квадрат 16х16)
	data->x = 10; // начальная точка х
	data->y = 10; // начальная точка у
 	//bresenham(10, 10, 600, 400, data);  //рисование линии
	//mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->x, data->y, 0x00FF0000); // рисование пикселя
	square(data); // рисование квадрата
	mlx_key_hook(data->win_ptr, deal_key, data); // следим за кнопками ( передаем окно, функцию deal_key и структуру(для изменения значений в ней))
	mlx_loop(data->mlx_ptr); // держим окно открытым пока программа работает 
}