# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tstahlhu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 12:47:35 by tstahlhu          #+#    #+#              #
#    Updated: 2023/11/03 12:03:14 by tstahlhu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	pipex
CC	=	cc
CFLAGS	=	-Wall -Werror -Wextra
LIBFT	=	libft.a
PATH_L	=	./libft
PATH_C	=	./src/
PATH_G	=	./src/gnl/
PATH_INCL =	./includes/

CFILES	=	pipex_bonus.c init_bonus.c path_bonus.c error_bonus.c \
			clean_up_bonus.c child_bonus.c here_doc.c
CFILES_G=	get_next_line.c get_next_line_utils.c

OBJ	:=	$(patsubst %.c, %.o, $(addprefix $(PATH_C), $(CFILES)))
OBJ_G	=	$(patsubst %.c, %.o, $(addprefix $(PATH_G), $(CFILES_G)))

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJ_G) $(OBJ)
				$(CC) $(CFLAGS) $(OBJ_G) $(OBJ) -l:$(LIBFT) -o $(NAME) -I $(PATH_L) -L $(PATH_L)

%.o: %.c
				$(CC) $(CFLAGS) -c -g -I $(PATH_INCL) $< -o $@

$(LIBFT):	
				@$(MAKE) -C $(PATH_L)
				cp $(PATH_L)/$(LIBFT) .


clean:
				rm -f $(OBJ) $(OBJ_G)
				@$(MAKE) -C $(PATH_L) clean
	
fclean:		clean
				rm -f $(NAME)
				rm -f $(LIBFT)

re:		fclean all


.PHONY: all clean fclean re bonus
