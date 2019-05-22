package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.DisplayMetrics;

/*
Idea for background
background is one, super wide image in drawable
the Rectange of the background that is drawn is based on
the controls. i.e. mario stays at the same x value on the screen

 */
public class Background {

    private Bitmap background;
    private Rect visibleScreen;
    private Rect destinationRect;
    private int HEIGHT_PIXEL;
    private int WIDTH_PIXEL;
    private static int pixels_moved_horizontally;

    public Background(Bitmap background, int height, int width) {
        this.background = background;
        HEIGHT_PIXEL = height;
        HEIGHT_PIXEL = width;

        visibleScreen = new Rect(0, 0, 1040, 780);//4:3 aspect ratio just like nes
        destinationRect = new Rect(0, 0, width, height);

    }

    public void draw(Canvas canvas) {
        visibleScreen.offset(pixels_moved_horizontally, 0);
        canvas.drawBitmap(background, visibleScreen, destinationRect, null);
        //have to set it back to zero to make it stop moving
        pixels_moved_horizontally = 0;


    }

    public void resetBackground() {
        visibleScreen = new Rect(0, 0, 1040, 780);
    }

    public static void setPixels_moved_horizontally(int pixels_moved_horizontally) {
        Background.pixels_moved_horizontally = pixels_moved_horizontally;
    }

    public void update(int pixels_moved_horizontally) {
        this.pixels_moved_horizontally += pixels_moved_horizontally;
    }

    public static int getPixels_moved_horizontally() {
        return pixels_moved_horizontally;
    }

    public int getXCenter(){
        return visibleScreen.centerX();
    }
}
