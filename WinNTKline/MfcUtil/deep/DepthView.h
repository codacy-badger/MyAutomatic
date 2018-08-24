#ifndef VIEW_DEPTH_H_
#define VIEW_DEPTH_H_

#include "MYGL/OGLKview.h"

class DepthView
{
private:
    float Py, Pm;
    int hour = 0;
    int column = 0;
    int MAX_COL = 17;
    OGLKview Okv;
    OGLKview::Color4f color = { 1,1,1,1 };
private:
    void fillItem();
    void fillList();
    void fillAskBid(OGLKview::Point pnt);
public:
    OGLKview::Item item;
public:
    DepthView();
    void FillChart(bool unfurl);
    void SetBackground();
    void DrawItem(OGLKview::Item item, int col);
    int DrawItem(OGLKview::Item item, bool mode = false);
    int DelItem(int item);
    DepthView* getDepth();
    virtual ~DepthView();
};
#endif // !VIEW_DEPTH_H_
