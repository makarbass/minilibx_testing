#include "fdf.h"

int render_next_frame(fdf *data) // РЕНДЕРИНГ СЛЕДУЮЩЕГО КАДРА
{
	//mlx_clear_window (data->mlx_ptr, data->win_ptr); // ЧИСТИМ КАДР
	square(data, 0x00ff0000); // РИСУЕМ НОВЫЙ КВАДРАТ
}

int	close(int keycode, fdf *data) //НАЖАТИЕ НА х
{
	exit(0); 
}

int resize(int keycode, fdf *data) // СВОРАЧИВАНИЕ & РАЗВОРОТ ОКНА
{
//	printf("RESIZE\n");
}

int deal_key(int key, fdf *data)  // НАЖАТИЕ КНОПКИ
{
	//printf("keycode : %d\n", key);
	if (key == 53) // ESC
	{
		exit(0); // выйти из программы
	}
	if ((key == 123 || key == 0) && (data->x > data->zoom)) // <- & A и контроль за тем, чтоб квадрат не вышел за рамку
	{
		square(data, 0x00000000); // на месте старого квадрата рисуем черный квадрат
		data->x -= data->zoom; // смещаемся по х влево
	}
	if ((key == 124 || key == 2) && (data->x < (data->width - 2 * data->zoom))) // -> & D и находимся не ближе чем край рамки минус один квадрат (два квадрата от края окна)
	{	
		square(data, 0x00000000); // на месте старого квадрата рисуем черный квадрат
		data->x += data->zoom; // смещаемся по х вправо
	}
	if ((key == 125 || key == 1) && (data->y < (data->height - 2 * data->zoom)))// DOWN & S
	{
		square(data, 0x00000000); // на месте старого квадрата рисуем черный квадрат
		data->y += data->zoom; // смещаемся по у вниз
	}
	if ((key == 126 || key == 13) && (data->y > data->zoom))//UP & W
	{
		square(data, 0x00000000); // на месте старого квадрата рисуем черный квадрат
		data->y -= data->zoom; // смещаемся по у вверх
	}
	return(0);
}

int release_key(int key, fdf *data) //ОТПУСК КНОПКИ
{
	//printf("OTPUSK\n");
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

void ramka(fdf *data) // рисуем рамку
{
	horizontal_line((data->zoom - 1), (data->width - data->zoom), (data->zoom - 1), data);
	horizontal_line((data->zoom - 1), (data->width - data->zoom), (data->height - data->zoom), data);
	vertical_line((data->zoom - 1), (data->zoom - 1), (data->height - data->zoom), data);
	vertical_line((data->width - data->zoom), (data->zoom - 1), (data->height - data->zoom + 1), data);
}

int main(int argc, char** argv)
{
	fdf *data; // структура, в которой хранятся все данные вместо переменных

	data = (fdf*)malloc(sizeof(fdf)); // Выделяем память
	init(data); // записываем начальные значения
	ramka(data); // рисуем рамку

	mlx_hook(data->win_ptr, 2, 0, deal_key, data); // следим за кнопками ( передаем окно, функцию deal_key и структуру(для изменения значений в ней))
	mlx_hook(data->win_ptr, 3 ,0, release_key, data); // отпустил кнопку
	mlx_hook(data->win_ptr, 17, 0, close, data); // НАЖАТИЕ НА "x" (крестик для закрытия)
	mlx_hook(data->win_ptr, 12, 0, resize, data); // развернул окно или свернул

	mlx_loop_hook(data->mlx_ptr, render_next_frame, data); // СЛЕДУЮЩИЙ КАДР
	mlx_loop(data->mlx_ptr); // держим окно открытым пока программа работает 
	free(data); // освобождаем память
	return(0);
}

//	bresenham(16, 16, 784, 16, data);  //рисование линии
//	mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->x, data->y, 0x00FF0000); // рисование пикселя