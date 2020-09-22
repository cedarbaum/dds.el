(require 'dash)
(require 'dds)

(defconst suits '("♠" "♥" "♦" "♣" "NT"))
(defconst positionHeaders '("" "N" "E" "S" "W"))

(defun dds-calc-dd-table-pbn-org-table (pbn)
  "Get solution for PBN and format as an Org mode table."
  (let* ((res (dds-calc-dd-table-pbn pbn))
         (res-with-suits (-map-indexed (lambda (idx row) (cons (nth idx suits) row)) res))
         (res-with-hline (cons 'hline res-with-suits))
         (res-with-headers (cons positionHeaders res-with-hline)))
    res-with-headers))
