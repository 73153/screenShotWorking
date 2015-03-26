package com.fallingscalemedia.Noah360;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;
import android.widget.Toast;

/**
 * Class to check Internet Connection in Java
 * 
 * See you I call it from C++ using InterfaceJNI
 * 
 * 
 * @author piperoman 2013
 *
 */
public class InternetConnection 
{
	/**
	 * Check if is working your hello world from C++
	 */
	public static void helloWorld()
	{
		Log.v("InternetConnection", "HELLO WORLD");
	}
	/**
	 * Check Internet Connection
	 * @return true is Online
	 */
	public static boolean isInternetConnection(Context myContext)
	{
		Log.v("InternetConnection", "isInternetConnection Start");
		
		Toast toast1 =
	            Toast.makeText(myContext,
	                    "Checking Internet", Toast.LENGTH_SHORT);
	        toast1.show();
		
		ConnectivityManager conMgr =  (ConnectivityManager)myContext.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo i = conMgr.getActiveNetworkInfo();
		
		if (i == null)
		{
			Log.v("InternetConnection", "isInternetConnection NULL :S");
			return false;
		}
			
		if (!i.isConnected())
		{
			Log.v("InternetConnection", "isInternetConnection is not connected");
			return false;
		}
			
		if (!i.isAvailable())
		{
			Log.v("InternetConnection", "isInternetConnection is not available");
			return false;
		}
		Log.v("InternetConnection", "isInternetConnection DONE!");
		
		return true;
	}
}
