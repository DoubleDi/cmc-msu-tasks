(defun bubl (n a)
    (cond ((= n 0)a)
          ((list (bubl (- n 1) a)))))


(defun p() '(a (b) c))
(bubl 1 5)
