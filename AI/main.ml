(*
 * Fiahil
 * 27.06.2012
 *)

let team = ref ""
let port = ref 4242
let host = ref "127.0.0.1"

let select_team t =
  team := t

let select_port p =
  port := p

let select_host h =
  host := h

let select_unkn v =
  raise (invalid_arg v)

let main () =
  let aux = Arg.parse
            [("-n", Arg.String select_team, "Team name");
             ("-p", Arg.Int select_port, "Port");
             ("-h", Arg.String select_host, "Host")]
            (select_unkn) "usage: -n Team [-p Port] [-h Host]"
  and
      check_all =
    if !team = "" then
      raise (invalid_arg "Invalid team name.")
  in
    try
      begin
        aux;
        check_all;
        Socket.connect !host !port;
        Bridge.push (Bridge.Team !team);
	MapSize.storage ();
	Random.self_init ();
	FsmSurvival.survival ()
      end
    with
      | Invalid_argument v      -> prerr_endline v
(*    | _                       -> prerr_endline "BOUM BOUM BOUM" *)

(*let _ = main () *)
