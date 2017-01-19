#include <cstdio>
#include <cstring>

#define maxn 200010
#define maxm 200000
#define minkey 0
#define maxkey 1000000001

struct NODE
{
    NODE *ch[2], *fa;
    unsigned int value;
};

struct SplayTree
{
    NODE _buff[maxn<<2], *root = NULL, *nil = NULL;
    unsigned int _buffsize;
    unsigned int ans[maxn];
    int cnt = 0;

    void clear()
    {
        memset(_buff, 0, sizeof(_buff));
        root = nil = NULL;
        Init();
    }

    NODE* GetNode(unsigned int value, NODE *fa)
    {
        NODE *x = _buff + _buffsize++;
        x->fa = fa;
        x->ch[0] = x->ch[1] = nil;
        x->value = value;
        fa != nil ? (value < fa->value) ? fa->ch[0] = x : fa->ch[1] = x : fa->ch[0] = x;
        return x;
    }

    void Init()
    {
        _buffsize = 0;
        memset(_buff, 0, sizeof(_buff));
        nil = _buff + _buffsize++;
        nil->fa = nil->ch[0] = nil->ch[1] = nil;
        root = GetNode(minkey, nil);
        root->ch[1] = GetNode(maxkey, root);
    }

    inline void FindValue(unsigned int value, NODE *&p, NODE *&q)
    {
        p = root, q = NULL;
        while (p != nil)
        {
            if (p->value == value) break;
            else if (p->value > value) { q = p; p = p->ch[0]; }
            else { q = p; p = p->ch[1]; }
        }
    }

    NODE* FindPrevValue(unsigned int value)
    {
        NODE *p = root, *q = NULL;
        FindValue(value, p, q);
        Splay(p, nil);
        q = p->ch[0];
        while (q->ch[1] != nil) q = q->ch[1];
        return q;
    }

    NODE* FindNextValue(unsigned int value)
    {
        NODE *p = root, *q = NULL;
        FindValue(value, p, q);
        Splay(p, nil);
        q = p->ch[1];
        while (q->ch[0] != nil) q = q->ch[0];
        return q;
    }

    NODE* Insert(unsigned int value)
    {
        NODE *p = root, *q = NULL;
        FindValue(value, p, q);
        if (p == nil) p = GetNode(value, q);
        Splay(p, nil);
        return p;
    }

    void Delete(unsigned int st, unsigned int ed)
    {
        Insert(st);
        NODE *p1 = FindPrevValue(st);
        Insert(ed);
        NODE *p2 = FindNextValue(ed);
        Splay(p1, nil); Splay(p2, root);
        p2->ch[0] = nil;
    }

    void Delete(unsigned int value)
    {
        NODE *p = root, *q = NULL;
        FindValue(value, p, q);
        if (p != nil)
        {
            // printf("Enter Delete\n");
            Splay(p, nil);
            NODE *p1 = FindPrevValue(value); 
            NODE *p2 = FindNextValue(value); 
            Splay(p1, nil); Splay(p2, root);
            p2->ch[0] = nil;
        }
    }

    void Rotate(NODE* x, bool isRightRotate)
    {
        NODE* xfa = x->fa;
        xfa->ch[!isRightRotate] = x->ch[isRightRotate];
        xfa->ch[!isRightRotate]->fa = xfa;
        x->fa = xfa->fa;
        xfa->fa->ch[0] == xfa ? x->fa->ch[0] = x : x->fa->ch[1] = x;
        xfa->fa = x; x->ch[isRightRotate] = xfa;
        if (xfa == root) root = x;
    }

    void Splay(NODE* x, NODE *fa)
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
    }

    unsigned int Query(unsigned int value)
    {
        NODE *p = root, *q = nil;
        unsigned int ans;
        while (p != nil)
        {
            if (p->value == value) return value;
            else if (p->value > value) {
                if (p->ch[0] == nil) return ans;
                else { q = p; p = p->ch[0]; }
            }
            else {
                ans = p->value;
                q = p; p = p->ch[1];
            }
        }
        return ans;
    }

    void InOrderHelper()
    {
        printf("root(%d): %d, ", root->fa == nil, root->value);
        InOrder(root);
        cnt = 0;
        printf("\n");
    }

    void InOrder(NODE *root)
    {
        if (root->ch[0] != nil) InOrder(root->ch[0]);
        // printf("%u ", root->value);
        ans[cnt++] = root->value;
        if (root->ch[1] != nil) InOrder(root->ch[1]);
    }
} stree;

int main()
{
    int n, key, st, ed;
    char ch[2];
    scanf("%d", &n);
    stree.Init();
    while (n--)
    {
        scanf("%s", &ch);
        switch (ch[0])
        {
        case 'I':
            scanf("%d", &key);
            stree.Insert(key);
            break;
        case 'D': 
            scanf("%d %d", &st, &ed);
            st = (st <= minkey) ? minkey + 1 : st;
            ed = (ed >= maxkey) ? maxkey - 1 : ed;
            stree.Delete(st, ed);
            break;
        case 'Q': 
            scanf("%d", &key);
            printf("%d\n", stree.Query(key));
            break;
        default:
            break;
        }
    }
    return 0;
}
