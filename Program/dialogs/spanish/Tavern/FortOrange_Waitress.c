// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Preguntas, "+GetAddress_Form(NPChar)+"?","¿En qué puedo ayudarle, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Mm, ¿cuál es la gran idea, "+GetAddress_Form(NPChar)+"? ","¿Otra vez con las preguntas extrañas? Chiquillo, ve a tomar un poco de ron o algo...")+"Hola, capitán.","Durante todo este día, esta es la tercera vez que hablas de alguna pregunta..."+GetSexPhrase(" ¿Son estas algunas señales de atención?","")+"","¿Más preguntas, supongo, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión","No tengo nada de qué hablar en este momento."),"No, no hermosa...","No querida...","No, ¿qué preguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "Escucha, mujer, dicen que estabas cerca de mi viejo compañero Francois Gontier. Muy cerca...";
                link.l1.go = "Jamaica_ratW_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
				if (CheckCharacterItem(pchar, "jewelry43"))
				{
					link.l1 = "He traído tu collar con gemas. Aquí tienes. Que Dios me proteja de mujeres codiciosas como tú en el futuro.";
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = "No en este momento. Estoy buscando tu collar.";
					link.l1.go = "exit";
				}
            }
			
		break;
		
		case "Jamaica_ratW_1":
            dialog.text = "Sí, lo estábamos. ¿Y qué con eso? No soy una mujer casada y paso el tiempo con quien quiero. François es un marinero muy respetable, no como nuestros pescadores y granjeros locales. Él es tan... ¡Oh! ¡Y me dio tan bonitos regalos!";
            link.l1 = "¡Está bien, ya basta! Sé qué cualidades posee mi compañero, no necesitas enumerarlas para mí. No me importa lo que haya pasado entre ustedes dos. Incluso pueden casarse, no me importa. Necesito encontrarlo de inmediato, ¿entiendes? ¿Sabes a dónde se ha marchado?";
            link.l1.go = "Jamaica_ratW_2";
        break;
		
		case "Jamaica_ratW_2":
            dialog.text = "Tee-hee... Eres su compañero de barco, y no sabes a dónde ha partido. ¡Eso es gracioso!";
            link.l1 = "No es nada gracioso, mujer. Habíamos acordado encontrarnos en Jamaica y luego nos esperaba un viaje conjunto... si entiendes lo que quiero decir. No podré hacerlo solo y él se ha marchado a sabe Dios dónde.";
            link.l1.go = "Jamaica_ratW_3";
        break;
		
		case "Jamaica_ratW_3":
            dialog.text = "Ya veo. Bueno, si un viaje tan lucrativo está a la vista para ti, considerando que tú y Francois son amigos... Te diré a dónde se ha dirigido, pero a cambio de una pequeña recompensa.";
            link.l1 = "Sí, conozco el asunto. ¿Cuánto quieres?";
            link.l1.go = "Jamaica_ratW_4";
        break;
		
		case "Jamaica_ratW_4":
            dialog.text = "¡Oh, qué venal! No necesito dinero. No, quiero algo especial. Francois prometió darme un hermoso collar con gemas. Ya me he jactado de él con mis amigos y él se ha marchado... Tráeme el colgante y te diré a dónde se ha ido, ¡je-je!";
            link.l1 = "¡Zorra descarada! ¡Las mujeres holandesas, son tan codiciosas como se puede ser! Muy bien, tendrás tu collar.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;
		
		case "Jamaica_ratW_5":
            dialog.text = "¡Ah, es hermoso! ¡Ahora mis amigas podrán ponerse verdes de envidia!";
            link.l1 = "Envíales mis condolencias. Ahora empieza a hablar. ¿Adónde se ha marchado François?";
            link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry43", 1);
        break;
		
		case "Jamaica_ratW_6":
            dialog.text = "Sí, por supuesto, mynheer. François ha zarpado hacia Cuba, a La Habana.";
            link.l1 = "Gracias por el caro consejo, moza. Eso es todo lo que quería.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
        break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
