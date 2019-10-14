#ifndef __FILE_READER_H__
#define __FILE_READER_H__

#define PATH_LENGTH	512
#define BUFFER_LENGTH	4096

//test case read manager
typedef struct file_reader{
    int    fd;
    char   path[PATH_LENGTH];
    char   buffer[BUFFER_LENGTH];
    int    seek;
}file_reader_t;


int init_file_reader(file_reader_t *reader, const char *file_path);
void deinit_file_reader(file_reader_t *reader);

int get_test_case(file_reader_t *reader, char * test_case, size_t length);

#endif
