package com.github.kumodatsu;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class HeightMap
{    
    private List<List<Integer>> heightMap;

    public HeightMap(List<List<Integer>> heightMap)
    {
        this.heightMap = heightMap;
    }

    public int getHeightAtPosition(int x, int y)
        throws IndexOutOfBoundsException
    {
        return this.heightMap.get(y).get(x);
    }

    public int getWidth()
    {
        return this.heightMap.get(0).size();
    }

    public int getHeight()
    {
        return this.heightMap.size();
    }
}
