#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;

map<string, vector<string>> category;
map<string, vector<string>> bookname;
map<string, vector<string>>::iterator mapIter;
vector<string> vec, root;
string strTmp, strZero("0");
void dfs_print(string key, int cls)
{
    map<string, vector<string>>::iterator mapIter;
    int pos = key.find_last_of("/") + 1;
    string newkey = key.substr(pos, key.size() - pos);
    cout << setw((cls << 2) + newkey.size()) << newkey << endl;
    mapIter = category.find(key);
    if (mapIter != category.end())
    {
        vector<string>::iterator vecIter;
        vector<string> cate = mapIter->second;
        sort(cate.begin(), cate.end());
        vecIter = unique(cate.begin(), cate.end());
        cate.erase(vecIter, cate.end());
        for (vecIter = cate.begin(); vecIter != cate.end(); ++vecIter)
            dfs_print(*vecIter, cls + 1);
    }
    mapIter = bookname.find(key);
    if (mapIter != bookname.end())
    {
        vector<string>::iterator vecIter;
        vector<string> book = mapIter->second;
        sort(book.begin(), book.end());
        vecIter = unique(book.begin(), book.end());
        book.erase(vecIter, book.end());
        for (vecIter = book.begin(); vecIter != book.end(); ++vecIter)
        {
            string key = *vecIter;
            int pos = key.find_last_of("/") + 1;
            key = key.substr(pos, key.size() - pos);
            cout << setw(((cls+1) << 2) + key.size()) << key << endl;
        }
            
    }

}

void split(const std::string &src, char delim, std::vector<std::string> &des) 
{
    std::stringstream ss(src);
    std::string item;
    while (std::getline(ss, item, delim)) des.push_back(item);
}

void Insert(map<string, vector<string>>& imap, string pa, string ch)
{
    mapIter = imap.find(pa);
    if (mapIter == imap.end())
    {
        vector<string> tmp;
        tmp.push_back(ch);
        pair<string, vector<string>> elem(pa, tmp);
        imap.insert(elem);
    }
    else
    {
        vector<string>& tmp = mapIter->second;
        tmp.push_back(ch);
    }
}
int main()
{
    vector<string>::iterator vecIter, rootIter;
    int Case = 0;
    while (getline(cin, strTmp))
    {
        if (strTmp.compare(strZero) == 0)
        {
            printf("Case %d:\n", ++Case);
            sort(root.begin(), root.end());
            rootIter = unique(root.begin(), root.end());
            root.erase(rootIter, root.end());
            for(rootIter = root.begin(); rootIter != root.end(); ++rootIter)
                dfs_print(*rootIter, 0);
            vec.clear();
            root.clear();
            category.clear();
            bookname.clear();
            continue;
        }
        split(strTmp, '/', vec);
        if (vec.size() == 0) continue;
        if (vec.size() == 1) { root.push_back(vec[0]);  continue; }
        string pa, ch;
        for (vecIter = vec.begin(), root.push_back(*vecIter); vecIter + 1 != vec.end(); ++vecIter)
        {
            if (vecIter == vec.begin())
            {
                root.push_back(*vecIter);
                pa = *vecIter;
                ch = *vecIter + "/" + *(vecIter + 1);
            }
            else
            {
                pa = ch;
                ch = ch + "/" + *(vecIter + 1);
            }
            if (vecIter + 2 != vec.end()) Insert(category, pa, ch);
            else Insert(bookname, pa, ch);
        }
        vec.clear();
    }
    return 0;
}