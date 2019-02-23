package mediator;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

class Mediator {
    private boolean slotFull = false;
    private int number;

    public synchronized void storeMessage(int number) {
        while (slotFull) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        slotFull = true;
        this.number = number;
        notifyAll();
    }

    public synchronized int retrieveMessage() {
        while (!slotFull) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        slotFull = false;
        notifyAll();
        return number;
    }
}

class Producer implements Runnable {
    private Mediator mediator;
    private int id;
    private static int num = 1;

    public Producer(Mediator mediator) {
        this.mediator = mediator;
        this.id = num++;
    }

    @Override
    public void run() {
        int num;
        while (true) {
            mediator.storeMessage(num = new Random().nextInt());
            System.out.print( "p" + id + "-" + num + "  " );
        }
    }
}

class Consumer implements Runnable {
    private Mediator mediator;
    private int id;
    private static int num = 1;

    public Consumer(Mediator mediator) {
        this.mediator = mediator;
        this.id = num++;
    }

    @Override
    public void run() {
        int num;
        while (true) {
            System.out.print("c" + id + "-" + mediator.retrieveMessage() + "  ");
        }
    }
}


/**
 * @author arthur.xw
 */
public class Demo {
    public static void main( String[] args ) {
        List<Thread> producerList = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        System.out.println("Press ENTER for exit");
        Mediator mb = new Mediator();
        producerList.add(new Thread(new Producer(mb)));
        producerList.add(new Thread(new Producer(mb)));
        producerList.add(new Thread(new Consumer(mb)));
        producerList.add(new Thread(new Consumer(mb)));
        producerList.add(new Thread(new Consumer(mb)));
        producerList.add(new Thread(new Consumer(mb)));
        for (Thread p : producerList) {
            p.start();
        }
        boolean stop = false;
        String exit = scanner.nextLine();
        while (!stop) {
            if ("".equals(exit)) {
                stop = true;
                for (Thread p : producerList) {
                    //noinspection deprecation
                    p.stop();
                }
            }
        }
    }
}
