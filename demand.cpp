#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<stack>
#include<queue>
#include"demand.h"

constexpr auto maxtime = 9999;
constexpr auto maxmoney = 9999;
#define price_max 99999;
#define time_max 99999;
float matrix[100][100];  //�ڽӾ���
bool visited[100];     //�������
float dist[100];         //Դ�㵽����i����̾���
int path[100];           //��¼���·��·��
int enqueue_num[100];  //��¼��Ӵ���
int vertex_num = 12;       //������
int edge_num = 50;          //����
int path_matrix[12][12][12]; //��¼��A��B������·��
int start_to_end[200];//��¼����㵽�յ����·��
vector<vector<imfo> > p;


using namespace std;
extern vector<vector<vector<imfo> > > coach;
extern vector<vector<vector<imfo> > > air;
extern vector<vector<vector<imfo> > > train;


demand::demand(int dpt,int avi,int stg):departure(dpt),arrvial(avi),strategy(stg)
{

}
demand::~demand()
{
	cout << "����demand��������" << endl;
}
void demand::print()
{
}
/*void demand::output()
{
	vector<imfo> finalway;
	switch (strategy)
	{
	case 2:
		least_time(finalway);
		break;
	case 3:
	{
		timeband_leastmoney(finalway);
		break;
	}	
	default:
		break;
	}
	vector<imfo>::iterator iter;
	if (finalway.empty())
	{
		cout << "erro!";
	}
	for (iter = finalway.begin();iter != finalway.end();++iter)
	{
		iter->printout();
	}
}*/
int demand::nametonum(string &str)
{
	int x = -1;
	if (str=="��ɳ") 
	{
		x = 0;
	}
	if (str=="����") 
	{
		x = 1;
	}
	if (str=="����")
	{
		x = 2;
	}
	if (str=="ʯ��ׯ")
	{
		x = 3;
	}
	if (str=="����")
	{
		x = 4;
	}
	if (str=="����")
	{
		x = 5;
	}
	if (str=="����")
	{
		x = 6;
	}
	if (str=="�ϲ�")
	{
		x = 7;
	}
	if (str=="�人")
	{
		x = 8;
	}
	if (str=="����")
	{
		x = 9;
	}
	if (str== "����")
	{
		x = 10;
	}
	if (str=="����")
	{
		x = 11;
	}
	if (x == -1)
	{
		cout << "��Ǹ��Ŀǰ�޸ó�����Ϣ������������:";
		cin >> str;
		x=nametonum(str);
	}
	return x;
}
vector<imfo> demand::least_money(float &money)
{
	/*************************************************************************************/
	//�м��Ƕ�һЩ��Ҫ�����Ķ���
    vector<imfo> out_order;
	float least_money = 99999;
	int out_num = 0;
	int tmp;
	int i = 0, j = 0, k;
	int len = 0;//len��������b��Ԫ�ص�������һ
	int  start = departure;//��ʼ����
	int  end = arrvial;//��ֹ����
	float** matrix_min;//�����������֮�����С����
	float min[12];//��ʱ���һ�����е������������е���С����
	int b[12];
	for (i = 0;i < 12;i++)
	{
		b[i] = -1;
	}
	vector<int>::iterator iter;
	for (iter = way_city.begin();iter != way_city.end();iter++)
	{
		len++;
	}
	len = len - 1;
	for (iter = way_city.begin(); iter != way_city.end(); iter++)
	{
		b[j] = *iter;
		j++;
	}

	int order[12];//����⼸����������ô;����
	//int b[3] = { 2,3,11 };//;���ĳ���,len=b����Ĵ�С-1



	string number_matrix[12];
	string** min_money_number = new string*[12];

	/*************************************************************************************/



	/*************************************************************************************/
	//�м��Ƕ����ݵĳ�ʼ��
	p.resize(12);//r��
	for (k = 0; k < 12; k++) {
		p[k].resize(12);//ÿ��Ϊc��
	}
	for (i = 0; i < 200; i++) {
		start_to_end[i] = -1;
	}
	for (i = 0; i < 12; i++)
	{
		order[i] = -1;
	}
	for (i = 0; i < 12; i++)
	{
		min_money_number[i] = new string[12];
	}
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			for (k = 0; k < 12; k++)
				path_matrix[i][j][k] = -1;
		}
	}
	for (i = 0; i < 200; i++)
	{
		start_to_end[i] = -1;
	}
	for (i = 0; i < vertex_num; i++) {
		for (j = 0; j < vertex_num; j++) {
			matrix[i][j] = 88888; //Initialize the matrix array
		}
	}

	/*************************************************************************************/


	matrix_min = get_min_matrix(min_money_number);//min_money_number��ŵ�����������֮�����С����

	for (i = 0; i < 12; ++i)
	{
		for (j = 0; j < 12; ++j)
		{
			matrix[i][j] = matrix_min[i][j];
		}
	}

	for (int source = 0; source < 12; ++source)
	{
		SPFA(source, min);
		for (i = 0; i < 12; ++i)
		{
			matrix_min[source][i] = min[i]; //matrix_min is Shortest path between two points
		}
	}

	for (i = 0; i < 12; i++)
	{
		SPFA(i, min);
		get_path_matrix(i, min);
	}


    if(len == -1)
    {
        least_money = matrix_min[start][end];
        order[0] = start;
        order[1] = end;
    }
    else
    {
        full_permutation(b, len, 0, start, end, least_money, order, matrix_min);
    }
	start_to_end[0] = start;
	k = 1;
	for (i = 0; order[i + 1] != -1; i++)
	{
		for (j = 1; path_matrix[order[i]][order[i + 1]][j] != -1; j++)
		{
			start_to_end[k] = path_matrix[order[i]][order[i + 1]][j];
			k++;
		}
	}
	for (i = 0; start_to_end[i + 1] != -1; i++)
	{
		out_order.push_back(p[start_to_end[i]][start_to_end[i + 1]]);
	}
	out_num = i;	
	/*for (iter1 = out_order.begin(); iter1 != out_order.end(); iter1++)
	{
		cout << "��" << i << "��:";
		i++;
		iter1->printout();
	}

	cout << "��С����Ϊ��" << least_money;*/
    money = least_money;
    way_city.clear();
    return out_order;

}
vector<imfo> demand::least_time( int &time, float &money)
{
    float total_cost;
    vector<imfo>finalway;
	finalway.clear();
	int cur_arrvial;
	if (way_city.empty())
	{
		cur_arrvial = arrvial;
	}
	else
	{
		cur_arrvial = way_city[0];
	}
	int cur_departure = departure;
	int min_time = maxtime;
	int nowtime = 0;
	int curtime = 0;
	int total_time = 0;
	int final_time = maxtime;
	int temp = cur_arrvial;
	int count = 0;
	int path[12], D[12], detime[12] = { 0 };
	bool visited[12];
	int **Gra = new int*[12];
	imfo **Cmpl = new imfo*[12];
	for (int i = 0;i < 12;i++)
	{
		Cmpl[i] = new imfo[12];
		Gra[i] = new int[12];
	}
	vector<int> finalroad;
	vector<int> temproad;
	vector<int> nowroad;
	
	vector<int>::iterator city_iter;
	vector<int>::iterator final_iter=finalroad.begin();
	vector<int>::iterator cur_iter = finalroad.begin();
	vector<int>::iterator nowroad_iter = nowroad.begin();
	finalroad.push_back(departure);
	temproad.push_back(departure);
	count = way_city.size();
	vector<vector<int>> city_pass(factorial(count), vector<int>(0));
	if (count != 0)
	{
		printRecurve(way_city, city_pass, count - 1, 0);
	}
	for (int num = 0;num < factorial(count);num++)
	{
		city_pass[num].push_back(arrvial);
		//cur_arrvial = way_city[0];
		cur_departure = departure;
		temp = cur_arrvial;
		for (city_iter = city_pass[num].begin();city_iter != city_pass[num].end();city_iter++)
		{
			cur_arrvial = *city_iter;
			/*��ʼ��ͼ*/
			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 12; j++)
				{
					Gra[i][j] = maxtime;
				}
				visited[i] = false;
				path[i] = -1;
			}
			if (city_iter == city_pass[num].begin())
			{
				initial_Grapah(Gra,time_range, detime, cur_departure);
				for (int judge = 0;judge < 12;judge++)
				{
					if (Gra[departure][judge] != maxtime)
					{
						judge = 12;
						finalway.clear();
					}
					if (judge == 11)
					{
						cout << "��ʱ�䷶Χ���޷��������!";
                        finalway.clear();
                        return finalway;
					}
				}
			}
			else {
				initial_Grapah(Gra,nowtime, detime, cur_departure);
			}
			cur_arrvial = *city_iter;
			/*�Ͻ�˹����*/
			for (int i = 0;i < 12;i++)
			{
				D[i] = Gra[cur_departure][i];
				if (D[i] < maxtime)
				{
					path[i] = cur_departure;
				}
				else
				{
					path[i] = -1;
				}
			}
			visited[cur_departure] = true;
			D[cur_departure] = 0;
			int min, count = 0, i = 0;
			for (int k = 0;k < 12;k++)
			{
				min = maxtime;
				for (int w = 0;w < 12;w++)
				{
					if (!visited[w] && D[w] < min)
					{
						i = w;
						min = D[w];
					}
				}
				if (city_iter == city_pass[num].begin())
				{
					nowtime = (detime[find_detime(path, i)] + D[i]) % 24;
				}
				else {
					nowtime = (D[i] + nowtime) % 24;
				}
				visited[i] = true;
				renew_Grapah(Gra,nowtime);
				for (int w = 0;w < 12;w++)
				{
					if (!visited[w] && (D[i] + Gra[i][w] < D[w]))
					{
						D[w] = D[i] + Gra[i][w];
						path[w] = i;
					}
				}
			}
			if (city_iter == city_pass[num].begin())
			{
				nowtime = (detime[find_detime(path, cur_arrvial)] + D[cur_arrvial]) % 24;
				curtime = nowtime;
			}
			else
			{
				nowtime = (curtime + D[cur_arrvial]) % 24;
				curtime = nowtime;
			}
			temp = cur_arrvial;
			total_time += D[temp];
			/*���*/
			while (temp != -1)
			{
				nowroad.push_back(temp);
				temp = path[temp];
			}
			reverse(nowroad.begin(), nowroad.end());
			for (nowroad_iter = ++nowroad.begin();nowroad_iter != nowroad.end();nowroad_iter++)
			{
				temproad.push_back(*nowroad_iter);
			}
			nowroad.clear();
	
			cur_departure = cur_arrvial;
		}
		if (total_time < final_time)
		{
			finalroad.clear();
			for (nowroad_iter = temproad.begin();nowroad_iter != temproad.end();nowroad_iter++)
			{
				finalroad.push_back(*nowroad_iter);
			}
			final_time = total_time;
		}
		temproad.clear();
		temproad.push_back(departure);
		total_time = 0;
		
	}
	initial_Grapah(Gra, Cmpl, time_range, detime, cur_departure);
	for (final_iter = finalroad.begin(), nowroad_iter = finalroad.begin();final_iter != finalroad.end();final_iter++)
	{
		if (final_iter == finalroad.begin())
		{
			continue;
		}

		if (nowroad_iter == finalroad.begin())
		{
			nowtime = (detime[*final_iter] + Gra[*nowroad_iter][*final_iter])%24;
		}
		else
		{
			nowtime = (nowtime + Gra[*nowroad_iter][*final_iter]) % 24;
		}
        total_cost += Cmpl[*nowroad_iter][*final_iter].Get_price();
		finalway.push_back(Cmpl[*nowroad_iter][*final_iter]);
		renew_Grapah(Gra, Cmpl, nowtime);
		nowroad_iter ++;
	}
	cout <<"����ʱ:"<< final_time << "Сʱ" << endl;
	/*�ͷ�����*/
	for (int i = 0;i < 12;i++)
	{
		delete[]Gra[i];
		delete[]Cmpl[i];
	}
	delete Gra;
	delete Cmpl;
    money = total_cost;
    time=final_time;
    return finalway;
}
//vector<imfo> timeband_leastmoney(int &time, float &money)
//{
//	int s[12][12] = {0};
//	float min_money = maxmoney;
//	float nowmoney = 0;
//	int travel_time = 0;
//	int passtime = 0;//һ�㵽��һ���ʱ��
//	int waittime = 0;//�ȴ���ʱ��
//	int tag = 0;//�ж��Ƿ��������һ�ڵ�
//	int lastout = -1;//�����ĳ���
//	int size = finalway.size();//�洢����Ĵ�С
//	bool city_passed[12] = { false };//�ж��Ƿ񾭹��ؾ��ĳ���
//	bool isall = false;
//	bool isfull = false;
	
//	stack<int>time_passed;//�洢ÿ������(������֮��)���ĵ���ʱ��
//	stack<int> p;//����ջʵ����ȱ���
//	vector<imfo>tempway;
//	p.push(departure);
//	city_passed[departure] = true;
//	int pnow = p.top();
//    float costOfMinPath;
//    out_order = least_money(costOfMinPath);
//	if (costOfMinPath < bound)
//	{
//		return costOfMinPath;//���ٻ��ѵĽ�Ǯ���������������ս�
//	}
//	int Mintime = least_time(finalway);
//	if (Mintime>bound)
//	{
//		cout << "�޷���������" << endl;//���ʱ���޷�����Ҫ�󼰲��������Ҫ��
//		return -1;
//	}

//	while (!p.empty())
//	{
//		pnow = p.top();//��ǰ�����Ľڵ�
//		for (int i = 0;i < 12;i++)
//		{
			
//			if (pnow == arrvial)
//			{
//				break;
//			}
//			if (s[pnow][i]== air[pnow][i].size()/*||i<=lastout*/)//�Ѿ������Ľڵ�
//			{
//				continue;
//			}
//			if (air[pnow][i].size())//�����������·��
//			{
				
//				if (air[pnow][i][s[pnow][i]].Get_arrival_time() < air[pnow][i][s[pnow][i]].Get_departure_time())
//				{
//					passtime = air[pnow][i][s[pnow][i]].Get_arrival_time() - air[pnow][i][s[pnow][i]].Get_departure_time() + 24;
//				}
//				else
//				{
//					passtime = air[pnow][i][s[pnow][i]].Get_arrival_time() - air[pnow][i][s[pnow][i]].Get_departure_time();
//				}
//				if (pnow == departure)
//				{
//					if (air[pnow][i][s[pnow][i]].Get_departure_time() < time_range[0] || air[pnow][i][s[pnow][i]].Get_departure_time() > time_range[1])
//					{
//						continue;
//					}
//					travel_time = air[pnow][i][s[pnow][i]].Get_departure_time();
//				}
//				if (nowmoney + air[pnow][i][s[pnow][i]].Get_price() > min_money || passtime> bound)
//				{
//					continue;//��ǰ���ѳ�������С����
//				}
//				if (i == arrvial)//�ҵ�һ��·��
//				{
					
//					//�ж��Ƿ񾭹�����;������
//					isall = true;
//					for (vector<int>::iterator iter = way_city.begin();iter != way_city.end();iter++)
//					{
//						if (!city_passed[*iter])
//						{
//							isall = false;
//							break;
//						}
//					}
//					if (!isall)
//					{
//						break;
//					}
//					nowmoney += air[pnow][i][s[pnow][i]].Get_price();
//					travel_time += passtime;
//					min_money = nowmoney;
//					p.push(i);//ѡ�д˳���ѹ��ջ��
//					//finaway ��ֵ
//					time_passed.push(passtime);
//					tempway.push_back(air[pnow][i][s[pnow][i]]);
//					s[pnow][i]++;

//					if (nowmoney < min_money)
//					{
//						finalway.clear();
//						for (vector<imfo>::iterator p = tempway.begin();p != tempway.end();p++)
//						{
//							finalway.push_back(*p);
//						}
//						min_money = nowmoney;
//					}
					


//					break;
//				}
//				else//�ҵ���һ�ڵ�
//				{
//					tag = 1;//��ʶ���α����ҵ�����һ�ڵ�
//					nowmoney += air[pnow][i][s[pnow][i]].Get_price();
//					travel_time += passtime;
//					p.push(i);
//					city_passed[i] = true;
//					tempway.push_back(air[pnow][i][s[pnow][i]]);
//					time_passed.push(passtime);
//					s[pnow][i]++;
//					lastout = -1;
//					break;
//				}
//			}
			
//		}
//		if (tag == 0)
//		{
//			lastout = p.top();
//			p.pop();
//			city_passed[lastout] = false;
//			if (p.empty())
//			{
//				break;
//			}
//			pnow = p.top();
//			isfull = true;
//			/*�ж�lastout�Ƿ�Ϊ�յ�*/
//			if (lastout == arrvial)
//			{
//				for (int i = 0;i < 12;i++)
//				{
//					s[lastout][i] = 0;
//				}
//			}
//			else
//			{
//				for (int i = 0;i < 12;i++)//����
//				{
//					if (s[lastout][i] != air[lastout][i].size())
//					{
//						isfull = false;
//						break;
//					}
//				}
//				if (isfull)
//				{
//					for (int i = 0;i < 12;i++)
//					{
//						s[lastout][i] = 0;
//					}
//				}
//			}
//			size = tempway.size();
//			nowmoney -= tempway[size - 1].Get_price();
//			travel_time -= time_passed.top();
//			tempway.pop_back();
//			time_passed.pop();
//		}
//		tag = 0;
//		travel_time = 0;
//		passtime = 0;//һ�㵽��һ���ʱ��
//		waittime = 0;//�ȴ���ʱ��
//		nowmoney = 0;
//		for (vector<imfo>::iterator p = tempway.begin();p != tempway.end();p++)
//		{
//			p->print();
//		}
//		cout << endl;
//	}
	
//}


//void demand::DFS(vector<imfo>& finalway)
//{
//	stack<int> p;
//	vector<imfo>temp;
//	vector<int>time_mem;
//	vector<float>price_mem;
//	p.push(departure);
//	int visited[12][12] = { 0 };
//	int s[12] = { 0 };
//	int pnow;
//	int tag = 0;
//	int lastout=-1;
//	int total_time = 0;
//	int total_money = 0;
//	int min_money = maxmoney;
//	int passtime = 0;
//	int waittime = 0;
//	int travel_time = 0;
//	int i = 0;//����
//	float min_price = 0;
	
//	s[departure] = 1;
//	while (!p.empty())
//	{
//		tag = 0;
//		pnow = p.top();
//		for (i = 0;i < 12;i++)
//		{
//			if (pnow == arrvial)
//			{
//				break;
//			}
//			if (i == pnow||s[i]== 1)
//			{
//				continue;
//			}
//			if (air[pnow][i].size() > 0 && visited[pnow][i] < air[pnow][i].size())
//			{
//				if (pnow == departure)
//				{
//					if (air[pnow][i][visited[pnow][i]].Get_departure_time() < time_range[0] || air[pnow][i][visited[pnow][i]].Get_departure_time() > time_range[1])
//					{
//						continue;
//					}
//					waittime = 0;
//					travel_time = air[pnow][i][visited[pnow][i]].Get_departure_time();
//				}
//				else
//				{
//					if (air[pnow][i][visited[pnow][i]].Get_departure_time() < travel_time)
//					{
//						waittime = 24 + (air[pnow][i][visited[pnow][i]].Get_departure_time() - travel_time);
//					}
//					else
//					{
//						waittime = air[pnow][i][visited[pnow][i]].Get_departure_time()-travel_time;
//					}
					
//				}
//				if (air[pnow][i][visited[pnow][i]].Get_arrival_time() < air[pnow][i][visited[pnow][i]].Get_departure_time())
//				{
//					passtime = air[pnow][i][visited[pnow][i]].Get_arrival_time() - air[pnow][i][visited[pnow][i]].Get_departure_time() + 24;
//				}
//				else
//				{
//					passtime = air[pnow][i][visited[pnow][i]].Get_arrival_time() - air[pnow][i][visited[pnow][i]].Get_departure_time();
//				}
				
//				time_mem.push_back(passtime+waittime);
//				price_mem.push_back(air[pnow][i][visited[pnow][i]].Get_price());
//				visited[pnow][i]++;
//				for (int j = 0;j < time_mem.size();j++)
//				{
//					total_time += time_mem[j];
//				}
//				for (int j = 0;j < time_mem.size();j++)
//				{
//					total_money += price_mem[j];
//				}
//				if (total_time > bound|| total_money >= min_money)
//				{
//					price_mem.pop_back();
//					time_mem.pop_back();
//					total_time = 0;
//					total_money = 0;
//					continue;
//				}
//				travel_time = (travel_time + passtime + waittime) % 24;
				
//				p.push(i);
//				temp.push_back(air[pnow][i][visited[pnow][i]-1]);
//				s[i] = 1;
//				tag = 1;
//				if (i == arrvial)
//				{
//					if (!ismeet(way_city, s))
//					{
//						tag = 0;
//					}
//					else
//					{
//						if (total_money < min_money)
//						{
//							min_money = total_money;
//							finalway.clear();
//							for (auto iter : temp)
//							{
//								finalway.push_back(iter);
//							}
//						}
//					}
//				}
//				total_time = 0;
//				total_money = 0;
//				break;
//			}
//		}
//		if (tag == 0)
//		{
//			lastout = p.top();
//			for (int j = 0;j < 12;j++)
//			{
//				visited[lastout][j] = 0;
//			}
//			s[lastout] = 0;
//			p.pop();
			
//			if (lastout != departure)
//			{
//				temp.pop_back();
//				travel_time = (travel_time - time_mem.back())%24;
//				time_mem.pop_back();
//				price_mem.pop_back();
//			}
//		}
//		tag = 0;
//	}
//	return;
//}
void initial_Grapah(int **Gra,imfo **Cmpl,int time_range[],int detime[],int departure)
{
    int min_time, dtime, atime;
    vector<imfo>::iterator coach_iter;
    imfo mintime;
    for (int k = 0; k < 12; k++)
    {
        for (int i = 0;i < 12; i++)
        {
            min_time = maxtime;
            if (i == k)
            {
                continue;
            }
            for (coach_iter = coach[k][i].begin();coach_iter != coach[k][i].end();coach_iter++)
            {
                if (coach_iter->Get_departure_time() < time_range[0])
                {
                    continue;
                }
                else {
                    dtime = coach_iter->Get_departure_time();
                    atime = coach_iter->Get_arrival_time();
                    if (atime < dtime)
                    {
                        atime += 24;
                    }
                    if (coach_iter->Get_departure_time() < time_range[1])
                    {
                        if (atime - dtime < min_time)
                        {
                            mintime = *coach_iter;
                            min_time = atime - dtime;
                            if (k == departure)
                            {
                                detime[i] = dtime;
                            }
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            Gra[k][i] = min_time;
            Cmpl[k][i] = mintime;
        }
    }
	
}
void initial_Grapah(int **Gra, int time_range[], int detime[], int departure)
{
    int min_time, dtime, atime;
    vector<imfo>::iterator coach_iter;
    for (int k = 0; k < 12; k++)
    {
        for (int i = 0;i < 12; i++)
        {
            min_time = maxtime;
            if (i == k)
            {
                continue;
            }
            for (coach_iter = coach[k][i].begin();coach_iter != coach[k][i].end();coach_iter++)
            {
                if (coach_iter->Get_departure_time() < time_range[0])
                {
                    continue;
                }
                else {
                    dtime = coach_iter->Get_departure_time();
                    atime = coach_iter->Get_arrival_time();
                    if (atime < dtime)
                    {
                        atime += 24;
                    }
                    if (coach_iter->Get_departure_time() < time_range[1])
                    {
                        if (atime - dtime < min_time)
                        {
                            min_time = atime - dtime;
                            if (k == departure)
                            {
                                detime[i] = dtime;
                            }
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            Gra[k][i] = min_time;
        }
    }

}
void initial_Grapah(int **Gra, int nowtime, int detime[], int departure)
{
	int min_time, dtime = 0, atime = 0, wait_time = 0;
	vector<imfo>::iterator coach_iter;
	for (int k = 0; k < 12; k++)
	{
		for (int i = 0;i < 12;i++)
		{
			min_time = maxtime;
			if (i == k)
			{
				continue;
			}
			for (coach_iter = coach[k][i].begin();coach_iter != coach[k][i].end();coach_iter++)
			{
				dtime = coach_iter->Get_departure_time();
				atime = coach_iter->Get_arrival_time();
				if (dtime < nowtime)
				{
					wait_time = dtime + 24 - nowtime;
				}
				else
				{
					wait_time = dtime - nowtime;
				}
				if (atime < dtime)
				{
					atime += 24;
				}
				if (atime - dtime + wait_time < min_time)
				{
					min_time = atime - dtime + wait_time;
					if (k == departure)
					{
						detime[i] = dtime;
					}
				}
			}
			Gra[k][i] = min_time;
		}
	}

}
void renew_Grapah(int **Gra, imfo **Cmpl, int nowtime)
{
	int min_time, dtime=0, atime=0,wait_time=0;
	vector<imfo>::iterator coach_iter;
	imfo mintime;
	for (int k = 0; k < 12; k++)
	{
		for (int i = 0;i < 12;i++)
		{
			min_time = maxtime;
			if (i == k)
			{
				continue;
			}
			for (coach_iter = coach[k][i].begin();coach_iter != coach[k][i].end();coach_iter++)
			{
				dtime = coach_iter->Get_departure_time();
				atime = coach_iter->Get_arrival_time();
				if (dtime < nowtime)
				{
					wait_time = dtime + 24 - nowtime;
				}
				else
				{
					wait_time = dtime - nowtime;
				}
				if (atime < dtime)
				{
					atime += 24;
				}
				if (atime - dtime + wait_time < min_time)
				{
					mintime = *coach_iter;
					min_time = atime - dtime + wait_time;
				}
			}
			Gra[k][i] = min_time;
			Cmpl[k][i] = mintime;
		}
	}
}
void renew_Grapah(int **Gra, int nowtime)
{
	int min_time, dtime = 0, atime = 0, wait_time = 0;
	vector<imfo>::iterator coach_iter;
	for (int k = 0; k < 12; k++)
	{
		for (int i = 0;i < 12;i++)
		{
			min_time = maxtime;
			if (i == k)
			{
				continue;
			}
			for (coach_iter = coach[k][i].begin();coach_iter != coach[k][i].end();coach_iter++)
			{
				dtime = coach_iter->Get_departure_time();
				atime = coach_iter->Get_arrival_time();
				if (dtime < nowtime)
				{
					wait_time = dtime + 24 - nowtime;
				}
				else
				{
					wait_time = dtime - nowtime;
				}
				if (atime < dtime)
				{
					atime += 24;
				}
				if (atime - dtime + wait_time < min_time)
				{
					min_time = atime - dtime + wait_time;
				}
			}
			Gra[k][i] = min_time;
		}
	}
}
int find_detime(int path[],int i)
{
	while (path[path[i]] != -1)
	{
		i = path[i];
	}
	return i;
}
void printRecurve(vector<int> a,vector<vector<int> >&b ,int len, int k)
{
	static int count = 0;
	if (len == k)
	{
		for (int i = 0; i <= len; ++i)
		{
			b[count].push_back(a[i]);
			
		}
		count++;
	}
	else
	{
		for (int idx = k; idx <= len; ++idx)
		{
			swap(a[idx], a[k]);
			printRecurve(a,b, len, k + 1);
			swap(a[idx], a[k]);
		}
	}
}
int factorial(int a)
{
	int result = 1;
	while (a != 0)
	{
		result *= a--;
	}
	return result;
}
void get_path_matrix(int source, float *min)
{
	for (int i = 0; i < vertex_num; i++)
	{
		if (i != source)
		{
			int p = i;
			stack<int> s;

			while (source != p)  //·��˳��������ģ������ȱ��浽ջ
			{
				s.push(p);
				p = path[p];
			}

			path_matrix[source][i][0] = source;
			int j = 1;
			while (!s.empty())  //���δ�ջ��ȡ���Ĳ�������·��
			{
				path_matrix[source][i][j] = s.top();
				s.pop();
				j++;
			}
		}
	}
}
int SPFA(int source, float *min)
{
	memset(visited, 0, sizeof(visited));
	memset(enqueue_num, 0, sizeof(enqueue_num));
	for (int i = 0; i < vertex_num; i++)
	{
		dist[i] = 99999;
		path[i] = source;
	}
	queue<int> Q;
	Q.push(source);
	dist[source] = 0;
	visited[source] = 1;
	enqueue_num[source]++;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		visited[u] = 0;
		for (int v = 0; v < vertex_num; v++)
		{
			if (matrix[u][v] != 99999)
			{
				if (dist[u] + matrix[u][v] < dist[v])
				{
					dist[v] = dist[u] + matrix[u][v];
					path[v] = u;
					if (!visited[v])
					{
						Q.push(v);
						enqueue_num[v]++;
						if (enqueue_num[v] >= vertex_num)
							return false;
						visited[v] = 1;
					}
				}
			}
		}
		for (int i = 0; i < 12; ++i) {
			min[i] = dist[i];
		}
	}
	return true;
}
float get_money(float **matrix_min, int start, int end, int a[], int len) {
	int i, order[12];
	float all_money = 0;
	for (i = 1; i <= len + 1; i++)
		order[i] = a[i - 1];
	order[0] = start;
	order[i] = end;

	for (i = 0; i <= len + 1; i++) {
		all_money = all_money + matrix_min[order[i]][order[i + 1]];
	}
	return all_money;
}
void full_permutation(int a[], int len, int k, int start, int end, float &least_money, int *order, float **matrix_min)
{
	if (len == k)
	{
		int i;
		float money = get_money(matrix_min, start, end, a, len);
		if (least_money > money)
		{
			least_money = money;
			for (i = 0; i <= len; ++i)
				order[i + 1] = a[i];
			order[0] = start;
			order[len + 2] = end;
		}

	}
	else
	{
		for (int idx = k; idx <= len; ++idx)
		{
			swap(a[idx], a[k]);
			full_permutation(a, len, k + 1, start, end, least_money, order, matrix_min);
			swap(a[idx], a[k]);
		}
	}
}
float** get_min_matrix(string** min_money_number) {
	int i, j;
	float min, temp;
	float **matrix_min = new float*[12];
	for (i = 0; i < 12; i++)
	{
		matrix_min[i] = new float[12];
	}
	vector<imfo>::iterator iter;
	for (i = 0; i < 12; ++i) {
		for (j = 0; j < 12; j++) {
			if (coach[i][j].empty()) {
				matrix_min[i][j] = price_max;
				min_money_number[i][j] = "0000000";
				p[i].push_back(0);
				continue;
			}
			min = coach[i][j][0].Get_price();
			min_money_number[i][j] = coach[i][j][0].Get_number();
			p[i][j] = coach[i][j][0];
			for (iter = coach[i][j].begin(); iter != coach[i][j].end(); ++iter)
			{
				temp = iter->Get_price();
				if (temp < min) {
					min = temp;
					min_money_number[i][j] = iter->Get_number();
					p[i][j] = *iter;
				}
			}
			matrix_min[i][j] = min;
		}
	}
	return matrix_min;
}

int ismeet(vector<int> way_city,int s[12])
{
	for (auto i: way_city)
	{
		if (s[i] == 0)
		{
			return 0;
		}
	}
	return 1;
}

