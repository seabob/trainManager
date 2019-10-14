#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "file_reader.h"

int init_file_reader(file_reader_t *reader, const char *path)
{
	size_t path_length = strlen(path);
	memset(reader, 0, sizeof(file_reader_t));
	reader->fd = open(path, O_RDWR);
	if(reader->fd < 0)
	{
		return reader->fd;
	}

	memset(&reader->path, 0, PATH_LENGTH);
	memcpy(&reader->path, path, path_length);
	return 0;
}

void deinit_file_reader(file_reader_t *reader)
{
	close(reader->fd);
	memset(reader, 0, sizeof(file_reader_t));
}

int get_test_case(file_reader_t *reader, char *test_case, size_t length)
{
    size_t count = 0;
    int ret = 0;
    char character;
	
    if(length < 4)
        return -1;

    memset(test_case, 0, length);

    for(;;)
    {
	if(count >= 3)
	    return count;

        ret = read(reader->fd, &character, 1);
	if(ret <= 0)
	{
	    memset(test_case, 0, length);
	    return ret;
	}

        if(character == ' ')
        {
	    count = 0;
            memset(test_case, 0, length);
            continue;
        }

	if(character == '\r' || character == '\n')
    	    continue;

	if(character == '\0')
	{
	    memset(test_case, 0, length);
            return 0;
	}

        
        test_case[count++] = character;
    }
    return ret;
}

