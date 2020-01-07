#include "DataAccessorF.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
void rewindImage_f(uint64_t * ptDataAccessor)
{
	((DataAccessor * ) (* ptDataAccessor))->rewindImage();
}
*/

void setLineSequential_f(uint64_t * ptDataAccessor,  char * dataLine) 
{
    ((DataAccessor * ) (* ptDataAccessor))->setLineSequential(dataLine);
}
void setLineSequentialBand_f(uint64_t * ptDataAccessor, char * dataLine, int * band)
{
    (*band) -=1;
    ((DataAccessor * ) (* ptDataAccessor))->setLineSequentialBand(dataLine, (*band));
    (*band) +=1;
}
void getLineSequential_f(uint64_t * ptDataAccessor,  char * dataLine, int * ptFlag) 
{
    (*ptFlag) =  ((DataAccessor * ) (* ptDataAccessor))->getLineSequential(dataLine);
}
void getLineSequentialBand_f(uint64_t * ptDataAccessor, char * dataLine, int *band, int *ptFlag)
{
    (*band) -=1;
    int flag = ((DataAccessor * ) (* ptDataAccessor))->getLineSequentialBand(dataLine, (*band));
    (*band) +=1;
    (*ptFlag) = flag;
}
void setLine_f(uint64_t * ptDataAccessor,  char * dataLine, int * ptLine) 
{
    // fortran is one based
    (*ptLine) -= 1;
    ((DataAccessor * ) (* ptDataAccessor))->setLine(dataLine, (*ptLine));
    (*ptLine) += 1;
}
void setLineBand_f(uint64_t * ptDataAccessor, char * dataLine, int * ptLine, int * band)
{
    (*ptLine) -= 1;
    (*band) -= 1;
    ((DataAccessor * ) (* ptDataAccessor))->setLineBand(dataLine, (*ptLine), (*band));
    (*ptLine) += 1;
    (*band) +=1;
}
void getLine_f(uint64_t * ptDataAccessor,  char * dataLine, int * ptLine) 
{
    // fortran is one based
    (*ptLine) -= 1;
    int flag = ((DataAccessor * ) (* ptDataAccessor))->getLine(dataLine, (*ptLine));
    if(flag < 0)
    {
        (*ptLine) = flag;
    }
    else
    {
        (*ptLine) += 1;
    }
}
void getLineBand_f(uint64_t * ptDataAccessor, char * dataLine, int *band, int *ptLine)
{
    int ptLine1, band1;
    ptLine1 = (*ptLine) - 1;
    band1 = (*band) - 1;
    int flag = ((DataAccessor * ) (* ptDataAccessor))->getLineBand(dataLine, ptLine1, band1);
    if (flag<0)
    {
        (*ptLine) = flag;
    }
//    else
//    {
//        (*ptLine) +=1;
//    }
}

void setSequentialElements_f(uint64_t * ptDataAccessor,  char * dataLine, int * ptRow, int * ptCol, int * ptNumEl) 
{
    // fortran is one based
    (*ptRow) -= 1;
    (*ptCol) -= 1;
    ((DataAccessor * ) (* ptDataAccessor))->setSequentialElements(dataLine, (*ptRow),(*ptCol),(*ptNumEl));
    (*ptRow) += 1;
    (*ptCol) += 1;
}
void getSequentialElements_f(uint64_t * ptDataAccessor,  char * dataLine, int * ptRow, int * ptCol, int * ptNumEl) 
{
    // fortran is one based
    (*ptRow) -= 1;
    (*ptCol) -= 1;
    ((DataAccessor * ) (* ptDataAccessor))->getSequentialElements(dataLine, (*ptRow),(*ptCol),(*ptNumEl));
    (*ptRow) += 1;
    (*ptCol) += 1;
}
void setStream_f(uint64_t * ptDataAccessor,  char * dataLine, int * numEl)
{
	((DataAccessor * ) (* ptDataAccessor))->setStream(dataLine, (*numEl));
}
void getStream_f(uint64_t * ptDataAccessor,  char * dataLine, int * numEl)
{
	((DataAccessor * ) (* ptDataAccessor))->getStream(dataLine, (*numEl));
}
void setStreamAtPos_f(uint64_t * ptDataAccessor,  char * dataLine, int * pos, int * numEl)
{
    // fortran is one based
    (*pos) -= 1;
	((DataAccessor * ) (* ptDataAccessor))->setStreamAtPos(dataLine, (*pos), (*numEl));
    (*pos) += 1;
}
void getStreamAtPos_f(uint64_t * ptDataAccessor,  char * dataLine, int * pos, int * numEl)
{
    // fortran is one based
    (*pos) -= 1;
	((DataAccessor * ) (* ptDataAccessor))->getStreamAtPos(dataLine, (*pos), (*numEl));
    (*pos) += 1;
}
void initSequentialAccessor_f(uint64_t * ptDataAccessor, int * begLine)
{
    // fortran is one based
    (*begLine) -= 1;
    ((DataAccessor * ) (* ptDataAccessor))->initSequentialAccessor((*begLine));
    (*begLine) += 1;
}
