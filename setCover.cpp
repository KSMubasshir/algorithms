#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <istream>
#include <sstream>
using namespace std;

int setCount=0;
std::ostream& operator<<(std::ostream& os, const std::set<int>& s) {
    std::copy(s.begin(), s.end(),std::ostream_iterator<int>(os," "));
    os<<endl;
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& s) {
    os << "";
    typename std::vector<T>::const_iterator it = s.begin();
    for( ; it != s.end(); ++it)
        os << *it;

    os << "";
    return os;
}

void setCover(vector< set<int> >& input, set<int>& target, vector< set<int> >& output)
{
    set<int> full=target;
    for(int i = input.size() - 1; i > 0; --i){
        vector<bool> vec(input.size(), false);
        fill(vec.begin() + i, vec.end(), true);
        set<int> comb;
        do{
            for(int j = 0; j < vec.size(); ++j){
                if(vec[j]){
                    comb.insert(input[j].begin(),input[j].end());
                }
            }

            if(includes(comb.begin(), comb.end(), target.begin(), target.end())){
                for(int j = 0; j < vec.size(); ++j){
                    if(vec[j]){
                        output.push_back(input[j]);
                        setCount++;
                    }
                }
                return;
            }
            comb.clear();
        }while(next_permutation(vec.begin(), vec.end()));
    }
}

int main()
{
    int i=0;
    int enterNumber;
    string line;
    ifstream myfile ("data/set_cover_input.txt");
    int n,m;
    getline(myfile,line);
    istringstream iss(line);
    iss >>n>>m;
    vector<set<int> > inputSets,outputSets;
    set<int> universe;
    for(i=1;i<=n;i++)
        universe.insert(i);
    set<int> temp;
    if (myfile.is_open())
    {
        for(i=0;i<m;i++)
        {
            getline(myfile,line);
            istringstream iss(line);
            while (iss >> enterNumber)
            {
                temp.insert(enterNumber);
            }
            inputSets.push_back(temp);
            temp.clear();
        }
        if(i==m)
        {
            myfile.close();
        }
    }
    setCover(inputSets,universe,outputSets);
    cout<<setCount<<endl;
    cout<<outputSets<<endl;
    return 0;
}
