(defun fact (n)
    (cond ((= n 0)())
          ((= n 1)(cons n (fact (- n 1))))
          ((cons n (cons '* (fact (- n 1)))))))


(defun p() '2)

(fact (p))
