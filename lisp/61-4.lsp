(defun transs (n S)
    (cond ((null S) S)
          ((= n 0)(cond ((atom S)S)
                        (1)))
          ((cons (transs (- n 1)(car S))(transs n (cdr S))))))


(defun p() '(((Z (Z) z) z (z))(z ())))
(defun q() '())

(transs 2 '(((A(5)8)B(K))(G(C))))
