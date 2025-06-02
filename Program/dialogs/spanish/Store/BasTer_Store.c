// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat("Adelante, ¿qué quieres?", "Justo estábamos hablando de eso. Debes haberlo olvidado...", "Esta es la tercera vez hoy que hablas de alguna pregunta...", "Escucha, esto es una tienda. La gente compra cosas aquí. ¡No me molestes!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Sabes, " + NPChar.name + ", tal vez la próxima vez.", "Correcto, lo he olvidado por alguna razón...", "Sí, realmente es la tercera vez...", "Hm, no lo haré...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";

		// Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
		if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
		{
			if (pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
			{
				dialog.text = "Gracias, capitán, por cumplir con mi petición. Ahora, cuando " + pchar.questTemp.Shadowtrader.Guardername + " esté aquí, al menos puedo sentirme un poco más relajado.";
				link.l1 = "Hmm... No quisiera parecer entrometido, pero me parece que estás teniendo problemas. ¿Puedes decirme de qué se trata el asunto? Tal vez podría ayudarte.";
				link.l1.go = "Shadowtrader_fort";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
			{
				dialog.text = "¿Entonces? ¿Has entregado mi carta?";
				link.l1 = "Lo hice, el comandante me respondió de viva voz que las pruebas en tu carta son insuficientes para que la guardia de la ciudad tome medidas.";
				link.l1.go = "Shadowtrader_trouble";
				pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
			{
				dialog.text = "Ya me he enterado de la noticia: esta noche, los guardias descubrieron un puesto de comercio ilegal de contrabandistas y los arrestaron a todos. Estaba bajo el mando de una rara pieza de escoria, pero ahora todo está bien, no podrá hacerle daño a nadie más por un tiempo.\nEl comandante me habló de tu papel en todo esto, ¡tienes mi gratitud! ¡Has cumplido tu palabra! Aquí, toma el dinero: 15 000 pesos. Me has salvado. ¡Nada amenaza mi negocio ahora!";
				link.l1 = "De nada. Fue fácil.";
				link.l1.go = "Shadowtrader_complete";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
			{
				dialog.text = "Entonces, ¿alguna buena nueva, " + pchar.name + "?";
				link.l1 = "He localizado a tu rival. No volverá a ser un dolor en el trasero, logré convencerlo de que se fuera de esta isla. Su 'tienda' estaba en una casa cerca de las puertas de la ciudad. Depende de ti decidir qué hacer con la carga que fue abandonada. Puedes entregarla a las autoridades o intentar recogerla para ti mismo.";
				link.l1.go = "Shadowtrader_Escape_complete";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
			{
				dialog.text = "Ya he oído la noticia: esta noche los guardias han descubierto un escondite de contrabandistas debajo de una de las casas. Dos villanos encontrados muertos. Buen trabajo, " + pchar.name + ", ¡te admiro! Toma la recompensa, 15 000 pesos. ¡Me acabas de salvar! ¡Ahora comerciaré de verdad!\nSatisface mi curiosidad, su líder... ¿también está entre los dos muertos?";
				link.l1 = "No. Pero nunca volverá a mostrar su rostro en tu pueblo. Creo que debería estar a varias docenas de millas de esta isla, mientras hablamos.";
				link.l1.go = "Shadowtrader_complete";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
			{
				dialog.text = "Ya he oído las noticias: esta noche los guardias han localizado una tienda secreta de contrabandistas en una de las casas. Tres villanos fueron encontrados muertos. Excelente trabajo, " + pchar.name + ", ¡te admiro! Aquí, toma el premio, 15 000 pesos. ¡Acabas de salvarme! ¡Ahora comerciaré de verdad!\nSatisface mi curiosidad, su líder... ¿también entre los dos muertos?";
				link.l1 = "Sí. Te has deshecho de tu rival para siempre. Nunca te molestará de nuevo.";
				link.l1.go = "Shadowtrader_complete";
				break;
			}
		}
		//<-- мини-квест Бесчестный конкурент
		break;

	// --> мини-квест Бесчестный конкурент
	case "Shadowtrader_begin":
		pchar.questTemp.Shadowtrader = "true";
		pchar.questTemp.Shadowtrader_Block = true;
		pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
		dialog.text = "¿Podrías ir a la taberna, buscar a un hombre llamado " + pchar.questTemp.Shadowtrader.Guardername + " y decirle que venga aquí lo antes posible? No puedo dejar la tienda, y ese cabeza hueca está en la taberna, atiborrándose de ron, y seguramente ni pensará en venir aquí, a pesar de estar de servicio.";
		link.l1 = "Siempre estoy feliz de ayudar, camarada, y más aún porque iba a visitar la taberna de todos modos.";
		link.l1.go = "Shadowtrader_begin_1";
		link.l2 = "¿Te estás burlando de mí? ¿Acaso parezco tu criado? La taberna está a solo unos pasos de aquí, puedes ir tú mismo.";
		link.l2.go = "exit";
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("BasTer");
		break;

	case "Shadowtrader_begin_1":
		dialog.text = "¡Gracias! Por favor, dile que venga aquí ahora mismo. ¿Por qué tiene que ser tan fastidioso...?";
		link.l1 = "No te preocupes. Lo resolveré a mi manera.";
		link.l1.go = "exit";
		pchar.questTemp.Shadowtrader.City = npchar.City;
		pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
		// создаем охранника
		sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder", "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
		FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
		sld.name = pchar.questTemp.Shadowtrader.Guardername;
		sld.lastname = "";
		sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
		sld.dialog.currentnode = "ShadowGuarder";
		sld.greeting = "pirat_common";
		LAi_SetSitType(sld);
		LAi_SetImmortal(sld, true);
		FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
		ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
		SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
		AddLandQuestMark(sld, "questmarkmain");
		break;

	case "Shadowtrader_fort":
		dialog.text = "Oh, capitán, realmente me gustaría su ayuda. ¿Podría entregar esta carta al comandante lo antes posible? Le pagaría 300 monedas por este trato trivial como ya he dicho, no puedo dejar mi tienda.";
		link.l1 = "Sin problema. Dame esa carta.";
		link.l1.go = "Shadowtrader_fort_1";
		link.l2 = "No, buen hombre, no tengo más tiempo para esa tontería.";
		link.l2.go = "Shadowtrader_fort_end";
		DelLandQuestMark(npchar);
		break;

	case "Shadowtrader_fort_1":
		dialog.text = "Aquí tienes. Por favor, entrégaselo hoy y tráeme su respuesta.";
		link.l1 = "No te preocupes, lo haré.";
		link.l1.go = "exit";
		GiveItem2Character(pchar, "letter_1");
		ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
		pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
		SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
		pchar.questTemp.Shadowtrader = "current" pchar.questTemp.Shadowtrader.Fort = "true";
		AddQuestRecord("Shadowtrader", "1");
		AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony" + pchar.questTemp.Shadowtrader.City + "Gen"));
		AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;

	case "Shadowtrader_fort_end":
		dialog.text = "Bueno, aparentemente tendré que preguntar a alguien más. Lamento haberle molestado, capitán.";
		link.l1 = "¡No hay problema! ¡Adiós!";
		link.l1.go = "exit";
		pchar.questTemp.Shadowtrader = "true";
		DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;

	case "Shadowtrader_trouble":
		dialog.text = "¿Eso es lo que dijo? ¿Qué evidencia necesita de mí, entonces? ¿Mi cadáver? ¡Bueno, pronto habrá uno, si sigue así!";
		link.l1 = "¡Eh, eh, " + npchar.name + ", cálmate, o te dará un ataque! Toma, bebe un poco de agua... Ahora dime. ¿Qué pasa? Tal vez pueda ayudarte.";
		link.l1.go = "Shadowtrader_trouble_1";
		DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
		DelLandQuestMark(npchar);
		break;

	case "Shadowtrader_trouble_1":
		dialog.text = "¡Oh, capitán! Por favor, tome sus 300 pesos, casi lo había olvidado... Por supuesto, se lo diré, pero no estoy seguro de cómo podría ayudarme. Mi negocio está casi arruinado y todo por culpa de esos malditos contrabandistas y ese bastardo desconocido que los lidera.";
		link.l1 = "¿Contrabandistas?";
		link.l1.go = "Shadowtrader_trouble_2";
		AddMoneyToCharacter(pchar, 300);
		break;

	case "Shadowtrader_trouble_2":
		dialog.text = "¡Eso es! ¡Esos bribones obviamente han decidido echarme de la ciudad! Hasta entonces todo había sido como de costumbre: revendían artículos prohibidos, y cuando las patrullas los atrapaban, se escondían o les pagaban. ¡Pero recientemente han abierto una tienda en algún callejón y han comenzado a vender los bienes más populares a precios increíblemente bajos! No puedo permitirme ese lujo, de hecho, tengo que pagar impuestos y progresivamente me he empobrecido, y los marineros casi no quieren mis mercancías. Todos los bienes se los compran a esos canallas.";
		link.l1 = "¡Pero deberías haber apelado a las autoridades! Después de todo, su trabajo es detener tal anarquía.";
		link.l1.go = "Shadowtrader_trouble_3";
		break;

	case "Shadowtrader_trouble_3":
		dialog.text = "Viste el resultado de la última apelación tú mismo. El gobernador está demasiado ocupado y el comandante no creyó que los contrabandistas organizaran tiendas clandestinas o lo finge, supongo que ese es el caso.\nPor supuesto, ¿por qué harían eso? Y yo digo: Estoy seguro de que algún sinvergüenza que quiere destruirme y expulsarme de la ciudad. Lo pleneó todo y luego en silencio, se adueñará de mi negocio para limpiar sus sucias manos.";
		link.l1 = "Hm... tu opinión no es infundada. Es propio de los mercaderes hacer que alguien cargue con el muerto de otro... Oh, lo siento, por supuesto que no me refería a ti. ";
		link.l1.go = "Shadowtrader_trouble_4";
		break;

	case "Shadowtrader_trouble_4":
		dialog.text = "Oh, no pasa nada... Y recientemente un rufián vino a mí y descaradamente dijo que si continuaba haciendo ruido, quemarían mi tienda.\nAsí que contraté un guardaespaldas. " + pchar.questTemp.Shadowtrader.Guardername + " no sale barato, pero es un profesional y bajo su protección puedo sentirme un poco más tranquilo.";
		link.l1 = "Ya veo... Sin duda es una historia desagradable. Aparentemente, tenías razón y no hay nada que pueda hacer por ti. Pero aún así, estoy seguro de que las cosas se resolverán solas, esos establecimientos turbios generalmente no duran mucho. ¡Buena suerte!";
		link.l1.go = "Shadowtrader_end";
		link.l2 = "Ya veo. Bueno, tal vez aún pueda ayudarte...";
		link.l2.go = "Shadowtrader_trouble_5";
		break;

	case "Shadowtrader_trouble_5":
		dialog.text = "¿Me ofrece su ayuda de todos modos? ¿Pero qué va a hacer?";
		link.l1 = "Trataré de encontrar a ese 'colega' tuyo y... persuadirlo para que te deje en paz. Sabes, tengo ciertas habilidades para persuadir a la gente.";
		link.l1.go = "Shadowtrader_trouble_6";
		break;

	case "Shadowtrader_trouble_6":
		dialog.text = "¿Hablas en serio? ¡Que el Señor bendiga tu justa causa! Si me liberas de esa inmundicia, te estaré en deuda.";
		link.l1 = "Está bien, considéralo un trato. Empezaré a buscar, entonces.";
		link.l1.go = "exit";
		pchar.questTemp.Shadowtrader.seeksmugglers = "true";
		AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		AddQuestRecord("Shadowtrader", "2");
		AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony" + pchar.questTemp.Shadowtrader.City + "Gen"));
		AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся", "ась"));
		break;

	case "Shadowtrader_end":
		pchar.questTemp.Shadowtrader = "true";
		CloseQuestHeader("Shadowtrader");
		DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		DialogExit();
		break;

	case "Shadowtrader_Escape_complete":
		dialog.text = "¿Es eso cierto? ¿Ahora puedo hacer negocios sin ningún temor? ¡Oh, muchas gracias! Aquí tienes tu recompensa, 15 000 pesos. En cuanto a las mercancías en su casa, supongo que lo mejor es entregarlas al comandante. ¡Gracias de nuevo!";
		link.l1 = "De nada. No fue muy difícil. Te dije que era bueno en persuasión.";
		link.l1.go = "Shadowtrader_complete";
		break;

	case "Shadowtrader_complete":
		dialog.text = "Ven a visitarme de nuevo, capitán, siempre estaré feliz de verte.";
		link.l1 = "¡Por supuesto! Y ahora permíteme retirarme, ¡tengo cosas que hacer! Adiós y buena suerte en tu comercio, " + npchar.name + ".";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
		AddMoneyToCharacter(pchar, 15000);
		pchar.questTemp.Shadowtrader = "complete";
		AddQuestRecord("Shadowtrader", "11");
		AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("", "а"));
		CloseQuestHeader("Shadowtrader");
		DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("BasTer");
		break;
		//<-- мини-квест Бесчестный конкурент
	}
	UnloadSegment(NPChar.FileDialog2);
}
