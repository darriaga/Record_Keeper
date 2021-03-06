/* recordKeeper.h */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <regex.h>
# include <malloc.h>

# define MAX_RECORD_INPUT  64
# define STANDARD_FORMAT   0x32
# define ISO_FORMAT        0x64
# define ISO_FMT_FIELDS    6
# define STD_FMT_FIELDS    6

# define MAX_STACK_COUNT   512
# define DEFAULT_INPUT     "../test/default.txt"

// Record struct for holding Time A and Time B
typedef struct Records 
{
    int id;
    char format;
    struct Timestamp *timeA;
    struct Timestamp *timeB;
    struct Records   *next;
} Record;

// Time stamp struct for holding scalar values of time
struct Timestamp
{
    char format;
    unsigned short int hour;
    unsigned short int minute;
};

// Stack of records for memory management
typedef struct RecordStack
{
    Record *record;
    struct RecordStack *next;
} rStack;

// functions in recordKeeper.c
int     rck_generateRecords();
int     rck_insertRecord(Record * record);
int     rck_traverseRecordsForDisplay(Record *const_root, Record *var_root);
int     rck_displayLaterRecords(Record * root, Record * rec);
int     rck_displayRecordStats(Record * record);
int     rck_displayRecord(Record *record);
Record *rck_allocateRecord();
struct Timestamp
       *rck_allocateTimestamp();
int     rck_clearList(Record * root);

// functions in record.c
Record  *rec_createRecord(char * buffer);
int      rec_populateRecord(Record * record, char * buffer);
Record  *rec_allocateRecord();
struct Timestamp 
        *rec_allocateTimestamp();
int      rec_addToRecordStack(Record * record);
int rec_freeRecords();

// functions in filestream.c
int     fs_startInputStream(char * filename);
int     fs_closeInputStream();
int     fs_getEntryFormat(char * entry);
FILE   *fs_getStream();

// functions in utils.c
int     ut_isEarlierTime(struct Timestamp *t1, struct Timestamp *t);
char   *ut_parseArguments(int argc, char * argv[]);
char   *ut_formatToString(char format);
int     ut_isEmptyRecord(Record * record);


/** TO-DO
 * - data gen program
*/
