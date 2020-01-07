#ifndef BSQAccessor_h
#define BSQAccessor_h

#ifndef MESSAGE
#define MESSAGE cout << "file " << __FILE__ << " line " << __LINE__ << endl;
#endif
#ifndef ERR_MESSAGE
#define ERR_MESSAGE cout << "Error in file " << __FILE__ << " at line " << __LINE__  << " Exiting" <<  endl; exit(1);
#endif

#include <iostream>
#include "InterleavedAccessor.h"
#include <stdint.h>
using namespace std;

class BSQAccessor: public InterleavedAccessor
{
    public:
        BSQAccessor(){}
        virtual ~BSQAccessor(){}
        void getData(char * buf,int row, int col, int & numEl);
        void getDataBand(char * buf,int row, int col, int & numEl, int band);
        void setData(char * buf,int row, int col, int numEl);
        void setDataBand(char * buf, int row, int col, int numEl, int band);
    protected:
};

#endif //BSQAccessor_h
