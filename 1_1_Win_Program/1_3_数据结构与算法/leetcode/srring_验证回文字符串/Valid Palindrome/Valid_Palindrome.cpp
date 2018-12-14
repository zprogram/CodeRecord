#include<stdio.h>
#include <string>
using std::string;

// 第一种方法
// https://www.cnblogs.com/17bdw/p/10117910.html#_label1_0
// 第二种方法
// https ://leetcode.com/problems/valid-palindrome/discuss/119173/C++-Easy-to-Understand-Solution


class Solution {
public:
	bool isPalindrome(string s) {

		string re_val = "";
        // 除去特殊符号，提取出字符串的小写字母
		for (char str_val : s)
		{
			// 确认字母数字
			if (isalnum(str_val) != false)
			{
				if (str_val >= 'A'&& str_val <= 'Z')
				{
					// 取小写与大写之间的差值，得到字符对应的小写ASCII码对应是什么存进字符串中
					re_val += (str_val + ('a' - 'A'));
				}
				else
				{
					// 如果是小写就不处理
					re_val += str_val;
				}
			}
		}
		for (int i=0,j=re_val.size()-1; i<j;i++,j--) 
		{
			//一个指针从左边指到右边，一个指针从右边指向左边。如果有不同的值，就判断不是回文字符。
			if (re_val[i] != re_val[j])
				return false;
		}
    	return true;
	}
};


int main()
{

	Solution solu;
	bool ret;
	ret = solu.isPalindrome("A man, a plan, a canal: Panama");
	printf("%d \n", ret);
	ret = solu.isPalindrome("race a car");
	printf("%d \n", ret);
	return 0;
}