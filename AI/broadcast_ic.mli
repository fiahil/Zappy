(*
 * Fiahil
 * 10.07.2012
 *)

(*
 * Search a Icq/Rsn broadcast. Discard others until end of queue is reached
 *)
val test_rcp : Broadcast.t -> unit

(*
 * Launch Icq rcp mode
 *)
val engage : unit -> unit

val ic_id : int ref
val ic_lvl : int ref
val ic_mode : int ref
