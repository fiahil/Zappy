(*
 * Fiahil
 * 25.06.2012
 *)

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
  | Prend of Inventory.resources
  | Pose of Inventory.resources
  | Team of string

type response_param =
  | RP_empty
  | RP_inventaire of Inventory.t
  | RP_voir of Inventory.t array
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

let timeout_t = ref 0.0
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

let voir_cmd str =
  let rec re = Str.regexp "[{}, ]"
  and
      aux bat = function
        | []                                -> Array.of_list (List.rev bat)
        | (Str.Delim "{")::tail             -> aux bat tail
        | (Str.Delim " ")::tail             -> aux bat tail
        | (Str.Delim "}")::tail             -> aux bat tail
        | (Str.Delim ",")::tail             -> aux ((Inventory.empty ())::bat) tail
        | (Str.Text "nourriture")::tail     ->
          aux ((Inventory.inc (List.hd bat) Inventory.Nourriture)::(List.tl bat)) tail
        | (Str.Text "linemate")::tail       ->
          aux ((Inventory.inc (List.hd bat) Inventory.Linemate)::(List.tl bat)) tail
        | (Str.Text "deraumere")::tail      ->
          aux ((Inventory.inc (List.hd bat) Inventory.Deraumere)::(List.tl bat)) tail
        | (Str.Text "sibur")::tail          ->
          aux ((Inventory.inc (List.hd bat) Inventory.Sibur)::(List.tl bat)) tail
        | (Str.Text "mendiane")::tail       ->
          aux ((Inventory.inc (List.hd bat) Inventory.Mendiane)::(List.tl bat)) tail
        | (Str.Text "phiras")::tail         ->
          aux ((Inventory.inc (List.hd bat) Inventory.Phiras)::(List.tl bat)) tail
        | (Str.Text "thystame")::tail       ->
          aux ((Inventory.inc (List.hd bat) Inventory.Thystame)::(List.tl bat)) tail
        | (Str.Text _)::tail                -> aux bat tail
        | _::tail                           -> aux bat tail
  in
  aux [Inventory.empty ()] (Str.full_split re str)

let inventaire_cmd str =
  let rec re = Str.regexp "[{}, ]"
  and
      aux target iv = function
        | []                                -> iv
        | (Str.Delim "{")::tail             -> aux target iv tail
        | (Str.Delim " ")::tail             -> aux target iv tail
        | (Str.Delim "}")::tail             -> aux target iv tail
        | (Str.Delim ",")::tail             -> aux target iv tail
        | (Str.Text "nourriture")::tail     -> aux Inventory.Nourriture iv tail
        | (Str.Text "linemate")::tail       -> aux Inventory.Linemate iv tail
        | (Str.Text "deraumere")::tail      -> aux Inventory.Deraumere iv tail
        | (Str.Text "sibur")::tail          -> aux Inventory.Sibur iv tail
        | (Str.Text "mendiane")::tail       -> aux Inventory.Mendiane iv tail
        | (Str.Text "phiras")::tail         -> aux Inventory.Phiras iv tail
        | (Str.Text "thystame")::tail       -> aux Inventory.Thystame iv tail
        | (Str.Text value)::tail            ->
          (try
             aux target (Inventory.set iv (int_of_string value) target) tail
           with
             | Failure "int_of_string"     -> aux target iv tail)
        | _::tail                            -> aux target iv tail
  in
  aux Inventory.Nourriture (Inventory.empty ()) (Str.full_split re str)

let incantation_cmd str =
  let rec re = Str.regexp "[2-8]"
  and
      aux = function
        | []                    -> 0
        | (Str.Delim v)::tail   ->
            (try
              int_of_string v
            with
              | Failure "int_of_string" -> 0)
        | _::tail               -> aux tail
  in
    aux (Str.full_split re str)

let expulse_cmd str =
  let rec re = Str.regexp "[1357]"
  and
      aux = function
        | []                    -> 0
        | (Str.Delim v)::tail   ->
            (try
               int_of_string v
             with
               | Failure "int_of_string" -> 0)
        | _::tail               -> aux tail
  in
    aux (Str.full_split re str)

let broadcast_cmd str =
  let rec re = Str.regexp ","
  and
      extract_dir str =
    print_endline str;
    try
      int_of_string (String.sub str (String.length str - 1) 1)
    with
      | _       -> 0
  and
      aux l = (extract_dir (List.hd l)), (List.hd (List.tl l))
  in
    aux (Str.bounded_split re str 2)

let map_cmd str =
  let rec re = Str.regexp " "
  and
      aux l =
    try
      (int_of_string (List.hd l)), (int_of_string (List.hd (List.tl l)))
    with
      | _       -> (0, 0)
  in
    aux (Str.bounded_split re str 2)

let connect_cmd str =
  try
    int_of_string str
  with
    | _         -> 0

let fill raw = function
  | R_voir _            -> R_voir (RP_voir (voir_cmd raw))
  | R_inventaire _      -> R_inventaire (RP_inventaire (inventaire_cmd raw))
  | R_end_incant _      -> R_end_incant (RP_incantation  (incantation_cmd raw))
  | R_elevation _       -> R_elevation RP_empty
  | R_expulse _         -> R_expulse (RP_expulse (expulse_cmd raw))
  | R_broadcast _       -> R_broadcast (RP_broadcast (broadcast_cmd raw))
  | R_ko _              -> R_ko RP_empty
  | R_ok _              -> R_ok RP_empty
  | R_map_size _        -> R_map_size (RP_map_size (map_cmd raw))
  | R_connect_nbr _     -> R_connect_nbr (RP_connect (connect_cmd raw))

let dr = function
  | R_map_size t        -> t
  | R_connect_nbr t     -> t
  | R_ok t              -> t
  | R_ko t              -> t
  | R_broadcast t       -> t
  | R_expulse t         -> t
  | R_elevation t       -> t
  | R_end_incant t      -> t
  | R_inventaire t      -> t
  | R_voir t            -> t

let voir = function
  | R_voir (RP_voir t)  -> t
  | _                   -> [||]

let inventaire = function
  | R_inventaire (RP_inventaire t)      -> t
  | _                                   -> Inventory.empty ()

let incantation = function
  | R_end_incant (RP_incantation t)     -> t
  | _                                   -> 0

let expulse = function
  | R_expulse (RP_expulse t)            -> t
  | _                                   -> 0

let broadcast = function
  | R_broadcast (RP_broadcast t)        -> t
  | _                                   -> (0, "")

let map_size = function
  | R_map_size (RP_map_size t)          -> t
  | _                                   -> (0, 0)

let connect = function
  | R_connect_nbr (RP_connect t)        -> t
  | _                                   -> 0

let connect_s = Stack.create ()
let voir_s  = Stack.create ()
let inventaire_s = Stack.create ()
let expulse_q = Queue.create ()
let incantation_s = Stack.create ()
let broadcast_q = Queue.create ()
let history_s = Stack.create ()
let map_s = Stack.create ()

let punch v = function
  | 0           -> Stack.push v connect_s
  | 1           -> Stack.push v history_s
  | 2           -> Stack.push v history_s
  | 3           -> Queue.push v broadcast_q
  | 4           -> Queue.push v expulse_q
  | 5           -> Stack.push v history_s
  | 6           -> Stack.push v incantation_s
  | 7           -> Stack.push v inventaire_s
  | 8           -> Stack.push v voir_s
  | 9           -> Stack.push v map_s
  | _           -> ()

let match_me str =
  let rec aux str idx =
    if str = "mort" then
      raise Exit
    else if idx = 11 then
      failwith "Unmatched string"
    else if Str.string_match (fst bat_re.(idx)) str 0 then
      punch (fill str (snd bat_re.(idx))) idx
    else
      aux str (idx + 1)
  in
    if not (str = "") then
      aux str 0

let rec gather = function
  | Connect_nbr         ->
      begin
        match_me (Socket.recv ());
        if Stack.is_empty connect_s then
          gather Connect_nbr
        else
          Stack.pop connect_s
      end
  | Voir                ->
      begin
        match_me (Socket.recv ());
        if Stack.is_empty voir_s then
          gather Voir
        else
          Stack.pop voir_s
      end
  | Inventaire          ->
      begin
        match_me (Socket.recv ());
        if Stack.is_empty inventaire_s then
          gather Inventaire
        else
          Stack.pop inventaire_s
      end
  | Expulse             ->
      begin
        match_me (Socket.recv ());
        if Queue.is_empty expulse_q then
          gather Expulse
        else
          Queue.pop expulse_q
      end
  | Incantation         ->
      begin
        match_me (Socket.recv ());
        if Stack.is_empty incantation_s then
          gather Incantation
        else  
          Stack.pop incantation_s
      end
  | Broadcast t         ->
      begin
        match_me (Socket.recv ());
        if Queue.is_empty broadcast_q then
          gather (Broadcast t)
        else                                  
          Queue.pop broadcast_q
      end
  | Prend t             ->
      begin
        match_me (Socket.recv ());
        if Stack.is_empty history_s then
          gather (Prend t)
        else
          Stack.pop history_s
      end
  | Pose t              ->
      begin
        match_me (Socket.recv ());
        if Stack.is_empty history_s then
          gather (Pose t) 
        else                                  
          Stack.pop history_s
      end
  | Team t              ->
      begin
        match_me (Socket.recv ());
        if Stack.is_empty map_s then
          gather (Team t) 
        else
          Stack.pop map_s
      end
  | _                   -> R_ko RP_empty

let pull = function
  | Connect_nbr         -> gather Connect_nbr
  | Voir                -> gather Voir
  | Inventaire          -> gather Inventaire
  | Expulse             -> gather Expulse
  | Gauche              -> R_ok RP_empty
  | Droite              -> R_ok RP_empty
  | Avance              -> R_ok RP_empty
  | Fork                -> R_ok RP_empty
  | Incantation         -> gather Incantation
  | Broadcast t         -> gather (Broadcast t)
  | Prend t             -> gather (Prend t)
  | Pose t              -> gather (Pose t)
  | Team t              -> gather (Team t)

let init () =
  let aux = Unix.gettimeofday ()
  in
    begin
      Socket.send "inventaire\n";
      pull Inventaire;
      timeout_t := ((Unix.gettimeofday ()) -. aux) /. 1.0;
    end

let push v =
  let is_not_team = function
    | Team _    -> false
    | _         -> true
  in
  let aux = function
    | Connect_nbr         -> Socket.send "connect_nbr\n"; 0.0
    | Voir                -> Socket.send "voir\n"; 7.0
    | Inventaire          -> Socket.send "inventaire\n"; 1.0
    | Expulse             -> Socket.send "expulse\n"; 7.0
    | Gauche              -> Socket.send "gauche\n"; 7.0
    | Droite              -> Socket.send "droite\n"; 7.0
    | Avance              -> Socket.send "avance\n"; 7.0
    | Fork                -> Socket.send "fork\n"; 42.0
    | Incantation         -> Socket.send "incantation\n"; 300.0
    | Broadcast value     -> Socket.send ("broadcast " ^ value ^ "\n"); 7.0
    | Prend Inventory.Nourriture    -> Socket.send "prend nourriture\n"; 7.0
    | Prend Inventory.Linemate      -> Socket.send "prend linemate\n"; 7.0
    | Prend Inventory.Deraumere     -> Socket.send "prend deraumere\n"; 7.0
    | Prend Inventory.Sibur         -> Socket.send "prend sibur\n"; 7.0
    | Prend Inventory.Mendiane      -> Socket.send "prend mendiane\n"; 7.0
    | Prend Inventory.Phiras        -> Socket.send "prend phiras\n"; 7.0
    | Prend Inventory.Thystame      -> Socket.send "prend thystame\n"; 7.0
    | Pose Inventory.Nourriture     -> Socket.send "pose nourriture\n"; 7.0
    | Pose Inventory.Linemate       -> Socket.send "pose linemate\n"; 7.0
    | Pose Inventory.Deraumere      -> Socket.send "pose deraumere\n"; 7.0
    | Pose Inventory.Sibur          -> Socket.send "pose sibur\n"; 7.0
    | Pose Inventory.Mendiane       -> Socket.send "pose mendiane\n"; 7.0
    | Pose Inventory.Phiras         -> Socket.send "pose phiras\n"; 7.0
    | Pose Inventory.Thystame       -> Socket.send "pose thystame\n"; 7.0
    | Team value          -> Socket.send (value ^ "\n"); 0.0
  in
    begin
      (if !timeout_t = 0.0 && is_not_team v then
         init ());
      ignore (Unix.select [] [] [] (!timeout_t *. aux v))
    end

(*
 * Unitest
 *)
let unitest () =
  let rec see bat=
    let rec print_iv bat =
      begin
        Printf.printf " = Voir = \n";
        Printf.printf "Nourriture %d\n" bat.Inventory.nourriture;
        Printf.printf "Linemate %d\n" bat.Inventory.linemate;
        Printf.printf "Deraumere %d\n" bat.Inventory.deraumere;
        Printf.printf "Sibur %d\n" bat.Inventory.sibur;
        Printf.printf "Mendiane %d\n" bat.Inventory.mendiane;
        Printf.printf "Phiras %d\n" bat.Inventory.phiras;
        Printf.printf "Thystame %d\n" bat.Inventory.thystame
      end
    in print_iv ((voir bat).(0))
  and
         inventory bat =
    let rec print_iv bat =
      begin
        Printf.printf " = Inventaire = \n";
        Printf.printf "Nourriture %d\n" bat.Inventory.nourriture;
        Printf.printf "Linemate %d\n" bat.Inventory.linemate;
        Printf.printf "Deraumere %d\n" bat.Inventory.deraumere;
        Printf.printf "Sibur %d\n" bat.Inventory.sibur;
        Printf.printf "Mendiane %d\n" bat.Inventory.mendiane;
        Printf.printf "Phiras %d\n" bat.Inventory.phiras;
        Printf.printf "Thystame %d\n" bat.Inventory.thystame
      end
    in print_iv (inventaire bat)
  and
         mapSize (x, y) =
    begin
      Printf.printf " = Map Size = \n";
      Printf.printf "%d %d\n" x y
    end
  and
      pok _ = Printf.printf " = OK BBQ = \n"
  and
                connection cn =
    begin
      Printf.printf " = Connect nbr = \n";
      Printf.printf "%d\n" cn
    end
  in
    begin
      Socket.connect "127.0.0.1" 4242;
      push (Team "Poney");
      push (Voir);
      push (Inventaire);
      print_endline "== 1";
      push (Voir);
      push (Inventaire);
      print_endline "== 2";
      push (Voir);
      push (Inventaire);
      print_endline "== 3";
      push (Voir);
      push (Inventaire);
      print_endline "== 4";
      push (Voir);
      push (Inventaire);
      print_endline "== 5";
      push (Avance);
      inventory (pull Inventaire);
      see (pull Voir);
      mapSize (map_size (pull (Team "")));
      pok (pull Avance);
      connection (connect (pull Connect_nbr))
    end
