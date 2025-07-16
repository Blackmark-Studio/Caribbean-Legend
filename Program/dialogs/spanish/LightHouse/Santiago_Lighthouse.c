// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué quieres?", "¿Qué te gustaría saber?"), "¿Qué necesitas, " + GetAddress_Form(NPChar) + "?", "Esa es la tercera vez que intentas preguntarme...", "¡Estoy harto de ti, piérdete!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Lo siento, he cambiado de opinión.", "Es nada, disculpas."), "Lo olvidé, mis disculpas...", "La tercera es la vencida, ¿eh? Disculpa...", "¡Lo siento, lo siento! Entonces me iré por mi cuenta...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
		{
			link.l1 = "Saludos. El inquisidor de Santiago, Padre Vincento, te ha mencionado en su carta. Dijo que podrías ayudarme.";
			link.l1.go = "guardoftruth";
		}
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
		{
			link.l1 = "¿Alguna noticia del Padre Vincento, " + npchar.name + "?";
			link.l1.go = "guardoftruth_5";
		}
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
		{
			link.l1 = "Necesito ver al Padre Vincento. He encontrado los objetos que le interesan.";
			link.l1.go = "guardoftruth_7";
		}
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
		{
			link.l1 = "Entonces, " + npchar.name + ", ¿qué te ha dicho el Padre Vincento?";
			link.l1.go = "guardoftruth_11";
		}
		break;

	case "guardoftruth":
		dialog.text = "Claro, señor. Debes ser un hombre de gran renombre si el Padre Vincento hace negocios contigo.";
		link.l1 = "Espléndido. Entonces eres nuestro mensajero. Ahora escucha, este hombre es de gran interés para el Padre Vincento. Ahora está bajo tu responsabilidad, debes trasladarlo a Santiago, o encontrar a alguien que lo haga.";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "...";
		link.l1 = "Usted es responsable del prisionero en nombre del Inquisidor. No le aconsejaría quitarle las cadenas, Gaius Marchais es un hombre fuerte. Entregue esta carta al padre Vincento, y dígale que espero una respuesta de él en dos días. Esto debería ser suficiente, espero.";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		Log_Info("¡Te libras de la carta!");
		PlaySound("interface\important_item.wav");
		dialog.text = "Entendido, señor. Haré lo mejor que pueda. No es la primera vez que ayudo al Santo Padre.";
		link.l1 = "Eso no es todo. El capitán de la carraca, San Gregorio, Carlos Guevarra debe haber estado aquí. Me trajo vainilla. ¿Te ha dado mi carta?";
		link.l1.go = "guardoftruth_3";
		break;

	case "guardoftruth_3":
		dialog.text = "Sí, su carga está bien y esperándole, señor.";
		link.l1 = "Bien, lo llevaré a mi barco entonces. Estaré aquí dos días esperando la respuesta del Padre Vincento. ¡Sin despedidas, " + npchar.name + "!";
		link.l1.go = "guardoftruth_4";
		break;

	case "guardoftruth_4":
		DialogExit();
		LocatorReloadEnterDisable("mayak9", "boat", false);
		ref sld = characterFromId("GOT_Marshe");
		LAi_SetStayType(sld);
		LAi_CharacterDisableDialog(sld);
		sld.lifeday = 0;
		pchar.questTemp.Guardoftruth = "mayak_wait";
		SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
		SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + sti(pchar.questTemp.Guardoftruth.VanilleQty));
		AddQuestRecord("Guardoftruth", "21");
		break;

	case "guardoftruth_5":
		dialog.text = "Sí, señor. Aquí hay una carta del Padre Vincento. Está muy complacido contigo, el resto lo sabrás por la carta.";
		link.l1 = "Espléndido. Hasta entonces, " + npchar.name + ". Y por ahora, adiós.";
		link.l1.go = "guardoftruth_6";
		break;

	case "guardoftruth_6":
		DialogExit();
		pchar.questTemp.Guardoftruth = "mayak_exit";
		GiveItem2Character(pchar, "specialletter");
		sld = ItemsFromID("specialletter");
		sld.text = "Letter_Vincento_next";
		break;

	case "guardoftruth_7":
		dialog.text = "Muy bien. Dámelos y los llevaré al santo padre.";
		link.l1 = "¡De ninguna manera, camarada! No fue fácil conseguirlos y no los entregaré así como así. Solo se los daré personalmente al Padre Vincento.";
		link.l1.go = "guardoftruth_8";
		break;

	case "guardoftruth_8":
		dialog.text = "¡Pero señor! ¿Cómo puedo saber que no me está engañando?";
		link.l1 = "Toma un vistazo: el incensario, el cáliz y la cruz con lazurita... " + npchar.name + ", ¿quién crees que soy? ¿Realmente piensas que soy tan estúpido como para ir a la Inquisición sin ellos?";
		link.l1.go = "guardoftruth_9";
		break;

	case "guardoftruth_9":
		dialog.text = "Perdóname, señor... Vuelve mañana y le contaré al Padre Vincento sobre tu llegada.";
		link.l1 = "Bien. Nos vemos mañana.";
		link.l1.go = "guardoftruth_10";
		break;

	case "guardoftruth_10":
		DialogExit();
		pchar.questTemp.Guardoftruth = "mayak_wait";
		SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;

	case "guardoftruth_11":
		dialog.text = "Su Gracia lo recibirá, señor. No demore su visita. Aquí está el documento, muéstrelo a los guardias y lo dejarán entrar. Pero primero izad una bandera española o es probable que los soldados lo arresten.";
		link.l1 = "Entendido. Entonces bandera española. ¡Gracias, camarada! ¡Estoy en camino!";
		link.l1.go = "guardoftruth_12";
		break;

	case "guardoftruth_12":
		DialogExit();
		GiveItem2Character(pchar, "VerifyPaper");
		ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
		pchar.questTemp.Guardoftruth = "santiago";
		AddQuestRecord("Guardoftruth", "34");
		AddCharacterExpToSkill(pchar, "Fortune", 200); // везение
		AddCharacterExpToSkill(pchar, "Sneak", 400);   // скрытность
		GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
