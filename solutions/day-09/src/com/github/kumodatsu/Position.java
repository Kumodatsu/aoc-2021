package com.github.kumodatsu;

public class Position
{
    private int x;
    private int y;

    public Position()
    {
        this(0, 0);
    }

    public Position(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    public int getX()
    {
        return this.x;
    }

    public int getY()
    {
        return this.y;
    }

    public void setX(int x)
    {
        this.x = x;
    }

    public void setY(int y)
    {
        this.y = y;
    }

    @Override
    public boolean equals(Object o)
    {
        if (o == this)
        {
            return true;
        }

        if (!(o instanceof Position))
        {
            return false;
        }

        Position other = (Position) o;

        return other.x == this.x && other.y == this.y;
    }

    @Override
    public int hashCode()
    {
        final int whacky_prime = 23;
        int hash = 1;
        hash = whacky_prime * hash + this.x;
        hash = whacky_prime * hash + this.y;
        return hash; 
    }
}
