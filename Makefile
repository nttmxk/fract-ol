NAME					= fractal

SRCS					= fractol.c \
						  fractol_utils.c \
						  fractol_loop.c \
						  mandelbrot.c \
						  julia.c \
						  burning_ship.c

BNS_SRCS				= fractol.c \
                          fractol_utils.c \
                          fractol_loop.c \
                          mandelbrot.c \
                          julia.c \
                          burning_ship.c

OBJS					= $(SRCS:.c=.o)

BNS_OBJS				= $(BNS_SRCS:.c=.o)

FLAGS					= -Wall -Wextra -Werror 

ifdef WITH_BNS
	OBJ_FILES = $(BNS_OBJS)
else
	OBJ_FILES = $(OBJS)
endif


$(NAME)	:	$(OBJ_FILES)
	gcc $(FLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@ $^

all		:	$(NAME)

bonus	:
	make WITH_BNS=1 all

%.o	: %.c
	gcc $(FLAGS) -Imlx -c $< -o $@ -I./

clean	:
	rm -f $(OBJS)

fclean	:	clean
	rm -f $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re bonus
