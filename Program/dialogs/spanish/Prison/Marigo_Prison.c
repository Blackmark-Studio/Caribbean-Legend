// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Habla, estoy escuchando";
			link.l1 = "Me equivoqué. Hasta luego.";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "Tienen a Simon Morelle arrestado aquí. Es un contrabandista cuyo balandro fue hundido por una patrulla no hace mucho. ¿Puedo verlo?";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "Oficial, fui enviado aquí por el señor gobernador de Philipsburg. Me pidió que asaltara la isla y sus aguas en busca de espías ingleses. Su Excelencia también me ha dicho que usted podría proporcionarme información útil.";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "Oficial, he encontrado la patrulla desaparecida. También he encontrado a los espías británicos. Están aquí en la isla.";
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = "Yo de nuevo, oficial. ¿Detuvisteis a los espías?";
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = "¿Y por qué lo necesita, señor?";
			link.l1 = "Quiero decirle que es un maldito bastardo y canalla. Espero que eso le ayude cuando esté en la horca.";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "¡Ja, ja! Tienes sentido del humor, señor... Bueno, dos mil pesos y puedes seguir adelante.";
			if(sti(Pchar.money) >= 2000)
			{
				link.l1 = "Tómalo, oficial. ¡Gracias!";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "Hm... Sabes, he cambiado de opinión. Mejor gastaré mi dinero en la taberna.";
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "De nada... ¡Sigue adelante!";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = "Como desees, no recibirás tal propuesta la próxima vez.";
			link.l1 = "No lo necesito de todos modos. ¡Nos vemos, oficial!";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "¿Útil? ¡Ja! Pensándolo bien, espera. Tengo algo útil que decirte. Una de nuestras patrullas ha desaparecido en la selva. Se suponía que ya deberían estar de regreso en sus barracones, pero parece que prefieren la compañía de los loros. O realmente ha sucedido algo. Si los encuentras durante tus búsquedas, por favor, diles que se inventen una justificación decente para su retraso o de lo contrario no les gustarán las consecuencias... El comandante de la patrulla se llama Jannes Hoffman.";
			link.l1 = "¿Es todo, oficial?";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Sí, maldita sea. Lo siento, pero no tengo nada más que decirte. Buena suerte, capitán.";
			link.l1 = "Gracias...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			DelLandQuestMark(npchar);
			dialog.text = "¿Qué?! Espero que no estés bromeando. ¡Dame un informe!";
			link.l1 = "Me encontré con una patrulla cerca de una cueva en la jungla. Me detuvieron y preguntaron adónde me dirigía y por qué, luego me dejaron ir. ¡Maldita sea, si esos no eran los británicos disfrazados con uniformes holandeses! También vi algo curioso en la jungla que parecía exactamente un grupo de hombres desnudos escondidos entre los arbustos. Supongo que el grupo de asalto británico había desarmado a tu patrulla y se había apoderado de sus uniformes.";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "...";
			link.l1 = "Como comprenderás, no me atreví a enfrentarme a un escuadrón de casacas rojas entrenados, así que en lugar de eso me apresuré a informarte.";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "Bueno-bueno... ¿Una cueva dijiste? ¿Cuántos de ellos contaste??";
			link.l1 = "Cinco hombres. Y sí, creo que entraron en esa cueva.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "¡Estoy enviando un escuadrón a la cueva inmediatamente! Capitán, si los hombres que encontraste son realmente los espías británicos, recibirás una merecida recompensa. Eres libre de unirte al escuadrón si deseas asistir a las autoridades en la detención de esos bastardos y recibir una recompensa extra, después de todo, estas son órdenes del gobernador. Entonces, ¿vienes con nosotros?";
			link.l1 = "No oficial, perseguir espías es tu trabajo. Asegúrate de enviar el escuadrón bien armado, estos canallas son demasiado peligrosos...";
			link.l1.go = "FMQN_7";
			link.l2 = "Creo que puedo hacer eso. Tus hombres encontrarán a los espías más rápido con mi ayuda.";
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = "Tu elección, capitán, tendré en cuenta tu consejo. Ven a verme mañana para conocer los resultados de nuestra operación.";
			link.l1 = "Nos vemos mañana.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			DelLandQuestMark(npchar);
			dialog.text = "Tu información era correcta, capitán. Encontramos a esos bastardos dentro de la cueva. No mostraron intención de rendirse y se enzarzaron en una pelea. Como resultado, los eliminamos a todos... También encontramos a la patrulla desaparecida. Están bien y vivos, aunque un poco magullados... Gracias, capitán, en nombre de todos los buenos ciudadanos de Philipsburg. Tu vigilancia será recompensada como se prometió. Por favor, tómalo.";
			link.l1 = "¡Gracias!";
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = "Eres siempre un huésped bienvenido en Sint-Maarten. Ahora, por favor, discúlpame, tengo otros asuntos que atender.";
			link.l1 = "Yo también. Adiós.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = "Muy bien. Tu ayuda es muy apreciada. Ve a las puertas de la ciudad, el escuadrón punitivo se reunirá allí en una hora.";
			link.l1 = "Un pequeño consejo, deberías enviar a los mejores soldados que tengas para esta misión. Esos espías son peligrosos.";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "No te preocupes. Estoy enviando a nuestros soldados más experimentados bajo el mando de un oficial, Hans Shulte, el maestro espadachín de Philipsburg.";
			link.l1 = "¡Genial! No perdamos tiempo entonces.";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
