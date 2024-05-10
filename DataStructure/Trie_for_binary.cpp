//mridul1809
#include<bits/stdc++.h>
using namespace std;

class Trie {

public:

	//N is number of possible characters in a string
	const static int N = 2,B = 30;

	//baseChar defines the base character for possible characters
	//like '0' for '0','1','2'... as possible characters in string 
    const static char baseChar = 'a';

	struct TrieNode
	{
		int next[N];
		//if isEnd is set to true , a string ended here
		bool isEnd;
		//freq is how many times this prefix occurs
    	int freq;

		TrieNode()
		{
			for(int i=0;i<N;i++)
				next[i] = -1;
			isEnd = false;
			freq = 0;
		}
	};

	//the implementation is via vector and each position in this vector
	//is similar as new pointer in pointer type implementation
	vector <TrieNode> tree;

	//Base Constructor
	Trie ()
	{
		tree.push_back(TrieNode());
	}

	//inserting a string in trie
	void insert(const int x)
    {
        int p = 0;
        tree[p].freq++;
        for(int i=B;i>=0;i--)
        {
        	// tree[]
            int b=(x&(1<<i)?1:0);
            if(tree[p].next[b] == -1)
            {
                tree.push_back(TrieNode());
                tree[p].next[b] = tree.size()-1;
            }

            p = tree[p].next[b];
            tree[p].freq++;
        }
        tree[p].isEnd = true;
    }

    //check is string exists
    bool checkNumber(const int x)
    {
    	int p = 0;
    	for(int i=B;i>=0;i--){
            int b=(x&(1<<i)?1:0);
    		if(tree[p].next[b] == -1)
    			return false;

    		p = tree[p].next[b];
    	}

    	return tree[p].isEnd;
    }

    int max_xor(const int x){
        int p = 0,ans=0;
        for(int i=B;i>=0;i--){
            int b=(x&(1<<i)?0:1);
            if(tree[p].next[b] == -1){
                p = tree[p].next[b^1];
            }
            else{
                p = tree[p].next[b];
                ans+=(1<<i);
            }
        }

        return ans;
    }

    int min_xor(const int x){
        int p = 0,ans=0;
        for(int i=B;i>=0;i--){
            int b=(x&(1<<i)?1:0);
            if(tree[p].next[b] == -1){
                p = tree[p].next[b^1];
            }
            else{
                p = tree[p].next[b];
                ans+=(1<<i);
            }
        }

        return ans;
    }
};
