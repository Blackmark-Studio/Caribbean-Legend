void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Qué quieres?";
		link.l1 = "Nada en este momento.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// Найти помощника в магазин
	case "Storehelper":
		DelLandQuestMark(npchar);
		dialog.text = "¿Hay algo que necesite, monsieur?";
		link.l1 = "¿Eres Gralam Lavoie, correcto?";
		link.l1.go = "Storehelper_1";
		break;

	case "Storehelper_1":
		dialog.text = "¿Quién pregunta? No me moleste mientras estoy bebiendo ron, señor. No estoy de humor para conversar.";
		link.l1 = "No te quitaré mucho tiempo. Me ha enviado un comerciante de Saint-Pierre. Fuiste su antiguo empleado. Te está buscando y...";
		link.l1.go = "Storehelper_2";
		break;

	case "Storehelper_2":
		dialog.text = "¡Ja, ¿está buscándome!? ¡Eso es digno de ese maldito avaro! ¿De verdad pensó que pasaría toda mi vida trabajando por tan míseros salarios? ¡Es el tacaño más codicioso del Caribe! Trabajé como un esclavo para él durante cinco años y nunca me pagó ni un centavo más de lo que podía evitar. ¡Bah, ni siquiera lo suficiente para comprar una bebida!\nQue cuente sus propias mercancías ahora, me largo. Nadie en Saint-Pierre trabajará para ese agarrado, eso seguro. Sólo le importa una cosa: ganar más para él mismo y pagar menos a su gente.";
		link.l1 = "¿Supongo que no volverás a trabajar para él?";
		link.l1.go = "Storehelper_3";
		break;

	case "Storehelper_3":
		dialog.text = "No, ¡que Dios me fulmine si lo hice! Simplemente esperaré aquí en Le Francois a que llegue algún barco y me embarcaré como sobrecargo si me aceptan. Y si eso no funciona, entonces me rebajaré a ser un simple marinero. No puedo ni soportar ver a ese avaricioso. Si voy a ser pobre, bien podría ser un hombre libre...";
		link.l1 = "Entiendo, eso es todo lo que necesitaba saber. ¡Buena suerte, Gralam!";
		link.l1.go = "Storehelper_12";
		break;

	case "Storehelper_4":
		DelLandQuestMark(npchar);
		dialog.text = "Señor, apártese. ¡Está en mi camino!";
		link.l1 = "Solo una pregunta, monsieur. ¿Es usted Gralam Lavoie?";
		link.l1.go = "Storehelper_5";
		break;

	case "Storehelper_5":
		dialog.text = "¡Ja! Sí, ese soy yo. ¿Qué quieres?";
		link.l1 = "Te está buscando un comerciante de San Pedro. Trabajabas para él, ¿verdad?";
		link.l1.go = "Storehelper_6";
		break;

	case "Storehelper_6":
		dialog.text = "¡Ja, ja! ¡Qué broma! ¿Y qué necesita su majestad real de mí? ¿Ha decidido pagarme mi salario faltante por mis últimas dos semanas de trabajo? ¿O está teniendo problemas para contar sus barriles y engañar a sus clientes al mismo tiempo, eh? ¡Ja-ja-ja!";
		link.l1 = "Él me pidió que te buscara y aclarara por qué ya no vas a su tienda a trabajar.";
		link.l1.go = "Storehelper_7";
		break;

	case "Storehelper_7":
		dialog.text = "¿Por qué? ¡Porque es un avaro de mierda y un empleador terrible! ¡Ahora soy parte de los Hermanos de la Costa, un hombre libre y un esclavo nunca más! ¡Mira a tu alrededor, realmente me estoy divirtiendo!\nPronto zarparé y contaré pesos y doblones tomados de los españoles en lugar de cajas de plátanos. Y sobre ese tacaño, dudo que encuentre a alguien para reemplazarme. Nadie en Saint-Pierre es tan estúpido como para trabajar para él, hemos difundido su reputación a todos los aprendices de la isla, ¡ja-ja!";
		link.l1 = "Entiendo. Eso es todo lo que necesitaba saber. ¡Buena suerte, Gralam!";
		link.l1.go = "Storehelper_12";
		break;

	case "Storehelper_8":
		DelLandQuestMark(npchar);
		dialog.text = "¿Cómo puedo ayudarte?";
		link.l1 = "Buenas tardes. ¿Gralam Lavoie, supongo?";
		link.l1.go = "Storehelper_9";
		break;

	case "Storehelper_9":
		dialog.text = "Sí. ¿Qué desea, monsieur?";
		link.l1 = "Un comerciante de Saint-Pierre te está buscando. Trabajaste para él, ¿no es así?";
		link.l1.go = "Storehelper_10";
		break;

	case "Storehelper_10":
		dialog.text = "Bien, que siga buscando. No le debo nada. Aún me debe dos semanas de salario, pero ni siquiera me voy a molestar en recuperar mi dinero de él. Espero que se atragante con sus propias monedas de cobre.";
		link.l1 = "Hum. Así que lo has dejado para siempre, ¿no es así?";
		link.l1.go = "Storehelper_11";
		break;

	case "Storehelper_11":
		dialog.text = "Lo has acertado todo, señor. Mi ex-empleador es un raro espécimen de avaro, verdaderamente bíblico en escala. Ahora soy un Hermano de la Costa y mis talentos son bien apreciados por mis nuevos camaradas. Gano el doble, además de bonificaciones. \nDudo que nuestro querido amigo encuentre a alguien para reemplazarme. Su avaricia es bien conocida por la gente de Saint-Pierre, nadie allí es tan tonto como para trabajar para él.";
		link.l1 = "Lo tengo. Eso es todo lo que necesitaba saber. ¡Buena suerte, Gralam!";
		link.l1.go = "Storehelper_12";
		break;

	case "Storehelper_12":
		DialogExit();
		npchar.lifeday = 0;
		AddQuestRecord("SharlieA", "2");
		pchar.questTemp.Sharlie.Storehelper = "return";
		LAi_CharacterDisableDialog(npchar);
		pchar.quest.StorehelperOver.over = "yes"; // снять таймер
		// Rebbebion, новые марки до места назначения
		QuestPointerToLoc("lefransua_town", "reload", "gate_back");
		QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
		QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
		QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
		QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
		QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
		AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
		QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
		QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
		QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
		QuestPointerDelLoc("martinique_jungle_02", "reload", "reload3_back");
		QuestPointerDelLoc("lefransua_exittown", "reload", "reload1_back");
		break;

	case "Newstorehelper_1":
		dialog.text = "Hola, monsieur. No quiero ser demasiado atrevido, pero creo que mi candidatura será bastante adecuada para el puesto que está ofreciendo.";
		link.l1 = "Buenas tardes. ¿Y por qué supones eso?";
		link.l1.go = "Newstorehelper_1_1";
		break;

	case "Newstorehelper_2":
		dialog.text = "¡Saludos, señor! Permítame contarle un poco sobre mí mismo.";
		link.l1 = "Soy todo oídos.";
		link.l1.go = "Newstorehelper_2_1";
		break;

	case "Newstorehelper_3":
		dialog.text = "Buena salud a usted, estimado señor. ¿Está ofreciendo una vacante de comerciante?";
		link.l1 = "Así es. ¿Qué puedes contarme sobre ti?";
		link.l1.go = "Newstorehelper_3_1";
		break;

	case "Newstorehelper_1_1":
		dialog.text = "Serví como contramaestre bajo el mando del propio Capitán Francis Dubois. Estaba bastante complacido con mis habilidades, pero resulté herido en batalla y tuve que tomar un permiso para ser tratado. Estoy bien ahora, completamente sano de cuerpo, pero el pensamiento de las olas me enferma. No, mi único deseo ahora es permanecer en tierra firme\n(susurrando) Y si me eliges, pagaré quinientos pesos y veinticinco doblones de oro extra.";
		link.l1 = "Ya veo. Lo pensaré.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Newstorehelper_1_2";
		break;

	case "Newstorehelper_2_1":
		dialog.text = "Solía ser un buhonero, pero tuve que huir de algunos acreedores y me hice al mar como sobrecargo en un barco mercante. El destino me ha traído a este pueblo. De todos modos, no me gustaba mucho la vida de marinero, y estaría encantado de aceptar tu oferta\n(susurrando) Y si me eliges, te daré no solo quinientos pesos, sino también este pesado paquete de ámbar.";
		link.l1 = "Ya veo. Lo pensaré.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Newstorehelper_2_2";
		break;

	case "Newstorehelper_3_1":
		dialog.text = "Era un empleado en uno de los almacenes portuarios de Glasgow. Vine al Caribe en busca de riqueza y logré ganar suficiente dinero para vivir mi vejez con dignidad. Pero me cansé de los viajes por mar y me gustaría vivir una vida tranquila en la costa.\n(Susurrando) Y si me eliges, te daré quinientos pesos más dos mil quinientos pesos adicionales como extra.";
		link.l1 = "Ya veo. Lo pensaré.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Newstorehelper_3_2";
		break;

	case "Newstorehelper_1_2":
		dialog.text = "Monsieur, tome la decisión correcta. Y no olvide los doblones...";
		link.l1 = "He decidido a tu favor. Ponte en orden. Vamos a Saint-Pierre.";
		link.l1.go = "Newstorehelper_1_3";
		link.l2 = "Aún no lo he decidido...";
		link.l2.go = "exit";
		NextDiag.TempNode = "Newstorehelper_1_2";
		break;

	case "Newstorehelper_2_2":
		dialog.text = "Espero que me elijas, monsieur. Y el ámbar también es una cosa bastante valiosa y útil...";
		link.l1 = "He decidido a tu favor. Prepárate. Vamos a Saint-Pierre.";
		link.l1.go = "Newstorehelper_2_3";
		link.l2 = "Aún no lo he decidido...";
		link.l2.go = "exit";
		NextDiag.TempNode = "Newstorehelper_2_2";
		break;

	case "Newstorehelper_3_2":
		dialog.text = "El mercader no quedará decepcionado con mi trabajo. Y no olvides tu bonificación.";
		link.l1 = "Me he decidido a tu favor. Ponte las pilas. Vamos a Saint-Pierre.";
		link.l1.go = "Newstorehelper_3_3";
		link.l2 = "Aún no lo he decidido...";
		link.l2.go = "exit";
		NextDiag.TempNode = "Newstorehelper_3_2";
		break;

	case "Newstorehelper_1_3":
		dialog.text = "¡Déjame reunir mis cosas! Te estaré esperando en la entrada de la taberna.";
		link.l1 = "...";
		link.l1.go = "Newstorehelper_exit";
		pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;

	case "Newstorehelper_2_3":
		dialog.text = "¡Estaré allí en un momento, monsieur! Te estaré esperando en la entrada de la taberna.";
		link.l1 = "...";
		link.l1.go = "Newstorehelper_exit";
		pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;

	case "Newstorehelper_3_3":
		dialog.text = "¡Iré a buscar mi vieja valija y te esperaré en la entrada de la taberna, señor!";
		link.l1 = "...";
		link.l1.go = "Newstorehelper_exit";
		pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;

	case "Newstorehelper_exit":
		DialogExit();
		chrDisableReloadToLocation = false; // открыть локацию
		pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
		DeleteAttribute(npchar, "LifeDay")
			chrDisableReloadToLocation = true;
		for (i = 1; i <= 3; i++)
		{
			sld = characterFromId("Newstorehelper_" + i);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
		}
		pchar.quest.storehelper2.win_condition.l1 = "location";
		pchar.quest.storehelper2.win_condition.l1.location = "LeFransua_town";
		pchar.quest.storehelper2.function = "NewstorehelperAdd";
		AddQuestRecord("SharlieA", "4");
		pchar.questTemp.Sharlie.Storehelper = "choise";
		pchar.quest.storehelper.over = "yes"; // снять прерывание
		pchar.quest.Sharlie_JungleBandos.win_condition.l1 = "location";
		pchar.quest.Sharlie_JungleBandos.win_condition.l1.location = "Martinique_Jungle_01";
		pchar.quest.Sharlie_JungleBandos.function = "SharlieJungleBandos";

		QuestPointerToLoc("lefransua_town", "reload", "gate_back");
		QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
		QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
		QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
		QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
		QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
		AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
		break;

	case "Newstorehelper_regard":
		dialog.text = "Bueno, supongo que aquí es donde trabajo a partir de ahora. Gracias, monsieur, por elegirme. Aquí están sus quinientos pesos y el bono adicional como prometido.";
		link.l1 = "Mi gratitud... Permíteme presentarte a tu empleador.";
		link.l1.go = "Newstorehelper_regard_1";
		break;

	case "Newstorehelper_regard_1":
		DialogExit();
		npchar.lifeday = 0;
		switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
		{
		case 0:
			AddMoneyToCharacter(pchar, 500);
			TakeNItems(pchar, "gold_dublon", 25);
			break;

		case 1:
			AddMoneyToCharacter(pchar, 500);
			TakeNItems(pchar, "jewelry8", 10);
			TakeNItems(pchar, "jewelry7", 1);
			break;

		case 2:
			AddMoneyToCharacter(pchar, 3000);
			break;
		}
		break;

	// контрабанда рома
	case "Rum_Cap_Over":
		dialog.text = "Monsieur, debo pedirle que abandone mi barco inmediatamente. ¡Estamos levantando anclas y zarpando!";
		link.l1 = "Está bien...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Rum_Cap_Over";
		chrDisableReloadToLocation = false;
		npchar.DontDeskTalk = true;
		LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;

	case "Rum_Cap":
		pchar.quest.Sharlie_rum2.over = "yes"; // снять таймер
		chrDisableReloadToLocation = false;	   // patch-4
		dialog.text = "¿Y bien? ¿Quién eres, camarada?";
		// link.l1.edit = 1;
		link.l1 = "" + pchar.questTemp.Sharlie.Rum.Pass + ".";
		link.l1.go = "Rum_Cap_1";
		break;

	case "Rum_Cap_1":
		dialog.text = "¡Tómate un trago de ron, marinero! ¡Ja, ja! Bienvenido a bordo de mi lugre. ¿Has venido por el producto?";
		link.l1 = "Sí. ¿Para qué más estaría aquí?";
		link.l1.go = "Rum_Cap_2";
		/* if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
		{
			dialog.text = "¡Tómate un trago de ron, marinero! ¡Ja-ja! Bienvenido a bordo de mi lugre. ¿Has venido por el producto?";
			link.l1 = "Sí. ¿Para qué más estaría aquí?";
			link.l1.go = "Rum_Cap_2";
		}
		else
		{
			dialog.text = "¡Vaya, vaya, qué hijo de una verde ramera! ¡Muchachos, este parece un recluta novato! ¡Larguémoslo por la borda!";
			link.l1 = "¡Hup!";
			link.l1.go = "Rum_Cap_getout";
		} */
		break;

	case "Rum_Cap_getout":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
			break;

	case "Rum_Cap_2":
		dialog.text = "¡Muchachos! ¡Carguen las cajas en la lancha!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;

	case "Rum_Cap_3":
		dialog.text = "Todas las cajas de ron están en tu lancha. Port Le Francois se encuentra justo al sur de aquí. ¡Apresúrate, es hora de que yo también levante ancla!";
		link.l1 = "¡No perdamos tiempo, caballeros! ¡Buena suerte!";
		link.l1.go = "Rum_Cap_4";
		break;

	case "Rum_Cap_4":
		dialog.text = "Lo mismo para ti, camarada...";
		link.l1 = "...";
		link.l1.go = "Rum_Cap_5";
		break;

	case "Rum_Cap_5":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		npchar.DontDeskTalk = true;
		NextDiag.CurrentNode = "Rum_Cap_Over";
		pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
		pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_town";
		pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
		AddQuestRecord("SharlieB", "4");
		i = FindIsland("Martinique");
		Islands[i].EffectRadius = 3000;

		DoQuestFunctionDelay("MessageRum1", 1.0);
		// NewGameTip("Transport the rum to Le Francois. Keep sailing around the island.");
		pchar.questTemp.Rum.Tip2.Reload = "l4";

		Weather.Wind.Speed = 16.0;
		pchar.wind.speed = Weather.Wind.Speed;
		fWeatherSpeed = stf(Weather.Wind.Speed); // халява первого выхода

		Weather.Wind.Angle = PId2;
		pchar.wind.angle = Weather.Wind.Angle;
		fWeatherAngle = stf(Weather.Wind.Angle); // халява первого выхода

		pchar.quest.MessageRum2.win_condition.l1 = "ExitFromLocation";
		pchar.quest.MessageRum2.win_condition.l1.location = pchar.location;
		pchar.quest.MessageRum2.function = "MessageRum2";
		break;

	case "Rum_Carrier":
		dialog.text = "Hemos estado esperándole, monsieur. ¿Cómo fue todo? ¿Tiene las cajas?";
		link.l1 = "Todo fue espectacular. Las cajas de ron están en el bote.";
		link.l1.go = "Rum_Carrier_1";
		break;

	case "Rum_Carrier_1":
		dialog.text = "Estupendo. Nos encargaremos de esto desde aquí. Tú dirígete a Saint-Pierre a la taberna para el pago. Sé atento y cauteloso en las junglas nocturnas.";
		link.l1 = "Todo lo mejor, caballeros.";
		link.l1.go = "Rum_Carrier_2";
		break;

	case "Rum_Carrier_2":
		DialogExit();
		for (i = 1; i <= 3; i++)
		{

			sld = characterFromId("Rum_Carrier2_" + i);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
		}
		pchar.questTemp.Sharlie.Rum = "regard";
		i = FindLocation("Fortfrance_town");
		setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
		SetCurrentTime(23, 0);
		Sharlie_removeLocks("");
		// Rebbebion, новые марки до места назначения
		QuestPointerToLoc("lefransua_town", "reload", "gate_back");
		QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
		QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
		QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
		QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
		QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
		if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
			QuestPointerToLocTime("fortfrance_town", "reload", "reload9_back", 23.0, 24.0);
		AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;

	// доставить девочку из борделя
	case "GigoloMan":
		DelLandQuestMark(npchar);
		dialog.text = "¡Buenas tardes, monsieur! Digo, no pareces uno de esos harapientos sinvergüenzas que suelen rondar por nuestra colonia. A juzgar por tu vestimenta, debes haber venido de muy lejos... ¿Llegaste de Europa, acaso?";
		link.l1 = "Exactamente, monsieur. " + GetFullName(pchar) + ", a su servicio. ¿Qué necesita?";
		link.l1.go = "GigoloMan_1";
		break;

	case "GigoloMan_1":
		dialog.text = "Permíteme presentarme, " + GetFullName(npchar) + " He llegado a este lugar espantoso desde Francia hace unos años. Pero eso no viene al caso. Tengo un asunto muy delicado para usted\nPor favor, entienda que si no estuviera seguro de que es un caballero, nunca le pediría tal favor.";
		link.l1 = "Por favor, indique su solicitud, monsieur. Si está dentro de mis capacidades, por supuesto intentaré ayudar.";
		link.l1.go = "GigoloMan_2";
		break;

	case "GigoloMan_2":
		dialog.text = "Me alegra oír eso, monsieur de Maure. Ahora, cómo decir esto delicadamente... Hay un burdel en esta ciudad. Una nueva chica apareció allí recientemente; joven, pálida, rubia, ¡impresionantemente hermosa! Ahora, la he estado observando durante semanas y... tengo un deseo muy fuerte de pasar algún tiempo con ella en privado, pero mi estado y estatus hacen... inconveniente visitar tal lugar. ¡Imagina los chismes!\nPor eso me dirijo a usted. Hablando claro, eres un recién llegado a nuestra isla, la gente no te conoce y no se preocupa por lo que haces... todavía. Podría hacerme un gran favor, monsieur.";
		link.l1 = "Creo que entiendo adónde quieres llegar.";
		link.l1.go = "GigoloMan_3";
		break;

	case "GigoloMan_3":
		dialog.text = "Aprecio su discreción, monsieur. No puedo ir a la chica, así que la chica debe venir a mí. A mi casa. Le pido que vaya al burdel y haga un trato con la madame para que le permita organizar una 'visita a domicilio' de la chica rubia por una noche. Aurora no se negará, es bien conocida por ofrecer tales servicios de entrega, aunque siempre cuesta un poco más. Después de eso, deberá traer a la chica a mi casa. Como pago, le daré seis mil pesos. Aurora usualmente cobra tres mil o tres mil quinientos por una noche con la chica en casa. Puede quedarse con el resto como compensación por sus molestias.";
		link.l1 = "No suena demasiado complicado. Puedo hacer eso.";
		link.l1.go = "GigoloMan_4";
		link.l2 = "Monsieur, tomo mi reputación como caballero tan en serio como usted. Por favor, perdóneme, pero no puedo cumplir con su solicitud. Debo rechazarla. Debería probablemente ir a la taberna y verificar si el tabernero tiene algún trabajo para mí.";
		link.l2.go = "GigoloMan_exit";
		break;

	case "GigoloMan_exit":
		DialogExit();
		LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false); // бордель open
		LocatorReloadEnterDisable("Fortfrance_town", "reload9", false);		 // бордель
		LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false); // таверна
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		chrDisableReloadToLocation = false;
		QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
		SetCurrentTime(17, 30);
		break;

	case "GigoloMan_4":
		dialog.text = "Me alegra mucho de oírlo. Escucha, la chica se llama Lucille. Te pido que la lleves a mi casa cuando oscurezca, no antes de las once de la noche, para evitar la atención indeseada de cualquier mirón. Llama a la puerta y te abriré.\nMi casa se encuentra a la izquierda de la residencia del gobernador, de espaldas a ella, una mansión de dos plantas con tejado rojo. Puedes encontrarla fácilmente, y también hay una tienda cerca. De hecho, ahora me dirijo a mi casa; no dudes en seguirme para ver qué aspecto tiene y dónde está exactamente, así no te perderás por la noche.\n En cuanto al asunto que nos ocupa, toma seis mil pesos. ¡Te espero a la hora acordada!";
		link.l1 = "Hemos llegado a un acuerdo. Tu rubia Lucille estará en tu puerta esta noche.";
		link.l1.go = "GigoloMan_5";
		break;

	case "GigoloMan_5":
		DialogExit();
		AddMoneyToCharacter(pchar, 6000);
		AddQuestRecord("SharlieC", "1");
		AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
		LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
		npchar.lifeday = 0;
		pchar.questTemp.Sharlie.Gigolo = "start";
		pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
		pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
		LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false); // бордель open
		LocatorReloadEnterDisable("Fortfrance_town", "reload91", false);	 // бордель
		AddLandQuestMark(characterFromId("Fortfrance_hostess"), "questmarkmain");
		QuestPointerToLoc("fortfrance_town", "reload", "reload9_back");
		QuestPointerToLoc("fortfrance_brothel", "reload", "reload3");
		chrDisableReloadToLocation = false;
		break;

	case "GigoloGirl":
		if (npchar.quest.meeting == "0")
		{
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
			dialog.text = "Buen día, monsieur. ¿Por qué, eres tú el hombre que me contrató esta noche? Vaya vaya, debo decir, soy una chica afortunada por encontrarme con un caballero tan apuesto y bien arreglado, nada como los brutos que vienen del muelle apestando a alquitrán y sudor...";
			link.l1 = "Mis disculpas, pero no esta noche, Lucille. Estoy aquí en nombre de mi buen amigo, quien por una multitud de razones muy complicadas no puede salir de su casa, así que te llevaré a él. Ahora, no te enojes, es un hombre amable y le gustas mucho. Creo que al final estarás contenta.";
			link.l1.go = "GigoloGirl_1";
			// belamour legendary edition -->
			link.l2 = "Uhm... Tienes toda la razón, querida. ¿Vamos?";
			link.l2.go = "GigoloGirl_1a";
			// <-- legendary edition
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "Monsieur, espero que entiendas que no puedo simplemente pasearme contigo por la noche. Necesitas llevarme rápidamente a la casa de tu amigo o regresaré directamente con Madame y vas a desperdiciar tu dinero.";
			link.l1 = "Está bien, entiendo. ¡Sígueme!";
			link.l1.go = "GigoloGirl_2";
		}
		break;
	// belamour legendary edition -->
	case "GigoloGirl_1a":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		LAi_SetActorType(npchar);
		LAi_SetActorType(pchar);
		chrDisableReloadToLocation = true; // закрыть локацию
		DoQuestReloadToLocation(pchar.location + "_room", "goto", "goto2", "GigoloGirl_Sex");
		ChangeCharacterAddressGroup(npchar, pchar.location + "_room", "goto", "goto1");
		if (!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
		{
			pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
			pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
			pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
			pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
		}
		break;

	case "GigoloGirl_1":
		AddCharacterExpToSkill(pchar, "Fortune", 40);
		// <-- legendary edition
		dialog.text = "Qué lástima... Me caíste bien de inmediato, monsieur. Me hubiera encantado pasar la noche contigo... quizás la próxima vez. ¿Vamos?";
		link.l1 = "Sí. ¡Sígueme!";
		link.l1.go = "GigoloGirl_2";
		break;

	case "GigoloGirl_2":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
		pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
		pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
		pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
		pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
		pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
		pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour = sti(GetTime() + 2);
		pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
		QuestPointerToLoc("fortfrance_town", "reload", "houseSp1");
		break;

	case "GigoloGirl_3":
		dialog.text = "Qué casa tan grandiosa. ¿Es este el lugar?";
		link.l1 = "Sí. Entra. No tengas miedo, mi amigo es un buen hombre.";
		link.l1.go = "GigoloGirl_4";
		break;

	case "GigoloGirl_4":
		dialog.text = "Me subestimas, no tengo miedo, monsieur. Sé cómo manejarme. Ahora, ¿quizás más tarde puedas pagarle a Madame por una noche conmigo? ¡Te prometo que será la mejor noche de tu vida!";
		link.l1 = "Todo es posible, Lucille. Quizás nos volvamos a encontrar. ¡Adiós!";
		link.l1.go = "GigoloGirl_5";
		break;

	case "GigoloGirl_5":
		pchar.quest.Sharlie_Gigolo1.over = "yes";
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
		QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
		if (!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
		{
			pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
			pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
			pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
			pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
		}
		break;

	// пираты с пленным испанцем
	case "CaptivePirate":
		pchar.quest.Captive_CreatePiratesOver.over = "yes";	 // снять таймер
		pchar.quest.Captive_CreatePiratesOver2.over = "yes"; // снять таймер
		// Rebbebion, новые марки до места назначения
		QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
		QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
		QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
		QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
		QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
		dialog.text = "¿Qué es esto!? ¿Quién eres tú? ¿Qué quieres aquí? ¡Vamos, lárgate de aquí!";
		link.l1 = "No eres muy cortés, señor.";
		link.l1.go = "CaptivePirate_1";
		break;

	case "CaptivePirate_1":
		dialog.text = "Escucha, muchacho, no me criaron para ser cortés, al igual que no aprendí a leer y escribir, pero partirte el cráneo con un alfanje me resulta tan fácil como a una ramera caerse de espaldas. Y te juro por mis luces muertas que si no sales de aquí en este instante, te sacarán cargado. ¿Lo entiendes?";
		link.l1 = "No, escúchame a mí, bribón. Tu artimaña ha sido descubierta. Necesito a ese hombre vivo, así que suelta las armas y corre. Hay un escuadrón de soldados franceses en la jungla justo detrás de mí. Si corres lo suficientemente rápido, tal vez logres salvar tus patéticas vidas.";
		link.l1.go = "CaptivePirate_3";
		link.l2 = "Está bien, está bien, cálmate. Me voy.";
		link.l2.go = "CaptivePirate_2";
		break;

	case "CaptivePirate_2":
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		DialogExit();
		n = makeint(MOD_SKILL_ENEMY_RATE / 2);
		if (n <= 1)
			n = 2;
		for (i = 1; i <= n; i++)
		{
			sld = characterFromId("CaptivePirate_" + i);
			LAi_CharacterDisableDialog(sld);
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
		}
		sld = characterFromId("CaptiveSpain");
		LAi_SetImmortal(sld, true);
		sld.lifeday = 0;
		pchar.quest.Sharlie_captive1.over = "yes";
		pchar.quest.Sharlie_captive2.over = "yes"; // снять прерывание
		AddQuestRecord("SharlieD", "5");
		CloseQuestHeader("SharlieD");
		DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		pchar.questTemp.Sharlie = "bankskipermoney";
		break;

	case "CaptivePirate_3":
		dialog.text = "¿C-cómo? ¡Estás fanfarroneando, amigo! ¡A por él, muchachos, a las armas!";
		link.l1 = "¡Entonces, que sea bajo tu propio riesgo, en garde!";
		link.l1.go = "CaptivePirate_4";
		break;

	case "CaptivePirate_4":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		int n = makeint(MOD_SKILL_ENEMY_RATE / 2);
		if (n <= 1)
			n = 2;
		for (i = 1; i <= n; i++)
		{
			sld = characterFromId("CaptivePirate_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
		AddDialogExitQuest("MainHeroFightModeOn");
		sld = characterFromId("CaptiveSpain");
		LAi_SetCitizenType(sld);
		DoQuestFunctionDelay("Ngt_CaptiveEng", 0.5);
		break;

	// пленный испанец
	case "CaptiveSpain":
		dialog.text = "¡Gracias a Dios! Ah, ¿eres francés? ¡Mierda, te enfrentaste a esos bandidos con estilo! Pero no pienses que simplemente me rendiré, ¡te mostraré cómo pelea un español! ¡Santiago!";
		link.l1 = "¡No, espera, por favor!";
		link.l1.go = "CaptiveSpain_1";
		break;

	case "CaptiveSpain_1":
		dialog.text = "¡Preferiría morir antes, que ser capturado por los franceses! Tomé un alfanje de uno de los cadáveres mientras peleabas... ¡ahora te haré bailar una cuadrilla española!";
		link.l1 = "¡Vosotros los españoles sois tan tercos como mulas!";
		link.l1.go = "CaptiveSpain_2";
		break;

	case "CaptiveSpain_2":
		DialogExit();
		LAi_SetPlayerType(pchar);
		NextDiag.currentnode = "CaptiveSpain_3";
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "CaptiveSpain_3":
		dialog.text = "Maldito... Ganaste. Me rindo, maldito francés. Estoy a tu merced.";
		link.l1 = "¡Guarda tu espada y déjame hablar, testarudo castellano! No quiero que mueras, y tampoco te voy a mandar a la cárcel.";
		link.l1.go = "CaptiveSpain_4";
		RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;

	case "CaptiveSpain_4":
		dialog.text = "¿Entonces qué estás haciendo? ¿Por qué mataste a los piratas? ¿Y dónde están tus soldados?";
		link.l1 = "No hay soldados. Intenté engañar a los granujas, pero como puedes ver a nuestro alrededor, no funcionó. Estoy aquí solo, según la petición de tu viejo amigo. Su nombre es " + pchar.questTemp.Sharlie.Captive.Name + ", es un banquero en Saint-Pierre.";
		link.l1.go = "CaptiveSpain_5";
		break;

	case "CaptiveSpain_5":
		dialog.text = "" + pchar.questTemp.Sharlie.Captive.Name + "¿No conozco a nadie con ese nombre...?";
		link.l1 = "Ni sabía nada de ti ni de tu cautiverio. Me enteré de tu traslado a un barco inglés por él. Mi tarea es entregarte a él y juré que lo cumpliría. Ahora, ven conmigo si quieres vivir.";
		link.l1.go = "CaptiveSpain_6";
		break;

	case "CaptiveSpain_6":
		dialog.text = "No tengo otra elección de todos modos... Este banquero tuyo no puede ser peor que los ingleses y su cocina atroz...";
		link.l1 = "Por fin estás tomando una decisión sabia. Ya basta de hablar por ahora, nos dirigimos a Saint-Pierre. Mantente cerca de mí y no te desvíes. Si huyes, te atraparé y te golpearé casi hasta matarte otra vez.";
		link.l1.go = "CaptiveSpain_7";
		break;

	case "CaptiveSpain_7":
		chrDisableReloadToLocation = false;
		DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
		DialogExit();
		AddQuestRecord("SharlieD", "6");
		LAi_group_Register("TempFriends");
		LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(npchar, "TempFriends");
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
		pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
		pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
		pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
		pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
		pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
		pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
		pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
		pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
		pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload"; // вход ночью
		pchar.questTemp.Sharlie = "bankskipercaptive";
		SetFunctionLocationCondition("CaptiveSpain_removeGuard", "fortfrance_town", 0);
		SetFunctionLocationCondition("CaptiveSpain_saveTip", "fortfrance_exittown", 0);
		LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
		// Rebbebion, новые марки до места назначения. belamour поправил - были не в ту сторону
		QuestPointerToLoc("shore39", "reload", "reload1_back");
		QuestPointerToLoc("martinique_jungle_03", "reload", "reload1_back");
		QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
		QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
		QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
		QuestPointerToLoc("fortfrance_town", "reload", "reload8_back");
		AddLandQuestMark(characterFromId("FortFrance_Usurer"), "questmarkmain");
		break;

	// горожанин с пропавшей дочерью
	case "Prosper":
		DelLandQuestMark(npchar);
		pchar.quest.Sharlie_RescueDaughter.over = "yes"; // снять прерывание
		dialog.text = "¿Qué necesita, monsieur? No tengo tiempo para charlas, así que sea breve.";
		link.l1 = "¿Eres Prosper Trubal, no es así?";
		link.l1.go = "Prosper_1";
		break;

	case "Prosper_1":
		dialog.text = "Sí, ese soy yo. Pero tienes ventaja sobre mí. Por favor, infórmame de quién eres y qué demonios quieres.";
		link.l1 = "Mi nombre es " + GetFullName(pchar) + ". Me han enviado a ti por " + GetFullName(characterFromId("Fortfrance_portman")) + ", el capitán del puerto. Dijo que necesitabas ayuda urgente...";
		link.l1.go = "Prosper_2";
		break;

	case "Prosper_2":
		dialog.text = "¡Dios mío, sí! ¡Ese bribón de comandante ni siquiera escuchó mi queja! O es demasiado perezoso o cobarde para ayudar. ¿De verdad has venido a ayudarme? Si es así, no te dejaré sin recompensa.";
		link.l1 = "Sí, Prosper. Dime qué sucedió y qué debo hacer para ayudar. He escuchado que tu hija desapareció...";
		link.l1.go = "Prosper_3";
		break;

	case "Prosper_3":
		dialog.text = "Sí, mi querida hija Celene ha estado desaparecida durante dos días. Fue a dar un paseo al fuerte no muy lejos de aquí. Pero no regresó, así que fui al fuerte yo mismo y los soldados me dijeron que nunca había estado allí.\nPero luego, al regresar, ¡fui atacado por dos indios salvajes! Saltaron sobre mí con garrotes y trataron de golpearme.\n¡Pero no soy un gatito!, así que le di un puñetazo a uno en la cara, me compré el tiempo suficiente para sacar mi pistola y disparar. Fallé, pero los asusté. Logré llegar a las puertas de la ciudad y le conté a los guardias sobre el ataque. Corrieron hacia la jungla, pero los salvajes ya se habían ido hace mucho.\nEstoy seguro de que son responsables de la desaparición de Celene. Además, encima de eso, ¡dos personas más han desaparecido la semana pasada, Cesar Blanchet y Gilbert Courcy! Uno se dirigía a la bahía y otro a Le Francois. Nunca regresaron.";
		link.l1 = "¿Así que los indios han estado atacando a la gente del pueblo justo en las puertas de la ciudad? Eso es increíblemente audaz...";
		link.l1.go = "Prosper_4";
		break;

	case "Prosper_4":
		dialog.text = "Mientras tanto, yo mismo fui a la selva a buscarla y encontré una cueva al norte de la ciudad. Encontré a los bastardos acampando allí. Vi a varios indios en la entrada, pero algunos de ellos deben estar dentro también\nEscuché a una chica gritar... Era mi Celene, estoy seguro de eso, ¡era su voz! Me tomó toda mi contención no entrar corriendo en ese mismo momento, las probabilidades no estaban a mi favor y me habrían destrozado. No le sirvo de nada muerto.";
		link.l1 = "¿Pero por qué demonios están atacando y tomando a los habitantes del pueblo como prisioneros?";
		link.l1.go = "Prosper_5";
		break;

	case "Prosper_5":
		dialog.text = "No sé... ¿Quizás para venderlos a piratas o esclavistas? Tal vez simplemente se los coman vivos, después de todo, son unos salvajes.";
		link.l1 = "Querido Dios en el Cielo, ¿son caníbales? Pensé que eso eran solo cuentos para asustar a los niños en Europa...";
		link.l1.go = "Prosper_6";
		break;

	case "Prosper_6":
		dialog.text = "¿Historias? Bueno, algunos hombres como tú pensaron lo mismo hasta que los caribes los cocinaron en una hoguera y se los comieron... Así que, de inmediato me dirigí al comandante y solicité una incursión punitiva para salvar a mi Celene. ¡Se negó! Dijo que cuando las chicas desaparecen, probablemente se escaparon con un chico, no con los indios. Me sugirió buscarla en los pajares locales\nY en cuanto a los otros dos desaparecidos... dijo que uno de ellos estaba bajo sospecha de contrabando, y que el otro probablemente está bebiendo hasta morir en la taberna de Le Francois. En resumen, no he logrado nada y decidí actuar por mi cuenta.";
		link.l1 = "¿Qué piensas hacer?";
		link.l1.go = "Prosper_7";
		break;

	case "Prosper_7":
		dialog.text = "Iré allí y mataré a cada uno de esos malditos rojos. Solo espero que Celene aún viva. Como puedes ver, compré un mosquete y sé cómo dispararlo. Pagué mucho por él, pero me importa un bledo\nMi misión será mucho más fácil si me acompañas. Juntos podemos acabar con los salvajes sin mucho problema si puedes cubrirme mientras recargo. ¿Vendrás conmigo a salvar a mi hija?";
		link.l1 = "¡Por supuesto! ¡Es una cuestión de honor! No puedo permitir que una chica muera por el cuchillo de algún salvaje.";
		link.l1.go = "Prosper_8";
		if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "")
		{
			link.l1.go = "Prosper_noweapon";
		}
		link.l2 = "Hum. Sabes, creo que las palabras del comandante tienen sentido. ¿Quizás deberíamos seguir primero su consejo?";
		link.l2.go = "Prosper_exit";
		break;

	case "Prosper_noweapon":
		dialog.text = "Monsieur, ¿dónde está vuestra espada?";
		link.l1 = "Creo que lo he extraviado.";
		link.l1.go = "Prosper_noweapon_1";
		break;

	case "Prosper_noweapon_1":
		dialog.text = "Eso simplemente no servirá. Te esperaré hasta la tarde, te aconsejo que te arrastres a los pies de nuestro gobernador y le supliques por su ayuda.";
		link.l1 = "¿Arrastrarme a sus pies, eh? Bueno, como desees...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Prosper_getweapon";
		SetFunctionTimerConditionParam("RescueDaughter_Over", 0, 0, 0, 22, false);
		break;

	case "Prosper_getweapon":
		dialog.text = "Bueno, monsieur, ¿te has hecho con un arma?";
		if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "")
		{
			link.l1 = "Aún no, por favor espera un poco más...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prosper_getweapon";
		}
		else
		{
			link.l1 = "Entendido. ¡Estoy listo para ayudarte!";
			link.l1.go = "Prosper_8";
			DeleteQuestCondition("RescueDaughter_Over");
		}
		break;

	case "Prosper_exit":
		dialog.text = "¡Dios mío!, ¿estás huyendo? ¡No! ¡Lárgate al diablo de aquí! ¡Cobarde!";
		link.l1 = "¡Hey-hey, tranquilo, simpletón! Será mejor que salga a ver si algún noble en las calles de Saint-Pierre necesita ayuda.";
		link.l1.go = "Prosper_exit_1";
		pchar.questTemp.Sharlie.GigoloMan.SamPodbezhit = true;
		break;

	case "Prosper_exit_1":
		DialogExit();
		npchar.lifeday = 0;
		// AddTimeToCurrent(2,0);
		SetCurrentTime(17, 30);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
		CloseQuestHeader("SharlieF");
		chrDisableReloadToLocation = true;

		// Подбегает дворянин с квестом "девочка по вызову"
		sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
		SetFantomParamFromRank(sld, 25, true);
		sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
		sld.dialog.currentnode = "GigoloMan";
		sld.greeting = "noble_male";
		AddLandQuestMark(sld, "questmarkmain");
		LAi_SetLoginTime(sld, 6.0, 21.0);
		LAi_SetImmortal(sld, true);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "Prosper_8":
		dialog.text = "Me alegra que al menos haya un hombre valiente en este pueblo. Aquí, toma estos tres frascos. Son hierbas curativas, las compré a nuestro herbolario. Pueden ser de gran ayuda para ti en batalla.";
		link.l1 = "¿Y tú?";
		link.l1.go = "Prosper_9";
		break;

	case "Prosper_9":
		TakeNItems(pchar, "potion1", 3);
		PlaySound("interface\important_item.wav");
		dialog.text = "No te preocupes, tengo más. ¿Estás listo?";
		link.l1 = "Sí, no perdamos tiempo. ¡Adelante!";
		link.l1.go = "Prosper_10";
		break;

	case "Prosper_10":
		DialogExit();
		chrDisableReloadToLocation = true;
		LAi_SetImmortal(npchar, true);
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "gate_back", "fortfrance_exittown", "reload", "reload3", "OpenTheDoors", 10.0);
		PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1 = "location";
		PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1.location = "FortFrance_ExitTown";
		PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition = "RescueDaughter_ProsperGateOutReload";
		AddQuestRecord("SharlieF", "3");
		pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
		pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
		pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
		pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
		pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour = sti(GetTime() + 2);
		pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
		NextDiag.CurrentNode = "Prosper_11";
		pchar.questTemp.Sharlie.RescueDaughter = "true";
		LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", true);	 // форт
		LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", true); // джунгли
		LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", true); // джунгли
		break;

	case "Prosper_11":
		dialog.text = "Estamos casi en posición, " + pchar.name + ". Más allá de esta curva está la entrada a la cueva. Acércate y te contaré nuestro plan.";
		link.l1 = "Soy todo oídos, Prosper.";
		link.l1.go = "Prosper_12";
		break;

	case "Prosper_12":
		dialog.text = "Necesito apuntar con precisión con este pesado arcabuz, pero si puedes darme tiempo, no fallaré. Si tengo que entrar en combate cuerpo a cuerpo, olvídate del apoyo de fuego; solo podré defenderme usando el cañón como garrote. Esta pelea dependerá de tu habilidad en la esgrima.";
		link.l1 = "¿Qué estás tratando de decir?";
		link.l1.go = "Prosper_13";
		break;

	case "Prosper_13":
		dialog.text = "Todo lo que necesitas es distraer su atención para que yo pueda dispararles a todos. No puedo moverme y disparar, así que me quedaré en un lugar. Hay tres bastardos cerca de la entrada de la cueva. Deberías lanzarte sobre ellos tan rápido como puedas con tu espada en mano\nGolpea a uno de ellos y haz que te persigan. Aléjalos de mí. Si los tres se enfocan en ti, puedo dispararles como a pájaros mientras tú paras y esquivas. Pero si esos salvajes se abalanzan sobre mí, estamos condenados. ¿Estás listo?";
		link.l1 = "Esta no será la primera vez que manejo una espada, estos salvajes no son una amenaza.";
		link.l1.go = "Prosper_14";
		// belamour legendary edition -->
		link.l2 = "¡Ja! No te preocupes por mí. ¡Es como cazar en Le Mans! Solo no me dispares por la espalda por error.";
		link.l2.go = "Prosper_14a";
		break;

	case "Prosper_14a":
		AddCharacterExpToSkill(pchar, "FencingL", 10);
		AddCharacterExpToSkill(pchar, "FencingS", 10);
		AddCharacterExpToSkill(pchar, "FencingH", 10);
		AddCharacterExpToSkill(pchar, "Pistol", 10);
		dialog.text = "Ve primero, estoy detrás de ti. Recuerda: ¡no debes dejar que se acerquen a mí!";
		link.l1 = "Recuerdo, vamos. ¡Adelante!";
		link.l1.go = "Prosper_15";
		break;

	case "Prosper_14":
		AddCharacterExpToSkill(pchar, "Leadership", 40);
		// <-- legendary edition
		dialog.text = "Entonces prepárate para la acción. Ve primero, yo estaré detrás de ti. Recuerda: ¡no puedes dejar que se acerquen demasiado a mí!";
		link.l1 = "Recuerdo. Haré todo lo que pueda. ¡Adelante!";
		link.l1.go = "Prosper_15";
		break;

	case "Prosper_15":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
		NextDiag.CurrentNode = "Prosper_16";
		NewGameTip("Nos espera una lucha difícil. (F6) para guardar rápidamente.");
		break;

	case "Prosper_16":
		dialog.text = "Bien hecho, " + pchar.name + "¡Estos paganos salvajes no asesinarán más! Ahora, al evento principal: la cueva. Creo que hay tres o cuatro de ellos dentro, pero no puedo saberlo con certeza. Ahora escucha\nHe estado allí hace diez años. Hay un túnel estrecho dentro de la cueva. Conduce a una pequeña gruta, dividida por una pared con un agujero en el medio. Repitamos nuestro plan de antes. Yo me quedo cerca de la entrada y tú te precipitas\nProvócalos, no intentes luchar contra todos de una vez, solo impide que me ataquen. Toma posición en el túnel que mencioné, es estrecho, así que solo uno o dos de ellos podrán pelear contigo al mismo tiempo\nYo les dispararé sobre tu hombro. ¿Listo?";
		link.l1 = "¡Adelante! ¡Terminemos con este nido de salvajes!";
		link.l1.go = "Prosper_17";
		break;

	case "Prosper_17":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
		AddComplexSelfExpToScill(20, 20, 20, 20);
		pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
		pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
		pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
		NextDiag.CurrentNode = "Prosper_18";
		break;

	case "Prosper_18":
		dialog.text = "¡Mi hija está viva! ¡Gracias a Dios! Hemos llegado a tiempo, " + pchar.name + " Estoy en deuda con usted, señor. ¡Es un hombre valiente y un buen luchador!";
		link.l1 = "Me alegra que haya un final feliz, Prosper. Fue un trabajo bastante sangriento acabar con todos esos indios.";
		link.l1.go = "Prosper_19";
		break;

	case "Prosper_19":
		DialogExit();
		sld = characterFromId("RD_Selina");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
		break;

	case "Prosper_20":
		dialog.text = "Mis más profundos agradecimientos una vez más, " + pchar.name + "¡ Ahora volvamos al pueblo. La vida de mi hija no tiene precio, es inconmensurable por cualquier cantidad de dinero, pero quiero agradecerte dándote lo que queda de mis ahorros. Tan pronto como lleguemos a Saint-Pierre, te los daré con gusto. ¡Y ni se te ocurra rechazarlo!";
		link.l1 = "No me negaré, Prosper. Aunque el dinero no fue mi objetivo al ayudarte.";
		link.l1.go = "Prosper_21";
		break;

	case "Prosper_21":
		dialog.text = "Eres un verdadero caballero cristiano, " + pchar.name + "¡Ahora no nos entrometamos aquí. Regresemos a casa cuanto antes!";
		link.l1 = "...";
		link.l1.go = "Prosper_22";
		break;

	case "Prosper_22":
		chrDisableReloadToLocation = false;
		DialogExit();
		LAi_SetImmortal(npchar, true);
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		sld = characterFromId("RD_Selina");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		sld = characterFromId("RD_Jilberte");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		pchar.quest.Tutorial_Amulet.over = "yes";
		SetLaunchFrameFormParam("De vuelta a la ciudad...", "Reload_To_Location", 0, 3.0);
		SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "gate_back", "");
		LaunchFrameForm();
		break;

	case "Prosper_23":
		SelectPresentAmulet();
		dialog.text = "Aquí estamos, Charles. Te agradezco una vez más por tu ayuda y ato esta modesta suma de pesos y doblones de oro a mis palabras. Te sugiero que no desperdicies los doblones y los guardes para ocasiones especiales. Sé que no es mucho dinero por el servicio que me has brindado, pero viene del fondo de mi corazón. También toma este amuleto, " + pchar.questTemp.SMQ.Text + "";
		link.l1 = "¡Gracias! ¡Adiós Prosper, deseo felicidad a ti y a tu querida hija!";
		link.l1.go = "Prosper_24";
		break;

	case "Prosper_24":
		LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", false);  // форт
		LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", false); // джунгли
		LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", false); // джунгли
		AddMoneyToCharacter(pchar, 5000);
		TakeNItems(pchar, "gold_dublon", 15);
		TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
		Log_Info("Has recibido 15 doblones");
		Log_Info("Has recibido un amuleto");
		PlaySound("interface\important_item.wav");
		dialog.text = "Ah, un marido como tú le vendría bien. Todo lo que hace es ser perseguida por la ciudad por un montón de fatuos sin barbilla y de patas flacas. Qué maldita lástima que cada uno de ellos se haya esfumado en algún lugar... que se los lleve el diablo. ¡Buena suerte, Charles!";
		link.l1 = "...";
		link.l1.go = "Prosper_25";
		break;

	case "Prosper_25":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
		sld = characterFromId("RD_Selina");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
		ChangeCharacterComplexReputation(pchar, "nobility", 3);
		ChangeCharacterComplexReputation(pchar, "authority", 2);
		AddCharacterExpToSkill(pchar, "Leadership", 120); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 70);	  // везение
		AddCharacterExpToSkill(pchar, "Sneak", 70);		  // скрытность
		AddQuestRecord("SharlieF", "7");
		CloseQuestHeader("SharlieF");
		DeleteAttribute(pchar, "questTemp.SMQ");
		pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
		pchar.questTemp.ZsI_Cannibals = true;  // Sinistra Требуется для квеста "Знакомство с индейцами"
		pchar.quest.Sharlie_JungleNative.win_condition.l1 = "location";
		pchar.quest.Sharlie_JungleNative.win_condition.l1.location = "Martinique_jungle_01";
		pchar.quest.Sharlie_JungleNative.function = "SharlieJungleNative";
		SetCurrentTime(17, 30);
		// AddTimeToCurrent(2,0);
		// QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
		sld = characterFromId("RD_Jilberte");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "Selina":
		dialog.text = "¡Ah! ¡Dios ayúdame! (llora) ¡Tú... tú ni siquiera puedes imaginar el horror que está sucediendo aquí! ¡Estos... estos indios nos han arrastrado aquí para matarnos y comernos! Cesar Blanchet estuvo aquí... Los salvajes lo llevaron... Realizaron algún espantoso ritual demoníaco y luego... ¡Señor, ni siquiera puedo hablar de ello! ¡Se suponía que yo iba a ser el siguiente! Iban a matarme... ¡mañana!";
		link.l1 = "Tranquila, Celine. Todo ha terminado. Esos bastardos han obtenido lo que se merecían y ya no harán daño a nadie más.";
		link.l1.go = "Selina_1";
		break;

	case "Selina_1":
		dialog.text = "Gilbert Coursie también está aquí. Por allá... él, uh... todavía no se ha recuperado. Habla con él... ¡Entonces apresurémonos y salgamos de aquí!";
		link.l1 = "Ahí, ahí. Está bien, chica. Basta de llorar. Todo está bien. Tienes un padre maravilloso. No dejaría que nadie te hiciera daño... Sal afuera, ayudaré a... eh... Gilbert a salir de aquí y te alcanzaré más tarde.";
		link.l1.go = "Selina_2";
		break;

	case "Selina_2":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
		sld = characterFromId("RD_Prosper");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
		AddQuestRecord("SharlieF", "5");
		sld = characterFromId("RD_Jilberte");
		LAi_SetStayType(sld);
		break;

	case "Selina_3":
		dialog.text = "¡Dios y la Santísima Madre han escuchado mis oraciones! ¿Has venido a salvarnos?";
		link.l1 = "Tú... Tu nombre es Celine, ¿no es así?";
		link.l1.go = "Selina_4";
		break;

	case "Selina_4":
		dialog.text = "Sí... (llora) ¡Tú... tú ni siquiera puedes imaginar el horror que está pasando aquí! ¡Estos... estos indios nos han arrastrado aquí para matarnos y comernos! Cesar Blanchet estuvo aquí... Lo llevaron... Hicieron algún ritual diabólico y luego... ¡Señor, ni siquiera puedo hablar de ello! ¡Se supone que seré el siguiente! Iban a sacrificarme... ¡mañana!";
		link.l1 = "Tranquila, jovencita... Lo siento, pero te traigo malas noticias. Vine aquí con tu padre. Fue asesinado justo afuera por esos salvajes de piel roja mientras luchábamos por llegar a ti. Dio su vida para salvarte.";
		link.l1.go = "Selina_5";
		break;

	case "Selina_5":
		dialog.text = "¿Qué?! Mi padre... ¡Oh Dios! Yo... Yo... (sollozando)";
		link.l1 = "Mis condolencias, Celine. Hay otro aquí contigo, ¿verdad?";
		link.l1.go = "Selina_6";
		break;

	case "Selina_6":
		dialog.text = "(con lágrimas) Sí... Gilbert Coursie. Está ahí... Aún no se ha recuperado. Ve a hablar con él... ¡Entonces salgamos de aquí rápido!";
		link.l1 = "Sí, por supuesto. No podemos perder ni un minuto aquí parados.";
		link.l1.go = "Selina_7";
		break;

	case "Selina_7":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
		AddQuestRecord("SharlieF", "6");
		sld = characterFromId("RD_Jilberte");
		LAi_SetStayType(sld);
		AddComplexSelfExpToScill(20, 20, 20, 20);
		break;

	case "Selina_8":
		dialog.text = "Mi padre... ¡Mi pobre, querido padre! Ah, monsieur, ni siquiera le he agradecido por salvarme...";
		link.l1 = "Selina, me alegra que tú y Gilbert salierais con vida de esa cueva. La heroica muerte de tu padre no fue en vano.";
		link.l1.go = "Selina_9";
		break;

	case "Selina_9":
		dialog.text = "(llora) Por favor, monsieur, llévenos con usted a la ciudad. Tenemos que enviar por los soldados para que vengan a recoger el cuerpo de mi padre, para que tenga un entierro cristiano adecuado...";
		link.l1 = "Por supuesto, Celine. ¡Sígueme!";
		link.l1.go = "Selina_10";
		break;

	case "Selina_10":
		chrDisableReloadToLocation = false;
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		sld = characterFromId("RD_Jilberte");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		break;

	case "Selina_11":
		dialog.text = "Gracias, monsieur, por acompañar a mi pobre padre... Gracias por salvarme de una muerte segura. Yo... Yo... Aquí, toma esta bolsa de doblones. La encontré en casa en el cofre de mi padre. Por favor, ¡ni se te ocurra pensar en rechazarla!";
		link.l1 = "Gracias, Celine. Me alegra que lográramos salvarte. Y mis más sinceras condolencias por la pérdida de tu padre.";
		link.l1.go = "Selina_12";
		break;

	case "Selina_12":
		TakeNItems(pchar, "gold_dublon", 15);
		PlaySound("interface\important_item.wav");
		dialog.text = "Eres un hombre noble, monsieur. Nunca te olvidaré. ¡Adiós!";
		link.l1 = "Adiós, Celine.";
		link.l1.go = "Selina_13";
		break;

	case "Selina_13":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
		npchar.lifeday = 0;
		ChangeCharacterComplexReputation(pchar, "nobility", 3);
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		AddCharacterExpToSkill(pchar, "Leadership", 100); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 50);	  // везение
		AddCharacterExpToSkill(pchar, "Sneak", 50);		  // скрытность
		AddQuestRecord("SharlieF", "8");
		CloseQuestHeader("SharlieF");
		pchar.questTemp.ZsI_Cannibals = true; // Sinistra Требуется для квеста "Знакомство с индейцами"

		sld = characterFromId("RD_Jilberte");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "Jilberte":
		PlaySound("Voice\Spanish\other\robinzons-09.wav");
		dialog.text = "¡Oh Señor, ¿realmente todo ha quedado atrás? No puedo ni creerlo... Me has salvado tanto a mí, como a Celine. Si no fuera por ti, el mismo destino que le ocurrió al desdichado Cesar habría llamado a ella mañana y lo mismo estaría preparado para mí en unos días.";
		link.l1 = "¿Estos indios, son realmente caníbales?!";
		link.l1.go = "Jilberte_1";
		break;

	case "Jilberte_1":
		dialog.text = "¿Lo dudas? Si tienes un estómago fuerte, echa un vistazo a las cenizas de su fogata. Encontrarás al pobre viejo César allí. Ahora es solo unos huesos roídos...";
		link.l1 = "Bendito Sacramento... No, pasaré. Recién he llegado aquí desde Europa y ni siquiera podía imaginar que tales cosas viles y diabólicas todavía ocurren en la Tierra.";
		link.l1.go = "Jilberte_2";
		break;

	case "Jilberte_2":
		dialog.text = "Muchas cosas extrañas suceden en el Caribe, cosas de las que oíste susurros en el Viejo Mundo... Médicos indios, magia, chamanes y rituales secretos. Quédate aquí más tiempo y serás testigo de todo tipo de brujería. Pero discúlpame, no te he agradecido por salvarme, todavía estoy en shock. \nMe salvaste la vida y voy a expresar mi gratitud no solo con palabras, sino también con oro. Escolta a Celine y a mí a la ciudad. Allí podré agradecerte como te mereces, monsieur.";
		link.l1 = "Está bien. Salgamos afuera. Primero voy a echar un vistazo por aquí.";
		link.l1.go = "Jilberte_3";
		break;

	case "Jilberte_3":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
		pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
		pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
		pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;

	case "Jilberte_4":
		dialog.text = "Permítame expresarle una vez más mi profunda gratitud por salvarme, ¡señor! Como prometí, añado a mi gratitud verbal una gratitud material en forma de pesos de plata y doblones de oro.";
		link.l1 = "Me alegra que todo haya salido bien, Gilbert.";
		link.l1.go = "Jilberte_5";
		break;

	case "Jilberte_5":
		AddMoneyToCharacter(pchar, 3000);
		TakeNItems(pchar, "gold_dublon", 20);
		Log_Info("Has recibido 20 doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "¡No puedes ni imaginar lo feliz que estoy por esto! Gracias una vez más y permítame retirarme, monsieur.";
		link.l1 = "¡Buena suerte, Gilbert! Por cierto, ¿sabes si alguien más en Saint-Pierre necesita ayuda?";
		link.l1.go = "Jilberte_6a";
		break;

	case "Jilberte_6a":
		dialog.text = "No lo sé, pero... Puedes preguntar a los ciudadanos en las calles, Monsieur. Es poco probable que los habitantes comunes, e incluso los más acomodados, ofrezcan algo digno, pero los nobles ricos... pueden tener algún trabajo para ti.";
		link.l1 = "Entendido, Gilbert, gracias. ¡Nos vemos!";
		link.l1.go = "Jilberte_6";
		break;

	case "Jilberte_6":
		chrDisableReloadToLocation = false;
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		npchar.lifeday = 0;
		DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");

		// Подбегает дворянин с квестом "девочка по вызову"
		sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
		SetFantomParamFromRank(sld, 25, true);
		sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
		sld.dialog.currentnode = "GigoloMan";
		sld.greeting = "noble_male";
		AddLandQuestMark(sld, "questmarkmain");
		LAi_SetLoginTime(sld, 6.0, 21.0);
		LAi_SetImmortal(sld, true);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
		sld.talker = 9;
		LAi_SetCitizenType(sld);
		break;

	// замечание по обнажённому оружию от персонажей типа citizen
	case "CitizenNotBlade":
		dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy un ciudadano respetuoso de la ley en esta ciudad. Debo pedirte que no andes por ahí con tu espada desenvainada como un ladrón.", "Señor, por favor, la ley es clara: los hombres no pueden andar con armas desenfundadas dentro de las murallas de la ciudad.");
		link.l1 = LinkRandPhrase("Está bien.", "Muy bien.", "Como desees...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		if (npchar.id == "GigoloMan")
			NextDiag.TempNode = "GigoloMan";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{
	case "HeroType_1":
		pchar.questTemp.SMQ.Amulet = "indian_7";
		pchar.questTemp.SMQ.Text = "añade resistencia y da un segundo soplo.";
		break;

	case "HeroType_2":
		pchar.questTemp.SMQ.Amulet = "amulet_7";
		pchar.questTemp.SMQ.Text = "aumenta la resistencia a las heridas de batalla.";
		break;

	case "HeroType_3":
		pchar.questTemp.SMQ.Amulet = "indian_4";
		pchar.questTemp.SMQ.Text = "aumenta la fuerza de ataque de tus armas.";
		break;

	case "HeroType_4":
		pchar.questTemp.SMQ.Amulet = "indian_1";
		pchar.questTemp.SMQ.Text = "hace que las armas de fuego sean mucho más letales.";
		break;
	}
}
