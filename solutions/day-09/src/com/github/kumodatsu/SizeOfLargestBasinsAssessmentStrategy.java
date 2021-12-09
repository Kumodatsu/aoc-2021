package com.github.kumodatsu;

import com.github.kumodatsu.HeightMap;
import com.github.kumodatsu.ThreatAssessmentStrategy;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import java.util.Queue;

public class SizeOfLargestBasinsAssessmentStrategy
    implements ThreatAssessmentStrategy
{
    @Override
    public int assessThreat(HeightMap heightMap)
    {
        Set<Position> handledPositions = new HashSet<Position>();
        List<Integer> basinSizes = new ArrayList<Integer>();
        for (int y = 0; y < heightMap.getHeight(); y++)
        {
            for (int x = 0; x < heightMap.getWidth(); x++)
            {
                if (heightMap.getHeightAtPosition(x, y) == 9)
                {
                    continue;
                }
                
                Position p = new Position(x, y);

                if (handledPositions.contains(p))
                {
                    continue;
                }

                int basinSize = 0;
                Queue<Position> queue = new LinkedList<Position>();
                queue.add(p);
                Position current = null;
                while ((current = queue.poll()) != null)
                {
                    int cx = current.getX();
                    int cy = current.getY();
                    if (
                        handledPositions.contains(current)
                        || heightMap.getHeightAtPosition(cx, cy) == 9
                    )
                    {
                        continue;
                    }
                    handledPositions.add(current);
                    basinSize++;
                    if (cx > 0)
                        queue.add(new Position(cx - 1, cy));
                    if (cx < heightMap.getWidth() - 1)
                        queue.add(new Position(cx + 1, cy));
                    if (cy > 0)
                        queue.add(new Position(cx, cy - 1));
                    if (cy < heightMap.getHeight() - 1)
                        queue.add(new Position(cx, cy + 1));
                }
                basinSizes.add(basinSize);
            }
        }

        Collections.sort(basinSizes, new Comparator<Integer>() {
            @Override
            public int compare(Integer x, Integer y)
            {
                return -Integer.compare(x, y);
            }
        });
        
        int basinIndex = 1;
        for (int i = 0; i < 3; i++)
        {
            basinIndex *= basinSizes.get(i);
        }

        return basinIndex;
    }
}
