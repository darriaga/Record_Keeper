# include "recordKeeper.h"

rStack record_stack[MAX_STACK_COUNT] = {};
int stack_member_count;
struct Timestamp * timestamp_stack = NULL;

const char * std_field_separators[] = {":" , " " , "," , ":" , " " , ""};
const char * iso_field_separators[] = {" " , ":" , "," , " " , ":", ""};

Record * rec_createRecord(char * buffer)
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

int rec_populateRecord(Record * record, char * buffer)
{
    if(buffer == NULL || strlen(buffer) < 1)
        return 1;
    
    struct Timestamp * timeA;
    struct Timestamp * timeB;
    
    char * token;
    
    int fmtcheck = fs_getEntryFormat(buffer);
    
    if(fmtcheck == ISO_FORMAT)
    {
        timeA = (struct Timestamp *)malloc(sizeof(struct Timestamp));
        timeB = (struct Timestamp *)malloc(sizeof(struct Timestamp));
               
        int i_fieldsep;
        for(i_fieldsep = 0; i_fieldsep < 6; i_fieldsep++)
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

Record * rec_allocateRecord()
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

struct Timestamp * rec_allocateTimestamp()
{
    struct Timestamp * time = NULL;
}

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
	printf("added %x\n", &record_stack[stack_member_count].record);
	stack_member_count++;
	return 0;	
}