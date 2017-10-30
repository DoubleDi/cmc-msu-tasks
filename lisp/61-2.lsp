(defun substt (a l e)
    (cond ((atom l)(cond ((equal l a)e)
                         (l)))
          ((cons (substt a (car l) e)(substt a (cdr l) e)))))


(defun p() '(((A (5) 8) B (K))(G (C))))
(defun q() '())

(substt 'Q '(Q (B (Q)) C ((Q) 8)) '(A Z))
