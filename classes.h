

class  State 
{
	
	public:
	
	int pk;
	bool mkd;
	vector<int> cpnt;
	long double prob;
	vector<int>  vec;
	State *PrevS;
	State *NextS;
	
	State *PrevN;
	State *NextN;
	
	int sorted_index;

	State( int *arr , int d , long double prob )
	{
		for ( int i=0 ; i<d ; i++ )
			this->vec.push_back( arr[i] ) ;
			
		this->prob = prob;
		
	}
	
	State( vector<int> vec , int d , long double prob )
	{
		
		this->vec  = vec;
		this->prob = prob;
		
	}
	
	
}; 

class List
{
     public:
       State *head;
       State *tail;
        
 };


class Zero_Homology_Group
{
    
    public:
        
        long double pb;
        int xb;
        long double pd;
        int xd;
        Zero_Homology_Group * NextH;
        Zero_Homology_Group * PrevH;

    Zero_Homology_Group()
    {
         pb = -1;
         xb = -1;
         pd = -1;
         xd = -1;
         NextH = NULL;
         PrevH = NULL;
	}
     
         
};

class List_ZHG
{
     public:
       Zero_Homology_Group *head;
       Zero_Homology_Group *tail;

       List_ZHG()
       {
           head = NULL;
           tail = NULL;
       }
        
 };

