(defun rightbr (l)
    (cond ((null l) ())
          ((null (cdr l)) (list (car l)))
          (T(list (car l) (rightbr (cdr l))))))
(defun p() '(a b c))

(rightbr (p))
