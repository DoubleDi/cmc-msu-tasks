(defun level (n S)
    (cond ((null S) S)
          ((= n 0)S)
          ((atom (car S))(level n (cdr S)))
          ((cons (level (- n 1)(car S))(level n (cdr S))))))


(defun p() '(((Z (Z) z) z (z))(z ())))
(defun q() '())

(Level 2 '(((A (5) 8) B) 7 (G (()))))
