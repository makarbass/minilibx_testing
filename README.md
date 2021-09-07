LINUX: 
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev

gcc -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
