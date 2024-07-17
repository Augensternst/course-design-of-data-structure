// ReSharper disable All
#include <iostream>
#include <ctime>
using namespace std;
clock_t start_time, end_time;
class sort
{
public:
	void bubblesort(int arr[],int start,int end);
	void select_sort(int arr[], int start, int end);
	void insert_sort(int arr[], int start, int end);
	void shell_sort(int arr[],int start, int end);
	void quick_sort(int array[], int start, int finish);
	void heapify(int array[], int start, int i, int n);
	void heap_sort(int array[], int start, int finish);
	void merge(int array[], int const left, int const mid, int const right);
	void merge_sort(int array[], int begin, int end);
	void custom_radix_sort_step(int data[], int start_idx, int end_idx, int digit);
	void radix_sort(int a[], int begin, int end);

	long long int num;

};

void sort::bubblesort(int arr[], int start, int end) {
	num = 0; // ���ý�������������
	for (int i = end; i >= start; i--) {
		for (int j = start; j < i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				num++; // ���ڽ�������ʱ���Ӽ���
			}
		}
	}
}


void sort::select_sort(int arr[], int start, int end)
{
	for(int i=start;i<end;i++)
	{
		int tem = i;
		for(int j=i+1;j<=end;j++)
		{
			if (arr[j] < arr[tem])
				tem = j;
			num++;
		}
		swap(arr[i], arr[tem]);
	}
}

void sort::insert_sort(int arr[], int start, int end)
{
	for (int i = start + 1; i <= end; i++)
	{
		for (int j = i; j > start; j--)
		{
			// ����������ǰ�Ƚ�
			if (arr[j] < arr[j - 1]) swap(arr[j], arr[j - 1]);
			num++;
		}
	}
}

void sort::shell_sort(int arr[], int start, int end)
{
	int range = (end - start + 1);
	for (int gap = range / 2; gap > 0; gap /= 2) {
		for (int i = start + gap; i <= end; i++) {
			int temp = arr[i];
			int j;
			for (j = i; j >= start + gap && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
				num++;
			}
			arr[j] = temp;
		}
	}
}

void sort::quick_sort(int array[], int start, int finish)
{
	if (start < finish) {
		int pivot = array[start];
		int i = start, j = finish;
		while (i < j) {
			while (i < j && array[j] >= pivot) j--;
			if (i < j) {
				array[i++] = array[j];
				num++;  // ������������
			}
			while (i < j && array[i] < pivot) i++;
			if (i < j) {
				array[j--] = array[i];
				num++;  // ������������
			}
		}
		array[i] = pivot;
		num++;  // ��pivot����������λ��Ҳ��һ�ν���

		quick_sort(array, start, i - 1);
		quick_sort(array, i + 1, finish);
	}
}

void sort::heapify(int array[], int start, int i, int n)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && array[start + left] > array[start + largest]) {
		largest = left;
	}
	if (right < n && array[start + right] > array[start + largest]) {
		largest = right;
	}
	if (largest != i) {
		swap(array[start + i], array[start + largest]);
		num++;  // ���ӽ�������
		heapify(array, start, largest, n);
	}

}

void sort::heap_sort(int array[], int start, int finish)
{
	int n = finish - start + 1;
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(array, start, i, n);
	}
	for (int i = n - 1; i >= 0; i--) {
		swap(array[start], array[start + i]);
		num++;  // ���ӽ�������
		heapify(array, start, 0, i);
	}
}

void sort::merge(int array[], int const left, int const mid, int const right)
{
	int sub_array_one = mid - left + 1;
	int sub_array_two = right - mid;
	int* left_array = new int[sub_array_one];
	int* right_array = new int[sub_array_two];

	for (int i = 0; i < sub_array_one; i++)
		left_array[i] = array[left + i];
	for (int j = 0; j < sub_array_two; j++)
		right_array[j] = array[mid + 1 + j];

	int index_one = 0, index_two = 0;
	int merged_index = left;

	while (index_one < sub_array_one && index_two < sub_array_two) {
		if (left_array[index_one] <= right_array[index_two]) {
			array[merged_index] = left_array[index_one++];
		}
		else {
			array[merged_index] = right_array[index_two++];
		}
		merged_index++;
		num++;  // ÿ�θ������ӽ�������
	}
	while (index_one < sub_array_one) {
		array[merged_index++] = left_array[index_one++];
		num++;  // ÿ�θ������ӽ�������
	}
	while (index_two < sub_array_two) {
		array[merged_index++] = right_array[index_two++];
		num++;  // ÿ�θ������ӽ�������
	}

	delete[] left_array;
	delete[] right_array;
}

void sort::merge_sort(int array[], int begin, int end)
{
	if (begin >= end) return;
	int mid = begin + (end - begin) / 2;
	merge_sort(array, begin, mid);
	merge_sort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

void sort::custom_radix_sort_step(int data[], int start_idx, int end_idx, int digit) {
	int sorted_data[100001]; // �����������ݵ���ʱ����
	int bucket[10] = { 0 };    // ��ʼ��Ͱ����

	// �������ݣ�����ÿ��Ͱ��Ԫ������
	for (int i = start_idx; i <= end_idx; i++) {
		int index = (data[i] / digit) % 10;
		bucket[index]++;
		num++; // ֱ��ʹ����ĳ�Ա����
	}

	// ����Ͱ���飬������sorted_data�е�λ��
	for (int i = 1; i < 10; i++) {
		bucket[i] += bucket[i - 1];
	}

	// ����Ͱ����Ϣ���������ݵ�sorted_data����
	for (int i = end_idx; i >= start_idx; i--) {
		int index = (data[i] / digit) % 10;
		sorted_data[--bucket[index]] = data[i];
		num++;
	}

	// ��sorted_data�е����ݸ��ƻ�ԭ����
	for (int i = start_idx; i <= end_idx; i++) {
		data[i] = sorted_data[i - start_idx];
		num++;
	}
}

void sort::radix_sort(int a[], int begin, int end)
{
	num = 0; // ���ü�����
	// �ҳ������е����ֵ
	int max_value = a[begin];
	for (int i = begin + 1; i <= end; i++) {
		if (a[i] > max_value) {
			max_value = a[i];
		}
	}
	// ��ÿһλ����������
	for (int digit = 1; max_value / digit > 0; digit *= 10) {
		custom_radix_sort_step(a, begin, end, digit); // ����Ҫ����num
	}
}


int main()
{
	srand((unsigned int)(time(0)));

	cout << "**        �����㷨        **" << endl;
	cout << "============================" << endl;
	cout << "**       1.ð������       **" << endl;
	cout << "**       2.ѡ������       **" << endl;
	cout << "**       3.��������       **" << endl;
	cout << "**       4.ϣ������       **" << endl;
	cout << "**       5.��������       **" << endl;
	cout << "**       6.������         **" << endl;
	cout << "**       7.�鲢����       **" << endl;
	cout << "**       8.��������       **" << endl;
	cout << "**       9.�˳�           **" << endl;
	cout << "============================" << endl;

	cout << endl << "���������������ĸ���(1-100000)��";
	int n;
	while(true)
	{
		cin >> n;
		if(n<1||n>100000||!cin.good())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "����������������룡" << endl;
			continue;
		}
		else
		{
			break;
		}
	}
	sort Sort;
	int a[100001];
	while(true)
	{
		cout << "��ѡ�������㷨��";
		int choice;
		cin >> choice;
		if (choice < 1 || choice>9 || !cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "��Ч�����֣����������룡" << endl;
			continue;
		}
		switch(choice)
		{
		case 1:
			// ���������
			for (int i = 0; i < n; i++)
				a[i] = rand();
			// ��¼��ʼʱ��
			start_time = clock();
			Sort.bubblesort(a, 0, n - 1);
			// ��¼����ʱ��
			end_time = clock();
			cout << "The run time is: " << double(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
			cout << "ð������Ƚϴ���: " << Sort.num << endl << endl;
			Sort.num = 0;
			break;
		case 2:
			// ���������
			for (int i = 0; i < n; i++)
				a[i] = rand();
			// ��¼��ʼʱ��
			start_time = clock();
			Sort.select_sort(a, 0, n - 1);
			// ��¼����ʱ��
			end_time = clock();
			cout << "The run time is: " << double(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
			cout << "ѡ������Ƚϴ���: " << Sort.num << endl << endl;
			Sort.num = 0;
			break;
		case 3:
			// ���������
			for (int i = 0; i < n; i++)
				a[i] = rand();
			// ��¼��ʼʱ��
			start_time = clock();
			Sort.insert_sort(a, 0, n - 1);
			// ��¼����ʱ��
			end_time = clock();
			cout << "The run time is: " << double(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
			cout << "��������Ƚϴ���: " << Sort.num << endl << endl;
			Sort.num = 0;
			break;
		case 4:

			// ���������
			for (int i = 0; i < n; i++)
				a[i] = rand();
			// ��¼��ʼʱ��
			start_time = clock();
			Sort.shell_sort(a, 0, n - 1);
			// ��¼����ʱ��
			end_time = clock();
			cout << "The run time is: " << double(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
			cout << "ϣ������Ƚϴ���: " << Sort.num << endl << endl;
			Sort.num = 0;
			break;
		case 5:
			// ���������
			for (int i = 0; i < n; i++)
				a[i] = rand();
			// ��¼��ʼʱ��
			start_time = clock();
			Sort.quick_sort(a, 0, n - 1);
			// ��¼����ʱ��
			end_time = clock();
			cout << "The run time is: " << double(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
			cout << "��������Ƚϴ���: " << Sort.num << endl << endl;
			Sort.num = 0;
			break;
		case 6:
			// ���������
			for (int i = 0; i < n; i++)
				a[i] = rand();
			// ��¼��ʼʱ��
			start_time = clock();
			Sort.heap_sort(a, 0, n - 1);
			// ��¼����ʱ��
			end_time = clock();
			cout << "The run time is: " << double(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
			cout << "������Ƚϴ���: " << Sort.num << endl << endl;
			Sort.num = 0;
			break;
		case 7:
			// ���������
			for (int i = 0; i < n; i++)
				a[i] = rand();
			// ��¼��ʼʱ��
			start_time = clock();
			Sort.merge_sort(a, 0, n - 1);
			// ��¼����ʱ��
			end_time = clock();
			cout << "The run time is: " << double(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
			cout << "�鲢����Ƚϴ���: " << Sort.num << endl << endl;
			Sort.num = 0;
			break;
		case 8:
			// ���������
			for (int i = 0; i < n; i++)
				a[i] = rand();
			// ��¼��ʼʱ��
			start_time = clock();
			Sort.radix_sort(a, 0, n - 1);
			// ��¼����ʱ��
			end_time = clock();
			cout << "The run time is: " << double(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
			cout << "��������Ƚϴ���: " << Sort.num << endl << endl;
			Sort.num = 0;
			break;
		case 9:
			cout << "��лʹ�ã����������" << endl;
			system("pause");
			return 0;
		}
	}




	
	
	


	

}


