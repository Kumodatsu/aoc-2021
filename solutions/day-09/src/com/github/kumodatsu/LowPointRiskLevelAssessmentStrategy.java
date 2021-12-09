package com.github.kumodatsu;

import com.github.kumodatsu.HeightMap;
import com.github.kumodatsu.ThreatAssessmentStrategy;
import java.util.List;

public class LowPointRiskLevelAssessmentStrategy
    implements ThreatAssessmentStrategy
{
    @Override
    public int assessThreat(HeightMap heightMap)
    {
        int totalRiskLevel = 0;

        for (int y = 0; y < heightMap.getHeight(); y++)
        {
            for (int x = 0; x < heightMap.getWidth(); x++)
            {
                int height = heightMap.getHeightAtPosition(x, y);

                try
                {
                    if (height >= heightMap.getHeightAtPosition(x + 1, y))
                    {
                        continue;
                    }
                }
                catch (IndexOutOfBoundsException exception)
                {
                }

                try
                {
                    if (height >= heightMap.getHeightAtPosition(x, y + 1))
                    {
                        continue;
                    }
                }
                catch (IndexOutOfBoundsException exception)
                {
                }

                try
                {
                    if (height >= heightMap.getHeightAtPosition(x - 1, y))
                    {
                        continue;
                    }
                }
                catch (IndexOutOfBoundsException exception)
                {
                }

                try
                {
                    if (height >= heightMap.getHeightAtPosition(x, y - 1))
                    {
                        continue;
                    }
                }
                catch (IndexOutOfBoundsException exception)
                {
                }

                totalRiskLevel += height + 1;
            }
        }
        
        return totalRiskLevel;
    }
}
