eqLetters::[String]->Bool
eqLetters [] = True
eqLetters (l : ls) | l!!0 == (reverse l)!!0 = True && (eqLetters ls)
                   | otherwise = False


isChain::[String]->Bool
isChain [] = True
isChain [a] = True
isChain (x : (y : ys)) | (reverse x)!!0 == y!!0 = True && (isChain (y : ys))
                       | otherwise = False


pathLength::(Floating a) => [(a,a)] -> [a]
pathLength [] = []
pathLength [(x1,x2)] = []
pathLength ((x1, x2) : ((y1, y2) : ys)) = (d : (pathLength ((y1, y2) : ys))) where
 d = sqrt((x1 - y1) * (x1 - y1) + (x2 - y2) * (x2 - y2))

ordbyAge :: (Ord b) => [(String, b)] -> Bool
ordbyAge [] = True
ordbyAge [(s, x)] = True
ordbyAge ((s, x) : ((s1, y) : l)) | x < y = ordbyAge ((s1, y) : l)
                                 | otherwise = False

main = print (ordbyAge [("ann",25),("bob",31),("tom",61)] )
