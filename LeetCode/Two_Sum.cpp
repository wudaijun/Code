#include<vector>
#include<unordered_map>
using namespace std;

/*
 *	2015-02-12 wudaijun
 *	思路：遍历一次 用Hash保存遍历结果(记录哪个数字出现在哪个位置)
 *	空间：O(n) 时间：O(n)
 */
class Solution {
    unordered_map<int, size_t> _hash;
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        vector<int> result;
        const size_t size = numbers.size();
        for(size_t i=0; i<size; ++i)
        {
            int this_number = numbers[i];
            int to_find = target - this_number;
            auto item = _hash.find(to_find);
            if( item != _hash.end())
            {
                result.push_back(item->second+1);
                result.push_back(i+1);
                break;
            }
            _hash[this_number] = i;
        }
        return result;
    }
};

#include<iostream>
int main()
{
	Solution s;
	int a[10] = {1, 8, 20, 70, 34, 65, 11, 9, 99, 5};
	vector<int> numbers(a, a+10);
	vector<int> res = s.twoSum(numbers, 101);

	if(res.size() > 0)
		cout<<res[0]<<" "<<res[1]<<endl;
	else
		cout<<"no answer"<<endl;
	return 0;
}
