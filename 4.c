#include<highgui.h>
#include<cv.h>
//#include "corners.cpp"
using namespace cv;
using namespace std;
int counter=0;
Mat fin;
Mat mrecons;
vector<vector<Point> >hull1;
typedef struct ftr_pts
{
    Point pt;
    int node;
    int next;
    }ftr_pts;
    ftr_pts ftr_pts1[500];
    int ftr_pts_cntr=0;
    typedef struct node
    {
        Point pt;
        float next_slope;
        float prev_slope;
        node *next;
        node *prev;
        }node;
        typedef struct list
        {
            node *head;
            int count;
            }list;
            list *l;
            void eliminate_line(node *temp2)
            {
                l->count--;
                node *aux2=temp2->next;
                node *aux=temp2->prev;
                if (aux!=NULL && aux2!=NULL)
                {
                    aux->next=aux2;
                    aux2->prev=aux;
                }
                else if (aux==NULL && aux2!=NULL)
                {
                    aux2->prev=NULL;
                    l->head=aux2;
                }
                else if (aux!=NULL && aux2==NULL)
                {
                    aux->next=NULL;
                }
                free(temp2);
            }
            float slope(Point p1,Point p2)
            {
                float slp;
                if (p2.x!=p1.x)
                slp=(float)(p2.y-p1.y)/(p2.x-p1.x);
                else
                slp=1000;
                return slp;
            }
            int dist2(Point p1,Point p2)
            {
                int dist2=pow((p2.x-p1.x),2)+pow((p2.y-p1.y),2);
                return dist2;
            }
            int parallel_dist(Point p1,Point p2,Point p3,Point p4)
            {
                int result=dist2(p1,p3);
                if (result>dist2(p1,p4));
                result=dist2(p1,p4);
                return sqrt(result);
            }
            void create_new_list(Point point)
            {
                node *tnew=(node *)malloc(sizeof(node));
                l=(list *)malloc(sizeof(list));
                if (tnew!=NULL)
                {
                    tnew->pt=point;
                    tnew->next=NULL;
                    tnew->prev=NULL;
                    l->count=1;
                    l->head=tnew;
                    counter=1;
                }
            }
            void add_new_node(Point point)
            {
                node *tnew=(node *)malloc(sizeof(node));
                if (tnew!=NULL)
                {
                    tnew->pt=point;
                    tnew->next=l->head;
                    //tnew->next_slope=slope(tnew->next->pt,tnew->pt);
                    l->head->prev=tnew;
                    //(tnew->next)->prev_slope=tnew->next_slope;
                    tnew->prev=NULL;
                    l->head=tnew;
                    l->count++;
                }
            }
            void sloper()
            {
                node *temp=l->head;
                temp->next_slope=slope(temp->pt,temp->next->pt);
                temp=temp->next;
                while(temp->next!=NULL)
                {
                    temp->prev_slope=slope(temp->prev->pt,temp->pt);
                    temp->next_slope=slope(temp->pt,temp->next->pt);
                    temp=temp->next;
                }
                temp->prev_slope=slope(temp->prev->pt,temp->pt);
            }
            int printer_counter=0;
            Mat gubu;
            void print_node(node *n) 
            {
                printer_counter++;
                printf("%d ",printer_counter);
                printf("Node - ");
                printf("(%d,%d) \n",n->pt.x,n->pt.y);
                printf("Prev slope %f\n",n->prev_slope);
                printf("Next slope %f\n",n->next_slope);
                printf("\n");
                circle(gubu,n->pt,1,Scalar(255,255,255),-1);
                if (n->prev!=NULL)
                line(gubu,n->pt,n->prev->pt,Scalar(0,255,0),1);
                cvWaitKey(1);
                imshow("gubu",gubu);
                cvWaitKey(1);
                } 
                void print_list() 
                {
                    node *temp=l->head;
                    //cvZero(fin);
                    while (temp!=NULL)
                    {
                        print_node(temp);
                        temp=temp->next;
                    }
                }
                void remover(node *temp)
                {
                    if (temp==NULL);
                    else if (temp->next==NULL)
                    free(temp);
                    else 
                    {
                        remover(temp->next);
                        free(temp);
                    }
                }
                void give_items(Point point)
                {
                    //printf("here2-%c %d %d %d %d\n",himg,start.x,start.y,end.x,end.y);
                    int flag=0;
                    if (counter==0)
                    {
                        create_new_list(point);
                    }
                    else
                    {
                        add_new_node(point);
                    }
                }
                int threshholder(IplImage *img)
                {
                    long int sum=0;
                    int avg;
                    for (int y=0;y<img->height;y++)
                    {
                        uchar *ptr=(uchar *)(img->imageData + y*img->widthStep);
                        for (int x=0;x<img->width;x++)
                        sum+=ptr[x];
                    }
                    avg=sum/(img->height*img->width);
                    return avg;
                }
                int check_ftr_pts1(Point val)
                {
                    int thresh_func=20;
                    for (int i=0;i<ftr_pts_cntr-1;i++)
                    {
                        if(dist2(ftr_pts1[i].pt,val)<=thresh_func)
                        return 1;
                    }
                }
                void join(int max_in1)
                {
                    ftr_pts_cntr=0;
                    printf("here2\n");
                    int join_eps=50;
                    for (int i=0;i<hull1[max_in1].size()-1;i++)
                    {
                        int j=i+1;
                        if (dist2(hull1[max_in1][i],hull1[max_in1][j])<join_eps)
                        {
                            // printf("reached here3 %d\n",dist2(hull1[max_in1][i],hull1[max_in1][j]));
                            }  
                            else
                            {
                                ftr_pts1[ftr_pts_cntr].pt.x=hull1[max_in1][i].x;
                                ftr_pts1[ftr_pts_cntr].pt.y=hull1[max_in1][i].y;
                                if (ftr_pts_cntr!=0)
                                {
                                    ftr_pts1[ftr_pts_cntr-1].next=ftr_pts_cntr;
                                }
                                //    printf("reached here4 %d\n",dist2(hull1[max_in1][i],hull1[max_in1][j]));
                                ftr_pts1[ftr_pts_cntr].next=j;
                                ftr_pts_cntr++;
                            }
                        }
                        ftr_pts1[ftr_pts_cntr-1].next=0;
                        mrecons=Scalar(0,0,0);
                        for (int i=0;i<ftr_pts_cntr;i++)
                        {
                            line(mrecons,ftr_pts1[i].pt,ftr_pts1[ftr_pts1[i].next].pt,Scalar(255,255,0));
                            circle(mrecons,ftr_pts1[i].pt,5,Scalar(0,255,255),-1);
                            //    circle(fin,ftr_pts1[i].pt,20,Scalar(255,0,255),1);
                        }
                    }
                    void elm_rep()
                    {
                        int eps=5;
                        int i,ck=0;
                        node*var1;
                        node*var2;
                        node*temp,*temp1;
                        int ctr=0;
                        for(temp=l->head;temp!=NULL;temp=temp->next)
                        {
                            for(temp1=l->head;temp1!=NULL ;temp1=temp1->next)
                            {
                                if(temp1!=temp)
                                {
                                    ctr++;
                                    if(ck==1)
                                    {
                                        if(temp1->prev==l->head)
                                        {
                                            l->head=temp1;
                                            l->head->prev=NULL;
                                            free(temp1->prev);
                                        }
                                        else
                                        {
                                            temp1->prev=NULL;
                                            free(temp1->prev);
                                        }
                                    }
                                    ck=0;
                                    if(dist2(temp1->pt,temp->pt)<eps)
                                    {
                                        var1=temp1->prev;
                                        var2=temp1->next;
                                        if(var1==NULL)
                                        {
                                            //var2->prev=NULL;
                                            ck=1;
                                        }
                                        else if(var2==NULL)
                                        {
                                            var1->next=NULL;
                                        }
                                        else if(var1==NULL && var2==NULL)
                                        {
                                            ck=1;
                                        }
                                        else
                                        {
                                            var1->next=var2;
                                            var2->prev=var1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    void elm_sl()
                    {
                        float eps=1;
                        int i,ck=0;
                        node*var1;
                        node*var2;
                        node*temp,*temp1;
                        int ctr=0;
                        for(temp1=l->head;temp1!=NULL ;temp1=temp1->next)
                        {
                            if(temp1!=temp)
                            {
                                ctr++;
                                if(ck==1)
                                {
                                    if(temp1->prev==l->head)
                                    {
                                        l->head=temp1;
                                        l->head->prev=NULL;
                                        free(temp1->prev);
                                    }
                                    else
                                    {
                                        temp1->prev=NULL;
                                        free(temp1->prev);
                                    }
                                }
                                ck=0;
                                if(abs(temp1->prev_slope-temp1->next_slope)<eps || abs(1/temp1->prev_slope-1/temp1->next_slope)<1/eps)
                                {
                                    var1=temp1->prev;
                                    var2=temp1->next;
                                    if(var1==NULL)
                                    {
                                        //var2->prev=NULL;
                                        ck=1;
                                    }
                                    else if(var2==NULL)
                                    {
                                        var1->next=NULL;
                                    }
                                    else if(var1==NULL && var2==NULL)
                                    {
                                        ck=1;
                                    }
                                    else
                                    {
                                        var1->next=var2;
                                        var2->prev=var1;
                                    }
                                }
                            }
                        }
                    }
                    void split(Mat source)
                    {
                        int hull_counter=0;
                        int max_in=-1;
                        float max_ar=0;
                        vector<vector<Point> > contours;
                        vector<Vec4i> hierarchy;
                        Mat src_gray;
                        cvtColor( source, src_gray, CV_BGR2GRAY );   
                        Mat threshold_output;
                        threshold( src_gray, threshold_output, 10, 255, THRESH_BINARY );
                        Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
                        gubu = Mat::zeros( threshold_output.size(), CV_8UC3 );
                        imshow("gencup",threshold_output);
                        cvWaitKey(0);
                        findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
                        for( int i = 0; i< contours.size(); i++ )
                        {
                            drawContours( threshold_output, contours, i, Scalar(0,0,255), 1, 8, vector<Vec4i>(), 0, Point() );
                            for( int j = 0; j< contours[i].size(); j++ )
                            {
                                circle(threshold_output,contours[i][j],1,Scalar(255,255,255),-1);
                                imshow( "Contour_demo", threshold_output);
                                cvWaitKey(1);
                                give_items(contours[i][j]);
                            }
                        }
                        elm_rep();
                        sloper(); 
                        elm_sl();
                    }
                    void hull(Mat src)
                    {
                        cvWaitKey(0);
                        Mat src_gray;
                        int thresh = 0;
                        int hull_counter=0;
                        int max_thresh = 255;
                        float max_ar=0;
                        int max_in=-1;
                        RNG rng(12345);
                        Mat src_copy = src.clone();
                        src_gray=src.clone();
                        Mat moment_drawing;
                        cvtColor( src, moment_drawing, CV_GRAY2BGR );
                        // blur( src_gray, src_gray, Size(3,3) );
                        imshow("src_gray",src_gray);
                        imshow("src",src);
                        cvWaitKey(0);
                        Mat threshold_output;
                        vector<vector<Point> > contours;
                        vector<Vec4i> hierarchy;
                        /// Detect edges using Threshold
                        IplImage img=src_gray;
                        thresh=255-threshholder(&img);
                        threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );
                        /// Find contours 
                        findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
                        vector<Moments> mu(contours.size() );
                        for( int i = 0; i < contours.size(); i++ )
                        { mu[i] = moments( contours[i], false ); }
                        ///  Get the mass centers:
                        vector<Point2f> mc( contours.size() );
                        /// Find the convex hull object for each contour
                        vector<vector<Point> >hull( contours.size() );
                        for( int i = 0; i < contours.size(); i++ )
                        {  
                        convexHull( Mat(contours[i]), hull[i], false );
                    }
                    /// Draw contours + hull results
                    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
                    int xsum=0,ysum=0,maxdist=0;
                    for( int i = 0; i < contours.size(); i++ )
                    {
                        mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); 
                        xsum+=mc[i].x;
                        ysum+=mc[i].y;
                        circle(moment_drawing,mc[i],5,Scalar(0,0,255),-1);
                    }
                    Point cen=Point(xsum/contours.size(),ysum/contours.size());
                    circle(moment_drawing,cen,5,Scalar(0,255,255),-1);
                    imshow("moments",moment_drawing);
                    cvWaitKey(0);
                    Mat drawing1= Mat::zeros( threshold_output.size(), CV_8UC3 );
                    for( int i = 0; i< contours.size(); i++ )
                    {
                        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                        if (contourArea(Mat(hull[i]))>=max_ar)
                        {
                            if (hull_counter==0)
                            {
                                hull_counter++;
                                continue;
                            }
                            max_in=i;
                            max_ar=contourArea(Mat(hull[i]));
                            hull_counter++;
                        }
                        drawContours( fin, contours, i, Scalar(0,0,255), 1, 8, vector<Vec4i>(), 0, Point() );
                        //imshow( "Contour demo", drawing1 );
                        //cvWaitKey(0);
                        //        drawContours( drawing, hull, i, Scalar(255,0,0), 1, 8, vector<Vec4i>(), 0, Point() );
                        //printf("%d hi-%f\n",i,contourArea(Mat(hull[i])));
                    }
                    //printf("hello-%f %d\n",max_ar,threshold_output.rows*threshold_output.cols-2*(threshold_output.cols+threshold_output.rows));
                    drawContours( drawing, hull, max_in, Scalar(255,0,255), 1, 8, vector<Vec4i>(), 0, Point() );
                    drawContours( moment_drawing, hull, max_in, Scalar(255,0,255), 1, 8, vector<Vec4i>(), 0, Point() );
                    imshow( "Contour demo", drawing);
                    imshow("moments",moment_drawing);
                    cvWaitKey(0);
                    hull1=hull;
                    join(max_in);
                    split(fin);
                    print_list();
                    /// Show in a window
                    namedWindow( "Hull demo", CV_WINDOW_AUTOSIZE );
                    imshow( "Hull demo", drawing );
                }
                int main(int argc, char** argv)
                {
                    int x1,y1,x2,y2;
                    int ref=100;
                    int thresh_value=0;
                    int size_lines;
                    Mat img=imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
                    Mat hull_mat=imread(argv[1]);
                    if (img.cols>640 || img.rows>480)
                    {
                        resize(img,img,Size(),0.2,0.2);
                        resize(hull_mat,hull_mat,Size(),0.2,0.2);
                    }
                    if (img.cols<150 || img.rows<150)
                    {
                        resize(img,img,Size(),3,3);
                        resize(hull_mat,hull_mat,Size(),3,3);
                    }
                    fin=cvCreateImage(img.size(),IPL_DEPTH_8U,3);
                    fin=Scalar(0,0,0);
                    mrecons=cvCreateMat(img.rows,img.cols,CV_8UC3);
                    mrecons=Scalar(0,0,0);
l
                    Mat src;
                    src=img;
                    Mat dst, cdst,gray,cgray;
                    Canny(src, dst, thresh_value, 255, 3);
                    imshow("Cannied image",dst);
                    gray=src;
                    cvtColor(dst, cdst, CV_GRAY2BGR);
                    cvtColor(gray, cgray, CV_GRAY2BGR);
                    vector<Vec4i> lines;
                    vector<Vec3f> circles;
                    hull(dst);
                    cvWaitKey(0);
                    imshow("mrecons", mrecons);
                    imshow("fin", fin);
                    cvWaitKey(0);
                    return 0;
                }
