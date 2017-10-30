(defun makeset (l) (mkset l ()))
(defun mkset (l x)
    (cond ((null l)x)
          ((member (car l) x)(mkset (cdr l) x))
          ((mkset (cdr l)(cons (car l) x)))))


(defun p() '(a b c b c d))

(makeset (p))
