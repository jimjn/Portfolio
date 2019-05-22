package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;

import static com.example.jingtaoz.eecs40_lames_hw4.Background.getPixels_moved_horizontally;

public class FallZone implements GameObject {
    private Rect r;
    private int left;
    private int right;
    private int oLeft;
    private int oRight;
    private int pixels_moved_horizontally;
    private int last_pixel_moved_horizontally;

    Paint bluePaint;

    public FallZone(int left, int right) {
        this.left = left;
        this.right = right;
        this.oLeft = left;
        this.oRight = right;

        bluePaint = new Paint();
        bluePaint.setColor(Color.rgb(0, 255, 255));

        r = new Rect(left, 740, right, 750);
    }

    public void resetZone() {
        this.left = this.oLeft;
        this.right = this.oRight;
        r = new Rect(this.oLeft, 740, this.oRight, 750);
    }

    public boolean inRange(){
        if (left < 400 && right > 400) {
            return true;
        }
        return false;
    }

    public void setLeft(int left) {
        this.left = left;
    }

    public int getLeft() {
        return left;
    }

    public void setRight(int right) {
        this.right = right;
    }

    public int getRight() {
        return right;
    }

    public void draw(Canvas canvas) {
        canvas.drawRect(r, bluePaint);
    }

    public void updateRect(int dx, int dy) {
        r.offset(dx, dy);
    }

    public void update() {
        pixels_moved_horizontally = getPixels_moved_horizontally();

        int moveAmt = (int) ((last_pixel_moved_horizontally - pixels_moved_horizontally) * Constants.offsetMultiplier);
        left += moveAmt;
        right += moveAmt;
        updateRect(moveAmt, 0);
    }
}
