(*
 * Fiahil
 * 09.07.2012
 *)

type t =
  | Hel
  | Icq
  | Icr
  | Ici
  | Ica
  | Icl
  | Icz

let hash_team = ref ""

let hash team =
  let aux team =
    if !hash_team = "" then
      print_endline "KOUKOU";
      print_endline (Digest.string team)
  in
  begin
    aux team;
    !hash_team
  end

let melt () =
  begin
    print_endline (hash !Main.team);
    hash !Main.team
  end

let bc = function
  | Hel         -> Bridge.push (Bridge.Broadcast ((melt ()) ^ "\n"))
  | _           -> Bridge.push (Bridge.Broadcast "YOUHOU PETIT PONEY!")

(*
 * Unitest
 *)
let _ =
  let _ = Socket.connect "127.0.0.1" 4242
  in
  let _ = Main.team := "Poney"
  in
  let _ = Bridge.push (Bridge.Team !Main.team)
  in
  bc Hel;
  Bridge.pull (Bridge.Broadcast "")
