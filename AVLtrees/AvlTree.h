#ifndef Hasturas
#define Hasturas
#include "iostream"
using namespace std;
template<class KEY, class OTHER>
struct SET
{
	KEY key = 0;
	OTHER other = 0;
	SET( KEY X,  OTHER Y)
	{
		key = X;
		other = Y;
	}
};
template <class KEY, class OTHER>
class AvlTree
{
    struct AvlNode
    {
        SET<KEY, OTHER>   data;
        AvlNode* left;
        AvlNode* right;
        int                     height;           //结点的高度

        AvlNode(const SET<KEY, OTHER>& element, AvlNode* lt, AvlNode* rt, int h = 1)
            : data(element), left(lt), right(rt), height(h) { }
    };

    AvlNode* root;
public:
    AvlTree() { root = NULL; }
    ~AvlTree() { makeEmpty(root); }
    SET<KEY, OTHER>* find(const KEY& x) const;
    bool insert(const SET<KEY, OTHER>& x);
    void remove(const KEY& x);
	bool insert(const SET<KEY, OTHER>& x, AvlNode*& t);
private:
    bool remove(const KEY& x, AvlNode*& t);
    void makeEmpty(AvlNode* t);
    int height(AvlNode* t) const { return t == NULL ? 0 : t->height; }
    void LL(AvlNode*& t);
    void LR(AvlNode*& t);
    void RL(AvlNode*& t);
    void RR(AvlNode*& t);
    int max(int a, int b) { return (a > b) ? a : b; }
    bool adjust(AvlNode*& t, int subTree);
};
//realize functions
template <class KEY, class OTHER>
SET<KEY, OTHER>* AvlTree<KEY, OTHER>::find(const KEY& x) const
{
	AvlNode* t = root;
    while (t != NULL && t->data.key != x)
    {
		if (t->data.key > x) t = t->left;
		else t = t->right;
	}
	if (t == NULL) return NULL;
	else return (SET<KEY, OTHER>*)t;
}
template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER>& x)
{
	return insert(x, root);
}
template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER>& x, AvlNode*& t)
{
    static bool signal = 0;
	if (t == NULL) t = new AvlNode(x, NULL, NULL);
    else if (x.key < t->data.key)
    {
		insert(x, t->left);
        if (height(t->left) - height(t->right) == 2)
        {
			if (x.key < t->left->data.key) LL(t);
			else LR(t);
            signal = 1;
		}
	}
    else if (x.key > t->data.key)
    {
		insert(x, t->right);
        if (height(t->right) - height(t->left) == 2)
        {
			if (x.key > t->right->data.key) RR(t);
			else RL(t);
            signal = 1;
		}
	}
	t->height = max(height(t->left), height(t->right)) + 1;
	return signal;
}
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::remove(const KEY& x)
{
	remove(x, root);
}
template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::remove(const KEY& x, AvlNode*& t)
{
	bool signal = 0;
	if (t == NULL) return 0;
    else if (x < t->data.key)
    {
		remove(x, t->left);
        if (height(t->right) - height(t->left) == 2)
        {
			if (height(t->right->right) >= height(t->right->left)) RR(t);
			else RL(t);
			signal = 1;
		}
	}
    else if (x > t->data.key)
    {
		remove(x, t->right);
        if (height(t->left) - height(t->right) == 2)
        {
			if (height(t->left->left) >= height(t->left->right)) LL(t);
			else LR(t);
			signal = 1;
		}
	}
    else if (t->left != NULL && t->right != NULL)
    {
		AvlNode* tmp = t->right;
		while (tmp->left != NULL) tmp = tmp->left;
		t->data = tmp->data;
		remove(t->data.key, t->right);
        if (height(t->left) - height(t->right) == 2)
        {
			if (height(t->left->left) >= height(t->left->right)) LL(t);
			else LR(t);
			signal = 1;
		}
	}
    else
    {
		AvlNode* oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
		return 1;
	}
	t->height = max(height(t->left), height(t->right)) + 1;
	return signal;
}
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::makeEmpty(AvlNode* t)
{
	if (t == NULL) return;
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
}
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LL(AvlNode*& t)
{
	AvlNode* t1 = t->left;
	t->left = t1->right;
	t1->right = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	t1->height = max(height(t1->left), t->height) + 1;
	t = t1;
}
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR(AvlNode*& t)
{
	AvlNode* t1 = t->right;
	t->right = t1->left;
	t1->left = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	t1->height = max(height(t1->right), t->height) + 1;
	t = t1;
}
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LR(AvlNode*& t)
{
	RR(t->left);
	LL(t);
}
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RL(AvlNode*& t)
{
	LL(t->right);
	RR(t);
}
template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::adjust(AvlNode*& t, int subTree)
{
	if (subTree == 1)
	{
		if (t->left->height - t->right->height == 1) return 1;
		else if (t->left->height - t->right->height == 0)
		{
			t->height--;
			return 0;
		}
		else
		{
			if (t->left->right->height > t->left->left->height) LR(t);
			else LL(t);
			return 0;
		}
	}
	else
	{
		if (t->right->height - t->left->height == 1) return 1;
		else if (t->right->height - t->left->height == 0)
		{
			t->height--;
			return 0;
		}
		else
		{
			if (t->right->left->height > t->right->right->height) RL(t);
			else RR(t);
			return 0;
		}
	}
}


#endif //Hasturas