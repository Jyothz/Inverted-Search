/*

NAME : JYOTHISH B CHANDRAN
DATE :
DESCRIPTION :
SAMPLE INPUT :
SAMPLE OUTPUT :
 */

#include "inverted_search.h"

Status update_DB(word_l *word[26], char *update_fname,f_arg **head_fname)
{
    int status;
    FILE *fptr;
    status = validate_and_open_update(update_fname,&fptr);
    if(status == FAILURE)
	return FAILURE;
    else if(status == FILE_EMPTY)
    {
	printf("The file %s is empty\n",update_fname);
	return FILE_EMPTY;
    }

    rewind(fptr);
    char *buff = NULL;
    size_t size=0;
    while(getline(&buff,&size,fptr) != -1)
    {
	char *token = strtok(buff,"#:");
	int number = atoi(token);

	token = strtok(NULL,"#:");
	//word
	word_l *new_w = NULL;
	create_word_node(&new_w,token);

	//file count
	token = strtok(NULL,"#:");
	new_w->file_count = atoi(token);

	//link the new word node
	if(word[number] == NULL)
	    word[number] = new_w;
	else
	{
	    word_l *temp_w = word[number];
	    while(temp_w->word_link != NULL)
	    {
		temp_w = temp_w->word_link;
	    }
	    temp_w->word_link = new_w;
	}

	//file node creation
	int count = 1;
	while(count <= new_w->file_count)
	{
	    //file name
	    token = strtok(NULL,"#:");

	    //add file name to file name linked list
	    if(!(*head_fname))
	    {
		f_arg *new_arg = malloc(sizeof(f_arg));
		strcpy(new_arg->file,token);
		new_arg->f_arg_link = NULL;
		(*head_fname) = new_arg;
	    }
	    //else check for file in Linked list
	    else
	    {
		f_arg *temp_arg = (*head_fname),*temp2_arg=NULL;
		while(temp_arg && strcmp(temp_arg->file,token))
		{
		    temp2_arg = temp_arg;
		    temp_arg = temp_arg->f_arg_link;
		}

		//if LL reaches null then dont add file to LL
		if(!temp_arg)
		{
		    f_arg *new_arg = malloc(sizeof(f_arg));
		    strcpy(new_arg->file,token);
		    new_arg->f_arg_link = NULL;
		    temp2_arg->f_arg_link = new_arg;
		}
		//else file already in LL so continue
	    }
	    //create node
	    f_name *new_f = NULL;
	    create_file_node(&new_f,token);

	    //word count in  file
	    token = strtok(NULL,"#:");
	    new_f->word_count = atoi(token);

	    //link to word  node/file node
	    if(new_w->f_link == NULL)
		new_w->f_link = new_f;
	    else
	    {
		f_name *temp_f = new_w->f_link;
		while(temp_f->file_link)
		{
		    temp_f = temp_f->file_link;
		}

		temp_f->file_link = new_f;
	    }

	    count++;
	}
    }

    return SUCCESS;
}

Status validate_and_open_update(char *update_fname,FILE **fptr)
{
    if(!strstr(update_fname,".txt"))
    {
	printf("Please provide .txt file\n");
	return FAILURE;
    }

    //open file 

    (*fptr) = fopen(update_fname,"r");
    if(!(*fptr))
    {
	printf("ERROR : File doesn't exist\n");
	return FAILURE;
    }

    rewind((*fptr));

    if(fgetc((*fptr))== EOF)
    {
	printf("The file %s is Empty\n",update_fname);
	return FILE_EMPTY;
    }


}
