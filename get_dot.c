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
            	int gubu_eps=100;
                printer_counter++;
                printf("%d ",printer_counter);
                printf("Node - ");
                printf("(%d,%d) \n",n->pt.x,n->pt.y);
                printf("Prev slope %f\n",n->prev_slope);
                printf("Next slope %f\n",n->next_slope);
                printf("\n");
                circle(gubu,n->pt,1,Scalar(255,255,255),-1);
                
                                imshow("gubu",gubu);
                                cvWaitKey(1);
                if (n->prev!=NULL&&(dist2(n->pt,n->prev->pt)<gubu_eps))
                line(gubu,n->pt,n->prev->pt,Scalar(0,255,0),1);
                
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
                    imwrite("1.jpg",gubu);
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
             
                    void elm_rep()
                    {
                        int eps=200;
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
             
                    void split(Mat source)
                    {
                    	Mat tester=source.clone();
                    	tester=Scalar(0);
                        int hull_counter=0;
                        int max_in=-1;
                        float max_ar=0;
                        vector<vector<Point> > contours;
                        vector<Vec4i> hierarchy;
                        Mat src_gray;
                        src_gray=source.clone();
//                        cvtColor( source, src_gray, CV_BGR2GRAY );   
                        Mat threshold_output;
                        threshold( src_gray, threshold_output, 10, 255, THRESH_BINARY );
                        Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
                        gubu = Mat::zeros( threshold_output.size(), CV_8UC3 );
                        imshow("gencup",threshold_output);
                        cvWaitKey(0);
                        findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
                        for( int i = 0; i< contours.size(); i++ )
                        {
                            drawContours( drawing, contours, i, Scalar(0,0,255), 1, 8, vector<Vec4i>(), 0, Point() );
                            for( int j = 0; j< contours[i].size(); j++ )
                            {
                                circle(tester,contours[i][j],1,Scalar(255,255,255),-1);
                                imshow( "tester", tester);
                                cvWaitKey(1);
                                give_items(contours[i][j]);
                            }

                        }
			elm_rep();
             
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
		    GaussianBlur(img,img,Size(3,3),0);                    
                    Mat src;
                    src=img;
                    Mat dst;
                    Canny(src, dst, thresh_value, 255, 3);
                    imshow("Cannied image",dst);
                    split(dst);
                    print_list();
                    cvWaitKey(0);
                    return 0;
                }
