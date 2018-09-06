myfilter :: (a -> Bool) -> [a] -> [a]
myfilter f = foldr (\a b -> if f a then (a : b) else b) []
 
main = print (myfilter (>4) [1,2,3,4,5,6,7,8,7,6,5,4,3,21,1]) 
