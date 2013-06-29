import Control.Applicative
import Control.Arrow
import Control.Monad
import Control.Monad.State
import Data.Array
import Data.Array.IO
import Data.Bits hiding (rotate)
import qualified Data.ByteString.Char8 as B
import Data.Char
import Data.Maybe

data Queue a = Queue [a] [a] [a] deriving Show
data Op = Push Int Int | Pop Int deriving Show

empty = Queue [] [] []

rotate [] [r] s = r:s
rotate (f:fs) (r:rs) s = f:rotate fs rs (r:s)

queue fs rs [] = Queue fs' [] fs'
  where
    fs' = rotate fs rs []
queue fs rs (s:ss) = Queue fs rs ss

pop q@(Queue [] _ _) = (q, -1)
pop (Queue (f:fs) rs ss) = (queue fs rs ss, f)

push (Queue fs rs ss) x = queue fs (x:rs) ss

parse = do
  n <- readInt
  replicateM n $ do
    op <- readChar
    if op == 'a'
       then Push <$> readInt <*> readInt
       else Pop <$> readInt
  where
    readInt = state $ fromJust . B.readInt . B.dropWhile isSpace
    readChar = state $ (B.head &&& B.tail) . B.dropWhile isSpace

solve :: [Op] -> [Int]
solve ops = map snd . tail $ elems a
  where
    a = listArray (0, length ops) $ (Main.empty, -2) : map f ops
    f (Push p x) = (push (fst (a!p)) x, -2)
    f (Pop p) = pop . fst $ a!p

main = do
  ops <- evalState parse <$> B.getContents
  forM_ (solve ops) $ liftM2 when (/= (-2)) print
