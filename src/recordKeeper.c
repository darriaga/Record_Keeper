
# include "recordKeeper.h"

Record *root_record = NULL;
unsigned int g_recordcount = 0;

int main(int argc, char * argv[])
{
    char * filename;
    
    filename = ut_parseArguments(argc, argv);
    
    if(filename != NULL)
    {
        if(fs_startInputStream(filename))
        {
            fprintf(stderr, "Error: could not open file\n");
            return 0;
        }
        if(rck_generateRecords())
        {
            fprintf(stderr, "Error: could not generate records\n");
            return 0;
        }
    }
    else
    {
        fprintf(stderr, "Invalid input path");
    }
    
    fs_closeInputStream();
    rec_freeRecords();
}

int rck_generateRecords()
{
    FILE *time_chart = fs_getStream();
    char buffer[MAX_RECORD_INPUT];
    
    while(fgets(buffer, sizeof(buffer), time_chart))
    {
        Record * record = rec_createRecord(buffer); 
        if(record == NULL)
        {
            fprintf(stderr, "Could not create record\n");
            return 1;
        }
        else if(buffer == "")
            return 0;
        else
        {
            g_recordcount++;
            record->id = g_recordcount;
        }
        
        rck_displayRecordStats(record);

        
        if(rck_insertRecord(record))
        {
            fprintf(stderr, "Could not insert record\n");
        }
    }
    
    if(rck_traverseRecordsForDisplay(root_record, root_record)){
        printf("Error: Could not display all later records\n");
        return 1;
    }
    
    return 0;
}

int rck_insertRecord(Record *record)
{
    record->next = root_record;
    root_record = record;
    
    if(root_record == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int rck_traverseRecordsForDisplay(Record *const_root, Record *var_root)
{
    if(var_root == NULL)
        return 0;
    if(rck_displayRecord(var_root)){
        fprintf(stderr, "Error: Could not display record\n");
        return 1;
    }
    if(rck_displayLaterRecords(const_root, var_root)){
        fprintf(stderr, "Error: Could not display later times");
        return 1;
    }
    rck_traverseRecordsForDisplay(const_root, var_root->next);
    return 0;
}

int rck_displayLaterRecords(Record * root, Record * rec)
{
    if(root == NULL)
        return 0;
    if(root->id != rec->id){
        if(ut_isEarlierTime(rec->timeB, root->timeB))
            printf("rec_num: %03d timeA %02d:%02d %2s is later than rec_num: %03d timeB %02d:%02d %s\n", 
                   root->id, root->timeB->hour, root->timeB->minute, ut_formatToString(root->timeB->format),
                   rec->id, rec->timeB->hour, rec->timeB->minute, ut_formatToString(rec->timeB->format));
            
        if(ut_isEarlierTime(rec->timeB, root->timeA))
            printf("rec_num: %03d timeA %02d:%02d %2s is later than rec_num: %03d timeB %02d:%02d %s\n", 
                   root->id, root->timeA->hour, root->timeA->minute, ut_formatToString(root->timeA->format),
                   rec->id, rec->timeB->hour, rec->timeB->minute, ut_formatToString(rec->timeB->format));
            
        if(ut_isEarlierTime(rec->timeA, root->timeB))
            printf("rec_num: %03d timeB %02d:%02d %2s is later than rec_num: %03d timeA %02d:%02d %s\n", 
                   root->id, root->timeB->hour, root->timeB->minute, ut_formatToString(root->timeB->format),
                   rec->id, rec->timeA->hour, rec->timeA->minute, ut_formatToString(rec->timeA->format));
            
        if(ut_isEarlierTime(rec->timeA, root->timeA))
            printf("rec_num: %03d timeA %02d:%02d %2s is later than rec_num: %03d timeA %02d:%02d %s\n", 
                   root->id, root->timeA->hour, root->timeA->minute, ut_formatToString(root->timeA->format),
                   rec->id, rec->timeA->hour, rec->timeA->minute, ut_formatToString(rec->timeA->format));
    }
    rck_displayLaterRecords(root->next, rec);
    return 0;
}

int rck_displayRecordStats(Record * record)
{
     if(record == NULL){
        fprintf(stderr, "Error: No record to display.\n");
        return 1;
    }
    
    rck_displayRecord(record);
    
    if(ut_isEarlierTime(record->timeA, record->timeB)){
        fprintf(stdout, "Result 'Time A is earlier than Time B'\n\n");
    } else {
        fprintf(stdout, "Result 'Time B is earlier than Time A'\n\n");
    }
}

int rck_displayRecord(Record *record)
{
    if(record == NULL){
        printf("Error: No record to display.\n");
        return 1;
    }
    fprintf(stdout, "---------------------------------\n");
    fprintf(stdout, "|%03d|    %02d:%02d %2s %2s  %02d:%02d %2s  |\n",
            record->id, record->timeA->hour, record->timeA->minute, ut_formatToString(record->timeA->format),"|",
            record->timeB->hour, record->timeB->minute, ut_formatToString(record->timeB->format));
    fprintf(stdout, "---------------------------------\n");
    
    return 0;
}
