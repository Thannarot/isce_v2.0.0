//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// copyright: 2010 to the present, california institute of technology.
// all rights reserved. united states government sponsorship acknowledged.
// any commercial use must be negotiated with the office of technology transfer
// at the california institute of technology.
// 
// this software may be subject to u.s. export control laws. by accepting this
// software, the user agrees to comply with all applicable u.s. export laws and
// regulations. user has the responsibility to obtain export licenses,  or other
// export authority as may be required before exporting such information to
// foreign countries or providing access to foreign persons.
// 
// installation and use of this software is restricted by a license agreement
// between the licensee and the california institute of technology. it is the
// user's responsibility to abide by the terms of the license agreement.
//
// Author: Giangi Sacco
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



#include "FilterFactory.h"
#include "MagnitudeExtractor.h"
#include "PhaseExtractor.h"
#include "RealExtractor.h"
#include "ImagExtractor.h"
#include "ComponentExtractor.h"
#include "BandExtractor.h"
using namespace std;

Filter * FilterFactory::createFilter(string type,int selector)
{
        Filter * filter;
        if(type == "MagnitudeExtractor")
        {
            //Magnitude from cartesian
            filter = new MagnitudeExtractor;
        }
        else if(type == "ComponentExtractor")
        {
            //Magnitude from polar or Real from cartesian selector = 0
            //Phase from polar or Imag from cartesian selector = 1
            filter = new ComponentExtractor;
            filter->selectComponent(selector);
        }
        else if(type == "PhaseExtractor")
        {
            //Phase from cartesian
            filter = new PhaseExtractor;
        }
        else if(type == "RealExtractor")
        {
            //Real from Polar
            filter = new RealExtractor;
        }
        else if(type == "ImagExtractor")
        {
            //Imag from polar
            filter = new ImagExtractor;
        }
        else if(type == "BandExtractor")
        {
            //Extract Band = selector
            filter = new BandExtractor;
            filter->selectBand(selector);
        }
        else
        {
            cout << "Filter " << type << " not implemented." << endl;
            ERR_MESSAGE;
        }
        return filter;
}
