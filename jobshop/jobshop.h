#define SIZE 30 //步骤数，机器数
#define GROUP 1000 //message长度 
struct input //输入
{
    int item; //工件
    int step;//步数
    int time; //时间
    int machine; //机器
    int process;//维修步骤 
};

struct chromosome // 染色体
{
    int message[GROUP]; //工作顺序
    int time; //在以上约束下的最短时间
};

struct machine //机器
{
  int number; //机器号
  int item;//物品号
  int process;//步骤 
  int begintime; //开始时间 
  int endtime; //结束时间
};

extern struct input inputArray[SIZE][SIZE];//输入的所有数据，行表示机器号，列表示工序
extern struct machine workMachine[SIZE][SIZE];//所有机器
extern struct machine originWorkMachine[SIZE][SIZE];//初始状态 
extern int originRepeat[SIZE];//初始工件步骤 
extern int originStep[SIZE];//初始机器步骤  

void input(); //输入 
void anneal(struct chromosome*,struct chromosome *); //退火 
void initchro(struct chromosome*);//随机生成序列 
void translate(int,struct chromosome*);//序列转化为时间 
void output1(struct chromosome *);//输出 
void output2(struct chromosome *);//输出 
void superAnneal(struct chromosome *);//加强版退火 
void draw_graphics(int *endtime,double *programme_endtime);


