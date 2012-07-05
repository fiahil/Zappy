(*
 * Fiahil
 * 25.06.2012
 *)

type resources =
  | Nourriture
  | Linemate
  | Deraumere
  | Sibur
  | Mendiane
  | Phiras
  | Thystame


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
  | Prend of resources
  | Pose of resources
  | Team of string

let bat_re = Array.make 10 (Str.regexp ".*")

let _ = bat_re.(0) <- Str.regexp "^[0-9]+\n"
let _ = bat_re.(1) <- Str.regexp "^ok\n"
let _ = bat_re.(2) <- Str.regexp "^ko\n"
let _ = bat_re.(3) <- Str.regexp "^message [0-8],.*\n"
let _ = bat_re.(4) <- Str.regexp "^deplacement: [1-8]\n"
let _ = bat_re.(5) <- Str.regexp "^elevation en cours\n"
let _ = bat_re.(6) <- Str.regexp "^niveau actuel : [2-8]\n"
let _ = bat_re.(7) <- Str.regexp "^{nourriture [0-9]+,linemate [0-9]+,deraumere [0-9]+,sibur [0-9]+,mendiane [0-9]+,phiras [0-9]+,thystame [0-9]+}\n"
let _ = bat_re.(8) <- Str.regexp "^{\\(\\( \\(\\bjoueur\\b\\|\\bnourriture\\b\\|\\blinemate\\b\\|\\bderaumere\\b\\|\\bsibur\\b\\|\\bmendiane\\b\\|\\bphiras\\b\\|\\bthystame\\b\\)\\)*,\\( \\(\\bjoueur\\b\\|\\bnourriture\\b\\|\\blinemate\\b\\|\\bderaumere\\b\\|\\bsibur\\b\\|\\bmendiane\\b\\|\\bphiras\\b\\|\\bthystame\\b\\)\\)*\\)*}\n"
let _ = bat_re.(9) <- Str.regexp "^[0-9]+ [0-9]+\n"

let push = function
  | Connect_nbr         -> Socket.send "connect_nbr\n"
  | Voir                -> Socket.send "voir\n"
  | Inventaire          -> Socket.send "inventaire\n"
  | Expulse             -> Socket.send "expulse\n"
  | Gauche              -> Socket.send "gauche\n"
  | Droite              -> Socket.send "droite\n"
  | Avance              -> Socket.send "avance\n"
  | Fork                -> Socket.send "fork\n"
  | Incantation         -> Socket.send "incantation\n"
  | Broadcast value     -> Socket.send ("broadcast " ^ value ^ "\n")
  | Prend Nourriture    -> Socket.send ("prend nourriture\n")
  | Prend Linemate      -> Socket.send ("prend linemate\n")
  | Prend Deraumere     -> Socket.send ("prend deraumere\n")
  | Prend Sibur         -> Socket.send ("prend sibur\n")
  | Prend Mendiane      -> Socket.send ("prend mendiane\n")
  | Prend Phiras        -> Socket.send ("prend phiras\n")
  | Prend Thystame      -> Socket.send ("prend thystame\n")
  | Pose Nourriture    -> Socket.send ("prend nourriture\n")
  | Pose Linemate      -> Socket.send ("prend linemate\n")
  | Pose Deraumere     -> Socket.send ("prend deraumere\n")
  | Pose Sibur         -> Socket.send ("prend sibur\n")
  | Pose Mendiane      -> Socket.send ("prend mendiane\n")
  | Pose Phiras        -> Socket.send ("prend phiras\n")
  | Pose Thystame      -> Socket.send ("prend thystame\n")
  | Team value          -> Socket.send (value ^ "\n")

let pull () =
  let rec aux idx str =
    if idx < 10 && Str.string_match bat_re.(idx) str 0 then
      print_endline str
    else if idx < 10 then
      aux (idx + 1) str
  in
    aux 0 (Socket.recv ())

let unitest () =
  begin
    Socket.connect "127.0.0.1" 4242;
    push (Team "Poney");
    pull ();
    pull ();
    push (Voir);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Connect_nbr);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Inventaire);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Expulse);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Gauche);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Droite);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Avance);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Fork);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Incantation);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Broadcast "Poney");
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Prend Nourriture);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Pose Linemate);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Prend Phiras);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    push (Pose Mendiane);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
  end

