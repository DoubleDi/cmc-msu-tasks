summ :: [Double] -> Double
summ [] = 0
summ (x:xs) = x + summ xs


sum2 :: [Double] -> Double
sum2 [] = 0
sum2 (x:xs) = x^2 + sum2 xs

sumWith :: (Double -> Double) -> [Double] -> Double
sumWith _ [] = 0
sumWith f (x:xs) = f x + sumWith f xs
-- id 
-- (\x -> 1)

sumWith2 :: (Double -> Double) -> [Double] -> Double
sumWith2 _ [] = 0
sumWith2 f l = sum (map f l)

sumWith3 :: (Double -> Double) -> [Double] -> Double
sumWith3 f = sum . map f

mymap :: (a -> b) -> [a] -> [b]
mymap _ [] = []
mymap f (x:xs) = f x : (map f xs)

lengths :: [String] -> [Int]
lengths = map length

 
main = print (lengths ["aaaa", "bbb", "cccc"]) 
