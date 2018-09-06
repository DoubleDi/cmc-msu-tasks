data Tree a = Leaf | Node a (Tree a) (Tree a) deriving (Show)

search :: Ord a => a -> Tree a -> Bool
search _ Leaf = False 
search x (Node y l r)
    | x == y = True
    | x < y = search x l
    | otherwise = search x r

insert :: Ord a => a -> Tree a -> Tree a
insert x Leaf = (Node x Leaf Leaf)
insert x (Node y l r) 
    | x < y = (Node y (insert x l) r)
    | otherwise = (Node y l (insert x r))  

getMaxVal :: Ord a => Tree a -> a
getMaxVal (Node x _ Leaf) = x
getMaxVal (Node x _ r) = getMaxVal r

deleteMax :: Ord a => Tree a -> Tree a
deleteMax (Node x _ Leaf) = Leaf
deleteMax (Node x _ r) = deleteMax r

-- delete :: Ord a => a -> Tree a -> Tree a
-- delete _ Leaf = Leaf
-- delete x (Node y l Leaf)
--     | x < y = (Node y (delete x l) Leaf) 
--     | x > y = (Node y l Leaf)
--     | otherwise = l
-- delete x (Node y l r)
--     | x < y = (Node y (delete x l) r) 
--     | x > y = (Node y l (delete x r))
--     | otherwise = (Node (getMaxVal r) l (deleteMax r))

isLeaf :: Tree a -> Bool
isLeaf Leaf = True
isLeaf _ = False

delete :: Ord a => a -> Tree a -> Tree a
delete x Leaf = Leaf
delete x (Node y l r)
    | x < y = (Node y (delete x l) r) 
    | x > y = (Node y l (delete x r))
    | isLeaf r = l
    | otherwise = (Node (getMaxVal r) l (deleteMax r))
 
main = print (delete 6 (Node 6 (Node 5 Leaf Leaf) Leaf)) 
