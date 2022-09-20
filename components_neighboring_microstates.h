int Max_Cpnts = 10;

void cpntInit(int i , vector<State> &  Microstates_X )
{
    
    
    vector<int> cpnt(Max_Cpnts);
    
    for( int i=0 ; i<Max_Cpnts ; i++ )
		cpnt[i] = -1;
    
    
	Microstates_X[i].cpnt = cpnt ;
        
}


void cpntAdd(int i, int k , vector<State> &  Microstates_X )
{
    
    int j = 0;
    
    State & x_i = Microstates_X[i];
    
    
    while ( (j < Max_Cpnts)  and ( x_i.cpnt[j] != -1 )  )
        j = j + 1;
  
        
    if ( (j+1) == Max_Cpnts )  // j >= Max_Cpnts
        cout<<"Error: Maximum cpnt is reached"<<endl;
        
    else
        x_i.cpnt[j] = k;
        

}

int cpntMax(int i ,  vector<State> & Microstates_X )
{
 
    
    State & x_i = Microstates_X[i];
    
    int MIN = -1 , temp_peak;
    
    if ( x_i.cpnt[0] == -1) 
        cout<< "Error: Component list is empty and has no maximum " << endl;
    else
    {
        
        MIN = PeakFind( x_i.cpnt[0] , Microstates_X );
        
        for( int j=1 ;  j < Max_Cpnts ; j++ ) 
        {    
            if ( x_i.cpnt[j] == -1 ) 
                continue    ;        
            
            temp_peak = PeakFind( x_i.cpnt[j] , Microstates_X );
            
            if ( temp_peak < MIN )
                MIN = temp_peak;
                
         }
         
    }   

    return MIN;

}
