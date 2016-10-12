#pragma once

//전체를 템플릿으로 만들면 좋을 것 같기도 한데 나중에 논의해봅시다.
//아주 주의해야 할 점: 트리에 들어가는 모든 원소는 메모리의 힙상에 있어야 함. >> delete 사용 할 것이기 때문
//오류를 나름 많은 경우에 대해 검증해 봤지만, 생각하지 못한 경우가 있을 수 있습니다. 때문에 오류가 발생할 경우 발생한 상황을 정리하여 주시면 감사하겠습니다.

class QNode {
public:
	QNode(){
		data = 0;
	}

	int data;	//QWidget이 들어갈 자리. 우선은 tree 제작을 위해 정수형으로 하고 나중에 필요한 데이터 추가
};

class QTreeNode : public QNode{		//QNode로 tree를 만들 때 원소
public:
	QTreeNode() : QNode(){
		lowCount = 0;
		index = 0;
		low = '\0';
		high = '\0';
		right = '\0';
		left = '\0';
		next = '\0';
	}

	~QTreeNode() {}

	//마우스로 객체가 클릭되면 this를 tree class로 전달하여 currentNode 갱신 과정이 필요

	int lowCount;	//low배열의 크기이다.
	int index;		//상위노드에서 Node를 볼 때 위치. 처음이 0이다.
	QTreeNode** low;
	QTreeNode* high;
	QTreeNode* right;
	QTreeNode* left;
	QTreeNode* next;	//search와 delete를 수행할 리스트의 링크변수
	//동일한 level간 더블리스트로 연결한다.
	// search할 때 사용할 포인터...
};

class QWidgetList {			//쓰지 않을 것을 추천합니다. 큐와 같이 사용할 때 충돌할 가능성이 있습니다. 다음을 만족할때만 사용해 주세요.
public:						//1. tree와 관련 없는 QTreeNode를 사용할 때
	QWidgetList() {			//2. list를 사용 후 큐를 사용하기 전에 list를 모두 broach로 모두 빼낸다.
		head = '\0';		//3. list를 사용 후 모든 QTreeNode의 next를 null로 만든다.	flushList를 사용하여 리스트를 비우면 next가 null로 자동 초기화 된다.
		tail = '\0';
		count = 0;
	}

	~QWidgetList() {}

	void setTail() {
		int i;
		tail = head;
		for (i = 0;i < count - 1;i++)
			tail = tail->next;
	}

	int add(QTreeNode* addNode) {
		if (addNode == '\0')
			return 0;		//add가 이루어지지 않았다는 의미
		if (head == '\0')
			head = addNode;
		else
			tail->next = addNode;
		count++;
		setTail();
		return 1;
	}

	int add(QTreeNode** addNodeArray, int arraySize) {
		int i;
		if (arraySize == 0)
			return 0;		//add가 이루어지지 않았다는 의미(넣을 것이 없어서)
		for (i = 0;i < arraySize;i++) {
			add(addNodeArray[i]);
			setTail();
		}
		return 1;
	}

	QTreeNode* broachByIndex(int index) {		//index를 받아 해당하는 부분을 삭제하고 다시 링킹한다.
		QTreeNode* broachedNode;
		QTreeNode* tempNode;
		int i;
		broachedNode = head;
		if (index >= count || index < 0)
			return '\0';
		if (index == 0) {
			head = head->next;
			count--;
			setTail();
			broachedNode->next = '\0';	//빼냈으므로, 링크를 끊는다.
			return broachedNode;
		}
		for (i = 0;i < index;i++) {
			broachedNode = broachedNode->next;
			if (i == 0)
				tempNode = head;
			else
				tempNode = tempNode->next;
		}
		tempNode->next = broachedNode->next;
		count--;
		setTail();
		broachedNode->next = '\0';	//빼냈으므로, 링크를 끊는다.
		return broachedNode;
	}

	void flushList() {		//tree에서 search를 한 번 하고 나면 flush를 할 것을 추천한다. 그러지 않으면 다른 list구조를 사용할 때 충돌이 발생한다.
		while (count != 0)
			broachByIndex(0);
	}

	void removeByIndex(int index) {		//만들어 놓긴 했지만 쓰지 않을 것을 강력하게 추천. 혹여 tree의 node를 삭제할 수도 있음.
		QTreeNode* tempNode;
		tempNode = broachByIndex(index);
		if (tempNode == '\0')
			return;
		else
			delete tempNode;
	}

	QTreeNode* head;
	QTreeNode* tail;
	int count;
};

class QWidgetQueue : public QWidgetList {
public:
	QWidgetQueue() : QWidgetList() {}

	~QWidgetQueue() {}

	void inQueue(QTreeNode* inQuNode) {	//받은 노드가 NULL이면 inQueue하지 않는다.
		this->add(inQuNode);
	}

	void inQueue(QTreeNode** nodeArray, int arraySize) {	//배열로 inQueue할 수도 있다. 배열이 비었으면 inQueue하지 않는다.
		this->add(nodeArray, arraySize);
	}
	
	QTreeNode* deQueue() {		//큐가 비었으면 NULL을 반환한다.
		return this->broachByIndex(0);
	}
};

class QWidgetTree {
public:
	QWidgetTree(){
		currentNode = '\0';
		addTemp = '\0';
		top = '\0';
		count = 0;
	}
	QWidgetTree(QTreeNode* inputNode) {
		addTemp = '\0';
		top = inputNode;
		currentNode = top;	//첫 생성시 currentNode는 top이다.
		count = 1;
	}
	~QWidgetTree() {

	}

	void setTop() {
		top = new QTreeNode;
		count++;
	}

	void setTop(QTreeNode* tempNode) {
		top = tempNode;
		count++;
	}

	void arrCopy(QTreeNode** to, QTreeNode** from, int toSize, int index) {	//배열의 단순 복사와 삭제 복사를 나눈다. index가 -1이면 단순복사, 아니면 index에 해당하는 원소 삭제 복사
		int i, j;												//index는 from에서 사라질 원소이다.
		if (to == '\0' || from == '\0')		//배열 포인터가 NULL인 상태에서 접근하면 안된다.
			exit(1);
		if (index == -1) {
			for (i = 0;i < toSize - 1;i++)	//현재 to보다 from이 원소 한개가 적다. 때문에 -1해줌.
				to[i] = from[i];
		}
		else{	//index에 해당하는 원소를 하나만 뺄 예정.
			for (i = 0, j=0;i < toSize;i++) {	//현재 to보다 from이 원소 한개가 더 많다. 그리고 from에서 한 개의 원소를 없애고 to에 넣는다. 따라서 오류 없이 복사 가능. - 호출하는 부분의 코드를 보면 이해에 도움이 됨
				if (index != i) {
					to[j] = from[i];	//from에서 index 하나 빼고 to에 대입.
					to[j]->index = j;	//index가 소거된 원소 뒤로 1씩 밀리므로, 재설정.
					j++;
				}
				else
					continue;
			}
		}
	}

	void addLowNode(QTreeNode* addNode) {		//트리의 특정 노드에 하위노드 추가
		currentNode->lowCount++;
		addTemp = currentNode->low;
		currentNode->low = new QTreeNode*[currentNode->lowCount];	//한 칸 더 큰 배열 생성
		count++;
		if (addTemp != '\0') {
			this->arrCopy(currentNode->low, addTemp, currentNode->lowCount, -1);
			delete[] addTemp;
		}
		currentNode->low[currentNode->lowCount - 1] = addNode;	//아레로 연결
		addNode->high = currentNode;	//위로도 연결
		if (currentNode->lowCount >= 2) {		//두번째 노드부터 노드간 연결이 필요.
			addNode->left = currentNode->low[currentNode->lowCount - 2];
			currentNode->low[currentNode->lowCount - 2]->right = addNode;	//하위 노드 간에 양 옆으로 연결
		}
		addNode->index = currentNode->lowCount - 1;	//index를 갱신
	}

	void linkLowNode() {	//low Node를 리스트로 재연결합니다. sorting에 사용됩니다. 배열을 sort하고 lownode를 다시 link합니다.ㅣ

	}

	void sort() {		//sorting

	}

	void remove() {		//특정 하위 트리(전체)를 제거. currentNode에 연결된 트리가 제거됨. BFS 알고리즘으로 구현.
		QTreeNode* removeTemp;
		QTreeNode** arrayTemp;
		if (currentNode->left != '\0')		//currentNode를 제거하기 전에 low에서의 연결 관계와 상위 노드에서의 배열을 바꿔야 한다.
			currentNode->left->right = currentNode->right;
		if (currentNode->right != '\0')
			currentNode->right->left = currentNode->left;
		if (currentNode->high != '\0') {
			arrayTemp = currentNode->high->low;
			currentNode->high->low = new QTreeNode*[currentNode->high->lowCount - 1];	//current Node를 배열에서 제거하는 과정. 원소를 하나 줄인다.
			this->arrCopy(currentNode->high->low, arrayTemp, currentNode->high->lowCount, currentNode->index);
			currentNode->high->lowCount--;

			//상위 노드의 low배열에서 currentNode를 삭제한다. 이렇게 되면 currentNode를 정상으로 가지는 tree는 독립적이 된다.
		}
		else
			top = '\0';
		queue.inQueue(currentNode);		//하위 트리를 큐에 모두 적제하고 삭제해버린다.
		do {
			removeTemp = queue.deQueue();
			if (removeTemp == '\0')
				break;
			queue.inQueue(removeTemp->low, removeTemp->lowCount);
			count--;
			delete removeTemp;
		} while (1);
	}

	void search(int data) {		//트리를 큐로 풀면서 탐색. BFS구현. 회로가 없으므로 BFS 구현이 깔끔하다.
		QTreeNode* searchTemp;
		queue.inQueue(top);		//top부터 시작한다.
		do {
			searchTemp = queue.deQueue();
			if (searchTemp == '\0')
				break;
			queue.inQueue(searchTemp->low, searchTemp->lowCount);
			if (searchTemp->data == data)
				searchedNodeList.add(searchTemp);
		} while (1);
	}

	QWidgetQueue queue;		//search와 remove를 위한 큐
	QWidgetList searchedNodeList;		//search에서 찾은 노드들을 저장할 리스트
	QTreeNode* currentNode;	//현제 추가/삭제 명령이 일어난 노드이다. 이벤트 발생시 갱신해야 한다.
	QTreeNode** addTemp;
	QTreeNode* top;
	int count;
};