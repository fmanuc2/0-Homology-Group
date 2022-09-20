int N_Slots2 =    100000;

vector<List> StateInit()
{
    
    vector<List> S(N_Slots2);
    
    return S;
}


void StateAdd( vector<List> & S , int i , int  d , vector<State> & Microstates_X )
{
    

    State & x_i = Microstates_X[i];
    
    int slot = HashFunction( N_Slots2, x_i.vec , d );
    
    if ( S[slot].head == NULL )
    { 
		
        S[slot].head = &x_i;
        S[slot].tail = &x_i;
        x_i.NextS = NULL;
        x_i.PrevS = NULL;
        
    }
    else
    { 
        S[slot].tail->NextS = &x_i;
        x_i.PrevS = S[slot].tail;
        x_i.NextS = NULL;
        S[slot].tail = &x_i;
        
     }
        
}


vector<List> StateHash( int d , vector<State> & Microstates_X )
{
    
    vector<List> S = StateInit();
    
    for( int i = 0 ; i < int( Microstates_X.size() ) ; i++ )
        StateAdd(  S , i , d  , Microstates_X );
        
    return S;
}
