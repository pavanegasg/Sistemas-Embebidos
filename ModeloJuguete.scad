
 
 difference(){  
difference()  {sphere(6,$fn=100); translate([0,-6,0])cube(12, center=true);}
sphere(5.8, $fn=100);
 
 }
 
 difference(){
 translate([0,5.6,0])
 rotate([90,90,0])

cylinder(r=1.45, h=2,$fn=100);
translate([0,6,0])
 rotate([90,90,0]){
cylinder(r=1.25, h=5,$fn=100);}
 
}
