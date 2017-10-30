(defun onlyz (l)
    (cond ((atom l)(cond ((eql l 'z)T)
                         ((null l)T)
                         (nil)))
          ((and (onlyz (car l))(onlyz (cdr l))))))


(defun p() '(((Z (Z) z) z (z))(z ())))
(defun q() '())

(onlyz (p))
