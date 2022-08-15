package com.demo.agent;

import java.lang.instrument.Instrumentation;

public class MethodCostTimeAgent {
    public static void premain(String agentOps, Instrumentation instrumentation) {
        System.out.println("Agent---");
        System.out.println("agentOps: " + agentOps);
        instrumentation.addTransformer(new TestTransformer());
    }

    public static void premain(String agentOps) {
        System.out.println("Agent---");
        System.out.println("agentOps: " + agentOps);
    }
}
