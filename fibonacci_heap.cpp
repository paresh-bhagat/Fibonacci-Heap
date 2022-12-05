#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
using namespace std;

// class for node of fibonacci heap

class node
{
    public:
        int key;           //value of node
        node *parent;      //parent of node
        node *child;       //pointer to a child
        node *left;        //pointer to left node
        node *right;        //pointer to right node
        int degree;         //degree of node
        char mark;          //black or white marked
};

//class for node of queue

class nodeq
{
public:
    node *pointer;
    nodeq *next;
};

//class for queue

class mydeque
{
    private:
        nodeq *front;
        nodeq *back;
    public:
        mydeque()
        {
            front=NULL;
            back=NULL;
        }
        void push_back(node *block)
        {
            nodeq *temp=new nodeq;
            temp->pointer=block;
            temp->next=NULL;
            if(front==NULL)
            {
                front=temp;
                back=temp;
            }
            else
            {
                back->next=temp;
                back=temp;
            }
        }
        void push_front(node *block)
        {
            nodeq *temp=new nodeq;
            temp->pointer=block;
            if(front==NULL)
            {
                front=temp;
                front->next=NULL;
            }
            else
            {
                temp->next=front;
                front=temp;
            }
        }
        bool isempty()
        {
            if(front==NULL)
                return true;
            else
                return false;
        }
        node* pop_front()
        {
            node *temp2;
            nodeq *temp;
            temp=front;
            front=front->next;
            if(front==NULL)
                back=NULL;
            temp2=temp->pointer;
            delete(temp);
            return temp2;
        }
        void insert(node *block,int position)
        {
            nodeq *temp=new nodeq;
            temp->pointer=block;
            if(front==NULL)
            {
                front=temp;
                front->next=NULL;
            }
            else if(position==1)
            {
                temp->next=front;
                front=temp;
            }
            else if(position>1)
            {
                nodeq *temp2=front;
                for(int i=1;temp2!=NULL;i++)
                {
                    if(i+1==position)
                    {
                        temp->next=temp2->next;
                        temp2->next=temp;
                        break;
                    }
                    temp2=temp2->next;
                }
            }
        }
        void display_mydeque()
        {
            cout<<endl;
            if(isempty()!=true)
            {
                nodeq *temp=front;
                while(temp!=NULL)
                {
                    cout<<temp->pointer->key<<" ";
                    temp=temp->next;
                }
            }
        }
};

//class for fibonacci heap

class fibonacci_heap
{
    private:
        node *min;
        int no_of_nodes;
        node *node_found;                                         //pointer to min
    public:
        fibonacci_heap();                                    //consructor for class
        void make_heap();                                    //make fibonaccci heap
        void insert_heap(int value);                          //insert in fibonacci heap
        int find_min();                                       //return minimum value in fibonacci heap
        void find_node(int value,node *temp1,node *temp2);    //for finding node                         //
        void fibonacci_link(node *temp1,node *temp2);        // Linking the heap nodes in parent child relationship
        void consolidate_heap();                              // Consolidating the heap
        void delete_min();                                     //delete minimum value in fibonacci heap
        void cut(node *temp);
        bool decrease_key(int old_value,int new_value);         //decrease any key
        void display(node *temp,node *temp2);                 //display fibonacci heap
        void display(){display(min,min);}
        int total_nodes();
};

//constructor for class fibonacci heap

fibonacci_heap::fibonacci_heap()
{
    min=NULL;
    no_of_nodes=0;
    node_found=NULL;
}

//construct fibonacci heap

void fibonacci_heap::make_heap()
{
    ifstream in;
    in.open("E:\\study material\\iitdelhi\\iit delhi 1st sem\\software fundamentals\\assignment-1 sf\\elements.txt");
    if(!in)
    {
        cout<<"File not opened";
        exit(0);
    }
    else                                               //for roots
    {
        mydeque q;
        cout<<"Heap element file opened";
        node *temp=NULL,*last=NULL,*first=NULL;
        int n,d;
        in>>d;
        no_of_nodes+=d;
        //cout<<"no. of roots="<<d<<"\n";
        for(int i=1;i<=d;i++)
        {
            in>>n;
            //cout<<n<<" ";
            temp=new node;
            temp->parent=NULL;
            temp->key=n;
            temp->degree=0;
            temp->mark='W';
            temp->child=NULL;
            temp->left=last;
            temp->right=NULL;
            if(i!=1)
                last->right=temp;
            last=temp;
            if(i==1)
            {
                first=temp;
                min=temp;
            }
            if(i==d)
            {
                last->right=first;
                first->left=last;
            }
            if((min->key)>last->key)
                min=last;
            q.push_back(last);
        }
        while(q.isempty()!=true)
        {
            //q.display_mydeque();
            node *temp2;
            in>>n>>d;
            //cout<<"\n"<<n<<" "<<d;
            temp2=q.pop_front();
            no_of_nodes+=d;
            if(d!=0)
            {
                temp=NULL;
                last=NULL;
                first=NULL;
                temp2->degree=d;
                for(int i=1;i<=d;i++)
                {
                    in>>n;
                    //cout<<"\n";
                    //cout<<n<<" ";
                    temp=new node;
                    temp->parent=temp2;
                    temp->key=n;
                    temp->mark='W';
                    temp->degree=0;
                    temp->child=NULL;
                    temp->left=last;
                    temp->right=NULL;
                    if(i!=1)
                        last->right=temp;
                    last=temp;
                    if(i==1)
                    {
                        first=temp;
                        temp2->child=temp;
                    }
                    if(i==d)
                    {
                        last->right=first;
                        first->left=last;
                    }
                    q.insert(last,i);
                }
            }
        }
    }
    in.close();
}

//insert in fibonacci heap

void fibonacci_heap::insert_heap(int value)
{
    node *temp=new node;
    temp->child=NULL;
    temp->mark='W';
    temp->parent=NULL;
    temp->key=value;
    temp->degree=0;
    temp->left=temp->right=NULL;
    if(min==NULL)
    {
        min=temp;
        min->left=min;
        min->right=min;
    }
    else
    {
        temp->right=min;
        temp->left=min->left;
        min->left->right=temp;
        min->left=temp;
        if((min->key)>(temp->key))
            min=temp;
    }
    no_of_nodes++;
}

//return minimum value in fibonacci heap

int fibonacci_heap::find_min()
{
    return min->key;
}

//return number of nodes in fibonacci heap

int fibonacci_heap::total_nodes()
{
    return no_of_nodes;
}

// Linking the heap nodes in parent child relationship

void fibonacci_heap::fibonacci_link(node *temp1,node *temp2)
{
    temp1->left->right=temp1->right;     //unlink temp1 from root nodes
    temp1->right->left=temp1->left;
    if(temp2->right==temp2)
        min=temp2;
    temp1->parent=temp2;                     //make parent of temp1=temp2
    if(temp2->child==NULL)                 //if temp2 child is NULL
    {
        temp2->child=temp1;
        temp1->left=temp1;
        temp1->right=temp1;
    }
    else
    {
        temp1->right=temp2->child->right;
        temp1->left=temp2->child;
        temp2->child->right->left=temp1;
        temp2->child->right=temp1;
    }                                           //else
    //if (temp1->key < (temp2->child)->key)
    //    temp2->child = temp1;
    temp1->mark='W';
    temp2->degree++;
}

 // Consolidating the heap

void fibonacci_heap::consolidate_heap()
{
    int i;
    float max_size=(log(no_of_nodes)) / (log(2));
    int array_size = max_size;
    node* arr[array_size+1];
    for(int i=0;i<=array_size;i++)
        arr[i]=NULL;
    node* ptr1=min;
    do
    {
        if(min->key > ptr1->key)      //update minimum
            min=ptr1;
        if(arr[ptr1->degree]==NULL)   //check empty
        {
            arr[ptr1->degree]=ptr1;
            ptr1=ptr1->right;
        }
        else                     //union
        {
            if((arr[ptr1->degree]->key) > (ptr1->key))
            {
                if(arr[ptr1->degree]==min)
                    min=ptr1;
                i=ptr1->degree;
                fibonacci_link(arr[ptr1->degree],ptr1);
                arr[i]=NULL;
            }
            else if((arr[ptr1->degree]->key) < (ptr1->key))
            {
                if(ptr1==min)
                    min=arr[ptr1->degree];
                i=ptr1->degree;
                fibonacci_link(ptr1,arr[ptr1->degree]);
                ptr1=arr[ptr1->degree];
                arr[i]=NULL;
            }
        }

    }while(arr[ptr1->degree]!=ptr1);
}

// delete minimum in fibonacci heap

void fibonacci_heap::delete_min()
{
    if (min == NULL)
        cout << "Heap is empty" << endl;
    else
    {
        if(min==min->right && min->child==NULL)
            min=NULL;
        else
        {
            if(min->child!=NULL)
            {
                node *temp=NULL,*temp1=NULL;
                temp=min->child;
                min->child=NULL;
                temp->left=min->left;
                min->left->right=temp;
                temp1=temp;
                do
                {
                   temp1->parent=NULL;
                   temp1=temp1->right;
                }while(temp1->right!=temp);
                temp1->parent=NULL;
                temp1->right=min;
                min->left=temp1;
            }
            min->left->right=min->right;
            min->right->left=min->left;
            min=min->right;                          //doubt
            consolidate_heap();
        }

    }
    no_of_nodes--;
}

//find node in heap

void fibonacci_heap::find_node(int value,node *temp1,node *temp2)
{
    if(temp1!=NULL && node_found==NULL)
    {
        if(temp1->key==value)
            node_found=temp1;
        find_node(value,temp1->child,temp1->child);
        if(temp1->right!=temp2)
            find_node(value,temp1->right,temp2);
    }
}

//cut node tree and paste to root list

void fibonacci_heap::cut(node *temp)
{
    temp->mark='W';
    if(temp->parent->degree==1)
        temp->parent->child=NULL;
    else
    {
        if(temp->parent->child==temp)
            temp->parent->child=temp->left;
        temp->left->right=temp->right;
        temp->right->left=temp->left;
    }
    temp->parent->degree--;
    temp->parent=NULL;
    temp->left=min->left;
    temp->right=min;
    temp->left->right=temp;
    min->left=temp;
    if(min->key>temp->key)
        min=temp;
}

// decrease key in fibonacci heap

bool fibonacci_heap::decrease_key(int old_value,int new_value)
{
    node_found=NULL;
    find_node(old_value,min,min);
    if(node_found==NULL)
        return false;
    else
    {
        node_found->key=new_value;
        if(node_found->parent==NULL && (node_found->key)<(min->key))                       //if node is root node
            min=node_found;
        else if(node_found->parent!=NULL && ((node_found->parent->key)<(node_found->key)))    //if heap property is not violated
        {

        }
        else if(node_found->parent!=NULL && ((node_found->parent->key)>(node_found->key)) && (node_found->parent->mark=='W')) //if min heap property violated but parent is unmarked
        {
            if(node_found->parent->parent!=NULL)
                node_found->parent->mark='B';
            cut(node_found);
        }
        else if(node_found->parent!=NULL && ((node_found->parent->key)>(node_found->key)) && (node_found->parent->mark=='B')) //if min heap property violated but parent is marked
        {
            node *temp1=node_found,*temp2=NULL;
            do
            {
                temp2=temp1->parent;
                cut(temp1);
                temp1=temp2;
            }while(temp1->parent!=NULL && temp1->mark=='B');
            if(temp1->parent!=NULL)
                temp1->mark='B';
        }
        node_found=NULL;
        return true;
    }
}

// display fibonacci heap using recursion

void fibonacci_heap::display(node *temp,node *temp2)
{
    if(temp!=NULL)
    {
        if(temp2==min)
        {
            cout<<"\n"<<"All nodes of tree with root node="<<temp->key<<" : ";
        }
        cout<<temp->key<<" ";
        display(temp->child,temp->child);
        if(temp->right!=temp2)
            display(temp->right,temp2);
    }
}

int main()
{
    fibonacci_heap f;
    int c,new_value,old_value;
    f.make_heap();
    cout<<"\nFibonacci heap created";
    while(1)
    {
        cout<<"\n\nEnter 1 to display all elements"<<endl;
        cout<<"Enter 2 to get total number of nodes"<<endl;
        cout<<"Enter 3 to display minimum value"<<endl;
        cout<<"Enter 4 to decrease value of a node"<<endl;
        cout<<"Enter 5 to delete minimum value"<<endl;
        cout<<"Enter 6 to quit"<<endl;
        cin>>c;
        switch(c)
        {
            case 1:
                f.display();
                break;
            case 2:
                cout<<"\n\nTotal number of nodes in heap = "<<f.total_nodes();
                break;
            case 3:
                cout<<"\n\nMinimum value in heap = "<<f.find_min();
                break;
            case 4:
                cout<<"\nEnter value of node to be decreased = ";
                cin>>old_value;
                cout<<"Enter new value of node = ";
                cin>>new_value;
                if(f.decrease_key(old_value,new_value))
                    cout<<"\nvalue of node successfully decreased from "<<old_value<<" to "<<new_value;
                else
                    cout<<"\nValue not found in heap";
                break;
            case 5:
                f.delete_min();
                cout<<"\nMinimum value deleted";
                break;
            case 6:
                exit(0);
            default:
                cout<<"\nWrong value entered"<<endl;
        }
    }
    return 0;
}
