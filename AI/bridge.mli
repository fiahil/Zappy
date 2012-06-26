(*
 * Fiahil
 * 25.06.2012
 *)

type action
type command =
  | Connect_nbr
  | Voir
  | Inventaire
  | Expulse
  | Gauche
  | Droite
  | Avance
  | Fork
  | Incantation
  | Broadcast of string
  | Prend of string
  | Pose of string
  | Reponse of string

val update : unit -> bool
val push : action -> bool
val discard : unit -> unit
val call : unit -> unit

val make_action : command -> (string -> unit) -> action

val unitest : unit -> unit
