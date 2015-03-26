
package com.MyCompany.AwesomeGame;
import org.cocos2dx.lib.Cocos2dxActivity;
import com.fallingscalemedia.Noah360.*;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.net.Uri;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.VideoView;

public class VideoSample extends Cocos2dxActivity {
    private static VideoSample smActivity = null;

    static {
        System.loadLibrary("game");
    }

    public static void displayVideo() {
        smActivity.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                smActivity.startVideo();
            }
        });
    }

    public static void removeVideo() {
        smActivity.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                smActivity.stopVideo();
            }
        });
    }

    private FrameLayout mGameView = null;
    private int mStopPosition = 0;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        smActivity = this;
    }

    @Override
    protected void onPause() {
        super.onPause();
        // stop video if it's playing
        if (mGameView != null) {
            VideoView vv = (VideoView) findViewById(R.id.videoPlayer);
            mStopPosition = vv.getCurrentPosition();
            vv.pause();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (mGameView != null) {
            VideoView vv = (VideoView) findViewById(R.id.videoPlayer);
            vv.seekTo(Math.max(0, mStopPosition - 3000));
            vv.start();
            mStopPosition = 0;
        }
    }

    private void startVideo() {
        View videoView = LayoutInflater.from(this)
                .inflate(R.layout.activity_cocos2dx_video, null);
        if (videoView != null) {
            FrameLayout view = (FrameLayout) findViewById(android.R.id.content);
            view.addView(videoView);
            mGameView = (FrameLayout) view.getChildAt(0);
            setContentView(videoView);

            Button skip = (Button) findViewById(R.id.videoPlayer);
            skip.setOnClickListener(new View.OnClickListener() {

                @Override
                public void onClick(View v) {
                    stopVideo();
                }
            });

            VideoView vv = (VideoView) findViewById(R.id.videoPlayer);
            vv.setVideoURI(Uri.parse("android.resource://" + getPackageName()
                    + "/" + R.raw.samplevideo));
            vv.setOnCompletionListener(new OnCompletionListener() {

                @Override
                public void onCompletion(MediaPlayer arg0) {
                    stopVideo();
                }
            });
            vv.start();
        }
    }

    private void stopVideo() {
        if (mGameView == null) {
            return;
        }
        VideoView vv = (VideoView) findViewById(R.id.videoPlayer);
        vv.stopPlayback();
        setContentView(mGameView);
        // make mGLSurfaceView get focus, or keyboard will popup after activity goes to background and comes back
        for (int i = 0; i < mGameView.getChildCount(); i++) {
            View v = mGameView.getChildAt(i);
            if (v instanceof Cocos2dxGLSurfaceView) {
                v.requestFocus();
                break;
            }
        }
        mGameView = null;
    }
}