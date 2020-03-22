/* --------------------------------------------------------------------------- *
 * TMOAncuti19.cpp: implementation of the TMOAncuti19 class.   *
 * VYF - term project
 * Author : Matej Bobuľa 
 * --------------------------------------------------------------------------- */

#include "TMOAncuti19.h"
#include <boost/concept_check.hpp>
#include <complex>



/* --------------------------------------------------------------------------- *
 * Constructor serves for describing a technique and input parameters          *
 * --------------------------------------------------------------------------- */
TMOAncuti19::TMOAncuti19()
{
	SetName(L"Ancuti19");						
    SetDescription(L"Image Decolorization based on Information Theory");
}

TMOAncuti19::~TMOAncuti19()
{
}


int TMOAncuti19::Transform()
{
	return 0;
}


