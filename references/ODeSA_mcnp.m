c ----------------------------------------------------------------------------
c    MC-Model for ODeSA
c
c     - Michael Febbraro, Rebecca Toomey
c     - Mar 25, 2019
c     - Nuclear Astrophysics, ORNL
c
c   Description of simulation:
c
c    Materials defined by 'Compendium of Material Composition Data for
c         Radiation Transport Modeling', R.J. McConn Jr., et al.,
c         PNNL-15870 Rev. 1, PIET-43741-TM-963, March 4, 2011
c
c ----------------------------------------------------------------------------
c CELL CARDS
c Can 
100 3 -8 (-104 102 -103 ):(104 100 -101 -107 ):(107 105 -106 -108 )
c Liquid
103 5 -0.954 (104 -107 -109 ):(111 -108 -104 ):(107 104 -110 -108 )
c Teflon
104 3 -5 (-104 103 -111 ):(104 -100 109 -107 ):(107 110 -105 110 -108 )
c Mounting flange
201 1 -2.7 (200 -201 212 -108 ):(-206 207 -203 108 ):
           (208 -207 108 -205 ):(-203 301 -300 206 )
c Glass window                                                                  
202     4   -2.23 -207 205 -206 
c Rest of universe -----------------------------------------------------------
900     0         -900 #100 #103 #104 #201 #202
901     0         900 
c END CELL CARD - BLANK LINE FOLLOWS

c units [cm] energy [MeV] time [shakes] temp [MeV] atom rho [b-1 cm-1]
c mass density [g cm3] x-section [b]
c SURFACE CARDS
c ODeSA cell -----------------------------------------------------------------
c Can ------------------------------------------------------------------------
100        tz 0 0 0.475 3.176 0.396 0.396  $ Inner torus
101        tz 0 0 0.475 3.176 0.475 0.475  $ Outer torus
102        pz 0                            $ Top outer surface
103        pz 0.079                        $ Top inner surface
c          cz cylinder || to z-axis
104        cz 3.176                        $ Torus cyl cut 
105        cz 3.572                        $ Inner cylinder
106        cz 3.651                        $ Outer cylinder
107        pz 0.475                        $ Torus z cut
108        pz 5.715                        $ Lower edge
109 TZ 0 0 0.475 3.176 0.317 0.317         $ Teflon torus
110 CZ 3.493                               $ Teflon cyl
111 PZ 0.158                               $ Teflon cut
c Mounting Flange ------------------------------------------------------------
200 PZ 4.445                               $ Upper edge
201 CZ 3.810                               $ Can side outer cyl
c can limit = can lower edge = 108
203 CZ 4.603                               $ PMT side outer cyl
204 CZ 3.569                               $ PMT side inner cyl
205 PZ 6.032                               $ Window limit cut
206 PZ 6.350                               $ Flange lower edge
207 CZ 3.873                               $ Window cut cyl outer
208 CZ 3.569                               $ Window cut cyl inner
c expnsion port upper edge = flange upper edge = 200
c expansion port lower edge = can limit = 106
c curved outer edges = 203, 201
209 PX 0.635                               $ Expansion port side
210 PX -0.635                              $ Expansion port side
211 C/Y 0 5.080 0.423                      $ Expansion port hole
212 CZ 3.658                               $ Can side inner cyl
c Borosilicate window --------------------------------------------------------
c upper = window limit = 205
c lower = flange lower edge = 206
c cylinder = window cut cyl outer = 207
c PMT collar -----------------------------------------------------------------
c collar upper edge = flange lower edge = 206
300 PZ 9.525                               $ Collar lower edge
c collar outer cyl = PMT side outer = 203
301 CZ 4.100                               $ Collar inner cyl
c Expansion port -------------------------------------------------------------
500 C/Y 0 5.080 0.241                      $ Horizontal flow hole
501 C/Y 0 5.080 0.521                      $ NPT section
502 PX 0.508                               $ Vertical cut, NPT to swagelok
503 C/Y 0 5.080 0.635                      $ Horizontal outer swagelok
504 C/Z 6.001 0 0.241                      $ Vertical flow hole
505 C/Z 6.001 0 0.634                      $ Vertical outer swagelok
506 PZ 6.248                               $ Horizontal swagelok nut cut
507 C/Z 6.001 0 0.826                      $ Swagelok nut
508 PZ 7.772                               $ Lower swagelok nut cut
509 C/Z 6.001 0 0.318                      $ 1/4 pipe outer
510 C/Z 6.001 0 0.236                      $ 1/4 pipe inner
511 PZ 7.137                               $ Upper pipe cut
512 PZ 17.297                              $ Lower pipe cut
513 PZ 16.662                              $ Upper nut cut
c inner nut hole = 1/4 pipe outer = 509
514 C/Z 6.001 0 0.826                      $ Nut outer cyl
515 PZ 17.932                              $ Lower nut cut
516 C/Z 6.001 0 0.737                      $ Nut stopper cyl
517 PZ 19.00                               $ Nut stopper lower cut
c Rest of universe -----------------------------------------------------------
900 box -100 -100 -100 200 0 0 0 200 0 0 0 200
c END SURFACE CARD - BLANK LINE FOLLOWS

c MATERIAL SPECIFICATION
M1   12000              -0.010000     $ Aluminum, Alloy 6061-O 2.7
        13027           -0.972000
        14000           -0.006000
        22000           -0.000880
        24000           -0.001950
        25055           -0.000880
        26000           -0.004090
        29000           -0.002750
        30000           -0.001460
M2   6000               -0.000400     $ 304 Stainless Steel 8.00
        14000           -0.005000
        15031           -0.000230
        16000           -0.000150
        24000           -0.190000
        25055           -0.010000
        26000           -0.701730
        28000           -0.092500
M3   6000               -0.000124     $ Air 0.001205
        7014            -0.755268
        8016            -0.231781
        18000           -0.012827
M4   5011               -0.040064     $ Borosilicate Glass 2.23
        8016            -0.539562 
        11023           -0.028191 
        13027           -0.011644 
        14000           -0.377220 
        19000           -0.003321
M5   1002               0.496         $ EJ-315 0.954
        1001            0.004
        6000            0.501
M6   6000               -0.240183     $ PTFE 2.25
        9019            -0.759818
c VARIANCE REDUCTION
imp:n 1 5r 0
imp:p 1 5r 0
c SOURCE SPECIFICATION
SDEF ERG=2.5 POS=0 0 -1 AXS= 0 0 1 RAD=d1 PAR=1 DIR=1 VEC=0 0 1
SI1 0 5.0  $ radial sampling range: 0 to Rmax
SP1 -21 1  $ radial sampling weighting: r^1 for disk source.
c TALLY SPECIFICATION
c DATA CARDS
mode n p
NPS  1E7
PHYS:N J 20.
PHYS:P 0 1 1
c The following CUT cards kill neutrons and photons having times 
c exceeding 200 ns after the originating source event
CUT:N 20     
CUT:P 2J 0
c TALLY SPECIFICATION
c MCNPX-POLIMI SPECIFICATION
IDUM 0 0 0 0 2J 1 103 $ Collisional data output
FILES 21 DUMN1    3J 22 DUMN2
