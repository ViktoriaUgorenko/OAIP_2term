#include &lt;iostream&gt;
float sum(int size, float* n, ...);
void main() {
	float summ;
	float** A = new float* [3];
	std::cout& lt; &lt; &quot; ������� ��������� ��� : \n& quot;;
	for (int i = 0; i & lt; 3; i++)/*���� �������� �����*/
	{
		A[i] = new float[3];
		for (int j = 0; j & lt; 3; j++)
		{
			std::cin& gt; &gt; A[i][j];
		}
	}
	summ = sum(3, A[0], A[1], A[2]);/*���� ������� ��������� � ������� ��������� ���������*/
	std::cout& lt; &lt; &quot; ���� �������� ���������� ������� ��� ������� ���������� : &quot; &lt; &lt; summ;
}
float sum(int size, float* n, ...) {/*������ �������� - ���������� �� ���� �����*/
	float sum = 0;
	float** p = &amp; n;
	for (int i = 1; i & lt; size; i++)/* ��� ����� ������� � �������*/
	{
		for (int j = 0; j & lt; i; j++) /*������ �������� ��������� ���� �� ����� �����*/
		{
			sum += p[i][j];
		}
	}
	return sum;
}