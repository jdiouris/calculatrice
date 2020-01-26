$fn=100;
H=6;
D=3.5;
e=1;

difference()
{
    cylinder(h=H,d=D+2*e);
    cylinder(h=H+2,d=D);
}