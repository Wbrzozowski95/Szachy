package main;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.Socket;

public class start {
    private static JFrame frame;
    private JTextField Address;
    private JPanel startpanel;
    private JButton exitButton;
    private JButton startButton;
    private JTextField FieldName;
    private game B;
    private Thread thread;

    public void createboard(){
        try {
            Socket CS = new Socket(Address.getText(),1234);
            B = new game(CS, frame, this.startpanel);
            thread = new Thread(B);
            thread.start();

        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, "Nie udalo sie polaczyc z serwerem.\n Prosze sprubowac pozniej.");
        }
    }

    public start() {
        startButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                createboard();
            }
        });
        exitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });
    }

    public static void main(String[] args) {
        start S = new start();
        frame = new JFrame("app");
        frame.setContentPane(S.startpanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }
}
