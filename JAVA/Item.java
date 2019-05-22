package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;

import static com.example.jingtaoz.eecs40_lames_hw4.Background.getPixels_moved_horizontally;

public abstract class Item implements GameObject {

    private Bitmap itemBitmap;
    private Rect itemRect;
    private int x;
    private int y;
    private int originalX;
    private int originalY;
    //private int pixels_moved_horizontally;

    public abstract void onCollide(Mario m);

    public Item(Bitmap itemBitmap, int x, int y) {
        this.itemBitmap = itemBitmap;
        this.x = x;
        this.y = y;
        this.originalX = x;
        this.originalY = y;
        itemRect = new Rect(x, y, x + itemBitmap.getWidth(), y + itemBitmap.getHeight());
    }

    public Rect getItemRect() {
        return itemRect;
    }

    public void updateRect(int dx, int dy) {
        itemRect.offset(dx, dy);
    }

    public void resetItem() {
        this.x = this.originalX;
        this.y = this.originalY;
        itemRect = new Rect(this.originalX, this.originalY,
                this.originalX + itemBitmap.getWidth(),
                this.originalY + itemBitmap.getHeight());
    }

    @Override
    public void draw(Canvas canvas) {
        canvas.drawBitmap(itemBitmap, x, y, null);
    }

    @Override
    public void update() {
        int moveAmt = (int) ((0 - getPixels_moved_horizontally()) * Constants.offsetMultiplier);
        x += moveAmt;
        updateRect(moveAmt, 0);
    }
}
