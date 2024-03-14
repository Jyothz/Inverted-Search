/*
NAME : JYOTHISH B CHANDRAN
DATE : 07/12/2023
DESCRIPTION : INVERTED SEARCH PROJECT
SAMPLE INPUT : //file name
SAMPLE OUTPUT : //search word in the file
 */

#include "inverted_search.h"

int flag=0;

int main(int argc,char **argv)
{
    //required variables
    int option,status,create_check=0;
    char search_w[25],fname[25];
    //file name LL head
    f_arg *head_fname = NULL;

    //main table // array of pointers
    word_l *word[26] = {NULL};



    while(1)
    {
	printf("SELECT ANY\n1.Create Database\n2.Display Datbase\n3.Search Word\n4.Update Database\n5.Save Database\n6.Exit\n");
	scanf("%d",&option);
	switch(option)
	{
	    case 1:
		//validate and create file name LL
		status = read_and_validate(argv,&head_fname);
		if(status == FAILURE)
		{
		    printf("Error : No file input found\n");
		    //return 1;
		}
		else
		    printf("Validation Success\n");
		if(flag)
		{
		    status = create_DB(word,head_fname);
		    if(status == SUCCESS)
		    {
			create_check = 1;
			printf("INFO : Database Created Successfully\n");
		    }
		    else
		    {
			printf("ERROR : Creating Database\n");
		    }
		}
		else
		{
		    printf("File already added to Database\n");
		}

		break;


	    case 2:
		//Display database
		status = display_DB(word);
		if(status == FILE_EMPTY)
		    printf("INFO : Database Empty\n");

		break;
	    case 3 :
		//Search database
		printf("Enter the word to search : ");
		scanf("%s",search_w);
		status = search_DB(word,search_w);
		if(status == FAILURE)
		    printf("ERROR : Searching Database\n");
		else if(status == DATA_NOT_FOUND)
		    printf("INFO :  No such match found\n");
		break;
	    case 4 :
		//update database
		if(!create_check)
		{
		    printf("Enter the file name to update data : ");
		    scanf("%s",fname);
		    status = update_DB(word,fname,&head_fname);
		    if(status == SUCCESS)
			printf("INFO : Database updated successfully\n");
		    else
			printf("ERROR : Updating database\n");
		}
		else
		{
		    printf("ERROR : Cannot Update Database after Create Database\n");
		}
		break;
	    case 5 :
		//save database
		printf("Enter the file name to save : ");
		scanf("%s",fname);

		status = save_DB(word,fname);
		if(status == FAILURE)
		    printf("ERROR : Saving Database\n");
		else
		    printf("INFO : Database saved Successfully\n");

		break;
	    case 6:
		//exit
		return 0;
	    default :
		//default case
		printf("Enter proper choice\n");
	}

    }
    return 0;
}

Status read_and_validate(char **argv,f_arg **head_fname)
{
    int i=1;

    while(argv[i] != NULL)
    {
	if(strstr(argv[i],".txt"))
	{
	    //create file name node
	    f_arg *new = malloc(sizeof(f_arg));
	    if(!new)
		return FAILURE;

	    strcpy(new->file, argv[i]);
	    new->f_arg_link = NULL;

	    if(!(*head_fname))
	    {
		(*head_fname) = new;
		flag=1;
	    }
	    else
	    {
		f_arg *temp = (*head_fname),*temp2;
		while(temp != NULL)
		{
		    temp2 = temp;
		    if(!strcmp(temp->file, new->file))
		    {
			printf("INFO : Duplicate file found '%s'\n",argv[i]);
			break;
		    }
		    temp = temp->f_arg_link;
		}

		if(!temp)
		{
		    temp2->f_arg_link = new;
		    flag=1;
		}
	    }
	}else
	{
	    printf("INFO : File '%s' is not a .txt file\n",argv[i]);
	}
	i++;
    }

    if(!flag)
	return FAILURE;

    return SUCCESS;
}
