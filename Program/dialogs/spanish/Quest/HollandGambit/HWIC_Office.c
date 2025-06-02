// НПС офиса ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Quieres algo?";
		link.l1 = "No.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// офицер
	case "HWIC_officer":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = "¡Alarma! ¡El enemigo está aquí! ¡A las armas!";
			link.l1 = "¡Maldita sea!";
			link.l1.go = "fight";
			break;
		}
		if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
		{
			dialog.text = "¡Tú ahí, alto! Tu cara me resulta familiar...¡por supuesto! ¡Eres buscado por tus crímenes! ¡Chicos, agárrenlo!";
			link.l1 = "¡Maldita sea!";
			link.l1.go = "fight";
			break;
		}
		chrDisableReloadToLocation = true;
		if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "Bienvenido a la Compañía Holandesa de las Indias Occidentales. Habla rápido, el tiempo es dinero.";
			link.l1 = "Estoy aquí por asuntos de comercio. Licencias, instrumentos de navegación y demás...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "Quiero ofrecer mis servicios a la Compañía. A cambio de oro, por supuesto. ¿Estáis contratando?";
			link.l2.go = "HWIC_officer_1";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			dialog.text = "Bienvenido a la Compañía Holandesa de las Indias Occidentales. Habla rápido, el tiempo es dinero.";
			link.l1 = "Lamento, parece que me equivoqué. Me marcho.";
			link.l1.go = "HWIC_officer_exit";
			link.l2 = "Estoy aquí por asuntos de comercio. Licencias, instrumentos de navegación y así sucesivamente...";
			link.l2.go = "HWIC_officer_3";
			break;
		}
		dialog.text = "Habla rápido, el tiempo es dinero.";
		link.l1 = "Estoy aquí por asuntos de comercio. Licencias, instrumentos de navegación y demás...";
		link.l1.go = "HWIC_officer_3";
		link.l2 = "Quiero ofrecer mis servicios a la Compañía. A cambio de oro, por supuesto. ¿Están contratando?";
		link.l2.go = "HWIC_officer_2";
		break;

	case "HWIC_officer_1":
		dialog.text = "Entonces sube a la oficina del señor Rodenburg.";
		link.l1 = "Gracias, estoy en camino.";
		link.l1.go = "HWIC_officer_exit";
		// belamour legendary edition переехали по другому адресу
		LocatorReloadEnterDisable("GVIK", "reload2", false); // кабинет откроем
		break;

	case "HWIC_officer_2":
		dialog.text = "La Compañía no está contratando en este momento.";
		link.l1 = "Eso es una lástima. Perdona por molestarte.";
		link.l1.go = "HWIC_officer_exit";
		break;

	case "HWIC_officer_3":
		dialog.text = "Habla con Mynheer Gerritz. Su mesa está a tu izquierda al entrar. Hace negocios con capitanes contratados.";
		link.l1 = "Gracias, oficial...";
		link.l1.go = "HWIC_officer_exit";
		break;

	case "HWIC_officer_exit":
		DialogExit();
		// belamour legendary edition переехали
		LAi_ActorGoToLocation(npchar, "soldiers", "soldier3", "GVIK", "soldiers", "soldier3", "", 5);
		DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
		NextDiag.TempNode = "HWIC_officer";
		break;

	// солдаты
	case "HWIC_soldier":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = "¡Alarma! ¡El enemigo está aquí! ¡A las armas!";
			link.l1 = "¡Maldita sea!";
			link.l1.go = "fight";
			break;
		}
		if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
		{
			dialog.text = "¡Ajá! Creo que sé quién eres... ¡Pero claro! ¡Eres buscado por tus crímenes! ¡Muchachos, tomenlo!";
			link.l1 = "¡Maldita sea!";
			link.l1.go = "fight";
			break;
		}
		dialog.text = "Habla con nuestros oficiales o con el señor Gerritz. No tengo nada que decirte. Estoy de servicio.";
		link.l1 = "Tu disciplina es admirable.";
		link.l1.go = "exit";
		NextDiag.TempNode = "HWIC_soldier";
		break;

	// клерки
	case "HWIC_clerk":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = "¡Alarma! ¡El enemigo está aquí! ¡Soldados!";
			link.l1 = "¡Maldita sea!";
			link.l1.go = "fight";
			break;
		}
		dialog.text = "Habla con Mynheer Gerritz.";
		link.l1 = "Está bien, lo entiendo.";
		link.l1.go = "exit";
		NextDiag.TempNode = "HWIC_clerk";
		break;

	// главный клерк - минхер Герритц
	case "HWIC_headclerk":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = "¡Alarma! ¡El enemigo está aquí! ¡Soldados, atrapadlo!";
			link.l1 = "¡Maldita sea!";
			link.l1.go = "fight";
			break;
		}
		if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
		{
			dialog.text = "Hum. Creo que hay algo raro en ti... ¡Pero claro! ¡Eres buscado por tus numerosos crímenes contra Holanda! ¡Soldados, llévenselo!";
			link.l1 = "¡Maldita sea!";
			link.l1.go = "fight";
			break;
		}
		dialog.text = "¿Desea algo, señor?";
		if (!CheckCharacterItem(pchar, "HolTradeLicence"))
		{
			link.l1 = "Quiero comprar una licencia de comercio de la Compañía Holandesa de las Indias Occidentales.";
			link.l1.go = "licence";
		}
		if (!CheckAttribute(npchar, "quest.trade"))
		{
			link.l2 = "Escuché que es posible comprar instrumentos de navegación y otros objetos útiles aquí. ¿Es eso cierto?";
			link.l2.go = "trade";
		}
		else
		{
			link.l2 = "¿Qué vendes hoy?";
			link.l2.go = "trade_1";
		}
		if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
		{
			link.l3 = "Tengo un documento interesante para usted, mynheer. Eche un vistazo a las primeras líneas. Concierne la supervivencia de la República y los beneficios de la Compañía. También están las coordenadas de cierta reunión. Se las venderé si está interesado. Por un precio generoso, por supuesto.";
			link.l3.go = "depeshe";
		}
		// калеуче
		if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
		{
			link.l4 = "Un capitán llamado Reginald Jackson debe estar trabajando para usted. Navega en un xebec llamado 'Harpy'. ¿Podría decirme cómo puedo encontrarlo? Tengo asuntos importantes con él.";
			link.l4.go = "caleuche";
		}
		// Sinistra Путеводная звезда
		if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
		{
			link.l4 = "Necesito ver al señor Rodenburg urgentemente. Es de suma importancia. ¿Dónde está?";
			link.l4.go = "PZ_RazgovorGerrits_1";
		}
		link.l9 = "No, es nada.";
		link.l9.go = "exit";
		NextDiag.TempNode = "HWIC_headclerk";
		break;

	// торговые лицензии
	case "licence":
		if (!CheckAttribute(npchar, "quest.licence"))
		{
			dialog.text = "Bien, eres libre de comprarlo. Pero debo advertirte que la Compañía valora su reputación de estricta neutralidad, por lo tanto, está prohibido atacar cualquier barco mercante de cualquier nación mientras poseas esta licencia.\nSi descubrimos que se ha cometido tal acto, anularemos tu licencia. Además, si entras en conflicto con los holandeses o la Compañía por cualquier motivo, tu licencia también será anulada. ¿Estamos claros?";
			link.l1 = "Claro como el cristal. Lo recordaré.";
			link.l1.go = "licence_0";
			npchar.quest.licence = true;
		}
		else
		{
			dialog.text = "Tienes la bienvenida para comprar una licencia. Entonces, ¿cuántos días?";
			link.l1.edit = 6;
			link.l1 = "";
			link.l1.go = "licence_1";
		}
		break;

	case "licence_0":
		dialog.text = "La licencia otorga libre paso a cualquier puerto de cualquier nación, muestra tus intenciones pacíficas y explica tu propósito: comerciar. Pero no te ayudará si tienes algún problema con la ley. Simplemente te la quitarán en ese caso. Recuerda, \nNo olvides izar una bandera amiga antes de entrar en cualquier puerto. Las patrullas y los artilleros de los fuertes prefieren disparar primero y preguntar después\nLa duración mínima de la licencia es de veinte días y la máxima es de seis meses o 180 días\nCierto, casi lo olvido... Según nuestras estimadas tradiciones, todos los tratos que involucran licencias se pagan en doblones. Ahora discutamos los términos. ¿Cuánto tiempo deseas que dure la licencia?";
		link.l1.edit = 6;
		link.l1 = "";
		link.l1.go = "licence_1";
		link.l2 = "Lo siento, pero tengo que pensarlo un poco más. Nos vemos más tarde.";
		link.l2.go = "exit";
		break;

	case "licence_1":
		float fQty = stf(dialogEditStrings[6]);
		npchar.quest.lcc_summ = makeint(sqrt(fQty) * 10) * 7;
		if (fQty < 1)
		{
			dialog.text = "Mynheer, por favor, hable claramente. No le escuché bien. ¿Entonces por cuánto tiempo?";
			link.l1 = "Déjame pensar...";
			link.l1.go = "licence_r";
			break;
		}
		if (fQty > 0 && fQty < 20)
		{
			dialog.text = "El plazo mínimo para la licencia es de veinte días. ¿Entonces? ¿Veinte días o más?";
			link.l1 = "Déjame pensar...";
			link.l1.go = "licence_r";
			break;
		}
		if (fQty > 180)
		{
			dialog.text = "El plazo máximo para la licencia es de medio año. ¿Ciento ochenta días o menos?";
			link.l1 = "Déjame pensar...";
			link.l1.go = "licence_r";
			break;
		}
		dialog.text = "¿Para " + FindRussianDaysString(sti(fQty)) + " días? Muy bien. Te costará " + FindRussianDublonString(sti(npchar.quest.lcc_summ)) + "¿Son aceptables esos términos?";
		if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
		{
			link.l1 = "Sí, lo son.";
			link.l1.go = "licence_2";
		}
		link.l2 = "Desafortunadamente, no tengo tanto dinero conmigo ahora. Volveré por la licencia más tarde.";
		link.l2.go = "exit";
		break;

	case "licence_r":
		dialog.text = "";
		link.l1.edit = 6;
		link.l1 = "";
		link.l1.go = "licence_1";
		link.l2 = "Lo siento, pero aún necesito pensarlo. Te veré más tarde.";
		link.l2.go = "exit";
		break;

	case "licence_2":
		int iQty = sti(dialogEditStrings[6]);
		RemoveDublonsFromPCharTotal(sti(npchar.quest.lcc_summ));
		GiveNationLicence(HOLLAND, iQty);
		// belamour legendary edition на пару с Акулой
		if (CheckAttribute(pchar, "questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "start")
		{
			if (iQty < 180)
			{
				Log_info("Misión: 'Junto a Shark' - tu licencia es inferior a 180 días");
			}
			else
			{
				pchar.questTemp.SharkGoldFleet.LicenceOk = true;
				AddQuestRecord("SharkGoldFleet", "2");
			}
			pchar.questTemp.SharkGoldFleet = "afterGvik";
		}
		dialog.text = "Espera un momento... Déjame poner un sello y una firma aquí... sellado y listo. Toma tu documento.";
		link.l1 = "¡Gracias! Adiós, señor.";
		link.l1.go = "exit";
		break;

	case "trade":
		dialog.text = "De hecho, sí. Aquí puedes comprar herramientas de navegación como brújulas, astrolabios, cronómetros y relojes de arena. Pero no siempre tenemos un stock completo listo para comprar, excepto quizás los relojes de arena. Nuestros contratistas y capitanes compran las otras herramientas muy rápidamente. Así que si no encuentras lo que necesitas, ven a vernos de nuevo en una semana cuando repongamos existencias. También vendemos mapas y catalejos. ¿Quieres ver lo que tenemos?";
		link.l1 = "Sí, por favor.";
		link.l1.go = "trade_1";
		npchar.quest.trade = "true";
		break;

	case "trade_1":
		DialogExit();
		if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
		{
			GiveItemToTrader(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "trade_date");
		}
		LaunchItemsTrade(npchar, 0);
		break;

	// депеша Кромвеля
	case "depeshe":
		dialog.text = "Mm, muéstrame...(leyendo) Bueno, bueno... El apetito de Cromwell está creciendo. ¡Kanker! ¿No derramaron esos perros puritanos suficiente sangre en su propia isla sin traer su suciedad aquí!? ¿De dónde obtuviste este despacho?";
		link.l1 = "Lo tomé de un mensajero inglés. ¿Te gustaría comprarlo?";
		link.l1.go = "depeshe_1";
		break;

	case "depeshe_1":
		dialog.text = "Sí. Peter Stuyvesant estará realmente encantado de leerlo, estoy seguro. Y tomará medidas efectivas para detenerlo... Puedo pagar con doblones de oro o puedo hacerte una licencia por un período de medio año. ¿Cuál prefieres?";
		link.l1 = "Elijo oro.";
		link.l1.go = "depeshe_dublon";
		link.l2 = "Quiero la licencia.";
		link.l2.go = "depeshe_licence";
		break;

	case "depeshe_dublon":
		TakeNItems(pchar, "gold_dublon", 700);
		Log_Info("Has recibido 700 doblones");
		dialog.text = "Muy bien. Aquí están tus setecientos doblones. Una recompensa generosa por un servicio bien hecho.";
		link.l1 = "Aquí está tu despacho.";
		link.l1.go = "depeshe_exit";
		break;

	case "depeshe_licence":
		if (CheckCharacterItem(pchar, "HolTradeLicence"))
			TakeNationLicence(HOLLAND);
		GiveNationLicence(HOLLAND, 180);
		dialog.text = "Bien. Aquí está tu licencia por un plazo de medio año.";
		link.l1 = "¡Gracias! Y aquí está tu despacho.";
		link.l1.go = "depeshe_exit";
		break;

	case "depeshe_exit":
		RemoveItems(pchar, "Cromvel_depeshe", 1);
		pchar.quest.Terrapin_CromvelScuadron.over = "yes"; // снять прерывание
		ChangeCharacterNationReputation(pchar, HOLLAND, 15);
		ChangeCharacterComplexReputation(pchar, "authority", 3);
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		dialog.text = "Bedankt. Es bueno que hayas mostrado tu conciencia y lealtad a la República. Le contaré a Matthias Beck y a Peter Stuyvesant sobre tu buena acción.";
		link.l1 = "Bueno saberlo. ¡Adiós!";
		link.l1.go = "exit";
		break;

	// Sinistra Путеводная звезда
	case "PZ_RazgovorGerrits_1":
		dialog.text = "Me temo que ya se ha marchado al Viejo Mundo con la familia Schneur. Creo que te lo mencionó.";
		link.l1 = "Así es, lo hizo. Pero esperaba que pudiera haberse retrasado por algún negocio reciente en el Archipiélago. Dime, Gerritz, ¿alguien en la Compañía mantiene contacto con el señor Rodenburg? ¿Quizás a través de barcos mensajeros?";
		link.l1.go = "PZ_RazgovorGerrits_2";
		break;

	case "PZ_RazgovorGerrits_2":
		dialog.text = "No en absoluto - antes de irse, nos pidió que nunca lo molestáramos - dijo que estaba comenzando una nueva y mejor vida.";
		link.l1 = "Esperemos que nuestras vidas también mejoren. Adiós.";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;

	// калеуче
	case "caleuche":
		dialog.text = "Déjame revisar los registros del manifiesto....Ikema, Immerzeel, Jacobs...Jackson, lo encontré. Hmm, el Kapitein Reginald Jackson está actualmente realizando operaciones de envío regulares entre Port Royal y Philipsburg. Búscalo en esa ruta. Ahora, kapitein, debo advertirte de antemano: si estás planeando alguna travesura, será mejor que no lo hagas, porque ese Kapitein Jackson está bajo nuestra protección. ¿Nos entendemos, mynheer?";
		link.l1 = "Solo tengo negocios con él. Un trato común. No pretendo hacerle daño de ninguna manera.";
		link.l1.go = "caleuche_1";
		break;

	case "caleuche_1":
		dialog.text = "Excelente. El Kapitein Jackson generalmente no se queda mucho tiempo en Port Royal o en Philipsburg. Al fin y al cabo, el tiempo es oro. Después de que su barco es descargado y cargado de nuevo, por lo general zarpa de inmediato. Tendrás mejor suerte encontrándolo en las rutas marítimas.";
		link.l1 = "¡Gracias!";
		link.l1.go = "caleuche_2";
		break;

	case "caleuche_2":
		DialogExit();
		pchar.questTemp.Caleuche.Garpiya = "capitan";
		pchar.questTemp.Garpiya = "to_portroyal";
		AddQuestRecord("Caleuche", "19");
		DoQuestFunctionDelay("Caleuche_CreateGarpiyaInWorld", 1.0);
		break;

	// новый босс ГВИК
	case "HWIC_Boss":
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
		{
			if (!CheckAttribute(npchar, "quest.silk_info") && sti(pchar.reputation.nobility) > 60)
			{
				dialog.text = "Ajá, Kapitein " + GetFullName(pchar) + " ¡Es bueno que hayas venido aquí! Tengo una propuesta de negocio para ti.";
				link.l1 = "¡Interesante! Le escucho, mynheer.";
				link.l1.go = "silk_info";
				break;
			}
		}
		dialog.text = "Buen día, Kapitein " + GetFullName(pchar) + ". ¿Cómo puedo servirle?";
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
		{
			if (CheckAttribute(npchar, "quest.silk")) // торговля шелком
			{
				if (GetDataDay() == 1 || GetDataDay() == 15)
				{
					link.l1 = "Sobre esa seda del barco...";
					link.l1.go = "trade_silk";
				}
			}
		}
		link.l2 = "Buen día. No, no necesito nada, solo quería saludar.";
		link.l2.go = "exit";
		NextDiag.TempNode = "HWIC_Boss";
		break;

	case "silk_info":
		dialog.text = "Recientemente he establecido conexiones comerciales con un comerciante de Lyon sobre el suministro de seda para barcos en el Caribe. ¿Sabes algo al respecto? Las mejores velas del mundo están hechas de esta seda, así que debes estar interesado.";
		link.l1 = "Que me parta un rayo, aye eso es música para mis oídos. ¿Cuáles son tus condiciones?";
		link.l1.go = "silk_info_1";
		break;

	case "silk_info_1":
		dialog.text = "Pequeños pero regulares envíos. Puedo reservarte treinta rollos cada dos semanas. El costo de un rollo es de veinte doblones. Hagámoslo así: te guardaré treinta rollos cada primer y decimoquinto día del mes. Si no vienes por ellos, los vendo a otro cliente.";
		link.l1 = "¿Ninguna obligación entonces?";
		link.l1.go = "silk_info_2";
		break;

	case "silk_info_2":
		dialog.text = "Precisamente, kapitein. Compra la seda si quieres. Pagas por todo el lote - seiscientos doblones. Espero que seas un cliente habitual.";
		link.l1 = "Gracias por su propuesta, mynheer. Trato hecho.";
		link.l1.go = "exit";
		NextDiag.TempNode = "HWIC_Boss";
		npchar.quest.silk_info = "true";
		npchar.quest.silk = "true";
		AddQuestRecordInfo("Unique_Goods", "3");
		break;

	// торговля шелком
	case "trade_silk":
		dialog.text = "Claro, kapitein. Su seda le está esperando. ¿Está listo para pagarla?";
		if (PCharDublonsTotal() >= 600)
		{
			link.l1 = "¡Claro! Aquí, toma seiscientos doblones.";
			link.l1.go = "trade_silk_1";
		}
		else
		{
			link.l1 = "¡Maldita sea, he olvidado el dinero en mi barco. Lo traeré en un segundo!";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "HWIC_Boss";
		break;

	case "trade_silk_1":
		RemoveDublonsFromPCharTotal(600);
		Log_Info("Has entregado 600 doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "Un placer hacer negocios contigo, kapitein. Tu seda será entregada a tu barco mediante un bote.";
		link.l1 = "¡Gracias!";
		link.l1.go = "trade_silk_2";
		break;

	case "trade_silk_2":
		dialog.text = "Espero verte pronto. Vuelve otra vez.";
		link.l1 = "Claro. ¡Nos vemos!";
		link.l1.go = "exit";
		AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
		DeleteAttribute(npchar, "quest.silk");
		SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
		AddCharacterExpToSkill(pchar, "Commerce", 150);
		NextDiag.TempNode = "HWIC_Boss";
		break;

	case "fight":
		DialogExit();
		sld = characterFromId("HWIC_officer");
		LAi_SetGuardianTypeNoGroup(sld);
		LAi_group_Attack(sld, Pchar);
		for (i = 1; i <= 6; i++)
		{
			sld = characterFromId("HWIC_sold_" + i);
			LAi_group_Attack(sld, Pchar);
		}
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
