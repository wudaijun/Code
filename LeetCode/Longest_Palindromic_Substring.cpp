
/*
 *	Created On: 2015-01-30
 *		Author: wudaijun
 *	
 *	求出字符串中的最长回文
 *
 */

class Solution {
public:
    string longestPalindrome(string s) {
		int isPalindrome[1000][1000];
		memset(isPalindrome, 0, sizeof(isPalindrome));

		int best_len = 0;
		int best_start = 0;
		const int size = s.size();
		for(int i = size-1; i >= 0; --i)
		{
			for(int j = i; j <= size-1; ++j)
			{
				if(s[i] == s[j] && ( (j-i<=2) || isPalindrome[i+1][j-1]==1) )
				{
					isPalindrome[i][j] = 1;
					int len = j - i + 1;
					if(len > best_len)
					{
						best_len = len;
						best_start = i;
					}
				}
			}
		}

		return s.substr(best_start, best_len);

	}
};

int main()
{
	string s;
	cin >> s;
	Solution sol;
	while(s != "q")
	{
		cout<<sol.longestPalindrome(s)<<endl;
		cin >> s;
	}
	return 0;
}


