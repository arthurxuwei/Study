package test;


public class ThreadPrint implements Runnable {
	
	public static void main(String[] args) {
		Object a = new Object();
		Object b = new Object();
		Object c = new Object();
		
		ThreadPrint printA = new ThreadPrint("A", c, a);
		ThreadPrint printB = new ThreadPrint("B", a, b);
		ThreadPrint printC = new ThreadPrint("C", b, c);
		
		new Thread(printA).start();
		try {
			Thread.sleep(500);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		new Thread(printB).start();
		try {
			Thread.sleep(500);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		new Thread(printC).start();
	}
	
	private String name;
	private Object prev;
	private Object self;
	
	private ThreadPrint(String name, Object prev, Object self) {
		this.name = name;
		this.prev = prev;
		this.self = self;
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		int count = 10;
		while (count > 0) {
			synchronized (prev) {
				synchronized (self) {
					System.out.print(name);
					System.out.print(count);
					count--;
					self.notify();
				}	
				try{
					prev.wait();
				} catch (InterruptedException e){
					e.printStackTrace();
				}
			}
		}
	}	

}
