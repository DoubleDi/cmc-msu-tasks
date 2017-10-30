(defun depth (l)
    (cond ((atom l)0)
          ((max (+ 1 (depth (car l))) (depth (cdr l))))))


(defun p() '(((A (5) 8) B (K))(G (C))))
(defun q() '())

(depth (p))
