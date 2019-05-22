package com.example.jingtaoz.eecs40_lames_hw4;

import android.content.pm.ActivityInfo;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ImageView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    int height;
    int width;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);

        DisplayMetrics displayMetrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
        height = displayMetrics.heightPixels;
        width = displayMetrics.widthPixels;
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);

        //setContentView(new GamePanel(this,height,width));
        setContentView(R.layout.activity_main);

        ImageView image = (ImageView) findViewById(R.id.imageView);
        image.setImageResource(R.drawable.mainscreen);

    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event){
        Toast.makeText(getApplicationContext(), "Input Recieved",
                Toast.LENGTH_LONG).show();
        return true;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event){

        setContentView(new GamePanel(this,height,width));
        return true;
    }
}
