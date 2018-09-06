import Data.Monoid

newtype AssocList k v = AssocList [(k,v)] deriving (Eq, Show)


instance Eq k => Monoid (AssocList k v) where
    mempty = AssocList []
    mappend (AssocList l) (AssocList r) = AssocList (l ++ (filter 
        (\(key,val) -> length (filter (isKey key) l) == 0) r))  
        where 
            isKey key (k,v) = k == key


main = print((AssocList [(1,2),(3,4)]) <> (AssocList [(1,3),(2,5)]))
