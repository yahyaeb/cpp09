# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/30 16:05:46 by yel-bouk          #+#    #+#              #
#    Updated: 2025/09/17 14:10:57 by yel-bouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = btc
CC = c++
SRCS = main.cpp \
		BitcoinExchange.cpp 

CFLAGS = -Wall -Wextra -Werror -std=c++98

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJS)
	
fclean:
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re