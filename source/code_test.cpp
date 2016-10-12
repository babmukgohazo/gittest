int checkName(String name){
    int length=name.length();
    if(!(name.at(length-2)==".")&&(name.at(length-1)=="m")&&(name.at(length-1)=="d"))//.md로 끝나는 파일이 맞는지 확인
        return -1;

    Qfile file(name);
    if(!file.open(Qfile::ReadOnly))//파일이 존재 하지 않으면
        return 0;
    return 1; //파일이 존재 하는 경우
}

void saveFile(int newSave, String name){
    if(newSave){//다른 이름으로 저장하는 경우라면
        do{
             //이름 받는 입력창 띄우기
            cin>>name;
        }while(checkName(name)==0);//파일 이름이 존재 하지 않는 것으로 받을 때까지 이름 받기
    }
    Qfile *outfile;
    outfile=fopen(name,"w");
    QdataStream out(&outfile);
    Qstring str=textEdit->toPlainText();//textEdit에 있는 내용을 문자열에 저장
    out<<str; //파일에 저장
}


void openFile(String name){
    Qfile file(name);//파일 열기
    Qdatastream in(&file);
    Qstring str;
    in>>str;
    textEdit->setText(str); //textEdit창에 파일에 있는 내용 뿌리기
}

void makeNewFile(){
    textEdit->setText(NULL);
}

void exit(String name){
    Qfile file(name);
    Qdatastream in(&file);
    Qstring strInFile,strInEdit;
    in>>striInFile;// 기존의 파일에 있었던 내용
    strInEdit=textEdit->toPlainText();//textEdit 창에 있는 파일 내용
    if(strInEdit.compare(strInFile)==0)// 변경내용이 없다면
        //나가기
    else
        //저장할거냐고 물어봐서 값 받아오기
           //저장할 것이면
              //다른이름으로 저장, 그냥 저장 물어보기 call saveFile
           //저장하지 않으면
              //나가기
}