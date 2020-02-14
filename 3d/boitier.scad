W=82;
L=120;
evis=3;
H=15;

$fn=100;
ep=5;

module tube(H,D1,D2)
{
    difference()
    {
        cylinder(h=H,d=D1);
         cylinder(h=H+2,d=D2);
    }
}

module principal()
{
    difference()
    {
        union()
        {
        //rotate([-90,0,0]) cylinder(h=L,d=2*hmax);
        //translate([W,0,0]) rotate([-90,0,0]) cylinder(h=L,d=2*hmax)
        translate([-ep,-ep,0]) cube([W+2*ep,L+2*ep,H]);
        translate([evis,evis,0]) tube(H+2,6,3);
        translate([W-evis,evis,0]) tube(H+2,6,3);
        translate([W-evis,L-evis,0]) tube(H+2,6,3);
        translate([evis,L-evis,0]) tube(H+2,6,3);
    
        }
        //cube([W,L+2,hmax+3]);
        translate([ep,ep,-1]) cube([W-2*ep,L-2*ep,H+3]);
        translate([evis,evis,0]) cylinder(h=H+2,d=3);
        translate([W-evis,evis,0]) cylinder(h=H+2,d=3);
        translate([W-evis,L-evis,0]) cylinder(h=H+2,d=3);
        translate([evis,L-evis,0]) cylinder(h=H+2,d=3);
    }
}

difference()
{
    principal();
    //translate([-50,0,-hmax-3]) cube([W+100,L+2,hmax+3]);
}