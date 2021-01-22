LIBS = "-lstdc++"
CFILES = player.cpp tttB_driver.cpp TTTBoard3.cpp

all: $(CFILES)
	gcc -o program $(LIBS) $(CFILES)
