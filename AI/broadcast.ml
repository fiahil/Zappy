(*
 * Fiahil
 * 09.07.2012
 *)

type t =
  | Hel
  | Icq of (string * int)
  | Icr of (string * int * bool)
  | Ici of (string * list int)
  | Ica of string
  | Icl of string
  | Icz of string

let hash_team = ref ""

let autohash team =
  hash_team := Digest.to_hex (Digest.string team)

let melt = function
  | Hel                 -> "Hello world"
  | Icq id, lvl         -> id ^ " " ^ (string_of_int lvl)
  | Icr id, pid, b      -> id ^ " " ^ (string_of_int pid) ^ " " ^ (string_of_bool b)
  | Ici id, l           -> id ^ " " ^ " TODO "
  | Ica id              -> id
  | Icl id              -> id
  | Icz id              -> id

let bc m =
  let aux = !hash_team ^ "--"
  in
  Bridge.push (Bridge.Broadcast (aux ^ (melt m)))

(*
 * Unitest
 *)
let unitest () =
  bc Hel;
  bc Hel;
  bc Hel;
  bc Hel;
  bc Hel;
  ignore (Bridge.pull (Bridge.Broadcast "PLOP"));
  ()
