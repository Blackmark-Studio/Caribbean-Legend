// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Preguntas, "+GetAddress_Form(NPChar)+"?","¿En qué puedo ayudarle, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Mm, ¿cuál es la gran idea, "+GetAddress_Form(NPChar)+"? ","¿Otra vez con las preguntas extrañas? Chiquillo, ve a tomar un poco de ron o algo...")+"Hola, capitán.","Durante todo este día, esta es la tercera vez que hablas de alguna pregunta..."+GetSexPhrase(" ¿Son estas algunas señales de atención?","")+"","¿Más preguntas, supongo, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión","No tengo nada de qué hablar en este momento."),"No, no hermosa...","No querida...","No, ¿qué preguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_2"))
			{
				link.l1 = "Necesito hacerte unas preguntas. ¿Trabajabas en la taberna el día que desapareció el barril de ginebra? ¿Qué puedes contarme sobre lo que pasó ese día?";
				link.l1.go = "OS_Tavern2_1";
			}
			//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern2_1":
			dialog.text = "Yo... yo no sé qué decir. Todo fue como siempre, no pasó nada extraño.";
			link.l1 = "¿Nada extraño? ¿Y qué hay del marinero del 'Sea Beast' que ese día te acosaba? Parece que pensó que no te importaría pasar la noche con él.";
			link.l1.go = "OS_Tavern2_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern2_2":
			dialog.text = "Ah, ¡ese! Simplemente había bebido demasiado. Eso no es raro aquí, ¿sabe? Por supuesto que no le di motivos, pero empezó a fastidiarme. Y yo lo rechacé.";
			link.l1 = "¿No le diste motivos? Él piensa lo contrario. ¿Por qué gritaste esta vez y no en otras ocasiones?";
			link.l1.go = "OS_Tavern2_3";
		break;

		case "OS_Tavern2_3":
			dialog.text = "¡Yo... no sé qué más decir! ¡De verdad no sé nada! Estuve a la vista de todos toda la noche. ¡No vi ni oí nada! Y sobre el barril... no sé nada, ¡no sé qué pasó con él! ¿Por qué este interrogatorio? Yo solo... solo trabajaba, como siempre.";
			link.l1 = "Creo que estás ocultando algo. Sabes, una noche en la bodega, sin luz ni comida, puede hacer maravillas con las personas. ¿Quieres probar? ¿O hablamos en buenos términos?";
			link.l1.go = "OS_Tavern2_4_HO";
			link.l2 = "Y yo creo que sabes mucho más de lo que dices. Tienes una oportunidad única ahora: cuéntalo todo y no mencionaré tu implicación. Pero si te callas, será peor para ti. Voy a descubrir la verdad de todos modos.";
			link.l2.go = "OS_Tavern2_4_harizma";
		break;

		case "OS_Tavern2_4_HO":
			dialog.text = "¡Yo... yo... se lo contaré todo! Todo fue idea de... mi pretendiente, Jack. ¡Jack Wales! Me convenció para seducir a cualquier marinero del 'Sea Beast'. Y cuando ese se pasara de listo, yo debía hacer un escándalo para sacar al tabernero de la barra. Mientras los ánimos se calmaban, dos marineros debían empezar una pelea para retenerlo en la sala. Así fue como ocurrió\nDurante ese tiempo, el capitán del 'Sea Beast' robó el barril. ¡Eso es todo lo que sé, "+GetSexPhrase("señor","señora")+"! Por favor, no me delate. ¡Yo solo quería que Jack me respetara al fin! ¡Yo lo ayudé...";
			link.l1 = "¿Ayudaste a uno y traicionaste al otro sin remordimiento? Bien, cumpliré mi palabra: no te delataré. Pero tendrás que vivir con esto. Por tu estupidez, el tabernero pudo haber tenido serios problemas. ¿Dónde está Jack? Y recuerda: si mientes, volveré. Y no te gustará.";
			link.l1.go = "OS_Tavern2_5";
			AddComplexSelfExpToScill(40, 40, 40, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;

		case "OS_Tavern2_4_harizma":
			dialog.text = "¡Yo... yo... se lo contaré todo! Todo fue idea de... mi pretendiente, Jack. ¡Jack Wales! Me convenció para seducir a cualquier marinero del 'Sea Beast'. Y cuando ese se pasara de listo, yo debía hacer un escándalo para sacar al tabernero de la barra. Mientras los ánimos se calmaban, dos marineros debían empezar una pelea para retenerlo en la sala. Así fue como ocurrió\nDurante ese tiempo, el capitán del 'Sea Beast' robó el barril. ¡Eso es todo lo que sé, "+GetSexPhrase("señor","señora")+"! Por favor, no me delate. ¡Yo solo quería que Jack me respetara al fin! ¡Yo lo ayudé...";
			link.l1 = "¿Ayudaste a uno y traicionaste al otro sin remordimiento? Bien, cumpliré mi palabra: no te delataré. Pero tendrás que vivir con esto. Por tu estupidez, el tabernero pudo haber tenido serios problemas. ¿Dónde está Jack? Y recuerda: si mientes, volveré. Y no te gustará.";
			link.l1.go = "OS_Tavern2_5";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "OS_Tavern2_5":
			dialog.text = "¡No pensé que fuera tan grave! ¡Solo era un barril...! Jack vive enfrente. Alquila una casa, yo... ¡yo no sé nada más! ¡Perdóneme, capitán! ¡Le juro que no lo volveré a hacer!";
			link.l1 = "Vuelve a trabajar y ni se te ocurra ponerte a llorar, no sea que el jefe sospeche algo.";
			link.l1.go = "OS_Tavern2_6";
		break;
		
		case "OS_Tavern2_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_2");
			AddQuestRecord("OS", "4");
			
			//
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.cask_gin = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.map_full = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.jewelry2 = 10;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.GunPowder = 50;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.bullet = 50;
			
			PChar.quest.OS_Zasada.win_condition.l1 = "item";
			PChar.quest.OS_Zasada.win_condition.l1.item = "cask_gin";
			PChar.quest.OS_Zasada.function = "OS_Zasada";
			
			SetFunctionLocationCondition("DWH_Close_House", "PuertoPrincipe_QuestHouse_1", false);
		break;
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
