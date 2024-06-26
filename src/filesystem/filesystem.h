#define BASE_BLOCK_ADDRESS 100
#define FILE_NAME_LENGTH 256

typedef struct {
    int head, tail;
} base_block_t;

typedef struct {
    char filename[FILE_NAME_LENGTH];
    int next_file_address;
} metadata_t;

base_block_t *base_block;

void filesystem_init();
void create_file(char *, char *);
char **list_files();
void print_fs();
char *read_file(char *);

metadata_t *load_metadata(int);
int get_address_by_filename( char * );
int get_prev_file_address(int);
int get_files_number();