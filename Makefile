ourPython	: ourPython.tab.o ourPython.o Object.o Expression.o Statement.o
		  g++ -o $@ ourPython.tab.o ourPython.o Object.o \
			Expression.o Statement.o

Object.o	: ourPython.h Exception.h Object.h Object.cpp
		  g++ -c -g Object.cpp

Expression.o	: ourPython.h Exception.h Object.h Expression.h Expression.cpp
		  g++ -c -g Expression.cpp

Statement.o	: ourPython.h Exception.h Object.h Expression.h Statement.h \
			Statement.cpp
		  g++ -c -g Statement.cpp

ourPython.o	: ourPython.h Exception.h Object.h Expression.h Statement.h \
			ourPython.tab.h ourPython.cpp
		  g++ -c -g ourPython.cpp

ourPython.cpp	: ourPython.lex
		  flex -o ourPython.cpp ourPython.lex 

ourPython.tab.o	: ourPython.h Exception.h Object.h Expression.h Statement.h \
			ourPython.tab.h ourPython.tab.c
		  g++ -c -g ourPython.tab.c

ourPython.tab.c	: ourPython.y
		  bison -d --debug ourPython.y

ourPython.tab.h	: ourPython.y
		  bison -d --debug ourPython.y

clean		:
		  rm *.o *.output *.tab.h *.tab.c ourPython ourPython.cpp