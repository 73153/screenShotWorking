/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package com.fallingscalemedia.Noah360;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;

public class Noah extends Cocos2dxActivity {
	private static final String TAG = "CCSocialNetwork";
	static Context myAndroidContext;
	public static Noah selfActivity = null;
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		myAndroidContext = getApplicationContext();
		selfActivity=this;
	}
	public static void playVideo(final String msg) {
		
    System.out.println("Play Video");
    
    Intent i = new Intent();
      i.setClass(selfActivity, Cocos2dxVideo.class);

      selfActivity.startActivity(i);
    
}
	// ////////////////////////////////////////////////////////////
	// Interface //
	// ////////////////////////////////////////////////////////////
	static public boolean isInternetConnection() {
		Log.v("InternetConnection", "isInternetConnection Start");
		/*
		 * // Toast make fail DEMO ! :S Toast toast1 =
		 * Toast.makeText(myAndroidContext, "Checking Internet",
		 * Toast.LENGTH_SHORT); toast1.show();
		 */
		ConnectivityManager conMgr = (ConnectivityManager) myAndroidContext
				.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo i = conMgr.getActiveNetworkInfo();

		if (i == null) {
			Log.v("InternetConnection", "isInternetConnection NULL :S");
			return false;
		}

		if (!i.isConnected()) {
			Log.v("InternetConnection", "isInternetConnection is not connected");
			return false;
		}

		if (!i.isAvailable()) {
			Log.v("InternetConnection", "isInternetConnection is not available");
			return false;
		}
		Log.v("InternetConnection", "isInternetConnection DONE!");

		return true;
	}

	private static void sendATweet() {
		Log.d(
				"activity",
				"Tweet on Java EDITABLE (Bad way, better use a library; Current version use web navigator)");
		String score = "123";
		String tweetUrl = "https://twitter.com/intent/tweet?text=Hello ! I have just got "
				+ score + " points in mygame for Android !!!!";
		Uri uri = Uri.parse(tweetUrl);
		Intent i = new Intent(Intent.ACTION_VIEW, uri);
		i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		myAndroidContext.startActivity(i);
	}

	private static void sendEMail() {
		Log.d("activity", "Send a email on Java");
		Intent i = new Intent(Intent.ACTION_SEND);
		// i.setType("text/plain"); //use this line for testing in the emulator
		i.setType("message/rfc822"); // use from lisve device
		i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		i.putExtra(Intent.EXTRA_EMAIL,
				new String[] { "mrpiperoman@hotmail.com"/* "test@gmail.com" */});
		i.putExtra(Intent.EXTRA_SUBJECT, "Subject goes here");
		i.putExtra(Intent.EXTRA_TEXT, "Test body goes here");
		myAndroidContext.startActivity(i);
	}

	public Cocos2dxGLSurfaceView onCreateView() {
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		// Learnnumber should create stencil buffer
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

		return glSurfaceView;
	}

	static {
		System.loadLibrary("cocos2dcpp");
	}
}
