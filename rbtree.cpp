/*   功能:实现c++红黑树的构造,插入与删除
     作者:朱婷
     日期:2016.4.06
*/

#include <iostream>
#define red 0
#define black 1
using namespace std;

template<class T>
class tree;
//定义树节点类
template<class T>
class node
{
	template<class T11>
	friend class tree;

	// template<class T1>
	// friend ostream& <<(ostream & out,treenode<T1> &node);

public:

	node(T _data)
	{

		data=_data;
		parent=NULL;
		left=NULL;
        right=NULL;
        color=red;//创建默认颜色为红色
	}
	// ~node()
	// {
	// 	delete node;
	// 	node=NULL;
	// }
private:
	T data;
	node<T> *parent;
	node<T> * left;
	node<T> * right;
	int color;
	
};

template<class T>
class tree
{
public:
	tree()
	{
		root = NULL;
	}
	// tree(const T val)
	// {
 //        insertnode(val);
 //    }
	// node<T>* makeguard()//定义叶子节点,在函数中进行调用
	// {
		
	// 		node<T>* NIL=new node<T>;
	// 		NIL->data=-100;
	// 		NIL->left=NULL;
	// 		NIL->right=NULL;
	// 		NIL->parent=NULL;
	// 		NIL->color=black;		
	// 	    //root=NIL;
	// 	    return NIL;
	// }
	 // node<T>* initnode(const T& val)//初始化新建节点
  //   {
  //       node<T>* newnode=new node<T>(val);
  //       newnode->left=makeguard();
  //       newnode->right=makeguard();
  //       newnode->parent=makeguard();
  //       return newnode;
  //   }
  void maketree(int a[],int length)//制造一颗含有length个元素的数
    {
        int i=0;
        for(i=0;i<length;i++)
        {
        	cout<<"lll"<<endl;
            //root=insertnode(root,a[i]);
              insertnode(a[i]);
        }
        treesize=length;
    }
   

    /*
				    函数名称:insertnode
				    参数:插入节点的元素值
				    功能:寻找插入节点合适的位置
				    返回值:插入节点的父节点
    */
   /* node<T>* insertnode(node<T>* root,const T val)
	{
		 cout<<"000"<<endl;
	     if(root->data==-100)
	     {
	     	cout<<"hhhh"<<endl;
	        node<T>* newnode=initnode(val);
	        root=newnode;
	        return root;
	     }
	     if(root->left->data==-100&& root->data>val)
	     {
	     	   cout<<"ssss"<<endl;
	           node<T>* newnode=initnode(val);
	           root->left=newnode;
	           newnode->parent=root;
	           return root;
	     }
	     if(root->right->data==-100 &&  root->data<val)
	     {
	     	   cout<<"ppp"<<endl;
	           node<T>* newnode=initnode(val);
	           root->right=newnode;
	           newnode->parent=root;
	           return root;
	     }
	     if(root->right->data!=-100 && root->data<val)
	     {
	            insertnode(root->right,val);
	     }
	     if(root->left->data!=-100 && root->data>val)
	     {
	           insertnode(root->left,val);
	     }
	     return root;
	}*/
  //   node<T>* insertnode(const T& val)
  //   {
  //   	int flag=0; 
  //   	cout<<"ggy"<<endl;
  //   	node<T> * pkey=new node<T>(val);//定义插入节点
  //   	node<T> *p=root;//记住当前父亲节点
  //   	if(root == NULL)//插入的是第一个节点
  //   	{
  //   		cout<<"eeew"<<endl;
  //           root=pkey;
  //           return root;
  //   	}
  //   	else//遍历树寻找插入位置
  //   	{
  //   		while(1)
  //   		{
  //   			if(flag==1)
  //   			{
  //   				break;
  //   			}
  //   			while(p->data>val)
	 //    		{
	 //    			cout<<"jjjjh"<<endl;
	 //    			if(p->left==NULL)
		// 	    	{
		// 	    	   flag=1;
		//                break; 
		// 	    	}
		// 	    	p=p->left;
		//     		}
	 //    		while(p->data<val)
	 //    		{
	 //    			cout<<"5766"<<endl;
	 //    			if(p->right ==NULL)
	 //    			{
	 //    				flag=1;
	 //    				cout<<"rrre"<<endl;
	 //    				break;
	 //    			}
	 //    			p=p->right;
	 //    		}
  //   		}
    		
    		
  //   	}     
    	 	   	
  //   	if(val<p->data)
  //   	{
  //   		p->left=pkey;
  //   		cout<<"111"<<endl;
  //   	}
  //   	else
  //   	{
  //   		p->right=pkey;
  //   	}
  //   	pkey->parent=p;
  //   	cout<<"66666"<<endl;   	
		// insertcorrent(pkey);//插入完毕,调用节点插入调整平衡函数实现红黑树构造   	
  //   	return p;
  //   }
       
        void insertnode(T _data)
      {
         node<T>* newnode = new node<T>(_data);
         if (root == NULL)
         {
           root = newnode;
           root->color = black;
         }
         else
         {
            node<T>* curr = root;
            node<T>* tmp = NULL;
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
            insertcorrent(newnode);
         }
       
      }
/*插入完毕后需重新调整实现平衡(P代表父节点,U代表叔节点,C代表插入节点,G代表爷爷节点)*/           
	void insertcorrent(node<T> *curr)
	{
	   node<T> *p=NULL;
	   node<T>* tmp = NULL;

        	//插入节点的父亲是红节点才需要进入循环调整
        	while( (p = curr->parent) &&p->color==red)//C为红,P为红,G一定存在且为黑
        	{
        		
                node<T> *g=p->parent;
                if(p==g->left)//P是G左孩子
                {
                	node<T> *uncle=g->right;
                	
                	if(uncle!=NULL&&uncle->color==red)//情况1:U存在且为红色
                	{
                		p->color=black;
                		uncle->color=black;
                		g->color=red;
                		curr=g;//把G看做一个插入的红节点继续向上检索
                	}
                	else if(p->right)//情况2:U为黑色,且C为P的右孩子
                	{                      
                        myleftrotate(p);//将C的P左旋----->尚未平衡,后接情况3操作
						tmp = p;
						p = curr;
						curr = tmp;

                	}
                	   //情况3:U黑色,且C为P的左孩子
                        p->color=black;
                        g->color=red;
                        myrightrotate(g);
                	
                }
                else//P是G的右孩子
                {
           
                    node<T> * uncle=curr->parent->parent->left;
                    if(uncle != NULL&&uncle->color==red)//情况1:U存在,且节点颜色为红色
                    {
                        p->color=black;
                        uncle->color=black;
                        g->color=red;
                        curr=g;//将G作为一个新的插入节点继续向上检索
                    }
                    else if(curr==curr->parent->left)//情况2:U为红色且C为P的左孩子
                    {
                    	
                    	myrightrotate(p);//后接情况3的操作
						tmp = p;
						p = curr;
						curr = tmp;
                    }
                
                        p->color=black;
                        g->color=red;           
                        myleftrotate(g);
                   
                }
        	}
       root->color=black;//将root设置为黑色 
	}

	//旋转函数
	/*
	函数名称:rightrotate
	参数:node<T> * cur(旋转的节点)
	功能:能够以旋转节点的左孩子为支点实现顺时针旋转,左孩子代替其原来的位置
	返回值为空
	*/
	void myrightrotate(node<T> * cur)//右旋
	{
		
        	node<T> * lchild=cur->left;
        	cur->left = lchild->right;    	
            if (cur->left != NULL)
            {
            	lchild->right->parent = cur;
            }
            lchild->right = cur;
            lchild->parent = cur->parent;
            if (lchild->parent != NULL)
            {
            	if (cur == cur->parent->left)
            	{
                   cur->parent->left = lchild;  
            	}
            	else
            	{ 
                   cur->parent->right = lchild;
            	}
            }
            else
            {
            	root = lchild;
            }
            cur->parent = lchild; 
        }

	/*
	函数名称:leftrotate
	参数:node<T> * cur(旋转的节点)
	功能:能够以旋转节点的右孩子为支点实现逆时针旋转,右孩子代替其原来的位置
	返回值为空
	*/
	void myleftrotate(node<T> * cur)//左旋
	{
		
        	node<T> * rchild=cur->right;
        	cur->right = rchild->left;    	
            if (cur->right != NULL)
            {
            	rchild->left->parent = cur;
            }
            rchild->left = cur;
            rchild->parent = cur->parent;
            if (rchild->parent != NULL)
            {
            	if (cur == cur->parent->left)
            	{
                   cur->parent->left = rchild;  
            	}
            	else
            	{ 
                   cur->parent->right = rchild;
            	}
            }
            else
            {
            	root = rchild;
            }
            cur->parent = rchild; 
	}
	/*查找最小数据所在节点并返回该节点*/
	node<T>* findmin()
	{
		curr=root;
		while(curr->left!=NIL)
		{
			curr=curr->left;
		}
		return curr;
	}
	/*查找最大数据所在节点并返回该节点*/
	node<T>* findmax()
	{
		curr=root;
		while(curr->right!=NIL)
		{
			curr=curr->right;
		}
		return curr;
	}
	/*查找删除数据所在的节点*/
	node<T> * find(const T k)
	{
		curr=root;
		while(curr!=NIL&&curr->data!=k)
		{
			if(curr->data<k)
			{
				curr=curr->right;
			}
			else
				curr=curr->left;
		}
		return curr;
	}
	/*寻找准确的删除节点*/
	node<T>* success(const T k)
	{
		curr=find(k);
		while(curr->right!=NIL)//如果所找到的节点的右孩子不为空,则后继为右子树的最小值
		{
	        curr=curr->right;
		}
		return curr;
	}
	
	/*             
	                 删除函数
	                 函数名字:erasenode
	                 实现的功能:删除指定节点,并重新形成树
	                 参数:T k(节点值)
	                 返回值为空
   */
	void erasenode(const T k)
	{
        curr=find(k);//先找到删除数据所对应的节点位置
        node<T> *pdel;//pdel为实际删除的节点
        node<T> *child;//删除节点的孩子
        if(curr==NIL)
        {
        	return;
        }
        if(curr->left==NIL||curr->right==NIL)//如果删除节点至多有一个孩子,则删除
        {
        	curr=pdel;
        }
        else//否则若有两个孩子,则删除其后继
        {
           pdel=success(k);
        }
        if(curr!=pdel)//若删除的是后继,则将后继值赋给前节点
        {
        	curr->data=pdel->data;
        }             
        if(pdel->left!=NIL)//记住不为空的孩子
        {
            child=pdel->left;
        }
        else
        {
        	child=pdel->right;
        }
        if(pdel->parent==NIL)//删除的是根节点
        {
            child=root;
        }
        else if(pdel==pdel->parent->left)
        {
        	pdel->parent->left=child;
        }
        else
        {
        	pdel->parent->right=child;
        } 
        if(pdel->color==black)//如果删除的节点颜色是黑色,则需要重新调整树的平衡性
        {
        	erasecorrent(pdel);
        }
        delete pdel;
	}

	/*   
	                  函数名称:erasecorrent
	                  作用:删除节点后将树调整平衡
	                  参数:node<T>* pkey(寻找到的需要删除的节点)
	                  返回值为空
	*/
	void erasecorrent(node<T>* pkey)
	{
        while(pkey->parent!=NULL&&pkey->color==black)//当前节点不是根节点且颜色为黑
        {
        	node<T> *p;        	
        	p=pkey->parent;       	
        	if(pkey==p->left)//若当前节点是父亲的左孩子
        	{
        		node<T> *brother=p->right;//----一定存在兄弟节点
        		if(brother->color==red)//情况1:兄弟节点的颜色为红-----父亲节点一定为黑
        		{
                    p->color=black;
                    brother->color=red;
                    leftrotate(p);
                    brother=pkey->parent->right;//先不删除,后接情况2处理
        		} 
        		//情况2:父亲节点为红,则兄弟节点一定为黑,兄弟的孩子全为黑
	        	if(p->color==red&&brother->left->color==black&&brother->right->color==black)
	        	{
	        		p->color=black;
	        		brother->color-red;
	        	}      		
        		
        		//情况3:兄弟颜色为黑且两个孩子颜色也为黑
        		else if(brother->color==black&&brother->left->color==black&&brother->right->color)
        		{
        			brother->color=red;
        			if(p->parent!=NIL)
        			{
        				p=p->parent;
        			}
        		}
        		
        		//情况4:父亲为任意色,兄弟为黑,且兄弟的右孩子为红,左孩子任意
        		if(brother->color==black&&brother->right->color==red)
        		{      			
        			brother->color=p->color;
        			p->color=black;
        			leftrotate(p);
        		}

        		//情况5:父亲为任意色,兄弟为黑,且兄弟的左孩子为红,右孩子为黑
        		if (brother->color == black && brother->left->color==red&&brother->right->color==black)
        		{
                    brother->color = red;
                    brother->left->color=black;
                    rightrotate(brother);
                    brother=pkey->parent->right;//尚未平衡,接情况4的操作
        		}
        	}
        	else//当前节点为其父亲的右孩子,与上5种情况相对应
        	{
                node<T> * brother=p->left;
                if(brother->color==red)//情况1:兄弟节点的颜色为红-----父亲节点一定为黑
        		{
                    p->color=black;
                    brother->color=red;
                    rightrotate(p);
                    brother=pkey->parent->left;//先不删除,后接情况2处理
        		}
        		//情况2:父亲节点为红,则兄弟节点一定为黑,兄弟的孩子全为黑
	        	if(p->color==red&&brother->left->color==black&&brother->right->color==black)
	        	{
	        		p->color=black;
	        		brother->color-red;
	        	} 

        		//情况3:兄弟颜色为黑且两个孩子颜色也为黑
        		else if(brother->color==black&&brother->left->color==black&&brother->right->color)
        		{
        			brother->color=red;
        			if(p->parent!=NIL)
        			{
        				p=p->parent;//把p当做新的起点向上检索
        			}
        		}
        		//情况4:父亲为任意色,兄弟为黑,且兄弟的左孩子为红,右孩子任意
        		if(brother->color==black&&brother->right->color==red)
        		{      			
        			brother->color=p->color;
        			p->color=black;
        			rightrotate(p);
        		}
        		//情况5:父亲为任意色,兄弟为黑,且兄弟的右孩子为红,左孩子为黑
        		if(brother->color==black&&brother->left->color==red&&brother->right->color==black)
        		{
                    brother->color=red;
                    brother->left->color=black;
                    rightrotate(brother);
                    brother=pkey->parent->right;//尚未平衡,接情况4的操作
        		}
        	}
        }     
	}

	/*
	             输出函数
	             三种方式输出:前序,中序,后序
	             参数:树的根节点root 
	             返回值为空
   */
	void pretree(node<T>* root)//前序遍历输出
	{
		curr=root;
		if(curr->data!=-100)
		{
			cout<<curr->data<<'\t'<<curr->color<<endl;
			pretree(curr->left);			
			pretree(curr->right);			
		}
	
	}
	 
	void midtree(node<T> *node)//中序遍历输出
	{
		//curr=root;
		if(node != NULL)
		{
			midtree(node->left);
			cout<<node->data<<'\t'<<node->color<<endl;
			midtree(node->right);
		}
		
	}

	void midtree()
	{
		midtree(root);
	}
	void lasttree(node<T>* root)//后序遍历输出
	{
		curr=root;
		if(curr->data!=-100)
		{
			lasttree(curr->left);			
			lasttree(curr->right);
			cout<<curr->data<<'\t'<<curr->color<<endl;
		}
	}
	// ~tree()
	// {
	// 	delete root;
	// 	root=NIL;
	// }
	node<T> *root;
private:
    
	node<T> *curr;
	int bh;//黑高度
	int treesize;//树的节点个数
    node<T>* NIL;//哨兵节点,被整个tree类所共有
};
int main(int argc, char const *argv[])
{
	//node<int> * root=NULL;
	int a[10]={2,8,90,43,9,51,1,73,12,6};	
	tree<int> t1;
	t1.maketree(a,10);
	
	// t1.insertnode(root,34);
	// t1.insertnode(4);
 //    t1.insertnode(19);
 //    t1.insertnode(30);
	// t1.insertnode(98);
	// t1.insertnode(64);
	// t1.insertnode(21);
	// t1.insertnode(1);
	// t1.insertnode(7);
	t1.midtree();	
	return 0;
}