# include "recordKeeper.h"

rStack record_stack[MAX_STACK_COUNT] = {};
int stack_member_count;
const char * std_field_separators[] = {":" , " " , "," , ":" , " " , ""};
const char * iso_field_separators[] = {" " , ":" , "," , " " , ":", ""};

/***
 * function rec_createRecord() will take in the input line buffer
 * and use the contents to create a new record.
 * 
 * parameters: char *buffer : the input line buffer
 * 
 * returns : Record pointer to new Record
 ***/
Record *rec_createRecord(char *buffer)
{
    if(buffer == NULL || strlen(buffer) < 1) {
        return NULL;
    }
    
    Record * record = rec_allocateRecord();
    
    if(rec_populateRecord(record, buffer)) {
        fprintf(stderr, "Error: Could not populate record.\n");
        return record;
    }
    
    if(record->timeA == NULL || record->timeB == NULL)
    {
        return NULL;
    }
    return record;
}

/***
 * function rec_populateRecord() will take in  a record and line 
 * buffer and process the population of the given record using the
 * buffer.
 * 
 * parameters: Record *record : the record to be populated
 *             char *buffer: buffer containting record data"
 * 
 * returns : 0 upon success, 1 on failure
 ***/
int rec_populateRecord(Record *record, char *buffer)
{
    if(buffer == NULL || strlen(buffer) < 1)
        return 1;
    
    struct Timestamp *timeA;
    struct Timestamp *timeB;
    
    char *token;
    
    int fmtcheck = fs_getEntryFormat(buffer);
    
    if(fmtcheck == ISO_FORMAT)
    {
        timeA = rec_allocateTimestamp();
        timeB = rec_allocateTimestamp();
               
        int i_fieldsep;
        for(i_fieldsep = 0; i_fieldsep < ISO_FMT_FIELDS; i_fieldsep++)
        {
            if(i_fieldsep)
            {
                token = strtok(NULL, iso_field_separators[i_fieldsep]);
            }
            switch(i_fieldsep)
            {
                case 0:
                    token = strtok(buffer, iso_field_separators[i_fieldsep]);
                    timeA->format = 'i';
                    break;
                case 1:
                    timeA->hour = atoi(token);
                    break;
                case 2:
                    timeA->minute = atoi(token);
                    break;
                case 3:
                    timeB->format = 'i';
                    break;
                case 4:                    
                    timeB->hour = atoi(token);
                    break;
                case 5:
                    timeB->minute = atoi(token);
                    break;
                default:
                    break;
            }
        }   
    }
    
    else  if(fmtcheck == STANDARD_FORMAT)
    {
        timeA = (struct Timestamp *)malloc(sizeof(struct Timestamp));
        timeB = (struct Timestamp *)malloc(sizeof(struct Timestamp));
               
        int i_fieldsep;
        for(i_fieldsep = 0; i_fieldsep < STD_FMT_FIELDS; i_fieldsep++)
        {
            if(i_fieldsep)
                token = strtok(NULL, std_field_separators[i_fieldsep]);
            
            switch(i_fieldsep)
            {
                case 0:
                    token = strtok(buffer, std_field_separators[i_fieldsep]);
                    timeA->hour = atoi(token);
                    break;
                case 1:
                    timeA->minute = atoi(token);
                    break;
                case 2:
                    timeA->format = *token;
                    break;
                case 3:
                    timeB->hour = atoi(token);
                    break;
                case 4:
                    timeB->minute = atoi(token);
                    break;
                case 5:
                    timeB->format = *token;
                    break;
                default:
                    break;
            }
        } 
    }
    
    else
    {
        fprintf(stderr, "buffer does not contain specified format\n");
        return 1;
    }
    
    record->timeA = timeA;
    record->timeB = timeB;
    
   return 0;
    
}

/***
 * function rec_allocateRecord() will allocate a new Record in memory
 * and push it to a statically declared Stack struct which we will
 * use as a way of keeping track of what we allocate dynamically.
 * 
 * returns newly allocated Record.
***/
Record *rec_allocateRecord()
{
    Record * rec = (Record *)malloc(sizeof(Record));
	rec->next = NULL;
    if(rec == NULL){
        fprintf(stderr, "Error: could not allocate record\n");
		free(rec);
        return NULL;
    }
	if(rec_addToRecordStack(rec)){
		fprintf(stderr, "Could not add record to stack\n");
		free(rec);
		return NULL;
	}
	return rec;
	
}

struct Timestamp *rec_allocateTimestamp()
{
    struct Timestamp *timestamp = (struct Timestamp *)malloc(sizeof(struct Timestamp));
    if(timestamp == NULL){
        fprintf(stderr, "Error: Could not allocate Timestamp.\n");
        free(timestamp);
        return NULL;
    }
    return timestamp;
}

/***
 * function rec_addToRecordStack() will take in a Record pointer and 
 * add it to the 'stack'.
 * 
 * parameters: Record *record : address of newly allocated Record
 * 
 * returns  0 on success 1 on failure
***/
int rec_addToRecordStack(Record * record)
{
	if(stack_member_count == 0){
		record_stack[0].record = record;
		record_stack[0].next = NULL;
	}
	else if(record_stack[stack_member_count].record == NULL){
		record_stack[stack_member_count].record = record;
		record_stack[stack_member_count].next = NULL;
		record_stack[stack_member_count - 1].next = &record_stack[stack_member_count];
	}else{
		fprintf(stderr, "Error: could not evaluate proper stack entry\n");
		return 1;
	}
	stack_member_count++;
	return 0;	
}

/***
 * function rec_freeRecords() will iteratively traverse through the
 * Record Stack and each record and its contents in memory.
 * 
 * returns 0 on success and 1 on failure.
**/
int rec_freeRecords()
{
    if(stack_member_count == 0){
		return 0;
	} else if (record_stack[0].record == NULL) {
        return 0;
    } else {
        int index;
		for(index = 0; index < stack_member_count; index++){
            free(record_stack[index].record->timeA);
            free(record_stack[index].record->timeB);
            free(record_stack[index].record);
        }
        return 0;
	}
	return 1;
}
    
