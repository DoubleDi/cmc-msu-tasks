(defun onelevel (l)
    (cond ((null l)T)
          ((and (atom (car l)) (onelevel (cdr l))))))


(defun p() '(a (b) c))
(onelevel (p))
