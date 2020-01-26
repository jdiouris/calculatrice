# draw_lines.py
 
from fpdf import FPDF

def draw_key(pdf,x,y,s1,s2,s3):
    pdf.rect(x,y,5,3)
    pdf.set_text_color(0,0,0)
    pdf.text(x+2.5-len(s1)*2/2,y-1,s1)
 

    
##    pdf.line(10, 10, 10, 100)
##    pdf.set_line_width(1)
##    pdf.set_draw_color(255, 0, 0)
##    pdf.line(20, 20, 100, 20)
    
 
if __name__ == '__main__':
    pdf = FPDF()
    pdf.set_font('Arial', 'B', 8)
    pdf.add_page()
    draw_key(pdf,100,100,'COS','','')
    pdf.output('masque.pdf')
