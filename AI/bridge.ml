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

type inventory =
    {
      nourriture : int;
      linemate : int;
      deraumere : int;
      sibur : int;
      mendiane : int;
      phiras : int;
      thystame : int
    }

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

type response_param =
  | RP_empty
  | RP_inventaire of inventory
  | RP_voir of inventory array
  | RP_incantation of int
  | RP_expulse of int
  | RP_broadcast of (int * string)
  | RP_map_size of (int * int)
  | RP_connect of int

type response =
  | R_map_size of response_param
  | R_connect_nbr of response_param
  | R_ok of response_param
  | R_ko of response_param
  | R_broadcast of response_param
  | R_expulse of response_param
  | R_elevation of response_param
  | R_end_incant of response_param
  | R_inventaire of response_param
  | R_voir of response_param

let bat_re = Array.make 10 (Str.regexp ".*", R_ko RP_empty)

let _ = bat_re.(0) <- (Str.regexp "^[0-9]+\n", R_connect_nbr RP_empty)
let _ = bat_re.(1) <- (Str.regexp "^ok\n", R_ok RP_empty)
let _ = bat_re.(2) <- (Str.regexp "^ko\n", R_ko RP_empty)
let _ = bat_re.(3) <- (Str.regexp "^message [0-8],.*\n", R_broadcast RP_empty)
let _ = bat_re.(4) <- (Str.regexp "^deplacement [1357]\n", R_broadcast RP_empty)
let _ = bat_re.(5) <- (Str.regexp "^elevation en cours\n", R_elevation RP_empty)
let _ = bat_re.(6) <- (Str.regexp "^niveau actuel : [2-8]\n", R_end_incant RP_empty)
let _ = bat_re.(7) <- (Str.regexp "^{nourriture [0-9]+,linemate [0-9]+,deraumere [0-9]+,sibur [0-9]+,mendiane [0-9]+,phiras [0-9]+,thystame [0-9]+}\n", R_inventaire RP_empty)
let _ = bat_re.(8) <- (Str.regexp "^{\\(\\( \\(\\bjoueur\\b\\|\\bnourriture\\b\\|\\blinemate\\b\\|\\bderaumere\\b\\|\\bsibur\\b\\|\\bmendiane\\b\\|\\bphiras\\b\\|\\bthystame\\b\\)\\)*,\\( \\(\\bjoueur\\b\\|\\bnourriture\\b\\|\\blinemate\\b\\|\\bderaumere\\b\\|\\bsibur\\b\\|\\bmendiane\\b\\|\\bphiras\\b\\|\\bthystame\\b\\)\\)*\\)*}\n", R_voir RP_empty)
let _ = bat_re.(9) <- (Str.regexp "^[0-9]+ [0-9]+\n", R_map_size RP_empty)

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
  | Prend Nourriture    -> Socket.send "prend nourriture\n"
  | Prend Linemate      -> Socket.send "prend linemate\n"
  | Prend Deraumere     -> Socket.send "prend deraumere\n"
  | Prend Sibur         -> Socket.send "prend sibur\n"
  | Prend Mendiane      -> Socket.send "prend mendiane\n"
  | Prend Phiras        -> Socket.send "prend phiras\n"
  | Prend Thystame      -> Socket.send "prend thystame\n"
  | Pose Nourriture     -> Socket.send "pose nourriture\n"
  | Pose Linemate       -> Socket.send "pose linemate\n"
  | Pose Deraumere      -> Socket.send "pose deraumere\n"
  | Pose Sibur          -> Socket.send "pose sibur\n"
  | Pose Mendiane       -> Socket.send "pose mendiane\n"
  | Pose Phiras         -> Socket.send "pose phiras\n"
  | Pose Thystame       -> Socket.send "pose thystame\n"
  | Team value          -> Socket.send (value ^ "\n")

let pull () =
  let rec aux idx str =
    if Str.string_match (fst (bat_re.(idx))) str 0 then
      snd bat_re.(idx)
    else if idx < 9 then
      aux (idx + 1) str
    else
      R_ko RP_empty
  in
    aux 0 (Socket.recv ())

(*
 * Unitest
 *)
let unitest () =
  let check v t =
    if v = t then
      print_endline "-- SUCCESS"
    else
      print_endline "-- FAIL"
  in
  begin
    Socket.connect "127.0.0.1" 4242;
    push (Team "Poney");
    ignore (Unix.select [] [] [] 0.5);
    check (pull ()) (R_connect_nbr (RP_connect 0));
    check (pull ()) (R_map_size (RP_map_size (20, 20)));
    print_endline "voir";
    push (Voir);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "connect_nbr";
    push (Connect_nbr);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "expulse";
    push (Expulse);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "gauche";
    push (Gauche);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "droite";
    push (Droite);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "avance";
    push (Avance);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "fork";
    push (Fork);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "incantation";
    push (Incantation);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "broadcast poney";
    push (Broadcast "Poney");
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "prend nourriture";
    push (Prend Nourriture);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "pose linemate";
    push (Pose Linemate);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "prend phiras";
    push (Prend Phiras);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "pose mendiane";
    push (Pose Mendiane);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
    print_endline "inventaire";
    push (Inventaire);
    ignore (Unix.select [] [] [] 0.5);
    pull ();
  end

