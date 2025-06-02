// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas, " + GetSexPhrase("hijo mío", "hija mía") + "?", "Pregunta lo que quieras, estoy escuchando..."), "Estoy escuchando, habla ahora, " + GetSexPhrase("hijo mío", "hija mía") + "... ", "Por tercera vez, " + GetSexPhrase("hijo mío", "hija mía") + ", pide lo que necesites.", "Un clérigo tiene mucho trabajo y me estás distrayendo, " + GetSexPhrase("hijo mío", "hija mía") + "... ", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No en este momento, padre..."), "No tengo nada que decir, mis disculpas.", "Lo preguntaré, pero más tarde. Perdóname, padre.", "Perdóneme, santo padre...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// калеуче
		if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
		{
			ref sld = characterFromId("Villemstad_Priest");
			link.l1 = "Saludos, padre. El padre superior " + sld.name + " de la iglesia de Willemstad me envió. Le hablaste de avistamientos extraños en una cueva en Cuba.";
			link.l1.go = "caleuche";
		}
		if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
		{
			link.l1 = "He visitado la cueva en la jungla, padre.";
			link.l1.go = "caleuche_4";
		}
		break;

	case "caleuche":
		dialog.text = "¡Gracias a Dios que prestó atención a esto! Una vez que los rumores sobre los muertos vivientes llegaron a mis oídos, inmediatamente notifiqué a Su Reverencia el Padre Vincento, el inquisidor de Santiago. Prometió investigar, pero hasta ahora no se ha tomado ninguna acción. Me temo que Su Reverencia tiene asuntos más importantes que atender...";
		link.l1 = "Investigaré por mi cuenta. Además, todos estos chismes no son más que los desvaríos de cazadores borrachos, por lo tanto, la Inquisición no los ha tomado en serio. Me adentraré en la jungla para presenciarlo con mis propios ojos.";
		link.l1.go = "caleuche_1";
		break;

	case "caleuche_1":
		dialog.text = "Te aseguro, hijo mío, que es crucial. Al hombre que me habló de los no-muertos, le confiaría mi vida.";
		link.l1 = "Muy bien, me prepararé para la batalla. Si las criaturas impías realmente se han arraigado en la caverna, las purgaré de este mundo.";
		link.l1.go = "caleuche_2";
		break;

	case "caleuche_2":
		dialog.text = "¡Ve con la bendición del Señor, hijo mío! Aquí, toma este amuleto santificado. Te ayudará en tu misión. ¡Ahora ve! ¡Destruye las criaturas del mal!";
		link.l1 = "Hasta entonces, Padre " + npchar.name + ". Una vez que termine, regresaré a ti de inmediato.";
		link.l1.go = "caleuche_3";
		break;

	case "caleuche_3":
		DialogExit();
		AddQuestRecord("Caleuche", "27");
		pchar.questTemp.Caleuche = "cave";
		Log_Info("¡Has recibido un amuleto de la iglesia!");
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "amulet_7");
		if (GetCharacterIndex("cavehunter") != -1)
		{
			sld = characterFromId("cavehunter");
			sld.dialog.currentnode = "cavehunter_5";
			LAi_SetGuardianType(sld);
			sld.protector = true;
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		}
		LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
		pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
		pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
		pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;

	case "caleuche_4":
		dialog.text = "¿Qué has visto, hijo mío? ¿Eran infundados nuestros temores?";
		link.l1 = "Me temo que no, Padre " + npchar.name + ". La cueva estaba infestada de muertos vivientes, pero con la ayuda de Dios salí victorioso. Ya no molestarán a nadie más.";
		link.l1.go = "caleuche_5";
		break;

	case "caleuche_5":
		dialog.text = "¡Alabado sea el Señor! ¡Tú eres en verdad su espada castigadora, hijo mío! Por favor, permíteme expresar mi más profundo agradecimiento en nombre de toda la parroquia de La Habana. Por favor, acepta estos amuletos santificados como una muestra de gratitud. Sin duda, los encontrarás útiles en tus peligrosas travesías.";
		link.l1 = "Gracias, Padre " + npchar.name + ".";
		link.l1.go = "caleuche_6";
		break;

	case "caleuche_6":
		Log_Info("¡Has recibido varios amuletos de la iglesia!");
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "amulet_3");
		GiveItem2Character(pchar, "amulet_9");
		GiveItem2Character(pchar, "obereg_7");
		GiveItem2Character(pchar, "obereg_11");
		dialog.text = "Además, me aseguraré de que tanto la plebe como los nobles conozcan tu heroica hazaña, y rezaré incansablemente por ti día y noche.";
		link.l1 = "Gracias, Padre. También tengo una pregunta más que hacer.";
		link.l1.go = "caleuche_7";
		break;

	case "caleuche_7":
		dialog.text = "Pregunta, hijo mío.";
		link.l1 = "Dime, Padre " + npchar.name + ", ¿llegó recientemente a su pueblo un hombre llamado Joachim Merriman? ¿Un señor de mediana edad, portugués con bigote, barba imperial y ojos penetrantes?";
		link.l1.go = "caleuche_8";
		break;

	case "caleuche_8":
		sld = characterFromId("Villemstad_Priest");
		dialog.text = "Ni el nombre ni la descripción me suenan, lo siento. ¿Quién es este hombre?";
		link.l1 = "Merriman es un brujo. La Inquisición lo ha estado cazando durante mucho tiempo. Padre " + sld.name + ", sospecho que la aparición de los muertos vivientes en Cuba es obra suya. No hace mucho, él vivía en Willemstad, luego desapareció repentinamente. Poco después, la mujer que lo alojaba se convirtió en un esqueleto andante.";
		link.l1.go = "caleuche_9";
		break;

	case "caleuche_9":
		dialog.text = "¡Qué pesadilla! Informaré inmediatamente a los inquisidores, al propio Padre Vincento. ¡Él debe saber lo que está sucediendo aquí! Dime, hijo mío, ¿crees que las personas que desaparecieron en la jungla...?";
		link.l1 = "De hecho, estoy casi seguro de que esos muertos vivientes en la caverna eran tus antiguos ciudadanos. ¡Quiero buscar a ese portugués en Cuba y hacer que pague! Ese bribón logró hacerse con una antigua reliquia pagana: un cráneo de jade de Yum Cimil. Me temo que con el artefacto y la brujería india, Merriman causará aún más problemas si nadie lo detiene pronto.";
		link.l1.go = "caleuche_10";
		break;

	case "caleuche_10":
		dialog.text = "¿Crees que los no-muertos se levantarán de nuevo?";
		link.l1 = "Casi con certeza. No estoy seguro de qué lo mueve, pero seguramente sus aspiraciones están lejos de ser virtuosas.";
		link.l1.go = "caleuche_11";
		break;

	case "caleuche_11":
		dialog.text = "¡Que el Todopoderoso tenga misericordia de nosotros! ¡Búscalo, hijo mío! ¡Te permito tomar cualquier medida contra él en el nombre de nuestra Santa Iglesia! Enviaré inmediatamente un mensajero a Santiago con un informe para el Padre Vincento.";
		link.l1 = "Haz eso. Adiós, padre " + npchar.name + ".";
		link.l1.go = "caleuche_12";
		break;

	case "caleuche_12":
		DialogExit();
		AddQuestRecord("Caleuche", "29");
		pchar.questTemp.Caleuche = "graveyard";
		AddCharacterMaxHealth(pchar, 3);
		ChangeCharacterComplexReputation(pchar, "nobility", 3);
		ChangeCharacterComplexReputation(pchar, "authority", 2);
		ChangeCharacterComplexReputation(pchar, "fame", 3);
		ChangeCharacterNationReputation(pchar, SPAIN, 10);
		AddCharacterExpToSkill(pchar, "Leadership", 500);
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
