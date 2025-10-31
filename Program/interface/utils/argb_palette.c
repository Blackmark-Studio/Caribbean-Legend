int ARGB_Color(string color)
{
	switch (color)
	{
		case "white":    return argb(255, 255, 255, 255); break;
		case "badGrey":  return argb(255, 145, 145, 145); break; // серый недоступный, неподходящий
		case "gold":     return argb(255, 235, 205, 0);   break;
		case "quest":    return argb(255, 255, 192, 255); break; // лиловый квестовый
		case "red":      return argb(255, 255, 196, 196); break;
		case "peach":    return argb(255, 255, 196, 98);  break; // персиковый
		case "green":    return argb(255, 105, 255, 105); break;
		case "offGrey":  return argb(255, 196, 196, 196); break; // глубокий сервый, отключено вообще
	}

	return -1;
}