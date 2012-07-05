(*
 * Fiahil
 * 25.06.2012
 *)

(*
 * Connect to a server. Only one connection allowed
 *)
val connect : string -> int -> unit

(*
 * Send a string. Connect must be called before
 *)
val send : string -> unit

(*
 * Receive a string. Split & aggregate strings. Connect must be called before
 *)
val recv : unit -> string

(*
 * Unitest
 *)
val unitest : unit -> unit
