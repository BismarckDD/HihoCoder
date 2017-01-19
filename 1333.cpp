#include <cstdio>
#include <cstring>

#define maxn 200010
#define maxm 200000
#define minkey 0
#define maxkey 1000000001
#define ll long long

struct NODE
{
    NODE *ch[2], *fa;
    ll id, val, lazy, sum, num;
};

struct SplayTree
{
    NODE _buff[maxn], *root = NULL, *nil = NULL;
    unsigned int _buffsize;

    NODE* GetNode(ll id, ll val, NODE *fa)
    {
        NODE *x = _buff + _buffsize++;
        x->fa = fa;
        x->ch[0] = x->ch[1] = nil;
        x->id = id, x->val = val, x->lazy = x->sum = x->num = 0;
        fa != nil ? (id < fa->id) ? fa->ch[0] = x : fa->ch[1] = x : fa->ch[0] = x;
        return x;
    }

    void Init()
    {
        _buffsize = 0;
        memset(_buff, 0, sizeof(_buff));
        nil = _buff + _buffsize++;
        nil->fa = nil->ch[0] = nil->ch[1] = nil;
        nil->id = nil->val = nil->lazy = nil->sum = 0;
        root = GetNode(minkey, minkey, nil);
        root->ch[1] = GetNode(maxkey, maxkey, root);
    }

    inline void push_up(NODE *x)
    {
        x->num = 1;
        x->sum = x->val;
        for (int i = 0; i <= 1; ++i)
        {
            if (x->ch[i] == nil) continue;
            x->num += x->ch[i]->num;
            x->sum += x->ch[i]->sum;
        }
    }

    inline void marking(NODE *x, ll lzay)
    {
        x->lazy = x->lazy + lzay;
        x->val = x->val + lzay;
        x->sum = x->sum + x->num * lzay;
        
    }

    inline void push_down(NODE *x)
    {
        // x->val += x->lazy;
        for (int i = 0; i <= 1; ++i)
        {
            if (x->ch[i] == nil) continue;
            marking(x->ch[i], x->lazy);
        }
        x->lazy = 0;
        push_up(x);
    }

    inline void Rotate(NODE* x, bool isRightRotate)
    {
        NODE* xfa = x->fa;
        push_down(xfa);
        push_down(x);
        xfa->ch[!isRightRotate] = x->ch[isRightRotate];
        xfa->ch[!isRightRotate]->fa = xfa;
        x->fa = xfa->fa;
        xfa->fa->ch[0] == xfa ? x->fa->ch[0] = x : x->fa->ch[1] = x;
        xfa->fa = x; x->ch[isRightRotate] = xfa;
        if (xfa == root) root = x;
        push_up(xfa);
        push_up(x);
    }

    void Splay(NODE* x, NODE *fa)
    {
        // push_down(x);
        while (x->fa != fa)
        {
            if (x->fa->fa == fa) {
                x->fa->ch[0] == x ? Rotate(x, true) : Rotate(x, false);
            }
            else {
                if (x->fa->fa->ch[0] == x->fa) {
                    if (x->fa->ch[0] == x) Rotate(x->fa, true), Rotate(x, true);
                    else Rotate(x, false), Rotate(x, true);
                }
                else {
                    if (x->fa->ch[0] == x) Rotate(x, true), Rotate(x, false);
                    else Rotate(x->fa, false), Rotate(x, false);
                }
            }
        }
        // push_up(x);
    }

    inline void Find(ll id, NODE *&p, NODE *&q)
    {
        p = root, q = NULL;
        while (p != nil)
        {
            if (p->id == id) break;
            else if (p->id > id) { q = p; p = p->ch[0]; }
            else { q = p; p = p->ch[1]; }
        }
    }

    inline NODE* FindPrev(ll id)
    {
        NODE *p = root, *q = NULL;
        while (p != nil)
        {
            if (p->id < id) q = p, p = p->ch[1];
            else p = p->ch[0];
        }
        return q;
    }

    inline NODE* FindNext(ll id)
    {
        NODE *p = root, *q = NULL;
        while (p != nil)
        {
            if (p->id > id) q = p, p = p->ch[0];
            else p = p->ch[1];
        }
        return q;
    }

    NODE* Insert(ll id, ll val)
    {
        NODE *p = root, *q = NULL;
        while (p != nil)
        {
            ++p->num;
            push_down(p);
            if (p->id == id) break;
            else if (p->id > id) q = p, p = p->ch[0];
            else if (p->id < id) q = p, p = p->ch[1];
            else continue;
        }
        if (p == nil) p = GetNode(id, val, q);
        Splay(p, nil);
        return p;
    }

    ll Query(ll st, ll ed) 
    { 
        NODE *p1 = FindPrev(st);
        NODE *p2 = FindNext(ed);
        Splay(p1, nil); Splay(p2, root);
        NODE *p3 = p2->ch[0];
        // push_up(p2); push_up(p1);
        return p3 == nil ? 0 : p3->sum;
    }

    void Delete(ll st, ll ed)
    {
        NODE *p1 = FindPrev(st);
        NODE *p2 = FindNext(ed);
        Splay(p1, nil); Splay(p2, root);
        p2->ch[0] = nil;
        // push_up(p2); push_up(p1);
    }

    void Update(ll st, ll ed, ll lzay)
    {
        NODE *p1 = FindPrev(st);
        NODE *p2 = FindNext(ed);
        Splay(p1, nil); Splay(p2, root);
        marking(p2->ch[0], lzay);
        // push_up(p2); push_up(p1);
    }
} stree;

int main()
{
    int n;
    ll id, val, st, ed;
    char ch[2];
    scanf("%d", &n);
    stree.Init();
    while (n--)
    {
        scanf("%s", &ch);
        switch (ch[0])
        {
        case 'I':
            scanf("%lld %lld", &id, &val);
            stree.Insert(id, val);
            break;
        case 'D':
            scanf("%lld %lld", &st, &ed);
            st = (st <= minkey) ? minkey + 1 : st;
            ed = (ed >= maxkey) ? maxkey - 1 : ed;
            stree.Delete(st, ed);
            break;
        case 'Q':
            scanf("%lld %lld", &st, &ed);
            st = (st <= minkey) ? minkey + 1 : st;
            ed = (ed >= maxkey) ? maxkey - 1 : ed;
            printf("%lld\n", stree.Query(st, ed));
            break;
        case 'M':
            scanf("%lld %lld %lld", &st, &ed, &val);
            st = (st <= minkey) ? minkey + 1 : st;
            ed = (ed >= maxkey) ? maxkey - 1 : ed;
            stree.Update(st, ed, val);
        default:
            break;
        }
    }
    return 0;
}
