(*
 * Fiahil
 * 10.07.2012
 *)

(*
 * Set state function
 *)
val set : (Inventory.resources list -> unit) -> unit

(*
 * Set param
 *)
val set_param : Inventory.resources list -> unit

(*
 * reset function to last state
 *)
val reset : unit -> unit

(*
 * Run Finite state machine
 *)
val run : unit -> unit
