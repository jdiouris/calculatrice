W=83;
L=121;
evis=3;
H=20;

$fn=100;
ep=3;

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
            ep=2;
            difference()
            {
            
            translate([-ep,-ep,0]) 
            minkowski()
            {
                cube([W+2*ep,L+2*ep,(H+5)/2]);
                cylinder(h=(H+5)/2,r=ep);
            }
            
            translate([0,0,H]) cube([W,L,10]);
            }
            sep=3;
        translate([evis-0.5,evis,0]) tube(H+sep,6,3);
        translate([W-evis+0.5,evis,0]) tube(H+sep,6,3);
        translate([W-evis+0.5,L-evis,0]) tube(H+sep,6,3);
        translate([evis-.5,L-evis,0]) tube(H+sep,6,3);
       
    
        }
        //cube([W,L+2,hmax+3]);
        ep=3;
        translate([2*ep,2*ep,+1]) cube([W-4*ep,L-2*ep,H+3]);
        translate([evis,evis,0]) cylinder(h=H+2,d=3);
        translate([W-evis,evis,0]) cylinder(h=H+2,d=3);
        translate([W-evis,L-evis,0]) cylinder(h=H+2,d=3);
        translate([evis,L-evis,0]) cylinder(h=H+2,d=3);
         translate([-10,L-36,H]) cube([20,20,10]);
    }
}

module dessous()
{
    difference()
    {
        translate([-ep,-ep,0])  cube([W+2*ep,L+2*ep,1.2]);
        translate([W/2,0,-1]) cylinder(h=10,d=4);
        translate([0,L-10,-1]) cylinder(h=10,d=4);
        translate([W,L-10,-1]) cylinder(h=10,d=4);
    }
    translate([5,0,-3]) cylinder(h=3,d=5);
    translate([W-5,0,-3]) cylinder(h=3,d=5);
     translate([5,L-5,-3]) cylinder(h=3,d=5);
    translate([W-5,L-5,-3]) cylinder(h=3,d=5);
}

//translate([0,0,-7])
//difference()
//{
//    rotate([3,0,0]) principal();
//    translate([-50,-10,-2]) cube([200,200,10]);
//    translate([W/2,0,7]) cylinder(h=10,d=4);
//    translate([0,L-10,7]) cylinder(h=10,d=4);
//    translate([W,L-10,7]) cylinder(h=10,d=4);
//    
//}

rotate([180,0,0]) 
   translate([0,0,-5]) dessous();
