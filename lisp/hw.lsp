(defun mix2(l1 l2) (
  cond((< (length l1) (length l2))(mix2 l2 l1))
      (T (mix l1 l2 ()))))

(defun mix(l1 l2 l3) (
  cond((null l2) l3)
      (T(mix (cdr l1)(cdr l2)(cons l3 (cons l1 l2))))))
