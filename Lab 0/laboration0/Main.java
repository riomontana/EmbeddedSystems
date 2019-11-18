package laboration0;

import laboration0_system.*;

public class Main {
	public static final int NBR_OF_BITS = 8;
	
	public static void main(String[] args) {
		new Controller(NBR_OF_BITS,
				       new Action[]{new ShowSwitchPanel()}, // I denna array lägger ni till Action-implementeringar
					   new BitHandler());
	}
}


class BitHandler implements BitConverter {
	public boolean[] intToArray(int state) {
		boolean[] result = new boolean[Main.NBR_OF_BITS];
		// komplettera med kod som fyller arrayen result med boolean-värden
		return result;
	}

	@Override
	public int arrayToInt(boolean[] switchState) {
		// komplettera med kod som skapar en int med hjälp av switchState
		return 0;
	}
	
}


class ShowSwitchPanel implements Action {
	public String getActionTitle() {
		return "Spegla";
	}

	public void action(Controller controller) {
		controller.setLeds(controller.getSwitchState());
	}
}

