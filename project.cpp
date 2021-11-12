# include<stdio.h>
# include<stdlib.h>
# include<string.h>
void insert_record();
void del_record();
void update_record();
void search_record();
void display_record();
void sort_record();

struct student{
	int roll_no;
	char name[40];
	char sec[10];
	char grade;
	double percentage;
	double marks;
};

struct student stud;
  
int main()
{
	int ch;
	while(ch!=7)
	{
		printf("\t_________________________\n");
		printf("Welcome to Student Management Portal\t");
		printf("\t_________________________\n");
		
		printf("\t Available Functions\n");
		printf("\t\t 1: Insert Student Record\n");
		printf("\t\t 2: Display Student Record\n");
		printf("\t\t 3: Search Student Record\n");
		printf("\t\t 4: Delete Student Record\n");
		printf("\t\t 5: Update Student Record\n");
		printf("\t\t 6: Sort Student Record\n");
		printf("\t\t 7: Exit\n\n");
		printf("Enter your Choice:\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: 
				insert_record();
				break;
			case 2:
				display_record();
				break;
			case 3:
				search_record();
				break;
			case 4: 
				del_record();
				break;
			case 5:
				update_record();
				break;
			case 6:
				sort_record();
				break;
			case 7:
				exit(1);
			default:
				printf("Enter a Valid Choice between 1 to 7");
		}
		printf("Press any key to continue");
		return 0;
	}
	return 0;
}
void insert_record()
{
	FILE *fstud=fopen("students.txt","ab+");
	/*fstud --> pointer*/
	
	/*ab+ --> append binary file, it will appen data into
	 the file if it's already created or else it will 
	 create a new one and append the values to it.*/
	if(fstud==NULL)
	{
		printf("Error cannot open file! File does not exists");
		return ;
	}
	printf("----Previous Record----");
	display_record();
	printf("----Enter new Student Record----");
	
	printf("Enter student roll number: ");
	scanf("%d",&stud.roll_no);
	fflush(stdin); 
	/*fflush cleares out the buffer 
	so there is enough space to enter
	new values */

	/*we are using %d or %f for 
	integer type and decimal type values*/

    /*for string */
	printf("Enter student name: ");
	fgets(stud.name,40,stdin);
	
	printf("Enter Student Section:");
	fgets(stud.sec,10,stdin);
	
	printf("Enter Student Total Marks:");
	scanf("%f",&stud.marks);
	
	printf("Enter Student Grade:");
	scanf("%c",&stud.grade);
	
	printf("Enter Student Percentage:");
	scanf("%f",&stud.percentage); 
	/*fwrite function will write into the file*/
	fwrite(&stud,sizeof(stud),1,fstud);
	/*here 1 means the number of times you want to update the file*/
	{
		printf("Student Record Inserted Successfully");
	}
	fclose(fstud);
	printf("Updated Record");
	display_record();
}
void display_record()
{
	FILE *fstud=fopen("students.txt","rb");
	if(fstud==NULL)
	{
		printf("Error! File does not Exist");
		return ;
	}
	printf("-------Student Details-------");
	printf("Roll Number\t Name\t Section\t Marks\t Grade\t Percentage\t");
	while(fread(&stud,sizeof(stud),1,fstud)==1)
	{
		printf("%d\t%s\t%s\t%f\t%c\t%f\t",stud.roll_no,stud.name,stud.sec,stud.marks,stud.grade,stud.percentage);		
	}
	fclose(fstud);
}	
void search_record()
{	
	int roll,flag=0;
	FILE *fstud=fopen("students.txt","rb+");
	if(fstud==NULL)
	{
		printf("ERROR! File does not Exist");
		return;
	}
	printf("Enter student Roll Number you want to search:");
	scanf("%d",&roll);
	while(fread(&stud,sizeof(stud),1,fstud)>0 &&flag==0)
	/*here 1 means the number of times you want to update the file*/
	{
		if(stud.roll_no==roll)
		{
		flag=1;
		printf("Search successfull! Student record is:");
		printf("Roll Number\t Name\t Section\t Marks\t Grade\t Percentage\t");
		printf("%d\t%s\t%s\t%f\t%c\t%f\t",stud.roll_no,stud.name,stud.sec,stud.marks,stud.grade,stud.percentage);		
		}
	}
if(flag==0)
{
	printf("No search Record");
	}	
	fclose(fstud);
}
void del_record()
{
	char name[40];
	int flag=0;
	FILE *fstud,*ftemp;
	fstud=fopen("students.txt","rb");
	if(fstud==NULL)
	{
		printf("ERROR! File does not exist");
		return;
	}
	printf("Previous Stored Data");
	display_record();
	printf("Enter Student roll no. which you want to delete");
	scanf("%d",&name);
	ftemp=fopen("students1.txt","ab+");
	while(fread(&stud,sizeof(stud),1,fstud)==1)
	{
		if(strcmp(name,stud.name)!=0)
		/*when there exists a value*/
		/*strcmp-> string compare*/
		{
			printf("Record Deleted successfully");
			fwrite(&stud,sizeof(stud),1,ftemp);
			/*ftemp file will store all the 
			  undeleted values in it*/
		}
		else
			flag=1; /*when no record exists*/
			
	}
	if(flag==0)
	{
		printf("No such Record Found");
	}
	fclose(fstud);
	fclose(ftemp);
	remove("students.txt");
	rename("students1.txt","students.txt");
	printf("Updated Record");
	display_record();		
}

void update_record()
{
	int ro,flag=0;
	FILE *fstud=fopen("students.txt","rb+");
	if(fstud==NULL)
	{
		printf("ERROR! No file exists");
		return ;
	}
	printf("Enter student roll number whose information you want to update:");
	scanf("%s",&ro);
	printf("Previous record of the student:");
	while(fread(&stud,sizeof(stud),1,fstud)>0 && flag==0)
	{
		if(stud.roll_no==ro)
		{
			flag=1;
			printf("Roll Number\t Name\t Section\t Marks\t Grade\t Percentage\t");
			printf("%d\t%s\t%s\t%f\t%c\t%f\t",stud.roll_no,stud.name,stud.sec,stud.marks,stud.grade,stud.percentage);		
			printf("---------Enter New Record---------");
			printf("Enter student roll number: ");
			scanf("%d",&stud.roll_no);
			fflush(stdin); 
			/*fflush cleares out the buffer 
			so there is enough space to enter
			new values */
	
			/*we are using %d or %f for 
			integer type and decimal type values*/
			
	    	/*for string */
			printf("Enter student name: ");
			fgets(stud.name,40,stdin);
		
			printf("Enter Student Section:");
			fgets(stud.sec,10,stdin);
			
			printf("Enter Student Total Marks:");
			scanf("%f",&stud.marks);
		
			printf("Enter Student Grade:");
			scanf("%c",&stud.grade);
		
			printf("Enter Student Percentage:");
			scanf("%f",&stud.percentage); 
			
			fseek(fstud,-(long)sizeof(stud),1);
			/*used to perform updation*/
			/*- means the data will get updated from the start*/
			fwrite(&stud,sizeof(stud),1,fstud);
			printf("Record Updated Successfully");
		}
	 }
	if(flag==0)
	{
		printf("ERROR! Something went wrong");	
	}
	fclose(fstud);
}
void sort_record()
{
	struct student temp;
	struct student arr[50];
	int i,j,k=0;
	FILE *fstud=fopen("students.txt","rb");
	if(fstud==NULL)
	{
		printf("ERROR! No file exists");
	}
	i=0;
	while(fread(&arr[i],sizeof(arr[i]),1,fstud)==1)
	{
		i++;k++;
	}
	for(i=0;i<k;i++)
	{
		for(j=0;j<k-i-1;j++)
		{
			if(arr[i].roll_no>arr[j+1].roll_no)
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
	printf("\n\t After sorting student details are:\n\n");
	for(i=0;i<k;i++)
	{
		printf("%d\t%s\t%s\t%f\t%f\t",arr[i].roll_no,arr[i].name,arr[i].grade,arr[i].percentage,arr[i].marks);
	}
}

