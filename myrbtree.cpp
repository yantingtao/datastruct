/**********************************
作者:颜廷涛
时间:2016.3.31
内容:红黑树代码实现
**********************************/
#include <iostream>
#include <string>
using namespace std;
#define BLACK 0
#define RED 1
template <class T>
class my_rbtree;//前置声明
/*
类名:my_rbnode(红黑树节点)
 */
template <class T>
class my_rbnode
{
	friend class my_rbtree<T>;//友元
  public:
  	my_rbnode(T _data)
  	{
  		data = _data;
  		colour = RED;//默认为红色
  		left = NULL;
  		right = NULL;
  		parent = NULL;
  	}
 private:
 	T data;//元素值
 	int colour;//颜色
 	my_rbnode<T>* left;//左孩子
 	my_rbnode<T>* right;//右孩子
 	my_rbnode<T>* parent;//父节点
};
/*
类名:my_rbtree
 */
template <class T>
class my_rbtree
{
   public:
       my_rbtree()
       {
       	  root = NULL;
       }
       /*函数名:rb_left_rotate
         函数作用:左旋
         参数:my_rbnode<T> *node(旋转的节点)
         返回值:无
       */
      void rb_left_rotate(my_rbnode<T> *node)
      {
         my_rbnode<T>* node_right = node->right;
         //断开node->node_right的指针,并把node_right->left的孩子赋值给node
         //赋值前判断node_right->left是否为空
         node->right = node_right->left;
         if ( node->right != NULL)
         {
             node_right->left->parent = node;
         }
         //断开node_right->node的指针并把node->parent赋值给 node_right的父指针
         node_right->parent = node->parent;
         if (node_right->parent != NULL)
         {
          //判断node是node->parent的左孩子还是右孩子来确定node_right的位置
         	 if (node == node_right->parent->left)
         	 {
         	 	node->parent->left = node_right;
         	 }
         	 else
         	 {
         	 	node->parent->right = node_right;
         	 }
         }
         else//如果node的父指针为空说明node为root,现在node_right为node的父指针,则root为node_right
         {
         	 root = node_right;
         }
          node_right->left = node;
         node->parent = node_right;
      }
         /*函数名:rb_right_rotate
           函数作用:右旋
           参数:my_rbnode<T> *node(旋转的节点)
           返回值:无
       */
      void rb_right_rotate(my_rbnode<T> *node)
      {
      	 my_rbnode<T>* node_left = node->left;
      	 node->left = node_left->right;
      	 if (node->left != NULL)
      	 {
      	 	node_left->right->parent = node;
      	 }
      	 node_left->left = node;
      	 node_left->parent = node->parent;
      	 if (node_left->parent != NULL)
      	 {
             if (node == node->parent->left)
             {
             	node->parent->left = node_left;
             }
             else
             {
             	node->parent->right = node_left;
             }
      	 }
      	 else
      	 {
      	 	root = node_left;
      	 }

      	 node->parent = node_left;
      }

      /*函数名:rbtree_insert_rebalance
        函数作用:插入的修复
        参数:my_rbnode<T>* node(插入的节点)
        返回值:无
       */
     void rbtree_insert_rebalance(my_rbnode<T>* node)
      {
      	  my_rbnode<T>* node_parent = NULL;
          my_rbnode<T>* node_grandparent = NULL;
          my_rbnode<T>* node_uncle = NULL;
          my_rbnode<T>* tmp = NULL;//tmp为临时变量
          node_parent = node->parent;
      	 while (node_parent != NULL &&node_parent->colour == RED)
      	 {
              node_grandparent = node_parent->parent;
              if (node_parent == node_grandparent->left)
              {
              	   node_uncle = node_grandparent->right;
              	   if (node_uncle != NULL && node_uncle->colour == RED)
              	   {
                      node_parent->colour = BLACK;
                      node_uncle->colour = BLACK;
                      node_grandparent->colour = RED;
                      node = node_grandparent;//转移不平衡点
                      node_parent = node->parent;
              	   }
              	   else
              	   {
                     /*情况2 叔叔节点为黑色 且 当前节点的父节点为右孩子*/
                     if (node == node_parent->right)
                     {
                        rb_left_rotate(node_parent);
                        tmp = node_parent;
                        node_parent = node;
                        node = tmp;
                     }
                     //情况3 当前节点的父节点为红色,叔叔节点为黑色,当前节点是父节点的左孩子
                        rb_right_rotate(node_grandparent);
                        node_parent->colour = BLACK;
                        node_grandparent->colour = RED;
              	   }
              }
              else//树的对称性下面是上面的对称过去的情况
              { 
                  node_uncle = node_grandparent->left;
                  if (node_uncle != NULL && node_uncle->colour == RED)
                  {
                      node_parent->colour = BLACK;
                      node_uncle->colour = BLACK;
                      node_grandparent->colour = RED;
                      node = node_grandparent;//转移不平衡点
                      node_parent = node->parent;
                  }
                  else
                  {
                       if (node == node_parent->left)
                       {
                       	    rb_right_rotate(node_parent);
                            tmp = node_parent;
                            node_parent = node;
                            node = tmp;
                       }
                       node_parent->colour = BLACK;
                       node_grandparent->colour = RED;
                       rb_left_rotate(node_grandparent);
                  }
              }
      	 }

      	 root->colour = BLACK;
      }
      /*     
        函数名:rbtree_insert
        作用:插入元素
        参数:T _data(元素值)
        返回值:无
      */
      void rbtree_insert(T _data)
      {
         my_rbnode<T>* newnode = new my_rbnode<T>(_data);
         if (root == NULL)
         {
           root = newnode;
           root->colour = BLACK;
         }
         else
         {
            my_rbnode<T>* curr = root;
            my_rbnode<T>* tmp = NULL;
            while (curr != NULL)
            {   
                 tmp = curr;
                if (curr->data > _data)
                {
                    curr = curr->left;
                }
                else
                {
                   curr = curr->right;
                }
            }
          newnode->parent = tmp;
          if (tmp->data > _data)
          {
             tmp->left = newnode;
          }
          else
          {
             tmp->right = newnode;
          }
            rbtree_insert_rebalance(newnode);
         }
       
      }
      /*函数名:input_tree
        函数作用:把数组中的元素都插入到rbtree中
        参数:T a[](数组),int length(数组长度)
        返回值:无
        */
       void input_tree(T a[],int length)
      {
         int i;
         for (i = 0; i < length; i++)
         {
            rbtree_insert(a[i]);
         }        
      }
      /*
       函数名:rbtree_find
       函数作用:查找
       参数:T _data(查找的元素值)
       返回值:my_rbnode<T>*(返回一个指查找的元素的指针)
        */
      my_rbnode<T>* rbtree_find(T _data)
       {
           my_rbnode<T>* curr = root;
           while (curr != NULL)
           { 
              if (curr->data > _data)
              {
                  curr = curr->left;
              }
              else if (curr->data < _data)
              {
                 curr = curr->right;
              }
              else
              {
                 return curr;
              }
           }
           return NULL;
       }
       /*
        函数名:rbtree_delete
        函数作用:删除
        参数:T _data(删除的元素值)
        返回值:无*/
      void rbtree_delete(T _data)
      {   
          /*判断要删除的节点是否存在*/
          my_rbnode<T>* node = rbtree_find(_data);
          if (node == NULL)
          {
             return;
          }
          my_rbnode<T>* replace = node;//后继点
          my_rbnode<T>* node_child = NULL;
          my_rbnode<T>* node_parent =NULL;
          int node_colour = RED;
          //第一种没有孩子和只有一个孩子的情况
          if (node->left == NULL || node->right == NULL)
          {
             if (node->left != NULL)
             {
                node_child = node->left;
             }
             else
             {
                node_child = node->right;
             }
             node_parent = node->parent;
             node_colour = node->colour;
              if (node_child != NULL)
              {
                    node_child->parent = node_parent;
              }  
              //判断父节点是否为空
              if (node_parent != NULL)
                {
                  //判断node为node_parent的那边孩子
                  if (node == node_parent->left)
                  {
                    node_parent->left = node_child;
                  }
                  else
                  {
                    node_parent->right = node_child;
                  }             
                }
               else
               {
                root = node_child;//父节点为空则为root
               }
            
          }
          else
          {
            //当有删除点两个孩子时得寻找一个后继点得比删除点的左孩子大而比右孩子小
            //所以得从删除点的右孩子中找一个最小的点来做后继点
             replace = node->right;
             while (replace->left != NULL)
             {
                replace = replace->left;//找后继点
             }
             node_child = replace->right;
             node_parent = replace->parent;
             node_colour = replace->colour;
             //判断后继点的孩子是否为空
            if (node_child != NULL)
            {
               node_child->parent = node_parent;
            }
            //判断后继点的父节点是否为空
            if (node_parent != NULL)
            {
              if (node_parent->left == replace)
               {
                 node_parent->left = node_child;
               }
              else
              {
                node_parent->right = node_child;
              }
            }
            else
            {
               root = node_child;
            }
            replace->parent = node->parent;
            replace->colour = node->colour;
            replace->left = node->left;
            replace->right = node->right;
            if (node->parent != NULL)
            {
                if (node->parent->left == node)
                {
                   node->parent->left = replace;
                }
                else
                {
                   node->parent->right = replace;
                }
            }
            else
            {
               root = replace;
            }
            node->left->parent = replace;
            //当node的右孩子没有右孩子时 node的右孩子为后继点则node->right == NULL
            if (node->right != NULL)
            {
               node->right->parent = replace;
            }
            //当node的右孩子没有左孩子时,当node被删除了 node_parent也会变成NULL
            if (node_parent == node)
            {
               node_parent = replace;
            }
           
          }
          delete node;
          if (node_colour == BLACK)
          {
             rbtree_delete_rebalance(node_child,node_parent);
          }

      }
       
       /*
        函数名:rbtree_delete_rebalance
        函数作用:删除修复
        参数:my_rbnode<T>* node(后继点的右孩子),my_rbnode<T>* node_parent(后继点的右孩子的父节点)
        返回值:无*/
       void rbtree_delete_rebalance(my_rbnode<T>* node,my_rbnode<T>* node_parent)
       {
          my_rbnode<T>* brother = NULL;
          my_rbnode<T>* bro_left = NULL;
          my_rbnode<T>* bro_right = NULL;
           
          while ((!node || node->colour == BLACK) && node != root)
          {   
               //判断当前节点在父节点的位置
               if (node_parent->left == node)
               { 
                //兄弟节点
                  brother = node_parent->right;
                  //首先判断兄弟节点是否为红,如果为红直接涂黑并把父节点涂红后左旋转
                  //第一种情况
                  if (brother->colour == RED)
                  {
                     brother->colour = BLACK;
                     node_parent->colour = RED;
                     rb_left_rotate(node_parent);
                     //旋转后重新获取兄弟节点的位置
                     brother = node_parent->right;
                  }
                   //判断兄弟节点的孩子是否全黑
                   //第二种情况
                  if ((!brother->left || brother->left->colour == BLACK) &&
                     (!brother->right || brother->right->colour == BLACK))
                  {
                     brother->colour = RED;
                     //重新获取当前节点
                     node = node_parent;
                     node_parent = node->parent;
                  }
                  else
                  { //第三种情况
                    //兄弟节点的左孩子为红右孩子为黑
                    if (!brother->right || brother->right->colour == BLACK)
                    {    
                       bro_left = brother->left;
                        if (bro_left != NULL)
                        {
                           bro_left->colour = BLACK;
                        }
                        brother->colour = RED;
                        rb_right_rotate(brother);
                        brother = node_parent->right;
                    }
                    //第四种情况
                    //兄弟节点右孩子为红,左孩子颜色随意
                    brother->colour = node_parent->colour;
                    node_parent->colour = BLACK;
                    if (brother->right != NULL)
                    {
                       brother->right->colour = BLACK;
                    }
                    rb_left_rotate(node_parent);
                    node = root;
                    break;
                  }
               }
               else//是上面的对称情况
               {
                  brother = node_parent->left;
                  if (brother->colour == RED)
                  {
                     brother->colour = BLACK;
                     node_parent->colour = RED;
                     rb_right_rotate(node_parent);
                     brother = node_parent->left;
                  }
                  if ((!brother->left || brother->left->colour == BLACK) &&
                     (!brother->right || brother->right->colour == BLACK))
                  {
                      brother->colour = RED;
                      node = node_parent;
                      node_parent = node->parent;
                  }
                  else
                  {
                        if (!brother->left || brother->left->colour == BLACK)
                        {  
                            bro_right = brother->right;
                           if (bro_right != NULL)
                           {
                             bro_right->colour = BLACK;
                           }

                           brother->colour = RED;
                           rb_left_rotate(brother);
                           brother = node_parent->left;
                        }
                        brother->colour = node_parent->colour;
                        node_parent->colour = BLACK; 
                        if (brother->left != NULL)
                       {
                         brother->left->colour = BLACK;
                       }
                       rb_left_rotate(node_parent);
                       node = root;
                       break;  
                  }
               }
          }

          if (node != NULL)
          {
             node->colour = BLACK;
          }
       }

       /*
        函数名:pretree
        函数作用:前序遍历
        参数:my_rbnode<T>* node(根节点)
        返回值:无*/
      void pretree(my_rbnode<T>* node)
      {
      	  if (node != NULL)
      	  {
      	  	    cout<<node->data<<'\t';
              if (node->colour == BLACK)
              {
                 cout<<"黑色"<<endl;
              }
              else
              {
                 cout<<"红色"<<endl;
              }
      	  	  pretree(node->left);
            
      	  	  pretree(node->right);
      	  }
      }
      void pretree()
      {
         pretree(root);
      }
      /*
        函数名:midtree
        函数作用:中序遍历
        参数:my_rbnode<T>* node(根节点)
        返回值:无*/
      void midtree(my_rbnode<T>* node)
      {
          if (node != NULL)
          {
            
              midtree(node->left);
               cout<<node->data<<'\t';
              if (node->colour == BLACK)
              {
                 cout<<"黑色"<<endl;
              }
              else
              {
                 cout<<"红色"<<endl;
              }
              midtree(node->right);
          }
      }
      void midtree()
      {
         midtree(root);
      }
        /*
        函数名:lasttree
        函数作用:后序遍历
        参数:my_rbnode<T>* node(根节点)
        返回值:无*/
      void lasttree(my_rbnode<T>* node)
      {
          if (node != NULL)
          {
            
              lasttree(node->left);
         
              lasttree(node->right);
              cout<<node->data<<'\t';
              if (node->colour == BLACK)
              {
                 cout<<"黑色"<<endl;
              }
              else
              {
                 cout<<"红色"<<endl;
              }
          }
      }
      void lasttree()
      {
         lasttree(root);
      }
   private:
   	my_rbnode<T>* root;
};
int main(int argc, char const *argv[])
{
	my_rbtree<char>  rb1;
	char ch[] = "1234456789";
    rb1.input_tree(ch,10);
    //rb1.pretree();
   rb1.rbtree_delete('8');
      rb1.rbtree_delete('7');
    // rb1.rbtree_delete(2);
    //rb1.rbtree_delete('3');
   // rb1.rbtree_delete('4');
    rb1.pretree();
    // if (rb1.rbtree_find('a'))
    // {
    //    cout<<"find"<<endl;
    // }
    // else
    // {
    //    cout<<"not find"<<endl;
    // }
	return 0;
}