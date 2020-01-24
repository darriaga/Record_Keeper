# include "recordKeeper.h"


int ut_isEarlierTime(struct Timestamp *t1, struct Timestamp *t2)
{
    struct Timestamp *t_stmps[2] = {t1, t2};
    int hours[2] = {t1->hour, t2->hour};
    
    int i;
    for(i = 0; i < 2; i++){
        if(t_stmps[i]->format == 'a' && hours[i] == 12) hours[i] = 0;
        else if(t_stmps[i]->format == 'p' && hours[i] != 12) hours[i] += 12;
    }
    if(hours[0] < hours[1]){
        return 1;
    }
    else if(hours[0] > hours[1]){
        return 0;
    }
    else if(hours[0] == hours[1]){
        if(t1->minute < t2->minute)
            return 1;
        else{
            return 0;
        }
    }
}

/**
 * Function parseArguments() will take in the command line arguments
 * and return the full path of the file to be interpreted assuming the
 * user passes in a valid path. If none is provided, a default timesheet
 * with sample data is used.
 * 
 * parameters: 
 *  int argc : count of arguments
 *  char * argv[] : list of arguments
 * 
 * returns: char * to string containing the full path of the timesheet.
 **/
char * ut_parseArguments(int argc, char * argv[])
{
    if(argc == 1)
    {
        return DEFAULT_INPUT;
    }
    else if (argc == 2)
    {
        return argv[1];
    }
    else if (argc > 2)
    {
        printf("Too many arguments\n");
        return NULL;
    }
    else 
    {
        printf("Input error\n");
        return NULL;
    }
}

char * ut_formatToString(char format)
{
    if(format == 'a')
        return "am";
    else if(format == 'p')
        return "pm";
    else if(format == 'i')
        return "";
}

int ut_isEmptyRecord(Record * record){
	return !record;
}
    
