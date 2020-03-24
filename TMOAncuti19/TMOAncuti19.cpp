/* --------------------------------------------------------------------------- *
 * TMOAncuti19.cpp: implementation of the TMOAncuti19 class.   *
 * VYF - term project
 * Author : Matej Bobuľa 
 * --------------------------------------------------------------------------- */

#include "TMOAncuti19.h"
#include <math.h>
#include <boost/concept_check.hpp>
#include <complex>

#define DEBUG 1


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

void TMOAncuti19::SaveData(double * dstData, cv::Mat &red, cv::Mat &green, cv::Mat &blue)
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


cv::Mat TMOAncuti19::LocalEntropy()
{
 
}


//returns matrix of size 5x5 from source o
cv::Mat TMOAncuti19::getLocalPatchFromSource(int patchSize, cv::Mat &src, int pos_x, int pos_y)
{
	
	cv::Mat localPatch = cv::Mat::zeros(patchSize, patchSize, CV_64FC1);

	int halfPatch =  floor(patchSize)/2;
	int patchRowCeneter = floor(patchSize)/2;
	int patchColCeneter = floor(patchSize)/2;


for (int row = -patchRowCeneter; row <= patchRowCeneter; row++) //idem po riadkoch, y-axis
	for (int col = -patchColCeneter; col <= patchColCeneter; col++) // prechadzam stlpce, cize po x-ovej suradnici
	{
		int pos_x_in_src = (pos_x + col);// - patchColCeneter;
		int pos_y_in_src = (pos_y + row);// - patchRowCeneter;

		int pos_x_in_patch = col + patchColCeneter;
		int pos_y_in_patch = row + patchRowCeneter;

		if (DEBUG) std::cerr << pos_x_in_patch << " " << pos_y_in_patch << " = " <<  pos_x_in_src << " " << pos_y_in_src <<"\n";
		
		localPatch.at<double>(pos_y_in_patch ,pos_x_in_patch) = src.at<double>(pos_y_in_src, pos_x_in_src);
	}

	if (DEBUG) std::cerr << "\nlocalPatch = \n" << localPatch << "\n\n";

	return localPatch;
}


int TMOAncuti19::Transform()
{


	double * srcData = pSrc->GetData();
	double * dstData = pDst->GetData();



	int width = pSrc->GetWidth();
	int height = pSrc->GetHeight();
	int patchSize = 5;


	cv::Mat red = cv::Mat::zeros(height, width, CV_64FC1);
	cv::Mat green = cv::Mat::zeros (height, width, CV_64FC1);
	cv::Mat blue = cv::Mat::zeros (height, width, CV_64FC1);
	
	//separate color channels
	for (int j = 0; j < height; j++)
	{
		pSrc->ProgressBar(j, height);	

		for (int i = 0; i < width; i++)
		{
			red.at<double>(j,i) = *srcData++; 
			green.at<double>(j,i) = *srcData++;
			blue.at<double>(j,i) = *srcData++;

		}
	}

	


	// local maps
	//cv::Mat redLocalMap = cv::Mat::zeros(height, width, CV_64FC1);
	cv::Mat localPatch = cv::Mat::zeros(patchSize, patchSize, CV_64FC1);


/*
	double entropy_ij
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			{
				localPatch.at<double>(0,0)
				localPatch.at<double>(1,0)
				localPatch.at<double>(2,0) 

				red.at<double>(j,i) = *srcData++; 

			}
*/


	localPatch = getLocalPatchFromSource(patchSize, green, 5, 5);








	if (DEBUG) std::cerr << "Saving...\n";
	//SaveData(dstData, red, green, blue);
	//SaveData(dstData, red, red, red);
	SaveData(dstData, green, green, green);
	//SaveData(dstData, blue, blue, blue);
	if (DEBUG) std::cerr << "Save Completed !\n";

	return 0;
}


