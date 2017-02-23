/*
 *	问题：https://leetcode.com/problems/two-sum/
 *	思路：遍历一次 用Hash保存遍历结果(记录哪个数字出现在哪个位置)
 *	空间：O(n)
 *	时间：O(n)
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,size_t> hash;
        vector<int> result;
        const size_t size = nums.size();
        for(size_t i=0; i<size; ++i)
        {
            int this_number = nums[i];
            int to_find = target - this_number;
            auto item = hash.find(to_find);
            if( item != hash.end())
            {
                result.push_back(item->second);
                result.push_back(i);
                break;
            }
            hash[this_number] = i;
        }
        return result;
    }
};
