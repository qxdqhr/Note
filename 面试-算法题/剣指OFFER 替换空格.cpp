class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param s string字符串 
     * @return string字符串
     */
    string replaceSpace(string s) {
        // write code here
        int len=s.size();
        int num=0;
        while(len>-1)
        {
            if(s[len]==' ')
            {
                num++;
            }
            len--;
        }
        len=s.size();
        int nlen=len+2*num;
        string res(nlen,'\0');
        while(nlen>-1)
        {
            
            if(s[len]!=' ')
            {
                res[nlen]=s[len];
                len--;
                nlen--;
            }
            else
            {
                res[nlen]='0';
                nlen--;
                res[nlen]='2';
                nlen--;
                res[nlen]='%';
                nlen--;
                len--;

            }

        }
        return res;
    }
};