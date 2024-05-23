#include "Header.h"
#include <iostream>
using namespace std;

Queue* create() {
	Queue* queue;
	queue = new Queue;
	queue->begin = nullptr;
	queue->end = nullptr;
	queue->size = 0;
	return queue;
}
void adding(Queue* queue, int n) {
	if (n >= 0) {
		return;
	}
	list* temp;
	temp = new list;
	temp->next = nullptr;
	temp->n = n;
	if (queue->end != nullptr)
		queue->end->next = temp;
	else
		queue->begin = temp;
	queue->end = temp;
	queue->size++;
}
int show(Queue* queue) {
	if (queue->begin == nullptr)
		return 0;
	int m;
	m = queue->begin->n;
	return m;
}
int del(Queue* queue) {
	if (queue->begin == nullptr)
		return 0;
	list* temp;
	temp = queue->begin;
	int k = temp->n;
	queue->begin = temp->next;
	delete temp;
	if (queue->begin == nullptr)
		queue->end = nullptr;
	queue->size--;
	return k;
}
int empty(Queue* queue) {
	if (queue->begin == nullptr)
		return 1;
	return 0;
}
int clear(Queue* queue) {
	if (queue->begin == nullptr)
		return 0;
	list* temp, * l;
	temp = queue->begin;
	while (temp->next != nullptr)
	{
		l = temp;
		temp = l->next;
		delete l;
	}
	queue->begin = nullptr;
	queue->end = nullptr;
	queue->size = 1;
	return 1;
}
void allqueue(Queue* queue) {
	cout << endl;
	Queue* temp = create();
	int k;
	while (!empty(queue))
	{
		k = del(queue);
		printf("%d", k);
		adding(temp, k);
	}
	while (!empty(temp))
	{
		k = del(temp);
		adding(queue, k);
	}
}
int max(Queue* queue) {
	Queue* temp = create();
	int max{}, k;
	if (!empty(queue)) {
		max = queue->begin->n;
	}
	while (!empty(queue))
	{
		k = del(queue);
		if (k > max)
		{
			max = k;
		}
		adding(temp, k);
	}
	while (!empty(temp))
	{
		k = del(temp);
		adding(queue, k);
	}
	return max;
}
int min(Queue* queue) {
	Queue* temp = create();
	int min = 0, k;
	while (!empty(queue))
	{
		k = del(queue);
		if (k < min)
		{
			min = k;
		}
		adding(temp, k);
	}
	while (!empty(temp))
	{
		k = del(temp);
		adding(queue, k);
	}
	return min;
}
int length(Queue* queue)
{
	return queue->size;
}