package com.github.kumodatsu;

import com.github.kumodatsu.LowPointRiskLevelAssessmentStrategy;
import com.github.kumodatsu.SizeOfLargestBasinsAssessmentStrategy;
import com.github.kumodatsu.ThreatAssessmentStrategy;

public class StrategyFactory
{
    public ThreatAssessmentStrategy createStrategy(int part)
    {
        switch (part)
        {
            case 1:
                return new LowPointRiskLevelAssessmentStrategy();
            case 2:
                return new SizeOfLargestBasinsAssessmentStrategy();
            default:
                throw new IllegalArgumentException();
        }
    }
}
