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

(*
 * Hash team name
 *)
val autohash : string -> unit

(*
 * Launch a broadcast
 *)
val bc : t -> unit

(*
 * Unitest
 *)
val unitest : unit -> unit
