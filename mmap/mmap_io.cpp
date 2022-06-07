#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include <stdio.h>
#include <stdlib.h>
/* io header files */
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
using namespace std;

// 将磁盘文件映射到内存之后，可以使用指针访问文件

// 时间测量函数
// template<class T>
// void measureTime(T&& func){
//     // 传入一个函数的universal reference
//     using namespace std::chrono;
//     auto start = system_clock::now();
//     func();
//     duration<double> diff = system_clock::now() - start;
//     cout<<"elapsed: " << diff.count() <<" seconds"<<endl;
// }

const int  MAX_EDGE=1000001;
/*********** 程序变量 ************/
int nodePairs[MAX_EDGE*3];
int dataNum;
/********* 测试参数 ***********/
const int N = 1e6;

//使用mmap读取txt文件，3百万个int型数据需要 0.051251s
void readtxtMmap(const string& inputFile){
    int fd = open(inputFile.c_str(), O_RDONLY);
    struct stat sb;
    fstat(fd, &sb);
    char *buffer = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);// 返回的是指向映射区域首地址的指针
    if(buffer==nullptr || buffer==(void*)-1){
      close(fd);
      exit(-1);
    }
    close(fd);

    int val=0;
    dataNum=0;
    bool flag=true;
    while(*buffer){
        if(*buffer<'0') // || *buffer>'9'
        {
            if(flag){
                nodePairs[dataNum]=val;
                ++dataNum;
                val=0;
                flag=false;
            }
        }
        else{
            val = val*10 + (*buffer - '0');
            //val = (val<<3) + (val<<1) + (*buffer - '0');
            flag=true;
        }
        buffer++;
    }
    munmap(buffer, sb.st_size);
}
// 使用fscanf()读取txt文件，3百万个int型数据需要 0.387049s
void readbyio(const string& inputFile){
    FILE *fp = fopen(inputFile.c_str(), "r");
    if (fp==nullptr)
    {
        printf("fail to open file");
        exit(-1);
    }
    dataNum = 0;
    while(!feof(fp)){
        fscanf(fp, "%d", &nodePairs[dataNum]);
        dataNum++;
    }
    // 这种方式读取，会多读一行文件末尾的空格，dataNum比实际的大1,最后一行会得到一个09
}
// 使用fprintf()写txt文件


// fread和fwrite函数是另一对读写函数


//写result.txt
void saveTxt(const string &outputFile){

    FILE *fp = fopen(outputFile.c_str(), "wb");
    int resCnt=0;
    for(int i=0;i<dataNum;i++){
        resCnt += i;
    }
    char temp[100];
    int idx=sprintf(temp,"%d\n",resCnt);
    temp[idx]='\0';
    fwrite(temp,idx,sizeof(char),fp);

    int j;
    for(int i=0; i<N; ++i) {
        
    }
    fclose(fp);
}

int main(){

    clock_t start, end;
    start = clock();

    const string inputTxtName = "input.txt";
    const string outputTxtName = "output.txt";
    /*
    // 构造需要读入的txt文件
    int bound = 50000; 
    ofstream ofs;
    ofs.open(inputTxtName, ios::out);
    // 一百万行数据
    for(int i=0; i<N; i++){
        for(int j=0; j<3; j++){
            ofs<< rand() % bound << " ";
        }
        ofs<<endl;
    }
    */

    //readtxtMmap(inputTxtName);
    //readbyio(inputTxtName);
    //saveTxt(outputTxtName);
    string a,b,c;
    cin>>a>>b>>c;
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<c<<endl;

    end = clock();
    cout<<"elapsed: " << (double)(end - start) / CLOCKS_PER_SEC <<" s "<<endl;

}