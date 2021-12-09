package com.github.kumodatsu;

import com.github.kumodatsu.HeightMap;
import com.github.kumodatsu.Position;
import com.github.kumodatsu.StrategyFactory;
import com.github.kumodatsu.ThreatAssessmentStrategy;
import java.util.Scanner;

class Main
{
    private static Main instance;
    
    private HeightMap heightMap;
    private ThreatAssessmentStrategy strategy;

    public static Main getInstance()
    {
        if (instance == null)
        {
            instance = new Main();
        }

        return instance;
    }

    public void initialize(int part)
    {
        Scanner scanner = new Scanner(System.in);
        this.heightMap = new HeightMapFactory().createHeightMap(scanner);
        scanner.close();
        this.strategy = new StrategyFactory().createStrategy(part);
    }

    public void run()
    {
        int threatLevel = this.strategy.assessThreat(this.heightMap);
        System.out.println(threatLevel);
    }

    public static void main(String[] args)
    {
        int part;

        try
        {
            part = Integer.parseInt(args[0]);
            if (part != 1 && part != 2)
            {
                throw new IllegalArgumentException();
            }
        }
        catch (Exception exception)
        {
            System.out.println(
                "You must specify 1 or 2 as an argument, for Part 1 and Part 2"
                + " respectively."
            );
            return;
        }

        Main main = Main.getInstance();
        main.initialize(part);
        main.run();
    }
}
