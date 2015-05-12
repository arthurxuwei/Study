import com.sun.corba.se.impl.presentation.rmi.DynamicMethodMarshallerImpl;

import java.util.concurrent.Semaphore;

/**
 * Created by arthur.xw on 2015/5/12.
 */
public class ReadThread implements Runnable {

    ReaderFirst mExample = null;
    String name = null;
    boolean flag = true;

    public ReadThread(ReaderFirst re, String name) {
        mExample = re;
        this.name = name;
    }
    @Override
    public void run() {
        mExample.mLatchStart.countDown();
        while (flag) {
            mExample.waitWriteEnd();

            int mReadLength = mExample.g_productor.size();
            String mReadStr = "";
            if (mReadLength > 0) {
                for (Integer a : mExample.g_productor) {
                    mReadStr += String.format("%x", a);
                    System.out.println(name+"read: "+mReadStr);
                }
            }

            if (mExample.bStopFlag) {
                flag = false;
            }
        }
        mExample.singalReadEnd();
    }
}

