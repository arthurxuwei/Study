maximum' :: (Ord a) => [a] -> a 
maximum' [] = error "maximum of empty list" 
maximum' [x] = x
maximum' (x:xs) = max x (maximum' xs) 

applyTwice' :: (a -> a) -> a -> a
applyTwice' f x = f (f x)

zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith' _ [] _ = []
zipWith' _ _ [] = []
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys