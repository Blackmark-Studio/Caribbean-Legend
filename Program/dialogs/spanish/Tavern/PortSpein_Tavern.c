// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?","¿En qué puedo ayudarte, "+GetAddress_Form(NPChar)+"?"),"Intentaste hacerme una pregunta no hace mucho, "+GetAddress_Form(NPChar)+"... ","Durante todo este día, esta es la tercera vez que hablas de alguna pregunta...","Más preguntas, supongo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...","No tengo nada de qué hablar en este momento."),"Umph, ¿dónde se ha ido mi memoria...?","Sí, realmente es la tercera vez...","No, ¿qué preguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
			{
				link.l1 = "He oído que la enfermedad está arrasando en tu fuerte. ¿Crees que la epidemia se va a extender al pueblo?";
				link.l1.go = "Consumption";
			}
			if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "¿Qué puedes decir sobre el comandante del fuerte?";
				link.l1.go = "Consumption_8";
			}
			if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dime, ¿el nombre 'Juan' te dice algo?";
				link.l1.go = "Consumption_12";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Escucha, en abril de 1654 una fragata atracó en tu puerto bajo el mando del Capitán Miguel Dichoso y luego desapareció. ¿Hay algo que puedas decirme al respecto?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "El comandante afirma que no hay peligro. Aquellos que son demasiado curiosos terminan encerrados en las casamatas. No soy uno de ellos, lo siento.";
			link.l1 = "¿Es eso así? ¡Un tabernero que no tiene deseos de escuchar rumores, eso sí que es algo nuevo! ¿Será que el tintineo de los pesos puede devolver tu curiosidad?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "La plata es tentadora, por supuesto, pero mi propia piel tiene más valor. ¿Quizás podría contarte sobre otra cosa, señor? ¡En realidad, siempre me alegra hablar, solo empieza la conversación!";
			link.l1 = "Así que así se desarrolla el asunto... Muy bien, en esta bolsa hay tres mil piezas de a ocho y tendremos una agradable charla sobre el clima, ¿trato hecho?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3000);
			dialog.text = "Oh, eres persistente, señor. Sólo recuerda que esta conversación nunca ocurrió. (susurrando) He oído varias veces ya durante todo un año, que la gente se consumía en nuestras prisiones, muriendo de tisis. Puedes culpar a las autoridades, puedes culpar a Dios, o al Diablo, pero la mayor parte se atribuye a la mala fortuna. Esta maldita enfermedad roba vidas muy rápido. A veces meten a un hombre perfectamente sano allí, y en una o dos semanas ha desaparecido. Así de simple...";
			link.l1 = "Vaya... ¿Un año entero, dices? ¿Y qué, nadie se ha encargado de hacer algo al respecto?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "¿A quién le importa, señor? ¿A quién le importan los prisioneros? La escoria de la sociedad, o eso dicen los grandes hombres de seda. Había un médico que trabajaba en las mazmorras. Intentó curar a esas pobres almas. No duró mucho, parece que la enfermedad se deshizo de él también.\nAhora el comandante no deja entrar a la gente, y nuestras autoridades no prestan atención a esos asuntos, especialmente cuando tienen que pagar menos por las raciones de la prisión.";
			link.l1 = "Interesante, pero ¿qué tiene esta enfermedad que te asusta tanto que, encerrados dentro de muros seguros, estamos susurrando como monjas en el confesionario?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Me resulta difícil decírtelo, pero había un tipo aquí. Lo arrestaron por contrabando y lo encerraron como medio año hasta que sus compañeros lo sacaron. Bueno, midieron oro para quien lo necesitase, pesaron lo que les dijeron, y el tipo salió. Pero desde entonces ha estado bastante loco.";
			link.l1 = "¿Más loco que una rata de sentina?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Supongo. Desde entonces fue inútil para sus compañeros, pasando todo el día aquí, bebiéndose hasta la muerte. Parecía que quería borrar algo de su cabeza. Cada vez que se emborrachaba, contaba historias sobre aquella enfermedad que se lleva a la gente en silencio.\nEsas fueron sus palabras exactas. Según él, la 'consunción' es lo peor que le puede pasar a un hombre.";
			link.l1 = "Desvaríos de un borracho. ¿Y qué con eso?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
			{
				dialog.text = "Nada, aparte de que encontró un poco de valor líquido y empezó a hablar más y más y luego, así como así, alguien le cortó el cuello y lo tiró a la cuneta... y quienquiera que lo hizo y para qué, todo me da igual.";
				link.l1 = "¿Qué puedes decir sobre el comandante?";
				link.l1.go = "Consumption_8";
			}
			else
			{
				dialog.text = "Nada, aparte de que se envalentonó y empezó a hablar cada vez más y entonces, de repente, alguien le cortó la garganta y lo arrojó a la cuneta... y quienquiera que lo haya hecho y por qué, a mí me da igual. (levanta la voz) Sí, las bahías y los arrecifes son realmente peligrosos aquí, señor. ¡Tienes que tener cuidado cuando las tormentas llegan rugiendo desde las Grandes Antillas, pierdes la ventaja del viento y estás perdido! Que descanse bien, señor, gracias por pasar por aquí.";
				link.l1 = "Tormentas... correcto. Gracias a ti también.";
				link.l1.go = "Consumption_7";
			}
			pchar.questTemp.Consumption.Contra = "true";
		break;
		
		case "Consumption_7":
			DialogExit();
			npchar.quest.Consumption = "true";
			AddQuestRecord("Consumption", "2");
		break;
		
		case "Consumption_8":
			dialog.text = "¿Qué se puede decir de él? Es un coronel, llegó de Europa hace un par de años tras recibir este lugar. Supuestamente fue degradado allí en el Viejo Mundo por algunos actos sucios en los que estaba involucrado. No sé si es cierto, pero al principio había rumores. Pero, quién no tiene rumores sobre ellos, ¿verdad?";
			link.l1 = "Travesuras sucias, dices... Eso es interesante. ¿Algo más?";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			dialog.text = "Bueno, ¿qué puedo decir...? El coronel parece un hombre que se preocupa profundamente por su propia seguridad. Claro, estos lugares no son seguros debido a los piratas, bandidos, indios y otra escoria, pero el Señor Comandante nunca sale de su casa sin varios guardaespaldas.\nTiene su mansión en esta ciudad y la ha convertido en una pequeña fortaleza: sus sirvientes están bien armados y mantienen las ventanas cerradas con barrotes.";
			link.l1 = "Pero durante el día, ¿no sirve en la prisión?";
			link.l1.go = "Consumption_10";
		break;
		
		case "Consumption_10":
			dialog.text = "Sí, pero esa mansión está básicamente esperando allí para una emboscada o una invasión. De todos modos, el Señor Comandante aparentemente no regresa allí a menudo, una verdadera fortaleza es más bien su fuerte, je-je.";
			link.l1 = "Gracias, has sido de gran ayuda. Hasta luego, "+npchar.name+".";
			link.l1.go = "Consumption_11";
		break;
		
		case "Consumption_11":
			DialogExit();
			if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
			else AddQuestRecord("Consumption", "5");
			DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
			pchar.questTemp.Consumption = "current";
		break;
		
		case "Consumption_12":
			dialog.text = "¿Juan? ¿Cuál de todos? Hay muchos aquí, la gente suele tener apellidos también... o al menos un apodo...";
			link.l1 = "Estaba pensando... Quizás su apodo sea 'Consumo', ¿alguna vez has escuchado eso?";
			link.l1.go = "Consumption_13";
		break;
		
		case "Consumption_13":
			dialog.text = "¡Dios mío, estás hablando de eso otra vez! No, gracias a Dios, no he oído. ¡Lo juro! Y ahora cambiemos de tema. ¡Por favor!";
			link.l1 = "Está bien, está bien, que no te dé un ataque al corazón...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption_1 = "true";
		break;
		//<-- Цена чахотки
		
		case "guardoftruth":
			dialog.text = "Lo recuerdo. A menudo pasaba por mi taberna, pero no hablaba mucho. Se tomaba unos tragos de ron, compartía un susurro con algunos clientes y se iba. Muy sombrío y serio como todos en ese bergantín. Mercenarios de aspecto peligroso que mantenían sus espadas listas.\nHabía un rumor de que el bergantín estaba lleno de tesoros, pero no creo en tales cuentos. La carga valiosa nunca se transporta en un solo barco sin un convoy. Estuvieron aquí un día, luego se fueron a Europa, escuché. Eso es todo lo que sé.";
			link.l1 = "Ya veo. Bueno, al menos es algo...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "40");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
