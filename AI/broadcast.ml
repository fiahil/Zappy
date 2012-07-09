(*
 * Fiahil
 * 09.07.2012
 *)

type t =
  | Hel
  | Icq of (string * int)
  | Icr of (string * int * bool)
  | Ici of (string * int list)
  | Ica of string
  | Icl of string
  | Icz of string

let hash_team = ref ""

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
  | Hel                 -> "Hello world"
  | Icq (id, lvl)       -> "Icq " ^ id ^ " " ^ (string_of_int lvl)
  | Icr (id, pid, b)    -> "Icr " ^ id ^ " " ^ (string_of_int pid) ^ " " ^ (string_of_bool b)
  | Ici (id, l)         -> "Ici " ^ id ^ " " ^ (string_of_id_list l)
  | Ica id              -> "Ica " ^ id
  | Icl id              -> "Icl " ^ id
  | Icz id              -> "Icz " ^ id

let bc m =
  let aux = !hash_team ^ "--"
  in
  Bridge.push (Bridge.Broadcast (aux ^ (melt m)))

(*
 * Unitest
 *)
let unitest () =
  bc Hel;
  bc (Icq ("COUCOU", 10));
  bc (Ici ("YOP", [10;12;666]));
  bc (Icr ("OKKK", 66, true));
  bc Hel;
  ignore (Bridge.pull (Bridge.Broadcast "PLOP"));
  ()
