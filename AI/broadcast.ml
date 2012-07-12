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
  | Rsn of (string * ((Inventory.resources * int) list))
  | Rsh of (string * int)
  | Rsc of (string * int)
  | Rsz of string
  | Rsr of (string * bool)
  | Rse of string

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

let string_of_resources_tuple = function
  | (Inventory.Joueur, v)       -> "joueur " ^ (string_of_int v)
  | (Inventory.Nourriture, v)   -> "nourriture " ^ (string_of_int v)
  | (Inventory.Linemate, v)     -> "linemate " ^ (string_of_int v)
  | (Inventory.Deraumere, v)    -> "deraumere " ^ (string_of_int v)
  | (Inventory.Sibur, v)        -> "sibur " ^ (string_of_int v)
  | (Inventory.Mendiane, v)     -> "mendiane " ^ (string_of_int v)
  | (Inventory.Phiras, v)       -> "phiras " ^ (string_of_int v)
  | (Inventory.Thystame, v)     -> "thystame " ^ (string_of_int v)

let string_of_resources_list l =
  let rec aux str = function
    | []                -> str
    | head::[]          -> aux (str ^ (string_of_resources_tuple head)) []
    | head::tail        -> aux (str ^ (string_of_resources_tuple head) ^ " ") tail
  in
  aux "" l

let list_of_resource_string str =
  let rec aux target l = function
    | []                            -> l
    | "joueur"::tail     -> aux Inventory.Joueur l tail
    | "nourriture"::tail -> aux Inventory.Nourriture l tail
    | "linemate"::tail   -> aux Inventory.Linemate l tail
    | "deraumere"::tail  -> aux Inventory.Deraumere l tail
    | "sibur"::tail      -> aux Inventory.Sibur l tail
    | "mendiane"::tail   -> aux Inventory.Mendiane l tail
    | "phiras"::tail     -> aux Inventory.Phiras l tail
    | "thystame"::tail   -> aux Inventory.Thystame l tail
    | value::tail        -> 
        aux target ((target, (int_of_string value))::l) tail
  in
  aux Inventory.Joueur [] str

let melt = function
  | Icq (id, lvl)       -> "Icq " ^ id ^ " " ^ (string_of_int lvl)
  | Icr (id, pid, b)    -> "Icr " ^ id ^ " " ^ (string_of_int pid) ^ " " ^ (string_of_bool b)
  | Ici (id, l)         -> "Ici " ^ id ^ " " ^ (string_of_id_list l)
  | Ica id              -> "Ica " ^ id
  | Icl id              -> "Icl " ^ id
  | Icz id              -> "Icz " ^ id
  | Rse id              -> "Rse " ^ id
  | Rsr (id, b)         -> "Rsr " ^ id ^ " " ^ (string_of_bool b)
  | Rsz id              -> "Rsz " ^ id
  | Rsc (id, pid)       -> "Rsc " ^ id ^ " " ^ (string_of_int pid)
  | Rsh (id, pid)       -> "Rsh " ^ id ^ " " ^ (string_of_int pid)
  | Rsn (id, l)         -> "Rsn " ^ id ^ " " ^ (string_of_resources_list l)
  | Err str             -> str
  | _                   -> "Hello World"

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

let match_rsn c l =
  try
    Rsn (List.hd l, list_of_resource_string (List.tl l))
  with
    | _                   -> Err c

let match_rsh c l =
  try
    Rsh (List.hd l, (int_of_string (List.nth l 1)))
  with
    | _                   -> Err c

let match_rsc c l =
  try
    Rsc (List.hd l, (int_of_string (List.nth l 1)))
  with
    | _                   -> Err c

let match_rsz c l =
  try
    Rsz (List.hd l)
  with
    | _                   -> Err c

let match_rsr c l =
  try
    Rsr (List.hd l, (bool_of_string (List.nth l 1)))
  with
    | _                   -> Err c

let match_rse c l =
  try
    Rse (List.hd l)
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
  | "Rsn"::tail         -> match_rsn c tail
  | "Rsh"::tail         -> match_rsh c tail
  | "Rsc"::tail         -> match_rsc c tail
  | "Rsz"::tail         -> match_rsz c tail
  | "Rsr"::tail         -> match_rsr c tail
  | "Rse"::tail         -> match_rse c tail
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
    | Rse id              -> Printf.printf "RSE %s\n" id
    | Rsr (id, b)         -> Printf.printf "RSR %s - %B\n" id b
    | Rsz id              -> Printf.printf "RSZ %s\n" id
    | Rsc (id, i)         -> Printf.printf "RSC %s - %d\n" id i
    | Rsh (id, i)         -> Printf.printf "RSH %s - %d\n" id i
    | Rsn (id, l)         -> Printf.printf "RSN %s - %d - %d - %d\n" id
    (snd (List.nth l 0)) (snd (List.nth l 1)) (snd (List.nth l 2))
    | Err str             -> Printf.printf "ERR %s\n" str
    | _                   -> Printf.printf "POOOOONNNNEYYYY\n"
  in
  bc Hel;
  bc (Rse "KOUKOU");
  bc (Rsz "KOUKOU");
  bc (Rsr ("KOUKOU", true));
  bc (Rsc ("KOUKOU", 1));
  bc (Rsh ("KOUKOU", 666));
  bc (Rsn ("KOUKOU",
  [(Inventory.Nourriture, 777); (Inventory.Phiras, 777); (Inventory.Thystame,
  888)]));
  Bridge.push (Bridge.Broadcast "CECI EST UNE ERREUR");
  print_pp (pp Bridge.pull);
  print_pp (pp Bridge.pull);
  print_pp (pp Bridge.pull);
  print_pp (pp Bridge.pull);
  print_pp (pp Bridge.pull);
  print_pp (pp Bridge.pull);
  print_pp (pp Bridge.pull);
  print_pp (pp Bridge.pull);
  ()
