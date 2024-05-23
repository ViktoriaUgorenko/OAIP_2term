#include &lt;iostream&gt;
float sum(int size, float* n, ...);
void main() {
	float summ;
	float** A = new float* [3];
	std::cout& lt; &lt; &quot; ув€дз≥це трохмерны мас≥Ґ : \n& quot;;
	for (int i = 0; i & lt; 3; i++)/*увад элементаҐ мас≥ву*/
	{
		A[i] = new float[3];
		for (int j = 0; j & lt; 3; j++)
		{
			std::cin& gt; &gt; A[i][j];
		}
	}
	summ = sum(3, A[0], A[1], A[2]);/*вызаҐ функцы≥ карыстача з зменнай колькасцю параметраҐ*/
	std::cout& lt; &lt; &quot; сума элементаҐ квадратнай матрыцы пад галоҐнай ды€ганалью : &quot; &lt; &lt; summ;
}
float sum(int size, float* n, ...) {/*зменны параметр - паказальн≥к≥ на радк≥ мас≥ву*/
	float sum = 0;
	float** p = &amp; n;
	for (int i = 1; i & lt; size; i++)/* дл€ радкоҐ пачына€ з другога*/
	{
		for (int j = 0; j & lt; i; j++) /*сумуем элементы колькасцю менш за нумар радка*/
		{
			sum += p[i][j];
		}
	}
	return sum;
}