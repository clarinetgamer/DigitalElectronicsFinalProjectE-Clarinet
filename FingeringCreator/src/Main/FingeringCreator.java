package Main;

import java.util.Scanner;

public class FingeringCreator {

	// Back of instrument
	boolean registerKey = false;
	boolean thumbKey = false;
	// Left of Instrument
	boolean leftSideKey = false;
	// Top Half of Instrument
	boolean aKey = false;
	boolean oneKey = false;
	boolean twoKey = false;
	boolean bananaTopKey = false;
	boolean threeKey = false;
	boolean cSharpKey = false;
	boolean leftPinkyExt1 = false;
	boolean leftPinkyExt2 = false;
	boolean leftPinkyExt3 = false;
	// Right side of instrument
	boolean sideKey1 = false;
	boolean sideKey2 = false;
	boolean sideKey3 = false;
	boolean sideKey4 = false;
	// Bottom Half of Instrument
	boolean fourKey = false;
	boolean fiveKey = false;
	boolean bananaLowKey = false;
	boolean sixKey = false;
	boolean ebKey = false;
	boolean rightPinky1 = false;
	boolean rightPinky2 = false;
	boolean rightPinky3 = false;

	public boolean inputToBool(String print) {
		Scanner input = new Scanner(System.in);
		System.out.println(print+":");
		String s = input.nextLine();
		if (s.contains("t")) {
			return true;
		} else {
			return false;
		}
	}
	
	public void askUser() {
		registerKey = inputToBool("registerKey");
		thumbKey = inputToBool("thumbKey");
		// Left of Instrument
		leftSideKey = inputToBool("leftSideKey");
		// Top Half of Instrument
		aKey = inputToBool("aKey");
		oneKey = inputToBool("oneKey");
		twoKey = inputToBool("twoKey");
		bananaTopKey = inputToBool("bananaTopKey");
		threeKey = inputToBool("threeKey");
		cSharpKey = inputToBool("cSharpKey");
		leftPinkyExt1 = inputToBool("leftPinkyExt1");
		leftPinkyExt2 = inputToBool("leftPinkyExt2");
		leftPinkyExt3 = inputToBool("leftPinkyExt3");
		// Right side of instrument
		sideKey1 = inputToBool("sideKey1");
		sideKey2 = inputToBool("sideKey2");
		sideKey3 = inputToBool("sideKey3");
		sideKey4 = inputToBool("sideKey4");
		// Bottom Half of Instrument
		fourKey = inputToBool("fourKey");
		fiveKey = inputToBool("fiveKey");
		bananaLowKey = inputToBool("bananaLowKey");
		sixKey = inputToBool("sixKey");
		ebKey = inputToBool("ebKey");
		rightPinky1 = inputToBool("rightPinky1");
		rightPinky2 = inputToBool("rightPinky2");
		rightPinky3 = inputToBool("rightPinky3");
	}

	public boolean[] createFingeringArr() {
		return new boolean[] { registerKey, thumbKey, leftSideKey, aKey, oneKey, twoKey, bananaTopKey, threeKey,
				cSharpKey, leftPinkyExt1, leftPinkyExt2, leftPinkyExt3, sideKey1, sideKey2, sideKey3, sideKey4, fourKey,
				fiveKey, bananaLowKey, sixKey, ebKey, rightPinky1, rightPinky2, rightPinky3 };

	}

	public static void main(String[] args) {
		FingeringCreator fc = new FingeringCreator(); //Creates to FingeringCreator Object
		fc.askUser(); //Ask user input for t or f for whether button is pressed for that finger
		//Display array to be copied into doc
		System.out.print("{");
		boolean[] arr = fc.createFingeringArr();
		for(int i = 0; i < arr.length; i++) {
			System.out.print(arr[i]);
			if(i != arr.length-1) {
				System.out.print(",");
			}
		}
		System.out.print("},");

	}

}
