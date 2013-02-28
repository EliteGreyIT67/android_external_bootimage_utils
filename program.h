
#ifndef _PROGAM_H_
#define _PROGAM_H_



#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__) 
	#include <windows.h>
#define lstat stat
#define DEFAULT_BOARD_NAME "board.txt"
#define DEFAULT_HEADER_NAME "header.txt"
#define DEFAULT_CMDLINE_NAME "cmdline.txt"
#define DEFAULT_PAGESIZE_NAME "pagesize.txt"
#define fsync 
#else
#define DEFAULT_HEADER_NAME "header"
#define DEFAULT_CMDLINE_NAME "cmdline"
#define DEFAULT_PAGESIZE_NAME "pagesize"
#define DEFAULT_BOARD_NAME "board"
#endif
#include <limits.h>	
#include <bootimg.h>
#include "file.h"
#include "help.h"
int create_boot_image_file();
int update_boot_image_file_direct();
int list_boot_image_info();
int extract_boot_image_file();
int update_boot_image_file();

int log_write(const char *format, ...);
int strlcmp(const char *s1, const char *s2);
int strstrlcmp(const char *s1,size_t s1_len, const char *s2,size_t s2_len );
#define ARRAYSIZE(a) (sizeof(a)/sizeof(*a))

typedef enum  _program_actions_enum {  NOT_SET,	 CREATE , LIST , EXTRACT,ADD , REMOVE , UPDATE } program_actions_emum ;

#define DEFAULT_PAGE_SIZE 2048
#define DEFAULT_PAGE_SIZE_NAME "pagesize"
#define DEFAULT_BASE_ADDRESS 0x10000000
#define DEFAULT_RAMDISK_ADDRESS 0x01000000+DEFAULT_BASE_ADDRESS
#define DEFAULT_KERNEL_ADDRESS 0x00008000+DEFAULT_BASE_ADDRESS
#define DEFAULT_SECOND_ADDRESS 0x00f00000+DEFAULT_BASE_ADDRESS
#define DEFAULT_TAGS_ADDRESS 0x00000100+DEFAULT_BASE_ADDRESS
#define DEFAULT_RAMDISK_NAME "ramdisk"
#define DEFAULT_RAMDISK_NAME_LENGTH 7
#define DEFAULT_RAMDISK_DIRECTORY_NAME "root"
#define DEFAULT_RAMDISK_DIRECTORY_NAME_LENGTH 4
#define DEFAULT_RAMDISK_CPIO_NAME "initramfs.cpio"
#define DEFAULT_RAMDISK_CPIO_GZIP_NAME "initramfs.cpio.gz"
#define DEFAULT_RAMDISK_CPIO_LZOP_NAME "initramfs.cpio.lzo"
#define DEFAULT_KERNEL_NAME "kernel"
#define DEFAULT_KERNEL_NAME_LENGTH 6
#define DEFAULT_SECOND_NAME "second"
#define DEFAULT_OUTPUT_DIRECTORY_NAME "."
#define DEFAULT_LOG_NAME "log"

typedef struct {
	char *image_filename ;
	char *kernel_filename;
	char *ramdisk_name;
	char *ramdisk_directory_name;
	char *ramdisk_cpio_filename;
	char *ramdisk_archive_filename;
	char *page_size_filename;
	char *header_filename;
	char *second_filename;
	char *cmdline_filename;
	char *output_directory_name;
	char *board_filename;
	char *target_filename;
	char *source_filename;
	char *file_list;
	int file_list_count;
	char *log_filename;
	char *cmdline_text;
	char *board_name;
	int page_size;
	int base_address;
	int list_ramdisk;
	int list_extended;
	int log_stdout;
	program_actions_emum action;
} optionvalues_t ;
optionvalues_t option_values;

// Specified the switches that are allow for each action type
// Most Switches have the same meaning between action types
typedef enum  _argument_type_enum { 
		NULL_ARG, NO_ARG=1, REQ_INT_ARG, DEF_INT_ARG, OPT_INT_ARG, 
		REQ_STR_ARG, OPT_STR_ARG, DEF_STR_ARG } argument_type_enum ;

typedef struct _opt {
		argument_type_enum argument_type;
		const char* long_name;
		const char* short_char;
		char* default_string;
		int default_value;
		void * dest_ptr;
		int (*parser_function_p)();
} command_line_switch_t ;

typedef command_line_switch_t* command_line_switches_p ;

static command_line_switch_t extract_switches[]={ 
	 { REQ_STR_ARG, "boot-image","i",NULL,0,&option_values.image_filename,0},
	 { DEF_STR_ARG, "ramdisk-cpio","C",DEFAULT_RAMDISK_CPIO_NAME,0,&option_values.ramdisk_cpio_filename,0},
	 { DEF_STR_ARG, "ramdisk-archive","x",DEFAULT_RAMDISK_CPIO_GZIP_NAME,0,&option_values.ramdisk_archive_filename,0},
	 { DEF_STR_ARG, "ramdisk-directory","d",DEFAULT_RAMDISK_DIRECTORY_NAME,0,&option_values.ramdisk_directory_name,0},
	 { DEF_STR_ARG, "kernel","k",DEFAULT_KERNEL_NAME,0,&option_values.kernel_filename,0},
	 { DEF_STR_ARG, "cmdline","c",DEFAULT_CMDLINE_NAME,0,&option_values.cmdline_filename,0},
	 { DEF_STR_ARG, "name","n",DEFAULT_BOARD_NAME,0,&option_values.board_filename,0},
	 { DEF_STR_ARG, "header","h",DEFAULT_HEADER_NAME,0,&option_values.header_filename,0},
	 { DEF_STR_ARG, "second","S",DEFAULT_SECOND_NAME,0,&option_values.second_filename,0},
	 { DEF_STR_ARG, "pagesize","p",DEFAULT_PAGESIZE_NAME,0,&option_values.page_size_filename,0},
	 { DEF_STR_ARG, "output-directory","o",DEFAULT_OUTPUT_DIRECTORY_NAME,0,&option_values.output_directory_name,0},
	 { REQ_STR_ARG, "source","s",NULL,0,&option_values.source_filename,0},
	 { REQ_STR_ARG, "files","f",NULL,0,&option_values.file_list,0},
	 { REQ_STR_ARG, "target","t",NULL,0,&option_values.target_filename,0},
	 { NULL_ARG, 0, 0, 0, 0,0,0}
};
static command_line_switch_t create_switches[]={ 
	 { REQ_STR_ARG, "boot-image","i",NULL,0,&option_values.image_filename,0},
	 { DEF_STR_ARG, "ramdisk-cpio","C",DEFAULT_RAMDISK_CPIO_NAME,0,&option_values.ramdisk_cpio_filename,0},
	 { DEF_STR_ARG, "ramdisk-archive","x",DEFAULT_RAMDISK_CPIO_GZIP_NAME,0,&option_values.ramdisk_archive_filename,0},
	 { DEF_STR_ARG, "ramdisk-directory","d",DEFAULT_RAMDISK_DIRECTORY_NAME,0,&option_values.ramdisk_directory_name,0},
	 { DEF_STR_ARG, "kernel","k",DEFAULT_KERNEL_NAME,0,&option_values.kernel_filename,0},
	 { DEF_STR_ARG, "cmdline","c",DEFAULT_CMDLINE_NAME,0,&option_values.cmdline_filename,0},
	 { REQ_STR_ARG, "name","n",NULL,0,&option_values.board_name,0},
	 { DEF_STR_ARG, "board-filename","B",DEFAULT_BOARD_NAME,0,&option_values.board_filename,0},
	 { DEF_STR_ARG, "header","h",DEFAULT_HEADER_NAME,0,&option_values.header_filename,0},
	 { DEF_STR_ARG, "second","S",DEFAULT_SECOND_NAME,0,&option_values.second_filename,0},
	 { DEF_STR_ARG, "pagesize","p",DEFAULT_PAGESIZE_NAME,0,&option_values.page_size_filename,0},
	 { DEF_STR_ARG, "output-directory","o",DEFAULT_OUTPUT_DIRECTORY_NAME,0,&option_values.output_directory_name,0},
	 { DEF_INT_ARG, "base-address","b",NULL,DEFAULT_BASE_ADDRESS,&option_values.base_address,0},
	 { NULL_ARG, 0, 0, 0, 0,0,0}
};
static command_line_switch_t list_switches[]={ 
	 { REQ_STR_ARG, "boot-image","i",NULL,0,&option_values.image_filename,0},
	 { REQ_INT_ARG, "ramdisk","l",NULL,0,NULL,&option_values.list_ramdisk},
	 { NULL_ARG, 0, 0, 0, 0,0,0}
};
static command_line_switch_t update_switches[]={ 
	 { REQ_STR_ARG, "boot-image","i",NULL,0,&option_values.image_filename,0},
	 { REQ_STR_ARG, "source","s",NULL,0,&option_values.source_filename,0},
	 { REQ_STR_ARG, "target","t",NULL,0,&option_values.target_filename,0},
	 { DEF_STR_ARG, "kernel","k",DEFAULT_KERNEL_NAME,0,&option_values.kernel_filename,0},
	 { DEF_STR_ARG, "ramdisk-cpio","C",DEFAULT_RAMDISK_CPIO_NAME,0,&option_values.ramdisk_cpio_filename,0},
	 { DEF_STR_ARG, "ramdisk-archive","x",DEFAULT_RAMDISK_CPIO_GZIP_NAME,0,&option_values.ramdisk_archive_filename,0},
	 { DEF_STR_ARG, "ramdisk-directory","d",DEFAULT_RAMDISK_DIRECTORY_NAME,0,&option_values.ramdisk_directory_name,0},
	 { DEF_STR_ARG, "name","n",DEFAULT_BOARD_NAME,0,&option_values.board_filename,0},
	 { DEF_STR_ARG, "cmdline","c",DEFAULT_CMDLINE_NAME,0,&option_values.cmdline_filename,0},
	 { REQ_STR_ARG, "files","f",NULL,0,&option_values.file_list,0},
	 { NULL_ARG, 0, 0, 0, 0,0,0}
};



typedef struct _program_options_t  {
	command_line_switches_p command_line_switches;
	program_actions_emum action ;
	int (*action_function_p)();
	int (*help_function_p)();
} program_options_t; 
	
		
static program_options_t program_options[] ={
		{NULL,NOT_SET,NULL,NULL},
		{create_switches,	CREATE ,create_boot_image_file,help_create},		 
		{list_switches,LIST ,list_boot_image_info,help_list},
		{extract_switches,EXTRACT,extract_boot_image_file ,help_extract},
		{NULL,ADD ,NULL,help_add},
		{NULL,REMOVE ,NULL,help_remove },
		{update_switches,UPDATE ,update_boot_image_file,help_update}
};
typedef  program_options_t* program_options_p;


#define ACTION_EXTRACT (option_values.action==EXTRACT )
#define ACTION_PACK (option_values.action==CREATE )
#define ACTION_LIST (option_values.action==LIST )
#define ACTION_ADD (option_values.action==ADD )
#define ACTION_REMOVE (option_values.action==REMOVE )
#define ACTION_UPDATE (option_values.action==UPDATE )
	

#define MEMORY_BUFFER_SIZE (const size_t)8192*1024

#endif



