CC = gcc
CFLAGS = -c -Wall
LDFLAGS = 
SOURCES = main.c vect.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = VectorLab

all: $(Sources) $(EXECUTABLE)

# pull in dependency infor for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)*.d