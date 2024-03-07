#include <stdio.h>

#define SIZE 3

typedef struct Student
{
	int studentID;
	int total_score;
} Student;

void init(Student *students);
void update(Student *students, Student student);

int main()
{
	Student topThree[SIZE], student;
	int n, i, prog, progLab, calculus;

	init(topThree);

	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &student.studentID); 
		scanf("%d", &prog);
		scanf("%d", &progLab);
		scanf("%d", &calculus);
		student.total_score = prog + progLab + calculus;

		update(topThree, student);
	}
	
	// Display top three students
	for (i = 0; i < SIZE; i++)
	{
		printf("%d\n", topThree[i].studentID);
	}
}

void init(Student *students)
{
        int i;
        for (i = 0; i < SIZE; i++)
        {
                students[i].studentID = 0;
                students[i].total_score = 0;
        }
}

void update(Student *students, Student student)
{
	int i;
	Student temp;

	for (i = 0; i < SIZE; i++)
	{
		if (students[i].total_score < student.total_score)
		{
			temp.studentID = students[i].studentID;
			temp.total_score = students[i].total_score;

			students[i].studentID = student.studentID;
			students[i].total_score = student.total_score;

			student.studentID = temp.studentID;
			student.total_score = temp.total_score;

		}
	}
}

