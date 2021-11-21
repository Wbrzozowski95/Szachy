package main;

import javax.swing.*;
import java.io.IOException;
import java.net.Socket;

public class game implements Runnable{
    private JFrame frame;
    private JPanel menu;
    private JPanel boardpanel;
    private JPanel Chessboard;
    private JTextField ColortextField;
    private JTextField ActivetextField;
    private JTextField twójKolorTextField;
    private JTextField wykonujeRuchTextField;
    private board B;

    public game(Socket CS, JFrame F, JPanel P){
        this.frame = F;
        this.menu = P;
        this.B = new board(CS);
        this.Chessboard.add(this.B);
    }

    @Override
    public void run() {
        boolean play = true;
        char S;
        frame.setContentPane(this.boardpanel);
        frame.pack();
        while (play){
            try {
                S = B.load();
                switch (S){
                    case 'W':
                        B.setColor('W');
                        this.ColortextField.setText("Biały");
                        break;
                    case 'B':
                        B.setColor('B');
                        this.ColortextField.setText("Czarny");
                        break;
                    case 'S':
                        if (B.getActive() == 'W') this.ActivetextField.setText("Biały");
                        else this.ActivetextField.setText("Czarny");
                        break;
                    case 'C':
                        choice C = new choice(B.getColor());
                        JOptionPane.showMessageDialog(null, C.getMain(), "Zmiana figury", JOptionPane.PLAIN_MESSAGE);
                        B.send(C.getSelect());
                        break;
                    case 'V':
                        play = false;
                        JOptionPane.showMessageDialog(null,"Wygrałeś");
                        break;
                    case 'L':
                        play = false;
                        JOptionPane.showMessageDialog(null,"Przegrałeś");
                        break;
                }
                frame.repaint();
            } catch (IOException e) {
                JOptionPane.showMessageDialog(null,"Bląd połączenia");
            }
        }
        this.frame.setContentPane(this.menu);
        this.frame.pack();
    }
}
