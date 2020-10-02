package Backjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main17136 {

	/*
	 * [백준] 색종이 붙이기
	 * 
	 * 1. 색종이를 가장 적게 붙일 수 있는 색종이수
	 * 
	 * 2. 무조건 10x10
	 * 
	 * 3. 완탐 dfs
	 */
	static int [][] map = new int[10][10];
    static int [] paper = {0, 5, 5, 5, 5, 5};
    static int ans = Integer.MAX_VALUE;
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        for(int i=0; i<10; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            for(int j=0; j<10; j++) {
            	map[i][j] = Integer.parseInt(st.nextToken());
            }
        }
        
        dfs(0, 0);
        
        System.out.println(ans==Integer.MAX_VALUE ? -1 : ans);
    }

	private static void dfs(int idx, int cnt) {
		if(idx == 100) {
			ans = ans>cnt? cnt : ans;
			return;
		}
		
		if(cnt > ans)return;
		
		int r = idx /10;
		int c = idx %10;
		
		if(map[r][c] == 1) {
			for (int i = 5; i > 0; i--) {
				if (paper[i] > 0 && chk(r, c, i)) {
					fill(r, c, i, 0);
					paper[i]--;
					dfs(idx + 1, cnt + 1);
					fill(r, c, i, 1);
					paper[i]++;
				}
			}
		}else dfs(idx+1, cnt);
		
	}

	private static void fill(int r, int c, int size, int num) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				map[r+i][c+j] = num;
			}
		}
	}

	private static boolean chk(int r, int c, int size) {
		if(r + size >10 || c + size > 10)return false;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if(map[r+i][c+j] ==0)return false;
			}
		}
		return true;
	}
}
