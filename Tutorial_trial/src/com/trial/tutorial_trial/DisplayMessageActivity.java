package com.trial.tutorial_trial;

import android.os.Bundle;

import android.app.Activity;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;
import android.support.v4.app.NavUtils;
import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.os.Build;


public class DisplayMessageActivity extends Activity {

	//int elem_flag;
	Drawline v;
	MotionEvent e;
	int ht;
	public boolean onTouchEvent(MotionEvent e) {
	    int num = e.getPointerCount();
	    
	    	    
	      int x = (int) e.getX(e.getPointerId(0));
	      int y = (int) e.getY(e.getPointerId(0));
	      for(int i=1;i<=4;i++)
	      {
	    	  Rect r=new Rect();
	    	  r.set(v.coor[i][0],v.coor[i][1]+ht,v.coor[i][2],v.coor[i][3]+ht);
	    	  if(r.contains(x,y))
	    	  {
	    		  Log.d("correct","correct");
	    		  v.flag=1;
	    		  setContentView(v);
	    	  }
	    	  
	      }
	      
	      if(v.flag==1)
	      {
	    	  
	      }
	      return false;
	  }
	@SuppressLint("NewApi")
	@Override
		
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//e=new MotionEvent();
		
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);

		//Remove notification bar
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		
		
		v = new Drawline(this);
		v.flag=0;
		setContentView(v);
		v.onTouchEvent(e);
		setupActionBar();
	}
		

	/**
	 * Set up the {@link android.app.ActionBar}, if the API is available.
	 */
	@TargetApi(Build.VERSION_CODES.HONEYCOMB)
	private void setupActionBar() {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
			getActionBar().setDisplayHomeAsUpEnabled(true);
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.display_message, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case android.R.id.home:
			// This ID represents the Home or Up button. In the case of this
			// activity, the Up button is shown. Use NavUtils to allow users
			// to navigate up one level in the application structure. For
			// more details, see the Navigation pattern on Android Design:
			//
			// http://developer.android.com/design/patterns/navigation.html#up-vs-back
			//
			NavUtils.navigateUpFromSameTask(this);
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

}
