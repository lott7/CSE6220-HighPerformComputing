CC = mpicxx
CFLAG = -lm

TARGET = pi_calc
SOURCES = main.cpp
(TARGET): $(SOURCES)
		$(CC) $(CFLAG) -o $(TARGET) $(SOURCES)
	
.PHONY: clean
clean:
		@$(RM) $(TARGET)