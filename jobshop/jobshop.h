#define SIZE 30 //��������������
#define GROUP 1000 //message���� 
struct input //����
{
    int item; //����
    int step;//����
    int time; //ʱ��
    int machine; //����
    int process;//ά�޲��� 
};

struct chromosome // Ⱦɫ��
{
    int message[GROUP]; //����˳��
    int time; //������Լ���µ����ʱ��
};

struct machine //����
{
  int number; //������
  int item;//��Ʒ��
  int process;//���� 
  int begintime; //��ʼʱ�� 
  int endtime; //����ʱ��
};

extern struct input inputArray[SIZE][SIZE];//������������ݣ��б�ʾ�����ţ��б�ʾ����
extern struct machine workMachine[SIZE][SIZE];//���л���
extern struct machine originWorkMachine[SIZE][SIZE];//��ʼ״̬ 
extern int originRepeat[SIZE];//��ʼ�������� 
extern int originStep[SIZE];//��ʼ��������  

void input(); //���� 
void anneal(struct chromosome*,struct chromosome *); //�˻� 
void initchro(struct chromosome*);//����������� 
void translate(int,struct chromosome*);//����ת��Ϊʱ�� 
void output1(struct chromosome *);//��� 
void output2(struct chromosome *);//��� 
void superAnneal(struct chromosome *);//��ǿ���˻� 
void draw_graphics(int *endtime,double *programme_endtime);


