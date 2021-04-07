NAME = libftprintf.a

#compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -Wformat -Wvarargs

#VPATH is used to gather sources from multiple directories
#sources
VPATH := ./src
SRCS	:=	ft_printf.c 
SRCS	+=	ftprintf_read_args.c \
			ftprintf_integer.c \
			ftprintf_float.c \
			ftprintf_str.c \
			ftprintf_c.c \
			ftprintf_convert.c \
			ftprintf_sign.c

#libft sources
VPATH += ./libft/srcs/process_control:./libft/srcs/file_io:./libft/srcs/math:\
./libft/srcs/type_conversion:./libft/srcs/string_utils:./libft/srcs/mem_utils \
./libft/srcs/wchar_utils
SRCS	+=	ft_getout.c
SRCS	+=	ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putstr_fd.c
SRCS	+=	ft_pow.c
SRCS	+=	ft_atoi.c \
			ft_itoa.c \
			ft_itoa_base.c \
			ft_uitoa.c \
			ft_uitoa_base.c \
			ft_ftoa.c
SRCS	+=	ft_strcat.c \
			ft_strncat.c \
			ft_strchr.c \
			ft_strcpy.c \
			ft_strequ.c \
			ft_strncpy.c \
			ft_strdup.c \
			ft_strndup.c \
			ft_strjoin.c \
			ft_strlen.c \
			ft_strnew.c
SRCS	+=	ft_bzero.c \
			ft_memalloc.c \
			ft_memset.c \
			ft_memcpy.c
SRCS	+=	ft_putwchar.c \
			ft_putwstr.c \
			ft_wcharlen.c \
			ft_wstrlen.c

#object files
OBJ_DIR	:=	./obj
OBJS	:=	$(patsubst %,$(OBJ_DIR)/%,$(SRCS:.c=.o))

#includes
INC_DIR	:=	./includes
INC_DIR	+=	./libft/includes
IFLAGS	+=	$(foreach d, $(INC_DIR), -I$d)

NC		= \033[0m
PURPLE	= \033[1;35m

all: $(NAME)

$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@echo "${PURPLE}[ftprintf] building library...${NC}"
	@ar rcs $(NAME) $(OBJS)

clean :
	@echo "${PURPLE}[ftprintf] removing object files...${NC}"
	@rm -rf $(OBJ_DIR)

fclean : clean
	@echo "${PURPLE}[ftprintf] removing binary...${NC}"
	@rm -f $(NAME)

re : fclean all
