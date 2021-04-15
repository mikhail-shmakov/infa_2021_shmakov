#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct TreeNode // структура узлов дерева
{
	int key;
	unsigned char height;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int k)
	{
		key = k; left = right = NULL; height = 1;
	}
};

unsigned char height(TreeNode* p) //  высота дерева p (0, если NULL)
{
	return p ? p->height : 0;
}

int bFactor(TreeNode* p) // разность высот правого и левого поддеревьев
{
	return height(p->right) - height(p->left);
}

void fixHeight(TreeNode* p) // устанавливает правильную высоту дерева с корнем p
{
	p->height = (height(p->left) > height(p->right) ? height(p->left) : height(p->right)) + 1;
}

TreeNode* rotateRight(TreeNode* p) // правый поворот вокруг p
{
	TreeNode* q = p->left;
	p->left = q->right;
	q->right = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}

TreeNode* rotateLeft(TreeNode* p) // левый поворот вокруг p
{
	TreeNode* q = p->right;
	p->right = q->left;
	q->left = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}

TreeNode* balance(TreeNode* p) // балансировка узла p
{
	fixHeight(p);
	if (bFactor(p) == 2) { // нужно вращение узла p
		if (bFactor(p->right) < 0) { // нужно большое вращение узла p, иначе малое
			p->right = rotateRight(p->right);
		}
		return rotateLeft(p);
	}
	if (bFactor(p) == -2) { // нужно вращение узла p
		if (bFactor(p->left) > 0) { // нужно большое вращение узла p, иначе малое
			p->left = rotateLeft(p->left);
		}
		return rotateRight(p);
	}
	return p; // вращение (балансировка) не нужна
}

TreeNode* insert(TreeNode* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) { // когда дошли до места где должен быть k, то создаём узел
		return new TreeNode(k);
	}
	if (k < p->key) {
		p->left = insert(p->left, k);
	}
	else {
		p->right = insert(p->right, k);
	}
	return balance(p);
}

TreeNode* findMin(TreeNode* p) // поиск узла с минимальным ключом в дереве p (самый левый)
{
	return p->left ? findMin(p->left) : p;
}

TreeNode* removeMin(TreeNode* p) // удаление узла с минимальным ключом из дерева p (самый левый)
{
	if (p->left == NULL) {
		return p->right;
	}
	p->left = removeMin(p->left);
	return balance(p);
}

TreeNode* remove(TreeNode* p, int k) // удаление ключа k из дерева p
{
	if (!p) {
		return 0;
	}
	if (k < p->key) {
		p->left = remove(p->left, k);
	} else if (k > p->key) {
		p->right = remove(p->right, k);
	} else { // находим нужный узел
		TreeNode* l = p->left;
		TreeNode* r = p->right;
		delete p;
		if (!r) { // если не правого поддерева
			return l;
		}
		TreeNode* min = findMin(r); // если есть то делаем замену
		min->right = removeMin(r);
		min->left = l;
		return balance(min);
	}
	return balance(p);
}

bool search(TreeNode* p, int k) // поиск элемента с ключом k
{
	if (!p) {
		return false;
	}
	if (k < p->key) {
		search(p->left, k);
	}
	else if (k > p->key) {
		search(p->right, k);
	}
	else {
		return true;
	}
}

void graphCheck(vector<pair<int, int>>* v, TreeNode* p) // перебор всего графа с записью узлов в вектор для записи в .dot 
{
	if (p->left) {
		pair<int, int> temp;
		temp.first = p->key;
		temp.second = p->left->key;
		v->push_back(temp);
		graphCheck(v, p->left);
	}

	if (p->right) {
		pair<int, int> temp;
		temp.first = p->key;
		temp.second = p->right->key;
		v->push_back(temp);
		graphCheck(v, p->right);
	}
}

void writeDot(string fname, vector<pair<int, int>> v) //  для записи в .dot можно визуализировать на http://www.webgraphviz.com/
{
	ofstream out("dot files/" + fname, ios::app);
	out << "digraph {\n";
	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i].first < v[i].second) {
			out << v[i].first << " -> " << v[i].second << " [label=r] " << ";\n";
		} else if ((v[i].first > v[i].second)) {
			out << v[i].first << " -> " << v[i].second << " [label=l] " << ";\n";
		}
	}
	out << "}\n";
}

int progressBar(int now, int total) // прогресс бар
{
	if (total <= 0.0) {
		return 0;
	}

	double percent_now = (double)now / (double)total;
	double progress = round(percent_now * 10000) / 10000 * 100;

	cout << "Done: " << progress << " %\r";
	cout.flush();
	return 0;
}

void writeToFile(string input, string file_name) // запись в файл
{
	ofstream out("calculations/" + file_name + ".txt", ios::app);
	if (out.is_open()) {
		out << input;
	}
	out.close();
}

int main()
{
	vector<pair<int, int>> graph_pairs; // вектор с парами: this->key, right(left)->key
	vector<pair<int, int>> graph_pairs_delete; // вектор после удаления с парами: this->key, right(left)->key
	vector<int> keys; // вектор с ключами (нужно, чтобы рандомно выбирать ключ и делать поиск(удалять узел))

	auto start = high_resolution_clock::now(); // таймер
	auto end = high_resolution_clock::now(); // таймер

	ofstream ofs;
	ofs.open("calculations/graphInsert.txt", ofstream::out | ofstream::trunc);
	ofs.close();

	ofs.open("calculations/graphSearch.txt", ofstream::out | ofstream::trunc);
	ofs.close();

	ofs.open("calculations/graphRemove.txt", ofstream::out | ofstream::trunc);
	ofs.close();

	// пример для построения картинки
	TreeNode* root1 = NULL;

	for (int i = 0; i < 20; ++i)
	{
		int paste = rand() % (20 * 2) + 1; // рандомное число от 1 до count * 2
		if (!search(root1, paste)) {
			root1 = insert(root1, paste);
		}
	}

	graphCheck(&graph_pairs, root1);
	writeDot("graph.dot", graph_pairs);

	for (int i = 0; i < 10; ++i)
	{
		int del = rand() % (10 * 2) + 1; // рандомное число от 1 до 20
		if (search(root1, del)) {
			root1 = remove(root1, del);
		}
	}

	graphCheck(&graph_pairs_delete, root1);
	writeDot("graph_delete.dot", graph_pairs_delete);

	cout << "Graph for picture done" << endl;

	int count = 10000; // сколько элементов обсчитывать

	TreeNode* root2 = NULL;

	while (keys.size() < count)
	{
		int paste = rand() % (count * 2) + 1; // рандомное число от 1 до count * 2
		if (!search(root2, paste)) {
			start = high_resolution_clock::now();
			root2 = insert(root2, paste);
			end = high_resolution_clock::now();
			keys.push_back(paste); // заполняем вектор ключами
			writeToFile(to_string(keys.size()) + " " + to_string(duration_cast<nanoseconds>(end - start).count()) + "\n", "graphInsert");
		}
		progressBar(keys.size(), count);
	}
	cout << "graphInsert done, count = " << count << endl;

	for (int i = 0; i < count; ++i)
	{
		int tKeyPos = rand() % keys.size(); // позиция ключа
		int tKey = keys[tKeyPos]; // выбираем ключ по которому будем удалять (перед этим искать)
		start = high_resolution_clock::now();
		search(root2, tKey);
		end = high_resolution_clock::now();
		writeToFile(to_string(keys.size()) + " " + to_string(duration_cast<nanoseconds>(end - start).count()) + "\n", "graphSearch");
		
		start = high_resolution_clock::now();
		root2 = remove(root2, tKey);
		end = high_resolution_clock::now();
		writeToFile(to_string(keys.size()) + " " + to_string(duration_cast<nanoseconds>(end - start).count()) + "\n", "graphRemove");

		progressBar(i, count);

		keys.erase(keys.begin() + tKeyPos);
	}
	cout << "graphSearch, graphRemove, count = " << count << endl;
}

