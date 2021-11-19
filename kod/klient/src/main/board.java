package main;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class board extends JPanel {
    private BufferedImage B;
    private BufferedImage T;
    private BufferedImage[] WF;
    private BufferedImage[] BF;
    private char[][][] chess;
    private char Color;
    private char Active;
    private InputStream IS;
    private OutputStream OS;

    public board(Socket CS) {
        super();
        chess = new char[2][8][8];
        try {
            this.IS = CS.getInputStream();
            this.OS = CS.getOutputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            this.setVisible(true);
            B = ImageIO.read(getClass().getResource("/images/board.png"));
            T = ImageIO.read(getClass().getResource("/images/target.png"));
            WF = new BufferedImage[6];
            WF[0] = ImageIO.read(getClass().getResource("/images/W_PAWN.png"));
            WF[1] = ImageIO.read(getClass().getResource("/images/W_ROOK.png"));
            WF[2] = ImageIO.read(getClass().getResource("/images/W_BISHOP.png"));
            WF[3] = ImageIO.read(getClass().getResource("/images/W_KNIGHT.png"));
            WF[4] = ImageIO.read(getClass().getResource("/images/W_QUEEN.png"));
            WF[5] = ImageIO.read(getClass().getResource("/images/W_KING.png"));
            BF = new BufferedImage[6];
            BF[0] = ImageIO.read(getClass().getResource("/images/B_PAWN.png"));
            BF[1] = ImageIO.read(getClass().getResource("/images/B_ROOK.png"));
            BF[2] = ImageIO.read(getClass().getResource("/images/B_BISHOP.png"));
            BF[3] = ImageIO.read(getClass().getResource("/images/B_KNIGHT.png"));
            BF[4] = ImageIO.read(getClass().getResource("/images/B_QUEEN.png"));
            BF[5] = ImageIO.read(getClass().getResource("/images/B_KING.png"));
        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, "Błąd wczytania obrazów");
        }
        this.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e){
                if (Color == Active){
                    try {
                        OS.write(String.format("%d-%d",e.getX()/100, e.getY()/100).getBytes());
                    } catch (IOException ex) {
                        JOptionPane.showMessageDialog(null, "Bład połączenia z serwerem");
                    }
                }
            }
        });
    }

    public char load() throws IOException {
        int c = 0;
        byte[] data = new byte[130];
        this.IS.read(data);
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++){
                    this.chess[k][j][i] = (char) data[c];
                    c += 1;
                }
            }
        }
        this.Active = (char) data[c];
        return  (char) data[c+1];
    }

    public void send(String S) throws IOException {
        this.OS.write(S.getBytes());
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        char f;
        g.drawImage(this.B,0,0,null);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (this.chess[1][i][j] == 'a') g.drawImage(this.T,i*100,j*100,null);
                f = this.chess[0][i][j];
                switch (f) {
                    case 'p' -> g.drawImage(this.WF[0], i * 100, j * 100, null);
                    case 'r' -> g.drawImage(this.WF[1], i * 100, j * 100, null);
                    case 'b' -> g.drawImage(this.WF[2], i * 100, j * 100, null);
                    case 'h' -> g.drawImage(this.WF[3], i * 100, j * 100, null);
                    case 'q' -> g.drawImage(this.WF[4], i * 100, j * 100, null);
                    case 'k' -> g.drawImage(this.WF[5], i * 100, j * 100, null);
                    case 'P' -> g.drawImage(this.BF[0], i * 100, j * 100, null);
                    case 'R' -> g.drawImage(this.BF[1], i * 100, j * 100, null);
                    case 'B' -> g.drawImage(this.BF[2], i * 100, j * 100, null);
                    case 'H' -> g.drawImage(this.BF[3], i * 100, j * 100, null);
                    case 'Q' -> g.drawImage(this.BF[4], i * 100, j * 100, null);
                    case 'K' -> g.drawImage(this.BF[5], i * 100, j * 100, null);
                }
            }
        }
    }

    public void setColor(char color) {
        Color = color;
    }

    public char getActive() {
        return Active;
    }
}
