data Quad a = Quad a a a a
  deriving (Show)
type Point = (Float, Float)  
type Rect = (Point, Point)

-- | Квадрант.
data Quadrant a
  = Empty                     -- ^ Пустой квадрант.
  | Bucket a Point            -- ^ Квадрант, содержащий один объект.
  | Split (Quad (QuadTree a)) -- ^ Квадрант, разбитый на четыре подквадранта.
  deriving (Show)

-- | Дерево квадрантов.
data QuadTree a = QuadTree Rect (Quadrant a)
  deriving (Show)


instance Functor QuadTree where
    fmap f (QuadTree r Empty) = (QuadTree r Empty)
    fmap f (QuadTree r (Bucket a p)) = (QuadTree r (Bucket (f a) p))
    fmap f (QuadTree r (Split (Quad x y z t))) = (QuadTree r (Split (Quad (fmap f x) (fmap f y) (fmap f z) (fmap f t))))

main = print 1
