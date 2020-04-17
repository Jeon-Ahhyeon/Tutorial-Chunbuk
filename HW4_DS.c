#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int row, int col);  //����� �����޸� �Ҵ��� �̿��Ͽ� 2���� �迭�� ����� �ִ� �Լ� ������ �迭�� ��ȯ
int free_matrix(int** matrix, int row, int col);//���� �޸𸮸� ���������ִ� �Լ�
void print_matrix(int** matrix, int row, int col);//2���� �迭�� ������� ����� ������ִ� �Լ�
int fill_data(int** matrix, int row, int col);//�Ҵ�� 2���� �迭(���)�� �������� ���� �Է����ִ� �Լ�
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);  //������� ����� ��ġ����� ���ϴ� �Լ�
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col);  //ũ�Ⱑ ���� ��� �ΰ��� �����ִ� �Լ�
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col);//ũ�Ⱑ ���� ��� �ΰ��� ���� �Լ�
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col);  //��İ� �� ����� ��ġ����� ���� ���ϴ� �Լ�



int main()
{
	int row, col;  //��� ���� �Է¹޴� �Լ�
	int** matrix=NULL , ** matrix_t = NULL, ** matrix_a = NULL, ** matrix_b = NULL, ** matrix_sub = NULL, ** matrix_sum = NULL, ** matrix_axt = NULL;  // ���� �����͸� �������ش�. �� 7���� 2���� �迭�� �����.
	int i = 0;
	printf("������ 2018068005\n\n");

	do {
		printf("����� �� : ");
		fflush(stdout);
		scanf_s("%d", &row);   //��� ���� �Է¹޴´�.

		printf("����� �� : ");
		fflush(stdout);
		scanf_s("%d", &col);
		if (row <= 0 || col <= 0)       //��� ���� ���� �߸� �Է����� ���
		{
			printf("��� ���� �ٽ� �Է����ּ���.\n");   //�ȳ��� �����
			continue;  //�ݺ����� ó������ ���ư� ��� ���� �ٽ� �Է¹޴´�.
		}
		matrix = create_matrix(row, col);  //��ĵ��� �������� �޸𸮸� �Ҵ����ش�.
		matrix_t = create_matrix(col,row);  //��ġ����� ��� ���� ũ�Ⱑ �ٲ�Ƿ� �Է¹��� ��� ���� �ٲ㼭 �Ѱ��ش�.
		matrix_a = create_matrix(row, col);
		matrix_b = create_matrix(row, col);
		matrix_sub = create_matrix(row, col);
		matrix_axt = create_matrix(row,row);  //��İ� ��ġ����� ���� ����� ��* ��ġ����� �� ũ�� �̹Ƿ� ���� ���� �Ѱ��ش�.
		matrix_sum = create_matrix(row, col);

		if (matrix != NULL || matrix_a != NULL || matrix_b != NULL || matrix_t != NULL || matrix_sub != NULL || matrix_sum != NULL || matrix_axt != NULL)
			break;  //��� ����� �����޸� �Ҵ����� �ùٸ��� �Ҵ� �޾Ҵٸ� �ݺ����� ����
		else //�Ҵ翡 �����ߴٸ�
		{
			printf("�����޸� �Ҵ��� �����Ͽ����ϴ�.\n");  //�ȳ����� ����� ��
			printf("���α׷��� �������ּ���.\n");
			return 0;  //���α׷��� �����Ѵ�.
		}
	} while (1);//���� �޸� �Ҵ��� �����Ҷ� ���� �ݺ��� ����


	srand((unsigned int)time NULL);  // ��Ŀ� ������ �����ϱ� ���� rand�� ����� �� �ʱ�ȭ

	if (fill_data(matrix, row, col) == -1)   //fill_data �Լ��� matrix, matrix_a, matrix_b ����� ������ ä���ش�.
	{
		printf("������ ���� ����� �Է¹��� ���߽��ϴ�.\n");  //��� ä��⸦ �����ߴٸ� �ȳ����� ����� ��
		i = -1;  //i�� -1�� �־��־� �����ߴٴ� ���� �˸���.
	}
	if (fill_data(matrix_a, row, col) == -1) {
		printf("������ ���� ����� �Է¹��� ���߽��ϴ�.\n");
		i = -1;
	}
	if (fill_data(matrix_b, row, col) == -1) {
		printf("������ ���� ����� �Է¹��� ���߽��ϴ�.\n");
		i = -1;
	}
	if (i == -1) // ������ ���ä��� ���� �����ߴٸ�
	{
		if (free_matrix(matrix, row, col) == -1) //�����޸𸮸� �̿��� �Ҵ���� �޸𸮸� �����Ѵ�.
			printf("1.�޸� ������ ����� �������� ���߽��ϴ�.\n");// ������ ����� ���� ������ ���� �ȳ����� ����Ѵ�.
		else
			printf("matrix�� �޸� ������ �����߽��ϴ�.\n");
		if (free_matrix(matrix_t, col, row) == -1)
			printf("2.�޸� ������ ����� �������� ���߽��ϴ�.\n");
		else
			printf("matrix_t�� �޸� ������ �����߽��ϴ�.\n");
		if (free_matrix(matrix_a, row, col) == -1)
			printf("3.�޸� ������ ����� �������� ���߽��ϴ�.\n");
		else
			printf("matrix_a�� �޸� ������ �����߽��ϴ�.\n");
		if (free_matrix(matrix_b, row, col) == -1)
			printf("4.�޸� ������ ����� �������� ���߽��ϴ�.\n");
		else
			printf("matrix_b�� �޸� ������ �����߽��ϴ�.\n");
		if (free_matrix(matrix_sum, row, col) == -1)
			printf("5.�޸� ������ ����� �������� ���߽��ϴ�.\n");
		else
			printf("matrix_sum�� �޸� ������ �����߽��ϴ�.\n");
		if (free_matrix(matrix_sub, row, col) == -1)
			printf("6.�޸� ������ ����� �������� ���߽��ϴ�.\n");
		else
			printf("matrix_sub�� �޸� ������ �����߽��ϴ�.\n");
		if (free_matrix(matrix_axt, row, row) == -1)
			printf("7.�޸� ������ ����� �������� ���߽��ϴ�.\n");
		else
			printf("matrix_axt�� �޸� ������ �����߽��ϴ�.\n");
		return 0; //���α׷��� �����Ѵ�.
	}

	printf("matrix ���\n");  //�ȳ��� ��� ��
	print_matrix(matrix, row, col);  //��� �Լ��� ȣ���Ͽ� matrix�� ����Ѵ�.
	printf("matrix_a ���\n");
	print_matrix(matrix_a, row, col);//��� �Լ��� ȣ���Ͽ� matrix_a�� ����Ѵ�.
	printf("matrix_b ���\n");
	print_matrix(matrix_b, row, col);//��� �Լ��� ȣ���Ͽ� matrix_b�� ����Ѵ�.

	if (addition_matrix(matrix_a, matrix_b, matrix_sum, row, col) == -1)  //����� ���ϴ� �Լ��� ȣ�� �Ͽ�
		printf("����� ���� �����Ͽ����ϴ�.\n");  //����� ���� ���� �Ͽ����� �ȳ��� ���
	else  //�����ߴٸ�
	{	printf("matrix ��\n");  //print_matrix �Լ��� ȣ���Ͽ� ��� ���
		print_matrix(matrix_sum, row, col);
	}

	if (subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, col) == -1)//�ΰ��� ����� ���� �Լ��� ȣ�� �Ͽ�
		printf("����� ���� �����Ͽ����ϴ�.\n");  //�����ϸ� ���� �ȳ��� ���
	else	{  //�����ϸ�
		printf("matrix ��\n");
		print_matrix(matrix_sub, row, col); //print_matrix �Լ��� ȣ���Ͽ� ��� ���
	}

	if (transpose_matrix(matrix_a, matrix_t, col,row) == -1)//����� ��ġ��ķ� �ٲ��ִ� �Լ� ȣ���Ͽ�
		printf("��ġ ����� ���� �߸��Ǿ����ϴ�. \n");  //�����ϸ� ���� �ȳ��� ���
	else{ //�����ϸ�
		printf("matrix ��ġ ���\n");
		print_matrix(matrix_t, col, row);  //print_matrix �Լ��� ȣ���Ͽ� ��� ���  , ��ġ����� ��� ���� ���� �ٲ��.
	}

	if (multiply_matrix(matrix_a, matrix_t,matrix_axt, row, col) == -1)  //��ġ��İ� ����� �����ִ� �Լ��� ȣ���Ͽ�
		printf("��ġ��İ� ����� ���� �����Ͽ����ϴ�.\n");  //�����ϸ� ���� �ȳ��� ���
	else  //�����ϸ�
	{
		printf("matrix ��\n");
		print_matrix(matrix_axt, row, row);  //print_matrix �Լ��� ȣ���Ͽ� ��� ���  , �� ����� ���ϸ� ����� ũ�Ⱑ �޶�����.
	}


	if (free_matrix(matrix, row, col) == -1) //�����޸𸮸� �̿��� �Ҵ���� �޸𸮸� �����Ѵ�.
		printf("1.�޸� ������ ����� �������� ���߽��ϴ�.\n");// ������ ����� ���� ������ ���� �ȳ����� ����Ѵ�.
	else
		printf("matrix�� �޸� ������ �����߽��ϴ�.\n");
	if (free_matrix(matrix_t, col, row) == -1)
		printf("2.�޸� ������ ����� �������� ���߽��ϴ�.\n");
	else
		printf("matrix_t�� �޸� ������ �����߽��ϴ�.\n");
	if (free_matrix(matrix_a, row, col) == -1)
		printf("3.�޸� ������ ����� �������� ���߽��ϴ�.\n");
	else
		printf("matrix_a�� �޸� ������ �����߽��ϴ�.\n");
	if (free_matrix(matrix_b, row, col) == -1)
		printf("4.�޸� ������ ����� �������� ���߽��ϴ�.\n");
	else
		printf("matrix_b�� �޸� ������ �����߽��ϴ�.\n");
	if (free_matrix(matrix_sum, row, col) == -1)
		printf("5.�޸� ������ ����� �������� ���߽��ϴ�.\n");
	else
		printf("matrix_sum�� �޸� ������ �����߽��ϴ�.\n");
	if (free_matrix(matrix_sub, row, col) == -1)
		printf("6.�޸� ������ ����� �������� ���߽��ϴ�.\n");
	else
		printf("matrix_sub�� �޸� ������ �����߽��ϴ�.\n");
	if (free_matrix(matrix_axt, row, row) == -1)
		printf("7.�޸� ������ ����� �������� ���߽��ϴ�.\n");
	else
		printf("matrix_axt�� �޸� ������ �����߽��ϴ�.\n");

}
int** create_matrix(int row, int col)
{
	if (row <= 0 || col <= 0) //��ó�� �˻�  �Ѱܹ��� ���ڰ� �߸��Ǿ��ٸ�
	{
		printf("check pre conditions\n");  //�ȳ��� ��� ��
		return NULL;  //NULL���� ��ȯ�Ͽ� ���α׷��� �����Ų��.
	}

	int** arr;  //�������� �Ҵ���� ���� ������ ���� ����

	arr = (int**)calloc(row, sizeof(int));  //���� ũ�� ��ŭ �����޸𸮸� �Ҵ����ش�.

	if (arr!=NULL)  // arr�� ���������� �޸𸮸� �Ҵ� �޾Ҵٸ�
	{
		for (int i = 0; i < row; i++)  //**arr�� ���� ũ�� ��ŭ ���� �޸𸮸� �Ҵ����ش�.
		{
			arr[i] = (int*)calloc(col, sizeof(int));
			if (arr[i] == NULL)  //���� �޸� �Ҵ��� �����ߴٸ�
				return NULL;  //NULL�� ��ȯ�Ͽ� ���α׷��� �����Ų��.
		}
	}


	else  //arr�� �޸� �Ҵ�޴� ���� �����ߴٸ�
		return NULL; //NULL�� ��ȯ�Ͽ� ���α׷��� �����Ų��.
	return arr;  //���������� �޸𸮸� �Ҵ� �޾Ҵٸ� 2���� �迭�� �ּҸ� �Ѱ��ش�.
}
int fill_data(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) //��ó�� �˻�  �Ѱܹ��� ���ڰ� �߸��Ǿ��ٸ�
	{
		printf("check pre conditions\n");  //�ȳ��� ��� ��
		return -1;  //-1�� ��ȯ�Ͽ� ���α׷��� �����Ų��.
	}

	for (int i = 0; i < row; i++)   //�ݺ����� �̿��Ͽ� �Ҵ���� �迭 �޸𸮿� 0~19������ ������ �������ش�.
		for (int j = 0; j < col; j++)
			matrix[i][j] = rand() % 20;
	for (int i = 0; i < row; i++)   //�ݺ����� �̿��Ͽ� �Ҵ���� �迭 �޸𸮿� ������ ����� �ԷµǾ����� Ȯ�����ش�.
		for (int j = 0; j < col; j++)
		{
			if (matrix[i][j]<0 && matrix[i][j]>19)  //���� �Է��� �����ߴٸ�
				return -1;
		}
		return 1;
}
void print_matrix(int** matrix, int row, int col)
{

	for (int i = 0; i < row; i++)   //�ݺ����� �̿��Ͽ�
		for (int j = 0; j < col; j++)
		{
			printf("%5d", matrix[i][j]);  //����� ������ش�.
			if (j+1 == col)   //����� �� ������ �� ����ߴٸ�
				printf("\n");  //���� �ٷ� �Ѿ��.
		}
}
int free_matrix(int** matrix, int row, int col)
{
	int *ptr;
	if (row <= 0 || col <= 0) //��ó�� �˻�  �Ѱܹ��� ���ڰ� �߸��Ǿ��ٸ�
	{
		printf("check pre conditions\n");  //�ȳ��� ��� ��
		return -1;  //-1�� ��ȯ�Ͽ� ���α׷��� �����Ų��.
	}

	for (int i = 0; i < row; i++)  //�ݺ����� �̿��Ͽ� ���� ������ŭ
	{
		ptr=matrix[i];  //ptr�� �޸� ���� ���� �ּҰ��� �־��ش�.
		free(matrix[i]);  //�������� ���� �޸𸮸� �������ش�.
		if (matrix[i] == *ptr)   //�޸� ���� ���� ���� ptr�� ����Ű�� ���� ������
			return -1;  //�޸� �Ҵ��� �����ߴٴ� ���� �˸���.
	}
	ptr=matrix;//ptr�� �޸� ���� �� �ּҰ��� �־��ش�.
	free(matrix);   //���������� 2���� �迭�� �޸𸮸� �������ش�.
	if(matrix==*ptr)  //�޸� ������ �����Ͽ��ٸ�
		return -1;  //�����ߴٴ� ���� �˸���.
	else
		return 1;
}
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	if (row <= 0 || col <= 0) //��ó�� �˻�  �Ѱܹ��� ���ڰ� �߸��Ǿ��ٸ�
	{
		printf("check pre conditions\n");  //�ȳ��� ��� ��
		return -1;  //-1�� ��ȯ�Ͽ� ���α׷��� �����Ų��.
	}
	matrix_t[0][0]=-1;  //������ ����� ù��°�� -1 �� �־��ش�.

	for (int i = 0; i < row; i++)  //�ݺ����� �̿��Ͽ�
		for (int j = 0; j < col; j++)  //����� ��ġ����� ���Ѵ�.
			matrix_t[i][j] = matrix[j][i];

	if (matrix_t[0][0]==-1)  //��ġ����� ���ֱ� �� ��Ŀ� �־�� -1 ���� ��ġ ��� �� ����� ������ �ִ� ���� ���Ͽ� ���� ���ٸ�
		return -1;  //-1�� ��ȯ�Ͽ� �����ߴٴ� ���� �˸���.
	return 1;  //�����ߴٸ� 1�� ��ȯ�Ѵ�.
}
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col)
{
	if (row <= 0 || col <= 0) //��ó�� �˻�  �Ѱܹ��� ���ڰ� �߸��Ǿ��ٸ�
	{
		printf("check pre conditions\n");  //�ȳ��� ��� ��
		return -1;  //-1�� ��ȯ�Ͽ� ���α׷��� �����Ų��.
	}

	matrix_sum[0][0]=-1; // �� ����� ���ϱ� ���� -1�� �־�д�.
	for (int i = 0; i < row; i++)//�ݺ����� �̿��Ͽ�
		for (int j = 0; j < col; j++)
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];  //�� ����� �����ش�.

	if (matrix_sum[0][0] == -1) //matrix_sum ����� ù��° ���� �� ����� ���ϱ� ���� �־�� -1�� ���ٸ�
		return -1;  //-1�� ��ȯ�Ͽ� ���� �����ߴٴ� ���� �˸���.
	else  //�����ߴٸ�
		return 1; //1�� ��ȯ�Ѵ�.
}
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col)
{
	if (row <= 0 || col <= 0) //��ó�� �˻�  �Ѱܹ��� ���ڰ� �߸��Ǿ��ٸ�
	{
		printf("check pre conditions\n");  //�ȳ��� ��� ��
		return -1;  //-1�� ��ȯ�Ͽ� ���α׷��� �����Ų��.
	}

	matrix_sub[0][0]=NULL; //matrix_sub�� ù��° ���� NULL�� ���ش�.
	for (int i = 0; i < row; i++)  //�ݺ����� �̿��Ͽ�
		for (int j = 0; j < col; j++)
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];  //�� �Լ��� ����.

	if (matrix_sub[0][0] ==NULL) //matrix_sum ����� ù��° �� NULL�̶��
		return -1;  //-1�� ��ȯ�Ͽ� �Լ��� �����ߴٴ� ���� �˸���.
	else  //�����ߴٸ�
		return 1; //1�� ��ȯ�Ѵ�.
}
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col)
{
	int sum = 0;

	if (row <= 0 || col <= 0) //��ó�� �˻�  �Ѱܹ��� ���ڰ� �߸��Ǿ��ٸ�
	{
		printf("check pre conditions\n");  //�ȳ��� ��� ��
		return -1;  //-1�� ��ȯ�Ͽ� ���α׷��� �����Ų��.
	}

	matrix_axt[0][0]=-1;  // matrix_axt�� ù��° ���� -1�� �־��ش�.
	for (int i = 0; i < row; i++)  //�ݺ����� �̿��Ͽ�
		for (int j = 0; j < row; j++)
		{
			sum = 0;
			for(int k=0;k<col;k++)  //��İ� ��ġ����� �����ְ�
				sum += (matrix_a[i][k] * matrix_t[k][j]);
			matrix_axt[i][j] = sum;
		}

	if (matrix_axt[0][0] == -1) //matrix_axt ����� ù��° ���� �� ����� ���ϱ� ���� �־�� -1�� ���ٸ�
		return -1;  //-1�� ��ȯ�Ͽ� �Լ��� �����ߴٴ� ���� �˸���.
	else  //�����ߴٸ�
		return 1; //1�� ��ȯ�Ѵ�.
}
