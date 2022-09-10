# ************************************************************************** #
#                                                    ,---.      .`````-.     #
#                                                   /,--.|     /   ,-.  \    #
#    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   #
#    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    #
#   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     #
#    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        #
#                                              /  `-----' || ( ' )(__..--.   #
#   Created: 2022/09/10 00:49:21               `-------|||-'(_{;}_)      |   #
#                                                      '-'   (_,_)-------'   #
#   Makefile                                                                 #
# ************************************************************************** #

NAME	=	ft_containers

CC		=	c++

FLAGS	=	-Wall -Wextra -Werror -std=c++98

HEADER	=	-I containers/ -I utils/

SRCS	=	main.cpp

all:		$(NAME)

$(NAME):	
			$(CC) $(FLAGS) $(HEADER) $(SRCS) -o std_containers -D NAMESPACE=std
			$(CC) $(FLAGS) $(HEADER) $(SRCS) -o $(NAME) -D NAMESPACE=ft

clean:
			@rm -f $(NAME) std_containers

fclean:		clean
			@rm -f diff.txt

re:			fclean all

diff:
			@./$(NAME) > ft.txt
			@./std_containers > std.txt
			@diff ft.txt std.txt > diff.txt
			@rm -f ft.txt std.txt

.PHONY:		all clean fclean re diff