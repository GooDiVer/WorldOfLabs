#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
/*111111111111111111111111111111111111111111111111111*/
	printf("Enter the dimension of the array (m > 3, n > 4): ");
	int m,n;
    scanf("%d %d",&m,&n);
	if(m < 4 || n < 5)
	{
		printf("\nIncorrect dimension!");
		return 1;
	}

	
    int **arr;
	arr =  (int**)malloc(m*sizeof(int*));
    int i,j;

    /* get it full */
	
    for ( i = 0; i < m; i++) 
	{
		arr[i] = (int*)malloc(n*sizeof(int));	
        for (j = 0; j < n; j++)
			arr[i][j] = rand() % 10;
	}

    for ( i = 0; i < m; i++) 
	{
        for (j = 0; j < n; j++)
		{
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
	
	
/*222222222222222222222222222222222222222222222222*/	
	/* Changing place */
    for( j = 0; j < n; j++) 
	{
        int tmp = arr[0][j];
        arr[0][j] = arr[m - 1][j];
        arr[m - 1][j] = tmp;
    }
	
	/*turning it by foot-head*/
    for ( i = 0; i < n/2; i++) 
	{
        int tmp;
        tmp = arr[0][i];
        arr[0][i] = arr[0][n - 1 - i];
        arr[0][n - 1 - i] = tmp;

        tmp = arr[m - 1][i];
        arr[m - 1][i] = arr[m - 1][n - 1 - i];
        arr[m - 1][n - 1 - i] = tmp;

    }

/*3333333333333333333333333333333333333333333333333333333333333333*/
	int ci,cj;
	int min = arr[ ci = 0][ cj = 0];

	/*looking for ROW and COLUMN where is minimum element*/
	for (i = 0; i < m; i++) 
	{
		for (j = 0; j < n; j++) 
		{
			if (arr[i][j] < min) 
			{
				min = arr[i][j];
				ci = i;
				cj = j;
			}
		}
	}
	
	/*declare massive where is no COLUMN and ROW with minimum value*/
	int newArr[m-1][n-1];
	
	/*index of ROW and COlUMN in newArr*/
	int newI,newJ;
	newI = newJ = 0;
	
	
	/*Copying cutted arr into newArr*/
	for (i = 0; i < m; i++) 
	{
		/*Ignore row with min*/
		if (i != ci) 
		{
			newJ = 0;
			for (j = 0; j < n; j++) 
			{
				/*Ignore column with min*/
				if (j != cj)
				{
					newArr[newI][newJ] = arr[i][j];
					newJ++;
				}
			}
			newI++;
		}
	}
	
	/*freeing memory*/
	for( i = 0; i < n; i++) 
		free(arr[i]);
	free(arr);

    printf("\n");

	/*we output the obtained matrix*/
	printf("A = \n");
    for ( i = 0; i < m - 1; i++) {
        for (j = 0; j < n - 1; j++){
            printf("%d ",newArr[i][j]);
        }
        printf("\n");
    }
	printf("\n");

/*444444444444444444444444444444444444444444444444444444444444444*/
	char c;
	int sum = 0;
	int msize = 0;
	int nsize = 0;
	int **a;

	a = (int**)malloc(1000 * sizeof(int*));
	a[msize] = (int*)malloc(1000 * sizeof(int*));

	printf("Enter array B manually (\" \" - end of element, \"%c\" - end of a line, \"%c\" - end of an array input):\n", ',','.');
	while ((c = getchar()) != '.' && c != EOF) 
	{
		if(isdigit(c)) 
			sum = sum*10 + c - '0';
		else if (c == ' ')            /*end of element*/ 
		{	
			a[msize][nsize++] = sum;
			sum = 0;
		}

		else if (c == ',')            /*end of row (allocating memory for the next row)*/
		{
			nsize = 0;
			msize++;
			a[msize] = (int*)malloc(1000*sizeof(int));
		}
	}

	msize++; /*number of rows*/
	printf("\n");
	
	
/*5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555*/	
	int **prArr = (int**)malloc(msize*sizeof(int*));
	for(i = 0; i < msize; i++) 
		prArr[i] = (int*)malloc((n - 1)*sizeof(int));
	
	int k;
	
	if (nsize == (m - 1))
	{
		for (i = 0; i < msize; i++)
		{
			for( k = 0; k < n - 1; k++)
			{
				for(j = 0; j < nsize; j++)
					sum += a[i][j]*newArr[j][k];
				prArr[i][k] = sum;
				sum = 0;
			}
		}
		
		printf("B * A = \n");
		for(i = 0; i < msize; i++)
		{
			for(j = 0; j < n - 1; j++)
				printf("%d ", prArr[i][j]);
			printf("\n");
		}		
	}
	else 
	{
		printf("Impossible operation!");
	}
	

	
	
	/*freeing of memory from (a) and (prArr) array*/
	for (i = 0; i < msize; i++)
	{
		/*count of row in "a" = count of row in "prArr"*/
		free(a[i]);	
		free(prArr[i]);
	}
	free(a);
	free(prArr);
	
	return 0;
}
