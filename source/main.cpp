#include <iostream>
#include "Tree.h"
using namespace std;


int main() {
	cout << "���� 1" << endl;
	QTreeNode* node = new QTreeNode;
	QTreeNode* newNode;
	QWidgetTree tree(node);			//���� �����ؾ� �� ��: Ʈ���� ���� ��� ���Ҵ� �޸��� ���� �־�� ��. >> delete ��� �� ���̱� ����
	tree.currentNode = tree.top;	//��带 �߰��� ��ġ�� top���� ����
	newNode = new QTreeNode;
	newNode->data = 1;
	tree.addLowNode(newNode);
	newNode = new QTreeNode;
	newNode->data = 10;
	tree.addLowNode(newNode);
	newNode = new QTreeNode;
	newNode->data = 100;
	tree.addLowNode(newNode);
	cout << tree.currentNode->low[0]->data << endl;	// 1
	cout << tree.currentNode->low[1]->data << endl;	// 10
	cout << tree.currentNode->low[2]->data << endl;	// 100
	cout << tree.top->low[0]->right->left->right->right->data << endl; //100, ���� ��ũ Ȯ��
	cout << tree.top->low[1]->high->low[2]->data << endl;	//100, ���� ��ũȮ��
	cout << endl;
	tree.currentNode = tree.top->low[2];
	newNode = new QTreeNode;
	newNode->data = 1000;
	tree.addLowNode(newNode);
	newNode = new QTreeNode;
	newNode->data = 2000;
	tree.addLowNode(newNode);
	newNode = new QTreeNode;
	newNode->data = 3000;
	tree.addLowNode(newNode);
	cout << tree.top->low[2]->low[0]->data << endl;	// 1000
	cout << tree.top->low[2]->low[1]->data << endl;	// 2000
	cout << tree.top->low[2]->low[2]->data << endl;	// 3000
	cout << tree.top->low[2]->low[0]->right->left->high->low[1]->right->data << endl;	// 3000, ��ũ Ȯ��
	cout << endl;

	// ����1. tree�� �����ϰ� top�� ������ �� top node�� �� ���� ���� node�� �߰��Ͽ���.
	//		�׸��� ���� ��� �ϳ��� �� �߰��� �� ���� ���� ��带 �߰��Ͽ���.

	cout << "���� 2" << endl;
	QWidgetList list;
	newNode = new QTreeNode;
	newNode->data = 1;
	list.add(newNode);
	newNode = new QTreeNode;
	newNode->data = 2;
	list.add(newNode);
	newNode = new QTreeNode;
	newNode->data = 3;
	list.add(newNode);		//tree�� ��带 �߰��Ѵ�.
	cout << list.head->data << endl;	// 1
	cout << list.head->next->data << endl;	// 2
	cout << list.head->next->next->data << endl;	// 3
	cout << endl;
	
	// ����2. list�� �����ϰ� �� ���� ��带 �߰��� �� ����Ѵ�.

	cout << "���� 3" << endl;
	list.broachByIndex(1);
	list.broachByIndex(1);
	list.broachByIndex(0);
	list.add(tree.top);
	list.add(tree.top->low[2]->low[1]);
	list.add(tree.top->low[1]);
	cout << list.head->data << endl;	// 0
	cout << list.head->next->data << endl;	// 2000
	cout << list.head->next->next->data << endl;	// 10
	cout << list.count << endl;	// 3
	list.broachByIndex(0);
	list.broachByIndex(0);
	list.broachByIndex(0);
	cout << endl;

	// ����3. �־��� ��带 �� �� ������, �ٽ� ���� �� �� ��带 �߰��� �� ����� ���� Ȯ���Ѵ�.

	cout << "���� 4" << endl;
	cout << tree.count << endl;		// 7
	tree.currentNode = tree.top->low[0];	//�� �� ����
	tree.remove();
	cout << tree.count << endl;		// 6
	cout << tree.top->low[1]->data << endl;		// 100	�� ��° �����Ͱ� ���� ������ ������ �� ��° �����Ͱ� �Ǿ���.
	cout << tree.top->low[0]->right->left->data << endl;	// 10	������ ���� �� ��ŷ�� �ٽ� �̷������.
	cout << tree.top->low[1]->low[2]->data << endl;		// 1000	���� Ʈ���� �� ����ٴѴ�.
	tree.currentNode = tree.top->low[1];
	tree.remove();
	cout << tree.count << endl;		// 2 currentNode �� ����, ���� ������� 3���� ����
	cout << tree.top->low[0]->next << endl;	//00000000 ���������� �������� �� �� �ִ�.
	tree.currentNode = tree.top;
	tree.remove();
	cout << tree.count << endl;		// 0 tree�� ��� ������Ƿ�, 0�� ��µȴ�.
	cout << endl;

	// ����4. tree�� remove�� ���, tree�� ���� ����� �� Ȯ��.

	cout << "���� 5" << endl;
	newNode = new QTreeNode;
	tree.setTop(newNode);
	tree.currentNode = tree.top;	//��带 �߰��� ��ġ�� top���� ����
	newNode = new QTreeNode;
	newNode->data = 1;
	tree.addLowNode(newNode);
	newNode = new QTreeNode;
	newNode->data = 10;
	tree.addLowNode(newNode);
	newNode = new QTreeNode;
	newNode->data = 100;
	tree.addLowNode(newNode);
	cout << tree.currentNode->low[0]->data << endl;	// 1
	cout << tree.currentNode->low[1]->data << endl;	// 10
	cout << tree.currentNode->low[2]->data << endl;	// 100
	cout << tree.top->low[0]->right->left->right->right->data << endl; //100, ���� ��ũ Ȯ��
	cout << tree.top->low[1]->high->low[2]->data << endl;	//100, ���� ��ũȮ��
	cout << endl;
	tree.currentNode = tree.top->low[2];
	newNode = new QTreeNode;
	newNode->data = 1000;
	tree.addLowNode(newNode);
	newNode = new QTreeNode;
	newNode->data = 2000;
	tree.addLowNode(newNode);
	newNode = new QTreeNode;
	newNode->data = 3000;
	tree.addLowNode(newNode);
	cout << tree.top->low[2]->low[0]->data << endl;	// 1000
	cout << tree.top->low[2]->low[1]->data << endl;	// 2000
	cout << tree.top->low[2]->low[2]->data << endl;	// 3000
	cout << tree.top->low[2]->low[0]->right->left->high->low[1]->right->data << endl;	// 3000, ��ũ Ȯ��
	cout << endl;

	// ����5. tree�� �ٽ� �����Ѵ�. ���� �ڵ�� �����ϴ�.

	cout << "���� 6" << endl;
	tree.search(1000);		// 1000�� ã�´�.
	cout << tree.searchedNodeList.head->data << endl; // 1000	ã�� �׸��� �����ϴ� ����Ʈ���� ������ ����.
	tree.searchedNodeList.flushList();	//�� �� search�ϰ� ���� list�� ����� �Ѵ�.
	tree.search(2000);
	cout << tree.searchedNodeList.head->data << endl; // 2000
	tree.searchedNodeList.flushList();// ����Ʈ�� ����.
	cout << tree.searchedNodeList.count << endl;	// 0
	tree.search(-1);	// ���� ��
	cout << tree.searchedNodeList.count << endl; // 0
	tree.searchedNodeList.flushList();	// �ʿ� ���� flush�̱� ������, search�������� �� flush�� �;� �Ѵٴ� �ǹ̿��� �߰��ߴ�.
	tree.top->low[1]->data = tree.top->low[2]->data;	//���� ���� �� �� �����Ѵ�.
	tree.top->low[0]->data = tree.top->low[2]->data;
	tree.search(tree.top->low[2]->data);
	cout << tree.searchedNodeList.count << endl;	// 3
	cout << tree.searchedNodeList.head->data << endl;	// 100
	cout << tree.searchedNodeList.head->next->data << endl;
	cout << tree.searchedNodeList.head->next->next->data << endl;	//��� ���� ���� ��µȴ�.
	tree.searchedNodeList.flushList();
	cout << tree.searchedNodeList.count << endl;	// 0	flush�� ����Ǿ���.

	// ����6. search�� �ٷﺻ��.

	return 0;
}
