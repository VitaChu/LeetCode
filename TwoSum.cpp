class Solution {
public:
  
    vector<int> twoSum(vector<int>& nums, int target) {
      unordered_map<int, int> mymap;
      vector<int> result;
      for(int i = 0; i < nums.size(); i++ ){
        int temp = target - nums[i];
        mymap.emplace(temp, i);
      }  
      
      for(int i = 0; i < nums.size(); i++ ){
        unordered_map<int, int>::const_iterator got = mymap.find(nums[i]);
        if( got != mymap.end() && got->second != i ) {
          result.push_back(i);
          result.push_back(got->second);
          return result;
        }
      }
        /*/
        vector<int> result;
        for( int i = 0; i < nums.size(); i++ ) {
            int temp = target - nums[i];
            for( int j = 0; j < nums.size() && i != j; j++ ) {
                if( temp == nums[j] ) {
                    result.push_back(i);
                    result.push_back(j);
                }
            }
        }
        //*/  
      
        /*/
        for( auto i : nums ) {
            vector<int>::iterator iter;
            int temp = target - i;
            for(iter = nums.begin(); iter != nums.end(); iter++ ) {
                if( temp == *iter ) {
                    result.push_back(i);
                    result.push_back(target - i);
                }
            }
        }
        //*/
       return result;
    }
};


// i have just added a small code (very small)
Kindly acknowledge
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> mp;
        vector<int> ans;
        for(int i=0;i<nums.size();i++){
            if(mp.find(target-nums[i])!=mp.end()){
                ans = {mp[target-nums[i]],i};
                break;
            }
            else mp[nums[i]] = i;
        }
        return ans;
    }
};
