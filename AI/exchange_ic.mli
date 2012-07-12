(*
 * Fiahil
 * 12.07.2012
 *)

(*
 * Launch Exchange mode
 *)
val engage : unit -> unit

val ex_fp : string ref
val ex_ll : ((Inventory.resources * int) list) ref
