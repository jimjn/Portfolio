package com.example.jingtaoz.eecs40_lames_hw4;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Point;
import android.graphics.Rect;
import android.util.Log;

import java.lang.reflect.Array;
import java.util.ArrayList;

import static com.example.jingtaoz.eecs40_lames_hw4.Level.itemType.coin;

public abstract class Level {
    private ArrayList<Enemy> enemies;
    private ArrayList<Block> blocks;
    private ArrayList<Fireball> fireballs;
    private ArrayList<Rect> fallingRects;
    private ArrayList<FallZone> gaps;
    private ArrayList<Item> items;

    private ArrayList<Rect> markers;

    private Bitmap background;
    private Bitmap marioBitmap;
    private Bitmap enemiesBitmap;
    private Bitmap itemsBitmap;
    private Bitmap brickBitmap;
    private Bitmap coinBlockBitmap;
    private Bitmap koopaBitmap;
    private Bitmap koopasBitmap;
    private Bitmap pkoopaBitmap;
    private Bitmap goombaL;
    private Bitmap goombaR;
    private Bitmap goombaF;
    private Bitmap fireball1;
    private Bitmap fireball2;
    private Bitmap fireball3;
    private Bitmap fireball4;
    private Bitmap coinBitmap;
    private Bitmap mushroomBitmap;
    private Bitmap fireFlowerBitmap;

    public enum enemyType {
        goomba, koopa, pkoopa
    }

    public enum itemType {
        coin, mushroom, fireflower
    }

    private Background backgroundManager;
    private int height;
    private int width;
    private Point marioPoint;//The point at which mario will start at and stay at(x value wont change but y will when jumping)
    private Mario mario;
    private final int marioXPosition = 400;
    private int marioYPosition = 740;
    private int marioWidth = 0;
    private int marioHeight = 0;

    private int marioBlockColl;

    private Rect endLevelRect;
    int last_pixels_moved_horizontally = 0;
    int endLevelStartX;


    public Level(Bitmap fireball1, Bitmap fireball2, Bitmap fireball3, Bitmap fireball4,
                 Bitmap goombaL, Bitmap goombaR, Bitmap goombaF, Bitmap marioBitmap,
                 Bitmap smallMarioBitmap, Bitmap fireMarioBitmap, Bitmap enemiesBitmap,
                 Bitmap itemsBitmap, Bitmap background, Bitmap brickBitmap, Bitmap coinBlockBitmap,
                 Bitmap koopaBitmap, Bitmap koopasBitmap, Bitmap pkoopaBitmap, Bitmap coinBitmap,
                 Bitmap mushroomBitmap, Bitmap fireFlowerBitmap, int height, int width) {
        this.background = background;
        this.enemiesBitmap = enemiesBitmap;
        this.itemsBitmap = itemsBitmap;
        this.marioBitmap = marioBitmap;
        this.koopaBitmap = koopaBitmap;
        this.koopasBitmap = koopasBitmap;
        this.pkoopaBitmap = pkoopaBitmap;
        this.goombaL = goombaL;
        this.goombaR = goombaR;
        this.goombaF = goombaF;
        this.fireball1 = fireball1;
        this.fireball2 = fireball2;
        this.fireball3 = fireball3;
        this.fireball4 = fireball4;
        this.brickBitmap = brickBitmap;
        this.coinBitmap = coinBitmap;
        this.coinBlockBitmap = coinBlockBitmap;
        this.fireFlowerBitmap = fireFlowerBitmap;
        this.mushroomBitmap = mushroomBitmap;
        this.fireFlowerBitmap = fireFlowerBitmap;

        //background class that keeps track of the background moving left/right
        backgroundManager = new Background(background, height, width);

        //Create the mario object and create a point for him to start at
        mario = new Mario(smallMarioBitmap, marioBitmap, fireMarioBitmap);
        marioPoint = new Point(marioXPosition, marioYPosition);
        marioWidth = mario.getMarioWidth();
        marioHeight = mario.getMarioHeight();

        //System.out.println("mario Width: " + marioWidth);

        enemies = new ArrayList<Enemy>();
        blocks = new ArrayList<Block>();
        fireballs = new ArrayList<Fireball>();
        fallingRects = new ArrayList<Rect>();
        gaps = new ArrayList<FallZone>();
        items = new ArrayList<Item>();


        populateEnemies();
        addBlocks();
        addGaps();
        setFallingRects();
        addItems();
        //setEndLevelRect(1000);


        initMarkers();
        setMarkers();

    }

    public abstract void populateEnemies();

    public abstract void addBlocks();

    public abstract void addGaps();

    public abstract void setFallingRects();

    public abstract void addItems();

    public void addFallingRect(Rect r) {
        this.fallingRects.add(r);
    }

    public void addEnemy(enemyType type, int x, int y) {
        switch (type) {
            case koopa:
                this.enemies.add(new Kooper(enemiesBitmap, x, y));
                break;
            case pkoopa:
                this.enemies.add(new KoopaParatrooper(enemiesBitmap, x, y));
                break;
            case goomba:
                this.enemies.add(new Goomba(goombaL, goombaR, goombaF, x, y));
                break;

        }
    }

    public void addBlock(int x, int y) {
        this.blocks.add(new BrickBlock(brickBitmap, brickBitmap, x, y));
    }

    public void addGap(int left, int right) {
        this.gaps.add(new FallZone(left, right));
    }

    public void addItem(itemType type, int x, int y) {
        switch (type) {
            case coin:
                this.items.add(new Coins(coinBitmap, x, y));
                break;
            case mushroom:
                this.items.add(new Mushroom(mushroomBitmap, x, y));
                break;
            case fireflower:
                this.items.add(new FireFlower(fireFlowerBitmap, x, y));
                break;
        }
    }

    //Returns 1 if collision that mario wins, 2 if mario dies in collision and 0 for no collision at all
    public int enemyCollision(ArrayList<Enemy> enemies, int marioWidth, int marioHeight, int marioX, int marioY) {
        for (Enemy e : enemies) {
            if (e.getEnemyState() != 2) {
                if (e.getEnemyRect().contains(marioX + (int) (marioWidth / 2), marioY + marioHeight + 5)) {
                    System.out.println("defeated enemy");
                    e.setEnemyState(2);
                    e.deleteEnemyRect();

                    return 1;
                } else {
                    if (e.getEnemyRect().contains(marioX, marioY + (int) (marioHeight / 2)))//bottom left point
                        return 2;
                    else if (e.getEnemyRect().contains(marioX + marioWidth, (int) (marioY + marioHeight)))//bottom right
                        return 2;
                }
            }
        }
        return 0;
    }

    public TaggedBlock marioBlockCollision(ArrayList<Block> blocks, int marioWidth, int marioHeight, int marioX, int marioY) {
        for (Block b : blocks) {
            if (b.getBlockRect().contains(marioX - 20, marioY + (int) (marioHeight / 2))) {//bot left point
                //Log.d("BLK_COLL", "left");
                return new TaggedBlock(b, 3);
                //return 3;
            } else if (b.getBlockRect().contains(marioX + marioWidth + 20, (int) (marioY + marioHeight / 2))) {//bot right
                //Log.d("BLK_COLL", "right");
                return new TaggedBlock(b, 4);
                //return 4;
            } else if (b.getBlockRect().contains(marioX + (int) (marioWidth / 2), marioY + marioHeight + 5)) {//marios feet collide
                //Log.d("BLK_COLL", "bot");
                return new TaggedBlock(b, 1);
                //return 1;
            } else if (b.getBlockRect().contains(marioX + (int) (marioWidth / 2), marioY)) {//mario's head collides
                //Log.d("BLK_COLL", "top");
                return new TaggedBlock(b, 2);
                //return 2;
            }
        }
        return null;
    }

    public void fireballEnemyCollision(ArrayList<Enemy> enemies, ArrayList<Fireball> fireballs) {
        for (Fireball fireball : fireballs)
            for (Enemy enemy : enemies) {
                if (fireball.getFireballRect().intersect(enemy.getEnemyRect())) {
                    enemy.deleteEnemyRect();
                    enemy.setEnemyState(2);
                    fireball.deleteFireball();
                    fireballs.remove(fireball);
                }
            }
    }

    public Item itemCollision(ArrayList<Item> items, int marioWidth, int marioHeight, int marioX, int marioY) {
        for (Item i : items) {
            if (i.getItemRect().contains(marioX, marioY) ||
                    i.getItemRect().contains(marioX + marioWidth, marioY) ||
                    i.getItemRect().contains(marioX, marioY + marioHeight) ||
                    i.getItemRect().contains(marioX + marioWidth, marioY + marioHeight)) {
                return i;
            }
        }
        return null;
    }

    public int marioFallingDeath(ArrayList<Rect> rects, int marioX, int marioY) {
        for (Rect rect : rects) {
            if (rect.contains(marioX, marioY))
                return 2;
        }
        return 0;
    }

    public boolean finishedLevel(Mario mario) {
        if (endLevelRect.contains(mario.getMarioPoint().x, mario.getMarioPoint().y)) {
            return true;
        }
        return false;
    }

    public void setEndLevelRect(int x) {
        endLevelStartX = x;
        endLevelRect = new Rect(x, 740, x + 40, 820);
    }

    public Rect getEndLevelRect() {
        return endLevelRect;
    }

    public void offsetEndLevelRect(int pixels_moved_horizontally) {
        endLevelRect.offset((int) ((last_pixels_moved_horizontally - pixels_moved_horizontally) * Constants.offsetMultiplier), 0);
        // last_pixels_moved_horizontally = pixels_moved_horizontally;
    }

    public void resetEndLevelRect() {
        endLevelRect = new Rect(endLevelStartX, 740, endLevelStartX + 40, 820);
    }


    public void initMarkers() {
        markers = new ArrayList<Rect>();
    }

    public void setMarkers() {
        for (int i = 0; i < 8500; i += 10) {
            markers.add(new Rect(i, 850, i + 10, 900));
        }
    }

    public void offsetMarkers(int pixels_moved_horizontally) {
        if (!markers.isEmpty()) {
            for (Rect r : markers) {
                r.offset((int) ((last_pixels_moved_horizontally - pixels_moved_horizontally) * Constants.offsetMultiplier), 0);
            }
        }
    }

    public ArrayList<Rect> getMarkers() {
        return markers;
    }

    public int getMarker(int marioX) {
        if (!markers.isEmpty()) {
            for (Rect r : markers) {
                if (r.contains(marioX, 875)) {
                    return r.left;
                }
            }
        }
        return -1;
    }

    public void addStaircase(int xStart, int direction) {//1- up, -1 -down
        /*Reverse Stair making form - start with bottom row(startY is bottom row)*/
        int startX = xStart;
        int startY = 825;
        int maxX = 8;
        int maxY = maxX - 1;
        if (direction == -1) {
            for (int y = 1; y < maxY; y++) {
                for (int x = 1; x < maxX; x++)
                    blocks.add(new BrickBlock(brickBitmap, brickBitmap, startX + (42 * x), startY - (42 * y)));
                maxX -= 1;
            }
        }
        /*Forward making form*/
        else {
            startX = xStart;
            startY = 825;
            maxX = 8;
            maxY = maxX;
            for (int y = 1; y < maxY; y++) {
                for (int x = 1; x < maxX; x++)
                    blocks.add(new BrickBlock(brickBitmap, brickBitmap, startX + (42 * x), startY - (42 * y)));
                maxX -= 1;
                startX += 42;
            }
        }
    }

    public void addRowOfBricks(int startX, int startY, int length) {
        int brickWidth = 42;

        for (int i = 1; i < length; i++)
            blocks.add(new BrickBlock(brickBitmap, brickBitmap, startX + (brickWidth * (i - 1)), startY));
    }

    public void addRowOfCoins(int startX,int startY,int length){
        int coinWidth = 26;

        for(int i = 1; i<length; i++)
            addItem(coin,startX + (coinWidth *(i-1)),startY);
    }
    public Mario getMario() {
        return mario;
    }

    public void makeFireball() {
        if (mario.getMarioForm() == 2) {
            fireballs.add(new Fireball(fireball1, fireball2, fireball3, fireball4,
                    marioPoint.x + 46, marioPoint.y + 30, mario.getMarioState()));
        }
    }

    public boolean finishedLevel() {
        //Return True if level has been finished

        //Return False if level has not been finished
        return false;
    }

    public void draw(Canvas canvas) {
        //call all draw methods
        Paint paint = new Paint();
        paint.setColor(Color.WHITE);
        backgroundManager.draw(canvas);
        canvas.drawRect(getEndLevelRect(), paint);

        mario.draw(canvas);
        for (Enemy e : enemies) {
            e.draw(canvas);
        }
        for (Block b : blocks) {
            b.draw(canvas);
        }
        for (FallZone f : gaps) {
            f.draw(canvas);
        }
        if (!fireballs.isEmpty()) {
            for (Fireball f : fireballs) {
                f.draw(canvas);
            }
        }
        if (!items.isEmpty()) {
            for (Item i : items) {
                i.draw(canvas);
            }
        }


        Paint redPaint = new Paint();
        redPaint.setColor(Color.RED);
        Paint greenPaint = new Paint();
        greenPaint.setColor(Color.GREEN);
        int i = 0;
        ArrayList<Rect> marks = getMarkers();
        for (Rect r : marks) {

            if (i % 2 == 0) {
                canvas.drawText(Integer.toString(i), r.left, (float) (r.top - (150 * Math.sin(i))), redPaint);
            } else {
                canvas.drawText(Integer.toString(i), r.left, (float) (r.top - (150 * Math.sin(i))), greenPaint);
            }
            i++;
        }

    }

    public void update(int pixels_moved_horizontally) {
        if (!markers.isEmpty()) {
            offsetMarkers(pixels_moved_horizontally);
        }

        //call all update methods
        //update the marioYposition
        marioYPosition = (int) mario.getMarioPoint().y;

        //Log.d("MarioPos", "" + backgroundManager.getXCenter());

        // update end level rect
        offsetEndLevelRect(pixels_moved_horizontally);
        //Check if mario fell down the hole like an idiot
        if (marioFallingDeath(fallingRects, marioXPosition, marioYPosition) == 2) {
            //yes mario fell down the hole
            mario.setLivesMinusOne();
            if (mario.getLives() == 0) {
                //GameOver
            } else {
                //reset mario back to begining
                //reset background
                mario.setGround(740);
                pixels_moved_horizontally = 0;
                backgroundManager.resetBackground();
                backgroundManager.setPixels_moved_horizontally(0);
                resetEndLevelRect();
                for (FallZone f : gaps) {
                    f.resetZone();
                }
                for (Enemy e : enemies) {
                    e.resetEnemy();
                }
                for (Block b : blocks) {
                    b.resetBlock();
                }
                if (!items.isEmpty()) {
                    for (Item i : items) {
                        i.resetItem();
                    }
                }
                mario.getMarioPoint().offset(0, -100);
                mario.setMarioForm(0);
            }

        }

        //check fireball collision
        fireballEnemyCollision(enemies, fireballs);

        //check block collision
        TaggedBlock marioBlockColl = marioBlockCollision(blocks, marioWidth, marioHeight, marioXPosition, marioYPosition);
        if (marioBlockColl == null) {
            mario.setGround(740);
            //check gaps
            for (FallZone f : gaps) {
                if (f.inRange()) {
                    mario.setGround(900);
                }
            }
            mario.allowRight();
            mario.allowLeft();
        } else if (marioBlockColl.getTag() == 2) {
            mario.stopJump();
            mario.allowRight();
            mario.allowLeft();
            mario.setGround(740);
            //check gaps
            for (FallZone f : gaps) {
                if (f.inRange()) {
                    mario.setGround(900);
                }
            }
        } else if (marioBlockColl.getTag() == 1) {
            //check gaps
            for (FallZone f : gaps) {
                if (f.inRange()) {
                    mario.setGround(900);
                }
            }
            mario.setGround(marioBlockColl.getB().getBlockRect().top - marioHeight);
            mario.allowRight();
            mario.allowLeft();
        } else if (marioBlockColl.getTag() == 3) {
            mario.allowRight();
            mario.stopLeft();
        } else if (marioBlockColl.getTag() == 4) {
            mario.allowLeft();
            mario.stopRight();
        }


        //check enemy collision
        int collisionCheck = enemyCollision(enemies, marioWidth, marioHeight, marioXPosition, marioYPosition);
        if (collisionCheck == 2) {//Mario died in collision
            System.out.println("Collision!!!!");
            if (mario.getInvincible()) {
                //do nothing
            } else if (mario.getMarioForm() == 0 && !mario.getInvincible()) {

                mario.setLivesMinusOne();
                if (mario.getLives() == 0) {
                    //game over
                }
                //reset mario back to begining
                //reset background
                mario.setGround(740);
                pixels_moved_horizontally = 0;
                backgroundManager.resetBackground();
                backgroundManager.setPixels_moved_horizontally(0);
                resetEndLevelRect();
                for (FallZone f : gaps) {
                    f.resetZone();
                }
                for (Enemy e : enemies) {
                    e.resetEnemy();
                }
                for (Block b : blocks) {
                    b.resetBlock();
                }
                if (!items.isEmpty()) {
                    for (Item i : items) {
                        i.resetItem();
                    }
                }
                mario.setInvincible(false);
                Log.d("reset", "");
            } else {
                Log.d("mario form", "" + mario.getMarioForm());
                mario.setMarioForm(mario.getMarioForm() - 1);
                mario.setInvincible(true);
            }
        } else if (collisionCheck == 1) {//enemy died in collision instead
            /*Set Mario state to jumping if hes not already jumping*/
            /*Reset jump frame to 0*/
            mario.setJumping(true, true);
        }

        if (!items.isEmpty()) {
            Item collItem = itemCollision(items, marioWidth, marioHeight, marioXPosition, marioYPosition);
            if (collItem == null) {
                //do nothing
            } else {
                collItem.onCollide(mario);
                items.remove(collItem);
            }
        }

        //move mario horizontally
        mario.update(marioPoint);
        backgroundManager.update(pixels_moved_horizontally);

        if (!enemies.isEmpty()) {
            for (Enemy e : enemies) {
                e.update();
            }
        }
        if (!blocks.isEmpty()) {
            for (Block b : blocks) {
                b.update();
            }
        }
        if (!gaps.isEmpty()) {
            for (FallZone f : gaps) {
                f.update();
            }
        }
        if (!fireballs.isEmpty()) {
            for (Fireball f : fireballs) {
                f.update();
            }
        }
        if (!items.isEmpty()) {
            for (Item i : items) {
                i.update();
            }
        }
    }
}
