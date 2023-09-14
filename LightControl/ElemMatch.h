#ifndef ELEMMATCH_H
#define ELEMMATCH_H

template<typename ElemType>
void CptPfFunc( const ElemType *Pattern,unsigned int pattern_len, int *PrefixFunc )
{
    int iLen = pattern_len;

    int LOLP = 0;     // Lenth of longest prefix
    PrefixFunc[0] = 0;
    PrefixFunc[1] = 0;

    for( int NOCM=2; NOCM<iLen+1; NOCM++ )     // NOCM represent the number of characters matched
    {
        while( LOLP>0 && (Pattern[LOLP] != Pattern[NOCM-1]) )
            LOLP = PrefixFunc[LOLP];
        if( Pattern[LOLP] == Pattern[NOCM-1] )
            LOLP++;
        PrefixFunc[NOCM] = LOLP;
    }
}

template<typename ElemType>
int  KMPElemMatching( const ElemType* Target,unsigned int target_len, const ElemType *Pattern ,unsigned int pattern_len)
{
    int *PrefixFunc = new int[pattern_len+1];
    int TarLen = target_len;
    int PatLen = pattern_len;

    // Compute the prefix function of Pattern
    CptPfFunc( Pattern,PatLen, PrefixFunc );

    int NOCM = 0;     // Number of characters matched
    int find_pos = -1;

    for( int i=0; i<TarLen; i++ )
    {
        while( NOCM>0 && Pattern[NOCM] != Target[i] )
            NOCM = PrefixFunc[NOCM];
        if( Pattern[NOCM] == Target[i] )
            NOCM++;
        if( NOCM == PatLen )
        {
            find_pos = i - PatLen + 1;
            break;
            //printf("KMP String Matching,pattern occurs with shift %d\n",i - PatLen + 1);
            NOCM = PrefixFunc[NOCM];
        }
    }
    delete[] PrefixFunc;
    return find_pos;
}

#endif // ELEMMATCH_H
