//Implementacja metod klasy Matrix
#include "pch.h"
#include "Matrix.h"

using namespace std;

void Matrix::test()
{
	system("cls");
	cout << "Notchecked:" << endl;
	cout << "\nDist: ";
	for (int i = 0; i < dnch; i++)
	{
		cout << notchecked[i].distance;
		if (notchecked[i].distance > 9 || notchecked[i].distance == -1) cout << " ";
		else cout << "  ";
	}
	cout << "\nPrev: ";
	for (int i = 0; i < dnch; i++)
	{
		cout << notchecked[i].prev;
		if (notchecked[i].prev > 9 || notchecked[i].prev == -1) cout << " ";
		else cout << "  ";
	}
	cout << "\nInde: ";
	for (int i = 0; i < dnch; i++)
	{
		cout << notchecked[i].index;
		if (notchecked[i].index > 9 || notchecked[i].index == -1) cout << " ";
		else cout << "  ";
	}
	_getche();
}

//Funkcja losowo tworz�ca graf
void Matrix::create(int NN, double EE, double ME, bool directed) 
{
	nodes = NN;
	edges = ME * (EE/100);
	bool found;
	int counter = nodes;
	int begin, end;
	int *visited = new int [nodes];
	pointer = new int *[nodes];
	for (int i = 0; i < nodes; i++)
	{
		visited[i] = 0;
		pointer[i] = new int[nodes];
		for (int j = 0; j < nodes; j++)
		{
			pointer[i][j] = 0;
		}
	}
	spanningtree(visited);
	if (!directed)
	{
		for (int i = 0; i < nodes; i++)
		{
			for (int j = 0; j < nodes; j++)
			{
				if (pointer[i][j] != 0) pointer[j][i] = pointer[i][j];
			}
		}
	}
	while (counter <= edges)
	{
		found = false;
		begin = rand() % nodes;
		for (int i = 0; i < nodes; i++)
		{
			if (i != begin && pointer[begin][i] == 0)
			{
				found = true;
				end = i;
			}
		}
		if (!found) continue;
		pointer[begin][end] = (rand() % 99) + 1;
		if (!directed) pointer[end][begin] = pointer[begin][end];
		counter++;
	}
	delete visited;
	display();
}

//Funkcja wy�wietlaj�ca graf
void Matrix::display()
{
	system("cls");
	if (pointer == nullptr) cout << "Graf nie istnieje!" << endl;
	else
	{
		cout << "\nWierzcho�ki: " << nodes << ", Kraw�dzie: " << edges;
		cout << "\nMacierz s�siedztwa: " << endl;
		cout << "  ";
		for (int i = 0; i < nodes; i++)
		{
			if (i > 10) cout << " ";
			else cout << "  ";
			cout << i;
		}
		cout << "\n" << endl;
		for (int i = 0; i < nodes; i++)
		{
			cout << i;
			if (i < 10) cout << " ";
			for (int j = 0; j < nodes; j++)
			{
				if (j > 0)
				{
					if (pointer[i][j - 1] >= 10) cout << " ";
					else cout << "  ";
				}
				else cout << "  ";
				cout << pointer[i][j];
			}
			cout << endl;
		}
	}
	_getche();
}

//Funkcja towrz�ca drzewo rozpinaj�ce dla nieskierowanego
void Matrix::spanningtree(int *visited)
{
	bool check = true;
	int created = 1;
	int node = 0;
	int children, count, temp, rr;
	visited[node] = 1;
	do
	{
		count = 0;
		children = (rand() % 2) + 2;
		do
		{
			if (created == nodes) return;
			temp = rand() % nodes;
			if (temp == (node)) continue;
			if (visited[temp] != 0) continue;
			else
			{
				pointer[node][temp] = (rand() % 99) + 1;
				visited[temp] = 1;
			}
			count++;
			created++;
		} while (count != children);
		while(true)
		{
			rr =  rand() % nodes;
			if (visited[rr] == 1)
			{
				for (int j = 1; j < nodes; j++)
				{
					if (pointer[rr][j] != 0) { check = false;  break; }
				}
				if (check) { node = rr; break; }
				else check = true;
			}
		}
	} while (created != nodes);
}

//Funkcja obs�uguj�ca algorytm Dijsktry
void Matrix::mst_Dijkstra(int start)
{
	dnch = nodes;
	dch = 0;
	notchecked = new Dijkstra[dnch];
	for (int i = 0; i < dnch; i++)
	{
		notchecked[i].index = i;
	}
	notchecked[start].distance = 0;
	do
	{
		start = relax(start);
		dnch--;
		dch++;
	} while (dnch != 0);
	display_Dijkstra();
}

//Funkcja relaksuj�ca s�siad�w
int Matrix::relax(int index)
{
	Dijkstra *temp;
	int loop;
	int fall = 0;
	int result;
	int small;
	for (int i = 0; i < dnch; i++)
	{
		if (index == notchecked[i].index)
		{
			fall = i;
			break;
		}
	}
	for (int i = 0; i < nodes; i++)
	{
		if (pointer[index][i] != 0)
		{
			for (int j = 0 ; j < dnch; j++)
			{
				if (notchecked[j].index == i)
				{
					if ((notchecked[fall].distance + pointer[index][i]) < notchecked[j].distance || notchecked[j].distance == -1)
					{
						notchecked[j].distance = notchecked[fall].distance + pointer[index][i];
						notchecked[j].prev = index;
					}
					break;
				}
			}
		}
	}
	temp = new Dijkstra[dch + 1];
	if (dch == 0) temp[0] = notchecked[fall];
	else
	{
		loop = 0;
		for (int i = 0; i < dch; i++)
		{
			temp[i] = checked[i];
			loop++;
		}
		temp[loop] = notchecked[fall];
		delete checked;
	}
	loop = 0;
	checked = temp;
	temp = new Dijkstra[dnch - 1];
	for (int i = 0; i < (dnch - 1); i++)
	{
		if (i == fall)
		{
			loop++;
			temp[i] = notchecked[loop];
		}
		else
		{
			temp[i] = notchecked[loop];
		}
		loop++;
	}
	delete notchecked;
	notchecked = temp;
	result = notchecked[0].index;
	small = 10000000;
	for (int i = 0; i < (dnch - 1); i++)
	{
		if (notchecked[i].distance != -1)
		{
			if (notchecked[i].distance < small)
			{
				result = notchecked[i].index;
				small = notchecked[i].distance;
			}
		}
	}
	return result;
}

//Funckja drukuj�ca wynik dzia�ania algorytmu Disjkstry
/*void Matrix::display_Dijkstra()
{
	system("cls");
	cout << "Checked:" << endl;
	cout << "\nDist: ";
	for (int i = 0; i < dch; i++)
	{
		cout << checked[i].distance; 
		if(checked[i].distance > 9 || checked[i].distance == -1) cout << " ";
		else cout << "  ";
	}
	cout << "\nPrev: ";
	for (int i = 0; i < dch; i++)
	{
		cout << checked[i].prev;
		if (checked[i].prev > 9 || checked[i].prev == -1) cout << " ";
		else cout << "  ";
	}
	cout << "\nInde: ";
	for (int i = 0; i < dch; i++)
	{
		cout << checked[i].index;
		if (checked[i].index > 9 || checked[i].index == -1) cout << " ";
		else cout << "  ";
	}
	_getche();
}*/