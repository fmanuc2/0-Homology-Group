bool CompareVectors( vector<int> &  vec1 ,  vector<int> & vec2 )
{
	if (  vec1.size()== vec2.size()  )
	{
		
		for ( int i=0 ; i < int( vec1.size() ) ; i++ )
		{ 
			if  (  vec1[i]!= vec2[i]  )
				return false;
		}
		
		return true;
		
	}
	
	return false;
}
 

int FindNbIndex( vector<List> & S, vector<int> & x , int d )
{
	
    
    int slot = HashFunction(N_Slots2, x , d);
    
    State *x_j = S[slot].head;
    
    while ( x_j != NULL )
    {   
        
        if ( CompareVectors(  x_j->vec , x ) )    //   compare vectors  [1,2] == [1,2]
		{
            	return x_j->sorted_index ;
        }
        else
        {
            x_j = x_j->NextS;
        }
    }
    
    return -1;
    
 }



vector< vector<int>  >    NeighborList(int i, int d ,  vector<State> &  Microstates_X )
{
    
    vector< vector<int> > N(2*d);
    
    
    State & x_i = Microstates_X[ i ];
    
    for( int j=0 ; j < d ; j++ )
    {
        
        vector<int> y1 =  x_i.vec;
        y1[j] = x_i.vec[j] - 1;
        N[2*j] = y1;
        
        vector<int> y2 =  x_i.vec;
        y2[j] = x_i.vec[j] + 1;
        N[2*j+1] = y2;
        
    }
        
        
    return N;

}

vector<int> NeighborIndex( vector<List> & S , vector< vector<int>  > &  N ,  int d )
{ 
    
    vector<int> I(2*d);
    
    for( int i =0 ; i < 2*d ; i++ )
        I[i] = FindNbIndex( S , N[i] , d );
        
    return I;
}
