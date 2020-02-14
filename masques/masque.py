# draw_lines.py
 
from fpdf import FPDF

def draw_key(pdf,x,y,s1,s2,s3):
    wb=6.7+1
    hb=3.7+1
    pdf.rect(x,y,wb,hb)
    pdf.set_text_color(0,0,0)
    pdf.text(x+wb/2-len(s1)*1.9*6/8/2,y-0.5,s1)
    pdf.set_text_color(0,0,255)
    pdf.text(x+1-4,y-3,s2)
    pdf.set_text_color(255,0,0)
    pdf.text(x+wb-1,y-3,s3)
 

    
##    pdf.line(10, 10, 10, 100)
##    pdf.set_line_width(1)
##    pdf.set_draw_color(255, 0, 0)
##    pdf.line(20, 20, 100, 20)

xs=15.25
ys=10.58

W=82
H=72

x0=5;
y0=3;

centre1=["Shift", "Alpha", "USER", "Up", "EDIT"]
centre2=["ARC", "STO", "<-", "'", "->"]
centre3=["COS", "SIN", "TAN", "Down", "del"]
centre4=["ENTER", "7", "8", "9", "/"]
centre5=["E", "4", "5", "6", "*"]
centre6=[".", "1", "2", "3", "-"]
centre7=["c", "0", ".", "spc", "+"]

right1=["", "", "", "", ""]
right2=["A", "B", "", "C", ""]
right3=["D", "E", "F", "", ""]
right4=["G", "H", "I", "J", "K"]
right5=["L", "M", "N", "O", "P"]
right6=["Q", "R", "S", "T", "U"]
right7=["V", "W", "X", "Y", "Z"]

left1=["", "", "", "", ""]
left2=["IF", "FOR", "WHILE", "DO", "END"]
left3=["STEP", "INP", "DISP", "WHO", "PI"]
left4=["COMP", "1/X", "LN", "SQ", "SQRT"]
left5=["LOG", "10^x", "y^x", "DUP", "SWAP"]
left6=["DROP", "MATH", "VAR", "", "FACT"]
left7=["OFF", "[", "<", ">", "="]

centre=centre1+centre2+centre3+centre4+centre5+centre6+centre7
right=right1+right2+right3+right4+right5+right6+right7
left=left1+left2+left3+left4+left5+left6+left7


 
if __name__ == '__main__':
    pdf = FPDF()
    pdf.set_font('Arial', 'B', 8)
    pdf.add_page()
    pdf.rect(10,10,W,H)
    for i in range(0,7):
        for j in range(0,5):
            draw_key(pdf,10+x0+j*xs,10+y0+i*ys,centre[j+i*5],left[j+i*5],right[j+i*5])
    pdf.output('masque.pdf')
