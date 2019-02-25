package dp;

/**
 * 
 * Solve Longest common subsequence(LCS) problem by Dynamic Programming
 * 
 *         |=  0                             When i = 0 or j = 0
 * C[i, j] |=  c[i - 1, j - 1] + 1           When i,j > 0 and xi = yj
 *         |= max(c[i, j - 1], c[i - 1, j])  When i,j > 0 and xi != yj
 *         
 *  according <<Introduction to Algorithms>>
 *  
 */        

public class LCS {

		public int[][] LCSLength(String s1, String s2) {
			char[] x = s1.toCharArray();
			char[] y = s2.toCharArray();
					
			int m = x.length + 1;
			int n = y.length + 1;
			int i, j;
			int[][] c = new int[m][n];
			int[][] b = new int[m][n];

			for (i = 1; i < m; i++) {
				c[i][0] = 0;
			}
			for (j = 0; j < n; j++){
				c[0][j] = 0;
			}
			
			for (i = 1; i < m; i++)
				for (j = 1; j < n; j++)
					if(x[i - 1] == y[j - 1]) {
						c[i][j] = c[i - 1][j - 1] + 1;
						b[i][j] = 1;
					} else if (c[i - 1][j] >= c[i][j - 1]) {
						c[i][j] = c[i - 1][j];
						b[i][j] = 2;
					} else {
						c[i][j] = c[i][j - 1];
						b[i][j] = 3;
					}
			
			return b;
		}
		
		public void printLCS(int[][] b, String s, int i, int j) {
			
			if (i == 0 || j == 0) {
				return;
			}
			if (b[i][j] == 1) {
				printLCS(b, s, i - 1, j - 1);
				System.out.print(s.charAt(i - 1));
			} else if (b[i][j] == 2) {
				printLCS(b, s, i - 1, j);
			} else {
				printLCS(b, s, i, j - 1);
			}
		}
		
		public static void main(String[] argv) {
			LCS algorithm = new LCS();
			
			String x = "ABCBDAB";
			String y = "BDCABA";
			
			algorithm.printLCS(algorithm.LCSLength(x, y), x, x.length(), y.length());
		}
}
