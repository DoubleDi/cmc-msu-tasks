(defun pos (x l n)
    (cond ((null l)0)
          ((equal (car l) x)(+ n 1))
          (T(pos x (cdr l) (+ n 1)))))

(defun posit (x l) (pos x l 0))

(defun s() '(a))
(defun p() '(a (a b)))

(posit (s) (p))
