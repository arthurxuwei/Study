import org.junit.Test;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class BIOTest {
    @Test
    public void test() throws IOException {
        ServerSocket serverSocket = new ServerSocket(8887);
        while(true){
            Socket socket = serverSocket.accept();
            new Thread(() -> {
                while(true){
                    // 获取客户端输入流
                    try {
                        InputStream is = socket.getInputStream();
                        byte[] b = new byte[1024];
                        // 循环读取数据, read() 阻塞点
                        int data = is.read(b);
                        if (data != -1) {
                            String info = new String(b, 0, data, "GBK");
                            System.out.println(info);
                        }
                        PrintWriter os = new PrintWriter(socket.getOutputStream());
                        os.println(b);
                        os.flush();
                    } catch (IOException e) {
                        System.out.println(e);
                    }

                }
            }).start();
        }
    }
}
