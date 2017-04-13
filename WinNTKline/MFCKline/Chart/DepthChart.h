﻿#ifndef CHART_DEPTH_H_
#define CHART_DEPTH_H_

#include "MGL/OGLKview.h"

class DepthChart
{
private:
	void fillItem();
	void fillList(void);
	void fillAskBid(OGLKview::Point pt);
private:
	float Py, Pm;
	int hour = 0;
	int column = 0;
	int MAX_COL = 17;
	OGLKview Okv;
	OGLKview::Color4f color = { 1,1,1,1 };
public:
	DepthChart();
	void DrawItem(OGLKview::Item item, int col);
	int DrawItem(OGLKview::Item item, bool mode = false);
	void FillChart(bool unfurl);
	void DelItem(int item);
	DepthChart* getDepth();
	virtual ~DepthChart();
public:
	OGLKview::Item item;
};
#endif // !CHART_DEPTH_H_