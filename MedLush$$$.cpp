#include<iostream>
#include<conio.h>
#include<fstream>
#include<windows.h>
#define SPACE 10
using namespace std;


// for setting axis................
void gotoxy(short x,short y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}


// nodes .....................................................

class user
{
	public:
		int id;
		string name;
		int pass;
		user *left;
		user *right;
		user()
		{
			id=0;
			pass=0;
			name="nil";
			left=NULL;
			right=NULL;
		}
};

class pat // patient
{
	public:
		int id;
		string name;
		int age;
		string mbn;
		pat *left;
		pat *right;
		pat()
		{
			id=0;
			age=0;
			name="nil";
			mbn="nil";
			left=NULL;
			right=NULL;
		}
};

class pro // product
{
	public:
		int id;
		string name;
		float price;
		pro *left;
		pro *right;
		pro()
		{
			id=0;
			name="nil";
			price=0;
			left=NULL;
			right=NULL;
		}
};

class slip
{
	public:
		int id;
		int p_id;
		string name;
		string mn;
		int age;
		float price;
		string u_n;
		string p_n;
		slip *left;
		slip *right;
		slip()
		{
			id=0;
			p_id=0;
			price=0;
			age=0;
			name="nil";
			u_n="nil";
			p_n="nil";
			mn="nil";
			left=NULL;
			right=NULL;
		}
};

class cash
{
	public:
		int id;
		string name;
		float money;
		cash *left;
		cash *right;
		cash()
		{
			id=0;
			name="nil";
			money=0;
			left=NULL;
			right=NULL;
		}
};

// trees ...........................................................
// user tree.........................................................
class user_tree
{
	public:
		user *root;
		user_tree()
		{
			root=NULL;
		}

user *rr(user *n)
{
	user *x = n->left;
	user *x2 = x->right;
	x->right = n;
	n->left = x2;
	return x;
}

user *lr(user *n)
{
	user *x = n->right;
	user *x2 = x->left;
	x->left = n;
	n->right = x2;
	return x;
}

int height(user *r)
{
	if(r==NULL)
	{
		return -1;
	}
	
	int lh=user_tree::height(r->left);
	int rh=user_tree::height(r->right);
	
	if(lh > rh)
	{
		return lh+1;
	}
	else
	{
		return rh+1;
	}
}

int getbalance(user *r)
{
	if(r==NULL)
	{
		return -1;
	}
	else
	{
		return (user_tree::height(r->left))-(user_tree::height(r->right));
	}
}

user *insert(user *r,user *n)
{
	if(r==NULL)
	{
		r=n;
		return r;
	}
	if(n->id < r->id)
	{
		r->left=user_tree::insert(r->left,n);
	}
	else if(n->id > r->id)
	{
		r->right=user_tree::insert(r->right,n);
	}
	else
	{
		cout<<"\n\t\t\t\t User with duplicate id...!";
		return r;
	}
	
	int bf=user_tree::getbalance(r);
	
	if(bf>1 && n->id < r->left->id )
	{
		return user_tree::rr(r);
	}
	if(bf<-1 && n->id > r->right->id)
	{
		return user_tree::lr(r);
	}
	if(bf>1 && n->id > r->left->id)
	{
		r->left=user_tree::lr(r->left);
		return user_tree::rr(r);
	}
	if(bf<-1 && n->id < r->right->id)
	{
		r->right=user_tree::rr(r->right);
		return user_tree::lr(r);
	}
	
	
	return r;
}

void print(user *r,int s)
{
	if(r==NULL)
	{
		return;
	}
	s+=SPACE;
	user_tree::print(r->right,s);
	cout<<endl;
	for(int i=SPACE;i<s;i++)
	{
		cout<<" ";
	}
	cout<<r->id<<"\n";
	user_tree::print(r->left,s);
}


user *search(user *r,int i)
{
	if(r==NULL || r->id==i)
	{
		return r;
	}
	else if(i<r->id)
	{
		return user_tree::search(r->left,i);
	}
	else
	{
		return user_tree::search(r->right,i);
	}
}


user *check_pass(user *r,int p)
{
		if(r==NULL || r->pass==p)
	{
		return r;
	}
	else if(user_tree::check_pass(r->left,p))
	{
	   return user_tree::check_pass(r->left,p);
    }
    else
    {
    	return user_tree::check_pass(r->right,p);
	}
}

void for_all(user *r)
{
	if(r==NULL)
	{
		return;
	}
	user_tree::for_all(r->left);
	cout<<"\n\t\t\t______________( "<<r->id<<" )_________________";
	cout<<"\n\t\t\t\t Name \t"<<r->name;
	cout<<"\n\t\t\t\t Pass \t"<<r->pass;
	user_tree::for_all(r->right);
}

user *minvalue(user *n)
{
	user *current=n;
	while(current->left!=NULL)
	{
		current=current->left;
	}
	return current;
}

user *del(user *r,int i)
{
	if(r==NULL)
	{
		return NULL;
	}
	else if(i<r->id)
	{
		r->left=user_tree::del(r->left,i);
	}
	else if(i>r->id)
	{
		r->right=user_tree::del(r->right,i);
	}
	else
	{
		if(r->left==NULL)
		{
			user *temp = r->right;
			delete r;
			return temp;
		}
		else if(r->right==NULL)
		{
			user *temp=r->left;
			delete r;
			return temp;
		}
		else
		{
			user *temp = user_tree::minvalue(r->right);
			r->id = temp->id;
			r->name = temp->name;
			r->pass = temp->pass;
			r->right= user_tree::del(r->right,temp->id);
		}
	}
	
	int bf= user_tree::getbalance(r);
	
	if(bf==2 && user_tree::getbalance(r->left)>=0)
	{
		return user_tree::rr(r);
	}
	if(bf==2 && user_tree::getbalance(r->left)==-1)
	{
		r->left= user_tree::lr(r->left);
		return user_tree::rr(r);
	}
	if(bf==-2 && user_tree::getbalance(r->right)<=0)
	{
		return user_tree::lr(r);
	}
	if(bf==-2 && user_tree::getbalance(r->right)==1)
	{
		r->right=user_tree::rr(r->right);
		return user_tree::lr(r);
	}
	return r;	
}

};
user_tree  obj1;


// patient tree........................................................
class pat_tree
{
	public:
		pat *root;
		pat_tree()
		{
			root=NULL;
		}

pat *rr(pat *n)
{
	pat *x = n->left;
	pat *x2 = x->right;
	x->right = n;
	n->left = x2;
	return x;
}

pat *lr(pat *n)
{
	pat *x = n->right;
	pat *x2 = x->left;
	x->left = n;
	n->right = x2;
	return x;
}

int height(pat *r)
{
	if(r==NULL)
	{
		return -1;
	}
	
	int lh=pat_tree::height(r->left);
	int rh=pat_tree::height(r->right);
	
	if(lh > rh)
	{
		return lh+1;
	}
	else
	{
		return rh+1;
	}
}

int getbalance(pat *r)
{
	if(r==NULL)
	{
		return -1;
	}
	else
	{
		return (pat_tree::height(r->left))-(pat_tree::height(r->right));
	}
}

pat *insert(pat *r,pat *n)
{
	if(r==NULL)
	{
		r=n;
		return r;
	}
	if(n->id < r->id)
	{
		r->left=pat_tree::insert(r->left,n);
	}
	else if(n->id > r->id)
	{
		r->right=pat_tree::insert(r->right,n);
	}
	else
	{
		cout<<"\n\t\t\t\t User with duplicate id...!";
		return r;
	}
	
	int bf=pat_tree::getbalance(r);
	
	if(bf>1 && n->id < r->left->id )
	{
		return pat_tree::rr(r);
	}
	if(bf<-1 && n->id > r->right->id)
	{
		return pat_tree::lr(r);
	}
	if(bf>1 && n->id > r->left->id)
	{
		r->left=pat_tree::lr(r->left);
		return pat_tree::rr(r);
	}
	if(bf<-1 && n->id < r->right->id)
	{
		r->right=pat_tree::rr(r->right);
		return pat_tree::lr(r);
	}
	
	
	return r;
}

void print(pat *r,int s)
{
	if(r==NULL)
	{
		return;
	}
	s+=SPACE;
	pat_tree::print(r->right,s);
	cout<<endl;
	for(int i=SPACE;i<s;i++)
	{
		cout<<" ";
	}
	cout<<r->id<<"\n";
	pat_tree::print(r->left,s);
}


pat *search(pat *r,int i)
{
	if(r==NULL || r->id==i)
	{
		return r;
	}
	else if(i<r->id)
	{
		return pat_tree::search(r->left,i);
	}
	else
	{
		return pat_tree::search(r->right,i);
	}
}



void for_all(pat *r)
{
	if(r==NULL)
	{
		return;
	}
	pat_tree::for_all(r->left);
	cout<<"\n\t\t\t______________( "<<r->id<<" )_________________";
	cout<<"\n\t\t\t\t Name \t"<<r->name;
	cout<<"\n\t\t\t\t Age  \t"<<r->age;
	cout<<"\n\t\t\t\t Mob.Num \t"<<r->mbn;
	pat_tree::for_all(r->right);
}

pat *minvalue(pat *n)
{
	pat *current=n;
	while(current->left!=NULL)
	{
		current=current->left;
	}
	return current;
}

pat *del(pat *r,int i)
{
	if(r==NULL)
	{
		return NULL;
	}
	else if(i<r->id)
	{
		r->left=pat_tree::del(r->left,i);
	}
	else if(i>r->id)
	{
		r->right=pat_tree::del(r->right,i);
	}
	else
	{
		if(r->left==NULL)
		{
			pat *temp = r->right;
			delete r;
			return temp;
		}
		else if(r->right==NULL)
		{
			pat *temp=r->left;
			delete r;
			return temp;
		}
		else
		{
			pat *temp = pat_tree::minvalue(r->right);
			r->id = temp->id;
			r->name = temp->name;
			r->age = temp->age;
			r->mbn = temp->mbn;
			r->right= pat_tree::del(r->right,temp->id);
		}
	}
	
	int bf= pat_tree::getbalance(r);
	
	if(bf==2 && pat_tree::getbalance(r->left)>=0)
	{
		return pat_tree::rr(r);
	}
	if(bf==2 && pat_tree::getbalance(r->left)==-1)
	{
		r->left= pat_tree::lr(r->left);
		return pat_tree::rr(r);
	}
	if(bf==-2 && pat_tree::getbalance(r->right)<=0)
	{
		return pat_tree::lr(r);
	}
	if(bf==-2 && pat_tree::getbalance(r->right)==1)
	{
		r->right=pat_tree::rr(r->right);
		return pat_tree::lr(r);
	}
	return r;	
}

};

pat_tree obj2;


// product tree........................................................
class pro_tree
{
	public:
		pro *root;
		pro_tree()
		{
			root=NULL;
		}

pro *rr(pro *n)
{
	pro *x = n->left;
	pro *x2 = x->right;
	x->right = n;
	n->left = x2;
	return x;
}

pro *lr(pro *n)
{
	pro *x = n->right;
	pro *x2 = x->left;
	x->left = n;
	n->right = x2;
	return x;
}

int height(pro *r)
{
	if(r==NULL)
	{
		return -1;
	}
	
	int lh=pro_tree::height(r->left);
	int rh=pro_tree::height(r->right);
	
	if(lh > rh)
	{
		return lh+1;
	}
	else
	{
		return rh+1;
	}
}

int getbalance(pro *r)
{
	if(r==NULL)
	{
		return -1;
	}
	else
	{
		return (pro_tree::height(r->left))-(pro_tree::height(r->right));
	}
}

pro *insert(pro *r,pro *n)
{
	if(r==NULL)
	{
		r=n;
		return r;
	}
	if(n->id < r->id)
	{
		r->left=pro_tree::insert(r->left,n);
	}
	else if(n->id > r->id)
	{
		r->right=pro_tree::insert(r->right,n);
	}
	else
	{
		cout<<"\n\t\t\t\t User with duplicate id...!";
		return r;
	}
	
	int bf=pro_tree::getbalance(r);
	
	if(bf>1 && n->id < r->left->id )
	{
		return pro_tree::rr(r);
	}
	if(bf<-1 && n->id > r->right->id)
	{
		return pro_tree::lr(r);
	}
	if(bf>1 && n->id > r->left->id)
	{
		r->left=pro_tree::lr(r->left);
		return pro_tree::rr(r);
	}
	if(bf<-1 && n->id < r->right->id)
	{
		r->right=pro_tree::rr(r->right);
		return pro_tree::lr(r);
	}
	
	return r;
}

void print(pro *r,int s)
{
	if(r==NULL)
	{
		return;
	}
	s+=SPACE;
	pro_tree::print(r->right,s);
	cout<<endl;
	for(int i=SPACE;i<s;i++)
	{
		cout<<" ";
	}
	cout<<r->id<<"\n";
	pro_tree::print(r->left,s);
}


pro *search(pro *r,int i)
{
	if(r==NULL || r->id==i)
	{
		return r;
	}
	else if(i<r->id)
	{
		return pro_tree::search(r->left,i);
	}
	else
	{
		return pro_tree::search(r->right,i);
	}
}

void for_all(pro *r)
{
	if(r==NULL)
	{
		return;
	}
	pro_tree::for_all(r->left);
	cout<<"\n\t\t\t_____________( "<<r->id<<" )________________";
	cout<<"\n\t\t\t\t Name  \t"<<r->name;
	cout<<"\n\t\t\t\t Price  \t"<<r->price;
	pro_tree::for_all(r->right);
}

pro *minvalue(pro *n)
{
	pro *current=n;
	while(current->left!=NULL)
	{
		current=current->left;
	}
	return current;
}

pro *del(pro *r,int i)
{
	if(r==NULL)
	{
		return NULL;
	}
	else if(i<r->id)
	{
		r->left=pro_tree::del(r->left,i);
	}
	else if(i>r->id)
	{
		r->right=pro_tree::del(r->right,i);
	}
	else
	{
		if(r->left==NULL)
		{
			pro *temp = r->right;
			delete r;
			return temp;
		}
		else if(r->right==NULL)
		{
			pro *temp=r->left;
			delete r;
			return temp;
		}
		else
		{
			pro *temp = pro_tree::minvalue(r->right);
			r->id = temp->id;
			r->name = temp->name;
			r->price = temp->price;
			r->right= pro_tree::del(r->right,temp->id);
		}
	}
	
	int bf= pro_tree::getbalance(r);
	
	if(bf==2 && pro_tree::getbalance(r->left)>=0)
	{
		return pro_tree::rr(r);
	}
	if(bf==2 && pro_tree::getbalance(r->left)==-1)
	{
		r->left= pro_tree::lr(r->left);
		return pro_tree::rr(r);
	}
	if(bf==-2 && pro_tree::getbalance(r->right)<=0)
	{
		return pro_tree::lr(r);
	}
	if(bf==-2 && pro_tree::getbalance(r->right)==1)
	{
		r->right=pro_tree::rr(r->right);
		return pro_tree::lr(r);
	}
	return r;	
}
};

pro_tree obj3;

// slip tree............................................................
class slip_tree
{
	public:
		slip *root;
		slip_tree()
		{
			root=NULL;
		}

slip *rr(slip *n)
{
	slip *x = n->left;
	slip *x2 = x->right;
	x->right = n;
	n->left = x2;
	return x;
}

slip *lr(slip *n)
{
	slip *x = n->right;
	slip *x2 = x->left;
	x->left = n;
	n->right = x2;
	return x;
}

int height(slip *r)
{
	if(r==NULL)
	{
		return -1;
	}
	
	int lh=slip_tree::height(r->left);
	int rh=slip_tree::height(r->right);
	
	if(lh > rh)
	{
		return lh+1;
	}
	else
	{
		return rh+1;
	}
}

int getbalance(slip *r)
{
	if(r==NULL)
	{
		return -1;
	}
	else
	{
		return (slip_tree::height(r->left))-(slip_tree::height(r->right));
	}
}

slip *insert(slip *r,slip *n)
{
	if(r==NULL)
	{
		r=n;
		return r;
	}
	if(n->id < r->id)
	{
		r->left=slip_tree::insert(r->left,n);
	}
	else if(n->id > r->id)
	{
		r->right=slip_tree::insert(r->right,n);
	}
	else
	{
		cout<<"\n\t\t\t\t user with duplicate id...!";
		return r;
	}
	
	int bf=slip_tree::getbalance(r);
	
	if(bf>1 && n->id < r->left->id )
	{
		return slip_tree::rr(r);
	}
	if(bf<-1 && n->id > r->right->id)
	{
		return slip_tree::lr(r);
	}
	if(bf>1 && n->id > r->left->id)
	{
		r->left=slip_tree::lr(r->left);
		return slip_tree::rr(r);
	}
	if(bf<-1 && n->id < r->right->id)
	{
		r->right=slip_tree::rr(r->right);
		return slip_tree::lr(r);
	}
	
	
	return r;
}

void print(slip *r,int s)
{
	if(r==NULL)
	{
		return;
	}
	s+=SPACE;
	slip_tree::print(r->right,s);
	cout<<endl;
	for(int i=SPACE;i<s;i++)
	{
		cout<<" ";
	}
	cout<<r->id<<"\n";
	slip_tree::print(r->left,s);
}


slip *search(slip *r,int i)
{
	if(r==NULL || r->id==i)
	{
		return r;
	}
	else if(i<r->id)
	{
		return slip_tree::search(r->left,i);
	}
	else
	{
		return slip_tree::search(r->right,i);
	}
}


void for_all(slip *r)
{
	if(r==NULL)
	{
		return;
	}
	slip_tree::for_all(r->left);
	cout<<"\n\t\t\t________________( "<<r->id<<" )________________";
	cout<<"\n\t\t\t\t Name \t"<<r->name;
	cout<<"\n\t\t\t\t Patient id \t"<<r->p_id;
	cout<<"\n\t\t\t\t Product Name \t"<<r->p_n;
	cout<<"\n\t\t\t\t Price \t"<<r->price;
	cout<<"\n\t\t\t\t Patient Age \t"<<r->age;
	cout<<"\n\t\t\t\t Mob.Num \t"<<r->mn;
	cout<<"\n\n\n\t\t\t\t\t\t\t Made by \t"<<r->u_n;
	slip_tree::for_all(r->right);
}

slip *minvalue(slip *n)
{
	slip *current=n;
	while(current->left!=NULL)
	{
		current=current->left;
	}
	return current;
}

slip *del(slip *r,int i)
{
	if(r==NULL)
	{
		return NULL;
	}
	else if(i<r->id)
	{
		r->left=slip_tree::del(r->left,i);
	}
	else if(i>r->id)
	{
		r->right=slip_tree::del(r->right,i);
	}
	else
	{
		if(r->left==NULL)
		{
			slip *temp = r->right;
			delete r;
			return temp;
		}
		else if(r->right==NULL)
		{
			slip *temp=r->left;
			delete r;
			return temp;
		}
		else
		{
			slip *temp = slip_tree::minvalue(r->right);
			r->id = temp->id;
			r->p_id = temp->p_id;
			r->price = temp->price;
			r->p_n = temp->p_n;
			r->u_n = temp->u_n;
			r->age = temp->age;
			r->mn = temp->mn;
			r->name = temp->name;
			r->right= slip_tree::del(r->right,temp->id);
		}
	}
	
	int bf= slip_tree::getbalance(r);
	
	if(bf==2 && slip_tree::getbalance(r->left)>=0)
	{
		return slip_tree::rr(r);
	}
	if(bf==2 && slip_tree::getbalance(r->left)==-1)
	{
		r->left= slip_tree::lr(r->left);
		return slip_tree::rr(r);
	}
	if(bf==-2 && slip_tree::getbalance(r->right)<=0)
	{
		return slip_tree::lr(r);
	}
	if(bf==-2 && slip_tree::getbalance(r->right)==1)
	{
		r->right=slip_tree::rr(r->right);
		return slip_tree::lr(r);
	}
	return r;	
}

};

slip_tree obj4;

// cash tree .......................................................
class cash_tree
{
	public:
		cash *root;
		cash_tree()
		{
			root=NULL;
		}

cash *rr(cash *n)
{
	cash *x = n->left;
	cash *x2 = x->right;
	x->right = n;
	n->left = x2;
	return x;
}

cash *lr(cash *n)
{
	cash *x = n->right;
	cash *x2 = x->left;
	x->left = n;
	n->right = x2;
	return x;
}

int height(cash *r)
{
	if(r==NULL)
	{
		return -1;
	}
	
	int lh=cash_tree::height(r->left);
	int rh=cash_tree::height(r->right);
	
	if(lh > rh)
	{
		return lh+1;
	}
	else
	{
		return rh+1;
	}
}

int getbalance(cash *r)
{
	if(r==NULL)
	{
		return -1;
	}
	else
	{
		return (cash_tree::height(r->left))-(cash_tree::height(r->right));
	}
}

cash *insert(cash *r,cash *n)
{
	if(r==NULL)
	{
		r=n;
		return r;
	}
	if(n->id < r->id)
	{
		r->left=cash_tree::insert(r->left,n);
	}
	else if(n->id > r->id)
	{
		r->right=cash_tree::insert(r->right,n);
	}
	else
	{
		cout<<"\n\t\t\t\t user with duplicate id...!";
		return r;
	}
	
	int bf=cash_tree::getbalance(r);
	
	if(bf>1 && n->id < r->left->id )
	{
		return cash_tree::rr(r);
	}
	if(bf<-1 && n->id > r->right->id)
	{
		return cash_tree::lr(r);
	}
	if(bf>1 && n->id > r->left->id)
	{
		r->left=cash_tree::lr(r->left);
		return cash_tree::rr(r);
	}
	if(bf<-1 && n->id < r->right->id)
	{
		r->right=cash_tree::rr(r->right);
		return cash_tree::lr(r);
	}
	
	
	return r;
}

void print(cash *r,int s)
{
	if(r==NULL)
	{
		return;
	}
	s+=SPACE;
	cash_tree::print(r->right,s);
	cout<<endl;
	for(int i=SPACE;i<s;i++)
	{
		cout<<" ";
	}
	cout<<r->id<<"\n";
	cash_tree::print(r->left,s);
}


cash *search(cash *r,int i)
{
	if(r==NULL || r->id==i)
	{
		return r;
	}
	else if(i<r->id)
	{
		return cash_tree::search(r->left,i);
	}
	else
	{
		return cash_tree::search(r->right,i);
	}
}


void for_all(cash *r)
{
	if(r==NULL)
	{
		return;
	}
	cash_tree::for_all(r->left);
	cout<<"\n\t\t\t_____________( "<<r->id<<" )_____________";
	cout<<"\n\t\t\t\t Name  \t"<<r->name;
	cout<<"\n\t\t\t\t Total Sale \t"<<r->money;
	cash_tree::for_all(r->right);
}

cash *minvalue(cash *n)
{
	cash *current=n;
	while(current->left!=NULL)
	{
		current=current->left;
	}
	return current;
}
cash *del(cash *r,int i)
{
	if(r==NULL)
	{
		return NULL;
	}
	else if(i<r->id)
	{
		r->left=cash_tree::del(r->left,i);
	}
	else if(i>r->id)
	{
		r->right=cash_tree::del(r->right,i);
	}
	else
	{
		if(r->left==NULL)
		{
			cash *temp = r->right;
			delete r;
			return temp;
		}
		else if(r->right==NULL)
		{
			cash *temp=r->left;
			delete r;
			return temp;
		}
		else
		{
			cash *temp = cash_tree::minvalue(r->right);
			r->id = temp->id;
			r->money = temp->money;
			r->name = temp->name;
			r->right= cash_tree::del(r->right,temp->id);
		}
	}
	
	int bf= cash_tree::getbalance(r);
	
	if(bf==2 && cash_tree::getbalance(r->left)>=0)
	{
		return cash_tree::rr(r);
	}
	if(bf==2 && cash_tree::getbalance(r->left)==-1)
	{
		r->left= cash_tree::lr(r->left);
		return cash_tree::rr(r);
	}
	if(bf==-2 && cash_tree::getbalance(r->right)<=0)
	{
		return cash_tree::lr(r);
	}
	if(bf==-2 && cash_tree::getbalance(r->right)==1)
	{
		r->right= cash_tree::rr(r->right);
		return cash_tree::lr(r);
	}
	return r;	
}

};

cash_tree obj5;

//lush class for main access
class lush
{
	public:
		string name;
		int pass;
		lush()
		{
			name="ahlush";
			pass=1234;
		}
	void menu();
	void user_menu(int i,string x);
	void admin_panel();	
	void patient_panel();
	void user_panel();
	void product_panel();
	void cash_recipt_panel();
	void cash_panel();
	void slip_panel();
	void dsa_panel();	
	void show_slip(slip *n);
	void show_cash(cash *n);
	void recipt();
	void ccash();
	void user_seri(user *r,fstream &o);
	void patient_seri(pat *r,fstream &o);
	void product_seri(pro *r,fstream &o);
	void slip_seri(slip *r,fstream &o);
	void cash_seri(cash *r,fstream &o);
	user *user_deseri(fstream &i);
	pat  *patient_deseri(fstream &i);
	pro  *product_deseri(fstream &i);
	slip *slip_deseri(fstream &i);
	cash *cash_deseri(fstream &i);
	void trees();
	void heights();
};


void lush::heights()
{
	int a;
	start:
		system("cls");
		gotoxy(32,3);
		cout<<"__________________HEIGHTS_________________";
		gotoxy(40,5);
		cout<<" 1) For User Tree Height";
		gotoxy(40,6);
		cout<<" 2) For Patient Tree Height";
		gotoxy(40,7);
		cout<<" 3) For Product Tree Height";
		gotoxy(40,8);
		cout<<" 4) For Slip Tree Height";
		gotoxy(40,9);
		cout<<" 5) For Cash Tree Height";
		gotoxy(40,10);
		cout<<" 6) Exit";
		do
		{
			gotoxy(40,12);
			cout<<" Enter here \t";
			cin>>a;
		}while(a<=0 || a>6);
		switch(a)
		{
			case 1:
				system("cls");
				gotoxy(38,7);
				cout<<" Height of User Tree is \t"<<obj1.height(obj1.root);
				getch();
				goto start;
				break;
				case 2:
					system("cls");
					gotoxy(38,7);
					cout<<" Height of Patient Tree is \t"<<obj2.height(obj2.root);
				    getch();
				    goto start;
					break;
					case 3:
						system("cls");
						gotoxy(38,7);
						cout<<" Height of Product Tree is \t"<<obj3.height(obj3.root);
				        getch();
				        goto start;
						break;
						case 4:
							system("cls");
							gotoxy(38,7);
							cout<<" Height of Slip Tree is \t"<<obj4.height(obj4.root);
				            getch();
				            goto start;
							break;
							case 5:
								system("cls");
								gotoxy(38,7);
								cout<<" Height of Cash Tree is \t"<<obj5.height(obj5.root);
				                getch();
				                goto start;
							   break;
							   case 6:
							   	return ;
							   	break;
		}
}

void lush::trees()
{
	int a;
	start:
		system("cls");
		gotoxy(34,3);
		cout<<"________________TREES________________";
		gotoxy(43,5);
		cout<<" 1) For User Tree";
		gotoxy(43,6);
		cout<<" 2) For Patient Tree";
		gotoxy(43,7);
		cout<<" 3) For Product Tree";
		gotoxy(43,8);
		cout<<" 4) For Slip Tree";
		gotoxy(43,9);
		cout<<" 5) For Cash Tree";
		gotoxy(43,10);
		cout<<" 6) Exit";
		do
		{
			gotoxy(43,12);
			cout<<" Enter Here \t";
			cin>>a;
		}while(a<=0 || a>6);
		switch(a)
		{
			case 1:
				system("cls");
				cout<<"\n\t\t\t\t User Tree \n\n";
				obj1.print(obj1.root,5);
				getch();
				goto start;
				break;
				case 2:
					system("cls");
					cout<<"\n\t\t\t\t Patient Tree \n\n";
					obj2.print(obj2.root,5);
					getch();
					goto start;
					break;
					case 3:
						system("cls");
						cout<<"\n\t\t\t\t Product Tree \n\n";
						obj3.print(obj3.root,5);
						getch();
						goto start;
						break;
						case 4:
							system("cls");
							cout<<"\n\t\t\t\t Slip Tree \n\n";
							obj4.print(obj4.root,5);
							getch();
							goto start;
							break;
							case 5:
								system("cls");
								cout<<"\n\t\t\t\t Cash Tree \n\n";
								obj5.print(obj5.root,5);
								getch();
								goto start;
								break;
								case 6:
									return ;
									break;
		}
}

void lush::dsa_panel()
{
	int a;
	start:
		system("cls");
		gotoxy(32,5);
		cout<<"__________________DSA PANEL__________________";
		gotoxy(40,7);
		cout<<" 1) For printing trees";
		gotoxy(40,8);
		cout<<" 2) For Heights";
		gotoxy(40,9);
		cout<<" 3) Exit";
		do
		{
			gotoxy(40,11);
			cout<<" Enter here \t";
			cin>>a;
		}while(a<=0 || a>3);
		switch(a)
		{
			case 1:
				lush::trees();
				getch();
				goto start;
				break;
				case 2:
					lush::heights();
					getch();
					goto start;
					break;
					case 3:
						return;
						break;
		}
}


void lush::ccash()
{
	int a;
	cash *ttemp;
	start:
		system("cls");
		gotoxy(38,5);
		cout<<"_____________Cash____________";
		gotoxy(43,7);
		cout<<" 1) For Everyone Cash \t";
		gotoxy(43,8);
		cout<<" 2 For MY Cash \t";
		gotoxy(43,9);
		cout<<" 3) Exit";
		do
		{
			gotoxy(43,11);
			cout<<" Enter here \t";
			cin>>a;
		}while(a<=0 || a>3);
		switch(a)
		{
			case 1:
				system("cls");
				obj5.for_all(obj5.root);
				getch();
				goto start;
				break;
				case 2:
					system("cls");
					gotoxy(40,5);
					cout<<" Enter User id \t";
					cin>>a;
					ttemp=obj5.search(obj5.root,a);
					if(ttemp!=NULL)
					{
						system("cls");
					lush::show_cash(ttemp);
					getch();
				    }
				    else
				    {
				    	gotoxy(40,8);
				    	cout<<" not found";
					}
					getch();
					goto start;
					break;
					case 3:
						return ;
						break;
		}
}


void lush::recipt()
{
	int a;
	slip *tttemp;
	start:
		system("cls");
		gotoxy(38,5);
		cout<<"_________Recipts________";
		gotoxy(43,8);
		cout<<" 1) For All Slips";
		gotoxy(43,9);
		cout<<" 2) For specific";
		gotoxy(43,10);
		cout<<" 3) Exit";
		do
		{
			gotoxy(43,12);
			cout<<" Enter Here \t";
			cin>>a;
		}while(a<=0 || a>3);
		switch(a)
		{
			case 1:
				system("cls");
				obj4.for_all(obj4.root);
				getch();
				goto start;
				break;
				case 2:
					system("cls");
					gotoxy(43,5);
					cout<<" Enter id \t";
					cin>>a;
					tttemp=obj4.search(obj4.root,a);
					if(tttemp!=NULL)
					{
						system("cls");
						lush::show_slip(tttemp);
						getch();
					}
					else
					{
						gotoxy(43,7);
						cout<<" Not Found";
					}
					getch();
					goto start;
					break;
					case 3:
						break;
		}
}

void lush::cash_recipt_panel()
{
	int a;
	start:
		system("cls");
		gotoxy(32,5);
		cout<<"_______________Cash nd Recipt________________";
		gotoxy(43,7);
		cout<<" 1) For Recipts";
		gotoxy(43,8);
		cout<<" 2) For cash";
		gotoxy(43,9);
		cout<<" 3) For Exit";
		do
		{
			gotoxy(43,11);
			cout<<" Enter here \t";
			cin>>a;
		}while(a<=0 || a>3);
		switch(a)
		{
			case 1:
				lush::recipt();
				getch();
				goto start;
				break;
				case 2:
					lush::ccash();
					getch();
					goto start;
					break;
					case 3:
						return ;
						break;
		}
}

void lush::user_panel()
{
	int a,b,d;
	string c;
	start:
		system("cls");
		gotoxy(32,3);
		cout<<"_______________USER MENU______________";
		gotoxy(40,5);
		cout<<" 1) For Adding New";
		gotoxy(40,6);
		cout<<" 2) For Deleting";
		gotoxy(40,7);
		cout<<" 3) For Updating";
		gotoxy(40,8);
		cout<<" 4) For Searching";
		gotoxy(40,9);
		cout<<" 5) For all";
		gotoxy(40,10);
		cout<<" 6) For Exit";
		do
		{
			gotoxy(40,12);
			cout<<" Enter here \t";
			cin>>a;
		}while(a<=0 || a>6);
		user *n1 = new user();
		cash *c1 = new cash();
		switch(a)
		{
			case 1:
				system("cls");
				gotoxy(38,5);
				cout<<"__________New__________";
				gotoxy(40,7);
				cout<<" Enter name of the user \t";
				cin>>c;
				gotoxy(40,8);
				cout<<" Enter id \t";
				cin>>b;
				gotoxy(40,9);
				cout<<" Enter password \t";
				cin>>d;
				n1->name=c;
				n1->pass=d;
				n1->id=b;
				obj1.root=obj1.insert(obj1.root,n1);
				c1->name=c;
				c1->id=b;
				obj5.root= obj5.insert(obj5.root,c1);
				getch();
				goto start;
				break;
				case 2:
					system("cls");
					gotoxy(40,5);
					cout<<" Enter id to delete \t";
					cin>>b;
					n1 = obj1.search(obj1.root,b);
					if(n1!=NULL)
					{
						obj1.root= obj1.del(obj1.root,b);
						gotoxy(40,8);
						cout<<" DELETED.....!";
					}
					else
					{
						gotoxy(40,8);
						cout<<" not found";
					}
					getch();
					goto start;
					break;
					case 3:
						system("cls");
						gotoxy(40,5);
							cout<<" Enter id to search \t";
							cin>>b;
							n1 = obj1.search(obj1.root,b);
							if(n1==NULL)
							{
								gotoxy(40,8);
								cout<<" nothing found";
							}
							else
							{
								gotoxy(40,7);
							   cout<<" Enter new name \t";
							   cin>>n1->name;
							   gotoxy(40,8);
							   cout<<" Enter new pass \t";
							   cin>>n1->pass;
							   gotoxy(40,10);
							   cout<<" Updated......!";
							}
						getch();
						goto start;
						break;
						case 4:
							system("cls");
							gotoxy(40,5);
							cout<<" Enter id to search \t";
							cin>>b;
							n1 = obj1.search(obj1.root,b);
							if(n1==NULL)
							{
								gotoxy(40,8);
								cout<<" nothing found";
							}
							else
							{
								gotoxy(40,7);
								cout<<" id  \t"<<n1->id;
								gotoxy(40,8);
								cout<<" name  \t"<<n1->name;
								gotoxy(40,9);
								cout<<" password  \t"<<n1->pass;
							}
							getch();
							goto start;
							break;
							case 5:
								system("cls");
								obj1.for_all(obj1.root);
								getch();
								goto start;
								break;
								case 6:
									return ;
									break;
		}
}


void lush::product_panel()
{
	int a,b;
	float c;
	string d;
	start:
		system("cls");
		gotoxy(32,3);
		cout<<"______________PRODUCT MENU__________________";
		gotoxy(42,5);
		cout<<" 1) For Adding New";
		gotoxy(42,6);
		cout<<" 2) For Deleting";
		gotoxy(42,7);
		cout<<" 3) For Updating";
		gotoxy(42,8);
		cout<<" 4) For Searching";
		gotoxy(42,9);
		cout<<" 5) For all";
		gotoxy(42,10);
		cout<<" 6) For Exit";
		do
		{
			gotoxy(42,12);
			cout<<" Enter here \t";
			cin>>a;
		}while(a<=0 || a>6);
		pro *n1 = new pro();
		switch(a)
		{
			case 1:
				system("cls");
				gotoxy(38,5);
				cout<<"___________New___________";
				gotoxy(40,7);
				cout<<" Enter id \t";
				cin>>b;
				gotoxy(40,8);
				cout<<" Enter Name of the Product \t";
				cin>>d;
				gotoxy(40,9);
				cout<<" Enter Price of Product \t";
				cin>>c;
				n1->name=d;
				n1->price=c;
				n1->id=b;
				obj3.root=obj3.insert(obj3.root,n1);
				getch();
				goto start;
				break;
				case 2:
					system("cls");
					gotoxy(40,5);
					cout<<" Enter id to Delete \t";
					cin>>b;
					n1=obj3.search(obj3.root,b);
					if(n1!=NULL)
					{
						obj3.root=obj3.del(obj3.root,b);
						gotoxy(43,8);
						cout<<" DELETED.....!";
					}
					else
					{
						gotoxy(43,8);
						cout<<" NOt Found";
					}
					getch();
					goto start;
					break;
					case 3:
						system("cls");
						gotoxy(40,5);
						cout<<" Enter id to Update \t";
						cin>>b;
						n1 = obj3.search(obj3.root,b);
						if(n1!=NULL)
						{
							gotoxy(40,7);
							cout<<" Enter New Name \t";
							cin>>n1->name;
							gotoxy(40,8);
							cout<<" Enter New Price \t";
							cin>>n1->price;
							gotoxy(40,10);
							cout<<" UPDATED....!";
						}
						else
						{
							gotoxy(43,8);
							cout<<" NOT FOUND";
						}
						getch();
						goto start;
						break;
						case 4:
							system("cls");
							gotoxy(40,5);
							cout<<" Enter Id to Search \t";
							cin>>b;
							n1 = obj3.search(obj3.root,b);
							if(n1!=NULL)
							{
								gotoxy(40,7);
								cout<<" Id  \t"<<n1->id;
								gotoxy(40,8);
								cout<<" Name  \t"<<n1->name;
								gotoxy(40,9);
								cout<<" Price  \t"<<n1->price;
							}
							else
							{
								gotoxy(43,8);
								cout<<" Not found";
							}
							getch();
							goto start;
							break;
							case 5:
								system("cls");
								obj3.for_all(obj3.root);
								getch();
								goto start;
								break;
								case 6:
									return ;
									break;
		}
}

void lush::patient_panel()
{
	int a,b;
	string c,d;
	start:
		system("cls");
		gotoxy(32,3);
		cout<<"______________Patient Menu_______________";
		gotoxy(40,5);
		cout<<" 1) For Adding New";
		gotoxy(40,6);
		cout<<" 2) For Deleting";
		gotoxy(40,7);
		cout<<" 3) For Updating";
		gotoxy(40,8);
		cout<<" 4) For Searching";
		gotoxy(40,9);
		cout<<" 5) For all";
		gotoxy(40,10);
		cout<<" 6) For Exit";
		do
		{
			gotoxy(40,12);
			cout<<" Enter here \t";
			cin>>a;
		}while(a<=0 || a>6);
		pat *n1= new pat();
		switch(a)
		{
			case 1:
				system("cls");
				gotoxy(37,5);
				cout<<"_____________New___________";
				gotoxy(40,7);
				cout<<" Enter Name of the Patient \t";
				cin>>c;
				gotoxy(40,8);
				cout<<" Enter Age of the Patient \t";
				cin>>b;
				gotoxy(40,9);
				cout<<" Enter Mobile Number \t";
				cin>>d;
				gotoxy(40,10);
				cout<<" Enter id of the Patient \t";
				cin>>a;
				n1->id=a;
				n1->name=c;
				n1->age=b;
				n1->mbn=d;
				obj2.root=obj2.insert(obj2.root,n1);
				getch();
				goto start;
				break;
				case 2:
					system("cls");
					gotoxy(37,5);
					cout<<" Enter id of the Patient to Delete \t";
					cin>>b;
					n1=obj2.search(obj2.root,b);
					if(n1!=NULL)
					{
						obj2.root=obj2.del(obj2.root,b);
						gotoxy(43,7);
						cout<<" DELETED....!";
					}
					else
					{
						gotoxy(43,7);
						cout<<" not found";
					}
					getch();
					goto start;
					break;
					case 3:
						system("cls");
						gotoxy(38,5);
						cout<<" Enter Patient id to Update \t";
						cin>>b;
						n1 = obj2.search(obj2.root,b);
						if(n1!=NULL)
						{
							gotoxy(40,7);
							cout<<" Enter new name \t";
							cin>>n1->name;
							gotoxy(40,8);
							cout<<" Enter new age \t";
							cin>>n1->age;
							gotoxy(40,9);
							cout<<" Enter new mobile number \t";
							cin>>n1->mbn;
							gotoxy(40,10);
							cout<<" UPDATED....!";
						}
						else
						{
							gotoxy(40,7);
							cout<<" Nothing Found";
						}
						getch();
						goto start;
						break;
						case 4:
							system("cls");
							gotoxy(38,5);
							cout<<" Enter Patient id to Search \t";
							cin>>b;
							n1 = obj2.search(obj2.root,b);
							if(n1!=NULL)
							{
								gotoxy(43,7);
								cout<<" id  \t"<<n1->id;
								gotoxy(43,8);
								cout<<" Name  \t"<<n1->name;
								gotoxy(43,9);
								cout<<" Age  \t"<<n1->age;
								gotoxy(43,10);
								cout<<" Mob.NUm \t"<<n1->mbn;
							}
							else
							{
								gotoxy(40,7);
								cout<<" Nothing Found";
							}
							getch();
							goto start;
							break;
							case 5:
								system("cls");
								obj2.for_all(obj2.root);
								getch();
								goto start;
								break;
								case 6:
									return ;
									break;
		}
}

void lush::slip_panel()
{
	int a,b,c,d,e;
	float f;
	string g,h,i,j;
	start:
		system("cls");
		gotoxy(32,3);
		cout<<"___________SLIP MENU_____________";
		gotoxy(40,5);
		cout<<" 1) For Adding New";
		gotoxy(40,6);
		cout<<" 2) For Deleting";
		gotoxy(40,7);
		cout<<" 3) For Updating";
		gotoxy(40,8);
		cout<<" 4) For Searching";
		gotoxy(40,9);
		cout<<" 5) For all";
		gotoxy(40,10);
		cout<<" 6) For Exit";
		do
		{
			gotoxy(40,12);
			cout<<" Enter here \t";
			cin>>a;
		}while(a<=0 || a>6);
		slip *n1 = new slip();
		switch(a)
		{
			case 1:
				system("cls");
				gotoxy(37,3);
				cout<<"_________NEW__________";
				gotoxy(40,5);
				cout<<" Enter name of the patient \t";
				cin>>g;
				gotoxy(40,6);
				cout<<" Enter Slip id \t";
				cin>>a;
				gotoxy(40,7);
				cout<<" Enter patient id \t";
				cin>>b;
				gotoxy(40,8);
				cout<<" Enter age \t";
				cin>>c;
				gotoxy(40,9);
				cout<<" Enter Product name \t";
				cin>>h;
				gotoxy(40,10);
				cout<<" Enter Price \t";
				cin>>f;
				gotoxy(40,11);
				cout<<" Enter User name \t";
				cin>>i;
				gotoxy(40,12);
				cout<<" Enter Mobile Number \t";
				cin>>j;
				n1->name=g;
				n1->id=a;
		        n1->p_id=b;
		        n1->age=c;
		        n1->p_n=h;
		        n1->price=f;
		        n1->u_n=i;
		        n1->mn=j;
				obj4.root=obj4.insert(obj4.root,n1);
				getch();
				goto start;
				break;
				case 2:
					system("cls");
					gotoxy(40,5);
					cout<<" Enter id to delete \t";
					cin>>b;
					n1 = obj4.search(obj4.root,b);
					if(n1!=NULL)
					{
						obj4.root= obj4.del(obj4.root,b);
						gotoxy(43,7);
						cout<<" DELETED.....!";
					}
					else
					{
						gotoxy(43,7);
						cout<<" Not found";
					}
					getch();
					goto start;
					break;
					case 3:
						system("cls");
							gotoxy(40,5);
							cout<<" Enter id to search \t";
							cin>>b;
							n1 = obj4.search(obj4.root,b);
							if(n1==NULL)
							{
								gotoxy(40,7);
								cout<<" nothing found";
							}
							else
							{
								gotoxy(40,7);
							   cout<<" Enter name of the patient \t";
				               cin>>n1->name;
				               gotoxy(40,8);
							   cout<<" Enter id \t";
				               cin>>n1->id;
				               gotoxy(40,9);
							   cout<<" Enter patient id \t";
				               cin>>n1->p_id;
				               gotoxy(40,10);
							   cout<<" Enter age \t";
				               cin>>n1->age;
				               gotoxy(40,11);
							   cout<<" Enter Product name \t";
			                   cin>>n1->p_n;
				               gotoxy(40,12);
							   cout<<" Enter Price \t";
				               cin>>n1->price;
				               gotoxy(40,13);
							   cout<<" Enter User name \t";
				               cin>>n1->u_n;
				               gotoxy(40,14);
							   cout<<" Enter Mobile Number \t";
				               cin>>n1->mn;
							   gotoxy(43,16);
							   cout<<" Updated......!";
							}
						getch();
						goto start;
						break;
						case 4:
							system("cls");
							gotoxy(40,5);
							cout<<" Enter id to search \t";
							cin>>b;
							n1 = obj4.search(obj4.root,b);
							if(n1==NULL)
							{
								gotoxy(40,7);
								cout<<" nothing found";
							}
							else
							{
								gotoxy(40,7);
								cout<<" Name is \t"<<n1->name;
								gotoxy(40,8);
								cout<<" Slip id \t"<<n1->id;
								gotoxy(40,9);
								cout<<" patient id \t"<<n1->p_id;
								gotoxy(40,10);
								cout<<" patient age \t"<<n1->age;
								gotoxy(40,11);
								cout<<" product name \t"<<n1->p_n;
								gotoxy(40,12);
								cout<<" price \t"<<n1->price;
								gotoxy(40,13);
								cout<<" mobile number \t"<<n1->mn;
								gotoxy(40,14);
								cout<<" user name \t"<<n1->u_n;
							}
							getch();
							goto start;
							break;
							case 5:
								obj4.for_all(obj4.root);
								getch();
								goto start;
								break;
								case 6:
									return ;
									break;
		}
}


void lush::cash_panel()
{
	int a,b;
	float f;
	string c;
	start:
		system("cls");
		gotoxy(32,3);
		cout<<"______________Cash Menu________________";
		gotoxy(40,5);
		cout<<" 1) For Adding New";
		gotoxy(40,6);
		cout<<" 2) For Deleting";
		gotoxy(40,7);
		cout<<" 3) For Updating";
		gotoxy(40,8);
		cout<<" 4) For Searching";
		gotoxy(40,9);
		cout<<" 5) For all";
		gotoxy(40,10);
		cout<<" 6) For Exit";
		do
		{
			gotoxy(40,12);
			cout<<" Enter here \t";
			cin>>a;
		}while(a<=0 || a>6);
		cash *n1 = new cash();
		switch(a)
		{
			case 1:
				system("cls");
				gotoxy(37,4);
				cout<<"_________NEW__________";
				gotoxy(40,6);
				cout<<" Enter name of the user \t";
				cin>>c;
			    gotoxy(40,7);
				cout<<" Enter id of the user \t";
			    cin>>b;
			    gotoxy(40,8);
				cout<<" Enter total sale \t";
			    cin>>f;
				n1->name=c;
				n1->id=b;
				n1->money=f;
				obj5.root=obj5.insert(obj5.root,n1);
				getch();
				goto start;
				break;
				case 2:
					system("cls");
					gotoxy(40,6);
					cout<<" Enter id to delete \t";
					cin>>b;
					n1 = obj5.search(obj5.root,b);
					if(n1!=NULL)
					{
						obj5.root= obj5.del(obj5.root,b);
						gotoxy(43,9);
						cout<<" DELETED.....!";
					}
					else
					{
						gotoxy(43,9);
						cout<<" not found";
					}
					getch();
					goto start;
					break;
					case 3:
						system("cls");
						gotoxy(40,5);
							cout<<" Enter id to search \t";
							cin>>b;
							n1 = obj5.search(obj5.root,b);
							if(n1==NULL)
							{
								gotoxy(43,8);
								cout<<" nothing found";
							}
							else
							{
								gotoxy(40,7);
							   cout<<" Enter new Name \t";
							   cin>>n1->name;
							   gotoxy(40,8);
							   cout<<" Enter new sale \t";
							   cin>>n1->money;
							   gotoxy(43,11);
							   cout<<" Updated......!";
							}
						getch();
						goto start;
						break;
						case 4:
							system("cls");
							gotoxy(40,5);
							cout<<" Enter id to search \t";
							cin>>b;
							n1 = obj5.search(obj5.root,b);
							if(n1==NULL)
							{
								gotoxy(43,7);
								cout<<" nothing found";
							}
							else
							{
								gotoxy(40,7);
								cout<<" Name  \t"<<n1->name;
								gotoxy(40,8);
								cout<<" Id  \t"<<n1->id;
								gotoxy(40,9);
								cout<<" Sale \t"<<n1->money;
							}
							getch();
							goto start;
							break;
							case 5:
								obj5.for_all(obj5.root);
								getch();
								goto start;
								break;
								case 6:
									return ;
									break;
		}
}


void lush::admin_panel()
{
	int a;
	start:
		system("cls");
		gotoxy(32,3);
		cout<<"_________________ADMIN MENU__________________";
		gotoxy(42,5);
		cout<<" 1) For User Panel";
		gotoxy(42,6);
		cout<<" 2) For Patient Panel";
		gotoxy(42,7);
		cout<<" 3) For Product Panel";
		gotoxy(42,8);
		cout<<" 4) For Cash nd Recipt";
		gotoxy(42,9);
		cout<<" 5) For DSA Stuff";
		gotoxy(42,10);
		cout<<" 6) For Exit";
		do
		{
			gotoxy(42,12);
			cout<<" Enter Here \t";
			cin>>a;
		}while(a<=0 || a>6);
		switch(a)
		{
			case 1:
				lush::user_panel();
				getch();
				goto start;
				break;
				case 2:
					lush::patient_panel();
					getch();
					goto start;
					break;
					case 3:
						lush::product_panel();
						getch();
						goto start;
						break;
						case 4:
							lush::cash_recipt_panel();
							getch();
							goto start;
							break;
							case 5:
								lush::dsa_panel();
								getch();
								goto start;
								break;
								case 6:
									return;
									break;
		}
}

void lush::show_slip(slip *n)
{
	system("cls");
	gotoxy(32,3);
	cout<<" ___________________("<<n->id<<")____________________";
	gotoxy(40,5);
	cout<<" Patient id \t"<<n->p_id;
	gotoxy(40,6);
	cout<<" Name \t"<<n->name;
	gotoxy(40,7);
	cout<<" Age \t"<<n->age;
	gotoxy(40,8);
	cout<<" Mob.NUM \t"<<n->mn;
	gotoxy(40,9);
	cout<<" Service \t"<<n->p_n;
	gotoxy(40,10);
	cout<<" Price \t"<<n->price;
	gotoxy(40,13);
	cout<<" Generated by \t "<<n->u_n;
}

void lush::show_cash(cash *n)
{
	gotoxy(30,5);
	cout<<" __________________("<<n->id<<")____________________";
	gotoxy(43,7);
	cout<<" Name \t"<<n->name;
	gotoxy(43,8);
	cout<<" Sale \t"<<n->money;
}

void lush::user_menu(int i,string x)
{
	int a,b,d;
	string c,e;
	cash *temp11;
	pat *temp21;
	pro *temp31;
	start:
		system("cls");
		gotoxy(32,3);
		cout<<"____________User Menu______________";
		gotoxy(43,5);
		cout<<" 1) For Registration";
		gotoxy(43,6);
		cout<<" 2) For Viewing Patient";
		gotoxy(43,7);
		cout<<" 3) For Viewing Products Info";
		gotoxy(43,8);
		cout<<" 4) For Cash Tally";
		gotoxy(43,9);
		cout<<" 5) For Exit";
		do
		{
			gotoxy(43,11);
			cout<<" Enter here \t";
			cin>>a;
		}while(a<=0 || a>5);
			pat *n2 = new pat();
			slip *s2 = new slip();
		switch(a)
		{
			case 1:
				m:
					system("cls");
					gotoxy(35,3);
					cout<<"_________Registration Menu__________";
				gotoxy(42,5);
				cout<<" 1) New Entry";
				gotoxy(42,7);
				cout<<" 2) By old Record";
				gotoxy(42,9);
				cout<<" 3) Exit";
				do
				{
					gotoxy(42,12);
					cout<<" Enter Here \t";
					cin>>a;
				}while(a<=0 || a>3);
				switch(a)
				{
					case 1:
						system("cls");
						gotoxy(40,3);
						cout<<" Enter Name of the Patient \t";
						cin>>c;
						gotoxy(40,4);
						cout<<" Enter Age of the Patient \t";
						cin>>b;
						gotoxy(40,5);
						cout<<" Enter Mobile Number \t";
						cin>>e;
						gotoxy(40,6);
						cout<<" Enter id of the Patient \t";
						cin>>a;
						n2->mbn=e;
						n2->age=b;
						n2->id=a;
						n2->name=c;
						obj2.root=obj2.insert(obj2.root,n2);
						gotoxy(40,8);
						cout<<" Enter product Id to add \t";
						cin>>d;
						temp31=obj3.search(obj3.root,d);
						if(temp31!=NULL)
						{
							gotoxy(40,10);
							cout<<" Enter Slip id \t";
							cin>>s2->id;
							s2->name=c;
							s2->age=b;
							s2->price=temp31->price;
							s2->p_id=a;
							s2->p_n= temp31->name;
							s2->mn=e;
							s2->u_n=x;
							obj4.root=obj4.insert(obj4.root,s2);
							temp11=obj5.search(obj5.root,i);
							temp11->money=temp11->money+temp31->price;
							lush::show_slip(s2);
							getch();
						}
						else
						{
							gotoxy(40,10);
							cout<<" No product Found ";
						}
						getch();
						goto m;
						break;
						case 2:
							system("cls");
							gotoxy(40,3);
							cout<<" Enter Patient id \t";
							cin>>b;
							temp21=obj2.search(obj2.root,b);
							if(temp21!=NULL)
							{
								gotoxy(40,5);
								cout<<" id \t"<<temp21->id;
								gotoxy(40,6);
								cout<<" Patient Name \t"<<temp21->name;
								gotoxy(40,7);
								cout<<" Age \t"<<temp21->age;
								gotoxy(40,8);
								cout<<" MOB.NUM \t"<<temp21->mbn;
								gotoxy(40,9);
								cout<<" Enter Product id \t";
								cin>>a;
								temp31=obj3.search(obj3.root,a);
								if(temp31!=NULL)
								{
									gotoxy(40,11);
									cout<<" Enter Slip id \t";
									cin>>s2->id;
									s2->name=temp21->name;
									s2->age=temp21->age;
									s2->mn=temp21->mbn;
									s2->p_id=temp21->id;
									s2->u_n=x;
									s2->price=temp31->price;
									s2->p_n=temp31->name;
									obj4.root=obj4.insert(obj4.root,s2);
									temp11=obj5.search(obj5.root,i);
									temp11->money=temp11->money+temp31->price;
									lush::show_slip(s2);
									getch();
								}
								else
								{
									gotoxy(40,11);
									cout<<" no product found";
								}
							}
							else
							{
								gotoxy(40,6);
								cout<<" No patient Record Found";
							}
							getch();
							goto m;
							break;
							case 3:
								break;
				}
				getch();
				goto start;
				break;
				case 2:
					system("cls");
					gotoxy(43,4);
					cout<<" Enter Patient id to see Info \t";
					cin>>b;
 					temp21 = obj2.search(obj2.root,b);
					if(temp21!=NULL)
					{
						gotoxy(43,6);
						cout<<" Id  \t"<<temp21->id;
						gotoxy(43,7);
						cout<<" Name  \t"<<temp21->name;
						gotoxy(43,8);
						cout<<" Mob.Num  \t"<<temp21->mbn;
					}
					else
					{
						gotoxy(43,7);
						cout<<" No Record Found ";
					}
					getch();
					goto start;
					break;
					case 3:
						system("cls");
                        obj3.for_all(obj3.root);
						getch();
						goto start;
						break;
						case 4:
							temp11=obj5.search(obj5.root,i);
							system("cls");
							lush::show_cash(temp11);
							getch();
							goto start;
							break;
							case 5:
								return;
								break;
		}
}

void lush::menu()
{
	int a;
	int b;
	int d;
	string c,un;
	user *temp,*temp2;
	start:
		system("cls");  
		gotoxy(32,4);
		cout<<"____________ Med Lush $$$________________";
		gotoxy(43,6);
		cout<<" 1) Login as Admin";
		gotoxy(43,8);
		cout<<" 2) login as User";
		gotoxy(43,10);
		cout<<" 3) EXIT";
		do
		{
			gotoxy(43,12);
			cout<<" Enter here \t";
			cin>>a;
		}while(a<=0 || a>3);
		switch(a)
		{
			case 1:
				system("cls");
				gotoxy(32,5);
				cout<<"_____________ADMIN LOGIN_______________";
				gotoxy(43,7);
				cout<<" Enter name \t";
				cin>>c;
				gotoxy(43,9);
				cout<<" Enter pass \t";
				cin>>b;
				if(c==lush::name && b==lush::pass)
				{
					lush::admin_panel();
				}
				else
				{
					gotoxy(43,11);
					cout<<" Wrong name or password";
				}
				getch();
				goto start;
				break;
				case 2:
					system("cls");
					gotoxy(32,5);
					cout<<"____________USER LOGIN____________";  
					gotoxy(43,7);
					cout<<" Enter username \t";
					cin>>c;
					gotoxy(43,9);
					cout<<" Enter pass \t";
					cin>>b;
					temp = obj1.check_pass(obj1.root,b);
					if(temp==NULL || temp->name!=c)
					{
						gotoxy(43,11);
						cout<<" Wrong Username or Password";
					}
					else
					{
						d=temp->id;
						un=temp->name;
						lush::user_menu(d,un);
					}
					getch();
					goto start;
					break;
					case 3:
						fstream out_user,out_pat,out_pro,out_slip,out_cash;
						out_user.open("user.txt", ios::out);
						out_pat.open("pat.txt", ios::out);
						out_pro.open("pro.txt", ios::out);
						out_slip.open("slip.txt", ios::out);
						out_cash.open("cash.txt", ios::out);
						lush::user_seri(obj1.root,out_user);
						lush::patient_seri(obj2.root,out_pat);
						lush::product_seri(obj3.root,out_pro);
						lush::slip_seri(obj4.root,out_slip);
						lush::cash_seri(obj5.root,out_cash);
						out_user.close();
						out_pat.close();
						out_pro.close();
						out_slip.close();
						out_cash.close();
						exit(0);
						break;
		}
}

// serialization............................................

void lush::user_seri(user *r,fstream &o)
{
	if(r==NULL)
	{
		o<<"# ";
		return;
	}
	
	o<<r->name<<" "<<r->id<<" "<<r->pass<<" ";
	lush::user_seri(r->left,o);
	lush::user_seri(r->right,o);
}

void lush::patient_seri(pat *r,fstream &o)
{
	if(r==NULL)
	{
		o<<"# ";
		return ;
	}
	
	o<<r->name<<" "<<r->mbn<<" "<<r->id<<" "<<r->age<<" ";
	
	lush::patient_seri(r->left,o);
	lush::patient_seri(r->right,o);
}

void lush::product_seri(pro *r,fstream &o)
{
	if(r==NULL)
	{
		o<<"# ";
		return ;
	}
	
	o<<r->name<<" "<<r->id<<" "<<r->price<<" ";
	
	lush::product_seri(r->left,o);
	lush::product_seri(r->right,o);
}

void lush::slip_seri(slip *r,fstream &o)
{
	if(r==NULL)
	{
		o<<"# ";
		return ;
	}
	
	o<<r->p_n<<" "<<r->u_n<<" "<<r->p_id<<" "<<r->price<<" "<<r->name<<" "<<r->mn<<" "<<r->id<<" "<<r->age<<" ";
	
	lush::slip_seri(r->left,o);
	lush::slip_seri(r->right,o);
}

void lush::cash_seri(cash *r,fstream &o)
{
	if(r==NULL)
	{
		o<<"# ";
		return;
	}
	
	o<<r->name<<" "<<r->id<<" "<<r->money<<" ";
	
	lush::cash_seri(r->left,o);
	lush::cash_seri(r->right,o);
}

// deserialization.................................................
cash *lush::cash_deseri(fstream &i)
{
	string tn;
	int  ti;
	float tm;
	i>>tn;
	if(tn=="#")
	{
		return NULL;
	}
	i>>ti;
	i>>tm;
	cash *ca = new cash();
	ca->name = tn;
	ca->id = ti;
	ca->money = tm;
	ca->left = lush::cash_deseri(i);
	ca->right = lush::cash_deseri(i);
	return ca;
}

slip *lush::slip_deseri(fstream &i)
{
	string tpn,tun,tn,tmn;
	int  tpi,ti,ta;
	float tp;
	i>>tpn;
	if(tpn=="#")
	{
		return NULL;
	}
	i>>tun;
	i>>tpi;
	i>>tp;
	i>>tn;
	i>>tmn;
	i>>ti;
	i>>ta;
	slip *sl = new slip();
	sl->name = tn;
	sl->id = ti;
	sl->p_n = tpn;
	sl->price = tp;
	sl->u_n = tun;
	sl->mn = tmn;
	sl->p_id = tpi;
	sl->age = ta;
	sl->left = lush::slip_deseri(i);
	sl->right = lush::slip_deseri(i);
	return sl;
}


user *lush::user_deseri(fstream &i)
{
	string tn;
	int ti,tp;
	i>>tn;
	if(tn=="#")
	{
		return NULL;
	}
	i>>ti;
	i>>tp;
	user *us = new user();
	us->name = tn;
	us->id = ti;
	us->pass = tp;
	us->left = lush::user_deseri(i);
	us->right = lush::user_deseri(i);
	return us;
}

pat *lush::patient_deseri(fstream &i)
{
	string tn,tmbn;
	int ti,ta;
	
	i>>tn;
	if(tn=="#")
	{
		return NULL;
	}
	i>>tmbn;
	i>>ti;
	i>>ta;
	pat *pa = new pat();
	pa->name = tn;
	pa->mbn = tmbn;
	pa->id = ti;
	pa->age = ta;
	pa->left = lush::patient_deseri(i);
	pa->right = lush::patient_deseri(i);
	return pa;
}

pro *lush::product_deseri(fstream &i)
{
	string tn;
	int ti;
	float tp;
	i>>tn;
	if(tn=="#")
	{
		return NULL;
	}
	
	i>>ti;
	i>>tp;
	pro *p = new pro();
	p->name = tn;
	p->id = ti;
	p->price = tp;
	p->left = lush::product_deseri(i);
	p->right = lush::product_deseri(i);
	return p;
}

int main()
{
	lush z;
	fstream in_user,in_pat,in_pro,in_slip,in_cash;
	in_user.open("user.txt", ios::in);
	in_pat.open("pat.txt", ios::in);
	in_pro.open("pro.txt", ios::in);
	in_slip.open("slip.txt", ios::in);
	in_cash.open("cash.txt", ios::in);
	if(in_user)
	{
		obj1.root=z.user_deseri(in_user);
	}
	
	if(in_pat)
	{
		obj2.root=z.patient_deseri(in_pat);
	}
	
	if(in_pro)
	{
		obj3.root=z.product_deseri(in_pro);
	}
	
	if(in_slip)
	{
		obj4.root=z.slip_deseri(in_slip);
	}
	
	if(in_cash)
	{
		obj5.root=z.cash_deseri(in_cash);
	}
	
	in_user.close();
	in_pat.close();
	in_pro.close();
	in_slip.close();
	in_cash.close();
	z.menu();
	return 0;
} 