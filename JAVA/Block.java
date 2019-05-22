package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.util.Log;

import static com.example.jingtaoz.eecs40_lames_hw4.MainThread.canvas;
import static com.example.jingtaoz.eecs40_lames_hw4.Background.getPixels_moved_horizontally;

public abstract class Block implements GameObject {

    private Bitmap normState;
    private Bitmap hitState;
    private Rect blockRect;
    private int x;
    private int y;
    private int originalX;
    private int originalY;
    private int pixels_moved_horizontally;
    private int last_pixel_moved_horizontally;
    private boolean isHit;

    public Block(Bitmap blockBitmap, Bitmap blockHitState, int x, int y) {
        normState = blockBitmap;
        hitState = blockHitState;
        this.x = x;
        this.y = y;
        this.originalX = x;
        this.originalY = y;
        this.isHit = false;

        blockRect = new Rect(this.x, this.y, this.x + normState.getWidth(),
                this.y + normState.getHeight());
    }


    public void resetBlock() {
        setX(this.originalX);
        setY(this.originalY);
        blockRect = new Rect(this.originalX, this.originalY,
                this.originalX + normState.getWidth(),
                this.originalY + normState.getHeight());
    }

    public boolean checkHit() {
        return false;
    }

    public boolean getIsHit() {
        return isHit;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public void updateRect(int dx, int dy) {
        blockRect.offset(dx, dy);
    }

    public Rect getBlockRect() {
        return blockRect;
    }

    public Bitmap getNormState() {
        return normState;
    }

    public Bitmap getHitState() {
        return hitState;
    }

    public abstract void draw(Canvas canvas);

    public void update() {
        pixels_moved_horizontally = getPixels_moved_horizontally();

        int moveAmt = (int) ((last_pixel_moved_horizontally - pixels_moved_horizontally) * Constants.offsetMultiplier);
        if (last_pixel_moved_horizontally > pixels_moved_horizontally) {//old > new -> mario moved left
            setX(getX() + moveAmt);
            updateRect(moveAmt, 0);
        } else {//mario moved right
            setX(getX() + moveAmt);
            updateRect(moveAmt, 0);
        }
    }

}

