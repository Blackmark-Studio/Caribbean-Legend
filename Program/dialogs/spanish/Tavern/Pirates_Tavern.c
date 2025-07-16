// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?","¿Cómo puedo ayudarle, "+GetAddress_Form(NPChar)+"?"),"Intentaste hacerme una pregunta no hace mucho, "+GetAddress_Form(NPChar)+"...","En todo este día, esta es la tercera vez que hablas de alguna pregunta...","¿Más preguntas, supongo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...","No tengo nada de qué hablar en este momento."),"Umph, ¿dónde se ha ido mi memoria...?","Sí, realmente es la tercera vez...","¿No, qué preguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(PChar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesorotavern")
			{
				link.l1 = "Escucha, "+npchar.name+", ¿has oído algo sobre un hombre llamado Miguel Dichoso? Dicen que su barco ha sido visto en las aguas de Isla Tesoro...";
				link.l1.go = "guardoftruth";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Escucha, "+npchar.name+", ¿no has visto a Miguel Dichoso últimamente en Isla Tesoro?";
				link.l1.go = "tieyasal";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Pues, la verdad sí. Ese don español le vendió a Shark Dodson un barco notable, una fragata, cuando aún residía aquí. Ah, ese barco... Era un increíble navío...";
			link.l1 = "Déjame adivinar: ¿tenía un casco moderno y elegante, y era capaz de alcanzar dieciséis nudos? ¿Y su nombre era 'Santa Quitaria'?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "En cuanto al armazón y la velocidad, tienes toda la razón, pero tenía otro nombre: 'San Martín'. Shark pagó una buena cantidad de oro a ese bribón por ese barco.";
			link.l1 = "¿Estás seguro de que era 'San Martín' y no 'Santa Quiteria'? ¿Cuándo lo compró? ¿Y por qué llamaste a Dichoso un bribón?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "¡Malditos sean mis ojos, estoy absolutamente seguro de que era el 'San Martín', porque personalmente vi a los trabajadores de Alexus arrancar una placa con esas tonterías papistas de la popa. Shark Dodson la llamó 'Fortuna', un nombre mucho más adecuado para semejante belleza. (escupe) La había comprado en el invierno del '54, no mucho antes de que Blaze fuera asesinado.\n¿Por qué llamé a Don Miguel un bribón? ¡Porque robó la maldita nave de la armada española en Providencia! Dodson organizó una actuación con fuego y humo para el fuerte de San Juan y su guarnición, como siempre me contaba cuando estaba borracho. Shark sacrificó dos barcas dañadas para hacer que la pelea con la fragata pareciera real.\nCuando llegó la noche, navegó en secreto el 'San Martín' hasta Isla Tesoro. Shark consiguió el barco y Dichoso consiguió el dinero. El astuto bastardo luego le dijo a sus superiores que la fragata se hundió durante la pelea con la flota pirata, el comandante del fuerte de San Juan lo confirmó.";
			link.l1 = "¡Oh, cómo esos don juanes españoles llenan sus bolsillos! ¡Qué embaucador! Dime, ¿estás seguro de que eso ocurrió en el invierno de 1654? ¿Podría haber sido durante la primavera? ¿Y no mostró esa fragata signos de desgaste por la tormenta?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Estoy bastante seguro de que era invierno... Oh, quién sabe. Tal vez era primavera. No lo recuerdo con certeza. Probablemente estaba borracho. Sin embargo, la fragata no estaba desgastada en absoluto, era completamente nueva.";
			link.l1 = "¿Y dónde está ahora esa belleza de fragata?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Una historia oscura, es... Cuando Blaze fue asesinado, todos sospecharon de Shark porque su collar, un diente de tiburón, fue encontrado en el cadáver. Además, algunas personas vieron a Shark en la residencia de Blaze esa noche.\nShark escapó de Isla Tesoro antes de que le dieran la marca negra. Visitó a Black Pastor e intercambió su fragata por un bergantín. No hay pista de dónde está el hombre ahora. Zachary vendió la fragata a William Paterson más tarde.";
			link.l1 = "¿Quién es este Paterson?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "¿Qué, nunca has oído hablar de Willie Paterson? Es un escocés, recién llegado al Caribe. ¡Se cree que es Capitán de la flota real, y el favorito del Coronel Fox! Por cierto, acaba de empezar a tramar algún negocio con Jackman también. El buque insignia de Paterson es la misma 'Fortuna'.";
			link.l1 = "Ya veo. ¿Sabes dónde está Dichoso ahora mismo?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "No tengo ni idea. Después de esa triquiñuela con 'Fortune', no lo he visto en Isla Tesoro desde entonces, y no he oído nada sobre él.";
			link.l1 = "Está bien, "+npchar.name+". ¡Gracias por la información detallada! ¡Eres un excelente tabernero! Ojalá hubiera más gente como tú... ¡Adiós!";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Buena suerte, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60_1");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "Parece que ambos se persiguen mutuamente, camarada. Sí, Dichoso estuvo aquí justo donde estás parado. Y de la misma manera exacta, él estaba preguntando por ti la última vez que estuviste en Sharptown.";
			link.l1 = "¡Maldita sea! Esa es la noticia... ¿Y dónde está Miguel ahora mismo?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "No tengo ni idea. Se ha marchado al mar donde... dijo algo sobre Blueweld. Probablemente fue allí solo para buscarte a ti.";
			link.l1 = "¿Acaso eres tú quien lo envió a Blueweld?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "No. Todo lo que le dije fue que no te había visto en mucho tiempo.";
			link.l1 = "Ya veo. Está bien, entonces. ¡Gracias, compañero!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			AddQuestRecord("Tieyasal", "3");
			npchar.quest.tieyasal = "true";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
