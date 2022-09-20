


bool PeakExist_In_Cpnt(  int pkid , vector<int> &  cpnt  )
{
	for ( int i=0 ; i < int( cpnt.size() ) ; i++ )
	{
		if ( pkid == cpnt[i] )
			return true;
	} 
	
	return false;
}



vector<List_ZHG> Compute_H0_group( vector<State> &  X  )
{
    
    int state_space_size = int( X.size()  );
    int d = int( X[0].vec.size() ) ;
    
    cout<<"Total States:" << state_space_size << endl;
    cout<<"State Vector Dimentions:"<<d<<endl;
    
    for(int i=0 ; i < state_space_size ; i++)
    {
		
        X[i].pk = i;
        X[i].mkd = 0;
        
        cpntInit( i ,  X );
        
        X[i].PrevN = NULL;
        X[i].NextN = NULL; 
        X[i].PrevS = NULL; 
        X[i].NextS = NULL;
        X[i].sorted_index = i;
	}


    

    
    vector<List> S  =  StateHash( d , X );
 
    vector<List_ZHG> H = HInit();
    
    HBirthAdd( H , d , X[0].prob , 0 ,  X );

    vector<List> B = BoundaryInit();

    X[0].mkd = 1;
    vector< vector<int> >  N = NeighborList( 0 , d , X );
    
    
    vector<int> I = NeighborIndex( S , N , d   );
    
    
    
    
    for(int j=0 ; j < int( I.size() ) ; j++ )
    {    
		if ( I[j] != -1 )
		{
            BoundaryAdd( B , I[j] , d , X );
            cpntAdd(I[j], 0 , X);
            PeakAssign(I[j],0, X );
         }
    
	}
    
    
    
    for( int i=1 ; i < state_space_size ; i++  )
	{

        if ( OnBoundary( B , i , d , X) == true )
        {
            int peakId = cpntMax(i , X );
            
            for(int j=0 ; j < Max_Cpnts ; j++ )
            {
                
                if (  ( X[i].cpnt[j] != -1 ) and  ( PeakFind( X[i].cpnt[j] , X ) != peakId )  )
                {
                    
                    long double BirthProb  = X[ PeakFind( X[i].cpnt[j] , X ) ].prob ;
                    int BirthState = PeakFind( X[i].cpnt[j] , X );
                    long double DeathProb  = X[i].prob;
                    int DeathState = i;

                    HDeathAdd( H , d , BirthState, DeathProb, DeathState , X ) ; 
                    
                    X [ X[i].cpnt[j]   ].pk = peakId ;

                 }
            }
            
            BoundaryRemove( B, i, d , X);

        }    
        else
        {   
            HBirthAdd( H , d , X[i].prob, i, X);
            cpntAdd( i , i , X );
        }   

        

        X[i].mkd = 1;
        N = NeighborList(i, d , X);
        I = NeighborIndex(S , N , d );
        
        for( int j=0 ; j < int( I.size() ) ; j++  )
        {
            
            if ( I[j] != -1 )
            {   
                
                if ( ( OnBoundary( B, I[j] , d , X ) == false ) &&  ( X[  I[j] ].mkd == 0 )  )
                {  

                    BoundaryAdd(B , I[j] , d , X );
                    X[I[j]].pk=X[i].pk;

                }

                    
                if ( ! PeakExist_In_Cpnt( PeakFind(i , X ) , X[ I[j] ].cpnt  )   )
                {   

                    cpntAdd( I[j] , PeakFind(i  , X) , X );

                }

                
             }
             
        }

    }
    
    return H; 
}
