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



void TMOAncuti19::SaveData(double * dstData, cv::Mat red, cv::Mat green, cv::Mat blue)
{
	for (int j = 0; j < pSrc->GetHeight(); j++)
	{
	    pSrc->ProgressBar(j, pSrc->GetHeight());
		
	    for (int i = 0; i < pSrc->GetWidth(); i++) ///result to output, taking only the image correction is discarded
	    {
		  *dstData++ = red.at<double>(j,i);
		  *dstData++ = green.at<double>(j,i);
		  *dstData++ = blue.at<double>(j,i);
	    }
	}
}

int TMOAncuti19::Transform()
{


	double * srcData = pSrc->GetData();
	double * dstData = pDst->GetData();

	int width = pSrc->GetWidth();
	int height = pSrc->GetHeight();


	cv::Mat red = cv::Mat::zeros(height, width, CV_64FC1);
	cv::Mat green = cv::Mat::zeros (height, width, CV_64FC1);
	cv::Mat blue = cv::Mat::zeros (height, width, CV_64FC1);
	
	
	//separate color channels
	for (int j = 0; j < pSrc->GetHeight(); j++)
	{
		pSrc->ProgressBar(j, pSrc->GetHeight());	
			for (int i = 0; i < pSrc->GetWidth(); i++)
		{
			red.at<double>(j,i) = *srcData++; 
			green.at<double>(j,i) = *srcData++;
			blue.at<double>(j,i) = *srcData++;

		}
	}

	SaveData(dstData, red, green, blue);
	//SaveData(dstData, red, red, red);
	//SaveData(dstData, green, green, green);
	//SaveData(dstData, blue, blue, blue);

	return 0;
}


