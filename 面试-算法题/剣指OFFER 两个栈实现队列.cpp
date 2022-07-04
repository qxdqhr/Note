class Solution
{
public:
    void push(int node) {
       
        while(stack2.size()>0)
        {
            int temp = stack2.top();
            stack2.pop();
            stack1.push(temp);
        }
        stack1.push(node);

    }

    int pop() {
        while(stack1.size()>0)
        {
            int temp = stack1.top();
            stack1.pop();
            stack2.push(temp);
        }
        int Top = stack2.top();
        stack2.pop();
        return Top;
    }

private:
    stack<int> stack1;//in
    stack<int> stack2;//out
};