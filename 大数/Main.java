import java.io.*;

import java.math.*;

import java.util.*;

import java.text.*;

public class Main

{

	public static void main(String[] args)

	{

		Scanner cin = new Scanner (new BufferedInputStream(System.in));
		
		int t=1;

		while(true)
		
		{
			

			BigInteger x, y, z;

			x = cin.nextBigInteger();

			if(x%73==0||x%137==0) System.out.println("Case #"+t+":YES");
else System.out.println("Case #"+t+":NO");
	
		}

	}

}
