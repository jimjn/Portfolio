package com.example.jingtaoz.eecs40_lames_hw4;


import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.ColorFilter;
import android.graphics.LightingColorFilter;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Point;
import android.graphics.Rect;
import android.util.Log;

import static com.example.jingtaoz.eecs40_lames_hw4.MainThread.canvas;

public class Mario implements GameObject {
    private Bitmap reg_Mario;// = BitmapFactory.decodeResource(getApplicationContext().  ,R.drawable.mario_test);
    private Bitmap reg_Mario_left;
    private Bitmap fire_Mario;
    private Bitmap fire_Mario_left;
    private Bitmap small_Mario;
    private Bitmap small_Mario_left;
    /*
    private Bitmap jump_Mario;
    private Bitmap jump_Mario_left;
    */
    private double scale = 3.1;
    private Point marioPoint;

    /*
    private boolean FIRE_MARIO = false;
    private boolean REG_MARIO = true;
    private boolean SUPER_MARIO = false;
    */

    private int marioState = 0;//0 right 1 left 2 jump
    private int marioForm = 0; //0 = small, 1 = norm, 2 = fire

    private int lives;
    private Paint whitePaint;
    private Paint blackPaint;

    private int score;

    private Rect marioVisible;
    private Rect marioDestination;

    private boolean invincible;
    private int invincibleFrame;
    private int endInvincibleFrame = 70;

    private boolean jumping;
    private int jumpingFrame;
    private int endJumpingFrame = 40;
    private int pixelsPerJumpingFrame = 8;

    private int yValGround = 740;
    private int fallPixelsPerFrame = 10;

    private boolean stopJumping = false;
    private boolean stopRight = false;
    private boolean stopLeft = false;

    public Point getMarioPoint() {
        return marioPoint;
    }

    public Mario(Bitmap small_Mario, Bitmap reg_Mario, Bitmap fire_Mario) {
        this.reg_Mario = reg_Mario;
        this.small_Mario = small_Mario;
        this.fire_Mario = fire_Mario;
        lives = 3;
        //marioVisible = new Rect(150,0,165,32);

        //this.reg_Mario = Bitmap.createBitmap(reg_Mario,(int)(78*scale)+1,5,(int)(15*scale)-4,(int)(32*scale)-5);
        Matrix matrix = new Matrix();
        matrix.preScale(-1.0f, 1.0f);
        reg_Mario_left = Bitmap.createBitmap(this.reg_Mario, 0, 0,
                this.reg_Mario.getWidth(), this.reg_Mario.getHeight(), matrix, true);
        small_Mario_left = Bitmap.createBitmap(this.small_Mario, 0, 0,
                this.small_Mario.getWidth(), this.small_Mario.getHeight(), matrix, true);
        fire_Mario_left = Bitmap.createBitmap(this.fire_Mario, 0, 0,
                this.fire_Mario.getWidth(), this.fire_Mario.getHeight(), matrix, true);

        //jump_Mario = Bitmap.createBitmap(reg_Mario,(int)(230*scale)-10,5,(int)(15*scale)-4,(int)(32*scale)-5);
        //jump_Mario_left = Bitmap.createBitmap(this.jump_Mario, 0, 0, this.reg_Mario.getWidth(), this.reg_Mario.getHeight(), matrix, true);
        //jump_Mario = reg_Mario;
        //jump_Mario_left = reg_Mario_left;
        whitePaint = new Paint();
        whitePaint.setColor(Color.WHITE);
        whitePaint.setTextSize(100);

        blackPaint = new Paint();
        blackPaint.setColor(Color.BLACK);
        blackPaint.setStyle(Paint.Style.STROKE);
        blackPaint.setStrokeWidth(4);
        blackPaint.setTextSize(100);

        marioPoint = new Point(400, 740);
        score = 0;
    }

    @Override
    public void draw(Canvas canvas) {
        Paint p = new Paint();
        ColorFilter filter = new LightingColorFilter(0xFFFFFFFF, 0x000088AA);
        if (invincible) {
            p.setColorFilter(filter);
        } else {
            p = null;
        }

        //p = null;

        if (marioState == 0) { //running right
            switch (marioForm) {
                case 0:
                    canvas.drawBitmap(small_Mario, marioPoint.x, marioPoint.y, p);
                    break;
                case 1:
                    canvas.drawBitmap(reg_Mario, marioPoint.x, marioPoint.y, p);
                    break;
                case 2:
                    canvas.drawBitmap(fire_Mario, marioPoint.x, marioPoint.y, p);
                    break;
            }
        } else if (marioState == 1) { //running left
            switch (marioForm) {
                case 0:
                    canvas.drawBitmap(small_Mario_left, marioPoint.x, marioPoint.y, p);
                    break;
                case 1:
                    canvas.drawBitmap(reg_Mario_left, marioPoint.x, marioPoint.y, p);
                    break;
                case 2:
                    canvas.drawBitmap(fire_Mario_left, marioPoint.x, marioPoint.y, p);
                    break;
            }
        } else if (marioState == 2) {//jumping right
            switch (marioForm) {
                case 0:
                    canvas.drawBitmap(small_Mario, marioPoint.x, marioPoint.y, p);
                    break;
                case 1:
                    canvas.drawBitmap(reg_Mario, marioPoint.x, marioPoint.y, p);
                    break;
                case 2:
                    canvas.drawBitmap(fire_Mario, marioPoint.x, marioPoint.y, p);
                    break;
            }
        } else if (marioState == 3) {//jumping left
            switch (marioForm) {
                case 0:
                    canvas.drawBitmap(small_Mario_left, marioPoint.x, marioPoint.y, p);
                    break;
                case 1:
                    canvas.drawBitmap(reg_Mario_left, marioPoint.x, marioPoint.y, p);
                    break;
                case 2:
                    canvas.drawBitmap(fire_Mario_left, marioPoint.x, marioPoint.y, p);
                    break;
            }
        }

        canvas.drawText("LIVES: " + lives, 10, 70, whitePaint);
        canvas.drawText("LIVES: " + lives, 10, 70, blackPaint);
        canvas.drawText("Score:" + score, 500, 70, whitePaint);
        canvas.drawText("Score:" + score, 500, 70, blackPaint);
    }

    public int getMarioWidth() {
        return reg_Mario.getWidth();
    }

    public int getMarioHeight() {
        return reg_Mario.getHeight();
    }

    @Override
    public void update() {

    }

    public void update(Point point) {
        this.marioPoint = point;
        //Log.d("mariopoint","x: " + point.x + ", y: " + point.y);
        this.endJumpingFrame = 15;
        this.pixelsPerJumpingFrame = 25;

        if (stopJumping) {
            jumping = false;
            stopJumping = false;
        }

        if (invincible) {
            invincibleFrame++;
            if (invincibleFrame >= endInvincibleFrame) {
                invincible = false;
            }
        }

        if (jumping) {
            this.marioPoint.offset(0, 0 - pixelsPerJumpingFrame);
            jumpingFrame++;
            if (jumpingFrame >= endJumpingFrame) {//stop jumping
                jumping = false;
                if (this.marioState == 2) {
                    this.marioState = 0;
                } else if (this.marioState == 3) {
                    this.marioState = 1;
                }
            }
        }

        if (point.y < yValGround) { //less than because thats how the coordiate system works
            this.marioPoint.offset(0, fallPixelsPerFrame);
        }
    }

    public int getLives() {
        return lives;
    }

    public void setMarioForm(int form) {
        if (form > this.marioForm) {
            this.marioForm = form;
        } else if (invincible) {
            //do nothing
        } else {
            this.marioForm = form;
        }
    }

    public int getMarioForm() {
        return this.marioForm;
    }

    public void setMarioState(int state) {
        this.marioState = state;
    }

    public int getMarioState() {
        return this.marioState;
    }

    public void setLivesMinusOne() {
        if (!invincible) {
            lives--;
        }
    }

    public void setInvincible(boolean invin) {
        if (!this.invincible) {
            this.invincible = invin;
            this.invincibleFrame = 1;
        }
    }

    public boolean getInvincible() {
        return this.invincible;
    }

    public void setJumping(boolean isjumping, boolean force) {
        if (force) {
            //set force for when bouncing off killed enemy
            this.jumping = isjumping;
            this.jumpingFrame = 1;
            if (this.marioState == 0) {
                this.marioState = 2;
            } else if (this.marioState == 1) {
                this.marioState = 3;
            }
        } else if (this.marioPoint.y < yValGround) {
            //do nothing; lockout so cant jump in midair
        } else {
            this.jumping = isjumping;
            this.jumpingFrame = 1;
            if (this.marioState == 0) {
                this.marioState = 2;
            } else if (this.marioState == 1) {
                this.marioState = 3;
            }
        }

    }

    public void addPoints(int i) {
        this.score += i;
    }

    public int getScore() {
        return score;
    }

    public void stopJump() {
        this.stopJumping = true;
    }

    public void stopRight() {
        this.stopRight = true;
    }

    public void stopLeft() {
        this.stopLeft = true;
    }

    public void allowLeft() {
        this.stopLeft = false;
    }

    public void allowRight() {
        this.stopRight = false;
    }

    public boolean getStopRight() {
        return this.stopRight;
    }

    public boolean getStopLeft() {
        return this.stopLeft;
    }

    public void setGround(int groundLevel) {
        this.yValGround = groundLevel;
    }
}
