## n-cnc-v1-xy general-purpose manufacturing machine

arduino mega + ramps 1.4 + tb6600 drivers + nema 23 stepper motors

#x-axis (ramps 1.4)             

  x       x       x       x       x       x       x       x       

         gnd                                             gnd



  x       x       x       x       x       x       x       x       

 ena                                            step     dir
 
 

TB6600-x

[signal]

ena -       >>>   gnd x-axis 
ena + 5v    >>>   ena x-axis
dir -       >>>   gnd x-axis
dir + 5v    >>>   dir x-axis (white wire)
pul -       >>>   gnd
pul + 5v    >>>   step x-axis (gray wire)

[high voltage]

b-  >>> nema 23 b- coil
b+  >>>  nema 23 b+ coil
a-  >>>  nema 23 a- coil
a+  >>>  nema 23 a+ coil
gnd >>>  gnd supply 
vcc >>>  +24v supply

#y-axis (ramps 1.4)             

  y       y       y       y       y       y       y       y       

         gnd                                             gnd



  y       y       y       y       y       y       y       y       

 ena                                            step     dir
 
 

TB6600-y

[signal]

ena -       >>>   gnd y-axis 
ena + 5v    >>>   ena y-axis
dir -       >>>   gnd y-axis
dir + 5v    >>>   dir y-axis (white wire)
pul -       >>>   gnd
pul + 5v    >>>   step y-axis (gray wire)

[high voltage]

b-  >>> nema 23 b- coil
b+  >>>  nema 23 b+ coil
a-  >>>  nema 23 a- coil
a+  >>>  nema 23 a+ coil
gnd >>>  gnd supply 
vcc >>>  +24v supply

#z-axis (ramps 1.4)             

  z       z       z       z       z       z       z       z       

         gnd                                             gnd



  z       z       z       z       z       z       z       z       

 ena                                            step     dir
 
 

TB6600-z

[signal]

ena -       >>>   gnd z-axis 
ena + 5v    >>>   ena z-axis
dir -       >>>   gnd z-axis
dir + 5v    >>>   dir z-axis (white wire)
pul -       >>>   gnd
pul + 5v    >>>   step z-axis (gray wire)

[high voltage]

b-  >>> nema 23 b- coil
b+  >>>  nema 23 b+ coil
a-  >>>  nema 23 a- coil
a+  >>>  nema 23 a+ coil
gnd >>>  gnd supply 
vcc >>>  +24v supply

