package laboration0_system;

import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

class Switch extends JPanel {
	private JLabel title;
	private JCheckBox onOff;
	
	public Switch(int ledNbr) {
		this(ledNbr,false);
	}
	
	public Switch(int ledNbr, boolean selected) {
		setLayout(new GridLayout(2,1));
		setPreferredSize(new Dimension(60,60));
		title = new JLabel(""+ledNbr,JLabel.CENTER);
		onOff = new JCheckBox();
		onOff.setHorizontalAlignment(SwingConstants.CENTER);
		onOff.setSelected(selected);
		add(title);
		add(onOff);
	}
	
	public boolean isSelected() {
		return onOff.isSelected();
	}
}