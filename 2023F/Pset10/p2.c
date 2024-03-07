#include <stdio.h>

typedef struct Point
{
	float x, y;

} Point;

typedef struct Line
{
	Point point;
	float slope;
} Line;

int main()
{
	Point p;
	Line l;

	scanf("%f, %f, %f", &l.point.x, &l.point.y, &l.slope);
	scanf("%f, %f", &p.x, &p.y);

	if (p.x != 0 && p.y / p.x == l.slope || p.x == 0 && p.y == 0 && l.slope == 1)
		printf("Yes");
	else
		printf("No");

	return 0;
}
