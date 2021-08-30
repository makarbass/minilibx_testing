#include "fdf.h"

int render_next_frame(fdf *data)
{
	mlx_clear_window (data->mlx_ptr, data->win_ptr);
	square(data, 0x00ff0000);
}

int	close(int keycode, fdf *data)
{
	exit(0);
}

int deal_key(int key, fdf *data)  // ОБРАБОТКА КНОПОК КЛАВИАТУРЫ
{
	//printf("keycode : %d\n", key);
	if (key == 53) // ESC
	{
		free(data); // освободить память, которую выделяем в main'e
		exit(0); // выйти из программы
	}
	if ((key == 123 || key == 0) && (data->x > 0)) // <- & A
		data->x -= data->zoom; // смещаемся по х влево
	if ((key == 124 || key == 2) && (data->x < (data->width - data->zoom))) // -> & D и находимся не ближе чем край минус один квадрат
		data->x += data->zoom; // смещаемся по х вправо
	if ((key == 125 || key == 1) && (data->y < (data->height - data->zoom)))// DOWN & S
		data->y += data->zoom; // смещаемся по у вниз
	if ((key == 126 || key == 13) && (data->y > 0))//UP & W
		data->y -= data->zoom; // смещаемся по у вверх
	return(0);
}

void init(fdf *data) // запись начальных значений
{
	data->width = 256;
	data->height = 240;
	data->mlx_ptr = mlx_init(); // инизиацизируем форму (значение в структуре data - mlx_ptr) 
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height, "TEST"); // создаем окно 
	data->zoom = 16; // коэффицент размера (будет не пиксель а квадрат 16х16)
	data->x = 16; // начальная точка х
	data->y = 16; // начальная точка у
	square(data, 0x00FF0000); // рисование квадрата
}

int main(int argc, char** argv)
{
	fdf *data; // структура, в которой хранятся все данные вместо переменных

	data = (fdf*)malloc(sizeof(fdf)); // Выделяем память
	init(data); // записываем начальные значения
	
	mlx_key_hook(data->win_ptr, deal_key, data); // следим за кнопками ( передаем окно, функцию deal_key и структуру(для изменения значений в ней))
	mlx_loop_hook(data->mlx_ptr, render_next_frame, data); // СЛЕДУЮЩИЙ КАДР
	mlx_hook(data->win_ptr, 17, 1L<<17, close, data); // НАЖАТИЕ НА "x" (крестик для закрытия)
	mlx_loop(data->mlx_ptr); // держим окно открытым пока программа работает 
}

//	bresenham(16, 16, 784, 16, data);  //рисование линии
//	mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->x, data->y, 0x00FF0000); // рисование пикселя