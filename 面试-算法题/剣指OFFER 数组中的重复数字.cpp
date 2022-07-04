class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即�?     *
     * 
     * @param numbers int整型vector 
     * @return int整型
     */
    int duplicate(vector<int>& numbers) {
        // write code here
        int i=0;
        int temp=0;
        int ctemp= 0 ;
        while(i<numbers.size())
        {
            temp=numbers[i];
            if(i==temp)//下标和数值位相同
            {
                i++;//走到下一�?            }
            else 
            {
                if(temp==numbers[temp])//数值和数值作为下标的对应位是否相�?                {
                    return temp;
                }
                else//数值交换到对应位置
                {
                    ctemp = numbers[i];
                    numbers[i]= numbers[ctemp];
                    numbers[ctemp]=ctemp;
                }
            }
        }
        return -1;
    }
};

















void listReverse(List*pHead)
{
?	stack<int> s1;
?	List*res;//����ָ��
?      	List*temp;//�м��ȡֵ�ڵ�
	List*mark=res;//�����ýڵ�
?	while(pHead!=NULL)//����������ջ
?	{

?		s1.pushback(pHead->val);
?		pHead=pHead->pnext;
?	}
?	while(s1.size()>0)
?	{
?		temp=new List;
?		temp->val=s1.top();//ȡջ��Ԫ��
?		s1.pop();//�����Ľ����ջ
?		temp->next=NULL;
?		res=temp;
?		if(res==NULL)//����β����
?		{
?			res=temp;
?		}
?		else
?		{
?			while(mark->next!=NULL)
?			{
?				mark=mark->next;
?			}
?			mark->next=temp;
?		}
?	}
	return res;
}