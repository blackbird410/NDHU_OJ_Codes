#include <stdio.h>

#define SIZE 1000

typedef struct Course {
	int sid[SIZE];
	int student_id[SIZE];
	int course_id[SIZE];
	int total_score[SIZE];
	int n_courses[SIZE];
} Course;

int inputCourses(Course *courses, int m);
void inputScores(Course *courses, int n);
int countFailed(Course *courses, int m);

void init(Course *courses)
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		courses->total_score[i] = 0;
		courses->n_courses[i] = 0;
	}
}

int main()
{
	int m, n, n_students, failed;
	Course courses;

	scanf("%d %d", &m, &n);
	
	init(&courses);
	n_students = inputCourses(&courses, m);
	inputScores(&courses, n);
	failed  = countFailed(&courses, m);
	printf("%d %d", n_students, failed);

	return 0;
}

int inputCourses(Course *courses, int m)
{
	int i, j, n_students = 0;
	for (i = 0; i < m; i++)
	{
		scanf("%d %d %d", &courses->sid[i], &courses->student_id[i], &courses->course_id[i]);
		n_students++;

		// Check if not already counted
		for(j = 0; j < i-1; j++)
		{
			if (courses->student_id[j] == courses->student_id[i])
			{
				n_students--;
				break;
			}
		}
	}

	return n_students;
}

int countFailed(Course *courses, int m)
{
	int i, count = 0;
	double avgScore = 0;

	for (i = 0; i < m; ++i)
	{
		avgScore = courses->total_score[i] / (double) courses->n_courses[i];
		count = (avgScore < 60.0)? count + 1: count;
	}

	return count;
}

void inputScores(Course *courses, int n)
{
	int i, sid, score;

	for (i = 0; i < n; i++)
	{
		scanf("%d %d", &sid, &score);
		courses->total_score[sid] += score;
		courses->n_courses[sid]++;
	}
}
