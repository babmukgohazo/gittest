#include <iostream>
#include "Tree.h"
using namespace std;


int main() {
	cout << "예시 1" << endl;
	QTreeNode* node = new QTreeNode;
	QTreeNode* newNode;
	QWidgetTree tree(node);			//아주 주의해야 할 점: 트리에 들어가는 모든 원소는 메모리의 힙상에 있어야 함. >> delete 사용 할 것이기 때문
	tree.currentNode = tree.top;	//노드를 추가할 위치를 top으로 설정
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
	cout << tree.top->low[0]->right->left->right->right->data << endl; //100, 수평 링크 확인
	cout << tree.top->low[1]->high->low[2]->data << endl;	//100, 수직 링크확인
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
	cout << tree.top->low[2]->low[0]->right->left->high->low[1]->right->data << endl;	// 3000, 링크 확인
	cout << endl;

	// 예시1. tree를 생성하고 top을 설정한 뒤 top node에 세 개의 하위 node를 추가하였다.
	//		그리고 하위 노드 하나에 또 추가로 세 개의 하위 노드를 추가하였다.

	cout << "예시 2" << endl;
	QWidgetList list;
	newNode = new QTreeNode;
	newNode->data = 1;
	list.add(newNode);
	newNode = new QTreeNode;
	newNode->data = 2;
	list.add(newNode);
	newNode = new QTreeNode;
	newNode->data = 3;
	list.add(newNode);		//tree의 노드를 추가한다.
	cout << list.head->data << endl;	// 1
	cout << list.head->next->data << endl;	// 2
	cout << list.head->next->next->data << endl;	// 3
	cout << endl;
	
	// 예시2. list를 생성하고 세 개의 노드를 추가한 뒤 출력한다.

	cout << "예시 3" << endl;
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

	// 예시3. 넣었던 노드를 세 개 꺼내고, 다시 같은 세 개 노드를 추가한 뒤 노드의 수를 확인한다.

	cout << "예시 4" << endl;
	cout << tree.count << endl;		// 7
	tree.currentNode = tree.top->low[0];	//한 개 삭제
	tree.remove();
	cout << tree.count << endl;		// 6
	cout << tree.top->low[1]->data << endl;		// 100	세 번째 데이터가 앞의 데이터 삭제로 두 번째 데이터가 되었다.
	cout << tree.top->low[0]->right->left->data << endl;	// 10	데이터 삭제 후 링킹이 다시 이루어졌다.
	cout << tree.top->low[1]->low[2]->data << endl;		// 1000	하위 트리도 잘 따라다닌다.
	tree.currentNode = tree.top->low[1];
	tree.remove();
	cout << tree.count << endl;		// 2 currentNode 한 개와, 그의 하위노드 3개를 제거
	cout << tree.top->low[0]->next << endl;	//00000000 정상적으로 끊겼음을 알 수 있다.
	tree.currentNode = tree.top;
	tree.remove();
	cout << tree.count << endl;		// 0 tree를 모두 비웠으므로, 0이 출력된다.
	cout << endl;

	// 예시4. tree의 remove를 사용, tree를 비우고 노드의 수 확인.

	cout << "예시 5" << endl;
	newNode = new QTreeNode;
	tree.setTop(newNode);
	tree.currentNode = tree.top;	//노드를 추가할 위치를 top으로 설정
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
	cout << tree.top->low[0]->right->left->right->right->data << endl; //100, 수평 링크 확인
	cout << tree.top->low[1]->high->low[2]->data << endl;	//100, 수직 링크확인
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
	cout << tree.top->low[2]->low[0]->right->left->high->low[1]->right->data << endl;	// 3000, 링크 확인
	cout << endl;

	// 예시5. tree를 다시 생성한다. 위의 코드와 동일하다.

	cout << "예시 6" << endl;
	tree.search(1000);		// 1000을 찾는다.
	cout << tree.searchedNodeList.head->data << endl; // 1000	찾은 항목을 저장하는 리스트에서 꺼내서 본다.
	tree.searchedNodeList.flushList();	//한 번 search하고 나면 list를 비워야 한다.
	tree.search(2000);
	cout << tree.searchedNodeList.head->data << endl; // 2000
	tree.searchedNodeList.flushList();// 리스트를 비운다.
	cout << tree.searchedNodeList.count << endl;	// 0
	tree.search(-1);	// 없는 값
	cout << tree.searchedNodeList.count << endl; // 0
	tree.searchedNodeList.flushList();	// 필요 없는 flush이긴 하지만, search다음에는 꼭 flush가 와야 한다는 의미에서 추가했다.
	tree.top->low[1]->data = tree.top->low[2]->data;	//같은 값을 세 개 설정한다.
	tree.top->low[0]->data = tree.top->low[2]->data;
	tree.search(tree.top->low[2]->data);
	cout << tree.searchedNodeList.count << endl;	// 3
	cout << tree.searchedNodeList.head->data << endl;	// 100
	cout << tree.searchedNodeList.head->next->data << endl;
	cout << tree.searchedNodeList.head->next->next->data << endl;	//모두 같은 값이 출력된다.
	tree.searchedNodeList.flushList();
	cout << tree.searchedNodeList.count << endl;	// 0	flush가 수행되었다.

	// 예시6. search를 다뤄본다.

	return 0;
}
