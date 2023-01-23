(define (fact n)
  (if (< n 2)
      1
      (* n (fact (- n 1)))))

(define (update dt)
  (randomize_video_mem lispc::Memory lispc::Screen)
  (display `(dt: ,dt fact10: ,(fact 10000)))
  (newline))
