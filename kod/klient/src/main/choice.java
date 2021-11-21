package main;

import javax.swing.*;

public class choice {
    private JRadioButton QRadioButton;
    private JRadioButton HRadioButton;
    private JRadioButton RRadioButton;
    private JRadioButton BRadioButton;
    private JPanel main;
    private ButtonGroup BG;

    public choice(char C) {
        if(C == 'W'){
            QRadioButton.setIcon(new ImageIcon(getClass().getResource("/images/W_QUEEN.png")));
            HRadioButton.setIcon(new ImageIcon(getClass().getResource("/images/W_KNIGHT.png")));
            RRadioButton.setIcon(new ImageIcon(getClass().getResource("/images/W_ROOK.png")));
            BRadioButton.setIcon(new ImageIcon(getClass().getResource("/images/W_BISHOP.png")));
        }
        if(C == 'B'){
            QRadioButton.setIcon(new ImageIcon(getClass().getResource("/images/B_QUEEN.png")));
            HRadioButton.setIcon(new ImageIcon(getClass().getResource("/images/B_KNIGHT.png")));
            RRadioButton.setIcon(new ImageIcon(getClass().getResource("/images/B_ROOK.png")));
            BRadioButton.setIcon(new ImageIcon(getClass().getResource("/images/B_BISHOP.png")));
        }
        BG = new ButtonGroup();
        BG.add(QRadioButton);
        BG.add(HRadioButton);
        BG.add(RRadioButton);
        BG.add(BRadioButton);
    }

    public JPanel getMain() {
        return main;
    }

    public String getSelect() {
        return  BG.getSelection().getActionCommand();
    }
}

