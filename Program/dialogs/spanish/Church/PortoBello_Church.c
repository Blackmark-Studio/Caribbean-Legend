// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas, " + GetSexPhrase("hijo mío", "hija mía") + "?", "Pregunta, estoy escuchando..."), "Estoy escuchando, habla ahora, " + GetSexPhrase("hijo mío", "hija mía") + "...", "Por tercera vez, " + GetSexPhrase("hijo mío", "hija mía") + ", pide lo que necesites.", "Un clérigo tiene mucho trabajo y me estás distrayendo, " + GetSexPhrase("hijo mío", "hija mía") + "... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No en este momento, padre..."), "No tengo nada que decir, mis disculpas.", "Preguntaré, pero más tarde. Perdóname, padre.", "Perdóneme, santo padre...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Church_1"))
            {
                link.l1 = "Padre santo, estoy buscando a Marisa Caldera. Dicen que es muy devota y que asistía a la iglesia con frecuencia. ¿Podría decirme dónde encontrarla?";
                link.l1.go = "LFD_Church_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		//--> Письмо от покойника
		case "LFD_Church_1_1":
			dialog.text = "Marisa fue una de nuestras feligresas más devotas, el verdadero alma de nuestra iglesia. Su ausencia es una gran pérdida para la parroquia. No sé qué la hizo desaparecer, pero no tengo dudas de que le tocaron pruebas inmerecidas y que no faltaron las intrigas del diablo y sus siervos.\nA veces me llegan rumores de que ha sido vista en la ciudad, pero nada más. Sólo nos queda confiar en la voluntad del Señor y creer que un día regresará y encontrará consuelo nuevamente bajo el amparo de la iglesia.";
			link.l1 = "¿Quizás conoce a alguien que pueda decirme más sobre ella?";
			link.l1.go = "LFD_Church_1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LFD_Church_1_2":
			dialog.text = ""+GetSexPhrase("Hijo mío","Hija mía")+", dime, ¿por qué estás buscando a Marisa? Sé que de vez en cuando la buscan personas cuyo aspecto está lejos del de un justo. El mundo está lleno de tentaciones, y no todos los que la buscan tienen buenas intenciones. Antes de decir una palabra, debo estar seguro de que no llevarás desgracia ni a ella, ni a quienes puedan estar con ella.";
			link.l1 = "Comprendo sus preocupaciones, padre, pero le aseguro que no tengo malas intenciones. Sólo quiero entregarle una carta que tardó demasiado en llegar a su destino. ¿Quién sabe? Tal vez contenga algo importante para ella. Mire usted.";
			link.l1.go = "LFD_Church_1_3";
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Entregado: Carta para Marisa Caldera", "None");
		break;
		
		case "LFD_Church_1_3":
			dialog.text = "Sí, esta carta parece haber soportado muchas tormentas antes de llegar a tus manos. Quién sabe qué dice y qué consecuencias traerá su lectura... Pero actúas con nobleza, capitán, devolviéndosela a su destinataria. Si alguien sabe dónde está Marisa ahora, es su amiga Dolores Moño, la única en quien pudo confiar.\nSu casa está a la izquierda de la oficina portuaria. Espero que esta carta no le traiga más sufrimiento, pues ya ha tenido bastante.";
			link.l1 = "Gracias, padre. Que Dios lo bendiga.";
			link.l1.go = "LFD_Church_1_4";
			GiveItem2Character(PChar, "LFD_letter");
		break;
		
		case "LFD_Church_1_4":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Church_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
