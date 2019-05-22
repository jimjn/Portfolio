package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Point;
import android.graphics.Rect;
import android.icu.text.SymbolTable;
import android.util.Log;

import java.util.ArrayList;

import static com.example.jingtaoz.eecs40_lames_hw4.Level.enemyType.goomba;
import static com.example.jingtaoz.eecs40_lames_hw4.Level.enemyType.koopa;
import static com.example.jingtaoz.eecs40_lames_hw4.Level.enemyType.pkoopa;
import static com.example.jingtaoz.eecs40_lames_hw4.Level.itemType.fireflower;

public class Level3 extends Level {

    public Level3(Bitmap fireball1, Bitmap fireball2, Bitmap fireball3, Bitmap fireball4,
                  Bitmap goombaL, Bitmap goombaR, Bitmap goombaF, Bitmap marioBitmap,
                  Bitmap smallMarioBitmap, Bitmap fireMarioBitmap, Bitmap enemiesBitmap,
                  Bitmap itemsBitmap, Bitmap background, Bitmap brickBitmap, Bitmap coinBlockBitmap,
                  Bitmap koopaBitmap, Bitmap koopasBitmap, Bitmap pkoopaBitmap, Bitmap coinBitmap,
                  Bitmap mushroomBitmap, Bitmap fireFlowerBitmap, int height, int width) {

        super(fireball1, fireball2, fireball3, fireball4, goombaL, goombaR, goombaF, marioBitmap,
                smallMarioBitmap, fireMarioBitmap, enemiesBitmap, itemsBitmap, background,
                brickBitmap, coinBlockBitmap, koopaBitmap, koopasBitmap, pkoopaBitmap, coinBitmap,
                mushroomBitmap, fireFlowerBitmap, height, width);

        super.setEndLevelRect(6230);
    }

    public void setFallingRects() {
        //intialize all of the holes as rectangles here and add to arraylist
        //ex.  fallingRects.add(new Rect(0,0,0,0))
        addFallingRect(new Rect(0, 800, 2000, 802));
    }

    public void populateEnemies() {
        super.addEnemy(goomba, 1000, 740 + 40);

        super.addEnemy(goomba, 3700, 740 + 40);
        super.addEnemy(goomba, 3750, 740 + 40);
        super.addEnemy(goomba, 3800, 740 + 40);


        super.addEnemy(koopa, 5200, 740);
        super.addEnemy(goomba, 5300, 740 + 40);
        super.addEnemy(goomba, 5350, 740 + 40);
        super.addEnemy(koopa, 5450, 740);
        super.addEnemy(pkoopa, 5325, 500);
        super.addEnemy(pkoopa, 5500, 600);
    }

    public void addBlocks() {
        super.addRowOfBricks(3500, 650, 6);
        super.addRowOfBricks(4000, 550, 8);
    }

    public void addGaps() {
        super.addGap(2170, 2400);
        super.addGap(3940, 4110);
    }

    public void addItems() {
        super.addItem(fireflower, 500, 650);
        super.addRowOfCoins(3526,550,4);
        super.addRowOfCoins(4026,450,10);
    }
}
