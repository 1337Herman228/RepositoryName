#include <cstdlib> 
#include <iostream> 
#include <conio.h> 
#include <stdio.h> 
#include<iomanip>
#include <stdlib.h> 
#include <windows.h>

using namespace std;

int **Adjacency_matrix; //Матрица смежности 
int **I; // Матрица инцидентности
int M; // Количество рёбер в матрице инцидентности

struct AdjListNode   // Структура для представления списка смежности узла
{
	int dest;
	struct AdjListNode* next;
};


struct AdjList	// Структура для представления списка смежности
{
	struct AdjListNode* head; // указатель на головной узел списка
};



struct Graph	// Структура для представления графа. Граф представляет собой массив из списков смежности.
{
	int V;	// Размер массива будет V (число вершин в графе) 
	struct AdjList* array;
};



struct AdjListNode* newAdjListNode(int dest)	// вспомогательная функция для создания узла нового списка смежности
{
	struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;

}

int del_node=99;

void delAdjListNode(struct Graph* graph, int dest)	// вспомогательная функция для удаления узла из графа
{
	int n = graph->V;

	for (int i = dest+1; i < n ; i++)
	{
		graph->array[i - 1].head = graph->array[i].head;
	}

	graph->V--;

	int counter=0;

		for (int i = 0; i < n; i++)
		{
			struct AdjListNode* pCrawl = graph->array[i].head;
			struct AdjListNode* p = graph->array[i].head;

			while (pCrawl)
			{
				if (pCrawl->dest == dest)
				{
					if (pCrawl->next)
					{
						p = pCrawl->next;
						graph->array[i].head = p;
					}
				}


				if (pCrawl->next)
				{
					if (pCrawl->next->dest == dest)
					{
						if (pCrawl->next->next)
						{
							p = pCrawl->next;

							for (int i = 0; i < counter; i++)
							{
								if (graph->array[i].head->next)
									graph->array[i].head->next;
							}

							/*if(graph->array[i].head->next)*/
							graph->array[i].head->next = p->next;
						}
					}
				}

				pCrawl = pCrawl->next;
				counter++;
			}
		}

		del_node = dest;
}

struct Graph* createGraph(int V)	// Служебная функция, которая создает граф с V вершинами
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;

	// Создание массива списков смежности. Размер массива будет V
	graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

	// Инициализация каждого списка смежности как пустого, сделав начало = NULL
	int i;
	for (i = 0; i < V; ++i)
		graph->array[i].head = NULL;
	return graph;
}


void addEdge(struct Graph* graph, int src, int dest)	//Добавляет ребро неориентированного графа
{
	// Добавляет ребро из src в построение. Новый узел добавляется в список смежности
	// Список src.Узел добавляется в начале
	struct AdjListNode* newNode = newAdjListNode(dest); 
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	// Поскольку граф неориентированный, также добавим ребро от Dest в SRC 
	newNode = newAdjListNode(src);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}

void create_Adjacency_matrix(struct Graph* graph)
{
	int n = graph->V;

	Adjacency_matrix = new int* [n];
	for (int i = 0; i < n; i++)
		Adjacency_matrix[i] = new int[n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Adjacency_matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++)
	{
		struct AdjListNode* pCrawl = graph->array[i].head;
		while (pCrawl)
		{
			Adjacency_matrix[i][pCrawl->dest] = 1;
			pCrawl = pCrawl->next;
		}
	}
}

void print_Adjacency_matrix(struct Graph* graph)
{
	int n = graph->V;

	cout << "Матрица смежности:" << endl << endl;

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < n; j++)
		{
			cout << setw(2) << Adjacency_matrix[i][j];
		}
		cout << endl;
	}

	cout << endl;
}

void printGraph(struct Graph* graph)
{
	int v;
	int counter=0;
	cout << "+---------+---------------------------+" << endl;
	cout << "| Вершина | Смежные ей другие вершины |" << endl;
	for (v = 1; v < graph->V; v++)
	{
		counter = 0;
		cout << "+---------+---------------------------+" << endl;
		struct AdjListNode* pCrawl = graph->array[v].head; 

		
		if (v >= del_node)
		{
			cout << "|" << setw(5) << v+1 << setw(5) << "|";
		}
		else
		cout << "|" << setw(5) << v << setw(5) << "|";

		while (pCrawl)
		{
			cout << setw(3) << pCrawl->dest;
			counter++;
			pCrawl = pCrawl->next;
		}
		cout <<setw(28 - counter*3) << "|" << endl;
	}
	cout << "+---------+---------------------------+" << endl;

	cout << endl;
}

void create_Incid_matrix(struct Graph* graph)
{
	M = 0;
	int n = graph->V;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			M += Adjacency_matrix[i][j];
		}
	}
	M /= 2; // вычисляем количество ребер

	I = new int* [n]; // Матрица инцидентности
	for (int i = 0; i < n; i++)
		I[i] = new int[M];

	for (int i = 0; i < n; i++) // Заполняем нулями
	{
		for (int j = 0; j < M; j++)
		{
			I[i][j] = 0;
		}
	}

	int C = 0; // Номер текущего ребра

	for (int i = 0; i < n; i++) // Заполняем матрицу инцидентности
		for (int j = i + 1; j < n; j++)
			if (Adjacency_matrix[i][j]) 
			{
				I[i][C] = 1;
				I[j][C] = 1;
				C++;
			}
}

void print_Incid_matrix(struct Graph* graph)
{
	int n = graph->V;

	cout << "Матрица инцидентности:" << endl << endl;

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << setw(2) << I[i][j];
		}
		cout << endl;
	}
}

void del_Edge(int number)
{
	int V = 8 + 1;
	struct Graph* graph = createGraph(V);

	addEdge(graph, 1, 2);
	addEdge(graph, 1, 8);

	addEdge(graph, 2, 3);
	addEdge(graph, 2, 6);

	addEdge(graph, 3, 4);
	addEdge(graph, 3, 6);

	addEdge(graph, 4, 5);
	addEdge(graph, 4, 7);

	addEdge(graph, 5, 6);
	addEdge(graph, 5, 7);

	addEdge(graph, 6, 7);

	addEdge(graph, 7, 8);

	create_Adjacency_matrix(graph); // создание матрицы смежности
	create_Incid_matrix(graph); // создание матрицы инцидентности
	delAdjListNode(graph, 6); // удалить вершину 6
	printGraph(graph);	// представление списка смежности вышеуказанного графа
	print_Adjacency_matrix(graph); // вывод матрицы смежности
	print_Incid_matrix(graph);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	cout << "Создаём граф согласно заданию 1: |" << endl;
	cout << "_________________________________|" << endl;

	// создать граф, согласно заданной выше фигуре
	int V = 8                                                                                                                                      + 1;
	struct Graph* graph = createGraph(V);

	addEdge(graph, 1, 2);
	addEdge(graph, 1, 6);
	addEdge(graph, 1, 8);

	addEdge(graph, 2, 3);
	addEdge(graph, 2, 6);

	addEdge(graph, 3, 4);
	addEdge(graph, 3, 5);
	addEdge(graph, 3, 6);

	addEdge(graph, 4, 5);
	addEdge(graph, 4, 7);

	addEdge(graph, 5, 6);
	addEdge(graph, 5, 7);

	addEdge(graph, 6, 7);
	addEdge(graph, 6, 8);

	addEdge(graph, 7, 8);

	create_Adjacency_matrix(graph); // создание матрицы смежности
	create_Incid_matrix(graph); // создание матрицы инцидентности

	printGraph(graph);	// представление списка смежности вышеуказанного графа
	print_Adjacency_matrix(graph); // вывод матрицы смежности
	print_Incid_matrix(graph); // вывод матрицы инцидентности

	cout << endl << ",____________________," << endl;
	cout << "| Удаляем вершину 6: |" << endl;
	cout << "|____________________|" << endl;
	delAdjListNode(graph, 6); // удалить вершину 6

	create_Adjacency_matrix(graph); // создание матрицы смежности
	create_Incid_matrix(graph); // создание матрицы инцидентности

	printGraph(graph);	// представление списка смежности вышеуказанного графа
	print_Adjacency_matrix(graph); // вывод матрицы смежности
	print_Incid_matrix(graph); // вывод матрицы инцидентности

	cout << endl << ",____________________," << endl;
	cout << "|  Удаляем ребро 3:  |" << endl;
	cout << "|____________________|" << endl;

	del_Edge( 3); // удалить ребро 3

	return 0;
}
