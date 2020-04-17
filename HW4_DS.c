#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int row, int col);  //행렬을 동적메모리 할당을 이용하여 2차원 배열로 만들어 주는 함수 이차원 배열을 반환
int free_matrix(int** matrix, int row, int col);//동적 메모리를 해제시켜주는 함수
void print_matrix(int** matrix, int row, int col);//2차원 배열로 만들어진 행렬을 출력해주는 함수
int fill_data(int** matrix, int row, int col);//할당된 2차원 배열(행렬)에 랜덤으로 값을 입력해주는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);  //만들어진 행렬의 전치행렬을 구하는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col);  //크기가 같은 행렬 두개를 더해주는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col);//크기가 같은 행렬 두개를 빼는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col);  //행렬과 그 행렬의 전치행렬의 곱을 구하는 함수



int main()
{
	int row, col;  //행과 열을 입력받는 함수
	int** matrix=NULL , ** matrix_t = NULL, ** matrix_a = NULL, ** matrix_b = NULL, ** matrix_sub = NULL, ** matrix_sum = NULL, ** matrix_axt = NULL;  // 이중 포인터를 선언해준다. 총 7개의 2차원 배열을 만든다.
	int i = 0;
	printf("전아현 2018068005\n\n");

	do {
		printf("행렬의 행 : ");
		fflush(stdout);
		scanf_s("%d", &row);   //행과 열을 입력받는다.

		printf("행렬의 열 : ");
		fflush(stdout);
		scanf_s("%d", &col);
		if (row <= 0 || col <= 0)       //행과 열의 수를 잘못 입력했을 경우
		{
			printf("행과 열을 다시 입력해주세요.\n");   //안내문 출력후
			continue;  //반복문의 처음으로 돌아가 행과 열을 다시 입력받는다.
		}
		matrix = create_matrix(row, col);  //행렬들을 동적으로 메모리를 할당해준다.
		matrix_t = create_matrix(col,row);  //전치행렬은 행과 열의 크기가 바뀌므로 입력받은 행과 열을 바꿔서 넘겨준다.
		matrix_a = create_matrix(row, col);
		matrix_b = create_matrix(row, col);
		matrix_sub = create_matrix(row, col);
		matrix_axt = create_matrix(row,row);  //행렬과 전치행렬의 곱은 행렬의 행* 전치행렬의 열 크기 이므로 행의 값을 넘겨준다.
		matrix_sum = create_matrix(row, col);

		if (matrix != NULL || matrix_a != NULL || matrix_b != NULL || matrix_t != NULL || matrix_sub != NULL || matrix_sum != NULL || matrix_axt != NULL)
			break;  //모든 행렬을 동적메모리 할당으로 올바르게 할당 받았다면 반복문을 종료
		else //할당에 실패했다면
		{
			printf("동적메모리 할당을 실패하였습니다.\n");  //안내문을 출력한 후
			printf("프로그램을 종료해주세요.\n");
			return 0;  //프로그램을 종료한다.
		}
	} while (1);//동적 메모리 할당이 성공할때 까지 반복문 실행


	srand((unsigned int)time NULL);  // 행렬에 난수를 설정하기 위해 rand에 사용할 수 초기화

	if (fill_data(matrix, row, col) == -1)   //fill_data 함수로 matrix, matrix_a, matrix_b 행렬을 난수로 채워준다.
	{
		printf("데이터 값을 제대로 입력받지 못했습니다.\n");  //행렬 채우기를 실패했다면 안내문을 출력한 후
		i = -1;  //i에 -1을 넣어주어 실패했다는 것을 알린다.
	}
	if (fill_data(matrix_a, row, col) == -1) {
		printf("데이터 값을 제대로 입력받지 못했습니다.\n");
		i = -1;
	}
	if (fill_data(matrix_b, row, col) == -1) {
		printf("데이터 값을 제대로 입력받지 못했습니다.\n");
		i = -1;
	}
	if (i == -1) // 난수로 행렬채우는 것을 실패했다면
	{
		if (free_matrix(matrix, row, col) == -1) //동적메모리를 이용해 할당받은 메모리를 해제한다.
			printf("1.메모리 해제를 제대로 실행하지 못했습니다.\n");// 해제가 제대로 되지 않으면 실패 안내문을 출력한다.
		else
			printf("matrix의 메모리 해제를 성공했습니다.\n");
		if (free_matrix(matrix_t, col, row) == -1)
			printf("2.메모리 해제를 제대로 실행하지 못했습니다.\n");
		else
			printf("matrix_t의 메모리 해제를 성공했습니다.\n");
		if (free_matrix(matrix_a, row, col) == -1)
			printf("3.메모리 해제를 제대로 실행하지 못했습니다.\n");
		else
			printf("matrix_a의 메모리 해제를 성공했습니다.\n");
		if (free_matrix(matrix_b, row, col) == -1)
			printf("4.메모리 해제를 제대로 실행하지 못했습니다.\n");
		else
			printf("matrix_b의 메모리 해제를 성공했습니다.\n");
		if (free_matrix(matrix_sum, row, col) == -1)
			printf("5.메모리 해제를 제대로 실행하지 못했습니다.\n");
		else
			printf("matrix_sum의 메모리 해제를 성공했습니다.\n");
		if (free_matrix(matrix_sub, row, col) == -1)
			printf("6.메모리 해제를 제대로 실행하지 못했습니다.\n");
		else
			printf("matrix_sub의 메모리 해제를 성공했습니다.\n");
		if (free_matrix(matrix_axt, row, row) == -1)
			printf("7.메모리 해제를 제대로 실행하지 못했습니다.\n");
		else
			printf("matrix_axt의 메모리 해제를 성공했습니다.\n");
		return 0; //프로그램을 종료한다.
	}

	printf("matrix 행렬\n");  //안내문 출력 후
	print_matrix(matrix, row, col);  //출력 함수를 호출하여 matrix를 출력한다.
	printf("matrix_a 행렬\n");
	print_matrix(matrix_a, row, col);//출력 함수를 호출하여 matrix_a를 출력한다.
	printf("matrix_b 행렬\n");
	print_matrix(matrix_b, row, col);//출력 함수를 호출하여 matrix_b를 출력한다.

	if (addition_matrix(matrix_a, matrix_b, matrix_sum, row, col) == -1)  //행렬을 더하는 함수를 호출 하여
		printf("행렬의 합이 실패하였습니다.\n");  //행렬의 합이 실패 하였으면 안내문 출력
	else  //성공했다면
	{	printf("matrix 합\n");  //print_matrix 함수를 호출하여 결과 출력
		print_matrix(matrix_sum, row, col);
	}

	if (subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, col) == -1)//두개의 행렬을 빼는 함수를 호출 하여
		printf("행렬의 차가 실패하였습니다.\n");  //실패하면 실패 안내문 출력
	else	{  //성공하면
		printf("matrix 차\n");
		print_matrix(matrix_sub, row, col); //print_matrix 함수를 호출하여 결과 출력
	}

	if (transpose_matrix(matrix_a, matrix_t, col,row) == -1)//행렬을 전치행렬로 바꿔주는 함수 호출하여
		printf("전치 행렬의 값이 잘못되었습니다. \n");  //실패하면 실패 안내문 출력
	else{ //성공하면
		printf("matrix 전치 행렬\n");
		print_matrix(matrix_t, col, row);  //print_matrix 함수를 호출하여 결과 출력  , 전치행렬은 행과 열의 수가 바뀐다.
	}

	if (multiply_matrix(matrix_a, matrix_t,matrix_axt, row, col) == -1)  //전치행렬과 행렬을 곱해주는 함수를 호출하여
		printf("전치행렬과 행렬의 곱이 실패하였습니다.\n");  //실패하면 실패 안내문 출력
	else  //성공하면
	{
		printf("matrix 곱\n");
		print_matrix(matrix_axt, row, row);  //print_matrix 함수를 호출하여 결과 출력  , 두 행렬을 곱하면 행렬의 크기가 달라진다.
	}


	if (free_matrix(matrix, row, col) == -1) //동적메모리를 이용해 할당받은 메모리를 해제한다.
		printf("1.메모리 해제를 제대로 실행하지 못했습니다.\n");// 해제가 제대로 되지 않으면 실패 안내문을 출력한다.
	else
		printf("matrix의 메모리 해제를 성공했습니다.\n");
	if (free_matrix(matrix_t, col, row) == -1)
		printf("2.메모리 해제를 제대로 실행하지 못했습니다.\n");
	else
		printf("matrix_t의 메모리 해제를 성공했습니다.\n");
	if (free_matrix(matrix_a, row, col) == -1)
		printf("3.메모리 해제를 제대로 실행하지 못했습니다.\n");
	else
		printf("matrix_a의 메모리 해제를 성공했습니다.\n");
	if (free_matrix(matrix_b, row, col) == -1)
		printf("4.메모리 해제를 제대로 실행하지 못했습니다.\n");
	else
		printf("matrix_b의 메모리 해제를 성공했습니다.\n");
	if (free_matrix(matrix_sum, row, col) == -1)
		printf("5.메모리 해제를 제대로 실행하지 못했습니다.\n");
	else
		printf("matrix_sum의 메모리 해제를 성공했습니다.\n");
	if (free_matrix(matrix_sub, row, col) == -1)
		printf("6.메모리 해제를 제대로 실행하지 못했습니다.\n");
	else
		printf("matrix_sub의 메모리 해제를 성공했습니다.\n");
	if (free_matrix(matrix_axt, row, row) == -1)
		printf("7.메모리 해제를 제대로 실행하지 못했습니다.\n");
	else
		printf("matrix_axt의 메모리 해제를 성공했습니다.\n");

}
int** create_matrix(int row, int col)
{
	if (row <= 0 || col <= 0) //전처리 검사  넘겨받은 인자가 잘못되었다면
	{
		printf("check pre conditions\n");  //안내문 출력 후
		return NULL;  //NULL값을 반환하여 프로그램을 종료시킨다.
	}

	int** arr;  //동적으로 할당받을 이중 포인터 변수 선언

	arr = (int**)calloc(row, sizeof(int));  //행의 크기 만큼 동적메모리를 할당해준다.

	if (arr!=NULL)  // arr가 성공적으로 메모리를 할당 받았다면
	{
		for (int i = 0; i < row; i++)  //**arr에 열의 크기 만큼 동적 메모리를 할당해준다.
		{
			arr[i] = (int*)calloc(col, sizeof(int));
			if (arr[i] == NULL)  //만약 메모리 할당이 실패했다면
				return NULL;  //NULL을 반환하여 프로그램을 종료시킨다.
		}
	}


	else  //arr가 메모리 할당받는 것을 실패했다면
		return NULL; //NULL을 반환하여 프로그램을 종료시킨다.
	return arr;  //성공적으로 메모리를 할당 받았다면 2차원 배열의 주소를 넘겨준다.
}
int fill_data(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) //전처리 검사  넘겨받은 인자가 잘못되었다면
	{
		printf("check pre conditions\n");  //안내문 출력 후
		return -1;  //-1을 반환하여 프로그램을 종료시킨다.
	}

	for (int i = 0; i < row; i++)   //반복문을 이용하여 할당받은 배열 메모리에 0~19까지의 난수를 저장해준다.
		for (int j = 0; j < col; j++)
			matrix[i][j] = rand() % 20;
	for (int i = 0; i < row; i++)   //반복문을 이용하여 할당받은 배열 메모리에 난수가 제대로 입력되었는지 확인해준다.
		for (int j = 0; j < col; j++)
		{
			if (matrix[i][j]<0 && matrix[i][j]>19)  //난수 입력을 실패했다면
				return -1;
		}
		return 1;
}
void print_matrix(int** matrix, int row, int col)
{

	for (int i = 0; i < row; i++)   //반복문을 이용하여
		for (int j = 0; j < col; j++)
		{
			printf("%5d", matrix[i][j]);  //행렬을 출력해준다.
			if (j+1 == col)   //행렬의 행 한줄을 다 출력했다면
				printf("\n");  //다음 줄로 넘어간다.
		}
}
int free_matrix(int** matrix, int row, int col)
{
	int *ptr;
	if (row <= 0 || col <= 0) //전처리 검사  넘겨받은 인자가 잘못되었다면
	{
		printf("check pre conditions\n");  //안내문 출력 후
		return -1;  //-1을 반환하여 프로그램을 종료시킨다.
	}

	for (int i = 0; i < row; i++)  //반복문을 이용하여 행의 갯수만큼
	{
		ptr=matrix[i];  //ptr에 메모리 해제 전의 주소값을 넣어준다.
		free(matrix[i]);  //동적으로 받은 메모리를 해제해준다.
		if (matrix[i] == *ptr)   //메모리 해제 전의 값과 ptr이 가리키는 값이 같으면
			return -1;  //메모리 할당이 실패했다는 것을 알린다.
	}
	ptr=matrix;//ptr에 메모리 해제 전 주소값을 넣어준다.
	free(matrix);   //마지막으로 2차원 배열의 메모리를 해제해준다.
	if(matrix==*ptr)  //메모리 해제가 실패하였다면
		return -1;  //실패했다는 것을 알린다.
	else
		return 1;
}
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	if (row <= 0 || col <= 0) //전처리 검사  넘겨받은 인자가 잘못되었다면
	{
		printf("check pre conditions\n");  //안내문 출력 후
		return -1;  //-1을 반환하여 프로그램을 종료시킨다.
	}
	matrix_t[0][0]=-1;  //변수에 행렬의 첫번째에 -1 을 넣어준다.

	for (int i = 0; i < row; i++)  //반복문을 이용하여
		for (int j = 0; j < col; j++)  //행렬의 전치행렬을 구한다.
			matrix_t[i][j] = matrix[j][i];

	if (matrix_t[0][0]==-1)  //전치행렬을 해주기 전 행렬에 넣어둔 -1 값과 전치 행렬 후 행렬이 가지고 있는 값을 비교하여 값이 같다면
		return -1;  //-1을 반환하여 실패했다는 것을 알린다.
	return 1;  //성공했다면 1을 반환한다.
}
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col)
{
	if (row <= 0 || col <= 0) //전처리 검사  넘겨받은 인자가 잘못되었다면
	{
		printf("check pre conditions\n");  //안내문 출력 후
		return -1;  //-1을 반환하여 프로그램을 종료시킨다.
	}

	matrix_sum[0][0]=-1; // 두 행렬을 더하기 전에 -1을 넣어둔다.
	for (int i = 0; i < row; i++)//반복문을 이용하여
		for (int j = 0; j < col; j++)
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];  //두 행렬을 더해준다.

	if (matrix_sum[0][0] == -1) //matrix_sum 행렬의 첫번째 값이 두 행렬을 더하기 전에 넣어둔 -1과 같다면
		return -1;  //-1을 반환하여 합이 실패했다는 것을 알린다.
	else  //성공했다면
		return 1; //1을 반환한다.
}
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col)
{
	if (row <= 0 || col <= 0) //전처리 검사  넘겨받은 인자가 잘못되었다면
	{
		printf("check pre conditions\n");  //안내문 출력 후
		return -1;  //-1을 반환하여 프로그램을 종료시킨다.
	}

	matrix_sub[0][0]=NULL; //matrix_sub의 첫번째 값을 NULL로 해준다.
	for (int i = 0; i < row; i++)  //반복문을 이용하여
		for (int j = 0; j < col; j++)
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];  //두 함수를 뺀다.

	if (matrix_sub[0][0] ==NULL) //matrix_sum 행렬의 첫번째 값 NULL이라면
		return -1;  //-1을 반환하여 함수가 실패했다는 것을 알린다.
	else  //성공했다면
		return 1; //1을 반환한다.
}
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col)
{
	int sum = 0;

	if (row <= 0 || col <= 0) //전처리 검사  넘겨받은 인자가 잘못되었다면
	{
		printf("check pre conditions\n");  //안내문 출력 후
		return -1;  //-1을 반환하여 프로그램을 종료시킨다.
	}

	matrix_axt[0][0]=-1;  // matrix_axt의 첫번째 값에 -1을 넣어준다.
	for (int i = 0; i < row; i++)  //반복문을 이용하여
		for (int j = 0; j < row; j++)
		{
			sum = 0;
			for(int k=0;k<col;k++)  //행렬과 전치행렬을 곱해주고
				sum += (matrix_a[i][k] * matrix_t[k][j]);
			matrix_axt[i][j] = sum;
		}

	if (matrix_axt[0][0] == -1) //matrix_axt 행렬의 첫번째 값이 두 행렬을 곱하기 전에 넣어둔 -1과 같다면
		return -1;  //-1을 반환하여 함수가 실패했다는 것을 알린다.
	else  //성공했다면
		return 1; //1을 반환한다.
}
