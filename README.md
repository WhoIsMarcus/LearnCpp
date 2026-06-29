This entire folder is just me learning how to use the basics of C++, The reason I decided to start learning this is because I want to make a tensor flow machine learning like bot, completly from scratch, and I will use python but it's slow so I am learning C++ to make functions which can be ran in python. I have heard that's what a lot of packages in python do.

Structure (For now):

the folder MainFiles contains all the files which I have deemed as fully fleshed out code, which is "ready" for deployment, I put ready in quotes because I am sure there's much I could fix. any other files contain "scratch work" and are all just for me to get the genral ideas down.


a lot of the math is based on how it is calculated in 3b1b "Backpropagation calculus | deep learning chapter 4" at ~4:17



∂c0 / ∂wL = ∂zL/∂wL * ∂aL/∂zL * ∂c0/∂aL
final     =    t1   *   t2    *   t3
 
y = desired output
aL = genrated output OR sigmoid(zL)
zL = wL * a(L-1) + bL
c0 = (aL - y)^2

t1 =a(L-1)
t2 = sigmoid'(zL)
t3 = 2(aL - y)


