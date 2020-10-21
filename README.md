# Rieman-Hypothesis-Value-Generator
WARNING: Program creates several threads and will pin your CPU at 100% until it solves, I've designed it so that it stores all the values in a vector before outputing them to help speed things up (I could easily make this more effecient to conserve RAM but for the range of values I needed, and most people will need, the program only used ~700 MB of RAM so I didnt bother), so dont input very high values & accuracy levels. OR bypass this feature (should be pretty straight forward) and output to the file each itteration (Will slow you down if you are using an HDD).

Creates a map of the complex values that the Riemann Zeta function outputs for a given complex input in the critical strip (complex numbers with real value 0.5 and imaginary part within a range).

All the numbers are output to a text file, Have fun :)

Below is a snipet of what the output looks like, mind you this was taken form a file with over 2 million lines
///////////////////////////////////////////////

(0.000000,-100.000000)		(-6.801919,-2.577035)

(0.000000,-99.990000)		(-6.873489,-2.311642)

(0.000000,-99.980000)		(-6.933550,-2.043684)

(0.000000,-99.970000)		(-6.981989,-1.773755)

(0.000000,-99.960000)		(-7.018729,-1.502453)

(0.000000,-99.950000)		(-7.043730,-1.230379)

(0.000000,-99.940000)		(-7.056990,-0.958135)

(0.000000,-99.930000)		(-7.058540,-0.686322)


///////////////////////////////////////////////
