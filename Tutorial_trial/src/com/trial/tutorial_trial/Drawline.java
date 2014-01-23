package com.trial.tutorial_trial;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.Typeface;
import android.util.Log;
import android.view.View;



public class Drawline extends View{
	
	//Rect[]r;
	int[][]coor = new int[10][4];
	int flag;
	public Drawline(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
	}
	
	public void branch(Canvas canvas,int num,int thresh,int heig)
	{
		int w=canvas.getWidth();
		int h=canvas.getHeight();
		Paint blue = new Paint();
		blue.setColor(Color.BLUE);
		blue.setStyle(Paint.Style.FILL);
		
		
		Paint red=new Paint();
		red.setColor(Color.RED);
		red.setStyle(Paint.Style.STROKE);
		int com=w-2*thresh;
		int bw=25;//Button width
		int bh=15;//Button height
		
		for(int i=1;i<=num;i++)
		{
			Rect r1 = new Rect();
			r1.set( thresh+(com*i)/(num+1)-bw,heig-bh,thresh+(com*i)/(num+1)+bw,heig+bh);
			coor[i][0]=thresh+(com*i)/(num+1)-bw;
			coor[i][1]=heig-bh;
			coor[i][2]=thresh+(com*i)/(num+1)+bw;
			coor[i][3]=heig+bh;
			
			if(i==1)
				canvas.drawLine(thresh,heig,thresh+(com*i)/(num+1)-bw,heig,blue);
			else 
				canvas.drawLine(thresh+(com*(i-1))/(num+1)+bw,heig,thresh+(com*i)/(num+1)-bw,heig,blue);
			canvas.drawRect(r1,red);
			
		}
		canvas.drawLine(thresh+(com*num)/(num+1)+bw,heig,w-thresh,heig,blue);
		
					
	}
	
	
	public void message(Canvas canvas,int thresh)
	{
		int h=canvas.getHeight();
		int w=canvas.getWidth();
		int bw=55;//Button width
		int bh=15;//Button height
		int l=(w-2*thresh);
		
		
		Paint black=new Paint();
		black.setColor(Color.BLACK);
		black.setStyle(Paint.Style.STROKE);
		
		
		Rect r1=new Rect();
		Rect r2=new Rect();
		Rect r3=new Rect();
		
		r1.set(thresh-bw,(3*h)/4-bh,thresh+bw,(3*h)/4+bh);
		r2.set(thresh-bw+(l/2),(3*h)/4-bh,thresh+bw+(l/2),(3*h)/4+bh);
		r3.set(thresh-bw+l,(3*h)/4-bh,thresh+bw+l,(3*h)/4+bh);
		
	
		canvas.drawRect(r1, black);
		canvas.drawRect(r2, black);
		canvas.drawRect(r3, black);
				
		//canvas.drawColor(Color.GREEN);

	      String t1 = "Series";
	      String t2 = "Parallel";
	      String t3 = "Add Element";
	      
	      Paint mPaint = new Paint();
	      mPaint.setAntiAlias(true);
	      mPaint.setTextSize(bh);
	      mPaint.setTypeface(Typeface.create(Typeface.SERIF,
	          Typeface.ITALIC));

	      
	      float t1w = mPaint.measureText(t1);
	      float t2w = mPaint.measureText(t2);
	      float t3w = mPaint.measureText(t3);
	      	      
	      float start1 = (thresh-t1w/2);
	      float start2 = (thresh-t2w/2 + l/2);
	      float start3 = (thresh-t3w/2 + l);
	      
	      
	      mPaint.setTextAlign(Paint.Align.LEFT);
	      //canvas.translate(0, 80);
	      canvas.translate(0,(3*h)/4+(bh/2));
	      mPaint.setColor(Color.BLUE);
	      canvas.drawText(t1, start1, 0, mPaint);
	      canvas.drawText(t2, start2, 0, mPaint);
	      canvas.drawText(t3, start3, 0, mPaint);
	      
	     // mPaint.setColor(Color.RED);
	      //canvas.drawText(redText, startPositionX + blackTextWidth, 0,mPaint);
	      
	      
	}
	
	@Override
	protected void onDraw(Canvas canvas) {
		// TODO Auto-generated method stub
		super.onDraw(canvas);
		
		int w=canvas.getWidth();
		int h=canvas.getHeight();
				
		branch(canvas,4,w/6,h/6);
		if(flag==1)
			message(canvas,(w/6));
				
	}

	
	
	
}


