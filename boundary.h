

int N_Slots1 =    100000;

vector<List>    BoundaryInit(  )
{
    vector<List> boundry_arry(N_Slots1);
    return boundry_arry;
}


bool OnBoundary( vector<List> &  boundary_array , int i , int d , vector<State> & Microstates_X )
{
    
    
    State & x_i  =  Microstates_X[i];
    
    int slot =  HashFunction( N_Slots1 , x_i.vec , d );
    
    bool Found = false;
    
    State *s = boundary_array[ slot ].head;
    
    
    while ( s != NULL )
    {
        
        if ( s->sorted_index == i    )     
        {   
            Found = true;
            return Found;
        }
        else
        {
            s = s->NextN;
        }
            
    }
            
    return Found;
}

void BoundaryAdd( vector<List>  & boundary_array , int i , int d , vector<State> &   Microstates_X )
{
    
    State & x_i = Microstates_X[i];
    
    int slot =  HashFunction( N_Slots1 , x_i.vec , d );
    
    if (boundary_array[slot].head == NULL)
    {    
        boundary_array[slot].head =  &x_i;  
        boundary_array[slot].tail =  &x_i;
        x_i.NextN = NULL ;
        x_i.PrevN = NULL;
    }
    else
    {
        
        boundary_array[slot].tail->NextN = &x_i;
        x_i.PrevN = boundary_array[slot].tail;
        x_i.NextN = NULL;
        boundary_array[slot].tail = &x_i;
        
    }

}




void BoundaryRemove(vector<List> &  boundary_array , int i , int d , vector<State> &   Microstates_X )
{    
    
    
    State & x_i = Microstates_X[i];
    
    int slot =  HashFunction( N_Slots1 , x_i.vec , d );
    
    if ( boundary_array[slot].head == boundary_array[slot].tail  )
    {   
        boundary_array[slot].head = NULL; 
        boundary_array[slot].tail  = NULL;
        
        x_i.NextN = NULL;
        x_i.PrevN = NULL;
    }
    
    else
    {  
        
        if ( x_i.sorted_index == boundary_array[slot].head->sorted_index )
        {    // update head
            // set prev with null 
            
            boundary_array[slot].head = boundary_array[slot].head->NextN;
            boundary_array[slot].head->PrevN = NULL;
            
        }
        else if ( x_i.sorted_index == boundary_array[slot].tail->sorted_index )
        {    // update tail
            // set next with null
            
            boundary_array[slot].tail = boundary_array[slot].tail->PrevN;
            boundary_array[slot].tail->NextN = NULL;
        }
            
        else
        {
            x_i.PrevN->NextN = x_i.NextN;
            x_i.NextN->PrevN = x_i.PrevN;
         }
            
            
        x_i.NextN = NULL;
        x_i.PrevN = NULL;  
    }    
             

}
