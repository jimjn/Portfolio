package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;

import java.security.KeyStore;
import java.util.ArrayList;

import static com.example.jingtaoz.eecs40_lames_hw4.Background.getPixels_moved_horizontally;

public class Fireball implements GameObject{

    private int startCycloidX;
    private int startCycloidY;
    private int currentX;
    private double currentY;
    private double t;
    private double tStep = .209;//1 second per arc is 30 frames, 2pi/30 = .209
    private double deltaX;
    private double deltaY;
    private double lastX;
    private double lastY;

    private double radiusInPixels;
    private double dampingFactor = 1;

    private int yOffsetDueToMario = 740;
    private int xOffsetDueToMario = 400;

    private int CurrentDrawFrame = 1;
    private int NextEndDrawFrame;
    private int framesPerPicture = 5;
    private int arrayListIndex;
    private int direction;//0 = right, 1 = left

    private Bitmap fireball1;
    private Bitmap fireball2;
    private Bitmap fireball3;
    private Bitmap fireball4;
    private ArrayList<Bitmap> fireballBitmap;

    private int last_pixel_moved_horizontally =0;
    private int pixels_moved_horizontally;

    private boolean fireBallIsDead;

    //linear model variables
    private double slope = 1;
    private int pixelsPerFrameX = 14;
    private int framesPerPeriod = 30;


    private Rect fireballRect;

    public Fireball(Bitmap fireball1,Bitmap fireball2,Bitmap fireball3,Bitmap fireball4, int x, int y,int direction){
        fireballBitmap = new ArrayList<Bitmap>();
        fireballBitmap.add(fireball1);
        fireballBitmap.add(fireball2);
        fireballBitmap.add(fireball3);
        fireballBitmap.add(fireball4);

        startCycloidX = x;
        startCycloidY = y;
        lastX = x;
        lastY = y;
        radiusInPixels = 10;//(double) (740-y);
        currentX = x;
        currentY = y;
        t = Math.PI;//start at top of arc

        fireballRect = new Rect(x,y,x+fireball1.getWidth(),y+fireball1.getHeight());
        this.direction = direction;

        fireBallIsDead = false;
        NextEndDrawFrame = CurrentDrawFrame + framesPerPicture;
        arrayListIndex = 0;
        last_pixel_moved_horizontally = getPixels_moved_horizontally();
        int value = x + getPixels_moved_horizontally();
        System.out.println("X Value: " + value);
    }

    @Override
    public void draw(Canvas canvas) {
        //System.out.println("Drawing fireball");
            if(CurrentDrawFrame == NextEndDrawFrame){
                if(arrayListIndex ==3)
                    arrayListIndex =0;
                else
                    arrayListIndex++;

                NextEndDrawFrame = CurrentDrawFrame+framesPerPicture;
            }
            canvas.drawBitmap(fireballBitmap.get(arrayListIndex),(float)currentX,(float)currentY,null);
            CurrentDrawFrame++;
    }

    @Override
    public void update() {
        /*Model the motion of the fireball as a cycloid*/
        /*parameterization
        * x = r(t - sint)
        * y = r(t - cost)
        * 0 < t < 2pi
        *
        * */


        //movement of cycloid - doesn't work
        /*
        if(t > (2*Math.PI)){
            t = 0;
            currentY = startCycloidY;
            currentX += 2*radiusInPixels;
        }
        deltaX = (radiusInPixels*(t - Math.sin(t)))*dampingFactor;
        deltaY = (radiusInPixels*(1 - Math.cos(t)))*dampingFactor;
        if(direction == 0)
            currentX = (int)((double)startCycloidX + deltaX);
        else
            currentX = (int)((double)startCycloidY - deltaX);

        currentY = (int)((double)startCycloidY -deltaY);

        t+=tStep;*/

        /*if(t > (2*Math.PI)){
            t = 0;
            currentY = startCycloidY;
        }*/

        if(direction ==0) {
            currentX += pixelsPerFrameX;
            fireballRect.offset(pixelsPerFrameX,0);
        }
        else {
            currentX -= pixelsPerFrameX;
            fireballRect.offset(pixelsPerFrameX,0);
        }
        //currentY = startCycloidY+(1*tStep - (.5)*(3.2)*tStep);



        //movement as a straight line

        //movement due to mario
        pixels_moved_horizontally = getPixels_moved_horizontally();
        int moveAmt = (int) ((last_pixel_moved_horizontally - pixels_moved_horizontally) * Constants.offsetMultiplier);
        currentX += moveAmt;

    }
    public Rect getFireballRect(){return fireballRect;}
    public void deleteFireball(){
        fireBallIsDead = true;
        fireballRect = new Rect(0,0,0,0);
    }
}
