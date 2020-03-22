#include "TMO.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


class TMOAncuti19: public TMO  
{
public:
	TMOAncuti19();
	virtual ~TMOAncuti19();
	virtual int Transform();
	void SaveData(double * dstData, cv::Mat red, cv::Mat green, cv::Mat blue);
	

protected:
	TMODouble dParameter;
};
