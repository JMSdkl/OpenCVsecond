#pragma once

#include <opencv2/opencv.hpp>;
using namespace cv;

class QuickDemo
{
public:
	void colorSpace_Demo(Mat &image);
	void video_Demo(Mat&image);
	void mat_creation_demo(Mat&image);
	void pixel_visit_demo(Mat&image);
	void operators_demo(Mat&image);
	void tracking_bar_demo(Mat&image);
	void bitwrite_demo(Mat&image);
	void color_style_demo(Mat&image);
	void channels_demo(Mat&image);
	void inrange_demo(Mat&image);
	void pixel_statistic_demo(Mat&image);
	void drawing_demo(Mat&image);
	void random_drawing();
	void polyline_drawing_demo();
	void mouse_drawing_demo(Mat&image);
	void resize_demo(Mat&image);
	void normalize_demo(Mat&image);
	void flip_demo(Mat&image);
	void rotate_demo(Mat&image);
	void showHistogram_demo(Mat&image);
	void Histogram_2d_demo(Mat&image);
	void histogram_eq_demo(Mat&image);
	void blur_demo(Mat&image);
	void gaussin_blur_demo(Mat&image);
	void bifilter_demo(Mat&image);
	void corrosion_expand(Mat&image);
};