package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;

import java.util.regex.Pattern;

public class BrickBlock extends Block {

    public BrickBlock(Bitmap blockBitmap, Bitmap blockHitState, int x, int y) {
        super(blockBitmap, blockHitState, x, y);

    }

    public void draw(Canvas canvas) {
        canvas.drawBitmap(super.getNormState(), super.getX(), super.getY(), null);
        /*
        if (getIsHit()) {
            canvas.drawBitmap(super.getHitState(), super.getX(), super.getY(), null);
        } else {
            canvas.drawBitmap(super.getNormState(), super.getX(), super.getY(), null);
        }
        */
    }

    public void update() {
        super.update();
    }
}
