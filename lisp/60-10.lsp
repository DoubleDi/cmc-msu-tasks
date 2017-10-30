(defun elem (n l)
    (cond ((null l)nil)
          ((= n 1)(car l))
          ((elem (- n 1)(cdr l)))))

(defun p() '(a (a b) (a (b b b))))

(elem 4 (p))
