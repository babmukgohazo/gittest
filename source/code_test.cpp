int checkName(String name){
    int length=name.length();
    if(!(name.at(length-2)==".")&&(name.at(length-1)=="m")&&(name.at(length-1)=="d"))//.md�� ������ ������ �´��� Ȯ��
        return -1;

    Qfile file(name);
    if(!file.open(Qfile::ReadOnly))//������ ���� ���� ������
        return 0;
    return 1; //������ ���� �ϴ� ���
}

void saveFile(int newSave, String name){
    if(newSave){//�ٸ� �̸����� �����ϴ� �����
        do{
             //�̸� �޴� �Է�â ����
            cin>>name;
        }while(checkName(name)==0);//���� �̸��� ���� ���� �ʴ� ������ ���� ������ �̸� �ޱ�
    }
    Qfile *outfile;
    outfile=fopen(name,"w");
    QdataStream out(&outfile);
    Qstring str=textEdit->toPlainText();//textEdit�� �ִ� ������ ���ڿ��� ����
    out<<str; //���Ͽ� ����
}


void openFile(String name){
    Qfile file(name);//���� ����
    Qdatastream in(&file);
    Qstring str;
    in>>str;
    textEdit->setText(str); //textEditâ�� ���Ͽ� �ִ� ���� �Ѹ���
}

void makeNewFile(){
    textEdit->setText(NULL);
}

void exit(String name){
    Qfile file(name);
    Qdatastream in(&file);
    Qstring strInFile,strInEdit;
    in>>striInFile;// ������ ���Ͽ� �־��� ����
    strInEdit=textEdit->toPlainText();//textEdit â�� �ִ� ���� ����
    if(strInEdit.compare(strInFile)==0)// ���泻���� ���ٸ�
        //������
    else
        //�����Ұųİ� ������� �� �޾ƿ���
           //������ ���̸�
              //�ٸ��̸����� ����, �׳� ���� ����� call saveFile
           //�������� ������
              //������
}