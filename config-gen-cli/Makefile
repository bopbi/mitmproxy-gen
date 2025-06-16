CC = gcc
CFLAGS = -Wall -g
SRCS = main.c db_migration.c url_pattern.c label.c url_label.c sqlite3.c
OBJS = $(SRCS:.c=.o)
TARGET = config-gen

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
