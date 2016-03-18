# include <iostream>
using namespace std;

class RBtree {
	public:
		struct node {
			bool color;
    		double data;
    		node * parent;
    		node * childl;
    		node * childr;
		};
		RBtree(){
			T.color=1;
			T.data=0;
			T.parent=NULL;
			T.childl=NULL;
			T.childr=NULL;
			p_nil=&T;
			Head=p_nil;
		}
		~RBtree(){
			del_all(Head);
		}
		node * search(double data);
		void insert(double data);
		void del(double data);
		void print(){ sub_print(Head);}
		void sub_print(node * p);
	private:
		void del_all(node * p){
			if (Head==NULL)
				return;
			if (p->childl==p_nil&&p->childr==p_nil){
				if (Head!=p){
					if (p->parent->childl==p)
						p->parent->childl=p_nil;
					else 
						p->parent->childr=p_nil;
				}
	//			cout<<"delete data ="<<p->data<<endl;
			    delete p;
			}
			else{
		        if (p->childl!=p_nil)  
					del_all(p->childl);
			    if (p->childr!=p_nil)
					del_all(p->childr);
	//			cout<<"delete data =" <<p->data<<endl;
				delete p;
			}
		};
		void transplant(node *u,node *v);
		void delete_fix_up(node * x);
		void fix_up(node * p);
		void rotadeR(node * p);
		void rotadeL(node * p);
		node T;
		node *p_nil;
		node *Head;
};
void RBtree::transplant(node *u,node *v){
	if (u==Head)
		Head = v;
	else if (u==u->parent->childl)
		u->parent->childl = v;
	else 
		u->parent->childr = v;
	if (v!=p_nil)
		v->parent = u->parent;
}
void RBtree::sub_print(node * p){

	if (p->childl==p_nil&&p->childr==p_nil){
		cout<<"data ="<<p->data<<" color ="<<p->color<<endl;
	}
	else{
		if (p->childl!=p_nil)
			sub_print(p->childl);
		cout<<"data ="<<p->data<<" color ="<<p->color<<endl;
		if (p->childr!=p_nil) 
			sub_print(p->childr);
		
	}
}

void RBtree::fix_up(node * p){
	if (p->color==0&&p==Head){ //判断是否为根节点红色，若是直接改红修正结束
		p->color=1;            
		return;
	} 
	if (p->parent->color==1){ //如果需要修正的节点的上一个节点为黑则修正结束
		return;
	}
	if (p->parent->color==0)  //如果为父节点为红
		if (p->parent->parent->childr==p->parent){ //判断父亲节点为祖父的左儿子还是右儿子，分类讨论
			if (p==p->parent->childl){ //判断该节点是父亲节点的左儿子还是右儿子
				rotadeR(p->parent);    //左儿子右旋
				p=p->childr;           //指向右儿子
			/*	cout<<"p.data ="<<p->data<<endl;
				cout<<"p.parent.data ="<<p->parent->data<<endl;
				cout<<"p.parent.parent.data ="<<p->parent->parent->data<<endl;
		*/	}
		//	rotadeL(p->parent->parent);
			if (p->parent->parent->childl->color==0){//如果叔叔节点为红	
				p->parent->parent->color=0;//祖父变红
				p->parent->parent->childl->color=1;//叔叔变黑
				p->parent->color=1;//父亲变黑
				fix_up(p->parent->parent);//接着修正祖父节点
			}else {
				rotadeL(p->parent->parent);//如果叔叔节点为黑，对祖父做左旋
				p->parent->color=1; //父亲变黑
				p->parent->childl->color=0;//左旋前的祖父变红，修正结束
			}
		}else{//父亲节点为祖父的左儿子，类似右儿子操作
			if (p==p->parent->childr){
				rotadeL(p->parent);
				p=p->childl;
			}
		//	rotadeR(p->parent->parent);
			if (p->parent->parent->childr->color==0){
				p->parent->parent->color=0;
				p->parent->parent->childr->color=1;
				p->parent->color=1;
				fix_up(p->parent->parent);
			}else{
				rotadeR(p->parent->parent);
				p->parent->color=1;
				p->parent->childr->color=0;
			}
		}
}

void RBtree::delete_fix_up(node * x){
}
void RBtree::rotadeR(node * p){//右旋，旋转后该节点成为右儿子
	if (p==Head){
		Head = p->childl;
	}
	else if (p->parent->childl==p){
		p->parent->childl = p->childl;
		if (p->childl!=p_nil)
			p->childl->parent = p->parent;
	}
	else {
		p->parent->childr = p->childl;
		if (p->childl!=p_nil)
			p->childl->parent = p->parent;
	}

	node * temp =p->childl;
	p->childl = p->childl->childr;
	if (p->childl!=p_nil)
		p->childl->parent = p;
	temp->childr = p;
	p->parent = temp;
	
}

void RBtree::rotadeL(node * p){//左旋，旋状转后该节点成为左儿子
	if (p ==Head){
		Head = p->childr;
	}
	else if (p->parent->childl==p){
		p->parent->childl = p->childr;
		if (p->childr!=p_nil)
			p->childr->parent = p->parent;
	}
	else{
		p->parent->childr = p->childr;
		if (p->childr!=p_nil)
			p->childr->parent = p->parent;
	}

	node * temp = p->childr;
	p->childr = p->childr->childl;
	if (p->childr!=p_nil)
		p->childr->parent = p;
	temp->childl = p; 	
	p->parent = temp; 
}

RBtree::node * RBtree::search(double data){//寻找节点
	 node * p =Head;
	 while(p->data!=data){
		if (p->data>data)
			p=p->childl;
		else
			p=p->childr;
	}
	return p;
}

void RBtree::insert(double data){//插入节点
	node * p =Head;
	if (Head==p_nil){//插入第一个节点
		node *a=new node {1,data,0,p_nil,p_nil};
		Head = a;
	}
	else{
			while((p->childl!=p_nil||p->data<data)&&(p->childr!=p_nil||p->data>data)){//找到合适的叶子节点
				if (p->data>data)
					p=p->childl;
				else 
					p=p->childr;
			}
			
			node *a= new node {0,data,p,p_nil,p_nil};

			if (p->data>data)//插入数据
				p->childl=a;
			else
				p->childr=a;
			fix_up(a); //修正红黑树
		}
}

void RBtree::del(double data){
	node * del_p = search(data);
	bool color = del_p->color;
	node * x;
	if (del_p->childl==p_nil){
		x = del_p->childr; 
		transplant(del_p,del_p->childr);
	}else if (del_p->childr==p_nil){
		x = del_p->childl;
		transplant(del_p,del_p->childl);
	}else {
		node * y =del_p->childr;
		while(y->childl!=p_nil)
			 y=y->childl;
		color = y->color;
		x = y->childr;
		if (y->parent == del_p)
			x->parent = y;
		else{
			transplant(y,y->childr);
			y->childr = del_p->childr;
			y->childr->parent =y;
		}
		transplant(del_p,y);
		y->childl = del_p->childl;
		y->childl->parent = y;
		y->color = del_p->color;
	}
	if (color ==1 )
		delete_fix_up(x);
	delete del_p;
}

int main(){
	double a[]={2,5,3,4,3,5,7,9,1,6,10};
	RBtree RB;
	for (int i=0;i<11;i++){
		RB.insert(a[i]);
		RB.print();
	}
	for (int i=0;i<10;i++){
		RB.del(a[i]);
		RB.print();
	}
	return 0;	
}









