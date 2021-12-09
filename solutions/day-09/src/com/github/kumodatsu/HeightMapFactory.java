package com.github.kumodatsu;

import com.github.kumodatsu.HeightMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class HeightMapFactory {
    
    public HeightMap createHeightMap(Scanner scanner)
    {
        List<List<Integer>> heightMap = new ArrayList<List<Integer>>();
        while (scanner.hasNextLine())
        {
            String line = scanner.nextLine();
            List<Integer> strip = new ArrayList<Integer>();
            for (int i = 0; i < line.length(); i++)
            {
                strip.add(Integer.parseInt(String.valueOf(line.charAt(i))));
            }
            heightMap.add(strip);
        }
        return new HeightMap(heightMap);
    }

}
