#pragma once

//��ü�� ���ø����� ����� ���� �� ���⵵ �ѵ� ���߿� �����غ��ô�.
//���� �����ؾ� �� ��: Ʈ���� ���� ��� ���Ҵ� �޸��� ���� �־�� ��. >> delete ��� �� ���̱� ����
//������ ���� ���� ��쿡 ���� ������ ������, �������� ���� ��찡 ���� �� �ֽ��ϴ�. ������ ������ �߻��� ��� �߻��� ��Ȳ�� �����Ͽ� �ֽø� �����ϰڽ��ϴ�.

class QNode {
public:
	QNode(){
		data = 0;
	}

	int data;	//QWidget�� �� �ڸ�. �켱�� tree ������ ���� ���������� �ϰ� ���߿� �ʿ��� ������ �߰�
};

class QTreeNode : public QNode{		//QNode�� tree�� ���� �� ����
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

	//���콺�� ��ü�� Ŭ���Ǹ� this�� tree class�� �����Ͽ� currentNode ���� ������ �ʿ�

	int lowCount;	//low�迭�� ũ���̴�.
	int index;		//������忡�� Node�� �� �� ��ġ. ó���� 0�̴�.
	QTreeNode** low;
	QTreeNode* high;
	QTreeNode* right;
	QTreeNode* left;
	QTreeNode* next;	//search�� delete�� ������ ����Ʈ�� ��ũ����
	//������ level�� ������Ʈ�� �����Ѵ�.
	// search�� �� ����� ������...
};

class QWidgetList {			//���� ���� ���� ��õ�մϴ�. ť�� ���� ����� �� �浹�� ���ɼ��� �ֽ��ϴ�. ������ �����Ҷ��� ����� �ּ���.
public:						//1. tree�� ���� ���� QTreeNode�� ����� ��
	QWidgetList() {			//2. list�� ��� �� ť�� ����ϱ� ���� list�� ��� broach�� ��� ������.
		head = '\0';		//3. list�� ��� �� ��� QTreeNode�� next�� null�� �����.	flushList�� ����Ͽ� ����Ʈ�� ���� next�� null�� �ڵ� �ʱ�ȭ �ȴ�.
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
			return 0;		//add�� �̷������ �ʾҴٴ� �ǹ�
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
			return 0;		//add�� �̷������ �ʾҴٴ� �ǹ�(���� ���� ���)
		for (i = 0;i < arraySize;i++) {
			add(addNodeArray[i]);
			setTail();
		}
		return 1;
	}

	QTreeNode* broachByIndex(int index) {		//index�� �޾� �ش��ϴ� �κ��� �����ϰ� �ٽ� ��ŷ�Ѵ�.
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
			broachedNode->next = '\0';	//�������Ƿ�, ��ũ�� ���´�.
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
		broachedNode->next = '\0';	//�������Ƿ�, ��ũ�� ���´�.
		return broachedNode;
	}

	void flushList() {		//tree���� search�� �� �� �ϰ� ���� flush�� �� ���� ��õ�Ѵ�. �׷��� ������ �ٸ� list������ ����� �� �浹�� �߻��Ѵ�.
		while (count != 0)
			broachByIndex(0);
	}

	void removeByIndex(int index) {		//����� ���� ������ ���� ���� ���� �����ϰ� ��õ. Ȥ�� tree�� node�� ������ ���� ����.
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

	void inQueue(QTreeNode* inQuNode) {	//���� ��尡 NULL�̸� inQueue���� �ʴ´�.
		this->add(inQuNode);
	}

	void inQueue(QTreeNode** nodeArray, int arraySize) {	//�迭�� inQueue�� ���� �ִ�. �迭�� ������� inQueue���� �ʴ´�.
		this->add(nodeArray, arraySize);
	}
	
	QTreeNode* deQueue() {		//ť�� ������� NULL�� ��ȯ�Ѵ�.
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
		currentNode = top;	//ù ������ currentNode�� top�̴�.
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

	void arrCopy(QTreeNode** to, QTreeNode** from, int toSize, int index) {	//�迭�� �ܼ� ����� ���� ���縦 ������. index�� -1�̸� �ܼ�����, �ƴϸ� index�� �ش��ϴ� ���� ���� ����
		int i, j;												//index�� from���� ����� �����̴�.
		if (to == '\0' || from == '\0')		//�迭 �����Ͱ� NULL�� ���¿��� �����ϸ� �ȵȴ�.
			exit(1);
		if (index == -1) {
			for (i = 0;i < toSize - 1;i++)	//���� to���� from�� ���� �Ѱ��� ����. ������ -1����.
				to[i] = from[i];
		}
		else{	//index�� �ش��ϴ� ���Ҹ� �ϳ��� �� ����.
			for (i = 0, j=0;i < toSize;i++) {	//���� to���� from�� ���� �Ѱ��� �� ����. �׸��� from���� �� ���� ���Ҹ� ���ְ� to�� �ִ´�. ���� ���� ���� ���� ����. - ȣ���ϴ� �κ��� �ڵ带 ���� ���ؿ� ������ ��
				if (index != i) {
					to[j] = from[i];	//from���� index �ϳ� ���� to�� ����.
					to[j]->index = j;	//index�� �Ұŵ� ���� �ڷ� 1�� �и��Ƿ�, �缳��.
					j++;
				}
				else
					continue;
			}
		}
	}

	void addLowNode(QTreeNode* addNode) {		//Ʈ���� Ư�� ��忡 ������� �߰�
		currentNode->lowCount++;
		addTemp = currentNode->low;
		currentNode->low = new QTreeNode*[currentNode->lowCount];	//�� ĭ �� ū �迭 ����
		count++;
		if (addTemp != '\0') {
			this->arrCopy(currentNode->low, addTemp, currentNode->lowCount, -1);
			delete[] addTemp;
		}
		currentNode->low[currentNode->lowCount - 1] = addNode;	//�Ʒ��� ����
		addNode->high = currentNode;	//���ε� ����
		if (currentNode->lowCount >= 2) {		//�ι�° ������ ��尣 ������ �ʿ�.
			addNode->left = currentNode->low[currentNode->lowCount - 2];
			currentNode->low[currentNode->lowCount - 2]->right = addNode;	//���� ��� ���� �� ������ ����
		}
		addNode->index = currentNode->lowCount - 1;	//index�� ����
	}

	void linkLowNode() {	//low Node�� ����Ʈ�� �翬���մϴ�. sorting�� ���˴ϴ�. �迭�� sort�ϰ� lownode�� �ٽ� link�մϴ�.��

	}

	void sort() {		//sorting

	}

	void remove() {		//Ư�� ���� Ʈ��(��ü)�� ����. currentNode�� ����� Ʈ���� ���ŵ�. BFS �˰������� ����.
		QTreeNode* removeTemp;
		QTreeNode** arrayTemp;
		if (currentNode->left != '\0')		//currentNode�� �����ϱ� ���� low������ ���� ����� ���� ��忡���� �迭�� �ٲ�� �Ѵ�.
			currentNode->left->right = currentNode->right;
		if (currentNode->right != '\0')
			currentNode->right->left = currentNode->left;
		if (currentNode->high != '\0') {
			arrayTemp = currentNode->high->low;
			currentNode->high->low = new QTreeNode*[currentNode->high->lowCount - 1];	//current Node�� �迭���� �����ϴ� ����. ���Ҹ� �ϳ� ���δ�.
			this->arrCopy(currentNode->high->low, arrayTemp, currentNode->high->lowCount, currentNode->index);
			currentNode->high->lowCount--;

			//���� ����� low�迭���� currentNode�� �����Ѵ�. �̷��� �Ǹ� currentNode�� �������� ������ tree�� �������� �ȴ�.
		}
		else
			top = '\0';
		queue.inQueue(currentNode);		//���� Ʈ���� ť�� ��� �����ϰ� �����ع�����.
		do {
			removeTemp = queue.deQueue();
			if (removeTemp == '\0')
				break;
			queue.inQueue(removeTemp->low, removeTemp->lowCount);
			count--;
			delete removeTemp;
		} while (1);
	}

	void search(int data) {		//Ʈ���� ť�� Ǯ�鼭 Ž��. BFS����. ȸ�ΰ� �����Ƿ� BFS ������ ����ϴ�.
		QTreeNode* searchTemp;
		queue.inQueue(top);		//top���� �����Ѵ�.
		do {
			searchTemp = queue.deQueue();
			if (searchTemp == '\0')
				break;
			queue.inQueue(searchTemp->low, searchTemp->lowCount);
			if (searchTemp->data == data)
				searchedNodeList.add(searchTemp);
		} while (1);
	}

	QWidgetQueue queue;		//search�� remove�� ���� ť
	QWidgetList searchedNodeList;		//search���� ã�� ������ ������ ����Ʈ
	QTreeNode* currentNode;	//���� �߰�/���� ����� �Ͼ ����̴�. �̺�Ʈ �߻��� �����ؾ� �Ѵ�.
	QTreeNode** addTemp;
	QTreeNode* top;
	int count;
};