#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

#define maxn 100010
#define max(a, b) (a>b?a:b)
#define min(a, b) (a<b?a:b)
#define LL long long
#define ULL unsigned long long
#define UInt unsigned int
const ULL ULLMIN = 0;
const ULL ULLMAX = ~(ULL)(1<<63);
int n, m, l, r, t;
struct OP1 { UInt s, m, r; } op1[maxn];
struct OP2 { UInt t, l, r; } op2[maxn];
vector<UInt> st[maxn], et[maxn];

int oprcmp(const OP2 &a, const OP2 &b)
{
    if (a.l == b.l) return a.r < b.r;
    return a.l < b.l;
}

struct NodeTimeSeg 
{ 
    NodeTimeSeg *ch[2], *fa; 
    ULL value, totalSeg, numberSeg, totalVal; // Seg length of current node, 
    //seg number in total, seg number of current length, seg length in total;
    // NodeTimeSeg() :value(0), totalSeg(0), numberSeg(0), totalVal(0) {};
};

struct NodeTime
{ 
    NodeTime *ch[2], *fa;
    ULL value;
    // NodeTime() :value(0) {};
};

template<typename NODETYPE, size_t BUFFSIZE>
class SplayTree
{
public:
    bool Init()
    {
        _buffsize = 0;
        memset(_buff, 0, sizeof(_buff));
        nil = _buff + _buffsize++;
        nil->fa = nil->ch[0] = nil->ch[1] = nil;
        root = GetNode(ULLMIN, nil);
        root->ch[1] = GetNode(ULLMAX, root);
        UpdateInternal(root->ch[1]);
        UpdateInternal(root);
        return true;
    }

    inline void FindValue(ULL value, NODETYPE *&p, NODETYPE *&q)
    {
        while (p != nil)
        {
            if (p->value == value) break;
            else if (p->value > value) { q = p; p = p->ch[0]; }
            else if (p->value < value) { q = p; p = p->ch[1]; }
            else continue;
        }
    }

    inline NODETYPE* FindPrev(ULL value)
    {
        NODETYPE *p = root, *q = NULL;
        while (p != nil)
        {
            if (p->value < value) q = p, p = p->ch[1];
            else p = p->ch[0];
        }
        return q;
    }

    inline NODETYPE* FindNext(ULL value)
    {
        NODETYPE *p = root, *q = NULL;
        while (p != nil)
        {
            if (p->value > value) q = p, p = p->ch[0];
            else p = p->ch[1];
        }
        return q;
    }

    bool Insert(ULL value)
    {
        if (value == 0) return false;
        NODETYPE *p = root, *q = NULL;
        FindValue(value, p, q);
        return InsertInternal(p, q, value);
    }

    bool Delete(ULL value)
    {
        if (value == 0) return false;
        NODETYPE *p = root, *q = NULL;
        FindValue(value, p, q);
        return DeleteInternal(p, value);
    }

protected:
    NODETYPE _buff[BUFFSIZE], *root = NULL, *nil = NULL;
    ULL _buffsize;

    virtual void GetNodeInternal(ULL value, NODETYPE* x, NODETYPE* fa) = 0;
    virtual void UpdateInternal(NODETYPE* x) = 0;
    virtual bool InsertInternal(NODETYPE* p, NODETYPE* q, ULL value) = 0;
    virtual bool DeleteInternal(NODETYPE* p, ULL value) = 0;

    NODETYPE* GetNode(ULL value, NODETYPE* fa)
    {
        NODETYPE* x = NULL;
        x = _buff + _buffsize++;
        x->ch[0] = x->ch[1] = nil;
        x->value = value;
        x->fa = fa;
        GetNodeInternal(value, x, fa);
        return x;
    }

    inline void Rotate(NODETYPE* x, bool isRightRotate)
    {
        NODETYPE* xfa = x->fa;
        xfa->ch[!isRightRotate] = x->ch[isRightRotate];
        xfa->ch[!isRightRotate]->fa = xfa;
        x->fa = xfa->fa;
        xfa->fa->ch[0] == xfa ? x->fa->ch[0] = x : x->fa->ch[1] = x;
        xfa->fa = x; x->ch[isRightRotate] = xfa;
        UpdateInternal(xfa);
        if (xfa == root) root = x;
    }

    bool Splay(NODETYPE* x, NODETYPE *fa)
    {
        while (x->fa != fa)
        {
            if (x->fa->fa == fa) {
                x->fa->ch[0] == x ? Rotate(x, true) : Rotate(x, false);
            } else {
                if (x->fa->fa->ch[0] == x->fa) {
                    if (x->fa->ch[0] == x) Rotate(x->fa, true), Rotate(x, true);
                    else Rotate(x, false), Rotate(x, true);
                } else {
                    if (x->fa->ch[0] == x) Rotate(x, true), Rotate(x, false);
                    else Rotate(x->fa, false), Rotate(x, false);
                }
            }
        }
        UpdateInternal(x);
        return true;
    }
};

class SplayTreeTimeSeg : public SplayTree<NodeTimeSeg, maxn << 2>
{
public:
    void Select(ULL value, ULL &size1, ULL &size2)
    {
        NodeTimeSeg *p = root, *q = NULL;
        FindValue(value, p, q);
        if (p == nil) p = FindNext(value);
        Splay(p, nil);
        size1 = root->ch[0]->totalVal;
        size2 = root->totalSeg - root->ch[0]->totalSeg - 1; // there exists a minimum number 0.
    }

protected:
    virtual void UpdateInternal(NodeTimeSeg* p)
    {
        if (p->numberSeg < 0) p->numberSeg = 0;
        p->totalSeg = p->ch[0]->totalSeg + p->ch[1]->totalSeg + p->numberSeg;
        p->totalVal = p->ch[0]->totalVal + p->ch[1]->totalVal + p->numberSeg * p->value;
    }
 
    virtual void GetNodeInternal(ULL value, NodeTimeSeg* x, NodeTimeSeg* fa)
    {
        x->totalVal = value;
        x->totalSeg = x->numberSeg = 1;
    }

    virtual bool InsertInternal(NodeTimeSeg* p, NodeTimeSeg* q, ULL value)
    {
        if (p != nil)
        {
            p->numberSeg += 1;
            p->totalSeg += 1;
            p->totalVal += value;
        }
        else
        {
            p = GetNode(value, q);
            value < q->value ? q->ch[0] = p : q->ch[1] = p;
        }
        Splay(p, nil);
        return true;
    }

    virtual bool DeleteInternal(NodeTimeSeg* p, ULL value)
    {
        if (p == nil) return false;
        p->numberSeg -= 1;
        p->totalSeg -= 1;
        p->totalVal -= value;
        Splay(p, nil);
        return false;
    }
};

class SplayTreeTime : public SplayTree<NodeTime, maxn << 2>
{
public:
    ULL m_a, m_b, m_c;

protected:
    virtual void GetNodeInternal(ULL value, NodeTime* x, NodeTime* fa) { return; }
    virtual void UpdateInternal(NodeTime* x) { return; }
    virtual bool InsertInternal(NodeTime* p, NodeTime* q, ULL value)
    {
        if (p == nil)
        {
            p = GetNode(value, q);
            value > q->value ? q->ch[1] = p : q->ch[0] = p;
            Splay(p, nil); 
            NodeTime *p1 = root->ch[0]; while (p1->ch[1] != nil) p1 = p1->ch[1];
            NodeTime *p2 = root->ch[1]; while (p2->ch[0] != nil) p2 = p2->ch[0];
            m_b = value; m_a = p1->value; m_c = p2->value;
            return true;
        }
        return false;
    }

    virtual bool DeleteInternal(NodeTime* p, ULL value)
    {
        if (p != nil)
        {
            Splay(p, nil);
            NodeTime *p1 = root->ch[0]; while (p1->ch[1] != nil) p1 = p1->ch[1];
            NodeTime *p2 = root->ch[1]; while (p2->ch[0] != nil) p2 = p2->ch[0];
            Splay(p1, nil); Splay(p2, root);
            m_a = p1->value; m_b = value; m_c = p2->value;
            p2->ch[0] = nil;
            return true;
        }
        return false;
    }

public:
    ULL GetMin() { return FindNext(ULLMIN)->value; }
    ULL GetMax() { return FindPrev(ULLMAX)->value; }
};

SplayTreeTime t2;
SplayTreeTimeSeg t1;

int main() 
{
    int tst = 1, ted = 1, sst, sed;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%u %u %u", &op1[i].s, &op1[i].m, &op1[i].r);
    scanf("%d", &m);
    scanf("%u %u %u", &op2[1].t, &op2[1].l, &op2[1].r);
    for (int i = 1, j = 2; i <= m; ++i) 
    {   // combine two querys like (1, 1, 4) & (1, 4, 7) into one query (1, 1, 7)
        
        i == m ? op2[j].t = ULLMAX, op2[j].l = ULLMIN, op2[j].r = ULLMAX : scanf("%u %u %u", &op2[j].t, &op2[j].l, &op2[j].r);
        if (op2[j].t != op2[j - 1].t)
        {
            if (ted > tst) 
            {
                sort(op2 + tst, op2 + ted + 1, oprcmp);
                for (sst = tst, sed = tst + 1; sed <= ted; ++sed)
                {
                    if (op2[sed].l <= op2[sst].r + 1) op2[sst].r = max(op2[sst].r, op2[sed].r);
                    else op2[++sst] = op2[sed];
                }
                op2[++sst] = op2[j]; j = sst;
            }
            tst = ted = j++;
        }
        else 
            ted = j++;
    }
    for (int i = 1; i < ted; ++i) 
    {
        st[op2[i].l].push_back(op2[i].t);
        et[op2[i].r].push_back(op2[i].t);
    }
    t1.Init(), t2.Init();
    ULL a, b, c, cover = 0;
    ULL ans = 0, size1, size2;
    bool ret = 0, flag = false;
    for (int i = 1; i <= n; ++i) // Deal with each magic unit.
    {
        for (int j = 0; j < st[i].size(); ++j) 
        {
            if (st[i][j] == 0) flag = true;
            ++cover;
            ret = t2.Insert(st[i][j]);
            // printf("insert: %d %d %d\n", a, b, c);
            if (!ret) continue;
            a = t2.m_a, b = t2.m_b, c = t2.m_c;
            // printf("insert: %d %d %d\n", a, b, c);
            if (c != ULLMAX) t1.Delete(c - a), t1.Insert(c - b);
            t1.Insert(b - a);
        }
        // printf("T1 Sum: %d\n", t1.totalVal);
        if (cover > 0 && op1[i].m > 0)
            if (op1[i].r > 0) 
            {
                ULL mint = flag ? 0 : t2.GetMin();
                ULL tmp = (op1[i].m + op1[i].r - 1) / op1[i].r;
                t1.Select(tmp, size1, size2);
                mint < tmp ? size1 -= mint : --size2; 
                ans += size1 * (ULL)op1[i].r + size2 * (ULL)op1[i].m; // most value.
                tmp = (op1[i].m - op1[i].s + op1[i].r - 1) / op1[i].r;
                ans += mint < tmp ? mint * (ULL)op1[i].r + op1[i].s : op1[i].m; // initial value.
            }
            else 
                ans += (ULL)op1[i].s;

        for (int j = 0; j < et[i].size(); ++j) 
        {
            if(et[i][j] == 0) flag = false;
            --cover;
            ret = t2.Delete(et[i][j]);
            if (!ret) continue;
            a = t2.m_a, b = t2.m_b, c = t2.m_c;
            t1.Delete(b - a);
            if (c != ULLMAX) t1.Delete(c - b), t1.Insert(c - a);
        }
    }
    printf("%llu\n", ans);
    return 0;
}
