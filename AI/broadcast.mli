(*
 * Fiahil
 * 09.07.2012
 *)

type t =
  | Hel
  | Err of string
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
 * Get direction of last broadcast
 *)
val gd : unit -> int

(*
 * Pull and parse a broadcast
 *)
val pp : (Bridge.command -> Bridge.response) -> t

(*
 * Unitest
 *)
val unitest : unit -> unit
