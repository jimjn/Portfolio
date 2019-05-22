package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Rect;

import static com.example.jingtaoz.eecs40_lames_hw4.Background.getPixels_moved_horizontally;

public abstract class Enemy {
    private int x;
    private int y;
    private Bitmap character;
    private Bitmap characterDefeatState;
    private Bitmap characterRight;
    private Rect enemyRect;
    private int originalX;
    private int originalY;

    public Enemy(Bitmap character, Bitmap characterDefeatState, int x, int y) {
        this.character = character;
        this.characterDefeatState = characterDefeatState;
        this.x = x;
        this.y = y;
        this.originalX = x;
        this.originalY = y;


        Matrix matrix = new Matrix();
        matrix.preScale(-1.0f, 1.0f);
        characterRight = Bitmap.createBitmap(character, 0, 0, character.getWidth(), character.getHeight(), matrix, true);

        enemyRect = new Rect(this.x, this.y, this.x + character.getWidth(), this.y + character.getHeight());
        //enemyRect.set(0,,10,10);
    }

    public Enemy() {

    }

    public void resetEnemy() {
        setX(this.originalX);
        setY(this.originalY);
        enemyRect = new Rect(this.originalX, this.originalY, this.originalX + character.getWidth(), this.originalY + character.getHeight());
    }

    public Bitmap getCharacter() {
        return character;
    }

    public Bitmap getCharacterRight() {
        return characterRight;
    }

    public Bitmap getCharacterDefeatState() {
        return characterDefeatState;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void updateRect(int dx, int dy) {
        enemyRect.offset(dx, dy);
    }

    public Rect getEnemyRect() {
        return enemyRect;
    }

    public void deleteEnemyRect() {
        enemyRect = new Rect(0, 0, 0, 0);
    }

    public void update(){
        //dont know why but u have to scale it by 1.9 to work better (not good but not very noticeable)
        int moveAmt = (int) ((0 - getPixels_moved_horizontally()) * Constants.offsetMultiplier);
        x += moveAmt;
        updateRect(moveAmt, 0);
    };

    public abstract void draw(Canvas canvas);

    public abstract int getEnemyState();

    public abstract void setEnemyState(int state);

}
