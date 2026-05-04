let rec len lst =
  match lst with
  | [] -> 0
  | _::t -> 1 + len t

let rec sum lst =
  match lst with
  | [] -> 0
  | h::t -> h + sum t

let rec concat lst =
  match lst with
  | [] -> ""
  | h::t -> h ^ concat t

let rec succAll lst =
  match lst with
  | [] -> []
  | h::t -> h+1::(succAll t)

let rec belongs a lst =
  match lst with
  | [] -> false
  | h::t -> if h == a then true else belongs a t