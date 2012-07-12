(*
 * Fiahil
 * 09.07.2012
 *)

val icp : (int * int) list ref

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
  | Rsa of string

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
