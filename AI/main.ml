(*
 * Fiahil
 * 27.06.2012
 *)

let select_team t =
  Param.team := t

let select_port p =
  Param.port := p

let select_host h =
  Param.host := h

let is_soldier () =
  Param.soldier := true

let select_unkn v =
  raise (invalid_arg v)

let main () =
  let aux = Arg.parse
            [("-n", Arg.String select_team, "Team name");
             ("-p", Arg.Int select_port, "Port");
             ("-h", Arg.String select_host, "Host");
	     ("-s", Arg.Unit is_soldier, "Soldier")]
            (select_unkn) "usage: -n Team [-p Port] [-h Host]"
  and
      check_all =
    if !Param.team = "" then
      raise (invalid_arg "Invalid team name.")
  in
    try
      begin
        aux;
        check_all;
        Socket.connect !Param.host !Param.port;
        Bridge.push (Bridge.Team !Param.team);
	MapSize.storage ();
        Broadcast.autohash !Param.team;
	if (!Param.soldier = true) then
          FsmLaunch.run ()
	else
	  Mother.run ()
      end
    with
      | Invalid_argument v      -> prerr_endline v
      | Pervasives.Exit         -> prerr_endline "Player disconnected"
      | _                       -> prerr_endline "An error occured"

let _ = main ()
