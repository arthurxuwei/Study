package AOP.AspectJ;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Pointcut;

/**
 * Created by arthur.xw on 2015/6/17.
 */
@Aspect
public class SimpleLoggerAspect {
    @Pointcut("execution(* *(..))")
    public void simpleTraceCall() {

    }

    @Around("AOP.AspectJ.SimpleLoggerAspect.simpleTraceCall()")
    public Object simpleTrace(ProceedingJoinPoint joinPoint) throws  Throwable {
        System.out.println("simpleTrace:before call"
            + joinPoint.getTarget().getClass().getName()
            + "." + joinPoint.getSignature().getName());

        Object retVal = null;
        try {
            retVal = joinPoint.proceed();
        } finally {
            System.out.println("simpleTrace:before call"
                + joinPoint.getTarget().getClass().getName()
                + "." + joinPoint.getSignature().getName()
                + " retval=" + retVal);
        }
        return retVal;
    }
}
