#include <iostream>
using namespace std;

struct Vertex {
	using DataType = int;
	DataType data;
	struct Vertex* left = nullptr;
	struct Vertex* right = nullptr;
};

int getRand(int from, int to) {
	int data = std::rand() % (to - from);
	return data;
}

void setVertex(Vertex* &vertex) {
	vertex = new Vertex{
		.data = getRand(10, 99),
		.left = nullptr,
		.right = nullptr
	};
}

void printTree(Vertex* vertex) {
	Vertex* root = vertex;
	std::cout << vertex->data << std::endl;
	std::cout << "| \\" << std::endl;

	std::cout << root->left->data << ' ';
	std::cout << root->right->data << std::endl;
	std::cout << "   |" << std::endl;

	std::cout << "   ";
	vertex = root->right->left;
	std::cout << vertex->data << std::endl;
	cout << "   | \\" << endl;

	std::cout << "   ";
	std::cout << vertex->left->data << ' ';
	std::cout << vertex->right->data << std::endl;
	return;
}

int sdp(Vertex*, int); // Вычисление средней высоты
int getSum(Vertex*); // Вычисление контрольной суммы
void traverseFromLeft(Vertex* root); // обход слева (печать дерева)
int getSize(Vertex*);
int getMax(int, int);
int getHeight(Vertex*);


int main()
{
	setlocale(LC_ALL, "rus");
	Vertex* root = nullptr;
	Vertex* point = nullptr;

	setVertex(root);

	point = root;
	setVertex(point->left);
	setVertex(point->right);

	point = root->right;
	setVertex(point->left);

	point = point->left;
	setVertex(point->left);
	setVertex(point->right);

	printTree(root);
	cout << "Обход слева на право: ";
	traverseFromLeft(root);
	cout << endl;

	cout << "Размер дерева: " << getSize(root) << endl;
	cout << "Высота дерева: " << getHeight(root) << endl;
	cout << "Средняя высота дерева: " << sdp(root, 1) / getSize(root) << endl;
	cout << "Контрольная сумма дерева: " << getSum(root) << endl;

	return 0;
}

int getSize(Vertex* x) {
	if (!x) return 0;
	return 1 + getSize(x->left) + getSize(x->right);
}

int getMax(int x, int y) {
	if (x > y) return x;
	return y;
}

int getHeight(Vertex* x) {
	if (!x) return 0;
	return 1 + getMax(getHeight(x->left), getHeight(x->right));
}

int sdp(Vertex* x, int l) {
	if (!x) return 0;
	return l + sdp(x->left, l + 1) + sdp(x->right, l + 1);
}

int getSum(Vertex* x) {
	if (!x) return 0;
	return x->data + getSum(x->left) + getSum(x->right);
}

void traverseFromLeft(Vertex* vertex) {
	if (!vertex) return;
	traverseFromLeft(vertex->left);
	cout << vertex->data << ' ';
	traverseFromLeft(vertex->right);
	return;
}
