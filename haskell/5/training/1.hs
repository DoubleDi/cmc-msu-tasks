type Gen = Int
type Dice = Int 

newtype Rand a = Rand 
    { getRand :: Gen -> (a, Gen) } deriving (Functor)

instance Functor Rand where
    fmap f (Rand r) = Rand (\g -> f (r g))

randInt:: Gen -> Int 
randInt = id

next :: Gen -> Gen
next g = g + 1 `mod` 10  

rand :: Rand Int
rand = Rand (\g -> (randInt g, next g))

dice :: Rand Dice
dice = fmap (\n -> 1 + n `mod` 6) rand 

apRand :: Rand(a -> b) -> Rand a -> Rand b
apRand (Rand rf) (Rand rx) = Rand(\g -> 
    let (f, g1) = rf g
        (x, g2) = rx g1
    in (f x, g2))
