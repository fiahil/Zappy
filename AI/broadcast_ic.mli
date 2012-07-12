(*
 * Fiahil
 * 10.07.2012
 *)

(*
 * Search a Icq broadcast. Discard others until end of queue is reached
 *)
val test_rcp : Broadcast.t -> int

(*
 * Launch Icq rcp mode
 *)
val engage : unit -> unit

val ic_id : int ref
