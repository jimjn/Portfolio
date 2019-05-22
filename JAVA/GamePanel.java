package com.example.jingtaoz.eecs40_lames_hw4;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Point;
import android.media.MediaPlayer;
import android.support.v4.view.MotionEventCompat;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Toast;

import java.util.ArrayList;

public class GamePanel extends SurfaceView implements SurfaceHolder.Callback {
    private MainThread thread;
    private int PIXEL_HEIGHT;
    private int PIXEL_WIDTH;
    private int pixels_moved_horizontally = 0;
    //game Objects
    private Point marioPoint;
    private Background backgroundManager;
    private int currentLevelCounter;
    private ArrayList<Level> currentLevelObject;

    private boolean touchHold;
    private int touchX;
    private int touchY;
    private int mActivePointerId;
    private int maxLevels = 3;

    public GamePanel(Context context, int height, int width) {
        super(context);
        PIXEL_HEIGHT = height;
        PIXEL_WIDTH = width;

        getHolder().addCallback(this);

        thread = new MainThread(getHolder(), this);

        //Load All necessary Bitmaps
        Bitmap itemsBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.items);
        Bitmap enemiesBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.enemies);

        //Bitmap background = BitmapFactory.decodeResource(context.getResources(), R.drawable.backgroundclean);
        Bitmap background1 = BitmapFactory.decodeResource(context.getResources(), R.drawable.level1);
        Bitmap background2 = BitmapFactory.decodeResource(context.getResources(), R.drawable.level2);
        Bitmap background3 = BitmapFactory.decodeResource(context.getResources(), R.drawable.level3);

        //Bitmap marioBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.mario_images);
        Bitmap koopaBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.kooper);
        Bitmap koopasBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.koopers);
        Bitmap pkoopaBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.kooperpara);
        Bitmap brickBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.brick);
        Bitmap coinBlockBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.coinblock);

        //mario bitmaps
        Bitmap marioBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.mario);
        Bitmap marioSmallBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.mario_small);
        Bitmap marioFireBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.fire_mario);

        //item Bitmaps
        Bitmap coinBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.coin);
        Bitmap mushroomBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.mushroom);
        Bitmap fireFlowerBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.fireflower);

        //3 Goomba Bitmaps
        Bitmap goombaL = BitmapFactory.decodeResource(context.getResources(), R.drawable.goombal);
        Bitmap goombaR = BitmapFactory.decodeResource(context.getResources(), R.drawable.goombar);
        Bitmap goombaF = BitmapFactory.decodeResource(context.getResources(), R.drawable.goombaf);

        //4 fireball images
        Bitmap fireball1 = BitmapFactory.decodeResource(context.getResources(), R.drawable.fireball1);
        Bitmap fireball2 = BitmapFactory.decodeResource(context.getResources(), R.drawable.fireball2);
        Bitmap fireball3 = BitmapFactory.decodeResource(context.getResources(), R.drawable.fireball3);
        Bitmap fireball4 = BitmapFactory.decodeResource(context.getResources(), R.drawable.fireball4);

        //MediaPlayer mediaPlayer = MediaPlayer.create(context,R.raw);
        //Create the data structure for the first level
        /*We should make an arraylist of bitmaps instead of just individually passing bitmaps*/
        currentLevelObject = new ArrayList<Level>();
        currentLevelObject.add(new Level1(fireball1, fireball2, fireball3, fireball4, goombaL,
                goombaR, goombaF, marioBitmap, marioSmallBitmap, marioFireBitmap, enemiesBitmap,
                itemsBitmap, background1, brickBitmap, coinBlockBitmap, koopaBitmap, koopasBitmap,
                pkoopaBitmap, coinBitmap, mushroomBitmap, fireFlowerBitmap, height, width));
        currentLevelObject.add(new Level2(fireball1, fireball2, fireball3, fireball4, goombaL,
                goombaR, goombaF, marioBitmap, marioSmallBitmap, marioFireBitmap, enemiesBitmap,
                itemsBitmap, background2, brickBitmap, coinBlockBitmap, koopaBitmap, koopasBitmap,
                pkoopaBitmap, coinBitmap, mushroomBitmap, fireFlowerBitmap, height, width));
        currentLevelObject.add(new Level3(fireball1, fireball2, fireball3, fireball4, goombaL,
                goombaR, goombaF, marioBitmap, marioSmallBitmap, marioFireBitmap, enemiesBitmap,
                itemsBitmap, background3, brickBitmap, coinBlockBitmap, koopaBitmap, koopasBitmap,
                pkoopaBitmap, coinBitmap, mushroomBitmap, fireFlowerBitmap, height, width));
        currentLevelCounter = 1;

        setFocusable(true);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        thread = new MainThread(getHolder(), this);

        thread.setRunning(true);
        thread.start();

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        boolean retry = true;
        while (true) {
            try {
                thread.setRunning(false);
                thread.join();
            } catch (Exception e) {
                e.printStackTrace();
            }
            retry = false;
        }
    }

    public void OnClick(View view) {
        System.out.println("ButtonClicked");
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        int action = MotionEventCompat.getActionMasked(event);
        this.mActivePointerId = event.getPointerId(0);

        switch (action) {
            case MotionEvent.ACTION_DOWN: {
                int pointerIndex = MotionEventCompat.getActionIndex(event);
                float x = MotionEventCompat.getX(event, pointerIndex);
                float y = MotionEventCompat.getY(event, pointerIndex);

                this.touchHold = true;
                this.touchX = (int) x;
                this.touchY = (int) y;
                if ((int) event.getX() > (PIXEL_WIDTH / 2) && (int) event.getY() > (PIXEL_HEIGHT / 2)) {//jump
                    getCurrentLevel().getMario().setJumping(true, false);
                } else if ((int) event.getX() > (PIXEL_WIDTH / 2) && (int) event.getY() < (PIXEL_HEIGHT / 2)) {//shoot Fireball
                    getCurrentLevel().makeFireball();
                }
                break;
            }
            case MotionEvent.ACTION_POINTER_DOWN: {
                int pointerIndex = MotionEventCompat.getActionIndex(event);
                float x = event.getX(pointerIndex);
                float y = event.getY(pointerIndex);
                //Log.d("MULTITOUCH", "2nd touch x:" + x + " ,y: " + y);

                this.touchHold = true;
                if ((int) x > (PIXEL_WIDTH / 2) && y > (PIXEL_HEIGHT / 2)) {//jump
                    getCurrentLevel().getMario().setJumping(true, false);
                } else if ((int) x > (PIXEL_WIDTH / 2) && (int) y < (PIXEL_HEIGHT / 2)) {//shoot Fireball
                    getCurrentLevel().makeFireball();
                }
                break;
            }
            case MotionEvent.ACTION_MOVE:
                this.touchX = (int) event.getX();
                this.touchY = (int) event.getY();
                break;
            case MotionEvent.ACTION_UP:
                this.touchHold = false;
                break;
            case MotionEvent.ACTION_POINTER_UP:
                break;
        }
        return true;
    }
/*
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_MOVE:
                if ((int) event.getX() > (PIXEL_WIDTH / 2) / 2 && (int) event.getX() < (PIXEL_WIDTH / 2)) {
                    pixels_moved_horizontally += 3;
                    currentLevelObject.getMario().setMarioState(0);
                } else if ((int) event.getX() < (PIXEL_WIDTH / 2) / 2) {
                    pixels_moved_horizontally -= 3;
                    currentLevelObject.getMario().setMarioState(1);
                }
                break;
            case MotionEvent.ACTION_UP:
                if ((int) event.getX() > (PIXEL_WIDTH / 2) && (int) event.getY() > (PIXEL_HEIGHT / 2)) {//jump
                    currentLevelObject.getMario().setJumping(true, false);
                } else if ((int) event.getX() > (PIXEL_WIDTH / 2) && (int) event.getY() < (PIXEL_HEIGHT / 2)) {//shoot Fireball
                    currentLevelObject.makeFireball();
                }
                break;
        }
        return true;
    }
    */


    /*@Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        System.out.println("        Action Taken from game controller");
        pixels_moved_horizontally+=3;
        boolean handled = false;
        if ((event.getSource() & InputDevice.SOURCE_GAMEPAD)
                == InputDevice.SOURCE_GAMEPAD) {
            if (event.getRepeatCount() == 0) {
                switch (keyCode) {
                    // Handle gamepad and D-pad button presses to
                    // navigate the ship
                    //...
                    case KeyEvent.KEYCODE_BUTTON_A:
                        System.out.println("Jumping");
                        currentLevelObject.getMario().setJumping(true);
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_DPAD_LEFT:
                        System.out.println("Moving Left");
                        pixels_moved_horizontally-=3;
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_DPAD_RIGHT:
                        System.out.println("Moving Left");
                        pixels_moved_horizontally+=3;
                        handled = true;
                        break;
                }
            }
            if (handled) {
                return true;
            }
        }
        return super.onKeyDown(keyCode, event);
    }
    @Override
    public boolean onKeyUp(int keyCode,KeyEvent event){

        return super.onKeyUp(keyCode, event);
    }

    private static boolean isFireKey(int keyCode) {
        // Here we treat Button_A and DPAD_CENTER as the primary action
        // keys for the game.
        return keyCode == KeyEvent.KEYCODE_DPAD_CENTER
                || keyCode == KeyEvent.KEYCODE_BUTTON_A;
    }*/

   /* @Override
    public boolean dispatchKeyEvent(KeyEvent event){
        //Toast.makeText(getApplicationContext(), "Input Recieved",
          //      Toast.LENGTH_LONG).show();
        pixels_moved_horizontally += 7;
        return true;
    }
    */

    public void update() {
        if (getCurrentLevel().finishedLevel(getCurrentLevel().getMario())) {
            //changing levels
            System.out.println("Finished Level");
            goToNextLevel();
        }
        //for holding down control
        else {
            if (this.touchHold) {
                if (touchX > (PIXEL_WIDTH / 2) / 2 && touchX < (PIXEL_WIDTH / 2)) { //go right
                    if (getCurrentLevel().getMario().getStopRight()) {
                        Log.d("Stop", "right");
                        pixels_moved_horizontally = 0;
                    } else {
                        pixels_moved_horizontally += 6;
                        getCurrentLevel().getMario().setMarioState(0);
                    }
                } else if (touchX < (PIXEL_WIDTH / 2) / 2) { //go left
                    if (getCurrentLevel().getMario().getStopLeft()) {
                        Log.d("Stop", "left");
                        pixels_moved_horizontally = 0;
                    } else {
                        pixels_moved_horizontally -= 6;
                        getCurrentLevel().getMario().setMarioState(1);
                    }
                }
            }

            //update the location
            getCurrentLevel().update(pixels_moved_horizontally);
            pixels_moved_horizontally = 0;
        }

    }

    @Override
    public void draw(Canvas canvas) {
        super.draw(canvas);
        getCurrentLevel().draw(canvas);
        //draw background
        //backgroundManager.draw(canvas);

        //draw player to screen
        //mario.draw(canvas);

    }

    private Level getCurrentLevel() {
        return currentLevelObject.get(currentLevelCounter - 1);
    }

    private void goToNextLevel() {
        currentLevelCounter++;
        if (currentLevelCounter > maxLevels)
            currentLevelCounter = maxLevels;
    }
}
