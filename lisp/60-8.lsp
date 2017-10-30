(defun mix1 (l x)
    (cond ((null l)x)
          ((null x)l)
          ((append (list (car l) (car x)) (mix1 (cdr l) (cdr x))))))


(defun p() '())
(defun q() '())

(mix1 (p) (q))
