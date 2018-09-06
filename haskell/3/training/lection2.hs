data Mark = X | O

instance Eq Mark where
    X == X = True
    O == O = True
    _ == _ = False

instance Eq a => Eq [a] where
    [] == [] = True
    (x:xs) == (y:ys) = (x == y) && (xs == ys)
    _ == _ = False 


main = print (myfilter (>4) [1,2,3,4,5,6,7,8,7,6,5,4,3,21,1]) 
