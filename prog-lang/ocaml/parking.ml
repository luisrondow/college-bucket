let div_ceil a =
  if a mod 60 = 0 then
    a / 60
  else
    (a / 60) + 1
let calc_time_in_park (t_in, t_out) = if (t_out - t_in) > 0 then t_out - t_in else 1440 - (t_in - t_out) ;;
let calc_price x = if x = 1 then 120 else if x = 2 then 120+140 else if x = 3 then 120+140+150 else 120+140+150+155*(x-3) ;;
let park (hour_in, min_in, hour_out, min_out) = calc_time_in_park(hour_in*60+min_in, hour_out*60+min_out) |> div_ceil |> calc_price ;;
