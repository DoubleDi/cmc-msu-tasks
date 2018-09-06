import Data.Monoid

data Is a = Is { getMaybe :: Maybe a }

instance Eq a => Monoid (Is a) where 
    mempty = Is Nothing
    mappend l (Is Nothing) = l
    mappend (Is Nothing) r = r
    mappend (Is (Just x)) (Is (Just y)) 
        | x == y = Is (Just x)
        | otherwise = Is Nothing

myfind :: (Monoid a, Foldable t) => (a -> Bool) -> t a -> Maybe a
myfind f mempty = Nothing
myfind f as = getMaybe (foldMap (\x -> if f x then (Is (Just x)) else (Is Nothing)) as)

main = print (myfind (==3) [1,2,3,4])
