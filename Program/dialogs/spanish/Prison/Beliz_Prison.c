// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = "Habla, te escucho";
		link.l1 = "Me equivoqué. Adiós.";
		link.l1.go = "Exit";
		// Калеуче
		if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
		{
			link.l1 = "He oído hablar de una banda de ladrones y rateros que opera en los alrededores de Belice y en la misma ciudad.";
			link.l1.go = "caleuche";
		}
		if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
		{
			link.l1 = "Puedo darte información sobre la banda.";
			link.l1.go = "caleuche_3";
		}
		if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
		{
			link.l1 = "¿Qué noticias hay sobre la banda? ¿Los has capturado en la cueva?";
			link.l1.go = "caleuche_7";
		}
		// Путеводная звезда ==>
		if (CheckAttribute(pchar, "questTemp.PZ_Beliz_Komendant"))
		{
			link.l1 = "Todo el pueblo parece estar celebrando la captura de un pirata. ¿Puedes contarme más al respecto?";
			link.l1.go = "PZ_Beliz_Komendant_1";
			DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
		}
		// <== Путеводная звезда
		break;

	// Путеводная звезда ==>
	case "PZ_Beliz_Komendant_1":
		dialog.text = "¡Con gusto! Este no es cualquier pirata, es ese canalla, Matthew Lutter.";
		link.l1 = "Eventualmente, a todos se les acaba la suerte.";
		link.l1.go = "PZ_Beliz_Komendant_2";
		DelLandQuestMark(npchar);
		break;

	case "PZ_Beliz_Komendant_2":
		dialog.text = "No eres inglés, y no pareces un comerciante, así que entiendo por qué no estás tan emocionado. Lutter ha aterrorizado estas aguas durante años, atacando tanto a nosotros como a los Dones, pero más a menudo a nosotros. Siempre lograba evadir nuestras patrullas costeras, navegando en su corbeta, la Gaviota, que una vez fue el barco más rápido del Archipiélago. Cómo llegó a comandar un buque de guerra así, solo Dios lo sabe.";
		link.l1 = "¿Entonces es cierto que perdió ante un mercader? ¿En una corbeta? Suena increíble.";
		link.l1.go = "PZ_Beliz_Komendant_3";
		break;

	case "PZ_Beliz_Komendant_3":
		dialog.text = "Por extraño que parezca, es cierto. ¡Un comerciante, y un español además! Nuestra armada podría aprender una o dos cosas de él. El capitán Sotta, al darse cuenta de que no había escapatoria, se preparó para la batalla...";
		link.l1 = "Un personaje bastante inusual, este Sotta.";
		link.l1.go = "PZ_Beliz_Komendant_4";
		break;

	case "PZ_Beliz_Komendant_4":
		dialog.text = "Quizás. Hizo reacondicionar su barco para llevar la mayor cantidad de carga posible, lo que hizo que escapar fuera imposible. Sabiendo que los piratas iban tras su carga, fingió estar a la deriva. Y entonces...";
		link.l1 = "...¿izaba las velas en el momento adecuado?";
		link.l1.go = "PZ_Beliz_Komendant_5";
		if (!CharacterIsHere("Longway"))
		{
			sld = CharacterFromID("Longway");
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		}
		break;

	case "PZ_Beliz_Komendant_5":
		dialog.text = "¡Ja! No, disparó una andanada de metralla a quemarropa cuando Lutter se acercó, ¡y luego abordó al pirata él mismo! Cuando descubrió quién era Lutter, nos lo entregó. ¡Un verdadero héroe, un hombre de honor!";
		link.l1 = "No fue solo el honor lo que lo impulsó, debió haber habido una recompensa por atrapar al Charlatán.";
		link.l1.go = "PZ_Beliz_Komendant_6";
		break;

	case "PZ_Beliz_Komendant_6":
		dialog.text = "A veces el beneficio se alinea con las buenas intenciones. Pero sí, fue generosamente recompensado. Su Excelencia lo cargó con mercancías caras como muestra de gratitud de nuestra ciudad antes de que zarpara.";
		link.l1 = "Me hubiera gustado conocerlo, me gustaría estrecharle la mano. Dime...";
		link.l1.go = "PZ_Beliz_Komendant_7";
		break;

	case "PZ_Beliz_Komendant_7":
		StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
		break;
	// <== Путеводная звезда

	// Калеуче
	case "caleuche":
		dialog.text = "Tu fuente decía la verdad. Estos bandidos se han convertido en un verdadero dolor de cabeza para nosotros. ¿Quieres contarnos algo sobre ellos?";
		link.l1 = "Además de que me han robado una cosa importante, nada realmente. Esperaba que pudieras decirme algo sobre ellos. Tal vez, uno de ellos fue capturado y ahora está listo para testificar...";
		link.l1.go = "caleuche_1";
		break;

	case "caleuche_1":
		dialog.text = "Lo siento por decepcionarle, capitán, pero no tengo información sobre ellos. Solo sé que se esconden en algún lugar de la jungla, y que tienen cómplices en la ciudad, eso es todo. Ahora, si se entera de algo nuevo sobre ellos, por favor dígamelo de inmediato.";
		link.l1 = "Está bien, oficial. Haré eso.";
		link.l1.go = "caleuche_2";
		break;

	case "caleuche_2":
		DialogExit();
		AddQuestRecord("Caleuche", "10");
		pchar.questTemp.Caleuche.Bandos = "seek";
		break;

	case "caleuche_3":
		string sTime;
		if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0)
			sTime = "en tres días";
		if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1)
			sTime = "pasado mañana";
		if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2)
			sTime = "tomorrow";
		dialog.text = "¿Hablas en serio, capitán? Habla, soy todo oídos.";
		link.l1 = "He encontrado a uno de sus informantes en la ciudad. Me dijo que su banda está preparando un ataque a un barco, que se supone llegará a la cala de Chetumal. Los villanos están reuniéndose " + sTime + " por la noche cerca de una cueva no lejos de Belice. Para llegar allí, solo necesitas tomar el camino de la izquierda en la bifurcación de la jungla.";
		link.l1.go = "caleuche_4";
		break;

	case "caleuche_4":
		dialog.text = "¿En la cueva? Excelentes noticias. Ordenaré preparar una emboscada para esos villanos. Si lo has entendido bien y tu informante decía la verdad, atraparemos a esos malnacidos, y luego solicitaré ante el gobernador que te recompensen.";
		link.l1 = "¡Gracias! Vendré a verte cuando todo termine.";
		link.l1.go = "caleuche_5";
		break;

	case "caleuche_5":
		dialog.text = "Está bien. Eso está bien.";
		link.l1 = "Nos vemos pronto, oficial.";
		link.l1.go = "caleuche_6";
		break;

	case "caleuche_6":
		DialogExit();
		AddQuestRecord("Caleuche", "15");
		pchar.questTemp.Caleuche.Bandos = "comendant";
		pchar.questTemp.Caleuche.BelizChance = hrand(3);
		SetFunctionTimerCondition("Caleuche_BelizRegard", 0, 0, 3, false); // таймер
		break;

	case "caleuche_7":
		if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
		{
			dialog.text = "¡Preparamos una cálida bienvenida para los canallas, ja-ja-ja! ¡Si tan solo pudieras haber visto sus caras! Nos llevamos a todos, ¡incluso al cabecilla! Algunos intentaron resistir, pero fueron eliminados por nuestros valientes soldados.";
			link.l1 = "¡Excelentes noticias, oficial! Ahora los ciudadanos de Belice finalmente pueden dormir tranquilos.";
			link.l1.go = "caleuche_12";
		}
		else
		{
			dialog.text = "Hum... Mis soldados les estuvieron esperando en la cueva toda la noche, pero nadie apareció nunca. El sargento estaba realmente furioso. Es bueno que aún no te haya atrapado.";
			link.l1 = "¡Maldita sea! ¡Eso no puede ser! ¿En qué cueva habéis tendido la emboscada? ¡Hay dos de ellas!";
			link.l1.go = "caleuche_8";
		}
		break;

	case "caleuche_8":
		dialog.text = "Donde me dijiste. En el de la derecha en la bifurcación...";
		link.l1 = "¡ES EL DE LA IZQUIERDA! ¡A la izquierda del tenedor, imbéciles!";
		link.l1.go = "caleuche_9";
		break;

	case "caleuche_9":
		dialog.text = "Pero recuerdo perfectamente que dijiste 'a la derecha'.";
		link.l1 = "¡Ay mi Señor! ¡A la izquierda! ¡Dije, A! ¡LA! ¡IZQUIERDA! ¡Los dejaste escapar, y fue tu culpa!";
		link.l1.go = "caleuche_10";
		break;

	case "caleuche_10":
		AddQuestRecord("Caleuche", "16");
		dialog.text = "Entonces debiste haber murmurado algo bajo tu nariz. Puedo escuchar bastante bien, ¿sabes?";
		link.l1 = "Está bien, oficial, no voy a discutir. Quería ayudarle, pero no se puede ayudar a aquellos que no pueden ayudarse a sí mismos. Adiós.";
		link.l1.go = "caleuche_11";
		break;

	case "caleuche_11":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
		DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;

	case "caleuche_12":
		dialog.text = "Informé al gobernador sobre tu papel en la eliminación de la banda. Valoró mucho tu contribución y me autorizó a presentarte una recompensa: una prima monetaria y una arcabuz trofeo.";
		link.l1 = "¡Gracias!";
		link.l1.go = "caleuche_13";
		break;

	case "caleuche_13":
		Log_Info("Has recibido un cofre con doblones");
		Log_Info("Has recibido un arquebus");
		PlaySound("interface\important_item.wav");
		AddQuestRecord("Caleuche", "17");
		GiveItem2Character(pchar, "chest");
		GiveItem2Character(pchar, "mushket3");
		dialog.text = "¡Gracias por el servicio, capitán! ¡Si tan solo todos nuestros ciudadanos fueran tan conscientes como usted, habríamos derrotado al crimen de una vez por todas hace mucho tiempo! ¡Le deseo la mejor de las suertes!";
		link.l1 = "¡Adiós, oficial! ¡Buena suerte en tu servicio!";
		link.l1.go = "caleuche_11";
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		ChangeCharacterComplexReputation(pchar, "authority", 3);
		ChangeCharacterComplexReputation(pchar, "fame", 3);
		OfficersReaction("good");
		ChangeCharacterNationReputation(pchar, ENGLAND, 8);
		AddCharacterExpToSkill(pchar, "Leadership", 300); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 200);	  // везение
		AddCharacterExpToSkill(pchar, "Sneak", 200);	  // скрытность
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
