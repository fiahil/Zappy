(*
 * Fiahil
 * 09.07.2012
 *)

let icp = ref []

type t =
  | Hel
  | Err of string
  | Icq of (string * int)
  | Icr of (string * int * bool)
  | Ici of (string * int list)
  | Ica of string
  | Icl of string
  | Icz of string

let hash_team = ref ""
let last_b = ref (0, "")

let autohash team =
  hash_team := Digest.to_hex (Digest.string team)

let string_of_id_list l =
  let rec aux str = function
    | []                -> str
    | head::[]          -> aux (str ^ (string_of_int head)) []
    | head::tail        -> aux (str ^ (string_of_int head) ^ " ") tail
  in
  aux "" l

let melt = function
  | Icq (id, lvl)       -> "Icq " ^ id ^ " " ^ (string_of_int lvl)
  | Icr (id, pid, b)    -> "Icr " ^ id ^ " " ^ (string_of_int pid) ^ " " ^ (string_of_bool b)
  | Ici (id, l)         -> "Ici " ^ id ^ " " ^ (string_of_id_list l)
  | Ica id              -> "Ica " ^ id
  | Icl id              -> "Icl " ^ id
  | Icz id              -> "Icz " ^ id
  | Err str             -> str
  | _                   -> "Hello THIS IZ PONEEEEEYYYYYY"

let bc m =
  let aux = !hash_team ^ "--"
  in
  match m with
    | Err v     -> Bridge.push (Bridge.Broadcast (melt (Err v)))
    | v         -> Bridge.push (Bridge.Broadcast (aux ^ (melt v)))

let split_param str =
  let re = Str.regexp "[ \n]+"
  in
  Str.split re str

let split_hash str =
  let re = Str.regexp "--"
  in
  Str.bounded_split re str 2

let is_my_team str =
  let aux = function
    | []        -> false
    | h::_      -> h = !hash_team
  in
  aux (split_hash str)

let match_icq c l =
  try
    Icq ((List.hd l), (int_of_string (List.nth l 1)))
  with
    | _                   -> Err c

let match_icr c l =
  try
    Icr ((List.hd l), (int_of_string (List.nth l 1)), (bool_of_string (List.nth l 2)))
  with
    | _                   -> Err c

let match_ici c l =
  try
    Ici ((List.hd l), (List.map (int_of_string) (List.tl l)))
  with
    | _                   -> Err c

let match_ica c l =
  try
    Ica (List.hd l)
  with
    | _                   -> Err c

let match_icl c l =
  try
    Icl (List.hd l)
  with
    | _                   -> Err c

let match_icz c l =
  try
    Icz (List.hd l)
  with
    | _                   -> Err c

let match_command c = function
  | "Hello"::tail       -> Hel
  | "Icq"::tail         -> match_icq c tail
  | "Icr"::tail         -> match_icr c tail
  | "Ici"::tail         -> match_ici c tail
  | "Ica"::tail         -> match_ica c tail
  | "Icl"::tail         -> match_icl c tail
  | "Icz"::tail         -> match_icz c tail
  | s                   -> Err c

let pp f =
  let aux () =
    begin
      last_b := Bridge.broadcast (f (Bridge.Broadcast ""));
      snd !last_b
    end
  in
  let auxx str =
    if is_my_team str then
      match_command (List.nth (split_hash str) 1) (split_param (List.nth (split_hash str) 1))
    else
      Err str
  in
  auxx (aux ())

let gd () = fst !last_b

(*
 * Unitest
 *)
let unitest () =
  let print_pp = function
    | Icq (id, lvl)       -> Printf.printf "ICQ %s - %d\n" id lvl
    | Icr (id, pid, b)    -> Printf.printf "ICR %s - %d - %B\n" id pid b
    | Ici (id, l)         -> Printf.printf "ICI %s - %d %d\n" id (List.nth l 0)(List.nth l 1)
    | Ica id              -> Printf.printf "ICA %s\n" id
    | Icl id              -> Printf.printf "ICL %s\n" id
    | Icz id              -> Printf.printf "ICZ %s\n" id
    | Err str             -> Printf.printf "ERR %s\n" str
    | _                   -> Printf.printf "POOOOONNNNEYYYY\n"
  in
  bc Hel;
  bc (Icq ("COUCOU", 777));
  bc (Ici ("COUCOU", [42;5555;666]));
  bc (Icr ("COUCOU", 888, true));
  bc (Ica "COUCOU");
  Bridge.push (Bridge.Broadcast "CECI EST UNE ERREUR");
  print_pp (pp Bridge.pull);
  print_pp (pp Bridge.pull);
  print_pp (pp Bridge.pull);
  print_pp (pp Bridge.pull);
  print_pp (pp Bridge.pull);
  print_pp (pp Bridge.pull);
  ()
